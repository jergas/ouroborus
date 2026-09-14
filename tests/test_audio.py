"""Real Csound integration; requires the native Csound 6 libraries."""
from array import array
import wave

import pytest


def csound_module():
    try:
        import ctcsound
    except (ImportError, OSError) as error:
        pytest.skip(f"Csound 6 native libraries unavailable: {error}")
    return ctcsound


def test_render_agent_voice(tmp_path):
    ctcsound = csound_module()
    from worldish.Csnd_data import CsdGenerator
    output = tmp_path / "agent.wav"
    options = f'<CsoundSynthesizer>\n<CsOptions>\n-o "{output}" -W -s -d -m0\n</CsOptions>'
    csd = CsdGenerator(3, options).csd.replace(
        "f3 36000 129 -7 0 128 1", "i1 0 0.2 440 480 5 0 0 0 0.5 0\nf0 0.25")
    csound = ctcsound.Csound()
    try:
        assert csound.compileCsdText(csd) == 0
        assert csound.start() == 0
        assert csound.perform() > 0
    finally:
        csound.cleanup()
        csound.reset()
    with wave.open(str(output)) as stream:
        assert stream.getnchannels() == 2
        assert stream.getframerate() == 44100
        assert stream.getnframes() >= 11025
        samples = array("h", stream.readframes(stream.getnframes()))
    assert 0 < max(abs(sample) for sample in samples) < 32767


def test_audio_enabled_threaded_simulation(tmp_path):
    csound_module()
    from test_worldish import run_example
    result, _ = run_example(tmp_path, "--mode", "threaded", "--display", "debug", "--silent-audio")
    assert result["iterations"] == 40
    assert result["births"] > 0


def test_audio_waits_for_genome_builds():
    """Unpaced silent audio must not consume the score during compilation."""
    csound_module()
    import time
    from worldish.csnd_interface import SoundServer
    server = SoundServer()
    try:
        server.initCSnd('<CsoundSynthesizer>\n<CsOptions>\n-n -d -m0\n</CsOptions>', 1)
        time.sleep(0.05)
        assert server.perf.status() == 0
        assert server.cSnd.currentTimeSamples() == 0
        server.play()
        deadline = time.monotonic() + 2
        while server.cSnd.currentTimeSamples() == 0 and time.monotonic() < deadline:
            time.sleep(0.01)
        assert server.cSnd.currentTimeSamples() > 0
    finally:
        server.endCsnd()


@pytest.mark.parametrize("volume", [0.0, 0.25, 1.0])
def test_master_volume_controls_both_channels(tmp_path, volume):
    ctcsound = csound_module()
    from worldish.Csnd_data import CsdGenerator
    output = tmp_path / "volume.wav"
    options = f'<CsoundSynthesizer>\n<CsOptions>\n-o "{output}" -W -s -d -m0\n</CsOptions>'
    csd = CsdGenerator(3, options).csd.replace(
        "f3 36000 129 -7 0 128 1", "i1 0 0.2 440 480 5 0 0 0 0.5 0\nf0 0.25")
    csound = ctcsound.Csound()
    try:
        assert csound.compileCsdText(csd) == 0
        csound.setControlChannel("worldish_attenuation", 1 - volume)
        assert csound.start() == 0
        assert csound.perform() > 0
    finally:
        csound.cleanup()
        csound.reset()
    with wave.open(str(output)) as stream:
        samples = array("h", stream.readframes(stream.getnframes()))
    for channel in (samples[::2], samples[1::2]):
        peak = max(abs(sample) for sample in channel)
        assert peak == 0 if volume == 0 else 0 < peak < 32767
