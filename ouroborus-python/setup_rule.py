



from distutils.core import setup
from distutils.extension import Extension
from Pyrex.Distutils import build_ext
setup(
  name = "rule",
  ext_modules=[
    Extension("rule", ["rule.pyx"])
    ],
  cmdclass = {'build_ext': build_ext}
)
