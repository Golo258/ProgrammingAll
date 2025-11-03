import asyncio
import aiofiles


async def read_file(file_name):
    async with aiofiles.open(file_name, mode="r") as file:
        content = await file.read()

    return content

# processing data from file contents
async def process_data(contents):
    # Przetwarzanie danych - w tym przykładzie, sumowanie liczby z pliku
    numbers = [int(line) for line in contents.split('\n') if line.strip()]
    total = sum(numbers)
    return total


async def write_to_file(filename, data):
    async with aiofiles.open(filename, mode="w") as file:
        await file.write(str(data))

async def main():
    filenames = ['Resources/file1.txt', 'Resources/file2.txt', 'Resources/file3.txt']
    results = []
    tasks = [read_file(filename) for filename in filenames]
    content_list = await  asyncio.gather(*tasks)
    for content in content_list:
        result = await process_data(content)
        results.append(result)

    await write_to_file("Resources/output.txt", '\n'.join(map(str, results)))

asyncio.run(main())

