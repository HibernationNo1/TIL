### config관련
import os, os.path as osp
# config file을 지정하지 않을 시 default config file path
DEFAULT_CONFIG_PATH = 'configs/app.py'

BASE_CONFIG_NAME = 'API'

### log관련
# log파일을 저장할 dir 
BASE_LOG_DIR = 'logs'
container_name = os.environ.get('CONTAINER_NAME', None)     
if container_name is not None:
    BASE_LOG_DIR = osp.join(BASE_LOG_DIR, container_name)   
    os.makedirs(BASE_LOG_DIR, exist_ok = True) 
else:
    os.makedirs(BASE_LOG_DIR, exist_ok=True)

# server관련 log의 이름. log파일 또한 관련되어 이름이 지어진다.
BASE_SERVER_LOGGER_NAME = 'Server'

# Debug관련 logger의 이름. log파일 또한 관련되어 이름이 지어진다.
BASE_DEBUG_LOGGER_NAME = 'Debug'