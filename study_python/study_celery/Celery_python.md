# Celery_python

**install**

```
$ pip install celery
```





### 비동기 작업 처리

**set celery application**

`celery.py`

```python
from celery import Celery

# set celery application
# celery를 사용하기 위해 application설정
app = Celery('app_name',
             broker='redis://localhost:6379/0',  # 메시지 브로커 설정 (Redis 예시)
             backend='redis://localhost:6379/0',  # 결과 저장 및 추적 설정 (Redis 예시)
             include=['myapp.tasks'])  # 작업 모듈 포함

# 위 내용은 app.task()을 사용하든 shared_task()을 사용하든 반드시 어느 file에 정의되어야 한다.-----

# 작업 정의
@app.task()
def task_function(a, b):
    return a + b
```

- app에 종속적이지 않게 사용하는 경우 `shared_task()` 사용

  ```python
  from celery import shared_task
  
  @shared_task()
  def task_function(a, b):
      return a + b
  ```









**start celery worker**

```
$ celery -A app_name worker --loglevel=info
```

- `-A app_name`: app_name라는 이름의 Celery application을 명시

이후 정의된 작업 실행

```python
from celery import task_function

result = task_function.delay(4, 5)  # 작업 비동기 실행
```

- `delay`: 작업을 예약하고 결과 객체를 반환



**check result**

```python
from celery import task_function

result = task_function.delay(4, 5)  # 작업 비동기 실행
print(result.status)  # 작업 상태 확인

result_value = result.get()  # 작업 결과 얻기
```







### 작업 scheduling

**scheduling 작업 정의**

`tmp/tasks.py` 정의

```python
from celery import shared_task

@shared_task
def scheduled_task():
    # 스케줄링 작업 내용
    pass
```



**set Celery Beat**

`celerybeat_conf.py` (`celery.py`나 `tasks.py`와 같은 파일 내에 설정하지 않는다. 독립덕인 file생성 후 설정한다.)

```python
from celery import Celery
from celery.schedules import crontab

# celery를 사용하기 위해 application설정
app = Celery('myapp')

# Celery Beat 설정
app.conf.beat_schedule = {
    'scheduled-task': {							# 정의된 scheduling의 이름
        'task': 'tmp/tasks.scheduled_task',		# scheduling 작업 경로
        'schedule': crontab(minute=0, hour=3),  # 매일 오전 3시에 실행
    },
}
```



**start Celery Beat **

```
$ celery -A myapp beat --loglevel=info
```

