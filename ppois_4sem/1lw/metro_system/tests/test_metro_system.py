import unittest
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/models')))

from system_metro import MetroSystem
from station import Station

class TestMetroSystem(unittest.TestCase):
    def setUp(self):
        self.metro = MetroSystem()

    def test_initial_state(self):
        self.assertEqual(self.metro.stations, [])
        self.assertEqual(self.metro.branches, [])

    def test_find_station(self):
        station = Station("Found Station")
        self.metro.stations.append(station)
        found = self.metro.find_station("Found Station")
        self.assertEqual(found, station)

if __name__ == '__main__':
    unittest.main()