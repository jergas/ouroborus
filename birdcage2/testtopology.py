### This is a suite of unit test cases for the module topology

import unittest as u
import topology as t
import exceptions_birdcage as E
import operator

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

    category = "Topology"
    topology = getattr(t, category)


    def testTopologyCanBeCreated(self):
        """Topology must instantiate with the sample values"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)


    def testTopologyHasSizeAsGiven(self):
        """Topology.size must be the list given at instantiation"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertEqual(size,topology.size)


    def testTopologyHasBackgroundAsGiven(self):
        """Topology.background must be the integer given at instantiation"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertEqual(background,topology.background)


    def testTopologyHasCorrectDimension(self):
        """Topology.dimension must be the length of size"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertEqual(len(size),topology.dimension)


    def testTopologyHasEnoughCells(self):
        """Topology.cells must be the number of cells in the grid"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            number = reduce(operator.mul, size, 1)
            self.assertEqual(number,topology.cells)


class TopologyMethods(u.TestCase):

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

    category = "Topology"
    topology = getattr(t, category)


    def testTopologyGetGivesBackground(self):
        """Topology.get is not implemented in the base class"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertRaises(NotImplementedError, topology.get, 5)


    def testTopologySetWorksRight(self):
        """Topology.set is not implemented in the base class"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertRaises(NotImplementedError, topology.set, (5,), 0)


    def testTopologyCloneYieldsCopy(self):
        """Topology.clone yields an equivalent topology"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            clone = topology.clone()
            self.assertEqual(topology.background, clone.background)
            self.assertEqual(topology.size, clone.size)
            self.assertEqual(topology.dimension, clone.dimension)
            self.assertEqual(topology.cells, clone.cells)
            self.assertEqual(clone.name, "Abstract Topology")


    def testTopologyNormalizeGivesValidAddress(self):
        """Topology.normalize raises an InvalidAddressError in the base class"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertRaises(E.InvalidAddressError, topology.normalize, (5,))


    def testTopologyIsNormalizedReturnsTrue(self):
        """Topology.isNormalized raises an InvalidAddressError in the base class"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertRaises(E.InvalidAddressError, topology.isNormalized, (5,))


    def testTopologyIsNormalizedReturnsFalse(self):
        """Topology.isNormalized raises an InvalidAddressError in the base class"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertRaises(E.InvalidAddressError, topology.isNormalized, (5,))


    def testTopologyResetWorksThroughoutGrid(self):
        """Topology.reset is not implemented in the base class"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertRaises(NotImplementedError, topology.reset, (5,))



class GridTopologySampleValues(TopologySampleValues):

    sampleValues = ( ((10,10), 0),
                     ((10,25), 7),
                     ((50,30), 2),                                    
                     ((80,80), 1) )

    category = "GridTopology"
    topology = getattr(t, category)


    def testTopologyCanBeCreated(self):
        """GridTopology must instantiate with the sample values"""

        TopologySampleValues.testTopologyCanBeCreated(self)


    def testTopologyHasSizeAsGiven(self):
        """GridTopology.size must be the list given at instantiation"""

        TopologySampleValues.testTopologyHasSizeAsGiven(self)


    def testTopologyHasBackgroundAsGiven(self):
        """GridTopology.background must be the integer given at instantiation"""

        TopologySampleValues.testTopologyHasBackgroundAsGiven(self)


    def testTopologyHasCorrectDimension(self):
        """GridTopology.dimension must be 2"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertEqual(2,topology.dimension)


    def testTopologyHasEnoughCells(self):
        """GridTopology.cells must be the number of cells in the grid"""

        TopologySampleValues.testTopologyHasEnoughCells(self)


    def testTopologyHasCorrectBorder(self):
        """GridTopology.border must be zero"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertEqual(0, topology.border)


    def testTopologyHasCorrectWidth(self):
        """GridTopology.width must be first entry in size"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertEqual(size[0], topology.width)


    def testTopologyHasCorrectHeight(self):
        """GridTopology.width must be second entry in size"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertEqual(size[1], topology.height)


class GridTopologyMethods(TopologyMethods):

    sampleValues = ( ((10,10), 0),
                     ((10,25), 7),
                     ((50,30), 2),                                    
                     ((80,80), 1) )

    category = "GridTopology"
    topology = getattr(t, category)


    def testTopologyGetGivesBackground(self):
        """GridTopology.get works for sample values"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertEqual(topology.get((size[0]-1,size[1]-1)),background)


    def testTopologyGetGivesBorder(self):
        """GridTopology.get gives border value for out-of-range values"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertEqual(topology.get((size[0],size[1])),topology.border)
            self.assertEqual(topology.get((0,size[1])),topology.border)
            self.assertEqual(topology.get((size[0],0)),topology.border)
            self.assertEqual(topology.get((0,-1)),topology.border)
            self.assertEqual(topology.get((-1,0)),topology.border)
            self.assertEqual(topology.get((-1,-1)),topology.border)


    def testTopologyGetFailsWithInvalidAddress(self):
        """GridTopology.get returns appropriate error when given an invalid address"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertRaises(E.InvalidAddressError,topology.get,(5,))
            self.assertRaises(E.InvalidAddressError,topology.get,(5,5,5))


    def testTopologySetFailsWithInvalidAddress(self):
        """GridTopology.set returns appropriate error when given an invalid address"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertRaises(E.InvalidAddressError,topology.set,(5,),0)
            self.assertRaises(E.InvalidAddressError,topology.set,(5,5,5),0)
            self.assertRaises(E.InvalidAddressError,topology.set,(size[0],size[1]),0)
            self.assertRaises(E.InvalidAddressError,topology.set,(0,size[1]),0)
            self.assertRaises(E.InvalidAddressError,topology.set,(size[0],0),0)
            self.assertRaises(E.InvalidAddressError,topology.set,(0,-1),0)
            self.assertRaises(E.InvalidAddressError,topology.set,(-1,0),0)
            self.assertRaises(E.InvalidAddressError,topology.set,(-1,-1),0)


    def testTopologySetWorksRight(self):
        """GridTopology.set changes grid values"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            topology.set(((size[0]-1,size[1]-1)),-7)
            self.assertEqual(topology.get((size[0]-1,size[1]-1)),-7)


    def testTopologyCloneYieldsCopy(self):
        """GridTopology.clone yields an equivalent topology"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            clone = topology.clone()
            self.assertEqual(topology.background, clone.background)
            self.assertEqual(topology.size, clone.size)
            self.assertEqual(topology.dimension, clone.dimension)
            self.assertEqual(topology.cells, clone.cells)
            self.assertEqual(clone.name, "Grid Topology")


    def testTopologyNormalizeGivesValidAddress(self):
        """GridTopology.normalize returns same address if valid"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            for x in range(size[0]):
                for y in range(size[1]):
                    self.assertEqual(topology.normalize((x,y)),(x,y))


    def testTopologyIsNormalizedReturnsTrue(self):
        """GridTopology.isNormalized returns true if address in grid"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            for x in range(size[0]):
                for y in range(size[1]):
                    self.assertTrue(topology.isNormalized((x,y)))


    def testTopologyIsNormalizedReturnsFalse(self):
        """GridTopology.isNormalized raises Invalid Address for off-grid address"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertRaises(E.InvalidAddressError,topology.isNormalized,(size[0],size[1]))
            self.assertRaises(E.InvalidAddressError,topology.isNormalized,(size[0]-1,size[1]))
            self.assertRaises(E.InvalidAddressError,topology.isNormalized,(size[0],size[1]-1))
            self.assertRaises(E.InvalidAddressError,topology.isNormalized,(-1,-1))
            self.assertRaises(E.InvalidAddressError,topology.isNormalized,(0,-1))
            self.assertRaises(E.InvalidAddressError,topology.isNormalized,(-1,0))


    def testTopologyResetWorksThroughoutGrid(self):
        """GridTopology.reset puts cells back to background state"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            topology.set((0,0),-7)
            topology.reset((0,0))
            self.assertEqual(topology.background, topology.get((0,0)))


    def testTopologyCenterYieldsValidAddress(self):
        """GridTopology.center yields a normalized address"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            center = topology.center()
            self.assertTrue(topology.isNormalized(center))


    def testTopologyRandomYieldsValidAddress(self):
        """GridTopology.random yields a normalized address"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            random = topology.random()
            self.assertTrue(topology.isNormalized(random))


class ToroidTopologySampleValues(GridTopologySampleValues):

    sampleValues = ( ((10,10), 0),
                     ((10,25), 7),
                     ((50,30), 2),                                    
                     ((80,80), 1) )

    category = "ToroidTopology"
    topology = getattr(t, category)


    def testTopologyCanBeCreated(self):
        """ToroidTopology must instantiate with the sample values"""

        GridTopologySampleValues.testTopologyCanBeCreated(self)


    def testTopologyHasSizeAsGiven(self):
        """ToroidTopology.size must be the list given at instantiation"""

        GridTopologySampleValues.testTopologyHasSizeAsGiven(self)


    def testTopologyHasBackgroundAsGiven(self):
        """ToroidTopology.background must be the integer given at instantiation"""

        GridTopologySampleValues.testTopologyHasBackgroundAsGiven(self)


    def testTopologyHasCorrectDimension(self):
        """ToroidTopology.dimension must be 2"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertEqual(2,topology.dimension)


    def testTopologyHasEnoughCells(self):
        """ToroidTopology.cells must be the number of cells in the grid"""

        TopologySampleValues.testTopologyHasEnoughCells(self)


    def testTopologyHasCorrectBorder(self):
        """ToroidTopology.border does not have a border"""

        pass


    def testTopologyHasCorrectWidth(self):
        """ToroidTopology.width must be first entry in size"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertEqual(size[0], topology.width)


    def testTopologyHasCorrectHeight(self):
        """ToroidTopology.width must be second entry in size"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertEqual(size[1], topology.height)


class ToroidTopologyMethods(GridTopologyMethods):

    sampleValues = ( ((10,10), 0),
                     ((10,25), 7),
                     ((50,30), 2),                                    
                     ((80,80), 1) )

    category = "ToroidTopology"
    topology = getattr(t, category)


    def testTopologyGetGivesBackground(self):
        """ToroidTopology.get works for sample values"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertEqual(topology.get((size[0]-1,size[1]-1)),background)
            self.assertEqual(topology.get((-1*size[0]-1,-5*size[1]-1)),background)
            self.assertEqual(topology.get((0*size[0]-1,2*size[1]-1)),background)
            self.assertEqual(topology.get((17*size[0]-1,29*size[1]-1)),background)


    def testTopologyGetGivesBorder(self):
        """ToroidTopology.get does not have a border"""

        pass

    def testTopologyGetFailsWithInvalidAddress(self):
        """ToroidTopology.get returns appropriate error when given an invalid address"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertRaises(E.InvalidAddressError,topology.get,(5,))
            self.assertRaises(E.InvalidAddressError,topology.get,(5,5,5))


    def testTopologySetFailsWithInvalidAddress(self):
        """ToroidTopology.set returns appropriate error when given an invalid address"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertRaises(E.InvalidAddressError,topology.set,(5,),0)
            self.assertRaises(E.InvalidAddressError,topology.set,(5,5,5),0)


    def testTopologySetWorksRight(self):
        """ToroidTopology.set changes grid values"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            topology.set(((size[0]-1,size[1]-1)),-7)
            self.assertEqual(topology.get((size[0]-1,size[1]-1)),-7)
            topology.set(((-1*size[0]-1,11*size[1]-1)),-7)
            self.assertEqual(topology.get((size[0]-1,size[1]-1)),-7)
            topology.set(((17*size[0]-1,19*size[1]-1)),-7)
            self.assertEqual(topology.get((size[0]-1,size[1]-1)),-7)


    def testTopologyCloneYieldsCopy(self):
        """ToroidTopology.clone yields an equivalent topology"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            clone = topology.clone()
            self.assertEqual(topology.background, clone.background)
            self.assertEqual(topology.size, clone.size)
            self.assertEqual(topology.dimension, clone.dimension)
            self.assertEqual(topology.cells, clone.cells)
            self.assertEqual(clone.name, "Toroid Topology")


    def testTopologyNormalizeGivesValidAddress(self):
        """ToroidTopology.normalize returns same address if valid"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            for x in range(size[0]):
                for y in range(size[1]):
                    self.assertEqual(topology.normalize((x,y)),(x,y))


    def testTopologyNormalizeGivesCorrectResult(self):
        """ToroidTopology.normalize returns normalized address"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            (x,y) = size
            for i in range(-11,11):
                for j in range(-3,5):
                    self.assertEqual(topology.normalize((i*x-1,j*y-1)),(x-1,y-1))



    def testTopologyNormalizeGivesNormalizedAddress(self):
        """ToroidTopology.normalize returns normalized address"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertTrue(topology.isNormalized(topology.normalize((size[0]-1,size[1]-1))))
            self.assertTrue(topology.isNormalized(topology.normalize((-1*size[0]-1,3*size[1]-1))))
            self.assertTrue(topology.isNormalized(topology.normalize((17*size[0]-1,5*size[1]-1))))


    def testTopologyIsNormalizedReturnsTrue(self):
        """ToroidTopology.isNormalized returns true if address is normalized"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            for x in range(size[0]):
                for y in range(size[1]):
                    self.assertTrue(topology.isNormalized((x,y)))


    def testTopologyIsNormalizedReturnsFalse(self):
        """ToroidTopology.isNormalized returns false if address is not normalized"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            self.assertFalse(topology.isNormalized((size[0],size[1])))
            self.assertFalse(topology.isNormalized((size[0]-1,size[1])))
            self.assertFalse(topology.isNormalized((size[0],size[1]-1)))
            self.assertFalse(topology.isNormalized((-1,-1)))
            self.assertFalse(topology.isNormalized((0,-1)))
            self.assertFalse(topology.isNormalized((-1,0)))


    def testTopologyResetWorksThroughoutGrid(self):
        """ToroidTopology.reset puts cells back to background state"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            topology.set((0,0),-7)
            topology.reset((0,0))
            self.assertEqual(topology.background, topology.get((0,0)))


    def testTopologyCenterYieldsValidAddress(self):
        """ToroidTopology.center yields a normalized address"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            center = topology.center()
            self.assertTrue(topology.isNormalized(center))


    def testTopologyRandomYieldsValidAddress(self):
        """ToroidTopology.random yields a normalized address"""

        for size, background in self.sampleValues:
            topology = self.topology(size, background)
            random = topology.random()
            self.assertTrue(topology.isNormalized(random))


if __name__ == "__main__":
    u.main()
