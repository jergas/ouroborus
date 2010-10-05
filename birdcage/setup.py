import specific
from distutils.core import setup
from distutils.extension import Extension
if specific.compiler == "cython":
	from Cython.Distutils import build_ext
else:
	from Pyrex.Distutils import build_ext

setup(name='Birdcage',
      version='0.5.5',
      description='Cellular Automata Engine',
      author='Sat Tara Singh Khalsa',
      author_email='sattara@guruarjan.com',
      url='http://ouroborus.info/',
#      packages = ['birdcage'],
      package_dir = {'birdcage':'.'},
      py_modules = ['birdcage.specific'],
      cmdclass = {'build_ext': build_ext},
# We don't want for the moment all the extensions in the birdcage directory :(
# unless we write a __init__ maybe later. Also the CAPITALS where used 'cause when I installed
# all the packages in the same dir begin with Capital or were all CAPITAL names.
      ext_package = 'birdcage', 
      ext_modules = [Extension('agent', ['agent.pyx']),
                     Extension('automaton', ['automaton.pyx']),
                     Extension('exceptions_birdcage', ['exceptions_birdcage.pyx']),
                     Extension('genome', ['genome.pyx']),
                     Extension('neighborhood', ['neighborhood.pyx']),
                     Extension('rule', ['rule.pyx']),
                     Extension('topology', ['topology.pyx']),
                     ],)
