### This is a suite of unit test cases for the module topology

import unittest as u
import topology as t

class TopologySampleValues(u.TestCase):

    sampleValues = ( ((1,), 0),
                     ((10,), 0),
                     ((10,1), 1),
                     ((10,10), 0),
                     ((10,25), 7),
                     ((10,10,1), 2),
                     ((10,10,10), 1),
                     ((10,15,25), -1),
                     ((10,10,10,10), 0),
                     ((10,10,10,10,10,10,10), 3) )


    def testTopologyCanBeCreated(self):
        """Topology must instantiate with the sample values"""

        for size, background in self.sampleValues:
            topology = t.Topology(size, background)


    def testTopologyHasSizeAsGiven(self):
        """Topology.size must be the list given at instantiation"""

        for size, background in self.sampleValues:
            topology = t.Topology(size, background)
            self.assertEqual(size,topology.size)


    def testTopologyHasBackgroundAsGiven(self):
        """Topology.background must be the integer given at instantiation"""

        for size, background in self.sampleValues:
            topology = t.Topology(size, background)
            self.assertEqual(background,topology.background)


if __name__ == "__main__":
    u.main()
