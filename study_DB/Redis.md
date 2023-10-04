# Redis

### introduce

- redis는 주로 key-value 저장소로 알려져 있지만, 그 기본적인 key-value 저장 방식 외에도 여러 다양한 데이터 타입을 지원한다.

- database, cache, message broker로 사용되며 인메모리 데이터 구조를 가진 저장소이다.

  redis는 빠른 속도를 자랑하지만 RAM의 용량문제와 휘발성 문제가 있다.

  > 사용
  >
  > 1. 보조적인 수단
  >
  >    - celery와 함께 사용할 때 message broker로 사용
  >
  > 2. main database
  >
  >    휘발성이 강하기 때문에(device가 off되는순간 data를 잃는다.) 두 가지 방법으로 data를 보존한다.
  >
  >    - 여러 server를 사용하여 master server와 slave server를 구성으로 한 cluster구축
  >
  >      elasticsearch의 shard의 개념처럼 여러 server에 data를 복제한 후, master server가 죽더라도 slave server중에서 하나를 master server로 변경해서 사용
  >
  >    - 특정 시간마다 disk로 data를 저장하는 scheduling사용

  때문에 메인으로 사용하는 database보다는 보조적인 수단으로 사용되는 경우가 많다.

- memory(RAM) 기반의 데이터베이스이기 때문에, Disk를 기반으로 하는 RDBMS보다 read가 빠르다.

  데이터를 디스크에 쓰는 구조가 아니라 메모리에서 데이터를 처리하기 때문에 속도가 빠르다.



**DB가 있는데도 Redis라는 인메모리 데이터 구조 저장소를 사용하는 이유**

- 데이터 베이스는 데이터를 물리 디스크에 직접 쓰기 때문에 서버에 문제가 발생하여 다운되더라도 데이터가 손실되지 않는다. 하지만 매번 디스크에 접근해야하기 때문에 사용자가 많아질수록 부하가 많아져서 느려질 수 있다.
- 일반적으로 서비스 운영 초반이거나 규모가 작은, 사용자가 많지 않은 서비스의 경우에는 WEB-WAS-DB 의 구조로도 데이터 베이스에 무리가 가지 않는다. 하지만 사용자가 늘어난다면 데이터 베이스가 과부하 될 수 있기 때문에 이때 캐시 서버(Redis)를 도입하여 사용한다.
- 캐시는 한번 읽어온 데이터를 임의의 공간에 저장하여 다음에 읽을 때는 빠르게 결괏값을 받을 수 있도록 도와주는 공간이다.
- 같은 요청이 여러 번 들어오는 경우 매번 데이터 베이스를 거치는 것이 아니라 캐시 서버에서 첫 번째 요청 이후 저장된 결괏값을 바로 내려주기 때문에 DB의 부하를 줄이고 서비스의 속도도 느려지지 않는 장점이 있다.



#### **Redis 사용에 주의할 점**

- 서버에 장애가 발생했을 경우 그에 대한 운영 플랜이 꼭 필요하다.
  인메모리 데이터 저장소의 특성상, 서버에 장애가 발생했을 경우 데이터 유실이 발생할 수 있다.





#### 동작

redis는 단일 thread model을 기반으로 동작하기 때문에 모든 요청을 순차적으로 처리한다. 

각 client 요청은 순서대로 처리되며, 동시에 처리되는 요청은 없다.

이러한 동작 방식은 복잡한 동시성 문제를 회피하고 data 일관성을 유지하는 데 도움이 된다.





#### data type

- **String (Binary safe)**: 가장 기본적인 key-value 저장 방식.

  value는 문자열 또는 바이너리 데이터

  - 예시

    ```
    SET mykey "Hello, Redis!"		# `mykey`라는 key에 "Hello, Redis!"라는 문자열 값을 저장
    GET mykey						# `mykey`라는 값을 확인하는 경우
    ```

    ```
    "Hello, Redis!"					# 출력
    ```

- **Lists**: 연결 리스트(Linked list)를 기반으로 하는 list 데이터 타입. 

  `LPUSH`, `RPUSH`, `LPOP`, `RPOP` 등의 명령을 사용하여 리스트의 앞이나 뒤에 항목을 추가하거나 제거할 수 있다.

  - 예시

    ```
    LPUSH mylist "World"		# mylist라는 이름의 리스트를 만들고, 문자열 요소 "World"를 왼쪽 끝에 추가합니다. 
    LPUSH mylist "Hello"		# mylist라는 이름의 리스트에 문자열 요소 "Hello"를 왼쪽 끝에 추가
    LRANGE mylist 0 -1			# 내용 확인
    ```

    ```
    1) "Hello"
    2) "World"
    ```

- **Sets**: 순서가 지정되지 않은 유일한 요소의 컬렉션. 

  `SADD`, `SREM`, `SMEMBERS` 등의 명령을 사용한다.

- **Sorted Sets (or ZSets)**: 각 멤버가 연결된 스코어 값을 가지며, 스코어에 따라 정렬되는 set. `ZADD`, `ZRANGE` 등의 명령을 사용한다.

- **Hashes**: Redis의 key-value 내에 또 다른 key-value 구조를 가지는 데이터 타입. 

  작은 객체나 데이터 구조를 표현하는 데 유용하며, `HSET`, `HGET`, `HDEL` 등의 명령을 사용한다.





### install

[공식](https://redis.io/docs/getting-started/installation/install-redis-on-linux/)

**Prerequisites**

```
$ sudo apt install lsb-release curl gpg
```

```
$ curl -fsSL https://packages.redis.io/gpg | sudo gpg --dearmor -o /usr/share/keyrings/redis-archive-keyring.gpg

$ echo "deb [signed-by=/usr/share/keyrings/redis-archive-keyring.gpg] https://packages.redis.io/deb $(lsb_release -cs) main" | sudo tee /etc/apt/sources.list.d/redis.list

$ sudo apt-get update
$ sudo apt-get install redis
```



- 설치 확인

  ```
  $ redis-server --version
  ```

  

**uninstall**

```
$ sudo apt remove redis-server
```







celery와 함게 사용할땐 종료



### start

redis서버 실행

서버 실행에는 두 가지 방법이 있다.

1. ```
   $ systemctl start redis-server # 시작
   $ systemctl stop redis-server # 정지
   $ systemctl status redis-server # 상태 확인
   ```

2. ```
   $ redis-server &
   ```
   
   > `systemstl`을 사용하여 redis를 실행시키는 경우 celery에서 broker경로를 찾지 못할때가 있다.



해당 server에 접속

```
$ redis-cli
```

- ```
  not connected> 
  ```

  연결 실패한 경우 위 처럼 나옴

  `exit`입력으로 종료



### with celery

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

1.  redis에서 이전에 worker에 전달했던 task의 고유 ID를 대조하여 해당 task가 완료되었는지 확인

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

   









