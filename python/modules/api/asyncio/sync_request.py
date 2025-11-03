import requests
import random
import json
import string
from collections import Counter
from http import HTTPStatus
import time

auth_token = ""
base_url = "https://gorest.co.in"

'''GET CALl'''


def get_users_id():
    url = f"{base_url}/public/v2/users"
    headers = {"Authorization": auth_token}
    response = requests.get(url, headers=headers)
    assert response.status_code == HTTPStatus.OK
    return [ body['id'] for body in response.json()]

def get_uer_by_id(user_id):
    url = f"{base_url}/public/v2/users/{user_id}"
    headers = {"Authorization": auth_token}
    response = requests.get(url, headers=headers)
    assert response.status_code == HTTPStatus.OK
    return response.json()

def main():
    print("Getting user_ids")
    users_ids = get_users_id()
    users_list = list()
    for user_id in users_ids:
        print(f"Adding user id: {user_id}")
        users_list.append(get_uer_by_id(user_id))

    print(f"{users_list = }")
    return len(users_ids)

if __name__ == '__main__':
    start_time = time.time()
    count_of_api_calls = main()
    end_time = time.time()
    total_time = end_time - start_time
    print(f"It took {total_time} seconds to make {count_of_api_calls} API calls")

'''It took 7.858609676361084 seconds to make 10 API calls'''
