#!/bin/python3

import math
import os
import random
import re
import sys


def conditional_statments(numb: int):
    if numb % 2 == 1:
        print("Weird")
    elif numb % 2 == 0:
        if 2 <= numb <= 5:
            print("Not Weird")
        elif 6 <= numb <= 20:
            print("Weird")
        elif numb > 20:
            print("Not weird")


def show_range():
    numb = int(input("Enter a number: "))
    numbers = [numb for numb in range(1, numb + 1)]
    print(*numbers, sep="")


import re


def check_number_correctness(number):
    pattern = r'^[789]\d{9}'
    if re.match(pattern, number):
        return "YES"
    else:
        return "NO"


def find_out_input_correctness():
    # 10 digits, 7 8 or 9 at beggining
    number_of_taken_numbers = int(input(""))
    numbers = []
    for occurrence in range(0, number_of_taken_numbers):
        checked_number = input()
        check_number_correctness(checked_number)


def geh_runner_up(scores: list):
    sorted_scores = list(sorted(set(scores)))
    return sorted_scores[-2]


def find_runner_up():
    n = int(input())
    arr = list(map(int, input().split()))
    runner_up = geh_runner_up(arr)
    print(runner_up)


def find_students_by_grade(students):
    grades = []
    for student in students:
        name, score = student
        grades.append(score)

    second_lowest = list(sorted(set(grades)))[1]
    searched_students = []
    for student in students:
        if student[1] == second_lowest:
            searched_students.append(student[0])

    if len(searched_students) > 1:
        return sorted(searched_students)
    else:
        return searched_students


def find_lowest_student_grades():
    students = []
    for _ in range(int(input())):
        name = input()
        score = float(input())
        students.append([name, score])

    students_name = find_students_by_grade(students)
    for student in students_name:
        print(student)


from functools import reduce


def get_scores_average_by_name(student_name, students_scores: dict):
    for name, scores in students_scores.items():
        if student_name == name:
            sum_of_scores = reduce(lambda first_score, second_score: first_score + second_score, scores)
            return "{:.2f}".format(sum_of_scores / len(scores))


def count_average_of_students_scores():
    n = int(input())
    student_marks = {}
    for _ in range(n):
        name, *line = input().split()
        scores = list(map(float, line))
        student_marks[name] = scores
    query_name = input()
    average = get_scores_average_by_name(query_name, student_marks)
    print(average)


def perform_actions(number_of_actions: int):
    base_list = []
    for _ in range(0, number_of_actions):
        action, *object = input().split()
        object_elements = list(map(int, object))
        match action:
            case "insert":
                base_list.insert(object_elements[0], object_elements[1])
            case "append":
                base_list.append(object_elements[0])
            case "remove":
                base_list.remove(object_elements[0])
            case "pop":
                base_list.pop()
            case "reverse":
                base_list.reverse()
            case "sort":
                base_list.sort()
            case "print":
                print(base_list)


def get_input_if_its_None(line):
    if line is None:
        line = input()
    return line


def swap_case(word):
    word = get_input_if_its_None(word)
    changed_word = ""
    for letter in word:
        if letter.islower():
            changed_word += letter.upper()
        elif letter.isupper:
            changed_word += letter.lower()

    return changed_word


def split_and_join(line):
    line = get_input_if_its_None(line)
    splited_line = line.split(" ")
    joined_splited_line = "-".join(splited_line)
    return joined_splited_line


def mutate_string(string, position, character):
    converted = list(string)
    converted[position] = character
    return "".join(converted)


def count_substring():
    string = "ABCDCDC"  # input().strip()
    sub_string = "CDC"  # input().strip()

    number_of_occurance = 0
    for index in range(0, len(string)):
        if string[index] in sub_string:
            if string[index:len(sub_string) + index] == sub_string:
                number_of_occurance += 1

    return number_of_occurance


def string_validatiors(text=None):
    if text is None:
        text = "qA2"
    # isalnum -  (az AZ 0-9) | isalpha - (az AZ) |    isDigits (0-9)
    # any takes generator, if any of the valiuse inside are true it returns true
    print(any(char.isalnum() for char in text))
    print(any(char.isalpha() for char in text))
    print(any(char.isdigit() for char in text))
    print(any(char.islower() for char in text))
    print(any(char.isupper() for char in text))


def text_alignment():
    print("World".ljust(20, "_"))
    print("World".center(20, "_"))
    print("World".rjust(20, "_"))

    def print_doormat():
        n = int(input().split()[0])
        for i in range(n // 2):
            print(((i * 2 + 1) * '.|.').center(3 * n, '-'))

        print('WELCOME'.center(3 * n, '-'))

        for i in reversed(range(n // 2)):
            print(((i * 2 + 1) * '.|.').center(3 * n, '-'))

    print_doormat()


def text_wrap():
    import textwrap
    string = "Mojaitwoja mama lubi placki ale nie za duzo"
    print(textwrap.wrap(string, 8))  # creating list of elements based on given width
    print(textwrap.fill(string, 8))  # create a text with \n striped by given width


def string_formatting():
    # your code goes here
    number = int(input())
    width = len(bin(number)) - 2
    for index in range(1, number + 1):
        decimal = str(index).rjust(width)
        octal = oct(index)[2:].rjust(width)
        hexadecimal = hex(index)[2:].upper().rjust(width)
        binary = bin(index)[2:].rjust(width)

        print(f"{decimal} {octal} {hexadecimal} {binary}")


import string


def alphabet_rangoli():
    chars_count = 5  # int(input())
    alfa_chars = list(string.ascii_lowercase)
    first_letter = alfa_chars[chars_count]
    pattern = generate_pattern(chars_count, 2)

    # for index in range(1, chars_count + 1):
    #     sequence = list(alfa_chars[chars_count])
    #     print((count_of_alphabet_letters[index - index]))


def generate_pattern(size, row):
    alphabet_chars = list(string.ascii_lowercase)
    pattern = []

    for i in range(1, row + 1):
        pattern.append(alphabet_chars[size - i])
    return pattern


def capitalize_name():
    full_name = "chris alan"
    seperated_name = full_name.split(" ")
    lowercase_names = filter(lambda name: name[0].islower(), seperated_name)
    capitalized_names = map(lambda name: name.capitalize(), lowercase_names)
    return " ".join(list(capitalized_names))


def minion_game():
    given_word = "BANANA"
    vowels = {'a', 'e', 'i', 'o', 'u'}  # kevin
    consonants = set('bcdfghjklmnpqrstvwxyz')  # stuart
    stuart_possible_start, kevin_possible_start = [], []
    for letter in given_word:
        if letter.lower() in vowels and letter not in kevin_possible_start:
            kevin_possible_start.append(letter)
        elif letter.lower() in consonants and letter not in stuart_possible_start:
            stuart_possible_start.append(letter)

    posible_stuart_words = generate_possible_words(stuart_possible_start, given_word)
    posible_kevin_words = generate_possible_words(kevin_possible_start, given_word)
    stuart_score =  generate_scores(posible_stuart_words, given_word)
    kevin_scores =  generate_scores(posible_kevin_words, given_word)

    if stuart_score > kevin_scores:
        print(f"Stuart {stuart_score}")
    else:
        print(f"Kevin {kevin_scores}")


def generate_possible_words(first_letters, given_word):
    possible_words = []
    for character in first_letters:
        index_of_start_letter = given_word.find(character)
        for end in range(index_of_start_letter + 1, len(given_word) + 1):
            possible_words.append(
                given_word[index_of_start_letter: end]
            )

    return possible_words

def generate_scores(possible_words, given_word :str):
    occurance = {}
    for word in possible_words:
        count_of_word_occurence = given_word.count(word)
        occurance[word] = count_of_word_occurence

    sum_of_scores = sum(occurance.values())
    return sum_of_scores
def merge_the_tools():
    # your code goes here
    import textwrap
    word = "AABCAAADA"
    factor = 3
    subsuequences = textwrap.wrap(word, factor)
    sequences_without_repetitions = [ remove_duplicates(sequence) for sequence in subsuequences ]
    for sequence in sequences_without_repetitions:
        print(sequence)

def remove_duplicates(string):
    unique_sequence = ""
    for letter in string:
        if letter not in unique_sequence:
            unique_sequence += letter
    return unique_sequence


def run_all():
    n = int(input().strip())
    conditional_statments(n)
    show_range()
    find_out_input_correctness()
    find_runner_up()
    find_lowest_student_grades()
    count_average_of_students_scores()
    string_validatiors()
    text_alignment()
    text_wrap()
    alphabet_rangoli()
    names = capitalize_name()
    print(names)


if __name__ == '__main__':
    minion_game()
