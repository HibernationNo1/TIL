# ### verson 20.4  비동기식
# import telegram
# import asyncio
# import time

# telegram_token = 'token값'
# chat_id = 'chat ID'
# async def send_message(bot_token, chat_id, text):
#     bot = telegram.Bot(token=bot_token)
#     await bot.send_message(chat_id=chat_id, text=text)

# try:
#     asyncio.run(send_message(telegram_token, chat_id, "test"))
# except Exception as e:
#     print(f" Telegram Error: {e}")
# time.sleep(3)


### version 13.4.1      동기식
import telegram


telegram_token = ''
chat_id = ''


def send_message(bot_token, chat_id, text):
    bot = telegram.Bot(token=bot_token)
    bot.sendMessage(chat_id=chat_id, text=text, timeout=100)

send_message(telegram_token, chat_id, 'test')