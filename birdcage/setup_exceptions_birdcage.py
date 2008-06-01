



from distutils.core import setup
from distutils.extension import Extension
from Pyrex.Distutils import build_ext
setup(
  name = "exceptions_birdcage",
  ext_modules=[
    Extension("exceptions_birdcage", ["exceptions_birdcage.pyx"])
    ],
  cmdclass = {'build_ext': build_ext}
)
