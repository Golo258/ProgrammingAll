
import asyncio

async def calculate_square(number):
    print(f"Calculating square of {number}")
    await asyncio.sleep(1)
    return number * number

async def main():
    numbers = [1, 2, 3, 4, 5]
    tasks = list()
    for numb in numbers:
        tasks.append(asyncio.create_task(calculate_square(numb)))

    squares = await asyncio.gather(*tasks)
    print("Results:", squares)

asyncio.run(main())