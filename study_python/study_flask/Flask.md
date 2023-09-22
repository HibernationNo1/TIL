# Flask

app instance생성

```python
from flask import Flask
from flask import request

app = Flask(__name__)

@app.route("/api/rout/path", methods=['GET'])
def example_function():
    
```

- `methods` :  http method



### request

##### data

```python
@app.route("/api/rout/path", methods=['POST'])
def example_function():
    tmp = request.data["tmp"]
    bar = request.data["bar"]
    print(tmp, bar) 			# tmp_value, bar_value 출력
```



- 위 app에 보낼 curl 예시

  ```
  curl --location --request POST 'http://127.0.0.1:5001/api/rout/path' --header 'Content-Type: application/json' --data '{"tmp":"tmp_value","bar":"bar_value"}' 
  ```

  



##### headers

```python
@app.route("/api/rout/path", methods=['GET'])
def example_function():
    headers = request.headers
    print(headers)
    Authorization = headers['Authorization']   
```

출력

```
request.headers ; Host: 127.0.0.1:5001
User-Agent: curl/7.68.0
Accept: */*
Content-Type: application/json
Authorization: TOKEN
```



- 위 app에 보낼 curl 예시

  ```
  curl --location --request GET 'http://127.0.0.1:5001/api/rout/path' --header 'Authorization: TOKEN' 
  ```







##### args

```python
@app.route("/api/rout/path", methods=['GET'])
def example_function():
    args_list = request.args.to_dict()
    print(args_list)
```

출력

```
{'userid': 'UID', 'pcodes': 'PCODES', 'uid_type': 'UID_TYPE'}
```





- 위 app에 보낼 curl 예시

  ```
  curl --location --request GET 'http://127.0.0.1:5001/api/rout/path?userid=UID&pcode=PCODE&uid_type=UID_TYPE' --header 'Authorization: TOKEN' 
  ```

  router경로 뒤에 `?`를 붙인 후 전달하고자 하는 arg를 명시한다.

