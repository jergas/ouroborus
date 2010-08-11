from distutils.core import setup
from distutils.extension import Extension
from Pyrex.Distutils import build_ext

setup(name='Birdcage',
#      packages = ['birdcage'],
#      package_dir = {'birdcage':'.'},
      cmdclass = {'build_ext': build_ext},
      ext_modules = [Extension('agent', ['agent.pyx']),
                     Extension('automaton', ['automaton.pyx']),
                     Extension('exceptions_birdcage', ['exceptions_birdcage.pyx']),
                     Extension('genome', ['genome.pyx']),
                     Extension('neighborhood', ['neighborhood.pyx']),
                     Extension('rule', ['rule.pyx']),
                     Extension('topology', ['topology.pyx']),
                     ],)