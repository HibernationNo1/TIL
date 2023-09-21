# gunicorn

**WSGI**

python 스크립트가 web server와 통신하기 위한 interpace

web server에서의 요청을 해석해여 python으로 던지는 역할을 수행한다.



**gunicorn**

python WSGI이다.

web server(Nginx)로부터 요청을 받으면 WSGI를 통해  python에서 실행되는 server app로 전달해주는 역할을 수행한다.



## start with python

### command

gunicorn으로 `server.py` 파일 실행

```
gunicorn --config 'gunicorn.py' server:app
```

- `server:app`: 

  - `server.py`

    실행하고자 하는 python 파일 이름

  - `app`: 

    `app = FlaskAPI(__name__)`, `app = Flask(__name__)` 와 같은 app라는 이름의 WSGI 애플리케이션 객체가 있어야 한다.

- `config`: gunicorn의 설정값을 적용할 file 지정

  `gunicorn.py`

  ```
  from multiprocessing import cpu_count
  
  
  def max_workers():
      return cpu_count()
      # return 4
  
  
  def min_workers():
      return 1
  
  
  bind = '0.0.0.0:5001'		
  max_requests = 1000
  worker_class = 'gevent'
  workers = max_workers()
  timeout = 60
  accesslog = 'run/gunicorn.access.log'
  # access_log_format = '%(h)s %(l)s %(u)s %(t)s "%(r)s" %(s)s %(b)s "%(f)s" "%(a)s" "%(D)s"'
  access_log_format = '%(h)s %(l)s %(t)s "%(r)s" %(s)s %(b)s "%(a)s" "%(M)s ms"'
  errorlog = 'run/gunicorn.error.log'
  pidfile = 'run/gunicorn.pid'
  daemon = True
  reload = True
  ```

  - `bind`: Gunicorn이 바인딩할 IP 주소와 port

    모든 IP의 접속을 허용하며, 5001의 port를 통해 접속해야 한다.

  - `max_requests`: 각 워커가 다시 시작되기 전에 처리할 요청의 최대 수. 

    1000개의 요청을 수행하고 나면 워커 재시작

  - `worker_class`: 워커의 유형

    - `sync` : 각 워커는 한 번에 하나의 요청 수행

      CPU 연산이 많지 않은 경우에는 효과적

      default

    - `gevent`: 비동기 워커

      워커 당 여러 연결을 비동기적으로 처리할 수 있기 때문에 동시에 많은 요청을 처리하는 환경에서 효율적

      > `gevent`는 파이썬의 경량화된 동시성 라이브러리

    - `eventlet`: 워커 당 여러 연결을 비동기적으로 처리

      `gevent`와 유사한 사용 사례에 적합하나 애플리케이션과 라이브러리에 따라 성능과 호환성 차이가 있다.

      > `gevent`와 유사한 비동기 프레임워크를 기반

    - `gthread`: `sync` 워커와 비슷하지만, 각 워커가 여러 스레드를 사용하여 동시에 여러 요청을 처리

  - `workers`: 워커의 개수

  - `timeout`: 워커가 한 번의 요청을 처리하는데 허용되는 최대 시간(sec)

  - `accesslog`, `errorlog`: 접근 및 오류 log를 남길 file path

  - `pidfile`: Gunicorn 프로세스 ID를 저장하는 file의 path

    Gunicorn이 실행되면 지정 path에 PID가 기록된 file생성

    > Gunicorn이 정상적으로 종료될 때 삭제된다.

  - `daemon` : True인 경우 daemon mode로 실행되기 때문에 background에서 실행된다.

  - `reload` : True인 경우 코드 변경이 감지될 때 Gunicorn이 자동으로 재시작



> 실행한 program 종료
>
> 1. ```
>    $ ps aux | grep gunicorn
>    ```
>
> 2. ```
>    kill -9 PID
>    ```









