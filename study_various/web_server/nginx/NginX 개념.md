# NginX

## introduction

**적은 자원으로 더 빠르게 서비스를 제공**하는것을 목표로 하는 '웹 서버'



#### Reverse Proxy

NginX는 Reverse Proxy

- Proxy란?

  프록시 서버는 클라이언트가 자신을 통해서 다른 네트워크 서비스에 간접적으로 점속할 수 있게 해주는 컴퓨터 시스템이나 응용 프로그램을 가리킨다.

  프록시 서버는 네트워크 상 어디에 위치하느냐, 혹은 어느 방향으로 데이터를 제공하느냐에 따라 **Forward Proxy**, **Reverse Proxy**로 나뉜다.

  ![](https://miro.medium.com/v2/resize:fit:720/format:webp/1*xvcdLFcqCTH-GBD6VsnBfg.png)

- Forward Proxy

  Forward Proxy는 client의 바로 앞에 위치한다.(최전방)

  client가 요청을 하는 경우, 신호는 요청의 목적지 server로 가는 것이 아니라 목적지 server의 Forward Proxy에 전달되게 된다.

  Proxy Server는 해당 요청을 인터넷으로 전달하고, 인터넷은 목적지 server로 요청을 전달한다.

  이후 목적지 server는 인터넷으로 응답을 전달하고, 인터넷은 Proxy Server로 응답을 전달하며, 마지막으로 Proxy Server는 client에데 응답을 준다.

  - **보안** 

    client는 Forward Proxy를 통해서만 외부에 요청을 하기 때문에 client가 해당 서버 혹은 웹 사이트에 직접적으로 접근하는 것을 방지할 수 있다. 

    대표적인 예가 client가 특정 사이트에 접근할 수 없도록 막을 수 있는 기능이다.

  - **캐싱** 

    client가 요청을 할 경우, Forward Proxy는 해당 요청을 캐싱하여 다른 client 혹은 동일한 요청이 들어올 경우 캐싱된 데이터를 전달해준다. 이렇게 되면 client는 캐싱된 데이터를 받아오기 때문에 서버에 부하를 줄일 수 있다.

  - **암호화** 

    client의 요청은 Forward Proxy 서버를 통과할 때 암호화 된다. 암호화 된 요청은 다른 서버를 통과할 때 필요한 최소한의 정보만 갖게 되는데, 이는 client의 ip를 숨길 수 있다는 장점이 있다. 요청을 받은 서버에서 ip를 역 추적해도 Forward Proxy 서버의 ip만 알 수 있게 된다.

  우리가 흔히 말하는 ‘Proxy Server’란 바로 Forward Proxy Server를 의미하는 것이다.

**Reverse Proxy**

Reverse Proxy는 client 다음의 인터넷 그 앞에 위치한다.

client가 요청을 하는 경우, 신호는 요청의 목적지 server로 가는 것이 아니라 목적지 server에서 관리하는 인터넷(Reverse Proxy의 url)으로 전달되고, 인터넷은 Reverse Proxy로 요청을 보내게 된다.

Reverse Proxy는 배후의 내부 server로 요청을 보낸다.

- load balancing

  대량의 트래픽이 있을 경우, Reverse Proxy는 내부의 여러 server에 트래픽을 분산하여 요청을 전달하여 과부하를 예방할 수 있다.

- 보안

  Reverse Proxy를 사용하면 본래 서버의 IP주소를 노출시키지 않을 수 있다.

- 암호화

  Reverse Proxys는 들어오는 요청을 복호화하고, 나가는 응답을 암호화 해 주므로 client와 본 server간의 암호화 통신 비용을 절감할 수 있다.

#### 장애 대응

Backend 서버에 대한 요청과 응답을 토대로 장애를 판단할 수 있다.

이를 통해 서버 상태를 monitering할 수 있고, backend server의 활성화 여부를 확인할 수 있다.

#### Keep Alive

Http 소켓 연결이 종료된 시점부터 웹 서버에 설정된 Timeout 까지 기존 소켓을 유지하는 기능이 있다.

이를 통해 Http 연결 소켓이 얼마나 지속되어 연결될 지를 설정하여 CPU을 좀 더 효율적으로 사용할 수 있고 연결 시간에 대한 이득을 챙길 수 있다.



#### Sub Domain

가상호스트 방식으로 두 개의 server을 하나의 웹서버에서 호스팅할 수 있게 해준다.





#### event-driven

웹 서버에 대한 요청을 관리하며, 그 과정에서 비동기 동작인 **event-driven**방식을 사용한다.

요청을 하나의 Event라 보고 Event Handler으로 관리를 하기 때문에 **메모리의 낭비가 적다**.

- multi threading과의 차이점

  ![](https://i.stack.imgur.com/waZGw.png)

  threading은 작업에 의한 응답을 받아야 해당 작업이 '끝났다'고 판단한다.

  그 과정에서, 작업이 시작되면 끝났다고 판단 될 때까지 해당 thread는 다른 작업을 수행하지 않는다.

  하지만 event-driven은 작업이 시작되면 응답이 올 때까지 해당 작업에 관심을 가지지 않는다.  (background에서 작업을 수행한다.)

  단지 그 작업의 응답이 올 때만 다시 자원을 사용해 응답을 받을 뿐이다.

   ![](https://i.stack.imgur.com/VdHKP.png)

- Event Handler

  어떤 event가 시작되었었고, 그 중 어떤 이벤트가 끝났는지 관리하는 역할을 한다. 

  ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Ft1.daumcdn.net%2Fcfile%2Ftistory%2F99A62B3E5B6EF60D1A)

때문에 Nginx란 `경량화된 소프트웨어 웹 서버`로 불리기도 한다.



주로 

HTTP Server로 활용되며 정적 파일들을 처리하기 위해 사용된다.

Reverse Proxy Server로 활용된다. 80번 포트로 들어오는 내용을 3000, 4000, 9000 등의 다른 포트로 분산 시켜줄 수 있다.




