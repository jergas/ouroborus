



from distutils.core import setup
from distutils.extension import Extension
from Pyrex.Distutils import build_ext
setup(
  name = "topology",
  ext_modules=[
    Extension("topology", ["topology.pyx"])
    ],
  cmdclass = {'build_ext': build_ext}
)
