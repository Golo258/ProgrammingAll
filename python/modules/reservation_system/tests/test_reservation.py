
import sys
import os
sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))


import pytest
from Models.Reservation import Reservation
from datetime import datetime, timedelta
@pytest.fixture
def reservation():
    return Reservation(
        room_number=101, name="John", surname="Snow"
    )


def test_reservation_creation(reservation):
    assert reservation.room_number == 101
    assert reservation.name == "John"
    assert reservation.surname == "Snow"
    assert isinstance(reservation.check_in, datetime)
    assert isinstance(reservation.check_out, datetime)
    assert reservation.check_out == reservation.check_in + timedelta(weeks=1)


def test_object_to_dict(reservation):
    reservation_dict = reservation.to_dict()
    assert reservation_dict['room_number'] == reservation.room_number
    assert reservation_dict['name'] == reservation.name
    assert reservation_dict['surname'] == reservation.surname

def test_dict_to_object(reservation):
    reservation_dict = reservation.to_dict()
    new_reservation = Reservation.from_dict(reservation_dict)
    assert new_reservation.room_number == 101
    assert new_reservation.name == "John"
    assert new_reservation.surname == "Snow"
