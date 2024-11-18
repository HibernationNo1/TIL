# Pika

pika는 Python에서 **RabbitMQ와 같은 메시지 브로커와 상호 작용하기 위한 library**로, 이를 통해 Python 애플리케이션이 **AMQP (Advanced Message Queuing Protocol)**을 사용하여 메시지 큐와 통신할 수 있도록 한다.

pika는 RabbitMQ의 공식 AMQP 클라이언트 라이브러리로 널리 사용되며, 주로 **비동기 작업, 마이크로서비스 간의 메시지 전달, 대규모 작업 분산**에 활용된다.

#### 주요 기능

1. **message queue 생성 및 관리**
   - pika를 사용하여 **RabbitMQ 내 큐를 생성하고 관리**할 수 있다.
   - 프로듀서가 큐에 메시지를 전송하고, 컨슈머가 큐에서 메시지를 가져와 처리하는 역할을 한다.

2. **Producer와 Consumer 역할**:
   - pika를 사용하면 **프로듀서(Producer)**로서 메시지를 큐에 추가하거나, **컨슈머(Consumer)**로서 큐에서 메시지를 읽고 처리할 수 있다.
   - 다양한 메서드를 통해 메시지의 송신 및 수신을 조절할 수 있다.

3. **내구성과 확인 기능**

   - 메시지를 영구적으로 유지하기 위해 큐를 내구성 있게 설정할 수 있으며, 메시지가 성공적으로 전달되었는지 확인하는 기능도 제공한다.

     이를 통해 메시지 손실을 방지하고, 애플리케이션의 안정성을 높일 수 있습니다.

4. **라우팅과 교환기(Exchange) 설정**:
   - pika는 RabbitMQ의 **교환기(Exchange)** 개념을 지원하여, 특정 라우팅 규칙에 따라 메시지를 분배할 수 있다.
   - Direct, Topic, Fanout, Headers와 같은 다양한 Exchange 타입을 지원하여 유연한 메시지 라우팅을 가능하게 합니다.

### connect

**연결 예시 코드**

```python
import pika

# RabbitMQ 서버에 대한 계정 정보를 설정
credentials = pika.PlainCredentials('my_user', 'my_password')

# ConnectionParameters에 계정 정보와 호스트를 설정
parameters = pika.ConnectionParameters(
    host='localhost',
    port=5672,
    credentials=credentials
)

# BlockingConnection으로 RabbitMQ에 연결
connection = pika.BlockingConnection(parameters)

# 채널 생성
channel = connection.channel()
```

- `PlainCredentials`: RabbitMQ에 연결할 때 사용할 계정과 암호를 설정하는 객체

- `ConnectionParameters`: 실행중인 RabbitMQ 서버에 연결하는 함수

- `BlockingConnection`: RabbitMQ 서버와의 연결을 설정

  - 이 객체는 **지속적으로 연결 상태를 유지**하며, BlockingConnection 방식은 **메시지를 동기적으로 송수신**하는 데 사용된다.

  - BlockingConnection은 호출 시 즉시 연결을 시도하고, 연결이 성공할 때까지 **프로그램 흐름을 멈추는(Blocking) 방식**으로 작동한다.

  - 이 연결이 생성되면 producer 또는 consumer로서 RabbitMQ와 직접 통신이 가능해진다.

    - producer:  메시지를 **큐에 전송하는 역할**을 한다. 

      `basic_publish` 메서드를 사용하여 큐에 메시지를 추가한다.

    - consumer: 메시지를 **큐에서 수신하고 처리하는 역할**을 한다. 

      `basic_consume` 메서드를 사용하여 큐에서 메시지를 가져와 콜백 함수로 처리합니다.

- `connection.channel()`: **RabbitMQ 연결에서 채널을 생성**한다.

  - 채널은 RabbitMQ 연결 내에서 실제로 메시지를 송수신하는 단위

  - RabbitMQ는 연결 내에서 **여러 채널을 지원**하며, 각 채널은 독립적인 메시지 송수신을 수행할 수 있다.

  - **채널을 생성하여 사용하는 이유**: nerwork resource 최적화와 다중 작업 지원을 위해서. 

    한 개의 물리적 연결에서 여러 채널을 열어 동시 작업을 처리할 수 있다.

### About queue

**예시 code**

```python
import pika

# RabbitMQ 서버에 연결
connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()

# 큐 생성
queue_result = channel.queue_declare(queue='test_queue', durable=True)

# 큐 선언 결과 정보 출력
print("Queue Name:", queue_result.method.queue)
print("Message Count:", queue_result.method.message_count)
print("Consumer Count:", queue_result.method.consumer_count)

connection.close()
```

#### `queue_declare`

 **RabbitMQ에서 큐(queue)를 생성하거나 확인**할 때 사용하는 메서드

- message를 저장하고 소비자(consumer)가 가져갈 수 있는 공간을 확보한다.

- 만약 queue가 이미 존재하면 해당 큐를 다시 생성하지 않고 확인만 한다.

- parameters

  - `queue`: 생성하고자 하는 queue의 이름

    `queue=''` 로 설정하면 RabbitMQ는 큐 이름을 자동으로 생성한다. 

    이 경우 큐의 이름은 무작위로 지정되며, 고유한 이름을 RabbitMQ가 자동으로 부여한다.

  - `durable`: 큐의 내구성을 설정 

    - `durable=True`로 설정하면, RabbitMQ 서버가 재시작되더라도 큐가 삭제되지 않는다.
    - 기본값은 False이며, 이 경우 RabbitMQ 서버가 재시작되면 큐가 사라진다..
    - 내구성이 높은 큐는 애플리케이션이 재시작되거나 서버가 중단되더라도 데이터가 유지되기를 원하는 경우에 사용한다.

  - `exclusive`: 큐의 독점성을 설정

    - `exclusive=True`로 설정하면 현재 연결된 클라이언트에서만 사용 가능하며, 해당 연결이 닫히면 큐가 삭제된다.
    - 주로 임시 큐를 생성할 때 사용된다.

  - `auto_delete`: 자동 삭제 여부를 설정

    - `auto_delete=True`로 설정하면, 큐를 사용하는 마지막 컨슈머가 연결을 끊을 때 큐가 자동으로 삭제된다.
    - 소비자가 존재하는 동안만 큐를 유지할 때 유용하다.

  - `arguments`: queue의 동작을 제어하는 추가적인 옵션을 딕셔너리 형태로 전달할 수 있다.

    예시 code

    ```python
    # 큐 생성 시 arguments를 사용하여 옵션 설정
    channel.queue_declare(
        queue='test_queue',
        durable=True,
        arguments={
            'x-message-ttl': 60000,  # 메시지의 생존 시간 설정 (밀리초 단위, 여기서는 1분)
            'x-max-length': 100      # 최대 메시지 수 설정 (100개로 제한)
        }
    )
    ```

#### `exchange_declare`

RabbitMQ에서 교환기(Exchange)를 생성하는 메서드

abbitMQ의 **Exchange(교환기)**는 message를 라우팅하여 적절한 큐로 전달하는 역할을 하며, 라우팅 규칙에 따라 여러 큐에 메시지를 전송할 수 있다.

Exchange에는 몇 가지 주요 타입이 있으며, 각 타입은 메시지를 큐에 분배하는 규칙이 다르다.

- parameters

  - `exchange`: 교환기의 이름을 지정한다. 

    예를 들어, exchange='logs'로 설정하면 "logs"라는 이름의 교환기가 생성된다.

  - `exchange_type`: 교환기의 유형을 지정한다.

    - **Direct Exchange**

      routing key가 정확히 일치하는 큐에만 메시지를 전달한다.

      특정 큐로 직접 메시지를 보내고 싶을 때 사용된다.

      ```python
      # Direct Exchange 생성
      channel.exchange_declare(exchange='direct_logs', exchange_type='direct')
      ```

    - **Fanout Exchange**

      **모든 바인딩된 큐**에 메시지를 전달한다. (routing key를 무시)

      방송(broadcast) 메시지를 모든 큐로 보내고 싶을 때 사용된다.

      ```python
      # Fanout Exchange 생성
      channel.exchange_declare(exchange='fanout_logs', exchange_type='fanout')
      ```

    - **Topic Exchange**

      **pattern 기반 라우팅**이 가능하여 routing key가 특정 pattern을 만족하는 qeueu로 message를 전달한다.

      라우팅 키는 "."으로 구분된 문자열로 구성되며, 큐의 바인딩 키에 와일드카드를 사용할 수 있습니다.

      사용 사례: 복잡한 라우팅 조건이 필요한 경우 사용된다.

      ```python
      # Topic Exchange 생성
      channel.exchange_declare(exchange='topic_logs', exchange_type='topic')
      ```

    - **Headers Exchange**

      메시지의 **헤더 속성**에 따라 routing된다.

      routing key 대신 헤더 정보를 기반으로 메시지를 특정 큐로 보낼 수 있습니다.

      사용 사례: message 속성에 따라 queue를 정교하게 라우팅하고 싶을 때 사용됩니다.

      ```python
      # Headers Exchange 생성
      channel.exchange_declare(exchange='header_logs', exchange_type='headers')
      ```

  - `durable`: True로 설정하면 교환기가 **지속성**을 가진다. 즉, 서버가 재시작되어도 교환기가 유지된다.

  - `auto_delete`: True로 설정하면 교환기가 더 이상 사용되지 않을 때 자동으로 삭제된다.

  - `internal`: True로 설정하면 내부 교환기로 설정되어, 직접 클라이언트에 의해 메시지가 게시되지 않고 다른 교환기를 통해서만 메시지를 받는다.

- 기본 교환기

  - 자동으로 생성되고 항상 존재한다.

    channel.basic_publish`에서 exchange=''로 지정하는 것만으로 사용할 수 있다.

  - 기본 교환기의 이름은 **빈 문자열로 고정**되어 있어, 사용자에게는 빈 문자열로 접근할 수 있지만 RabbitMQ 내부적으로는 특별한 시스템 교환기처럼 관리된다.

    즉, 기본 교환기는 이름을 변경하거나 수정할 수 없으며, 큐 이름과 동일한 라우팅 키를 사용하여 메시지를 전달할 때 사용한다.

  - `channel.basic_publish`로 메시지를 전송할 때 지정된 교환기가 존재하지 않으면 RabbitMQ는 오류를 발생시키는데, 기본 교환기는 RabbitMQ의 시스템 구조 내에서 미리 정의된 것이므로  빈 문자열(exchange='')로 설정하면 오류가 발생하지 않는다.



#### `queue_bind`

**큐(queue)와 교환기(exchange)를 연결**하여, 교환기를 통해 들어오는 메시지가 특정 큐로 전달되도록 설정하는 메서드

- parameters

  - `queue`: binding할 queue의 이름을 지정한다.

    예를 들어, `queue='my_queue'`라고 설정하면 my_queue라는 큐를 교환기에 binding한다.

  - `exchange`: queue에 message를 전달할 교환기의 이름을 지정한다.

    예를 들어, exchange='logs'라고 설정하면 logs라는 이름의 교환기와 큐를 binding한다.

  - `routing_key`: message를 queue로 보내는 데 사용할 routing key를 지정한다.

    이 값은 교환기의 타입에 따라 다르게 동작한다.

    예를 들어, Direct 교환기에서는 라우팅 키가 정확히 일치하는 큐에 메시지를 전달하고, Topic 교환기에서는 패턴 매칭을 위해 .로 구분된 문자열로 구성된 키를 사용한다.



### producer

message 전송

**예시 code**

```python
import pika

# RabbitMQ 서버에 연결
connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()

# 큐 생성
queue_result = channel.queue_declare(queue='test_queue', durable=True)

# 메시지 전송
channel.basic_publish(exchange='', routing_key='test_queue', body='Hello World')
print("Message sent!")

connection.close()
```



#### `basic_publish`

**RabbitMQ로 메시지를 전송**할 때 사용하는 메서드

- 프로듀서(Producer)가 큐에 메시지를 넣어 소비자(Consumer)에게 전달할 수 있도록 한다.

- parameters

  - `exchange`: message를 전달할 교환기(Exchange) 이름.

    - 기본 교환기를 사용하려면 빈 문자열(exchange='')로 설정한다.

      > 기본 교환기에 대한 설명은 exchange_declare 부분에서 이어서..

    - 교환기는 message를 특정 큐로 라우팅하는 역할을 하며, Direct, Fanout, Topic, Headers 등의 다양한 타입이 있다.

  - `routing_key`: 메시지를 보낼 큐의 이름을 지정하는 routing key

    - Direct Exchange인 경우 routing_key가 특정 큐로 메시지를 라우팅한다.

      예를 들어, routing_key='hello'로 설정하면 이름이 hello인 큐로 메시지가 전송된다.

  - `body`: queue에 보낼 메시지의 내용.

    - 문자열 또는 바이너리 형태의 메시지를 보낼 수 있다.
    - message는 기본적으로 UTF-8로 인코딩되며, RabbitMQ가 이를 바이트로 처리한다.

  - `properties`: message의 속성을 지정할 수 있는 옵션

    - `pika.BasicProperties` 객체를 사용하여 메시지의 우선순위, 만료 시간, 메시지 ID, 콘텐츠 유형 등을 지정할 수 있다.

      `pika.BasicProperties`: **메시지 자체의 속성**을 설정하는 데 사용된다.

      `callback` 함수에서 properties 의 속성값으로 접근할 수 있다.

      **예시 code**

      ```python
      import pika
      
      connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
      channel = connection.channel()
      
      # 메시지 속성 설정
      properties = pika.BasicProperties(
          content_type='application/json',
          content_encoding='utf-8',
          delivery_mode=2,  # 영구 저장
          priority=5,
          correlation_id='12345',
          reply_to='response_queue',
          expiration='60000',  # 1분 후 만료
          message_id='abc-123',
          timestamp=1685578790,
          headers={'retry_count': 1, 'user_id': 'user_42'}
      )
      
      # 메시지 전송
      channel.basic_publish(
          exchange='',
          routing_key='test_queue',
          body='{"key": "value"}',
          properties=properties
      )
      
      print("Message sent with custom properties!")
      connection.close()
      ```

      - `delivery_mode`: message의 영속성 설정을 제어한다.

        `delivery_mode=1` 비영구 message(메모리에서 관리).

        `delivery_mode=2` 영구 message(디스크에 저장, queue가 영속성을 가진 경우에만 유효).

      - `content_type`: 메시지의 **콘텐츠 유형**을 설정한다. 주로 application/json 또는 text/plain 등으로 지정된다.

        예: `content_type='application/json'`

      - `expiration`

        메시지의 **TTL(Time To Live)**을 설정하여 특정 시간 후에 메시지가 자동 삭제되도록 한다.

        값은 밀리초 단위의 문자열로 설정한다.

        예: `expiration='60000'` (60초 후 삭제)

      - `priority`: message 우선순위를 설정한다. 

        우선순위 큐에서만 유효하며, 기본값은 0.

        예: `priority=5`

      - `headers`: 헤더 정보를 딕셔너리 형태로 설정한다. 

        Headers Exchange에서 사용되며, 헤더에 따라 message routing이 가능하다.

        예: `headers={'key1': 'value1', 'key2': 'value2'}`

      - `content_encoding`: message 본문의 인코딩 방식을 지정한다.(default utf-8)

      - `reply_to`: 응답을 받을 queue의 이름을 지정할 때 사용된다.

      - `message_id`: 메시지의 고유 식별자로, 각 메시지에 대한 식별 정보가 필요할 때 설정한다.

      - `timestamp`: 메시지가 생성된 시간을 타임스탬프로 기록할때 사용한다. Unix 시간 형식으로 설정된다.



### consumer

Message 수신

**예시 code**

```python
import pika

# RabbitMQ 서버에 연결
connection = pika.BlockingConnection(pika.ConnectionParameters('localhost'))
channel = connection.channel()

# 큐 생성 (프로듀서와 동일한 큐 이름 사용)
channel.queue_declare(queue='test_queue', durable=True)

# 메시지를 처리하는 콜백 함수 정의
def callback(ch, method, properties, body):
    print(" [x] Received %r" % body)

# 큐로부터 메시지를 소비하고 콜백 함수로 전달
channel.basic_consume(queue='test_queue', on_message_callback=callback, auto_ack=True)

print(' [*] Waiting for messages. To exit press CTRL+C')
channel.start_consuming()
```

#### `basic_consume`

queue에서 message를 소비하기 위한 메서드. 

consumer는 메시지를 큐에서 읽어와 처리하는 역할을 하며, 다양한 인수를 통해 동작 방식을 제어할 수 있다.

- paremeters

  - `queue`: message를 소비할 queue의 이름을 지정한다.

    예: `queue='task_queue'`

  - `on_message_callback`: 메시지를 처리할 callback 함수를 지정한다.

    callback 함수는 message를 소비할 때 호출되며, `ch`, `method`, `properties`, `body`를 인수로 받는다.

  - `auto_ack`: 자동 확인 여부를 설정한다. 

    - True로 설정하면 메시지를 소비한 후 자동으로 확인(Acknowledgment)합니다.
    - False로 설정하면, 콜백 함수 내부에서 basic_ack 메서드를 호출하여 수동으로 메시지 소비를 확인해야 한다.

  - `exclusive`: 해당 큐의 소비자로 현재 연결된 consumer만 작동하도록 제한할 수있다.

    exclusive=True로 설정하면 consumer제한, 다른 consumer가 동일한 큐에 접근하지 못하도록 한다.

  - `arguments`: 추가 설정을 딕셔너리 형태로 전달한다. 

    예를 들어, TTL 설정 등을 포함할 수 있다.



#### callback

queue에서 message를 소비할 때 호출되는 함수로, 각 메시지를 처리하는 역할을 한다.

- arguments

  - `ch` (Channel): RabbitMQ와의 통신을 담당하는 채널 객체.

    이 객체를 통해 message에 대해 **ACK(확인), NACK(비확인), REJECT** 등의 처리를 할 수 있다.

  - `method` (Method): message에 대한 **전달 메타데이터**를 포함하는 객체.

    주요 속성

    - `delivery_tag`: 메시지에 대한 고유 식별자.

      이 식별자는 basic_ack, basic_nack, basic_reject 등을 통해 메시지를 처리할 때 반드시 명시해야 한다.

      ```python
      ch.basic_ack(delivery_tag=method.delivery_tag)
      ```

    - `exchange`: 메시지를 전송한 교환기(exchange)의 이름입니다.

    - `routing_key`: 메시지가 전송된 라우팅 키 이름

    - `redelivered`: 메시지가 **다시 전달되었는지** 여부를 나타내는 부울 값

      True일 경우, 이전에 전송된 후 NACK나 REJECT로 인해 재전송된 메시지를 의미한다.

  - `properties` (Properties): message 속성을 포함하는 객체로, message의 metadata(header) 정보를 담고 있다.

    message의 속성을 확인하거나, 송신할 때 message에 추가적인 메타데이터를 포함할 수 있다.

    `pika.BasicProperties` 를 사용하여 `basic_publish`에 값을 전달하여 설정할 수 있다.

  - body: **message의 실제 내용(본문)**

    바이트 문자열 형태로 전달되며, 필요에 따라 UTF-8 등의 인코딩으로 디코딩하여 사용한다.

-  ack, nack, reject

  - **ack(Acknowledgment**): message가 정상적으로 소비(처리)되었음을 RabbitMQ 서버에 알리는 신호.

    consumer가 queue에서 message를 가져와 작업을 완료하면, 해당 메시지가 제대로 처리되었음을 알리기 위해 ack을 return한다.

    이 과정이 없으면 RabbitMQ는 메시지가 성공적으로 처리되었는지 알 수 없기 때문에, 자동으로 메시지를 다른 컨슈머에게 재전송하거나 큐에 다시 남겨둘 수 있다.

    ```python
    def callback(ch, method, properties, body):
        # 메시지 처리 완료 후 ack 전송
        print(" [x] Received %r" % body)
        ch.basic_ack(delivery_tag=method.delivery_tag)
    ```

  - **nack (Negative Acknowledgment)**: message 처리 실패를 RabbitMQ에 알리는 신호.

    consumer가 message를 처리하는 중에 오류가 발생하거나 메시지를 처리할 수 없을 때 nack을 사용한다.

    nack을 사용하면, 메시지를 다시 큐에 넣어 다른 consumer가 처리할 수 있도록 재전송할 수 있다(requeue=True).

  - **reject**: nack과 유사하지만 특정 message를 거부하고 큐에 다시 추가하지 않는 경우에 사용된다.

    기본적으로 message를 삭제하거나, 필요에 따라 Dead Letter Queue(DLQ)로 전달할 수도 있다.

  **예시 code**

  ```python
  # 메시지 처리 콜백 함수 정의
  def callback(ch, method, properties, body):
      print(" [x] Received %r" % body)
      
      try:
          # 메시지 처리 로직
          # 특정 조건에서 예외 발생 시킴 (예: 메시지 내용이 'error'일 때)
          if body == b'error':
              raise ValueError("Intentional error for testing")
  
          # 메시지 처리가 성공적으로 완료된 경우 ACK 전송
          ch.basic_ack(delivery_tag=method.delivery_tag)
          print(" [x] Message processed successfully")
          
      except ValueError:
          # 메시지 재처리(큐에 다시 넣기)를 위한 nack 전송
          ch.basic_nack(delivery_tag=method.delivery_tag, requeue=True)
          print(" [!] Error occurred, requeuing message")
      
      except Exception:
          # 메시지를 재처리하지 않고 삭제하기 위해 reject 사용
          ch.basic_reject(delivery_tag=method.delivery_tag, requeue=False)
          print(" [!] Message rejected and removed from queue")
  
  # 큐에서 메시지 소비
  channel.basic_consume(queue='task_queue', on_message_callback=callback, auto_ack=False)
  ```

  