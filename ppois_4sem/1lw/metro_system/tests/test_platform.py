import unittest
import sys
import os
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/models')))
from station_platform import Platform

class TestPlatform(unittest.TestCase):
    def setUp(self):
        self.platform = Platform()

    def test_initial_state(self):
        self.assertTrue(self.platform.is_closed)
        self.assertTrue(self.platform.is_empty)
        self.assertIsNone(self.platform.current_train)

    def test_open_platform(self):
        self.platform.open_platform()
        self.assertFalse(self.platform.is_closed)

if __name__ == '__main__':
    unittest.main()