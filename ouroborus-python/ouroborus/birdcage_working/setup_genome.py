



from distutils.core import setup
from distutils.extension import Extension
from Pyrex.Distutils import build_ext
setup(
  name = "genome",
  ext_modules=[
    Extension("genome", ["genome.pyx"])
    ],
  cmdclass = {'build_ext': build_ext}
)
