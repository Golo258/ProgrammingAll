import json
from typing import List
from Models.Reservation import Reservation
from Models.Room import Room


def get_options(self):
    posible_options = {
        "[Add] Create new reservation": self.add_reservation,
        "[Show] Present all reservations": self.show_reservations,
        "[View] Show reservation by id": self.show_reservation_by_id,
        "[Modify] Change reservation by id": self.change_reservation,
        "[Remove] Delete reservation by id": self.remove_reservation,
        "[Load] Upload file reservation to list": self.load_reservations,
        "[Write] Add reservations to file": self.write_reservations
        # "[Options] Show all possible options ": (self.print_possible_options(), ()),
    }
    return posible_options


class ReservationSystem:
    def __init__(self):
        self.options = get_options(self)
        self.reservation_list: List[Reservation] = []
        self.json_file_path = "Static//Reservations.json"
        self.available_rooms_numbers = self.get_available_rooms_numbers()
        print(self.options.keys())

    def run_system(self):
        try:
            chosen_option = input("Enter option from given").lower()
            for key, value in self.options.items():
                if chosen_option in key.lower():
                    value()
                    return True
                elif chosen_option in "Quit program":
                    return False

        except Exception as input_exc:
            print(f"There occurred an {input_exc} during taking option")

    def add_reservation(self):
        global chosen_room_number
        room_number_chosen = False
        try:
            print(f"You can pick from available rooms: {self.available_rooms_numbers}")
            while not room_number_chosen:
                chosen_room_number = int(input("Choose room number from available rooms number: "))
                room_number_chosen = True if chosen_room_number in self.available_rooms_numbers else False

            new_reservation = Reservation(
                room_number=chosen_room_number,
                name=input("Type your name: "),
                surname=input("Type your surname: "),
            )
            if new_reservation not in self.reservation_list:
                self.reservation_list.append(new_reservation)
                self.available_rooms_numbers.remove(chosen_room_number)
                print(f"Updated avaialble rooms numbers {self.available_rooms_numbers}")
            else:
                print("This room is already taken. Please choose another one")
        except Exception as exp:
            print(f"There occurred an error {exp}")

    def show_reservations(self):
        for reservation in self.reservation_list:
            print(reservation)

    def show_reservation_by_id(self):
        reservation_by_id = self.check_reservation_ownership()
        if isinstance(reservation_by_id, Reservation):
            print(str(reservation_by_id))
        else:
            print(reservation_by_id)

    def change_reservation(self):
        reservation_by_id = self.check_reservation_ownership()
        try:
            if isinstance(reservation_by_id, Reservation):
                user_choices = input("What would you like to change, use [,] to type many options")
                attributes_list = [word.strip() for word in user_choices.split(',')]
                for attribute in attributes_list:
                    if hasattr(reservation_by_id, attribute):
                        setattr(reservation_by_id, attribute, input(f"Type new value of {attribute}: "))
            return reservation_by_id
        except Exception as change_exc:
            print(f"During reservation change error {change_exc} occurs")

    def remove_reservation(self):
        reservation_by_id = self.check_reservation_ownership()
        if isinstance(reservation_by_id, Reservation):
            self.reservation_list.remove(reservation_by_id)

    def load_reservations(self):
        try:
            with open("Static//Reservations.json", "r") as read_file:
                json_data = json.load(read_file)

            for reservation in json_data['Reservations']:
                json_reservation = Reservation.from_dict(reservation)
                self.reservation_list.append(json_reservation)

        except Exception as exc:
            print(f"There occurs an error {exc} during writing reservation to json file")


    def write_reservations(self):
        try:
            with open("Static//Reservations.json", "r") as read_file:
                json_data = json.load(read_file)

            for reservation in self.reservation_list:
                json_data['Reservations'].append(reservation.to_dict())
            with open("Static//Reservations.json", "w") as write_file:
                json.dump(json_data, write_file)
        except Exception as exc:
            print(f"There occurs an error {exc} during writing reservation to json file")

    def check_reservation_ownership(self):
        self.show_reservations()

        reservation_id = int(input("What is reservation id  : "))
        reserved_room_number = int(input("Which is your room number: "))
        searched_reservation = [reservation for reservation in self.reservation_list if
                                reservation.room_number == reserved_room_number
                                and reservation.id == reservation_id]
        if searched_reservation is None:
            return "Reservation does not exist"
        return searched_reservation[0] if len(searched_reservation) == 1 else searched_reservation

    def get_available_rooms_numbers(self):
        try:
            with open("Static//AvailableRooms.json", "r") as json_file:
                json_data = json.load(json_file)
            available_rooms = [
                Room(
                    room_number=room['room_number'],
                    description=room['description'],
                    bedrooms=room['bedrooms'],
                    bathrooms=room['bathrooms'],
                    air_conditioning=room['air_conditioning'],
                )
                for room in json_data['AvailableRooms']
            ]
            available_rooms_numbers = [
                room.room_number for room in available_rooms if not room.is_taken
            ]
            return available_rooms_numbers
        except Exception as exc:
            print(f"There occurs an error: {exc} while reading json file")

    def call_chosen_options_function(self, key: str):
        func_ref, default_args, = self.options[key]
        return func_ref()
