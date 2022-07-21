# requests

python으로 HTTP통신이 필요한 프로그램을 작성할 때 사용되는 library

**install**

```
$ pip install requests
```



check

```python
import requests
requests.get("https://google.com")
```

> `Responce[200]`	상태 code 200 : 정상



HTTP요청 방식

- GET : `requests.get()`
- POST : `requests.post()`
- PUT : `requests.put()`
- DELETE : `requests.delete()`



### response

응답 전문(response body/payload) 방식

```python
import requests
responce = requests.get("...")
```

- `responce.content` : binary 원문으로 받는다
- `response.text` :  UTF-8로 인코딩된 문자열을 받는다.
- `response.json()` : JSON 포멧을 받는다.
- `response.headers` : metric형태의 meta data를 담고 있을땐 dict형태로 받는다



### requests

요청 전문(request body/payload) 방식



**HTML 양식(form) data 전송** : `data` option사용

```python
import requests
dict_tmp = {"tmp_1" : 1,
       "tmp_2" : 2}

requests.post("...", 
             data = dict_tmp)
```



**json (REST API) data 전송** : `json` option사용

```python
import requests
dict_tmp = {"tmp_1" : 1,
       "tmp_2" : 2}

requests.post("...", 
             json = dict_tmp)
```



dict data전송 : `headers` option사용

```python
import requests
headers = {
    "Content-Type": "application/x-www-form-urlencoded",
}

requests.post("...", 
             headers = headers)
```

header에 실리는 정보는 자원의 형식을 명시하며, 이 값은 표준으로 정해져 있다.

자세한건 `Content-Type` 검색 



## Session



```python
import requests

session = requests.Session()
response = session.get("URL")


```

