# REST API



**사전 지식**

- **URI**(Uniform Resource Identifier): 통합 자원 식별자

  하위로 **URL**이 있다.

  - `https://www.inflearn.com/52034?tab=curriculum`
    - `https://www.inflearn.com` : 주소
    - `52034` : ?앞에 있는 이것은 route
    - `tab=curriculum` : paprmeter(식별자)
    - `https://www.inflearn.com/52034`: 주소 + route = **RUL**

  

- **http와 https의 차이점**

  `http`: 주소 마지막에 `:443`이라는 port번호가 자동으로 할당된다.

  `https`: 주소 마지막에 `:80`이라는 port번호가 자동으로 할당된다.



- web server

  web server는 정적인 HTML page를 return한다.  (요청에 따른 정적인 data를 return)

  web server가 동적으로 data를 return하기 위해서는 WAS framework가 필요하다.

  주요 WAS framework로는 flask, django, rails, node.js 등이 있다.

  > 상용화를 위해서는 별도 전문 web server를 사용해야 하지만, flask는 기본 web server도 간단한 명령으로 제공함



### REST API

data를 가져오기 위해 HTTP protocol을 사용하는 것을 의미하며, REST기반으로 서비스 API를 구현한 것이다.

- **REST**(REpresentational State Transfer): 자원(resource)의 표현(representation)에 의한 상태 전달을 의미

  HTTP(Hypertext Transfer protocol) URL를 통해 원하는 resource를 명시하고, HTTP method를 통해 resource에 대한 CRUD Operation을 적용한다.

  - ` CRUD Operation` : resource를 요청하는 특정한 방법(`HTTP Method`) 



##### HTTP Method

요청하는 방법 

- `GET`(read): 요청을 보내고 data를 받기만 하는 경우
- `POST`(create): 내용(file 등)을 전송 후 data를 받는다.
- `PUT`(Updata): 내용을 갱신한다. 내용(file 등)을 전송할 수 있다.
- `DELETE`(Delete): web resource를 delete한다.

> 보통 `GET`과 `POST`로 모두 구현한다.



#### Request

- **Line**: {`HTTP Method`}{`path of route`}{`version of HTTP`}
  - `HTTP Method`: 요청하는 방법 명시
  - `path of route` : route경로
  - `version of HTTP` : HTTP의 version명시(자동으로 명시됨)

- **Header**
  - `Host`: 주소
  - `Connection`:  keep-alive
- **Body** : optional



##### e.g.

- GET

  GET을 사용할 때 parameter값을 전달할 때는 `URL?{parameter_name = value}` 형식으로 전달해야 한다.

  ```
  $ http GET http://localhost:8080/login?user_name=foo
  ```

  - `user_name=foo` : parameter값 전달

  > 여러개의 parameter를 전달할 땐 `&`를 사용하자
  >
  > ```
  > $ http GET http://localhost:8080/login?user_name=foo&tmp_parameter=bar
  > ```

  







#### Response

- **Line**: {`version of HTTP`}{`Status Code`}{`Status Message`}
  - `ersion of HTTP`: HTTP의 version명시
  - `Status Code`
    - `200`:
    - ㅇ
  - `Status Message`
    - `OK`

- **Hearder**

  - `Server`: web server정보
  - `content-type`:   type of MIME 
  - `content-length`: HTTP Body길이

- **Body** 

  HTML데이터





#### test

**httpie**

postman과는 다르게, terminal에서 api test를 진행할 수 있다.

- install 

  ```
  $ pip install --upgrade pip setuptools		# 또는 python  -m pip install --upgrade pip setuptools
  $ pip install --upgrade httpie
  ```



- how to use?

  `http` {`method of HTTP`} {`URL`}

  ```
  $ http GET http://localhost:8080/json_test
  ```

  

  - options

    `-v` : 요청을 보낼 때 어떤 data가 http request의 header에 들어갔는지, body에 들어갔는지 알 수 있다. 







