from setuptools import Extension, setup
from Cython.Build import cythonize

modules = ["agent", "automaton", "exceptions_birdcage", "genome", "neighborhood", "rule", "topology"]
extensions = [Extension(f"birdcage.{name}", [f"birdcage/{name}.pyx"]) for name in modules]
extensions.append(Extension("worldish.code", ["worldish/code.pyx"]))
setup(
    packages=["birdcage", "worldish", "worldish.desktop", "worldish.desktop.qml"],
    package_data={"birdcage": ["*.pxd", "*.pyx"], "worldish": ["*.pyx", "*.png"], "worldish.desktop.qml": ["*.qml"]},
    ext_modules=cythonize(extensions, compiler_directives={"language_level": 3}, build_dir="build/cython"),
)
