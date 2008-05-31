



from distutils.core import setup
from distutils.extension import Extension
from Pyrex.Distutils import build_ext
setup(
  name = "automaton",
  ext_modules=[
    Extension("automaton", ["automaton.pyx"])
    ],
  cmdclass = {'build_ext': build_ext}
)
