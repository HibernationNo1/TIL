import requests
import schedule
from functools import partial
import time

import asyncio

import json


from utils.utils import make_scheduling_time_table, send_message


from utils.logger import Logger
logger = Logger(logger_name= 'health_check', file_name=f'health_check.log', print_log = True)     

with open('utils/token_table.json', "r") as f:
    token_table = json.load(f)

telegram_token = token_table['health_check']['telegram_token']
chat_id = token_table['health_check']['group_chat_id']

confim_count = 3        # 한 번 제대로 응답이 안왔을 시 재확인 횟수

# 스케줄링으로 health check 할 서비스 목록
with open('utils/server_table.json', "r") as f:
    server_table = json.load(f)

server_dict = server_table['health_check']
    
def send_warning_notification(project_name, message = " "):
    text = f"project_name: '{project_name}', \n message: {message}"
    logger.info(text)
    
    try:
        asyncio.run(send_message(telegram_token, chat_id, text))
    except Exception as e:
        logger.info(f" Telegram Error: {e}\n")
    time.sleep(3)
        

def confim_health(url, headers, timeout, confim_count = 3):
    health_flag = False
    for i in range(confim_count):
        logger.info(f"      Retry request to '{url}'.  count: {i+1} ")
        try:
            response = requests.get(url, headers=headers, timeout=timeout)
            if response.status_code == 200:
                health_flag = True
                break
        except : pass
        time.sleep(5)
    return health_flag
        
        
def scheduling_func(url, timeout, project_name):
    headers = {'Content-Type': 'application/json'}
    
    try:
        logger.info(f"Try request to '{url}'")
        
        # request로 health checking
        response = requests.get(url, headers=headers, timeout=timeout)
        
        if response.status_code !=200:      
            # responce가 비정상 상태 code를 반환한 경우
            # 추가로 health check를 N번 확인 
            health_flag = confim_health(url, headers, timeout, confim_count)
            if not health_flag:
                send_warning_notification(project_name)
    except Exception as e:
        # request가 제대로 동작하지 않은 경우
        # 추가로 health check를 N번 확인 
        health_flag = confim_health(url, headers, timeout, confim_count)
        if not health_flag:
            send_warning_notification(project_name, message = e)

def get_scheduling(server_dict):
    for project_name, info_dict in server_dict.items():
        # scheduling할 시간 설정
        scheduling_time_table = make_scheduling_time_table(info_dict['start_time'], info_dict['time_minute_in_hour'])   
        
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
    schedule_ins = get_scheduling(server_dict)
    while True:
        schedule_ins.run_pending()
        time.sleep(1)

        