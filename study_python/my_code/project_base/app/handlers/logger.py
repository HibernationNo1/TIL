import os, os.path as osp
from datetime import datetime
import logging
from logging.handlers import TimedRotatingFileHandler

from configs.default import BASE_LOG_DIR

# 여러 logger를 담을 registry.
LOGGER_REGISTRY = dict()

class Logger(object):
    """
    - 목적에 따라 logger를 따로 저장해야 하는 경우, 여러개의 logger생성
        logger_controller = Logger()
        logger_controller.add_logger(logger_name='api_1', file_name='api_1.log', print_log = True)     

    - 다른 python script에서 이전에 기록하던 log를 가져와야 하는 경우
        logger_controller = Logger()
        logger_controller.get_logger(logger_name='api_1')     
    
    """
    def __init__(self, default_level = logging.INFO):
        os.makedirs(BASE_LOG_DIR, exist_ok=True)
        self.default_log_name = 'log'
        self.default_filename = f'{BASE_LOG_DIR}/api.log'
        self.default_level = default_level

        # log의 format결정. 모든 handler에 적용할 format이다.
        self.formatter = logging.Formatter("[%(asctime)s]|[%(filename)s line: %(lineno)d] %(levelname)s :%(message)s")

    def set_logger(self, log_name=None, file_path=None, level=None, print_log = False):
        if log_name is None:
            log_name = self.default_log_name

        # root logger
        logger = logging.getLogger(log_name)

        if level is None:
            level = self.default_level

        if level >= logging.WARN or print_log:
            streamHandler = logging.StreamHandler()
            streamHandler.setFormatter(self.formatter)
            logger.addHandler(streamHandler)

        if file_path is None:
            file_path = self.default_filename

        # TimedRotatingFileHandler 설정
        # 자정에 로그 파일 회전, backup 개수 50개
        rotatingHandler = TimedRotatingFileHandler(file_path, when='midnight', backupCount=50)
        rotatingHandler.setFormatter(self.formatter)
        logger.addHandler(rotatingHandler)

        logger.setLevel(level=level)

        return dict(logger = logger,
                    level = level,
                    file_path = file_path,
                    name = log_name)
                    

    def add_logger(self, 
                   logger_name: str, 
                   file_name: str = None, 
                   file_format = 'log',
                   print_log = False,
                   level = None):
        
        # logger추가.
        if logger_name in LOGGER_REGISTRY.keys():
            print(f"{logger_name} already exists in logger registry")
            return LOGGER_REGISTRY[logger_name]

        if file_name is not None:
            if os.path.splitext(file_name)[-1] == '':
                file_path = osp.join(BASE_LOG_DIR, f'{file_name}.{file_format}')
            else:
                file_path = osp.join(BASE_LOG_DIR, file_name)
        else:
            file_path = osp.join(BASE_LOG_DIR, f'{logger_name}.{file_format}')
        LOGGER_REGISTRY[logger_name] = self.set_logger(log_name=logger_name, 
                                                                file_path= file_path,
                                                                print_log = print_log,
                                                                level = level)
        return LOGGER_REGISTRY[logger_name]['logger']

    def show_logger_list(self):
        if len(LOGGER_REGISTRY.keys()) == 0:
            print(f"LOGGER_REGISTRY is empty!")
            return None
        for logger_name in LOGGER_REGISTRY.keys():
            print(logger_name)


    def get_logger(self, logger_name):
        if len(LOGGER_REGISTRY.keys()) == 0:
            raise OSError("LOGGER_REGISTRY is empty!")
        
        # logger_registry에 저장된 logger를 return
        if logger_name in LOGGER_REGISTRY.keys():
            return LOGGER_REGISTRY[logger_name]['logger']
        else:
            raise KeyError(f"The logger `{logger_name}` dose no exist!")

            
    def get_logger_info(self, logger_name):
        # logger_registry에 저장된 logger dict를 return
        if logger_name in LOGGER_REGISTRY.keys():
            return LOGGER_REGISTRY[logger_name]
        else:
            raise KeyError(f"The logger `{logger_name}` dose no exist!")