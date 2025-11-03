
import aiohttp
import asyncio

async def fetch_page(page_url):
    async with aiohttp.ClientSession() as session:
        async with session.get(page_url) as response:
            return await response.text()


async def main():
    urls = [
        'http://example.com/page1',
        'http://example.com/page2',
        'http://example.com/page3',
    ]
    tasks = [
        fetch_page(url) for url in urls
    ]
    pages = await asyncio.gather(*tasks)
    for page in pages:
        print(page)

asyncio.run(main())
