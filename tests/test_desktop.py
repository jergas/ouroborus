"""Desktop protocol and real-worker integration, without a physical display."""
import json
import os
from pathlib import Path
import signal
import time

import pytest

from worldish.config import SimulationConfig
from worldish.protocol import Decoder, encode


def test_config_rejects_invalid_launch_values():
    for values in ({"steps": 0}, {"seed": -1}, {"audio": "unknown"},
                   {"interval": float("nan")}, {"volume": 2}, {"preset": "unknown"}):
        with pytest.raises(ValueError):
            SimulationConfig(**values)


def test_protocol_handles_fragmentation_and_rejects_bad_versions():
    decoder = Decoder()
    data = encode({"type": "state", "state": "paused"})
    assert decoder.feed(data[:6]) == []
    assert decoder.feed(data[6:])[0]["state"] == "paused"
    with pytest.raises(ValueError):
        decoder.feed(b'{"version":99}\n')


@pytest.fixture(scope="module")
def qtapp():
    pytest.importorskip("PySide6")
    pytest.importorskip("pyte")
    os.environ["QT_QPA_PLATFORM"] = "offscreen"
    os.environ["QT_QUICK_BACKEND"] = "software"
    os.environ["QT_QPA_PLATFORMTHEME"] = "basic"
    from PySide6.QtGui import QGuiApplication
    app = QGuiApplication.instance() or QGuiApplication([])
    yield app


def wait_for(app, condition, timeout=90):
    deadline = time.monotonic() + timeout
    while time.monotonic() < deadline:
        app.processEvents()
        if condition():
            return
        time.sleep(0.01)
    raise AssertionError("Timed out waiting for desktop state")


def test_terminal_colors_unicode_and_alternate_screen(qtapp):
    from worldish.desktop.views import TerminalScreen
    import pyte
    screen = TerminalScreen(20, 8)
    stream = pyte.ByteStream(screen)
    stream.feed("home".encode())
    stream.feed(b"\x1b[?1049h\x1b[32m")
    stream.feed("λ".encode()[:1])
    stream.feed("λ".encode()[1:])
    assert screen.buffer[0][0].data == "λ"
    assert screen.buffer[0][0].fg == "green"
    stream.feed(b"\x1b[?1049l")
    assert screen.display[0].startswith("home")


def test_real_worker_pause_step_resize_and_finish(qtapp, tmp_path):
    from worldish.desktop.controller import Controller
    from worldish.desktop.views import TerminalView
    controller = Controller(output_root=tmp_path)
    terminal = TerminalView()
    controller.terminalData.connect(terminal.feed)
    frames = []
    controller.snapshotChanged.connect(frames.append)
    try:
        controller.start("alpha", 12, 42, 0.15, "off", 0.5)
        wait_for(qtapp, lambda: len(frames) >= 2 or controller.process is None)
        assert controller.state == "running", controller.message
        assert any(any(line.strip()) for line in terminal.screen.display)
        controller.command("pause")
        wait_for(qtapp, lambda: controller.state == "paused")
        wait_for(qtapp, lambda: True, timeout=1)
        tick = frames[-1]["tick"]
        deadline = time.monotonic() + 0.25
        while time.monotonic() < deadline:
            qtapp.processEvents()
            time.sleep(0.01)
        assert frames[-1]["tick"] == tick
        controller.resize(25, 10)
        controller.command("step")
        wait_for(qtapp, lambda: frames[-1]["tick"] == tick + 1 or controller.process is None)
        assert controller.state == "paused", controller.message
        assert frames[-1]["tick"] == tick + 1
        controller.resize(110, 50)
        controller.setPace(0.01)
        controller.command("resume")
        wait_for(qtapp, lambda: controller.process is None)
        assert controller.state == "finished", controller.message
        result = json.loads((Path(controller.runPath) / "result.json").read_text())
        assert result["iterations"] == 12
        assert result["births"] - result["deaths"] == result["population"]
        assert frames[-1]["width"] == 80
        assert len(frames[-1]["cells"]) == 1600
    finally:
        controller.shutdown()


def test_stop_during_initialization_cleans_process_group(qtapp, tmp_path):
    from worldish.desktop.controller import Controller
    controller = Controller(output_root=tmp_path)
    try:
        controller.start("alpha", 10000, 42, 0.1, "off", 0.5)
        pid = controller.process.pid
        wait_for(qtapp, lambda: any(Path(controller.runPath).glob("creatures/*.pyx")) or controller.process is None)
        assert controller.process is not None, controller.message
        controller.stop()
        wait_for(qtapp, lambda: controller.process is None, timeout=15)
        assert controller.state == "stopped"
        # Group members may briefly be unreaped zombies, but none may run.
        for entry in Path("/proc").iterdir():
            if entry.name.isdigit():
                try:
                    fields = (entry / "stat").read_text().split(") ", 1)[1].split()
                    assert not (int(fields[2]) == pid and fields[0] != "Z")
                except (FileNotFoundError, ProcessLookupError):
                    pass
    finally:
        controller.shutdown()


def test_silent_audio_worker(qtapp, tmp_path):
    import ctypes.util
    if not ctypes.util.find_library("csound64"):
        pytest.skip("Native Csound unavailable")
    from worldish.desktop.controller import Controller
    controller = Controller(output_root=tmp_path)
    try:
        controller.start("epsilon", 5, 42, 0.01, "silent", 0.4)
        wait_for(qtapp, lambda: controller.process is None)
        assert controller.state == "finished", controller.message
        assert json.loads((Path(controller.runPath) / "result.json").read_text())["iterations"] == 5
    finally:
        controller.shutdown()


def test_settings_roundtrip_and_invalid_file(qtapp, tmp_path):
    from PySide6.QtCore import QUrl
    from worldish.desktop.controller import Controller
    controller = Controller(output_root=tmp_path)
    path = tmp_path / "settings.json"
    url = QUrl.fromLocalFile(str(path))
    values = SimulationConfig(preset="beta", seed=123, audio="off").to_dict()
    controller.savePreset(url, values)
    assert controller.loadPreset(url) == values
    path.write_text('{"version":99}')
    assert controller.loadPreset(url) == {}
    assert "Unsupported" in controller.message


def test_qml_transport_visible_and_settings_bridge(qtapp, tmp_path):
    from PySide6.QtCore import QUrl, QPointF
    from PySide6.QtQml import QQmlApplicationEngine, qmlRegisterType
    from PySide6.QtQuick import QQuickItem
    from PySide6.QtQuickControls2 import QQuickStyle
    from worldish.desktop.controller import Controller
    from worldish.desktop.views import TerminalView, GridView
    QQuickStyle.setStyle("Basic")
    qmlRegisterType(TerminalView, "Ouroborus", 1, 0, "TerminalView")
    qmlRegisterType(GridView, "Ouroborus", 1, 0, "GridView")
    controller = Controller(output_root=tmp_path)
    engine = QQmlApplicationEngine()
    engine.rootContext().setContextProperty("simulation", controller)
    warnings = []
    engine.warnings.connect(lambda errors: warnings.extend(str(error) for error in errors))
    qml = Path(__file__).resolve().parents[1] / "worldish/desktop/qml/Main.qml"
    engine.load(QUrl.fromLocalFile(str(qml)))
    assert engine.rootObjects(), warnings
    window = engine.rootObjects()[0]
    try:
        window.setWidth(800)
        window.setHeight(560)
        qtapp.processEvents()
        button = window.findChild(QQuickItem, "startButton")
        point = button.mapToScene(QPointF(0, button.height()))
        assert 0 < point.y() <= window.height()
        values = window.draft().toVariant()
        url = QUrl.fromLocalFile(str(tmp_path / "qml-settings.json"))
        controller.savePreset(url, values)
        assert controller.loadPreset(url)["preset"] == "alpha", controller.message
        from PySide6.QtCore import QObject
        inspector = window.findChild(QObject, "agentInspector")
        assert inspector is not None
        inspector.open()
        qtapp.processEvents()
        inspector.close()
        assert not warnings, warnings
    finally:
        window.close()
        engine.deleteLater()
        qtapp.processEvents()


def test_worker_crash_is_reported_and_can_restart(qtapp, tmp_path):
    from worldish.desktop.controller import Controller
    controller = Controller(output_root=tmp_path)
    try:
        controller.start("epsilon", 1000, 42, 0.1, "off", 0.5)
        wait_for(qtapp, lambda: controller.state == "running" or controller.process is None)
        assert controller.process is not None, controller.message
        first_path = controller.runPath
        os.kill(controller.process.pid, signal.SIGKILL)
        wait_for(qtapp, lambda: controller.process is None)
        assert controller.state == "failed"
        assert "Worker exited" in controller.message
        controller.start("epsilon", 2, 123, 0.01, "off", 0.5)
        wait_for(qtapp, lambda: controller.process is None)
        assert controller.state == "finished", controller.message
        assert controller.runPath != first_path
    finally:
        controller.shutdown()


def test_grid_selection_uses_centered_coordinates_and_cycles_overlap(qtapp):
    from worldish.desktop.views import GridView
    grid = GridView()
    grid.setWidth(200)
    grid.setHeight(200)
    grid.snapshot({"width": 10, "height": 5, "cells": [0] * 50, "agents": [],
                   "organisms": [{"id": "one", "position": [2, 1]},
                                 {"id": "two", "position": [2, 1]}]})
    assert grid.agentAt(50, 80) == "one"
    grid.setSelectedAgentId("one")
    assert grid.agentAt(50, 80) == "two"
    assert grid.agentAt(50, 20) == ""
    grid.reset()
    assert grid.agentAt(50, 80) == ""


def test_paused_agent_inspection_and_trace_settings(qtapp, tmp_path):
    from worldish.desktop.controller import Controller
    from PySide6.QtCore import QUrl
    controller = Controller(output_root=tmp_path)
    frames = []
    controller.snapshotChanged.connect(frames.append)
    settings = SimulationConfig(preset="forager", steps=100, interval=0.1, audio="off",
                                execution_method="interpreted", trace_mode="instructions",
                                trace_limit=1000).to_dict()
    url = QUrl.fromLocalFile(str(tmp_path / "settings.json"))
    controller.savePreset(url, settings)
    assert controller.loadPreset(url) == settings
    try:
        controller.startConfigured(settings)
        wait_for(qtapp, lambda: bool(controller.agentChoices) or controller.process is None)
        assert controller.process is not None, controller.message
        controller.command("pause")
        wait_for(qtapp, lambda: controller.state == "paused")
        tick, cells, ledger = frames[-1]["tick"], frames[-1]["cells"], frames[-1]["ledger"]
        agent_id = controller.agentChoices[0]
        controller.selectAgent(agent_id)
        wait_for(qtapp, lambda: controller.agentDetails.get("id") == agent_id)
        assert frames[-1]["tick"] == tick and frames[-1]["cells"] == cells
        assert frames[-1]["ledger"] == ledger and ledger["balance_error"] == 0
        assert controller.agentDetails["raw_genome"]
        assert controller.agentDetails["execution_method"] == "interpreted"
        controller.stop()
        wait_for(qtapp, lambda: controller.process is None)
        result = json.loads((Path(controller.runPath) / "result.json").read_text())
        assert result["observation"]["ledger"]["balance_error"] == 0
        assert (Path(controller.runPath) / "events.jsonl").exists()
    finally:
        controller.shutdown()
