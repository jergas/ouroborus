



from distutils.core import setup
from distutils.extension import Extension
from Pyrex.Distutils import build_ext
setup(
  name = "code",
  ext_modules=[
    Extension("code", ["code.pyx"])
    ],
  cmdclass = {'build_ext': build_ext}
)
