import asyncio
import aiohttp
from http import HTTPStatus
import time
import requests

auth_token = ""
base_url = "https://gorest.co.in"

'''GET CALl'''


def get_users_id():
    url = f"{base_url}/public/v2/users"
    headers = {"Authorization": auth_token}
    response = requests.get(url, headers=headers)
    assert response.status_code == HTTPStatus.OK
    return [body['id'] for body in response.json()]


print("Getting user_ids")
users_ids = get_users_id()
print("Starting time counting: ")


def get_task(session):
    tasks = []
    for id in users_ids:
        tasks.append(asyncio.create_task(session.get(f"{base_url}/public/v2/users/{id}",
                                 headers={"Authorization": auth_token},
                                 ssl=False)))
    return tasks

start_time = time.time()
users_list = list()

async def get_users():
    async with aiohttp.ClientSession() as session:
        tasks = get_task(session)
        responses = await asyncio.gather(*tasks)
        for response in responses:
            users_list.append(await response.json())



asyncio.run(get_users())

end_time = time.time()
total_time = end_time - start_time
print(f"It took {total_time} seconds to make {len(users_ids)} API calls")

'''It took 0.7960920333862305 seconds to make 10 API calls'''