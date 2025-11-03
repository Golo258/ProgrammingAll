import requests
import random
import json
import string
from collections import Counter
from http import HTTPStatus

auth_token = ""

base_url = "https://gorest.co.in"

'''GET CALl'''


def get_request():
    url = f"{base_url}/public/v2/users"
    headers = {"Authorization": auth_token}
    response = requests.get(url, headers=headers)
    assert response.status_code == HTTPStatus.OK
    print(json.dumps(response.json(), indent=3))
    return response.json()


def get_users_infos(json_body_list: list, searched_value):
    searched_values = list()
    for body in json_body_list:
        try:
            searched_values.append(body[searched_value])
        except Exception as exc:
            print(f"{exc} occures")
    return searched_values


def get_posible_values(user_data):
    genders = get_users_infos(user_data, "gender")
    statuses = get_users_infos(user_data, "status")
    return {"gender": genders, "status": statuses}


def get_random_name(length):
    letters = string.ascii_letters
    result = ''.join(random.choice(letters) for i in range(length))
    return result


def get_most_common_posible_values_to_new_user(user_data):
    posible_values = get_posible_values(user_data)
    key_name = list(posible_values.keys())[0]
    values_range = range(len(posible_values[key_name]))
    possible_statuses = [posible_values['status'][index] for index in values_range]
    possible_genders = [posible_values['gender'][index] for index in values_range]
    status_counter = Counter(possible_statuses)
    gender_counter = Counter(possible_genders)
    data = {
        "name": get_random_name(15),
        "email": f"{get_random_name(12)}@automation.com",
        "gender": gender_counter.most_common(1)[0][0],
        "status": status_counter.most_common(1)[0][0]
    }
    return data


'''POST CALl'''


def post_new_user(user_data) -> int:
    url = f"{base_url}/public/v2/users"
    headers = {"Authorization": auth_token}
    new_data = get_most_common_posible_values_to_new_user(user_data)
    post_result = requests.post(url, json=new_data, headers=headers)
    assert post_result.status_code == HTTPStatus.CREATED
    json_data = post_result.json()
    print(json.dumps(json_data, indent=4))
    new_created_user_id = json_data["id"]
    assert json_data['name'] == new_data['name']
    return new_created_user_id


'''PUT CALL'''


def put_changed_user(user_id) -> dict:
    url = f"{base_url}/public/v2/users/{user_id}"
    headers = {"Authorization": auth_token}
    previous_data = requests.get(url, headers=headers)
    changed_data = previous_data.json() if previous_data.status_code == HTTPStatus.OK else dict()
    assert changed_data != dict()
    changed_data['name'] = "Kasztan";
    changed_data['gender'] = "female"
    put_result = requests.put(url, json=changed_data, headers=headers)
    assert put_result.status_code == HTTPStatus.OK
    json_data = put_result.json()
    print(json.dumps(json_data, indent=4))
    return json_data


''' DELETE CALL'''


def delete_request(user_id):
    url = f"{base_url}/public/v2/users/{user_id}"
    headers = {"Authorization": auth_token}
    deleting_result = requests.delete(url, headers=headers)
    assert deleting_result.status_code == HTTPStatus.NO_CONTENT

if __name__ == '__main__':
    get_body = get_request()
    created_id = post_new_user(get_body)
    changed_user = put_changed_user(created_id)
    delete_request(created_id)
