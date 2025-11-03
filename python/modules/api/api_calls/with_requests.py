# ! C:\Users\Czesław\Desktop\Repositories\PythonProjects\Revise\API\env\Scripts\python.exe

import requests

BASE_URL = "https://jsonplaceholder.typicode.com/posts/"


def get_item_by_id(post_id=None):
    if post_id is None:
        url = BASE_URL
    else:
        url = f"{BASE_URL}{post_id}"
    try:
        response = requests.get(url)
        if response.status_code == 200:
            json_response = response.json()
            return json_response
        else:
            print(f"Wrong response status {response.status_code}")

    except requests.exceptions.RequestException as reqException:
        print(f"There occures an exception with request{reqException}")


def post_new_item(item_body: dict):
    url = BASE_URL
    try:
        response = requests.post(url, data=item_body)
        if response.status_code == 201:
            return response.reason
        else:
            raise Exception("The response body is wrong")
    except requests.exceptions.RequestException as reqException:
        print(f"There occures an exception with request{reqException}")


if __name__ == "__main__":
    get_item_by_id(1)  # by id
    get_item_by_id()  # all
    post_body = {'userId': 123, 'id': 123, 'title': 'SUper fajny post', 'body': 'No i tak to jest z tym wszysktim'}
    post_reason = post_new_item(post_body)
    if post_reason == 'Created':
        get_item_by_id(123)
    else:
        print("Item has not been created")
