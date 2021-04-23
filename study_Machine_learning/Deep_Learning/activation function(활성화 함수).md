# activation function

## 개념 및 사용이유

신경망모델의 각 layer에서는 input 값과 W, b를 곱, 합연산을 통해 a=WX+b를 계산하고 마지막에 활성화 함수를 거쳐 h(a)를 출력한다. 

이렇게 각 layer마다 sigmoid, softmax, relu 등.. 여러 활성화 함수를 사용하면 입력값에 대한 출력값이 linear하게 나오지 않으므로 선형분류기를 비선형 시스템으로 만들 수 있기 때문이다.

> 아래 그림에서 확인할 수 있듯이 기존의 퍼셉트론은 AND와 OR문제는 해결할 수 있었지만 선형 분류기라는 한계에 의해 XOR과 같은 non-linear한 문제는 해결할 수 없었다.
>
> ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FkzozO%2FbtqA0OR0l7G%2FyuHw8Y762KYUfnaoP4Ymx1%2Fimg.png)
>
> 그리고 이를 해결하기 위해 나온 개념이 hidden layer이다. 그러나 이 hidden layer도 무작정 쌓기만 한다고 해서 퍼셉트론을 선형분류기에서 비선형분류기로 바꿀 수 있는 것은 아니다.
>
> 왜냐하면 선형 시스템이 아무리 깊어지더라도 f(ax+by)=af(x) + bf(y)의 성질 때문에 결국 하나의 layer로 깊은 layer를 구현할 수 있기 때문이다.
>
> 이에 대한 해결책이 바로 **활성화 함수(activation function)**이다. 
>
> 활성화 함수를 사용하면 입력값에 대한 출력값이 linear하게 나오지 않으므로 선형분류기를 비선형 시스템으로 만들 수 있다.

**활성화 함수는 입력값을 non-linear한 방식으로 출력값을 도출하기 위해 사용한다.**



## 종류

### 1. Sigmoid

linear regression에서 classification을 수행하기 위해 사용하는 대표적인 함수. 

- 수식
  $$
  \sigma(x) = \frac{1}{1+e^{-x}}
  $$
  

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbDk83K%2FbtqAZO51QIQ%2FIZrbpIaB8qwnnBFtX7M7IK%2Fimg.png)

output값을 0에서 1사이로 만들어준다. 데이터의 평균은 0.5를 갖게된다.

위 그림에서 시그모이드 함수의 기울기를 보면 알 수 있듯이 input값이 어느정도 크거나 작으면 기울기가 아주 작아진다. 이로인해 생기는 문제점은 vanishing gradient현상이 있다.

> **Vanishing Gradient Problem**(기울기값이 사라지는 문제)는 인공신경망을 기울기값을 베이스로 하는 method(backpropagation)로 학습시키려고 할 때 발생되는 어려움이다.
>
> 시그모이드로 여러 layer를 쌓았다고 가정하자. 그러면 출력층에서 멀어질수록 기울기가 거의 0인 몇몇 노드에 의해서 점점 역전파해갈수록, 즉 입력층 쪽으로갈수록 대부분의 노드에서 기울기가 0이되어 결국 gradient가 거의 완전히 사라지고만다. 결국 입력층쪽 노드들은 기울기가 사라지므로 학습이 되지 않게 된다. 
>
> ![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSsZD1lr3mkJp7ioA758ZQNIqsHz11E5njHHw&usqp=CAU)
>
> 특히 이 문제는 네트워크에서 앞쪽 레이어의 파라미터들을 학습시키고, 튜닝하기 정말 어렵게 만든다. 이 문제는 신경망 구조에서 레이어가 늘어날수록 더 악화된다.
>
> **이 문제는 역전파 과정에서 발생한다.**
>
> 왜?
>
> back propagation은 Gradient를 반환하는데,  Sigmoid와 Tanh는 Gradient가 1 보다 작다. 그렇기 때문에 Layer을 많이 쌓을수록 Chain Rule에 의해서 Gradient가 0에 가까워지는 것이다.

- 사용하는 경우

  대부분의 경우에서 시그모이드함수는 좋지 않기때문에 사용하지 않는다. 그러나 유일한 예외가 있는데

  binary classification경우 출력층 노드가 1개이므로 이 노드에서 0~1사이의 값을 가져야 마지막에 cast를 통해(ex. 0.5이상이면 1, 미만이면 0) 1혹은 0값을 output으로 받을 수 있다. 따라서 이때는 시그모이드를 사용한다.



- **정리**

  장점) binary classification의 출력층 노드에서 0~1사이의 값을 만들고 싶을때 사용한다.

  단점) Vanishing gradient - input값이 너무 크거나 작아지면 기울기가 거의 0이된다.
  
  > 역전파 과정에서 기울기 소실되는 문제 발생

---

### 2. Tanh

- 수식
  
  $$
  \frac{e^{z} -e^{(-z)}}{e^{(z)} + e^{(-z)}}
  $$
  
  하지만 tanh(z)의 값은 마이너스가 존재하기 때문에 Classification에서 확률로서의 해석을 할 수 없어서 sigmoid function을 사용할 수 밖에 없다.
  
  **tanh function의 partial derivative**
  $$
  \frac{\part(tanh(z))}{\part z} = \frac{\part}{\part z } \left[ \frac{e^{z} -e^{(-z)}}{e^{(z)} + e^{(-z)}}\right] = \frac{(e^{z} + e^{-z})^2 - (e^{z} - e^{-z})^2}{(e^{z} + e^{-z})^2} \\
   = \frac{4}{(e^{z} + e^{-z})^2} = \frac{2e^{-z}}{e^{z} + e^{-z}} * \frac{2e^z}{e^{z} + e^{-z}} \\
   = \frac{(e^{z} + e^{-z}) + (e^{z} - e^{-z})}{e^{z} + e^{-z}}* \frac{(e^{z} + e^{-z}) - (e^{z} - e^{-z})}{e^{z} + e^{-z}} \\
   = \left (1 + \frac{e^{z} - e^{-z}}{e^{z} + e^{-z}} \right) * \left (1 - \frac{e^{z} - e^{-z}}{e^{z} + e^{-z}} \right)
  $$
  즉, 
  $$
  \frac{\part(tanh(z))}{\part z}  = \left (1 + tanh(z)\right) * \left (1 - tanh(z) \right)
  $$
  
  
  ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2Fc0ambs%2FbtqA2VvQ82W%2FaUsDa9VwaMcKiOfR1UZqJ0%2Fimg.png)

시그모이드 함수와 거의 유사하다. 차이는 -1~1값을 가지고 데이터의 평균이 0이라는 점이다. 시그모이드와 같이 결과값의 평균이 양수로 편향된 문제를 해결하기 위해 사용된다. 데이터의 평균이 0.5가 아닌 0이라는 유일한 차이밖에 없지만 대부분의 경우에서 시그모이드보다 Tanh가 성능이 더 좋다. 그러나 시그모이드와 마찬가지로 Vanishing gradient라는 단점이 있다.



- **정리**

  장점) output데이터의 평균이 0으로써 시그모이드보다 대부분의 경우에서 학습이 더 잘 된다.

  단점) 시그모이드와 마찬가지로 Vanishing gradient현상이 일어난다.

---

### 3. ReLU

- 수식
  ##### 
  
  $$
  ReLU(z) = \left\{\begin{matrix}
  0,\ \ \ \ where\ z <0
  \\ 
  z,\ \ \ \ where\ z \geq 0
  \end{matrix}\right.\\ max(0, z)
  $$
  
  
  
  **ReLU function의 partial derivative**
  $$
  \frac{\part (ReLU(z)) }{\part z}= \left\{\begin{matrix}
  0,\ \ \ \ where\ z <0
  \\ 
  1,\ \ \ \ where\ z \geq 0
  \end{matrix}\right.
  $$
  ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcfAwRD%2FbtqA1y2vSnH%2FeL8PnTymMANrq5TfV7BNw0%2Fimg.png)

그림을 보면 input이 0보다 작을 경우 기울기가 0이기 때문에 대부분의 경우에서 기울기가 0이 되는것을 막아주는게 납득이 안 될수 있지만 실제로 **hidden layer에서 대부분 노드의 z값은 0보다 크기 때문에 기울기가 0이 되는 경우가 많지 않다.** 

**대부분의 input값에 대해 기울기가 0이 아니기 때문에 학습이 빨리 된다.** 학습을 느리게하는 원인이 gradient가 0이 되는 것인데 이를 대부분의 경우에서 막아주기 때문에 시그모이드, Tanh같은 함수보다 학습이 빠르다.

- 사용하는 경우

  대부분의 경우 일반적으로 ReLU의 성능이 가장 좋기때문에 ReLU를 사용한다.



- **정리**

  장점) 대부분의 경우에서 기울기가 0이 되는 것을 막아주기 때문에 학습이 아주 빠르게 잘 되다.

  hidden layer에서 활성화 함수 뭐 써야할지 모르겠으면 그냥 ReLU를 쓰면 된다.

---

### 4. **leaky ReLU**

- 수식
  $$
  a = max(0.01z, z)
  $$
  ![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FcNZbqy%2FbtqA2b61IiI%2FUeCvlYm9rI5q22GUHR0Ap1%2Fimg.png)

ReLU와 유일한 차이점으로는 max(0, z)가 아닌 max(0.01z, z)라는 점이다.

즉, input값인 z가 음수일 경우 기울기가 0이 아닌 0.01값을 갖게 된다.

leaky ReLU를 일반적으로 많이 쓰진 않지만 ReLU보다 학습이 더 잘 되긴 한다.



- **정리**

  장점) z가 음수일때 기울기가 0이 아닌 0.01을 갖게 하므로 ReLU보다 학습이 더 잘 된다.



### 5. Softmax

- 수식
  $$
  softmax(x)_i = \frac{exp(x_i)}{\sum_jexp(x_j)}
  $$
  

Softmax(소프트맥스)는 입력받은 값을 출력으로 0~1사이의 값으로 모두 정규화하며 출력 값들의 총합은 항상 1이 되는 특성을 가진 함수이다.

분류하고 싶은 클래수의 수 만큼 출력으로 구성한다.

가장 큰 출력 값을 부여받은 클래스가 확률이 가장 높은 것으로 이용된다.

소프트맥스 결과값을 One hot encoder의 입력으로 연결하면

가장 큰 값만 True값, 나머지는 False값이 나오게 하여 이용 가능하다.





- 정리:  다중 클래스 분류 시 사용, 출력 노드의 활성화 함수로 많이 사용한다.

