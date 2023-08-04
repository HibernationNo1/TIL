# TCP/IP

TCP/IP는 internet에서 사용하는 protocol group을 칭한다.

TCP/IP는 `Application layer`, `Transport layer`, `Network layer`, `Data link layer`, `Physical layer` 총 5개의 layer로 나뉜다.



**OSI**

OSI 7계층은 네트워크 통신을 표준화한 모델로, 통신 시스템을 7단계로 나누어 설명한 것이다. 

하지만 OSI모델이 실무적으로 이용하기에 복잡한 탓에 실제 인터넷에서는 이를 단순화한 TCP/IP 4계층이 사용되고 있다.

![](https://media.geeksforgeeks.org/wp-content/uploads/20230417045622/OSI-vs-TCP-vs-Hybrid-2.webp)

- 위에 위치한 layer일 수록 사용자가 접근하여 사용하는 layer이다.

- 각 계층은 하위 계층의 기능을 이용하고, 상위 계층에게 기능을 제공한다.

  > HTTP는 TCP와 IP프로토콜을 이용해서 작동한다.

- 일반적으로 상위 계층의 프로토콜은 소프트웨어로, 하위 계층의 프로토콜은 하드웨어로 구현된다





**예시**

- application layer (응용 계층)

  HTTP, FRP, DNS, Telnet, SMTP, SSH 등

- Transport layer (전송 계층)

  TCP, UDP

- netwok layer // internet layer (인터넷 계증)

  IP , ICMP, AR 등

- nerwork access layer // network intetface layer (네트워크 계층)

  Ethernet 등



### Encapsulation / Decapsulation

캡슐화 / 역캡슐화

- Encapsulation 

  통신 프로토콜의 특성을 포함한 infomation을 Header에 포함시켜서 하위 계층에 전송하는 것을 의미한다.

- Decapsulation

  통신 수신측에서 Header를 역순으로 제거하면서 원래의 data를 얻는 과정을 의미한다.

![](https://i.ytimg.com/vi/oM4jEIGs1BM/maxresdefault.jpg)

하위 계층으로 내려갈수록 data에 header가 하나씩 붙고(Encapsulation), 다시 상위 계층으로 올라갈수록 data에 header가 하나씩 없어진다(Decapsulation).



## Transport layer

- 두 `Application layer` 사이에서의 process-to-process통신을 제공한다.

- `Application layer`로부터 메시지를 받아 `Transport layer` 패킷으로 캡슐화하여 전송한다.

  TCP로 전송시 이 패킷을 segment라고 부른다.

  UDP로 전송시 이 패킷을 datagram이라고 부른다.

- `Transport layer`의 주된 protocol은 TCP,UDP이다.



### TCP, UDP

**TCP**(Transmission control protocol)



- 수행 단계

  1. connection setup

     연결지향적 service를 제공하기 위해 data를 전송하기 전에 3 - way handsaking을 하여 두 host의 전송 계층 사이에 논리적 연결을 설립한다.

     - 3 - way handsaking

       TCP/IP프로토콜을 이용해서 통신을 하는 응용프로그램이 data를 전송하기 전에 먼저 수신자와 사전에 session을 수립하는 과정을 의미한다.

       - SYN(Synchronization): 연결 요청. session을 설정하는데 사용되며 초기에 시퀀스 번호를 보낸다.
       - ACK(Acknowledgement): 확인 응답. 요청수락.

       1. Host에서 server로 SYN를 보낸다.
       2. server에서 Host로 SYN + ACK를 보낸다.
       3. Host에서 server로 ACK를 보낸다.

       ![](https://velog.velcdn.com/images%2Faverycode%2Fpost%2Fcd53e336-a624-4f8a-b7e5-20fe62eb6648%2Fimage.png)

  2. data transfer

     data를 전송하며, 신뢰성 있는 service를 제공하기 위해 오류제어, 흐름제어, 혼잡제어 등을 실행한다.

     - 오류제어

       훼손된 segment의 감지 및 재전송, 손실된 segment의 재전송, 순서가 맞지 않게 도착한 segment를 정렬하고 중복 segment감지 및 폐기

     - 흐름제어

       data를 보내는 속도와 받는 속도의 균형을 맞춘다.

     - 혼잡제어

  3. connection termination

     4 - way handshaking을 수행한다. (연결 종료)

     - 4 - way handshaking
       1. Client TCP에서 Server tcp로 FIN segment를 보낸다.
       2. Server는 FIN segment를 받았다는 응답으로 ACK를 보낸다.
       3. Server에서 process가 종료되면 Server tcp에서 FIN segment를 Client TCP에게 보낸다.
       4. FIN segment를 받은 Client는 Server로 ACK를 보낸다. server TCP가 ACK를 받으면 연결이 종료된다.

  



- 연결형, 신뢰성 전송 프로토콜
- 신뢰성을 보장하기 위해서 hearder가 더 크고 속도가 비교적 느리다







**UDP**(user datagram protocol)

- 비견결형 프로토콜로 3way handsaking등의 session수립 과정이 없다.
- 흐름제어, 오류제어, 혼잡제어를 제공하지 않는다.
- 적은 양의 overhead를 가지며, 수신 속도가 빠르다.



TCP는 신뢰성이 중요한 통신(HTTP, File전송 등)에 사용되고, UDP는 실시간성이 중요한 통신(스트리밍 등)에 주로 사용된다.



