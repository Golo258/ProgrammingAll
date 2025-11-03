import sys
import os

sys.path.insert(0, os.path.abspath(os.path.join(os.path.dirname(__file__), '..')))

import pytest
from Algoritms.example_algoritms import (find_minimum,
                                         read_list_from_file,
                                         write_list_to_file)

from unittest.mock import patch, mock_open


def test_positive_numbers():
    assert find_minimum([5, 3, 8, 1, 7]) == 1


def test_negative_numbers():
    assert find_minimum([-10, -52, 6, 7, -2]) == -52


def test_mixed_numbers():
    assert find_minimum([4, 6, -21, 6, 7, -121.5]) == -121.5


def test_single_element():
    assert find_minimum([1]) == 1


def test_empty_list():
    with pytest.raises(ValueError, match="The list is empty"):
        find_minimum([])


def test_collections_as_elements():
    with pytest.raises(TypeError, match="Elements of type list or dict are not allowed"):
        find_minimum([5, 2, -25, [12, 5, 6]])


def test_unsupported_elements_type():
    with pytest.raises(TypeError) as exception_info:
        find_minimum([5, 2, -25, "Its a word"])
    assert str(exception_info.value) == "Unsupported element type: <class 'str'>"


@patch("builtins.open", new_callable=mock_open)
def test_write_list_to_file(mock_file):
    data = [5, 4, 3, 6, 21]
    write_list_to_file("fake_path.txt", data)
    mock_file.assert_called_with("fake_path.txt", "w")
    handle = mock_file()
    written_data = handle.write.call_args[0][0]
    assert written_data == "5,4,3,6,21"


@patch("builtins.open", new_callable=mock_open, read_data="5,4,6,7,12")
def test_read_list_from_file(mock_file):
    result = read_list_from_file("fake_path.txt")
    mock_file.assert_called_with("fake_path.txt", "r")
    assert result == [5, 4, 6, 7, 12]
