import sys
import os

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

import pytest
from unittest.mock import patch, mock_open
import json
from Service.ReservationSystem import ReservationSystem
from Models.Reservation import Reservation


@pytest.fixture
def reservation_system():
    return ReservationSystem()


test_data = {
    "Reservations": [
        {
            "id": 1,
            "room_number": 101,
            "name": "John",
            "surname": "Doe",
            "check_in": "2023-07-20T12:00:00",
            "check_out": "2023-07-27T12:00:00"
        }
    ]
}


@patch("builtins.open", new_callable=mock_open,
       read_data=json.dumps(test_data))
def test_load_reservations(mock_file, reservation_system):
    reservation_system.load_reservations()
    assert len(reservation_system.reservation_list) == 1
    assert reservation_system.reservation_list[0].name == "John"


@patch("builtins.open", new_callable=mock_open)
def test_write_reservations(mock_file, reservation_system):
    reservation = Reservation(room_number=102, name="John", surname="Doe")
    reservation_system.reservation_list.append(reservation)
    reservation_system.write_reservations()
    mock_file.assert_called_with("Static/Reservations.json", "w")
    handle = mock_file()
    written_data = json.loads(handle.write.call_args[0][0])
    assert written_data['Reservations'][1]['name'] == "John"
