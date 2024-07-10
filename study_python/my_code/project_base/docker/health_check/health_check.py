# -*- coding: utf-8 -*-
import requests
import schedule
from functools import partial
import time

import asyncio
import telegram

# live server local에서 health check 하고 telegram으로 알람을 보내기 위한 code
# 2024.03.21 부 업무시간 외 IDC - local server간의 접속 차단에 의한 조치

import logging

# 로깅 설정: 로그 레벨, 로그 메시지 형식 및 날짜 형식 설정
logging.basicConfig(filename = 'health_check.log',
                    level=logging.INFO,
                    format='%(asctime)s - %(levelname)s - %(message)s',
                    datefmt='%Y-%m-%d %H:%M:%S',
                    )


CONFIM_COUNT = 3   # 한 번 제대로 응답이 안왔을 시 재확인 횟수
telegram_token = "6818574021:AAEjZxXVUXLCST-u84Un5dYVY-XC3unznj8"
chat_id = "-1002116316211"     # group chat id 사용.   
# teno의 개인 chat id: "6317154266"

server_dict = dict(
    container_name_1 = dict(
        host = "container_name_1",
        port = 20001,
        route = "/v1/health/check",
        timeout = 10,
        start_time = 1,             
        time_minute_in_hour = 10    
    ),
    container_name_2 = dict(
        host = "container_name_2",
        port = 20002,
        route = "/v1/health/check",
        timeout = 10,
        start_time = 1,             
        time_minute_in_hour = 10    
    ),
    container_name_3 = dict(
        host = "container_name_3",
        port = 20003,
        route = "/v1/health/check",
        timeout = 10,
        start_time = 1,             
        time_minute_in_hour = 10    
    ),
)


def confim_health(url, headers, timeout):
    # CONFIM_COUNT 만큼 요청을 다시 보낸다. 
    # 응답이 한 번이라도 제대로 온 경우 return True 
    health_flag = False
    for i in range(CONFIM_COUNT):
        logging.info(f"      Retry request to '{url}'.  count: {i+1} ")
        try:
            response = requests.get(url, headers=headers, timeout=timeout)
            if response.status_code == 200:
                health_flag = True
                break
        except : pass
        time.sleep(5)
    return health_flag


async def send_message(bot_token, chat_id, text):
    bot = telegram.Bot(token=bot_token)
    await bot.send_message(chat_id=chat_id, text=text)
    
    
def send_warning_notification(project_name, message = " "):
    text = f"project_name: '{project_name}', \n message: {message}"
    logging.info(text)
    
    try:
        asyncio.run(send_message(telegram_token, chat_id, text))
    except Exception as e:
        logging.info(f" Telegram Error: {e}\n")
    time.sleep(3) 



def scheduling_func(url, timeout, project_name):
    headers = {'Content-Type': 'application/json'}
    
    try:
        logging.info(f"Try request to '{url}'")
        
        # request로 health checking
        response = requests.get(url, headers=headers, timeout=timeout)
        
        if response.status_code !=200:      
            # responce가 비정상 상태 code를 반환한 경우
            # 추가로 health check를 N번 확인 
            health_flag = confim_health(url, headers, timeout)
            if not health_flag:
                send_warning_notification(project_name)
    except Exception as e:
        # request가 제대로 동작하지 않은 경우
        # 추가로 health check를 N번 확인 
        health_flag = confim_health(url, headers, timeout)
        if not health_flag:
            send_warning_notification(project_name, message = e)


        
def make_scheduling_time_table(start_time, time_minute_in_hour):                               
    scheduling_count_in_hour = 60 // (time_minute_in_hour)     # 매 시간마다 몇 번 실행되는지 횟수 계산  
    scheduling_time_table = [start_time + time_minute_in_hour*i 
                            for i in range(scheduling_count_in_hour+1)
                            if start_time + time_minute_in_hour*i < 60]   # 매 시간마다 몇 분에 스케쥴링을 실행할지 결정한 table

    return scheduling_time_table


def get_scheduling(server_dict):
    for project_name, info_dict in server_dict.items():
        # scheduling할 시간 table 구성
        scheduling_time_table = make_scheduling_time_table(info_dict['start_time'], info_dict['time_minute_in_hour'])
        logging.info(f" time table: {scheduling_time_table}")
        
        # 주소 결정
        url = f"http://{info_dict['host']}:{info_dict['port']}{info_dict['route']}"
        
        for web_minute in scheduling_time_table:
            # schedule 모듈에 추가 
            schedule.every().hour.at(f":{web_minute:02d}").do(partial(scheduling_func, 
                                                                        url = url,
                                                                        timeout = info_dict['timeout']),
                                                                        project_name = project_name)
    return schedule



        
if __name__=="__main__":
    # scheduling을 위한 instance 생성
    logging.info("Start health check.")
    schedule_ins = get_scheduling(server_dict)
    while True:
        schedule_ins.run_pending()
        time.sleep(1)