

- https://jordano-jackson.tistory.com/63

  

- https://ratsgo.github.io/natural%20language%20processing/2017/03/09/rnnlstm/

- https://www.youtube.com/watch?v=573EZkzfnZ0



# LSTM

LSTM은 순서에 따라 서로 연관된 정보를 가진 데이터(시계열 데이터)를 다루기 위해 고안된 신경망으로, 가장 기본적인 시퀀스 모델인 RNN의 단점을 해결하고자 하여 탄생했다.

인공 신경망의 학습은 오차를 최소화하는 가중치를 찾는 목적으로 순전파와 역전파를 반복한다. 때문에 우리는 

1. 순전파에 의해 예측값을 얻는다.
2. 예측값과 정답값 간에 오차를 계산한다. (loss function)
3. 역전파를 통해 가중치를 업데이트한다. (최적화)

위의 동작을 반복하는데, LSTM의 순전파와 역전파를 이해하기 위해서는 RNN의 동작을 이해할 필요가 있다.

그럼, RNN이란 무엇이냐

기본적인 ANN구조에서 이전 시간(t-1)의 은닉층의 출력값을 다음 시간(t)에 은닉층의 입력값으로 다시 집어넣는 경로가 추가된 형태이다. 

RNN은 간단히 표현하자면 아래 1번과 같은데, 이를 시간의 흐름 순으로 unfold하게 표현하면 2번과 같다.

1. ![](https://wikidocs.net/images/page/22886/rnn_image4_ver2.PNG)
2. ![](https://wikidocs.net/images/page/22886/rnn_image2_ver3.PNG)





이 때 forward propagation을 수식으로 표현하며 아래와 같다.

![](http://i.imgur.com/TIdBDTJ.png)

1. h_raw계산
   $$
   h_{raw} = x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h}
   $$

2. h_t 계산
   $$
   h_{t} = tanh(h_{raw}) \ \ = \ \ tanh(x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h})
   $$

3. y_t
   $$
   y_{t} = h_{t}w_{hy} + b_{y}
   $$

이때 h_t를 계산하는데 하이퍼볼릭 탄젠트를 사용한다. 

그 이유는, RNN은 이전 step의 값에 의해 현재의 값이 영향을 받기 때문에 이에 따라 값이 발산하는 문제를 방지하기 위해서 이다.

값이 발산하는 문제를 방지하기 위해 normalizing 하는 것이 필요하다면 sigmoid와 tanh를 activate function으로 사용할 수 있는데

왜 tanh를 사용했는가? 하면 아래 두 가지 이유가 있다.

> 1. sigmoid
>    $$
>    s(x) = \frac{1}{1 + e^{-x}}
>    $$
>    
>
> ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FsRw8n%2FbtrcAbQ1Jvt%2FGJXPMt1FNkS1WFPdhRuXg0%2Fimg.png)![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcvQoHr%2FbtrcHFixoOL%2FLyV9Iph7bpLQLD4SCSIve0%2Fimg.png)





1. 효율적인 학습이 가능하다.

   그래프를 보면 sigmoid는 (0,1)의 범위를 가지고 있고, tanh는 (-1,1)의 범위를 가진다. 

   양의 값만을 가지는 sigmoid는 입력 x가 양의 값을 가지는 경우

   역전파를 할 때 한 노드에서 모든 파라미터의 미분 값이 모두 같은 부호를 같게 되는데, 같은 방향으로 update되는 과정은 학습을 지그재그 형태로 만드는 원인을 낳는다.(효율x)

   > 수식
   >
   > weight(w)와 입력값(x)가 있다고 할 때 activate function에 의한 node의 출력값 L은 아래와 같다.
   > $$
   > L = f(wx)
   > $$
   > 이는 미분을 했을 때 아래와 같다.
   > $$
   > \frac{dL}{dw} = \frac{dz}{dw}\frac{dL}{dz} \\
   > 이\ 때 \ z는\ chain\ rule에\ 의해\ (wx)를\ 표현한\ 것이며,  \\
   > \frac{dz}{dw}는\ z를\ w에\ 의해\ 미분했다는\ 의미임으로 \\
   > \ \frac{dz}{dw} == x\ 가\ 성립되며 \\
   > \frac{dL}{dw} = x\frac{dL}{dz}  == f'(z)\times x\ 가\ 성립된다.
   > $$
   > 이는 x가 +부호를 가질 때 dL/dw의 부호는 dL/dz에 의해서 결정되며 이는 최적과 수식에서 항상 모든 weight가 같은 방향(+ or -)으로 update된다는 의미히다. 

   

2. 은닉층의 깊이가 깊다면 **vanishing gradient problem**이 발생할 수 있다. 역전파(Backpropagation)를 계산하는 과정에서 activation function의 미분 값을 곱하는 과정이 포함되는데, sigmoid함수의 미분값은 최대가 0.25로 낮기 때문이다.

   > 예시
   >
   > sigmoid함수 미분
   > $$
   > \frac{d}{dx}sigmoid(x) = \frac{d}{dx}(1 + e^{-1})^{-1} \\
   >  = (-1)\frac{1}{(1 + e^{-x})^2}(-e^{-x}) \\
   >   = \frac{e^{-x}}{(1 + e^{-x})^2}
   > $$
   > ![](https://taewanmerepo.github.io/2017/09/sigmoid/differential_sigmoid.jpg)

