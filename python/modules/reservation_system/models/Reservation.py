from uuid import uuid4

from datetime import timedelta, datetime


class Reservation:
    id_counter = 0

    def __init__(self, room_number: int, name: str, surname: str):
        Reservation.id_counter += 1
        self._id: int = Reservation.id_counter
        self._room_number = room_number
        self._name = name
        self._surname = surname
        self._check_in = datetime.now()
        self._check_out = self.check_in + timedelta(weeks=1)

    @property
    def id(self):
        return self._id

    @id.setter
    def id(self, value):
        self._id = value

    @property
    def room_number(self):
        return self._room_number

    @room_number.setter
    def room_number(self, value):
        self._room_number = value

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, value):
        self._name = value

    @property
    def surname(self):
        return self._surname

    @surname.setter
    def surname(self, value):
        self._surname = value

    @property
    def check_in(self):
        return self._check_in

    @check_in.setter
    def check_in(self, value):
        self._check_in = value

    @property
    def check_out(self):
        return self._check_out

    @check_out.setter
    def check_out(self, value):
        self._check_out = value

    def __repr__(self):
        return (f"Reservation(id={self._id}, room_number={self._room_number}, "
                f"name='{self._name}', surname='{self._surname}', "
                f"check_in={self._check_in}, check_out={self._check_out})")

    def __str__(self):
        return (f"Reservation number {self.id}, for Client {self.name}, {self.surname} "
                f"\nOn room {self.room_number}\t Date In: {self.check_in} | Out: {self.check_out}")

    def to_dict(self):
        return {
            'id': self._id,
            'room_number': self._room_number,
            'name': self._name,
            'surname': self._surname,
            'check_in': self._check_in.isoformat(),  # Używa formatu ISO 8601
            'check_out': self._check_out.isoformat()  # Używa formatu ISO 8601
        }

    @classmethod
    def from_dict(cls, data):
        instance = cls(
            room_number=data['room_number'],
            name=data['name'],
            surname=data['surname']
        )
        instance._id = data['id']
        instance._check_in = datetime.fromisoformat(data['check_in'])
        instance._check_out = datetime.fromisoformat(data['check_out'])
        return instance