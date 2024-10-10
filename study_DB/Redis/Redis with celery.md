### Redis with celery

redis는 celery와 함께 사용하는 경우 message broker역할을 하게 된다.

이 때 redis는 worker로 task를 전달한 후, worker의 result을 다시 받는 동작을 수행한다.

**worker로 task를 전달**

1. celery의 task를 massage queue에 저장

   1. celery를 통해 python script에서 task정의 및 호출

      ```python
      # 간단한 task정의
      @app.task
      def add(x, y):
          return x + y
      
      # task 호출
      add.delay(4, 4)
      ```

   2. 해당 task를 직렬화

      ```
      {
          "id": "4c4c5b64-e2e8-4c18-8ab1-5554f3ef4c56",		# 작업의 고유 ID
          "task": "myapp.tasks.add",							# 작업의 이름
          "args": [4, 4],										# 작업에 전달된 인수
          "kwargs": {},										# 작업에 전달된 키워드 인수
          "retries": 0,										# 작업이 재시도된 횟수
          "eta": null,										# 예약된 실행 시간
          ...
      }
      ```

      > 실제 형태는 다를 수 있다.

   3. `LPUSH`를 사용되어 redis list에 추가

      ```
      LPUSH celery  "{\"id\": \"4c4c5b64-e2e8-4c18-8ab1-5554f3ef4c56\", \"task\": \"myapp.tasks.add\", \"args\": [4, 4], \"kwargs\": {}, \"retries\": 0, \"eta\": null, ...}"
      ```

2. redis로부터 worker로 task전달

   1. `RPOP` 가 사용되어 오래된 작업를 전달

      ```
      RPOP celery
      ```

      > 이 동작을 worker의 thread개수만큼 진행

   2. 역직렬화되어 Python 객체로 변환



**worker의 result을 다시 받는 동작**

task가 완료되면 task의 반환 값이 Redis에 저장한다.

1. redis에서 이전에 worker에 전달했던 task의 고유 ID를 대조하여 해당 task가 완료되었는지 확인

2. 고유ID를 key값으로 하여 redis의 string형태로 저장

   `SET`명령어가 사용됨

   ```
   SET "celery-result-4c4c5b64-e2e8-4c18-8ab1-5554f3ef4c56" "8"
   ```

   > `celery-result-4c4c5b64-e2e8-4c18-8ab1-5554f3ef4c56`: 고유 ID값
   >
   > `8`: task의 result

3. application에서 해당 task의 결과 조회

   ID를 대조하여 Redis에서 결과 get

   ```
   GET "celery-result-4c4c5b64-e2e8-4c18-8ab1-5554f3ef4c56"
   ```

   



