



from distutils.core import setup
from distutils.extension import Extension
from Pyrex.Distutils import build_ext
setup(
  name = "agent",
  ext_modules=[
    Extension("agent", ["agent.pyx"])
    ],
  cmdclass = {'build_ext': build_ext}
)
