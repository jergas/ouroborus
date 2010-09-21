from distutils.core import setup
from distutils.extension import Extension
from Pyrex.Distutils import build_ext

setup(name='Birdcage',
      version='0.5.5',
      description='Cellular Automata Engine',
      author='Sat Tara Singh Khalsa',
      author_email='sattara@guruarjan.com',
      url='http://ouroborus.info/',
#      packages = ['birdcage'],
#      package_dir = {'':'Birdcage'},
       cmdclass = {'build_ext': build_ext},
#      ext_package = 'Birdcage',
       ext_modules = [Extension('agent', ['agent.pyx']),
                     Extension('automaton', ['automaton.pyx']),
                     Extension('exceptions_birdcage', ['exceptions_birdcage.pyx']),
                     Extension('genome', ['genome.pyx']),
                     Extension('neighborhood', ['neighborhood.pyx']),
                     Extension('rule', ['rule.pyx']),
                     Extension('topology', ['topology.pyx']),
                     ],)
