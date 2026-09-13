"""Build a generated genome in a child process, without modifying runner state."""
from pathlib import Path
import sys
from Cython.Build import cythonize
from setuptools import Extension, setup

if __name__ == "__main__":
    name, source = sys.argv[1:]
    setup(
        name=name,
        packages=[],
        py_modules=[],
        ext_modules=cythonize(
            [Extension(name, [source])],
            compiler_directives={"language_level": 3},
            build_dir="build/cython",
        ),
        script_args=["build_ext", "--inplace"],
    )
