import os, os.path as osp
from fastapi import FastAPI, APIRouter, HTTPException
from pydantic import BaseModel
import uvicorn
from prometheus_fastapi_instrumentator import Instrumentator

app = FastAPI()
Instrumentator().instrument(app).expose(app)            # prometheus 적용

from handlers.config import Config
cfg = Config.fromfile(f'configs/main.py')


# application의 모든 중간과정을 제어하기 위해 middleware 추가
from api_utils.middleware import APPMiddleWare
app.add_middleware(APPMiddleWare, 
                   allowed_ips=cfg.server.middleware.allowed_ips, 
                   content_type=cfg.server.middleware.content_type, 
                   logger = Logger(logger_name = cfg.logger.middleware.name, 
                                   file_name = cfg.logger.middleware.file, 
                                   middleware = True)
                   )

from handlers.logger import Logger
logger = Logger(logger_name = cfg.logger.service.name, file_name = cfg.logger.service.file, print_log=True)


from handlers.prometheus import PROMETHEUS_REGISTRY
Prom_request = PROMETHEUS_REGISTRY['function']
count = PROMETHEUS_REGISTRY['count'] 






# health check
@app.get('/api/check/status')
def check_status():
    result = {"status": "OK",
                "version": f'v{cfg.server.version}'}
    logger.info(f"{result}")
    return result


class Item(BaseModel):
    path_dict: dict
    
    
# name에 가게 이름
@app.post('/api/predict')
def name_predict(item: Item):
    logger.info(f"---- Start OCR ----")
    count.inc() # count 1증가
    
    file_path = item.file_path
    file_name = osp.basename(file_path)

    result_dict = dict()
    try:
        pass
    except Exception as e:
        message = f"Cannot access to '{file_path}'. Error: {e}"
        logger.error(message)
        raise HTTPException(status_code = 430, detail=message)
         

    result_dict[file_name] = dict()
    
    
    logger.info(f"---- Complete API ----")
    logger.info(result_dict)
    return result_dict



if __name__ == "__main__":
    uvicorn.run(app, host=cfg.server.host, port=cfg.server.port)