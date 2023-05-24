# HTTP

HyperText Transfer Protocol

web상에서 정보를 전송하기 위한 통신 프로토콜

![](https://media.geeksforgeeks.org/wp-content/uploads/20210905091508/ImageOfHTTPRequestResponse-660x374.png)

- TCP/IP기반

- server에 연결 후 요청에 응답을 받으면 연결을 끊어버리는 Connectionless특성을 갖는다.

  이로 인해 많은 사람이 웹을 이용하더라도 실제 동시 접속을 최소화하여 더 많은 user의 요청을 처리할 수 있다.

- Connectionless특성 때문에 클라이언트의 이전 상태(로그인 유무 등)을 알 수 없는 Stateless특성을 가지고 있다.

  이 때문에 정보를 유지할 수 없어 cookie, session, jwt등의 방법을 사용하여 정보를 유지하고자 한다.

- HTTP는 정보를 text 형식으로 주고받기 때문에 중간에 데이터 유출이 발생할 수 있다.

  때문에 HTTP에 암호화를 추가한 프로토콜인 HTTPS를 사용하기도 한다.



### request

request의 method에도 여러 종류가 있다.



**GET**

client가 server에게 resource를 요청할 때 사용하는 method

필요한 정보를 특정하기 위해 URL뒤에 key-value쌍으로 parameter를 포함한 `query string`을 추가하여 전송한다.

> `https://www.inflearn.com/course/lecture?courseSlug=%EA%B0%9urriculum`
>
> 위의 `?` 뒤에서부터 query string부분이고, `=`의 왼쪽이 key값 오른쪽이 value값이다.

GET요청의 경우 browser에 history가 남게 되고 cash보관이 가능하기 때문에 동일한 요청은 browser에 저장된 값으로 가져올 수 있다.



**POST**

client가 server에게 data처리(data 생성)을 요청할 때 사용하는 method

server는 POST 메시지를 받으면 resource를 등록하는 것 외에도 data를 생성하거나 변경하기도 한다. 또한 특정 process를 처리하기도 한다.

전달할data를 body부분에 포함하여 통신한다.

POST요청의 경우 브라우저에 history가 남지 않고 cash가 불가능하다.



**PUT**

server의 resource를 대체한다.

해당 resource가 없으면 생성한다.



**PATCH**

server의 resource중 일부분을 수정한다.



PUT과 PATCH는 server의 resource를 update하는 method이다.

### response

**Status code**

client로부터 받은 request에 대한 server의 response에 대한 간락한 설명

client가 보낸 HTTP요청에 대한 server의 응답 code로, status code를 통해 요청의 성공/실패 여부를 판단할 수 있다.

- 100번대 (정보)

  요청을 받았으며, 작업을 계속한다.

- 200번대 (성공)

  client가 요청한 동작을 성공적으로 수신하여 이해했고, 성공적으로 처리하였다.

  - 200

    요청이 성공했을 경우

    > 잔액조회 성공
    >
    > 주로 GET에 대한 응답

  - 201

    resource의 생성이 성공했을 경우 

    > 게시글 작성 성공, 회원가입 성공
    >
    > 주로 POST에 대한 응답

- 300번대 

  요청을 완료하기 위해 추가 작업 조치가 필요하다.

  - 302

    추가적인 인증 절차가 필요한 경우

    > kubernetes의 특정 resource에 접근 시 dex인증이 필요한 경우 응답이 302번으로 온다.

- 400번대 (client 오류)

  client의 요청에 문제가 있다.

  - 401

    인증되지 않은 상태에서 인증이 필요한 resource에 접근한 경우

    > 올바르지 않은 형식의 data입력 등

  - 403

    인증된 상태에서 권한이 없는 resource에 접근하는 경우

    > 일반 user가 관리자 메뉴 접근 등

  - 404

    요청한 route가 없음

    > 존재하지 않는 주소

- 500번대 (server오류)

  server가 유요한 요청의 수행을 실패했다.

  - 500

    server에서 예상치 못한 에러가 발생하는 경우





### Access to URL

www.google.com을 주소창에 입력한 경우 

1. **사용자가 browser에 URL입력한다.**
2. **DNS lookup을 통해 서버의 IP주소를 찾는다.**
   1. client의 Application layer에서 DNS server에 해당 URL에 대한 정보(domain name)을 전송한다.
   2. DNS server는 domain name을 토대로 IP주소를 찾아 응답한다.
3. **server로 HTTP request를 보낸다.**
   1. client의 Application layer에서 HTTP request 메시지를 만든다.
   2. Transport layer에서 HTTP request 메시지 정보를 포함하여 TCP/IP 패킷을 생성한다.
   3. server(IP주소)로 전송한다.
4. **server가 HTTP request를 받고, client로 HTTP response를 보낸다.**
   1. server의 Transport layer가 client로부터 TCP/IP 패킷(request)을 받는다.
   2. server의 Transport layer가 TCP/IP 패킷을 unpacking하여 HTTP request를 복원 후 Application layer로 보낸다.
   3. server의  Application layer는 HTTP request를 unpacking하여 URL을 복원 후 server컴퓨터로 보낸다.
   4. 특정 process가 이루어지고 그에 대한 응답 data가 만들어진다.
   5. server의 Application layer에서 응답 data에 대한 HTTP response 메시지를 만든다.
   6. server의 Transport layer가 HTTP response 메시지 정보를 포함하여 TCP/IP 패킷을 생성한다.
   7. client로 전송한다.
5. **도착한 HTTP response 메시지는 web bowser에 의해 출력된다.(렌더링)**
   1. client의 Transport layer가 server로부터 TCP/IP 패킷(response)을 받는다.
   2. Transport layer가 TCP/IP 패킷을 unpacking하여 HTTP response를 복원 후 Application layer로 보낸다.
   3. client의 Application layer에서 HTTP response의 정보를 통해 응답 data를 만든다.
   4. browser는 응답 data를 받고 HTML렌더링 과정을 통해 모니터에 출력한다.





### Cookie & Session

HTTP의 Connectionless(비 연결성)특성과 Stateless(비 상태성)특성에 의해 server는 client에 대한 상태 정보를 유지하지 않는다.

하지만 로그인이나 비밀번호 저장과 같은 기능을 사용하기 위해서는 이를 극복해야 했고, 이를 위해  Cookie & Session을 사용하게 되었다.



#### Cookie

cookie는 client(browser)에 key-value쌍으로 local에 저장되는 data file이다. 유효시간 내에서는 browser가 종료되어도 계속 유지된다.

user가 따로 작업을 하지 않더라도 browser가 cookie를 request header에 담에서 server에 전송한다.

1. server가 client로부터 요청을 받았을 때, client에 관한 정보를 토대로 cookie를 생성한다.

   이를 **set-cookie**라고 한다.

2. server는 client에게 보내는 응답의 header에 cookie를 담아 보낸다.

3. client가 응답을 받으면, browser는 cookie를 cookie derectory에 저장한다.

4. 이후 client가 server에 어떠한 요청을 보낼 때 cookie를 담아 보내게 되고, server는 해당 cookie의 정보를 참조하여 응답하게 된다.



>  예시
>
> - 장바구니
> - 자동로그인 또는 아이디와 비번 저장
> - "오늘 더 이상 이 창을 보지 않음"



#### Session

기본적으로 cookie를 이용하여 구현된다.

- client를 구분하기 위해 각 client에게 session ID를 부여하고 client는 cookie에 session ID를 저장해 둔다.

- user 정보를 browser에 저장하는 cookie와 달리 session은 server측에서 저장하여 관리한다.

- session은 유효시간을 두어 일정 시간 응답이 없다면 끊을 수 있고, browser가 종료될 때 까지 인증상태를 유지할 수 있다.

- 사용자 정보를 server에 두기 때문에 cookie보다 보안은 좋지만 server자원을 차지하기 때문에 server에 과부하를 줄 수 있고 성능 저하의 요인이 될 수 있다.





### authentication & authorization

authentication(인증)은 사용자가 누구인지 확인하는 절차로, 회원가입과 로그인 과정이 대표적인 예시이다.

authorization(인가)는 사용자가 요청하는 것에 대한 권한이 있는지를 확인하는 절차이다.



**Cookie , Session을 통한 authentication & authorization **

1. client가 로그인을 하면 server는 회원정보를 대조하여 authentication을 한다.

2. 회원 정보를 session저장소에 생성하고 session ID를 발급한다.

3. http response header cookie에 위에서 발급한 발급한 session ID를 담아서 보낸다.

4. clinet에서 session ID를 cookie저장소에 저장하고, 이후에 http request를 보낼 때마다 coockie에 session ID를 담아서 보낸다.

   > session ID가 포함된 요청일 경우 로그인을 할 필요가 없다.

5. server에서는 cookie에 담겨져서 온 session ID에 해당하는 회원 정보를 session저장소에서 확인하여 authorization를 진행한다.

   > 해당 회원이 누구인지 알 수 있고 어떤 권한을 가지고 있는지 알 수 있다.
   >
   > 이를 통해 client정보에 떄라 맞춤 응답을 할 수 있다.(추천 시스템) 

6. 응답 메시지에 회원 정보를 바탕으로 처리된 data를 담아서 client에 보낸다.



단점

- Load Balancing및 server효율성 관리 및 확장이 어려워질 수 있다.





**session hijacking**

session ID만 사용하여 악의를 가진 다른 user가 server에 요청을 하면 server는 구별할 방법이 없다.

이를 방지하기 위해 HTTPS를 사용하거나 session에 짧은 주기로 만료시간을 설정하기도 한다.



