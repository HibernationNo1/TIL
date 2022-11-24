# Gunicorn

> python WSGI으로 사용하는 경우에 대해서만 기록



Gunicorn은 python WSGI이다.

> WSGI : python application이 WEB Server와 통신하기 위한 인터페이스.
>
> WEB Server에서의 요청을 해석하여 python application으로 던지는 역할을 수행한다.



**install**

[공식](https://docs.gunicorn.org/en/stable/install.html)

```
$ pip install gunicorn
```



check

```
$ which gunicorn
```

> 가상환경에 설치된 gnunicorn의 path출력



**사용 방법 with flask**

특정 `.py` 에 flask로 route가 선언되어 있다면 (위 예시`application.py` code)



1. gunicorn config 작성 (python)

   ```python
   bind = "0.0.0.0:4958"		# gunicorn을 통해 4958번 port로 
   workers = 1
   
   accesslog = "gunicorn/access.log"
   
   errorlog = "gunicorn/error.log"
   
   capture_output = True
   
   loglevel = "all"
   ```

   - `bind` : bind할 소켓을 지정 

     > default : 127.0.0.1:8000

   - `workers` : master 프로세스가 fork하는 worker 프로세스의 수

   - `accesslog` : path of gunicorn access log file 

     > access log를 기록할 file. 

   - `errorlog` : path of gunicorn error log file 

     > error log뿐 아니라 gunicorn의 실행, worker process의 spawn, termination 등 master process 레벨의 log도 기록

   - `loglevel `: level of errorlog

     > - `all` : 
     > - `info` : worker의 실행 및 종료까지 파악

2. gunicorn에 연결(API start)

   shell script를 작성해서 사용 (`start.sh`)

   ```shell
   echo Starting Gunicorn server
   exec gunicorn --reload wsgi:app -c gunicorn/gunicorn_cfg.py --daemon
   ```

   - `echo Starting Gunicorn server` : Gunicorn server를 시작했음을 출력

   - `exec gunicorn --reload wsgi:app -c gunicorn/gunicorn_cfg.py --daemon` : gunicorn 실행
     - `--reload` : code가 변경될 때 마다 worker가 재시작되는 option
     - `wsgi:app` : wsgi을 사용하며, `application.py`의 flask객체 이름이 app
     - `-c gunicorn/gunicorn_cfg.py` : `.py` format의 config file을 가리킨다.
     - `--daemon` : back ground로 구동

   ```
   $ start.sh
   ```

   

3. gunicorn에 연결 해체(API stop)

   shell script를 작성해서 사용 (`stop.sh`)

   ```shell
   echo Stopping Gunicorn server..
   exec pkill -9 gunicorn		# -9 : 강제 종료			-15를 사용하면 순차적으로 안전하게 종료
   echo Done!
   ```

   ```
   $ stop.sh
   ```

   

**정리**

1. 어느 서버에서 아래 요청을 한다.

   ```
   $ curl -X POST {url or IP}:{port_1}/{locate} -d "model_type=strawberry" -d "img_file=file_path"
   ```

   `url or IP`를 통해 특정 공유기 접근 후 `port_1`를 통해 접속

   > port는 port forward를 통해 연결되어있어야 한다. (공유기에서)
   >
   > 목적지 : `start.sh` 가 background로 구동중인 device

   `locate` : port위의 특정 locate결정

2. `start.sh` (background로 구동중)

   ```
   exec gunicorn --reload wsgi:app -c gunicorn/gunicorn_cfg.py --daemon
   ```

   `wsgi:app` : 위에서 온 신호(wsgi)를 flask객체 이름 app에 연결한다. 

   이 때 config는 아래와 같다.

   

   `gunicorn_cfg.py`

   ```python
   bind = "0.0.0.0:{port_2}
   workers = 1
   
   accesslog = "gunicorn/access.log"
   
   errorlog = "gunicorn/error.log"
   
   capture_output = True
   
   loglevel = "all"
   ```

   > `port_2` 는 flask의 port번호
   >
   > 그저 사용 안하는 port번호를 입력하면 해당 port는 flask의 app객체가 실행되는 port로 할당된다.

   

   gunicorn으로 `gunicorn_cfg.py`가 구동이 되면 bind를 통해 app객체의 rount함우가 decorate된 function이 run상태가 된다. 

   > (요청에 따라 service를 할땐 `app.run`사용, data를 반환할때는 `app.response_class`  사용)

   ```python
   @app.route('/{locate}', methods=['POST'])
   def exam():
       ...
       return app.response_class(response=json.dumps(res['result']), status=res['status'], mimetype='application/json')
   ```

   > 1번에서 요청이 POST로 왔기 때문에 `methods=['POST']` 명시
   >
   > `locate` : 1번에서 요청에 포함된 locate와 동일해야 한다. (같은 port에도 여러 app가 실행될 수 있기 때문)

   - `app.response_class` 
     - `response` : api 요정으로 반환할 data 
     - `status` : 실패시 500, 성공시 200반환(int)
     - `mimetype` : '{해당 code가 작성된 .py file의 이름}/{반환될 data의 format}'