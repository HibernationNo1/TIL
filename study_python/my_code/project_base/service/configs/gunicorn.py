"""gunicorn WSGI server configuration."""
from multiprocessing import cpu_count
import os, os.path as osp

from configs.default import BASE_LOG_DIR
from handlers.config import Config
# config를 file로부터 load하고 registry에 저장 
cfg = Config.fromfile('configs/api.py')

def max_workers():
    return cpu_count()

def half_workers():
    return round(cpu_count()/2)

# gunicorn의 여러 instance에 대한 metrix을 한곳에 모아 기록(한번에 관리)하기 위해 `PROMETHEUS_MULTIPROC_DIR` 설정 필요
prometheus_path = cfg.gunicorn.prometheus_path
os.environ['PROMETHEUS_MULTIPROC_DIR'] = prometheus_path
os.makedirs(prometheus_path, exist_ok=True)


bind = f'{cfg.server.host}:{cfg.server.port}'
max_requests = cfg.gunicorn.max_requests
worker_class = cfg.gunicorn.worker_class
workers = 1
timeout = cfg.gunicorn.timeout

if len(BASE_LOG_DIR.split('/')) > 1:
    # BASE_LOG_DIR 가 logs/container_name 인 경우
    accesslog = osp.join(osp.dirname(BASE_LOG_DIR), 'gunicorn.all_access.log')
else:
    # BASE_LOG_DIR 가 logs 인 경우
    accesslog = osp.join(BASE_LOG_DIR, 'gunicorn.all_access.log')
access_log_format = '%(h)s %(l)s %(t)s "%(r)s" %(s)s %(b)s "%(a)s" "%(M)s ms"'
errorlog = osp.join(BASE_LOG_DIR, f'gunicorn.error.log') 
pidfile = osp.join(BASE_LOG_DIR, f'gunicorn_master.pid')
worker_pidfile = osp.join(BASE_LOG_DIR, 'gunicorn_worker.pid')  # Worker PID 파일 경로
daemon = cfg.gunicorn.daemon
reload = cfg.gunicorn.reload



# post_fork 훅 추가
def post_fork(server, worker):
    with open(worker_pidfile, 'a') as f:
        f.write(f"{worker.pid}\n")