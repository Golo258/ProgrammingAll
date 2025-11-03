import re
from datetime import datetime, timedelta

expenses = {
    "2023-01": {
        "01": {
            "food": [22.11, 43, 11.72, 2.2, 36.29, 2.5, 19],
            "fuel": [210.22]
        },
        "09": {
            "food": [11.9],
            "fuel": [190.22]
        }
    },
    "2023-03": {
        "07": {
            "food": [20, 11.9, 30.20, 11.9]
        },
        "04": {
            "food": [10.20, 11.50, 2.5],
            "fuel": []
        }
    },
    "2023-04": {}
}


def count_list_median(numbers):
    sorted_numbers = sorted(numbers)
    numbers_len = len(sorted_numbers)
    if numbers_len % 2 == 1:
        median = sorted_numbers[numbers_len // 2]
    else:
        first_middle = sorted_numbers[(numbers_len // 2) - 1]
        second_middle = sorted_numbers[(numbers_len // 2)]
        median = (first_middle + second_middle) / 2
    return median


def get_first_sunday(year, month):
    first_day = datetime(year, month, 1)
    days_to_sunday = (6 - first_day.weekday()) % 7
    return first_day + timedelta(days=days_to_sunday)


def get_dates_until_first_sunday(year, month):
    first_sunday = get_first_sunday(year, month)
    month_start_date = datetime(year, month, 1)
    dates = []
    current_date = month_start_date
    while current_date <= first_sunday:
        dates.append(f"{current_date.day:02}")
        current_date += timedelta(days=1)
    return dates


def get_accumulated_monthly_expenses(possible_dates, expenses_dates):
    accumulated_monthly_expenses = []
    for date in possible_dates:
        if date in expenses_dates:
            daily_costs = expenses_dates[date]
            accumulated_daily_costs = [item_price for costs in daily_costs.values() for item_price in costs]
            accumulated_monthly_expenses.extend(accumulated_daily_costs)
    return accumulated_monthly_expenses


def find_all_expenses(expanses):
    given_months_expenses = []
    for key, value in expanses.items():
        if re.match(r"^\d{4}-\d{2}$", key):
            year, month = key.split("-")
            dates = get_dates_until_first_sunday(int(year), int(month))
            accumulated_monthly_expenses = get_accumulated_monthly_expenses(dates, value)
            given_months_expenses.extend(accumulated_monthly_expenses)

    return given_months_expenses


def solution(expenses):
    all_expenses = find_all_expenses(expenses)
    return count_list_median(all_expenses)


if __name__ == '__main__':
    print(solution(expenses))
