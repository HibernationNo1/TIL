import os, os.path as osp
import json

from flask import Flask, request, jsonify, Response, abort
app = Flask(__name__)


from handlers.logger import Logger
logger = Logger(logger_name = 'logger_name', file_name = f'file_name.log', print_log=True)
    
    
from handlers.config import Config
cfg = Config.fromfile(f'configs/api.py')

from prometheus_flask_exporter import PrometheusMetrics
from handlers.prometheus import PROMETHEUS_REGISTRY
PROMETHEUS_REGISTRY['metrics'] = PrometheusMetrics(app)
Prom_request = PROMETHEUS_REGISTRY['request']
count = PROMETHEUS_REGISTRY['count'] 


# health check
@app.route('/api/check/status', methods = ['GET'])
def check_status():
    result = {"status": "OK",
                "version": f'v{cfg.server.version}'}
    logger.info(f"{result}")
    return Response(response=json.dumps(result))   


@app.route('/api/predict', methods = ['POST'])
@Prom_request.time()       # prometheus를 사용해서 request latency 측정 및 기록
def name_predict():
    logger.info(f"---- Start API ----")
    count.inc() # count 1증가
    
    file_path = request.json.get('file_path')
    file_name = osp.basename(file_path)

    result_dict = dict()
    try:
        pass
    except Exception as e:
        message = f"Cannot access to '{file_path}'. Error: {e}"
        logger.error(message)
        abort(430, description=message)
         

    result_dict[file_name] = dict()
    
    
    logger.info(f"---- Complete API ----")
    logger.info(result_dict)
    return Response(response=json.dumps(result_dict))   
 

if __name__ == "__main__":
    app.run(host=cfg.server.host, port=cfg.server.port)