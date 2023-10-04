# Celery

## intro

python으로 작성된 비동기 작업 큐(Asynchronous task queue/job queue)라이브러리로, python동시성 프로그래밍에서 사용된다.

celery는 task를 broker(Redis, rabbitmq와 같은)를 통해 전달받고, worker가 처리하는 구조이다.

- task: 비동기 큐 작업을 할 process

  >  task 예시:  'DB로부터 얻은 data를 바탕으로 수행할 작업'을 의미한다.

- broker

  - DB로부터 task를 받아 메시지 큐에 적재하고, worker는 메시지 큐로부터 task를 전달받는다.

    - broker를 사용하지 않는다면 

      어떠한 app이 DB의 data를 조회하여 특정 동작(task)을 수행하려고 할 때

      그 과정 중 어떠한 단계에서 블로킹(지연)이 발생한다면, 그 지연시간 만큼 기다린 후에 다른 task를 진행해야 한다.

    - broker를 사용한다면

      특정 동작(task)을 broker에 전달하면, broker는 큐에 해당 task를 쌓는다.

      이후 task가 쌓인 큐를 worker에 전달하면

      worker는 task를 할당받은 tread의 개수만큼 비동기식으로, background에서 수행한다.

      이 과정 중 특정 task를 수행하다 어떠한 단계에서 블로킹(지연)이 발생한다 해도

      - 여러 task를 받아 비동기식으로 진행하기 때문에 지연되지 않는 다른 task들은 정상적으로 result를 반환한다
      - background에서 수행되기 때문에 큐에 적제된 task가 전부 지연된다 해도 사용자는 다른 작업을 이어나갈 수 있다.

  - worker로부터 수행된 task의 result를 수신받는다.

    worker로 전달된 task가 전부 수행이 끝난 후 result를 다시 수신받아야 전달했던 모든 task의 동작이 끝났음을 알 수 있다. 

- worker: task를 비동기 큐 작업으로 수행한다.

![](https://certain-innocent-1e3.notion.site/image/https%3A%2F%2Fprod-files-secure.s3.us-west-2.amazonaws.com%2F5def4dbd-0dd6-497f-8a63-0a75abb4c76d%2Fc49eafbf-a94d-475e-822d-abc4dd1d76d4%2FUntitled.png?table=block&id=d865f463-a15f-4524-b6a4-b0960bae8b7d&spaceId=5def4dbd-0dd6-497f-8a63-0a75abb4c76d&width=2000&userId=&cache=v2)



**개념**

실시간 처리에 중점을두고 작업 예약을 지원하는 작업 큐

- **비동기 작업 처리**

  시간이 오래 걸리는 작업을 background에서 실행한다.

  사용자는 결과를 기다리지 않고 다른 작업을 수행할 수 있다.

- **작업 scheduling**

  특정 시간 또는 주기적으로 작업을 예약하고 실행할 수 있다.

- **분산 작업**

  여러 서버 또는 worker에서 작업을 분산하여 처리할 수 있다.

  이를 통해 처리 능력을 확장할 수 있다.

- **실패 처리 및 재시도**

  celery는 작업이 실패하면 재시도하거나 실패한 작업을 처리하는 매커니즘을 제공한다.



**사용 이유**

- flask와 비교

  Flask는 프로세스를 동기적(Synchronous)으로 처리하기 때문에 업로드된 데이터 처리 또는 이메일 전송과 같이 다소 오래 걸리는 작업이나 무거운 연산 같은 경우 사용자는 웹 서버의 처리가 모두 마무리될 때까지 기다려야 한다.

  이를 개선하기 위해 미리 구현된 비동기 작업 큐 lilbary인 celery를 사용.

Celery는 Python으로 작성된 비동기 작업 큐(Asynchronous task queue/job queue)이기 때문에 Flask와 같은 Python Web Framework에 붙여서 사용하기 수월하다.

- gunicorn과 비교

  gunicorn은 process(API)단위로 비동기식 운영을 하는 web server이다.

  celery는 하나의 process안에서 task단위로 비동기식 동작을 한다.





**Celery 구성 요소**

![](https://miro.medium.com/v2/resize:fit:626/1*Al-ATyDXQGHREGW40CymcQ.png)

- Celery Client

  background 작업을 요청하는데 사용 된다.

- Celery Workers

  Celery Client와 동일한 서버에서 백그라운드 작업을 실행하는데 사용 됩니다.

- Message Broker

  클라이언트는 Message 큐를 통해 작업자와 통신 하며 Celery는 이러한 큐를 구현하는 여러 가지 방법을 지원한다.

  >  가장 일반적으로 사용되는 브로커는 RabbitMQ 및 Redis 



## start-stop

#### start

```
celery multi start {worker_name} --app={python_script}.celery --pidfile="{path/celery.pid}" --logfile="{path/celery.log}" --loglevel=warning
```

- `--app`:  아래 code가 선언된 python script를 명시한다

  ```python
  from celery import Celery
  celery = Celery('celery_instance_name', broker='redis://127.0.0.1:6379/1', backend='rpc://')
  ```

  - `broker` : 사용할 broker를 결정한다

    > 위 예시는 redis사용시

  - `backend`: 작업의 결과를 어디에 저장할지 지정

    - `rpc://` : RPC사용. 

      message que를 사용하여 작업 결과를 저장

    - `redis://localhost:6379/0`: redis사용.  

      key-value database인 redis에 결과 저장

    - `db+driver://username:password@host:port/database` : SQL database사용

      관계형 데이터베이스를 백엔드로 사용하여 저장

    - `file:///tmp/celery-results` : filesystem사용

      file에 저장할때 사용

- `multi` : 여러 worker process를 관리한다

- `--pidfile`: worker process의 PID를 저장할 file의 path를 명시한다 (.pid)

- `--logfile`: celery의 log를 저장할 file의 path를 명시한다. (.log)

- `--loglevel` : logging level을 지정한다

  



#### stop

```
celery multi stop {worker_name} --app={python_script}.celery --pidfile="{path/celery.pid}" --logfile="{path/celery.log}" --loglevel=warning
```





#### restart

```
celery multi restart {worker_name} --app={python_script}.celery --pidfile="{path/celery.pid}" --logfile="{path/celery.log}" --loglevel=warning
```

