# flask_redis

redis를 활용한 session생성

- redis작동 확인

  ```
  $ ps -aux | grep redis
  ```

  

#### session

##### set

```python
from flask import Flask
from flask_redis import FlaskRedis

app = Flask(__name__)

# redis db를 활용하기 위한 url
app.config['REDIS_URL'] = "redis://127.0.0.1:6379/1"			# 예시

redis_client = FlaskRedis(app)	# 내부적으로 `init_app`가 호출되어 redis_client와 app를 연결


def random_string(string_length=12):
    from uuid import uuid4
    random = str(uuid4())
    random = random.upper()
    random = random.replace("-", "")
    return random[0:string_length]

username = "user_name"
prefix = 'session_token:'
token = random_string(32)
timeout = 86400		# session에 대한 정보가 유지되는 시간(sec)

result = redis_client.set(prefix + username, token, timeout)		# session이 성공적으로 생성되면 True를 return
```

- `prefix + username : token` key-value형식으로 data생성 



token을 발급하고 session을 생성하는 예제

```python
from flask import Flask
from flask_redis import FlaskRedis

app = Flask(__name__)

# redis db를 활용하기 위한 url
app.config['REDIS_URL'] = "redis://127.0.0.1:6379/1"			# 예시

redis_client = FlaskRedis(app)	# 내부적으로 `init_app`가 호출되어 redis_client와 app를 연결


def random_string(string_length=12):
    from uuid import uuid4
    random = str(uuid4())
    random = random.upper()
    random = random.replace("-", "")
    return random[0:string_length]


def set_session(token, userid):
    
	prefix = 'session_token:'
	timeout = 86400		# session에 대한 정보가 유지되는 시간(sec)

	result = redis_client.set(prefix + username, token, timeout)		# session이 성공적으로 생성되면 True를 return
    

def make_token(username):
    result = None
	token = random_string(32)
    
    if set_session(token, userid):
        result = token
    return result
   
  
token = make_token("user_name")
```



##### get

```python
token = redis_client.get(prefix + username)		# 해당 token은 b'C24A5F41D9BF4335BD86338E42A52438'와 같은 형태
token = token.decode("utf-8")					# C24A5F41D9BF4335BD86338E42A52438 으로 바꿔줘야 한다
```

`prefix + username`라는 key값으로 내부 data(token)을 get

redis client에서 get을 사용해 값을 return받은 경우, `b'value'` 의 형태로 되어있다

해당 value를 str로 사용하기 위해서 `decode("utf-8")`이 필요하다