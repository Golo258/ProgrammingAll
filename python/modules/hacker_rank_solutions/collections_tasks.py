from itertools import (product,
                       permutations)
from collections import Counter, defaultdict


def example_products():
    # ilcozyn kartezjanski ( wszystkie pary, do wszystkich par)
    repeated_product = list(product([1, 2, 3], repeat=2))
    two_lists = list(product([1, 2, 3], [3, 4]))
    three_lists = list(product([1, 2, 3], [3, 4, 5], [6, 7, 8]))
    print(repeated_product)
    print(two_lists)
    print(three_lists)


# ---------------------------------
def counter_example():
    example_list = [1, 1, 2, 3, 4, 5, 3, 2, 3, 4, 2, 1, 2, 3]
    # keys = occuration of singular elements
    # value = total amount of occrance of this element in the table
    list_counter = Counter(example_list)
    print(list_counter.items())
    print(list_counter.values())


# -------------------------

def permutations_example():
    # permutacja - kazde mozliowe uporzadkowanie elementów zbioru
    set_permutation = list(permutations([1, 2, 3]))
    permutation_with_factor = list(
        permutations([1, 2, 3, 4], 2)
    )
    print(set_permutation)
    print(permutation_with_factor)


# -------------------------
def default_dict_example():
    # przydatny gdy chcemy uniknac błedów w zwiazku z próbą dostania sie do nieistniejace klucz

    default = defaultdict(list)
    default['python'].append("awesome")
    default["else"].append("not relevant")
    print(default['mayonesa'])  # stworzy ten klucz, ale  z pusta tablica
    for item in default.items():
        print(item)


# --------------------
def product_task():
    first_list = list(map(int, input().split()))
    second_list = list(map(int, input().split()))
    computed_list = list(product(first_list, second_list))
    print(*computed_list, sep=" ")


def count_earned_money(available_sizes, customer_orders):
    size_count = Counter(available_sizes)
    earned_money = 0
    for size, price in customer_orders:
        if size_count[size] > 0:
            earned_money += price
            size_count[size] -= 1

    return earned_money


def counter_task_solution():
    number_of_shoes = int(input())
    available_shoe_sizes = list(map(int, input().split()))
    customers_amount = int(input())
    customer_order = []  # shoes_size | shoe price
    for customer in range(0, customers_amount):
        customer_order.append(
            tuple(map(int, input().split()))
        )
    print(
        count_earned_money(available_shoe_sizes, customer_order)
    )


def permutation_task_solution():
    string, factor = list("HACK"), 2
    permutated_strings = list(permutations(string, factor))
    collected_strings = []
    for string in permutated_strings:
        collected_strings.append(
            "".join(string)
        )
    return collected_strings


def count_set_average():
    number_of_plant = 10
    plant_heights = [161, 182, 161, 154, 176, 170, 167, 171, 170, 174]
    plan_set = set(plant_heights)
    average = round(sum(plan_set) / len(plan_set), 3)
    print(average)
    return average


def get_group_indices(group):
    indices_group = defaultdict(list)
    for element in group:
        indices_group[element].append(group.index(element))
        group.

    return indices_group


def print_indices_of_groups():
    import collections
    n, m = map(int, input().split())
    d = collections.defaultdict(list)

    for i in range(n):
        d[input()].append(i + 1)

    for j in range(m):
        B = input()
        key = d.keys()
        if (B in key):
            print(*d[B])
        else:
            print(-1)


def run_all():
    strings = permutation_task_solution()
    for word in sorted(strings):
        print(word)


if __name__ == '__main__':
    print_indices_of_groups()
