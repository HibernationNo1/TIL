# Pipeline

Pipeline이란, 모델의 일련의 학습과정을 의미한다.



##### 사전 지식

- 기술 부채(Technical Debt)란?

  현 시점에서 더 오래 소요될 수 있는 더 나은 접근방식을 사용하는 대신 쉬운(제한된) 솔루션을 채택함으로써 발생되는 추가적인 재작업의 비용을 반영하는 소프트웨어 개발의 한 관점이다.

  기술부채를 없애는 방법

  - 리팩토링
  - 종속성 제거
  - 단위 테스트
  - API 강화
  - 미사용 코드 삭제
  - 문서화

- Pipeline이 왜 필요한가?

  ML시스템에서는 기존에 알려진 코드 수준의 기술 부채 제거 방식으로는 문제를 해결하기 어렵기 때문에, 기술 부채를 미리 제거하기 위해서 Pipeline이 필요하다.

- ML개발

  ML은 본질적으로 실험이다. 다른 feature, algorithm, mpdeling 기술 및 parameter 구성을 시도해 가능한 빨리 문제점에 가장 적합한 것을 찾는다. 

  무엇이 효과가 있었는지, 무엇이 그렇지 않은지를 추적하고, 코드 재사용을 극대화 하면서 재현성을 유지하는 것이 과제다.

- ML model

  ML model은 coding뿐 아니라 지속적으로 발전하는 data 프로파일 때문에 performance가 저하될 수 있다. 따라서 data의 통계치를 추적하고 model의 온라인 performance를 모니터링해 예상치를 벗어날 때 알림을 보내거나 롤백해야 한다.



**머신러닝 문제의 특징**

- 쉬운 Machine Learning의 문제
  - data의 변화가 **천천히** 일어난다
  - 모델 재학습이 다음에 의해 일어난다.
    - 더 많은 data로 model의 perfomance를 개선할 때
    - software 혹은 system의 변화가 있을 때
  - labeling은 다음과 같은 방법으로 이루어 진다.
    - 실 서비스를 통해 수집한 데이터
    - 크라우드 소싱
- 어려운 Machine Learning의 문제
  - data의 변화가 **빠르게** 일어난다.(주 단위로)
  - 모델 재학습이 다음에 의해 일어난다.
    - **model의 perfomance가 저하될 때**
    - 더 많은 data로 model의 perfomance를 개선할 때
    - software 혹은 system의 변화가 있을 때
  - labeling은 다음과 같은 방법으로 이루어 진다.
    - **User의 직접적인 피드백**
    - 실 서비스를 통해 수집한 데이터
    - 크라우드 소싱