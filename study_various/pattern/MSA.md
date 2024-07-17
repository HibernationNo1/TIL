# MSA

**MSA(MicroServices Architecture) pattern**: 소프트웨어 시스템을 독립적으로 배포, 개발 및 유지보수할 수 있는 작은 서비스 단위로 분할하는 디자인 패턴

- 마이크로서비스는 특정 비즈니스 기능을 수행하며, 서로 다른 프로그래밍 언어로 작성될 수 있고, 독립적으로 배포될 수 있다.
- 각 AI 모델 또는 서비스가 독립된 마이크로서비스로 배포되어, 독립적으로 스케일링, 배포 및 유지보수가 가능하기 때문에 AI 모델 서빙에 매우 적합한 패턴이다.
- 서비스 간의 통신은 주로 HTTP/HTTPS를 통한 RESTful API 또는 메시지 큐를 통해 이루어진다.



### Structure for AI model service

AI 모델 서비스는 일반적으로 아래의 동작이 순서대로 이루어진다.

1. **Get input data**: 데이터를 받는다.
2. **Data pre-processing**: 데이터 전처리를 수행한다.
3. **Model predict**: AI model에 의한 추론을 수행한다.
4. **Data post-processing**: 추론 결과를 서비스를 위한 데이터로 만드는 후처리를 수행한다.
5. **Send result data**: 결과 데이터를 전송한다.

- 위 과정 중 3번을 제외한 1, 2, 4, 5 과정은 Controller에서 수행한다.

  ![](https://github.com/HibernationNo1/TIL/blob/master/image/pattern/AI_API_1.png?raw=true)

  이 때, Controller와 Model inference API는 독립적인 환경(Node or pod or container)에 배포된다.

- 위 과정 중 3번은 Model inference API라는 독립적은 환경에서 진행되기 때문에 Controller와 HTTP/HTTPS를 통한 RESTful API 또는 메시지 큐를 통해 데이터를 주고받는다.

- 위 과정의 앞, 뒤에는 송출을 담당하는 서비스가 있다.(Web service)

  웹 서비스에서 다수의 AI 서비스를 제공한다면 아래와 같은 구조가 된다.

  ![](https://github.com/HibernationNo1/TIL/blob/master/image/pattern/AI_API_2.png?raw=true)

