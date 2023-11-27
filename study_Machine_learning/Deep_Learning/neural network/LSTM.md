# 장/단기 기억 네트워크(Long Short-Term Memory, LSTM)

LSTM은 RNN의 Vanishing Gradient Problem(경사도 사라짐 문제)을 해결하여 더 좋은 성능을 보이기 위해 탄생한 network이다.

Vanishing Gradient Problem을 이해하기 위해서는 RNN의 순환 구조를 알아야 한다.





### 1. RNN

Recurrent Neural Network(RNN)이란 **딥 러닝의 가장 기본적인 시퀀스 모델**로, 순서에 따라 서로 연관된 정보를 가진 데이터(시계열 데이터)를 다루기 위해 고안된 신경망이다. 

RNN은 기본적인 ANN구조에서 이전 시간(t-1)의 은닉층의 출력값을 다음 시간(t)에 은닉층의 입력값으로 다시 집어넣는 경로가 추가된 형태이다.



![](https://wikidocs.net/images/page/22886/rnn_image2_ver3.PNG)



**수식**

![](https://wikidocs.net/images/page/22886/rnn_image4_ver2.PNG)

- 은닉 상태값

  
  $$
  시간t일때\ 은닉 상태값: h_{t} = \sigma(W_{x_t}x_t + W_{h_{t-1}}h_{t-1} + b) \\
  W_{x}: 입력층을\ 위한\ 가중치\ \\
  x_{t}: 입력층의\ input \\
  W_{h}: 이전\ 시점(t-1)의\ 은닉\ 상태값h_{t-1}을\ 위한 가중치 \\
  b: bias \\
  \sigma: 활성 함수
  $$

  - 은닉 상태값에 사용되는 활성 함수는 보통 tanh(하이퍼볼릭 탄젠트)를 활용한다.

    ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbD7Rwb%2FbtrEfD65Qtx%2FvR9hVsZl21L4u1tP2VHna1%2Fimg.png)
    $$
    \frac{e^x - e^{-x}}{e^x + e^{-x}}
    $$
    -1과 1사이의 값을 가지며, 0의 위치에서 기울기가 최대치로 1이다. 

  - 예시)  

    - `t = 1` 인 경우
      $$
      h_{1} = \sigma(W_{x_1}x_{1} + b)
      $$

    - `t = 2` 인 경우
      $$
      h_{2} = \sigma(W_{x_2}x_{2} + W_{h_1}h_{1} + b) \\
      = \sigma(W_{x_2}x_{2} + W_{h_1}\sigma(W_{x_1}x_{1} + b) + b)
      $$

-  출력값
  $$
  시간\ t일때\ 출력값: y_{t}: f(W_{y}h_{t}+b) \\
  W_{y}: 출력층을\ 위한\ 가중치 \\
  h_{t}: 은닉\ 상태값 \\
  f: 활성화 함수
  $$

  - 출력값에 사용되는 활성 함수는 비선형(sigmoid, tanh, ReLU 등) 함수 중 하나이다.



위 수식을 통해 Vanishing Gradient Problem이 왜 발생하는지 알 수 있다.

은닉 상태값인 `h_{t}`는 sequence가 넘어갈수록 Weight가 곱해져 본래의 영향력을 점점 잃게 되기 때문이다.

- 예시

  ![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSsZD1lr3mkJp7ioA758ZQNIqsHz11E5njHHw&usqp=CAU)

  시간축 1에서 input data의 영향력은 크게 남아있지만, 새로운 시간축에서 들어온 input data의 영향력이 시간축 1의 input data위에 반복해서 덮어씌워지다 보면

  시간축 1의 input data의 영향력은 점점 약해지는 것

때문에 RNN은 현재 시간축에서 멀리 떨어진 시간축의 데이터의 중요도를 크게 고려하지 못하기 때문에, 장기 기억력을 가지지 못한다.





### 2. LSTM

LSTM은 은닉층을 각각의 노드가 input gate, forget date, output gate로 구성된 메모리 블럭이라는 조금 복잡한 구조로 대체한다. (이를 이용해서 경사도 사라짐 문제를 완화할 수 있다.)

![](https://kr.mathworks.com/help/deeplearning/ref/lstmgates.png)

- 경사도 사라짐 문제 해결 동작

  아래 그림에서 은닉층의 아래는 input gate, 은닉층의 왼쪽은 forget gate, 은닉층의 위쪽은 output gate를 나타낸다. 또한 o은 게이트가 열린 상태, -는 게이트가 닫힌 상태를 나타낸다.



​	그림에서는, 시간 1에서 인풋 데이트를 열어서 시간 1의 인풋 데이터의 영향력을 가져가고, 시간 6까	지 포겟 게이트를 열어서 시간 1의 영향력을 계속해서 다음 시간으로 가져간다. 그러면서 시간 2에	서부터 시간6까지는 인풋 게이트를 닫아서 해당 시간동안의 인풋 데이터의 영향력을 없앤다. 그리고	시간 1, 2, 3, 5에서는 아웃풋 게이트를 닫고 시간 4, 6에서만 아웃풋 게이트를 연다.

​	이를 통해서 RNN의 출력 결과를 4, 6에서만 방출할 수 있다.

