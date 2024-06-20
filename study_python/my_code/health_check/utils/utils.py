import telegram

def make_scheduling_time_table(start_time, time_minute_in_hour):                               
    scheduling_count_in_hour = 60 // (time_minute_in_hour)     # 매 시간마다 몇 번 실행되는지 횟수 계산  
    scheduling_time_table = [start_time + time_minute_in_hour*i 
                             for i in range(scheduling_count_in_hour+1)
                             if start_time + time_minute_in_hour*i < 60]   # 매 시간마다 몇 분에 스케쥴링을 실행할지 결정한 table

    return scheduling_time_table




async def send_message(bot_token, chat_id, text):
    bot = telegram.Bot(token=bot_token)
    await bot.send_message(chat_id=chat_id, text=text)
    