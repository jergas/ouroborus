"""Exercise real compiled genomes and complete example lifecycles."""
import json
import os
from pathlib import Path
import subprocess
import sys

import pytest

ROOT = Path(__file__).resolve().parents[1]


def run_example(tmp_path, *options):
    output = tmp_path / "run"
    command = [sys.executable, "-m", "worldish.start", "--steps", "40", "--seed", "42",
               "--fast", "--output-dir", str(output), *options]
    result = subprocess.run(command, cwd=ROOT, capture_output=True, text=True, timeout=90)
    log = (output / "debug_output.txt").read_text() if (output / "debug_output.txt").exists() else ""
    assert result.returncode == 0, result.stdout + result.stderr + log[-6000:]
    assert "Traceback" not in log and "Exception in thread" not in log
    return json.loads((output / "result.json").read_text()), output


@pytest.mark.parametrize("specificity", ["alpha", "beta", "delta", "epsilon"])
def test_debug_configurations(tmp_path, specificity):
    result, output = run_example(tmp_path, "--mode", "debug", "--specificity", specificity)
    assert result["iterations"] == 40
    assert result["population"] == result["births"] - result["deaths"]
    if specificity == "epsilon":
        assert result["births"] == result["genotypes_compiled"] == 0
    else:
        assert result["births"] >= 3
        # Identical genomes share one compiled extension across births.
        assert result["genotypes_compiled"] == 1
        assert len(list((output / "creatures").glob("*.pyx"))) == 1
        assert list(output.glob("*.so"))
    if specificity == "alpha":
        assert result["births"] > 3
        assert result["deaths"] > 0


@pytest.mark.parametrize("mode", ["visual", "audiovisual", "threaded"])
def test_display_sequences_without_audio(tmp_path, mode):
    result, _ = run_example(tmp_path, "--mode", mode, "--display", "debug", "--no-sound")
    assert result["iterations"] == 40
    assert result["population"] == result["births"] - result["deaths"]


def test_pygame_rendering(tmp_path, monkeypatch):
    pytest.importorskip("pygame")
    monkeypatch.setenv("SDL_VIDEODRIVER", "dummy")
    result, _ = run_example(tmp_path, "--mode", "visual", "--display", "pygame")
    assert result["iterations"] == 40


def test_bad_mode_is_reported_without_silent_fallback(tmp_path):
    result = subprocess.run([sys.executable, "-m", "worldish.start", "--mode", "typo"],
                            cwd=ROOT, capture_output=True, text=True, timeout=10)
    assert result.returncode == 2
    assert "invalid choice" in result.stderr


def test_integer_center_and_exception_messages():
    from birdcage.topology import ToroidTopology
    from birdcage.exceptions_birdcage import InvalidAddressError
    grid = ToroidTopology((9, 7), 0)
    assert grid.center() == (4, 3)
    assert "address" in str(InvalidAddressError((100, 100), "test grid"))


@pytest.mark.parametrize("workers", ["one", "custom", "onePerAgent"])
def test_experimental_agent_clocks(tmp_path, workers):
    result, _ = run_example(tmp_path, "--mode", "experimental", "--display", "debug",
                            "--no-sound", "--agent-threads", workers)
    assert result["iterations"] == 40
    assert result["births"] >= 3
    assert result["population"] == result["births"] - result["deaths"]


def test_threaded_display_failure_does_not_hang(tmp_path):
    script = '''
from worldish import runtime
specific = runtime.get_specific()
specific.soundOn = False
specific.debugOutputToFile = specific.sysOutToFile = False
from worldish import sequence_threaded

def fail(self):
    raise RuntimeError("deliberate display failure")

sequence_threaded.ThreadedSequence.showBackground = fail
from worldish.start import main
main(["--mode", "threaded", "--display", "debug", "--no-sound", "--fast",
      "--steps", "3", "--output-dir", OUTPUT])
'''.replace("OUTPUT", repr(str(tmp_path / "failure")))
    result = subprocess.run([sys.executable, "-c", script], cwd=ROOT,
                            capture_output=True, text=True, timeout=30)
    assert result.returncode != 0
    assert "deliberate display failure" in result.stderr


def test_individual_genome_compilation(tmp_path):
    script = '''
from worldish import runtime
specific = runtime.get_specific()
specific.compiling = "IndividualCompile"
specific.avatars = 2
from worldish.start import main
main(["--mode", "debug", "--steps", "5", "--seed", "42", "--output-dir", OUTPUT])
'''.replace("OUTPUT", repr(str(tmp_path / "individual")))
    result = subprocess.run([sys.executable, "-c", script], cwd=ROOT,
                            capture_output=True, text=True, timeout=60)
    assert result.returncode == 0, result.stderr
    output = tmp_path / "individual"
    summary = json.loads((output / "result.json").read_text())
    assert summary["births"] == summary["population"] == 2
    assert summary["genotypes_compiled"] == 2
    assert len(list(output.glob("*.so"))) == 2
