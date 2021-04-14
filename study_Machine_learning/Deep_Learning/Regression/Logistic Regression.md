# Logistic Regression

**Logistic Regression**: 데이터가 특정 카테고리에 속할지를 0과 1사이의 연속적인 확률로 예측하는 회귀 알고리즘 (Binary Classification 문제를 해결하기 위한 Regression)

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
  Logistic Function으로 인해 Linear Function은 비선형 function이 된다.



이제 Affine Function과 Logistic Function 으로 인해 Artificial Neural이 완성될 수 있다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/35.jpg?raw=true)



### Logistic Regression

Affine Function	 ->	  Activation Function	 ->	Binary Cross Entropy Loss	 - > 	Gradient Descent Mothod

여기서 MES대신 CEL(Cross Entropy Loss)을 사용하는 이유 : Logistic Function에 MES를 사용하게 되면 convex하지 않은 Loss가 된다. 그렇기 때문에 convexity를 보장하기 위해 CEL을 사용하는 것이다.

Affine Function
$$
z = \overrightarrow{\theta^*} \overrightarrow{x}
$$
Logistic Function
$$
a = \sigma(z) = \widehat{y}
$$
Cross Entropy Loss
$$
J = \frac{1}{n}\sum_{i = 1}^{n}BCE^{(i)}
$$

> BCE = Binary Cross Entropy Loss



##### Sigmoid(z)

Sigmoid Function의 partial derivative를 구해보자
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

###### Requirement

정답에 알맞은 예측을 하면 Loss를 줄이고, 정답에 알맞지 않은 예측을 하면 Loss를 높히는 방식으로 Logistic Regression 모델의 학습에 강화학습(보상)을 적용해 보자
$$
case1 :  \ \ \ label = 0:  \ \ \widehat{y} \approx  1 \rightarrow  Loss\ 증가,\ \ \ \ \widehat{y} \approx  0 \rightarrow  Loss\ 감소\\
case2 :  \ \ \ label = 1:  \ \ \widehat{y} \approx  0 \rightarrow  Loss\ 증가,\ \ \ \ \widehat{y} \approx  1 \rightarrow  Loss\ 감소\\
$$
이는 log함수로 설명될 수 있다.
$$
case 1: -log(1-\widehat{y}) \\
case 2: -log(\widehat{y}) \\
$$
![](https://github.com/HibernationNo1/TIL/blob/master/image/36.jpg?raw=true)

이를 적용해서 우리는 Binary Cross Entropy를 구현할 수 있다.



###### BCE

$$
BCE = \left\{\begin{matrix}
-log(\widehat{y}), \ \ \ \ where \ y = 1
\\ 
-log(1-\widehat{y}), \ \ \ \ where \ y = 0
\end{matrix}\right.\\
$$

즉, 
$$
Loss= -[y log(\widehat{y}) + (1 - y)log(1 - \widehat{y})]
$$
**BCE Loss Function의 partial derivative**
$$
\frac{\part L}{\part \widehat{y}} = \frac{\part}{\part \widehat{y}} \left[  -[y log(\widehat{y}) + (1 - y)log(1 - \widehat{y})]\right] \\ = - \left[ y\frac{\part}{\part \widehat{y}}log(\widehat{y}) + (1-y) \frac{\part}{\part \widehat{y}} log(1 - \widehat{y}) \right] \\
= -\left( \frac{y}{\widehat{y}} - \frac{1 - y}{1 - \widehat{y}} \right) \\ = \frac{\widehat{y} - y}{\widehat{y}(1-\widehat{y})}
$$


#### propagation

- forward propagation

  Affine Function	 ->	  Sigmoid Function	 ->	Binary Cross Entropy Loss	

  

- backward propagation

  d(Binary Cross Entropy Loss) * d(Sigmoid Function)  * d(Affine Function)

  -> 	Gradient Descent Mothod

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