# mqtt

#### mqtt란? 

- M2M, IOT를 위한 프로토콜로서, 최소한의 전력과 패킷량으로 통신하는 프로토콜이다.

- MQTT는 HTTP, TCP등의 통신과 같이 클라이언트-서버 구조로 이루어진 것이 아닌, Broker, Publisher, Subscriber 구조로 이루어져 있다.



#### 용어

**Client**

- MQTT의 broker에 연결된 모든 구독자와 발행자를 의미한다.

**Broker**

- publisher(발행자)와 subscriber(구독자)의 중간에서 서로를 연결해주는 서버 역할을 한다.
- 모든 메세지를 수신, 필터링, 수신받을 메세지를 구독하는 클라이언트에게 송신하는 역할을 한다.

**publisher(발행자)**

- 발행자는 topic과 data를 자신을 구독하는 구독자에게 보낼 수 있다.

**subscriber(구독자)**

- 자신이 구독 한 발행자로부터 topic과 data를 받을 수 있다.

**topic**

- 유튜브의 채널명처럼, 구독자가 구독하는 클라이언트라고 생각하면 된다. 전달하는 데이터의 종류를 나타낸다.

- MQTT의 topic은 '**/**'를 분리 문자로 사용하여 볼터 및 파일과 유사한 계층 구조를 가진다. (mysensors는 다르다)

- topic의 + 와 # 키워드를 가지고 있다. 

  ex)

  > house 
  >
  > house/room1
  >
  > house/room1/main-light    // room1의 main-light 
  >
  > house/room1/left-light	   // room1의 left-light
  >
  > house/room2/main-light	// room2의 main-light 
  >
  > house/room2/left-light
  >
  > house/room1/# 				  // room1의 하위 topic을 모두 포함한다.
  >
  > house/+/left-light 				//모든 room의 left-light 를 의미한다.

**mosquitto**

- MQTT의 broker 중 하나, 중소규모의 mqtt broker다.( 작은 규모의 IOT플랫폼 제작에 적합)



**mosquitto 사용해보기** 

- mosquitto 서버 실행

cmd창에서  mosquitto  입력 >> 서버 실행

1883번 포트를 사용하는 브로커가 활성화된다.

- mosquitto 클라이언트 테스트

[mosquitto 클라이언트 다운](https://mqttfx.jensd.de/index.php/download) (원래는 클라이언트를 코드로 작성하지만, 단순 테스트를 위해 설치해본다.)

우선 cmd창 두 개를 띄운다

> >  publisher (주는사람)  // 먼저 실행해야함
> >
> > 1. cmd > mosquitto_pub -h 호스트IP -t 토픽  //토픽 먼저 설정
> >
> > > cmd > mosquitto_pub -h localhost -t home/temp
>
> >  subscribe (받는사람)
> >
> > 2. cmd > mosquitoo_sub -h 호스트IP -t 토픽
> >
> > > cmd > mosquitto_pub -h localhost -t home //구독 실행
>
> > publisher
> >
> > 3. cmd > mosquitto_pub -h 호스트IP -t 토픽 -m 보낼 데이터
> >
> > > mosquitto_pub -h localhost -t home/temp -m 12345
>
> > subscribe 
> >
> > 4.  12345  // 데이터 받으면 양호









