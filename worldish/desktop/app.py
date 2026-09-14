"""Launch the desktop shell independently of the simulation runtime."""

import argparse
from pathlib import Path
import sys


def main(argv=None):
    parser = argparse.ArgumentParser(description="Ouroborus desktop")
    parser.add_argument("--smoke-test", action="store_true",
                        help="load the window and exit automatically")
    args = parser.parse_args(argv)
    try:
        from PySide6.QtCore import QCoreApplication, QEvent, QTimer, QUrl
        from PySide6.QtGui import QGuiApplication
        from PySide6.QtQml import QQmlApplicationEngine, qmlRegisterType
        from PySide6.QtQuickControls2 import QQuickStyle
        from .controller import Controller
        from .views import TerminalView, GridView
    except ModuleNotFoundError as exc:
        if exc.name not in ("PySide6", "pyte"):
            raise
        parser.exit(1, "Desktop dependencies missing. Install with: pip install -e '.[desktop]'\n")

    QQuickStyle.setStyle("Basic")
    app = QGuiApplication([sys.argv[0]])
    app.setApplicationName("Ouroborus")
    qmlRegisterType(TerminalView, "Ouroborus", 1, 0, "TerminalView")
    qmlRegisterType(GridView, "Ouroborus", 1, 0, "GridView")
    controller = Controller()
    engine = QQmlApplicationEngine()
    engine.rootContext().setContextProperty("simulation", controller)
    engine.load(QUrl.fromLocalFile(str(Path(__file__).parent / "qml" / "Main.qml")))
    if not engine.rootObjects():
        return 1
    terminal = engine.rootObjects()[0].findChild(TerminalView, "terminal")
    grid = engine.rootObjects()[0].findChild(GridView, "grid")
    controller.terminalData.connect(terminal.feed)
    controller.terminalReset.connect(terminal.reset)
    controller.terminalReset.connect(grid.reset)
    controller.snapshotChanged.connect(grid.snapshot)
    terminal.resized.connect(controller.resize)
    terminal.inputBytes.connect(controller.terminal_input)
    terminal._resize()
    app.aboutToQuit.connect(controller.shutdown)
    if args.smoke_test:
        QTimer.singleShot(300, app.quit)
    result = app.exec()
    # Destroy QML bindings while their Python controller is still alive.
    engine.deleteLater()
    QCoreApplication.sendPostedEvents(None, QEvent.Type.DeferredDelete)
    return result


if __name__ == "__main__":
    raise SystemExit(main())
