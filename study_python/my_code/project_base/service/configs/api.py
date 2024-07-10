import os, os.path as osp


server = dict(
    host = '0.0.0.0',
    port = os.environ.get('PORT', 10015),
    version = '0.0.1'
)


gunicorn = dict(
    max_requests = 1000,
    worker_class = 'gevent', # "uvicorn.workers.UvicornWorker",
    workers = 1,
    timeout = 60,
    daemon = False, #  if os.environ.get("DEBUG", False) else True,         # docker-compose로 command: sh start.sh 를 사용하려면 deamon이 False이여야 한다.
    reload = False,
    prometheus_path = '/tmp/prometheus_multiproc_dir'
)

