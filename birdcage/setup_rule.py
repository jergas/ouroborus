"""Compatibility entry point; prefer installing from the repository root."""
from pathlib import Path
import os
import runpy

root = Path(__file__).resolve().parents[1]
os.chdir(root)
runpy.run_path(str(root / "setup.py"), run_name="__main__")
