# gunicorn

gunicorn은 WSGI(Web Server Gateway Interface)서버로, python으로 작성된 web application과 python으로 작성된 server사이의 약속된 interface규칙이라 이해햐면 된다.





## start

```
$ gunicorn --config 'config/gunicorn.py' server:app
```

- `--config 'config/gunicorn.py'`: gunicorn실행 시 참조할 config파일 위치

- `server:app`: `{Module_name}:{Variable_name}` 지정

  `Module_name.py` 안에 `app = Flask(__name__)` 이 존재하는 형태





## config

ugnicorn실행 시 참조하는 config파일

name: `gunicorn.config.py`(default) 

**예시**

```python
"""gunicorn WSGI server configuration."""
from multiprocessing import cpu_count


def max_workers():
    return cpu_count()

def half_workers():
    return round(cpu_count()/2)


def min_workers():
    return 1


bind = '0.0.0.0:5004'		# server에서 지정한 host:port 를 명시한다.
max_requests = 1000			# 각 werker가 처리할 수 있는 요청의 개수. 
							# 해당 만큼의 요청을 처리했다면 werker가 자동으로 재시작된다.
worker_class = 'gevent'		# werker의 type을 지정한다.
							# `gevent`: 비동기 처리를 위한 경량화 된 워커를 사용
workers = half_workers()	# werker의 숫자 지정
timeout = 60				
accesslog = 'run/gunicorn.access.log'		# 접근 log의 파일 경로
access_log_format = '%(h)s %(l)s %(t)s "%(r)s" %(s)s %(b)s "%(a)s" "%(M)s ms"'
											# 접근 log의 파일 형식 지정.
    
errorlog = 'run/gunicorn.error.log'			# python code에 의한 error log의 파일 경로. 
pidfile = 'run/gunicorn.pid'				# master process의 PID를 저장할 파일의 경로
daemon = True				# deamon으로 실행할지 여부. True로 설정하면 background에서 실행된다.
reload = True				# code가 수정되면 구동되고 있는 server에 바로 적용
							# development환경에서는 True, production환경에서는 False를 권장

```





## werker

Gunicorn은 "프리포크 워커 모델"을 사용한다.

이는 Gunicorn이 시작될 때 부모 프로세스(master process)가 생성되고, 이 부모 프로세스는 여러 개의 자식 프로세스(workers)를 관리하는 것이다.

- **부모 process**: 이 프로세스는 설정을 로드하고, 자식 워커 프로세스들을 관리(생성 및 종료)하며, 서버의 전반적인 작동을 조정한다.

- **자식 process(werkers)**: 이 프로세스들은 실제 HTTP 요청을 처리한다.

  각 워커는 독립적으로 요청을 받아 처리하므로, 다수의 요청을 병렬로 처리할 수 있다.

이러한 구조는 Gunicorn 서버가 높은 동시성을 갖고 효율적으로 요청을 처리할 수 있게 해준다.

설정 파일에서 `workers` 옵션을 통해 생성할 워커 프로세스의 수를 조정할 수 있습니다.





## zombi process

Gunicorn을 사용하다 보면 werker가 좀비 프로세스가 되는 경우가 있다.



해결방법 

1. 