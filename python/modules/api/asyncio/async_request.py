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
start_time = time.time()
users_list = list()


async def get_users():
    async with aiohttp.ClientSession() as session:
        for user_id in users_ids:
            print(f"Adding user id: {user_id}")
            response = await session.get(f"{base_url}/public/v2/users/{user_id}",
                                   headers={"Authorization": auth_token},
                                   ssl=False)
            users_list.append(await response.json())


# loop = asyncio.get_event_loop()
# loop.run_until_complete(get_users())
# loop.close()
asyncio.run(get_users())

end_time = time.time()
total_time = end_time - start_time
print(f"It took {total_time} seconds to make {len(users_ids)} API calls")

'''It took 2.8964478969573975 seconds to make 10 API calls'''