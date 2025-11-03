
from services.ReservationSystem import ReservationSystem

if __name__ == '__main__':
    system = ReservationSystem()
    is_running = True
    # system.print_possible_options()
    print(list(option for option in system.options.keys()), sep="\n")
    while is_running:

        is_running = system.run_system()
