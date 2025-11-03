from uuid import uuid4


class Room:
    def __init__(self, room_number: int, description: str, bedrooms: int,
                 bathrooms: int, air_conditioning: bool):
        self._room_number = room_number
        self._description = description
        self._bedrooms = bedrooms
        self._bathrooms = bathrooms
        self._air_conditioning = air_conditioning
        self._is_taken = False

    @property
    def room_number(self):
        return self._room_number

    @room_number.setter
    def room_number(self, value):
        self._room_number = value

    @property
    def description(self):
        return self._description

    @description.setter
    def description(self, value):
        self._description = value

    @property
    def bedrooms(self):
        return self._bedrooms

    @bedrooms.setter
    def bedrooms(self, value):
        self._bedrooms = value

    @property
    def bathrooms(self):
        return self._bathrooms

    @bathrooms.setter
    def bathrooms(self, value):
        self._bathrooms = value

    @property
    def air_conditioning(self):
        return self._air_conditioning

    @air_conditioning.setter
    def air_conditioning(self, value):
        self._air_conditioning = value

    @property
    def is_taken(self):
        return self._is_taken

    @is_taken.setter
    def is_taken(self, value):
        self._is_taken = value

    def __str__(self):
        return (f"Room {self.room_number}, {self.description}"
                f"Have {self.bedrooms} bedrooms and {self.bathrooms} bathrooms and "
                f"{"also have air conditioning" if self.air_conditioning else "dont have air conditioning"}.")
