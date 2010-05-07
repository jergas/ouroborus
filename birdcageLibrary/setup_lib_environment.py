



from distutils.core import setup
from distutils.extension import Extension
from Pyrex.Distutils import build_ext
setup(
  name = "lib_environment",
  ext_modules=[
    Extension("lib_environment", ["lib_environment.pyx"])
    ],
  cmdclass = {'build_ext': build_ext}
)
