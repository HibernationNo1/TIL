# flask

```
$ pip install flask
```



flask는 특정 객채를 만들고, 해당 객체에 웹 서비스의 기능을 추가하는 방식으로 구성된다. 

```python
from flask import Flask

app = Flask(__name__)	# `app`이라는 객체를 만듦
```







## app

기본 순서:

```python
from flask import Flask

app = Flask(__name__)		# create instance

@app.route("/hello")		# define application
def hello():
	return "<h1>Hello World!<h1>"
	
if __name__ =="__main__":
    app.run(host=None, port=None, debug=None)		# excute server
```





### decorater

#### route

적절한 목적지를 찾아주는 기능

URL을 해당 RUL에 맞는 기능과 연결을 해 준다.

- 예시: `https://www.inflearn.com/hello`

  `https://www.inflearn.com` 라는 서버에서 `hello`라는 목적지에 맞는 function을 invoke

  ```python
  @app.route("/hello")		# `/`로 시작해야 한다.
  def hello():
  	return "<h1>Hello World!<h1>"
  ```

  `주소/hello` 라는 경로에 요청이 들어오고, hello라는 function이 실행된다.



##### argument

`< >` 를 사용하면 인자를 받아서 사용할 수 있다.

```python
from flask import Flask

app=Flask(__name__)
	
@app.route("/test/<username>")		# 특정한 값을 받는다.
def get_username(username):			# username이라는 변수를 그대로 받아서 사용
    return f"test: {username}"

if __nmame__ == "__main__":
    app.run(host="0.0.0.0", port= "8080")
```



이 때, arguments의 type도 지정할 수 있다.

```python
@app.route("/test/<int:number>")		# int값을 받도록 지정
def get_username(number):			
    return f"test: {number}"
```

> 따로 지정을 안하면 string으로 인지 



##### methods

API요청이 왔을 때 허용하는 method형식을  명시한다.

```python
@app.route("/exam", methods = ['POST', "PUT"])	
```



#### errorhandler

특정 error가 발생했을 때 default화면을 보여주는 것이 아닌, 내가 만든 특정 결과를 보여주도록 할 수 있다.

```python
@app.errorhandler(404)
def page_not_found(error):
    return "<h1>404 Error</h1>", 404
```



#### before_first_request

web application기동 이후 가장 처음에 들어오는 HTTP request에서만 실행 (argument를 전달받을 수 없다.)

```python
app = False(__name__)

@app.before_first_request
def before_first_request():
    print("flast 실행 후 첫 request")
```







#### before_request

HTTP요청이 들어올 때마다 실행 (argument를 전달받을 수 없다.)

```python
app = False(__name__)

@app.before_request
def before_request():
    print("HTTP request를 받음")
```





#### after_request

HTTP요청 처리가 끝나고 브라우저에 응답하기 전에 실행 (response를 return해야한다.)

```python
app = False(__name__)

@app.after_request
def after_request():
    print("HTTP request에 대한 처리가 끝남")
```





### run

main module로 실행될 때 flask 웹 server 구동

`app.run()`으로 server의 구동이 가능하다.

```
app.run(host=None, port=None, debug=None)
```

- `host`: web 주소

- `port`: port번호  **http: 443**, **https: 80**

- `debug` : debug mode로 실행할지 여부 (True or False)

  > debug mode로 실행 시 오류가 발생하면 자세한 infomation을 포함하여 출력되고 server가 정상 동작을 하지 않을 수 있다.
  >
  > if `True`: `app.debug` is True
  >
  > 개발 test과정에서만 True를 할당한다.





### response_class

route decorator로 감싼 function안에서 response의 형식을 완성한다.

```
response = app.response_class(response=, status=, mimetype=)
```

- `response`: response할 data

- `status`: response시 명시할 status

- `mimetype` : response시 명시할 data의 type

  > `{route_path}/{type}` 형식으로 작성



```python
from flask import Flask

app=Flask(__name__)
	
@app.route("/test/<username>")		
def get_username(username):		
    result = dict(username = username, 
                  foo= "foo",
                  bar= 10000)
    response = app.response_class(response=json.dumps(reslult), status=status, mimetype='application/json')
    
    return response

if __nmame__ == "__main__":
    app.run(host="0.0.0.0", port= "8080")
```





### logger

logging 라이브러리를 사용하여 app.logger를 생성하여 사용

```python
import logging
from flask import Flast

app = Flast(__name__)

if not app.debug:		# debug mode가 아닌 경우에만 실행    
    from logging.handlers import RotatingFileHandler		# 특정 handler를 사용
    file_handler = RotatingFileHandler("exam_log.log", maxBytes = 2000, backupCount = 10)		# 기록할 log file에 대한 정보
    file_handler.setLevel(logging.WARNING)		# 어느 level까지 logging할지 명시
    app.logger.addHandler(file_handler)		# 이제 app.logger로 사용 가능
    
@app.errorhandler(404)
def page_not_found(error):
    app.logger.error(error)
    return "<h1>404 Error</h1>", 404

...

...

if __nmame__ == "__main__":
    app.run(host="0.0.0.0", port= "8080")
```





## jsonify

return data를 json formmat으로 제공한다.



```python
from flask import Flask, jsonify

app=Flask(__name__)

@app.route('/json_test')
def hello_json():
    data = {'one': 1, "two": 2, "tmp": 10000}
    return jsonify(data)

if __name__=="__main__":
    app.run(host="0.0.0.0", port="8080")
```



아래 링크로 접속해보기

```
http://localhost:8080/json_test
```



또는 httpie사용

```
$ http GET http://localhost:8080/json_test
```





## request

RUI에서 prameter값을 flask code안에서 사용할때 필요하다.



### args

api요청으로 여러 arguments를 받았을 때, 해당 arguments의 이름에 따라 받은 값을 받을 수 있다.



```python
from flask import Flask, jsonify, request

app = Flask(__name__)

@app.route('/login')
def login():
    username = request.args.get("user_name")
    if username == "foo":
        return_data = dict(auth = "seccess")
    else:
        return_data = dict(auth = 'failed')
    
    tmp_parameter = request.args.get("tmp_parameter")
    return jsonify(return_data)

if __name__=="__main__":
    app.run(host="0.0.0.0", port="8080")
```



**test by httpie**

- GET

  ```
  $ http GET http://localhost:8080/login?user_name=foo
  ```

  - `user_name=foo` : parameter값 전달

  > 여러개의 parameter를 전달할 땐 `&`를 사용하자
  >
  > ```
  > $ http GET http://localhost:8080/login?user_name=foo&tmp_parameter=bar
  > ```

  

### files

API의 body에서 file을 받을때 사용

```python
@app.route("/exam", methods = ['POST'])	
def exam():
	files = request.files['img_file']			# key : img_file 인 경우 file으로 받음
```

> `img_file`이라는 key를 만든다.
>
> curl명령어를 이용해서 API를 호출할 때 `-d` opiton으로 명시할 수 있다.
>
> - 이 때 file이 `.jpg` format의 image인 경우 아래 code를 활용한다.
>
>   ```python
>   # type(files) : list
>   for file in files:
>   	bin_img = files[file].read()					# 이 때 bin_img는 binary data이다.
>       nparr = np.fromstring(bin_img,np.int8)			# convert binary data to numpy array
>       img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)		# decode numpy array to opencv image
>       # type(img) : numpy
>   ```





### from

API의 body에서 value(srt)을 받을때 사용

> args와 다른 점:

```python
...

@app.route("/exam", methods = ['POST'])	
def exam():
	files = request.form['model_type']			# key : model_type 인 경우 form으로 받음
    
...
```





#### e.g.

`application.py` 

```python
from flask import Flask, request

@app.route("/inference", methods = ['POST', "PUT"])	
def api_inference():
    images = []
   	files = request.files['img_file']
	model_type = request.form['model_type']			
    for file in files:	
        bin_img = files[file].read()				# get file binary data
        nparr = np.fromstring(bin_img,np.int8)		# convert binary data to numpy array
        
        try:
            img = cv2.imdecode(nparr, cv2.IMREAD_COLOR)		# decode numpy array to opencv image
            if img is not None:
                images.append(img)					
        except Exception as e:
            print(f'Error {e} when convert request stream to image')
            print(bin_img)
     
    for sub_images in images:
        result = inference(sub_images, model_type)		# inference : img와 model을 받아서 inference
    
    
    response = app.response_class(response=json.dumps(res['result']), status=res['status'], mimetype='application/json')
    return response

if __name__=="__main__":
    app.run(debug=True, host = "0.0.0.0", port=4958)
```

> `port` 기억 



서버로부터 받는 body 형식

```
$ curl -X POST http://127.0.0.1:4958/inference -d "model_type=strawberry" -d "img_file=file_path"
```

- `http://127.0.0.1:4958/inference` : url주소

- `-d` : data를 받는 option

  - `"model_type=strawberry"`: `request.form['model_type']		` 이 code에 선언되어 있기 때문에 `model_type`를 key값으로 사용해서 value를 받음

  - `"img_file = file_path"` :  `request.files['img_file']` 이 code에 선언되어 있기 때문에 `img_file`를 key값으로 사용해서 file을 받음

    



