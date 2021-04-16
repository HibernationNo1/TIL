# Logistic Regression

## 개념 설명

**Logistic Regression**: 데이터가 0(No Pass)과 1(Pass)중 어디에 속할지를 연속적인 확률로 예측하는 회귀 알고리즘 (Binary Classification 문제를 해결하기 위한 Regression)

과정: 입력 data에 의해 Initial Decision Boundary가 정해지고, 계속해서 data를 통해 training을 하며 최종 Decision Boundary을 결정하는 것이 Logistic Regression의 학습 과정이다.

> Linear Regression에서는 Binary Classification 문제를 해결하기엔 문제가 있다. (out layer로 인해 큰 Loss가 발생해서 Decision Boundary가 적절한 위치에 있지 못하게 되기 때문) 
>
> 이러한 문제를 해결하기 위해 사용하는 activation function을 Sigmoid function이라고 하며, Sigmoid function 함수를 사용해서 classification 문제를 해결하는 regression을 Logistic Refression이라고 한다.



#### Sigmoid Function

$$
\sigma(x) = \frac{1}{1+e^{-x}}
$$

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbDk83K%2FbtqAZO51QIQ%2FIZrbpIaB8qwnnBFtX7M7IK%2Fimg.png)

- x가 증가하면 1에 가까워지고, x가 줄어들면 0에 가까워진다. 즉, 0에서 1사이의 값을 출력한다.

- 실수의 작은 범위에서(위 그림 기준 -5 ~ +5) 유의미한 변화가 일어난다. 즉, out layer에 의한 큰 Loss가 발생하지 않아 Decision Boundary가 이동하지 않는다.



#### Logistic Function

- Affine Function(예시)
  $$
  z = \theta_1  x + \theta_0
  $$

- Sigmoid Function
  $$
  \sigma(x) = \frac{1}{1+e^{-x}}
  $$

- Logistic Function
  $$
  a = \sigma(z)\\
  \widehat{y} = \frac{1}{1 + \exp^{-(\theta_1 x + \theta_0)}}
  $$

Affine Function을 Sigmoid Function에 대입한 것이 바로 Logistic Function임을 알 수 있다.

> Logistic Function으로 인해 Linear Function은 비선형 function이 된다.



이제 Affine Function과 Logistic Function 으로 인해 Artificial Neural이 완성될 수 있다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/35.jpg?raw=true)



## 식 유도 과정

- updata 과정

  **Affine Function(Logit)	 ->	  Activation Function(Logistic Function)	 ->	Loss Function(Binary Cross Entropy Loss)	 - > 	Gradient Descent Mothod**

> 여기서 Loss Function에서 MES대신 CEL(Cross Entropy Loss)을 사용하는 이유 : Logistic Function에 MES를 사용하게 되면 convex하지 않은 Loss가 된다. 그렇기 때문에 convexity를 보장하기 위해 CEL을 사용하는 것이다.

Affine Function
$$
z = \overrightarrow{\theta^*} \overrightarrow{x}
$$
Logistic Function
$$
a = \sigma(z) = \widehat{y}
$$
Binary Cross Entropy Loss
$$
J = \frac{1}{n}\sum_{i = 1}^{n}BCE^{(i)}
$$

> BCE = Binary Cross Entropy Loss



#### Sigmoid Function

Sigmoid Function은 Affine Function의 weighted sum을 pass(확률)로 바꿔주는 역할을 한다.
$$
\sigma(x) = \frac{1}{1+e^{-x}}
$$

> [Sigmoid Function](https://github.com/HibernationNo1/TIL/blob/master/study_Machine_learning/Deep_Learning/Regression/Logit.md)



#### Binary Cross Entropy

##### Binary Entropy

- 기대값(Expected value)

  기대값이란 어떤 사건이 일어날 여러 경우의 수가 있을 때 가장 일어날거라는 기대가 큰 값이다.

  이는 수식으로 아래와 같이 표현할 수 있다.
  $$
  \mathbb{E} = \sum_{i= 1}^{k}p_ix_i
  \\x : 사건 \ \ \ \ \ \ p:사건이\ 일어날\ 확률
  $$

  > 예) 주사위
  > $$
  > x = \{1,2 , 3, 4, 5, 6 \} \ \ \ \ \ p_i  = \frac{1}{6} \\ 
  > \mathbb{E} = \sum_{i= 1}^{6}\frac{x_i}{6} = 3.5
  > $$

  이 때 x에는 function을 대입할 수 있다. (Expected Value of a Function)
  $$
  \mathbb{E}[f(X)] = \sum_{i= 1}^{k}p_i f(x_i)
  $$

  > 예 ) 2차 함수
  > $$
  > x = \{1,2 , 3, 4, 5, 6 \} \ \ \ \ \ f(x_i) = x^2 \ \ \ \ \ p_i = 6\\
  > \mathbb{E} = \sum_{i= 1}^{6}\frac{x_i^2}{6} = 15.17
  > $$



- 정보의 값어치

  어떠한 사건이 발생했을 때, 그 확률이 낮을수록 해당 사건이 발생할거라는 정보는 더욱 큰 값어치를 가진다고 할 수 있다.  이는 아래처럼 표현될 수 있다.
  $$
  P(A) : 사건\ A가\ 일어날\ 확률 \ \ \ \ \ \ I(A): 사건\ A가\ 일어났을때\ 사건의\ 값어치\\
  P(A) = \frac{1}{I(A)}
  $$
  그리고 위 식을 아래처럼 표현한다면 System이 Linear하게 증가할수록 Information도 Linear하게 증가함을 표현할 수 있다.
  $$
  I(A) = log \left( \frac{1}{P(A)} \right)
  $$

  > System이 증가한다는 것은 특정 경우의 수를 가진 행동을 독립적으로 다시 또 수행하는 경우를 의미함( ex. 동전 던지기를 1번만 한다 ->  2번을 한다 : System의 증가)
  > $$
  > P(A) = \frac{1}{2},  \ \ \ I(A) = log \frac{1}{2}\\
  > P(A) = (\frac{1}{2})^2,  \ \ \ I(A) = 2log \frac{1}{2}
  > $$

  이를 통해 우리는 같은 경우의 수를 가진 작업을 k번 수행하는 System 안에서 i번째에 어떤 사건이 일어났을 경우의 값을 아래처럼 표현할 수 있다.
  $$
  I(x_i) = -log(P(x_i))
  $$



**Binary Entropy 유도**

두 가지 경우의 수를 가지고 있는 사건에 대해서 Information을 수학적으로 표현해보자.
$$
사건의\ 종류는\ X = \{x_1, x_2\} 이고, \ \ 사건이\ 일어났을때의\ 값은\ I(x_i) = -log(P(x_i)) \ \ 이며 \\ 
y : 사건\ x_1이\ 일어날\ 확률  = P(x_1) = p\ \\ \widehat{y} :사건\ x_2가\ 일어날\ 확률  = P(x_2) = 1 - p\\ 이므로
\\ I(x_1) = -log(p)\ 이고, \ \ \ \ \ I(x_2) = -log(1-p) \\ 이다.
$$
그리고 이를 Expected Value 수식에 대입하고 이를 H(X)라고 하자.
$$
\\ \mathbb{E}(I[X]) =H(X)= \sum_{i= 1}^{2}P(x_i)I(x_i) \\
 = P(x_1)*I(x_1) +  P(x_2)*I(x_2) \\ 즉\\
H(X) = -[p*log(p) + (1 - p)log(1 - p)]
$$
이는 우리가 예측을 하는 정보의 사건에 대한 Binary Entropy라고 할 수 있다.

>  Entropy가 낮을수록 불확실성이 낮음으로, 예측을 더 잘 한다고 이해하면 된다.(열역학처럼) 
>
> 그리고 위 Binary Entropy 식은 pass 확률이 0에 가깝거나 1에 가까울 수록 그 값이 낮음을 알 수 있다.

$$
p = 0.5 \ \ \ \ \ 1 - p = 0.5 \ \ \ =>\ \ H(X)  = 0.69\\
p = 0.2 \ \ \ \ \ 1 - p = 0.8 \ \ \ =>\ \ H(X)  = 0.5\\
p = 0.8 \ \ \ \ \ 1 - p = 0.2 \ \ \ =>\ \ H(X)  = 0.5\\
p = 0.05 \ \ \ \ \ 1 - p = 0.95 \ \ \ =>\ \ H(X)  = 0.2\\
p = 0.95 \ \ \ \ \ 1 - p = 0.05 \ \ \ =>\ \ H(X)  = 0.2\\
$$

![](https://www.researchgate.net/profile/Erik-Hostens/publication/28360346/figure/fig3/AS:669446519656457@1536619896995/The-binary-entropy-function-hp-1-p.png)



이는 곧 어떤 data가 Logistic Regression Model에 input되었을 때, Model의 Accuracy가 높을수록 해당 data의 pass 확률이 0.5에 가까워도 잘 분류를 한다는 것이다.

> 그렇기 때문에 pass 확률이 0.5에 가까운 data를 잘 분류하는 알고리즘을 연구하는 것이 중요하다. 
>
> 그리고 학습이 끝났다고 해도 pass 확률이 0.5에 가까운(Entropy가 높게 Classification 된) data를 따로 추려내서 추가적인 러닝을 통해 확률을 더 높이는 방법도 있다.



##### Binary Cross Entropy

###### Cross Entropy

x_data에 대해서 Probablity Distribution 이 두 개가 있다고 한다면
$$
X = \{x_1,x_2, ... , x_k \} \left\{ \begin{matrix}
P(x_i) \rightarrow  I_p(x) = -log(P(x)) \rightarrow  H_P(X) = -\sum_{x \in X} P(x)log(P(x))
\\
\\ 
Q(x_i)\rightarrow  I_Q(x) = -log(Q(x)) \rightarrow H_Q(X) = -\sum_{x \in X} Q(x)log(Q(x))
\end{matrix}\right.
$$
이고 두 P, Q에 대한 Cross Entropy는 아래와 같다.
$$
H(P, Q) = - \sum_{x \in X}P(x)log(Q(x))
$$


###### KL Divergence

두 Information Entropy의 상대적 비교값을 의미한다. (거리를 의미하는게 아니라 '차이'를 의미함)

여기서 말하는 Information Entropy는**확률 분포**를 의미하기 때문에 **'두 확률 분포의 차이'** 라고 이해해도 된다. 

단, '차이'는 두 Information Entropy값을 나눔으로써 구할 수 있으며 그 기준은 두 가지가 될 수 있다.

1. a라는 point에서 확률분포 P로부터 확률분포 Q와의 차이(different)
2. a라는 point에서 확률분포 Q로부터 확률분포 P와의 차이(different)

그리고 같은 point에서 두 기준의 차이는 다른 값을 가진다. 이것이 바로 '거리'와는 다른 점이다.( 거리는 어떤 지점이 기준이든 그 값은 똑같다. )



KL Divergence을 유도하기 위해서, 확률분포가 아닌 random variable distribution에서의 한 data point의 value를 나눈 식을 표현해보자. (해당 식을 X라고 칭하겠다.)
$$
P에\ 대한\ Q의\ 차이 : \frac{Q(x_i)}{p(x_i)}
$$
이미지 42



X를 하나의 Probability라고 가정하고 Information 수식에 대입하면 아래와 같다
$$
I(A) = log \left( \frac{1}{P(A)} \right)\\
\frac{Q(x_i)}{p(x_i)} \overset{Information}{\rightarrow} -log \left( \frac{Q(x_i)}{p(x_i)} \right)
$$

> I(A)와 X의 차이점: I(A)의 Probability는 0~1이지만, X의 범위는 실수 전체임

그리고 위 식을 Expected Value of a Function 에 대입해보자
$$
\mathbb{E}[f(X)] = \sum_{i= 1}^{k}p_i f(x_i)\\
-log \left( \frac{Q(x_i)}{p(x_i)} \right)\overset{Expectation}{\rightarrow}
- \sum_{i= 1}^{k}P(x_i) log \left( \frac{Q(x_i)}{p(x_i)} \right)
$$
이렇게 만들어진 식이 바로 **P에 대한 KL Divergence**다.
$$
D_{KL}(P||Q) = -\sum_{x\in X }P_X(x) *log \left( \frac{Q_X(x)}{p_X(x)} \right)
$$

> P에서부터 Q를 측정한 KL Divergence

이미지 43

> 굵은 line의 distribution이 P, 보라~빨강의 각각 distribution이 여러개의 Q



P에 대한 KL Divergence를 전개해보면
$$
D_{KL}(P||Q) = -\sum_{x\in X }P_X(x) *log \left( \frac{Q_X(x)}{p_X(x)} \right) \\ = -\sum_{x\in X }P(x)log(Q(x)) - \sum_{x\in X }P(x)log\left (\frac{1}{P(x)}\right) \\
= H(P, Q) - H(P)
$$
이는 **P, Q에 대한 Cross Entropy - P에 대한 Self Entropy**로 나타남을 알 수 있다.

이 때 P를 정답 label(정답 값)이라고 하면 P가 뽑은 distribution은 1 또는 0의 값만 담고있기 때문에 P에 대한 Self Entropy는 0이 된다.

즉, Classification Learning에서 Cross Entropy는 KL Divergence의 대체품이 되는 것이다.



위에서 표현한 P, Q에 대한 Cross Entropy의 data colunm을 두 개만 담고, P는 정답 label이라고 한다면,  Binary Cross Entropy는 아래와 같이 표현될 수 있다.
$$
X = \{x_1, x_2\} \left\{\begin{matrix}
Y(x_1) = y \ \ \ \ \ Y(x_2) = 1 - y \ \ \ where\ y \in \{0, 1\}
\\ 
\\
\widehat{Y}(x_1) = \widehat{y}\ \ \ \ \ \widehat{Y}(x_2) = 1 - \widehat{y}
\end{matrix}\right.
$$

$$
H(Y, \widehat{Y}) = -\left[ Y(x_1)*log(\widehat{Y_1}) + \widehat{Y}(x_2)*log(\widehat{Y}_2)\right] \\
=- \left[ y log(\widehat{y}) + (1 - y)log(1 - \widehat{y})\right]
$$

즉, Model은 Loss Function으로 Binary Cross Entropy를 사용하게 되고, 학습이 진행될수록 Y, Y_hat에 대한 Cross Entropy는 작아지게 되는 것이다.

이미지 44



+ Self Entropy이 필요한 이유

  predict에 대한 Self Entropy값이 크다면, data set에서 Classification 이 잘 안되는 data들이 많다는 것을 의미한다. 
  $$
  H(\widehat{Y}) =- \left[\widehat{y} log(\widehat{y}) + (1 -\widehat{y})log(1 - \widehat{y})\right]
  $$
  그렇기 때문에 해당 데이터들을 따로 추려낸 후, 여러 data와 합치며 새로운 data set을 만들어 learning함으로써 더욱 좋은 Classification 성능을 기대할 수 있을 것이다.

  



###### Requirement

정답에 알맞은 예측을 하면 Loss를 줄이고, 정답에 알맞지 않은 예측을 하면 Loss를 높히는 방식으로 Logistic Regression 모델의 학습에 강화학습(보상)이 적용됨을 확인해보자.
$$
case1 :  \ \ \ label = 0:  \ \ \widehat{y} \approx  1 \rightarrow  Loss\ 증가,\ \ \ \ \widehat{y} \approx  0 \rightarrow  Loss\ 감소\\
case2 :  \ \ \ label = 1:  \ \ \widehat{y} \approx  0 \rightarrow  Loss\ 증가,\ \ \ \ \widehat{y} \approx  1 \rightarrow  Loss\ 감소\\
$$
이는 log함수로 설명될 수 있다.
$$
case 1: -log_e(1-\widehat{y}) \\
case 2: -log_e(\widehat{y}) \\
$$
![](https://github.com/HibernationNo1/TIL/blob/master/image/36.jpg?raw=true)

이는 아래 식으로 표현될 수 있다.



$$
 \left\{\begin{matrix}
-log_e(\widehat{y}), \ \ \ \ where \ y = 1
\\ 
-log_e(1-\widehat{y}), \ \ \ \ where \ y = 0
\end{matrix}\right.\\
$$



그리고 Binary Cross Entropy 식을 보면 Requirement이 적용됨을 알 수가 있다.
$$
Loss= -[y log(\widehat{y}) + (1 - y)log(1 - \widehat{y})]
$$



## propagation

- forward propagation

  Affine Function	 ->	  Sigmoid Function	 ->	Binary Cross Entropy Loss	

  

- backward propagation

  d(Binary Cross Entropy Loss) * d(Sigmoid Function)  * d(Affine Function)

  -> 	Gradient Descent Mothod



#### partial derivative

##### Sigmoid Function

$$
\frac{\part\sigma(z)}{\sigma z} = \frac{\part}{\part z}[\frac{1}{1+\exp^{(-z)}}] = -(1 + \exp^{(-z)})^{-2} * (-\exp^{(-z)})\\
 = \frac{\exp^{(-z)}}{(1+\exp^{(-z)})^2} = \frac{1}{1+\exp^{(-z)}} * \frac{1 + \exp^{(-z)} -1}{1 + \exp^{(-z)}}\\
 = \frac{1}{1+\exp^{(-z)}} *(1 - \frac{1}{1+\exp^{(-z)}}) \\
 = \sigma(z)*(1-\sigma(z))
$$

즉, 
$$
\frac{\part\sigma(z)}{\sigma z} = \sigma(z)*(1-\sigma(z))
$$
![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbDk83K%2FbtqAZO51QIQ%2FIZrbpIaB8qwnnBFtX7M7IK%2Fimg.png)

여기서 알 수 있는것은, data에 의한 분류가 확실할 때는(|sigmoid| 가 클 때) updata가 잘 이루어지지 않고 data에 의한 분류가 조금씩 불확실할 때는(|sigmoid| 가 0에 가까울 때) updata가 잘 이루어진다는 것이다.

또한 sigmoid 함수의 값은 0~1까지의 값을 가지고 있는것을 알 수 있다. 이는 0.5에 대해서 대칭되는 값이며 동시에 다음 neural의 input data가 되기 때문에 0에 대칭되는 값에 비교해서 비효울적이게 된다.  이를 극복하기 위해 tanh(z) function을 사용하고자 했다.

하지만 tanh(z)의 값은 마이너스가 존재하기 때문에 Classification에서 확률로서의 해석을 할 수 없어서 sigmoid function을 사용할 수 밖에 없다.



##### Binary Cross Entropy

$$
\frac{\part L}{\part \widehat{y}} = \frac{\part}{\part \widehat{y}} \left[  -[y log(\widehat{y}) + (1 - y)log(1 - \widehat{y})]\right] \\ = - \left[ y\frac{\part}{\part \widehat{y}}log(\widehat{y}) + (1-y) \frac{\part}{\part \widehat{y}} log(1 - \widehat{y}) \right] \\
= -\left( \frac{y}{\widehat{y}} - \frac{1 - y}{1 - \widehat{y}} \right) \\ = \frac{\widehat{y} - y}{\widehat{y}(1-\widehat{y})}
$$

#### 

#### GDM

![](https://github.com/HibernationNo1/TIL/blob/master/image/37.jpg?raw=true)
$$
\frac{\part L}{\part \overrightarrow\theta} = \frac{\part L}{\part \widehat{y}} \frac{\part \widehat{y}}{\part z} \frac{\part z}{\part \overrightarrow\theta} \\
= \frac{\widehat{y} - y}{\widehat{y}(1-\widehat{y})} * \widehat{y} * (1-\widehat{y}) ( x_m + x_{m-1} + ... + x_1 +1) \\
= (x_m(\widehat{y} -y), \ \ \ x_{m-1}(\widehat{y} -y), \ \ \ \ ... , \ \ \ \ x_{1}(\widehat{y} -y), \ \ \ \ (\widehat{y} -y))
$$
여기서 theta의 GDM을 계산해보면 아래와 같이 나온다
$$
\theta_m := \theta_m + \alpha x_m (y - \widehat{y})\\
\theta_{m-1} :=\theta_{m-1}+ \alpha x_{m-1} (y - \widehat{y})\\
\vdots\\ 
\theta_{1} :=\theta_{1}+ \alpha x_{1} (y - \widehat{y})\\
\theta_{0} :=\theta_{0}+ \alpha(y - \widehat{y})
$$
이는 Linear Regression의 GDM와 같은 규칙을 가짐을 확인할 수 있다.

> Linear Regression의 GDM
> $$
> \theta_m := \theta_m + 2\alpha x_m (y - \widehat{y})\\
> \theta_{m-1} :=\theta_{m-1}+ 2\alpha x_{m-1} (y - \widehat{y})\\
> \vdots\\ 
> \theta_{1} :=\theta_{1}+ 2\alpha x_{1} (y - \widehat{y})\\
> \theta_{0} :=\theta_{0}+ 2\alpha(y - \widehat{y})
> $$