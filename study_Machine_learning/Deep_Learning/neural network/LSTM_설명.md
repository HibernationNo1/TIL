

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

#### RNN

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

그 이유는, RNN은 이전 step의 값에 의해 현재의 값이 영향을 받기 때문에 이에 따라 값이 발산하는 문제를 방지하기 위해 normalizing을 필요로 하기 때문이다.

값이 발산하는 문제를 방지하기 위해 normalizing 하는 것이 필요하다면 sigmoid와 tanh를 activate function으로 사용할 수 있는데

왜 tanh를 사용했는가? 하면 아래 두 가지 이유가 있다.
$$
sigmoid(x) = \frac{1}{1 + e^{-x}}
$$

$$
tanh(x) = \frac{e^{x} - e^{-x}}{e^{x} + e^{-x}}
$$



> 1. sigmoid									
>    $$
>    sigmoid(x) = \frac{1}{1 + e^{-x}}
>    $$
>    
> 2. 
>
> 2. tanh
>    $$
>    tanh(x) = \frac{e^{x} - e^{-x}}{e^{x} + e^{-x}}
>    $$
>    
>
> ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FsRw8n%2FbtrcAbQ1Jvt%2FGJXPMt1FNkS1WFPdhRuXg0%2Fimg.png) ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcvQoHr%2FbtrcHFixoOL%2FLyV9Iph7bpLQLD4SCSIve0%2Fimg.png)





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
   > \frac{dL}{dw} =\frac{dL}{dz}  \frac{dz}{dw}\\
   > 이\ 때 \ z는\ (wx)를\ 표현한\ 것이며,  \\
   > \frac{dz}{dw}는\ z를\ w에\ 의해\ 미분했다는\ 의미임으로 \\
   > \ \frac{dz}{dw} == x\ 가\ 성립되며 \\
   > \frac{dL}{dw} = x\frac{dL}{dz}  == f'(z)\times x\ 가\ 성립된다.
   > $$
   > 이는 x가 +부호를 가질 때 dL/dw의 부호는 dL/dz에 의해서 결정되며 이는 최적과 수식에서 항상 모든 weight가 같은 방향(+ or -)으로 update된다는 의미이다.
   >
   > 예시: (w_1, w_2, w_3)이라는 3차원의 공간에서 세 가중치가 모두 증가하거나, 모두 감소하거나 하게 되면 지그재그 움직임을 볼 수 있다.
   >
   > 단, x가 -부호를 가질 때는 tanh와 같이 weight가 다양한 방향으로 update될 수 있다.

   

2. 은닉층의 깊이가 깊다면 **vanishing gradient problem**이 발생할 수 있다. 역전파(Backpropagation)를 계산하는 과정에서 activation function의 미분 값을 곱하는 과정이 포함되는데, sigmoid함수의 미분값은 최대가 0.25로 낮기 때문이다.

   > 예시
   >
   > sigmoid함수 미분
   > $$
   > \frac{d}{dx}sigmoid(x) = \frac{d}{dx}(1 + e^{-x})^{-1} \\
   > = (-1)\frac{1}{(1 + e^{-x})^2}(-e^{-x}) \\
   > = \frac{e^{-x}}{(1 + e^{-x})^2} \\ \\
   > = sigmoid(x)(1-sigmoid(x))
   > $$
   > ![](https://taewanmerepo.github.io/2017/09/sigmoid/differential_sigmoid.jpg)
   >
   > tanh 함수 미분
   > $$
   > \frac{d}{dx} tanh(x) = \frac{d}{dx} \frac{e^{x} - e^{-x}}{e^{x} + e^{-x}} \\ = \frac{(e^{x} + e^{-x})(e^{x} + e^{-x}) - (e^{x} - e^{-x})(e^{x} - e^{-x})}{(e^{x} + e^{-x})^2} \\
   > =  \frac{4}{e^{2x} + 2 + e^{-2x}} \\
   >  = (1 - tanh^{2}(x))
   > $$
   >
   >
   > ![](https://ko.d2l.ai/_images/chapter_deep-learning-basics_mlp_13_0.svg)



그리고 back propagation을 수식으로 표현하며 아래와 같다.

손실함수 L과 경사하강법을 사용한다고 가정
$$
h_{raw} = x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h}
$$

$$
h_{t} = tanh(h_{raw}) \ \ = \ \ tanh(x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h})
$$

$$
y_{t} = h_{t}w_{hy} + b_{y}
$$



손실함수 L을 weight 에 대해서 편미분 (chain rule이 적용된다.)
$$
Loss : L
$$

$$
\frac{\partial L}{\partial w} = \frac{\partial L }{\partial y_{t}}  \frac{\partial y_{t}}{\partial w} \\
 =\frac{\partial L }{\partial y_{t}}\frac{\partial y_{t}}{\partial h_{t}}\frac{\partial h_{t}}{\partial w} \\
 =\frac{\partial L }{\partial y_{t}}\frac{\partial y_{t}}{\partial h_{t}}\frac{\partial h_{t}}{\partial h_{raw}}\frac{\partial h_{raw}}{\partial w}
$$
이 때 weight는 w_{xh}와 w_{hh}가 있기 때문에 아래와 같이 표현할 수 있다.b
$$
\frac{\partial L}{\partial w_{xh}} 
=\frac{\partial L }{\partial y_{t}}\frac{\partial y_{t}}{\partial h_{t}}\frac{\partial h_{t}}{\partial h_{raw}}\frac{\partial h_{raw}}{\partial w_{xh}} \\
\frac{\partial L}{\partial w_{hh}}
=\frac{\partial L }{\partial y_{t}}\frac{\partial y_{t}}{\partial h_{t}}\frac{\partial h_{t}}{\partial h_{raw}}\frac{\partial h_{raw}}{\partial w_{hh}}
$$
이를 각각 계산해보자면


$$
1.\ \frac{\partial y_{t}}{\partial h_{t}} = \frac{\partial (h_{t}w_{hy} + b_{y})}{\partial h_{t}} =  w_{hy} \\
2.\ \frac{\partial h_{t}}{\partial h_{raw}} = \frac{\partial ( tanh(h_{raw}))}{\partial h_{raw}} = 1-tanh^{2}(h_{raw})\\
3.\ \frac{\partial h_{raw}}{\partial w_{xh}} = \frac{\partial (x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h})}{\partial w_{xh}} = x_{t}\\
4.\ \frac{\partial h_{raw}}{\partial w_{hh}} =  \frac{\partial (x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h})}{\partial w_{hh}} =  h_{t-1} \\
$$
임으로 최종 식은 아래와 같다
$$
\frac{\partial L}{\partial w_{xh}} 
=\frac{\partial L }{\partial y_{t}}w_{hy}( 1-tanh^{2}(h_{raw})) x_{t} \\
\frac{\partial L}{\partial w_{hh}}
=\frac{\partial L }{\partial y_{t}}w_{hy}( 1-tanh^{2}(h_{raw})) h_{t-1}
$$

> $$
> tanh(x) = \frac{e^{x} - e^{-x}}{e^{x} + e^{-x}} \\
> 1 - tanh(x)^2 = \frac{4}{e^{2x} + 2 + e^{-2x}}
> $$
>
> 

이를 경사하강법에 대입해 보면 아래와 같다.

- w_{xh}^{new}
  $$
  Optimizer: SGD \\
  
  w_{xh}^{new} =  w_{xh} - \alpha\frac{\partial L}{\partial w_{xh}} \\
   = w_{xh}-\alpha(\frac{\partial L }{\partial y_{t}}w_{hy}( 1-tanh^{2}(h_{raw})) h_{t-1})
  $$
  위 식을 풀어서 표현하면 아래와 같다
  $$
  w_{xh}^{new} = w_{xh}-\alpha 
  \left (
  \frac{\partial L }{\partial y_{t}}w_{hy}( 1-tanh^{2}(x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h})) x_{t})
  \right ) \\
   = w_{xh}-\alpha\left (\frac{\partial L }{\partial y_{t}}w_{hy}\frac{4 x_{t}}{e^{2(x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h})} + 2 + e^{-2(x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h})}}\right )
  $$
  
- w_{hh}^{new}

$$
w_{hh}^{new} = w_{hh} - \alpha\frac{\partial L}{\partial w_{hh}} \\
 = w_{hh}-\alpha(\frac{\partial L }{\partial y_{t}}w_{hy}( 1-tanh^{2}(h_{raw})) h_{t-1})
$$

위 식을 풀어서 표현하면 아래와 같다
$$
w_{hh}^{new} = w_{hh}-\alpha 
\left (
\frac{\partial L }{\partial y_{t}}w_{hy}( 1-tanh^{2}(x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h})) h_{t-1})
\right ) \\
 = w_{hh}-\alpha\left (\frac{\partial L }{\partial y_{t}}w_{hy}\frac{4 h_{t-1}}{e^{2(x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h})} + 2 + e^{-2(x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h})}}\right )
$$


이러한 편미분은 시간 단계 t에서 뿐만 아니라 이전 시간 단계들에 대해서도 계산되며, 이는 역전파를 통해 시간을 거슬러 올라가면서 이루어진다.

때문에 RNN 에서의 back propagationd은  Back Propagation Through Time(BPTT)라는 이름으로 불린다.



그럼 왜 RNN이 아니라  LSTM을 사용하는 것일까?



**Long Term Dependency**

RNN의 은닉 상태값을 보면 아래와 같다.
$$
h_{raw}^{t} = x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h}
$$

$$
h_{t} = tanh(h_{raw}^{t}) \ \ = \ \ tanh(x_{t}w_{xh} + h_{t-1}w_{hh} + b_{h})
$$

t가 증가할수록 범위가 (-1 ~ 1)인 tanh가 계속해서 곱해지기 때문에 forward propagation과정에서 뒷 단의 sequence로 갈 수록 정보를 잃어버리게 된다.



![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSsZD1lr3mkJp7ioA758ZQNIqsHz11E5njHHw&usqp=CAU)

시간축 1에서 input data의 영향력은 크게 남아있지만, 새로운 시간축에서 들어온 input data의 영향력이 시간축 1의 input data위에 반복해서 덮어씌워지다 보면

시간축 1의 input data의 영향력은 점점 약해지기 때문이다.



back propagaton과정은 아래의 수식을 통해 설명한다.

 h_{T}를 h\_{t}로 미분해보면 (t시점부터 T시점의 상태값 변화량) 아래와 같다




$$
\frac{d(tanh(x_{t}w_{xh} + h_{T-1}w_{hh} + b_{h}))}{dh_{T-1}} = \\
\frac{dh_{T}}{dh_{T-1}} =  w_{hh}^{T}(1 - tanh^{2}(x_{t}w_{xh} + h_{T-1}w_{hh} + b_{h})))\\

\frac{dh_T}{dh_{t}} = \frac{dh_{T}}{dh_{T-1}}\frac{dh_{T-1}}{dh_{T-2}}...\frac{dh_{t+1}}{dh_{t}} \\
 = w_{hh}^{T}(1 - tanh^{2}(h_{raw}^{T}))*w_{hh}^{T-1}(1 - tanh^{2}(h_{raw}^{T-1}))*w_{hh}^{T-2}(1 - tanh^{2}(h_{raw}^{T-2}))* ... * 
 w_{hh}^{t+1}(1 - tanh^{2}(h_{raw}^{t+1}))*w_{hh}^{t}1 - tanh^{2}(h_{raw}^{t})) \\
  =  \prod_{i = t}^{T}w_{hh}^{i} *  \prod_{i = t}^{T}(1 - tanh^{2}(h_{raw}^{i}))
$$


- 1- tanh^{2}는 항상 절대값 1보다 작은 값이 곱해져서 0으로 수령
- weight또한 그대로 곱해지기 때문에 그 값이 크던 적던 영향력을 그대로 행사하기 때문에, sequence가 길어지면 초기 t의 weight의 영향력은 줄어들게 된다.

이는 즉 t부터 T까지의 sequence가 지났을 경우 은닉 상태값의 변화량이 0에 수렴한다는 의미이다.  







때문에 RNN은 장기 기억력을 가지지 못한다는 단점이 있다.

이를 극복하기 위해 LSTM이 제안되었다.



#### LSTM

우선, 구조부터 비교를 해 보자.

LSTM은 RNN의 히든 state에 cell-state를 추가한 구조이다.

![](http://i.imgur.com/jKodJ1u.png)



cell-state란?

 Cell state는 RNNdml hidden state와 마찬가지로 이전 시점의 cell state를 다음 시점으로 넘겨준다.

차이점은,  gate들과 함께 작용하여 정보를 선택적으로 활용할 수 있도록 하는 것이다. 

정보를 선택적으로 활용하는 이유는, 시퀀스가 길더라도 gradient, 즉 오차를 상대적으로 잘 전파 할 수 있도록 한다.



아래의 구조를 보고 어떻게 정보를 선택적으로 활용할 수 있는지 확인해보자

![](https://www.researchgate.net/publication/329362532/figure/fig5/AS:699592479870977@1543807253596/Structure-of-the-LSTM-cell-and-equations-that-describe-the-gates-of-an-LSTM-cell.jpg) 
$$
\sigma: 활성화\ 함수\ sigmoid
$$

- f_{t}

  과거 정보를 잊기 위한 gate

  h_{t-1}과 입력 x_t를 입력으로 받는다.
  $$
  f_{t} = \sigma(W_{xh}^{f}x_{t} + W_{hh}^{f}h_{t-1} + b_{n}^{f}) \\
  = sigmoid(z_{t}^{f})
  $$
  sigmoid함수를 사용하는 이유는, 이전 상태의 값이 낮은 값(음수값이 클 수록)을 가진 입력이라면 잊기 위함이다.

  이는 필요하지 않는 정보는 제거하고, 중요한 정보만을 cell상태에 반영하기 위함이다.

- i_{t} ⊙ g\_{t}

  현재 정보를 기억하기 위한 gate

  - i_{t}
    $$
    i_{t} = \sigma(W_{xh}^{i}x_{t} + W_{hh}^{i}h_{t-1} + b_{n}^{i}) \\
    = sigmoid(z_{t}^{i})
    $$
    이에 대한 output은 0~1의 값을 가지게 될 것이다.
    
    
    
  - g\_{t}
    $$
    g_{t} = tanh(W_{xh}^{g}x_{t} + W_{hh}^{g}h_{t-1} + b_{n}^{g}) \\
    = tanh(z_{t}^{g})
    $$
    입력 값에 하이퍼볼릭 탄젠트를 적용한다.
    
    이는 RNN의 은닉 상태값을 계산하는 것과 같은 수식이다.
    
    이에 대한 output은 -1~1의 값을 가지게 될 것이다.
    
  - `⊙`: Hadamard product
  
    같은 위치의 element끼리 element by element 곱셈 연산을 수행한 것으로, 같은 크기의 두 행렬의 각 성분을 곱하는 연산이다.
  
  $$
  i_{t} \bigcirc g_{t} = \sigma(W_{xh}^{i}x_{t} + W_{hh}^{i}h_{t-1} + b_{n}^{i})\  
  \bigcirc \ tanh(W_{xh}^{g}x_{t} + W_{hh}^{g}h_{t-1} + b_{n}^{g})
  $$

  이는 현재 정보를 기억하기 위한 gate이다.

  0~1의 값을 가지는 i_{t}와 -1~1의 값을 가지는 g\_{t}사이에 Hadamard product를 취하면 아래의 두 경우가 있다.

  - g\_{t} > 0 일 경우

    i_{t} ⊙ g\_{t} 는 g\_{t}보다 더 낮은 값을 가지게 된다.

  - g\_{t} < 0 일 경우

    i_{t} ⊙ g\_{t} 는 g\_{t}보다 더 높은 값을 가지게 된다.
  
  이는 결과적으로 i_{t}가 g\_{t}를 범위를 조정하는 역할을 한다. 즉, 은닉 상태값의 절대값을 0에 가깝게 조정한다.
  
  즉,  g\_{t}를 얼마나 반영될지를 결정하는 스케일링 팩터로 작동한다.
  
- o_{t}
  $$
  o_{t} = \sigma(W_{xh}^{o}x_{t} + W_{hh}^{o}h_{t-1} + b_{n}^{o}) \\
  = sigmoid(z_{t}^{o})
  $$

그리고  C_t는 아래와 같다.
$$
C_{t} = f_{t} \bigcirc C_{t-1} + i_{t} \bigcirc g_{t}
$$

- f_{t} ⊙ C\_{t-1}

  이는 결과적으로 f_{t}가 C\_{t-1}를 범위를 조정하는 역할을 한다. 즉, 이전 시점의 cell정보값을 0에 가깝게 조정한다. 

  이전 시점의 셀 상태값 C\_{t-1}이 얼마나 반영될지를 결정하는 스케일링 팩터로 작동한다.

- i\_{t} ⊙ g\_{t} + f\_{t} ⊙ C\_{t-1}

  이는 '과거의 정보 중 유지할 정보' + '이전 cell상태중 유지할 정보'이며, 이 계산을 통해 현재 시점의 cell state를 update한다.

  이를 통해 LSTM은 중요한 정보를 유지하면서도 불필요한 정보는 잊어버릴 수 있다.



그리고 h_{t}는 아래와 같다.
$$
h_{t} = tanh(C_{t}) \bigcirc o_{t}
$$

- tanh(C_{t})

  이는 셀 값이 정규화되어, 은닉 상태에 공급될 때 더 안정적인 형태를 가지게 된다.

- tanh(C_{t}) ⊙ o\_{t}

  이는 현재 셀 상태 중 어떤 정보가 최종 은닉 상태로 출력될지를 결정





그리고 LSTM에서 사용하는 loss를 L2이라고 가정해보자.
$$
L = Loss
$$

$$
L(x) =\sum_{i=1}^{n}(y_{i} - \hat{y_{i}})^2
$$

- y: 실제 정답 닶
- \hat{y}: 예측 값

그렇다면 L(y_{t})는 아래와 같다.
$$
L(h_{t}) =  \sum_{i=1}^{t}(y_{i} - h_{i})^2
$$



이제, backpropagation에 대해서 계산해보자.

우리가 update하고자 하는 weight는 W_{xh}, W\_{hh}이다.

이를 위해서는 4개의 편미분값을 구해야 한다.


$$
\frac{dL}{dg_{t}} \ \ \frac{dL}{df_{t}}  \ \ \frac{dL}{di_{t}} \ \ \frac{dL}{do_{t}}
$$



$$
df_{t},\ di_{t},\ dg_{t},\ do_{t}\
$$

- dL/do_{t}
  $$
  \frac{dL}{do_{t}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{do_{t}} \\
  = \frac{dL}{dh_{t}}tanh(C_{t})
  $$

  >$$
  >o_{t} = \sigma(W_{xh}^{o}x_{t} + W_{hh}^{o}h_{t-1} + b_{n}^{o}) \\
  >= sigmoid(z_{t}^{o})
  >$$

  - dL/dw_{xh}^{o}
    $$
    \frac{dL}{dw_{xh}^{o}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{do_{t}}\frac{do_{t}}{dw_{xh}^{o}} \\
    =  \frac{dL}{dh_{t}}tanh(C_{t}) * sigmoid(z_{t}^{o}) * (1-sigmoid(z_{t}^{o})) * x_{t}
    $$

  - dL/dw_{hh}^{o}
    $$
    \frac{dL}{dw_{hh}^{o}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{do_{t}}\frac{do_{t}}{dw_{hh}^{o}} \\
    =  \frac{dL}{dh_{t}}tanh(C_{t}) * sigmoid(z_{t}^{o}) * (1-sigmoid(z_{t}^{o})) * h_{t-1}
    $$

  - dL/db_{n}^{o}
    $$
    \frac{dL}{db_{n}^{o}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{do_{t}}\frac{do_{t}}{db_{n}^{o}} \\
    =  \frac{dL}{dh_{t}}tanh(C_{t}) * sigmoid(z_{t}^{o}) * (1-sigmoid(z_{t}^{o}))
    $$
    

- dL/dC_{t}
  $$
  \frac{dL}{dC_{t}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}} \\
  = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t}))
  $$

  - dL/dg_{t}
    $$
    \frac{dL}{dg_{t}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}}\frac{dC_{t}}{dg_{t}} \\
    = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t})) * i_{t}
    $$

    > $$
    > g_{t} = tanh(W_{xh}^{g}x_{t} + W_{hh}^{g}h_{t-1} + b_{n}^{g}) \\
    > = tanh(z_{t}^{g})
    > $$

    

    - dL/dw_{xh}^{g}
      $$
      \frac{dL}{dw_{xh}^{g}}  = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}}\frac{dC_{t}}{dg_{t}}\frac{dg_{t}}{dw_{xh}^{g}} \\
      = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t})) * i_{t}* (1-tanh^{2}(z_{t}^{g})) * x_{t}
      $$

    - dL/dw_{hh}^{g}
      $$
      \frac{dL}{dw_{hh}^{g}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}}\frac{dC_{t}}{dg_{t}}\frac{dg_{t}}{dw_{hh}^{g}}  \\
      = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t})) * i_{t}* (1-tanh^{2}(z_{t}^{g}))* h_{t-1}
      $$

    - dL/db_{n}^{g}
      $$
      \frac{dL}{db_{n}^{g}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}}\frac{dC_{t}}{dg_{t}}\frac{dg_{t}}{db_{n}^{g}}  \\
      = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t})) * i_{t}* (1-tanh^{2}(z_{t}^{g}))
      $$
      

  - dL/di_{t}
    $$
    \frac{dL}{di_{t}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}}\frac{dC_{t}}{di_{t}} \\
    = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t})) * g_{t}
    $$

    > $$
    > i_{t} = \sigma(W_{xh}^{i}x_{t} + W_{hh}^{i}h_{t-1} + b_{n}^{i}) \\
    > = sigmoid(z_{t}^{i})
    > $$

    - dL/dw_{xh}^{i}
      $$
      \frac{dL}{dw_{xh}^{i}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}}\frac{dC_{t}}{di_{t}}\frac{di_{t}}{dw_{xh}^{i}} \\
      = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t})) * g_{t} * sigmoid(z_{t}^{i}) * (1-sigmoid(z_{t}^{i})) * x_{t}
      $$

    - dL/dw_{hh}^{i}
      $$
      \frac{dL}{dw_{hh}^{i}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}}\frac{dC_{t}}{di_{t}}\frac{di_{t}}{dw_{hh}^{i}} \\
      = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t})) * g_{t} * sigmoid(z_{t}^{i}) * (1-sigmoid(z_{t}^{i})) * h_{t-1}
      $$

    - dL/db_{n}^{i}
      $$
      \frac{dL}{db_{n}^{i}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}}\frac{dC_{t}}{di_{t}}\frac{di_{t}}{db_{n}^{i}} \\
      = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t})) * g_{t} * sigmoid(z_{t}^{i}) * (1-sigmoid(z_{t}^{i}))
      $$
      

  - dL/df_{t}
    $$
    \frac{dL}{df_{t}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}}\frac{dC_{t}}{df_{t}} \\
    = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t})) * C_{t-1}
    $$
    

    >$$
    >f_{t} = \sigma(W_{xh}^{f}x_{t} + W_{hh}^{f}h_{t-1} + b_{n}^{f}) \\
    >= sigmoid(z_{t}^{f})
    >$$

    - dL/dw_{xh}^{f}
      $$
      \frac{dL}{dw_{xh}^{f}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}}\frac{dC_{t}}{df_{t}}\frac{df_{t}}{dw_{xh}^{f}} \\
      = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t})) * C_{t-1}* sigmoid(z_{t}^{f}) * (1-sigmoid(z_{t}^{f})) * x_{t}
      $$

    - dL/dw_{hh}^{f}
      $$
      \frac{dL}{dw_{hh}^{f}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}}\frac{dC_{t}}{df_{t}}\frac{df_{t}}{dw_{hh}^{f}} \\
      = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t})) * C_{t-1}* sigmoid(z_{t}^{f}) * (1-sigmoid(z_{t}^{f})) * h_{t-1}
      $$

    - dL/db_{n}^{f}
      $$
      \frac{dL}{db_{n}^{f}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}}\frac{dC_{t}}{df_{t}}\frac{df_{t}}{db_{n}^{f}} \\
      = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t})) * C_{t-1}* sigmoid(z_{t}^{f}) * (1-sigmoid(z_{t}^{f})) * x_{t}
      $$
      

  - dL/dC_{t-1}
    $$
    \frac{dL}{di_{f}} = \frac{dL}{dh_{t}}\frac{dh_{t}}{dC_{t}}\frac{dC_{t}}{dC_{t-1}} \\
    = \frac{dL}{dh_{t}}* o_{t}* (1-tanh^{2}(C_{t})) * f_{t}
    $$

  

  

  

최적화 실행

Adam사용

1. momentum 계산
   $$
   m_{t} = \beta_{1} * m_{t-1} + (1 - \beta_{1}) \frac{dL}{dw}
   $$

   - \beta_{1} : momentum의 계수에 대한 감쇄율. momentum의 지수이동평균(0.9에 가까운 값)

     이 값은 이전 m_{t}와 loss의 변화량 중 어느것의 영향을 더 중요시 할지 결정한다.

     이동하는 열차의 속도에 변화를 줄 때 관성의 힘과 가하는 운동에너지의 비율을 결정한다고 이해하면 된다. 

     최적화 반향을 안정화하는데 사용된다.

2. scale 계산
   $$
   v_{t} = \beta_{2} * v_{t-1} + (1-\beta_{2})\left(\frac{dL}{dw} \right)^{2}
   $$

   - \beta_{2} : scale계수에 대한 감쇄율. RMSProp의 지수이동평균(0.999에 가까운 값)

     이는 loss의 변화량이 클 때 그 영향력을 줄이는데 사용된다. 갑자기 큰 변화가 있을 경우 loss의 발산을 막는데 사용된다.

3. \hat{m\_{t}}, \hat{v\_{t}} 계산
   $$
   \hat{m_{t}} = \frac{m_{t}}{1-\beta_{1}^{t}} \\
   \hat{v_{t}} = \frac{v_{t}}{1-\beta_{2}^{t}}
   $$

   - `\beta_{1}^{t}`, `\beta_{2}^{t}`: beta_{1}과 beta\_{2}를 각각 iteration만큼 거듭제곱한 값

     이를 통해 초기에 m_{t}와 v\_{t}가 정보가 없어 0에 가까운 값일 때 그 영향력을 크게 증대시켜주며, 시간 t가 증가할수록 그 영향력을 있는 그대로 행사할 수 있게 대 준다. 

4. 최종 optimizer 수식
   $$
   x_{t} = x_{t-1} - \frac{\eta * \hat{m_{t}}}{\sqrt{\hat{v_{t}} + \epsilon}}
   $$

   - \eta: learning rate
   - \epsilon: 분모가 0이 되는것을 방지하기 위한 작은 상수

   이를 풀어서 쓰자면
   $$
   x_{t} = x_{t-1} - 
   \frac{\eta * \frac{\beta_{1} * m_{t-1} + (1 - \beta_{1}) \frac{dL}{dw}}{1-\beta_{1}^{t}}}
   {\sqrt{\frac{\beta_{2} * v_{t-1} + (1-\beta_{2})\left(\frac{dL}{dw} \right)^{2}}{1-\beta_{2}^{t}} + \epsilon}}
   $$
   



LSTM은 왜 RNN보다 장기기억력이 좋은가?







반면, LSTM의 은식 상태값을 보면 아래와 같다.
$$
C_{t} = f_{t} \bigcirc C_{t-1} + i_{t} \bigcirc g_{t}
$$
C_{T}를 C\_{t}로 미분해보면 (t시점부터 T시점의 상태값 변화량) 아래와 같다.
$$
\frac{dC_{T}}{dC_{t}} = \frac{dC_T}{dC_{T-1}} \frac{dC_{T-1}}{dC_{T-2}} ...  \frac{dC_{t+1}}{dC_{t}} \\
= f_{T} * f_{T-1} * f_{T-2} * ... * f_{t+1} * f_{t} \\
= \prod_{i = t}^{T}f_{i}
$$
여기서 f_{t}는 아래와 같다.
$$
f_{t} = \sigma(W_{xh}^{f}x_{t} + W_{hh}^{f}h_{t-1} + b_{n}^{f})
$$
시간이 지나며 weight의 최적화가 진행 되더라도 sigmoid함수에 의해 (0~1)의 값을 가지게 되는데 

- 값의 발산이 발생하지 않게 되며 

- t의 시간대에서 f가 중요하다고 판단되어 1에 가까운 값을 가지게 되더라도 추 후 t+2의 시간대에서는 중요하지 않다고 판단된다면 0에 가까운 값을 가지게 된다.

  T와 t사이에 중요하지 않다고 판단되는 시간이 한 번이라도 존재한다면,  t시간대의 정보를 잃게 되기 때문에 f_{t}를 망각 게이트라고 하게 되는 것이다.

- 만일 t의 시간대의 정보가 중요하다고 판단되어 장기적으로 가져가야하는 정보라면, 각각 시점 t부터 T까지의 모든 f의 weight는 f의 값이 1에 가깝도록 학습하게 될 것이다.





또한 C_{T}를 C\_{t}로 미분해보면 (t시점부터 T시점의 상태값 변화량) 아래와 같다.

