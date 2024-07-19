import os, os.path as osp
import uvicorn

_base_ = ['database.py']
_name_ = 'main'


server = dict(
    host = '0.0.0.0',
    port = os.environ.get('PORT', 10015),
    version = '0.0.1',
    middleware = dict(
        content_type = "application/json",
        allowed_ips = ["all"]  # ["127.0.0.1", "192.168.1.1"],
    )
)

logger = dict(
    service = dict(
        name = "main",
        file = "main.log"
    ),
    middleware = dict(
        name = "middleware",
        file = "main.log"
    )
)



gunicorn = dict(
    max_requests = 1000,
    worker_class = uvicorn.workers.UvicornWorker, # "gevent",
    workers = 1,
    timeout = 60,
    daemon = False, #  if os.environ.get("DEBUG", False) else True,         # docker-compose로 command: sh start.sh 를 사용하려면 deamon이 False이여야 한다.
    reload = False,
    prometheus_path = '/tmp/prometheus_multiproc_dir'       # gunicorn환경에서 prometheus사용 시 임의의 dir을 만들어야 한다.
)

