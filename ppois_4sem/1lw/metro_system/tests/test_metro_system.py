import unittest
import sys
import os
import json
from unittest.mock import patch, mock_open

# Добавляем путь к папке с моделями
sys.path.append(os.path.abspath(os.path.join(os.path.dirname(__file__), '../src/models')))

from system_metro import MetroSystem
from station import Station
from passenger import Passenger

class TestMetroSystem(unittest.TestCase):
    def setUp(self):
        """Инициализация MetroSystem перед каждым тестом."""
        self.metro = MetroSystem()

    def test_initial_state(self):
        """Проверка начального состояния MetroSystem."""
        self.assertEqual(self.metro.stations, [])
        self.assertEqual(self.metro.branches, [])
        self.assertIsNone(self.metro.passenger)

    def test_add_station(self):
        """Проверка добавления станции."""
        station = self.metro.add_station("Test Station")
        self.assertEqual(len(self.metro.stations), 1)
        self.assertEqual(self.metro.stations[0].name, "Test Station")
        self.assertEqual(station.name, "Test Station")

    def test_find_station_existing(self):
        """Проверка поиска существующей станции."""
        station = Station("Found Station")
        self.metro.stations.append(station)
        found = self.metro.find_station("Found Station")
        self.assertEqual(found, station)

    def test_find_station_not_found(self):
        """Проверка поиска несуществующей станции."""
        with patch('builtins.print') as mocked_print:
            result = self.metro.find_station("Nonexistent Station")
            self.assertIsNone(result)
            mocked_print.assert_called_with("Станция Nonexistent Station не найдена")

    def test_create_passenger(self):
        """Проверка создания пассажира."""
        self.metro.create_passenger("Alice", 10)
        self.assertIsNotNone(self.metro.passenger)
        self.assertEqual(self.metro.passenger.name, "Alice")
        self.assertEqual(self.metro.passenger.money, 10)

    def test_save_state_no_passenger(self):
        """Проверка сохранения состояния без пассажира."""
        station = self.metro.add_station("Station A")
        expected_data = {
            "stations": [{"name": "Station A"}],
            "passenger": None
        }
        with patch('builtins.open', mock_open()) as mocked_file:
            with patch('json.dump') as mocked_json:
                self.metro.save_state("test_state.json")
                mocked_file.assert_called_once_with("test_state.json", "w", encoding="utf-8")
                mocked_json.assert_called_once_with(expected_data, mocked_file(), ensure_ascii=False, indent=4)

    def test_save_state_with_passenger(self):
        """Проверка сохранения состояния с пассажиром."""
        self.metro.create_passenger("Bob", 5)
        station = self.metro.add_station("Station B")
        self.metro.passenger.station = station
        self.metro.passenger.progress = 2
        expected_data = {
            "stations": [{"name": "Station B"}],
            "passenger": {
                "name": "Bob",
                "money": 5,
                "progress": 2,
                "station": "Station B"
            }
        }
        with patch('builtins.open', mock_open()) as mocked_file:
            with patch('json.dump') as mocked_json:
                self.metro.save_state("test_state.json")
                mocked_file.assert_called_once_with("test_state.json", "w", encoding="utf-8")
                mocked_json.assert_called_once_with(expected_data, mocked_file(), ensure_ascii=False, indent=4)

    def test_load_state_success(self):
        """Проверка успешной загрузки состояния."""
        mock_data = {
            "stations": [{"name": "Loaded Station"}],
            "passenger": {
                "name": "Charlie",
                "money": 15,
                "progress": 3,
                "station": "Loaded Station"
            }
        }
        with patch('builtins.open', mock_open(read_data=json.dumps(mock_data))):
            with patch('builtins.print') as mocked_print:
                self.metro.load_state("test_state.json")
                self.assertEqual(len(self.metro.stations), 1)
                self.assertEqual(self.metro.stations[0].name, "Loaded Station")
                self.assertEqual(self.metro.passenger.name, "Charlie")
                self.assertEqual(self.metro.passenger.money, 15)
                self.assertEqual(self.metro.passenger.progress, 3)
                self.assertEqual(self.metro.passenger.station.name, "Loaded Station")
                mocked_print.assert_called_with("Состояние загружено.")

    def test_load_state_no_passenger(self):
        """Проверка загрузки состояния без пассажира."""
        mock_data = {
            "stations": [{"name": "Empty Station"}],
            "passenger": None
        }
        with patch('builtins.open', mock_open(read_data=json.dumps(mock_data))):
            with patch('builtins.print') as mocked_print:
                self.metro.load_state("test_state.json")
                self.assertEqual(len(self.metro.stations), 1)
                self.assertEqual(self.metro.stations[0].name, "Empty Station")
                self.assertIsNone(self.metro.passenger)
                mocked_print.assert_called_with("Состояние загружено.")

    def test_load_state_file_not_found(self):
        """Проверка загрузки состояния при отсутствии файла."""
        with patch('builtins.open', side_effect=FileNotFoundError):
            with patch('builtins.print') as mocked_print:
                self.metro.load_state("test_state.json")
                self.assertEqual(self.metro.stations, [])
                self.assertIsNone(self.metro.passenger)
                mocked_print.assert_called_with("Файл состояния не найден, начинаем с нуля.")

if __name__ == '__main__':
    unittest.main()