import os, os.path as osp
import logging
from logging.handlers import RotatingFileHandler

from configs.default import BASE_LOG_DIR

# 여러 logger를 담을 registry.
LOGGER_REGISTRY = dict()

# Default Logger Config
DEFAULT_LOG_NAME = 'log'
DEFAULT_FILENAME = 'logs/api.log'
FORMATTER = logging.Formatter("[%(asctime)s]|[%(filename)s line: %(lineno)d] %(levelname)s :%(message)s") # log의 format결정. 모든 handler에 적용할 format이다.
DEFAULT_LEVEL = logging.INFO

class Logger:
    """
    - 목적에 따라 logger를 따로 저장해야 하는 경우, 여러개의 logger생성
        logger_for_api_1 = Logger(logger_name = 'api_1', file_name = 'api_1.log')
        logger_for_api_2 = Logger(logger_name = 'api_2', file_name = 'api_2.log')

    - 다른 python script에서 이전에 기록하던 log를 가져와야 하는 경우
        logger_for_api_2 = Logger.get_logger(logger_name = 'api_2')

    - 어떤 logger가 있는지 확인하는 경우
        Logger.check_logger_list()
    
    """
    def __new__(cls, 
                logger_name: str = None, 
                   file_name: str = None, 
                   file_format = 'log',
                   print_log = False,
                   level = None):
        
        if logger_name is None:
            logger_name = DEFAULT_LOG_NAME
        return cls.add_logger(logger_name, file_name, file_format, print_log, level)

    @staticmethod
    def set_logger(log_name=None, file_path=None, level=None, print_log = False):
        if log_name is None:
            log_name = DEFAULT_LOG_NAME
        if level is None:
            level = DEFAULT_LEVEL

        # root logger
        logger = logging.getLogger(log_name)


        if level >= logging.WARN or print_log:
            streamHandler = logging.StreamHandler()
            streamHandler.setFormatter(FORMATTER)
            logger.addHandler(streamHandler)

        if file_path is None:
            file_path = DEFAULT_FILENAME


        # # FileHandler 설정
        # fileHandler = logging.FileHandler(filename=file_path)
        # fileHandler.setFormatter(FORMATTER)
        # logger.addHandler(fileHandler)

        # RotatingFileHandler 설정
        # 최대 크기 1GB, backup 개수 5개
        rotatingHandler = RotatingFileHandler(file_path, maxBytes=1024**3, backupCount=5)
        rotatingHandler.setFormatter(FORMATTER)
        logger.addHandler(rotatingHandler)

        logger.setLevel(level=level)

        return dict(logger = logger,
                    level = level,
                    file_path = file_path,
                    name = log_name)
            
    @staticmethod
    def add_logger(logger_name: str, 
                   file_name: str = None, 
                   file_format = 'log',
                   print_log = False,
                   level = None):
        
        # logger추가.
        if logger_name in LOGGER_REGISTRY.keys():
            print(f"{logger_name} already exists in logger registry")
            return LOGGER_REGISTRY[logger_name]['logger']

        if file_name is not None:
            if os.path.splitext(file_name)[-1] == '':
                file_path = osp.join(BASE_LOG_DIR, f'{file_name}.{file_format}')
            else:
                file_path = osp.join(BASE_LOG_DIR, file_name)
        else:
            file_path = osp.join(BASE_LOG_DIR, f'{logger_name}.{file_format}')

        os.makedirs(osp.dirname(file_path), exist_ok=True)
  
        LOGGER_REGISTRY[logger_name] = Logger.set_logger(log_name=logger_name, 
                                                                file_path= file_path,
                                                                print_log = print_log,
                                                                level = level)
        return LOGGER_REGISTRY[logger_name]['logger']

    @staticmethod
    def show_logger_list():
        if len(LOGGER_REGISTRY.keys()) == 0:
            print(f"LOGGER_REGISTRY is empty!")
            return None
        for logger_name in LOGGER_REGISTRY.keys():
            print(logger_name)

    @staticmethod
    def get_logger(logger_name):
        if len(LOGGER_REGISTRY.keys()) == 0:
            raise OSError("LOGGER_REGISTRY is empty!")
        
        # logger_registry에 저장된 logger를 return
        if logger_name in LOGGER_REGISTRY.keys():
            return LOGGER_REGISTRY[logger_name]['logger']
        else:
            raise KeyError(f"The logger `{logger_name}` dose no exist!")

    @staticmethod
    def get_logger_info(logger_name):
        # logger_registry에 저장된 logger dict를 return
        if logger_name in LOGGER_REGISTRY.keys():
            return LOGGER_REGISTRY[logger_name]
        else:
            raise KeyError(f"The logger `{logger_name}` dose no exist!")

