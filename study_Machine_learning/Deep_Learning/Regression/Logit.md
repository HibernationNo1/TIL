# Logit

- probability: 전체 경우의 수 중 특정 사건이 일어날 확률

  Y = 3개,  N = 7 라면 P = 3/10 

#### **Odds란?**

전체 경우의 수 중 (특정 사건이 일어나는 경우)/(특정 사건이 일어나지 않는 경우)

> Y = 3개,  N = 7 라면 O(N) = 3/7,  O(Y) = 7/3,  

$$
O = \frac{Happening}{NOT\ Happening}
$$

이는 곧 각각 아래처럼 표현할 수 있다.
$$
O(Y) = \frac{P(pass)}{P(no\ pass)} = \frac{P(pass)}{1-P(pass)} \\
O(N) =  \frac{P(no\ pass)}{P(pass)} = \frac{P(no\ pass)}{1 - P(no\ pass)}
$$
즉, 
$$
O(pass)= \frac{P(pass)}{1-P(pass)} 
$$
Odds(x) = x / 1-x 와 같음을 알 수 있다.

이 식에서는 세 가지의 경우의 수가 존재할 수 있다.
$$
1. \ \ \ \ P(pass) > P(no\ pass) == (x > 1-x) \ \ \ \ \therefore O(pass) >1 \\
2. \ \ \ \ P(pass) = P(no\ pass) == (x = 1-x) \ \ \ \ \therefore O(pass) =1 \\
3. \ \ \ \ P(pass) < P(no\ pass) == (x < 1-x) \ \ \ \ \therefore 0<O(pass) <1 \\
$$


**Odds의 단점**

분모가 더 클때(O > 1) 와 분자가 더 클때( 0< O < 1)가 비대칭적이다.



Odds를 대칭적으로 만드는 방법 : log를 취하면 된다.
$$
logit(pass) = log_e \left ( \frac{P(pass)}{1-P(pass)} \right)
$$
![](https://github.com/HibernationNo1/TIL/blob/master/image/38.jpg?raw=true)

![](https://github.com/HibernationNo1/TIL/blob/master/image/39.jpg?raw=true)

이렇게 Odds에 log를 취한 것을 logit이라고 한다.

>  예를 들어보자
>
> 전체 경우의 수가 7이고, pass = 3 일 때
> $$
> O(pass) = \frac{3}{4} = 0.75\  \ \ \ \ O(no\ pass) = \frac{4}{3}= 1.33 \\
> logit(pass) = log_e(\frac{3}{4}) = -0.29 \ \ \ \ \ logit(no\ pass) = log_e(\frac{4}{3}) = +0.29
> $$

$$
-\infty  < logit(pass) < +\infty
$$

#### **Logit을 왜 공부할까? **

Logistic Regression의 동작을 보면

Affin Function의 output은 Logit이고 Logistic Function의 output은 확률이며, 이 확률을 통해서 Loss를 계산을 하게 된다. 

즉, Logistic Function의 input에 Logit형태의 data를 주고, 이후 Binary cross Entropy를 적용 후 이어서 GDM를 수행하면 비로소 Logit의 역할을 수행하는 것을 알 수 있다.

(Logistic Regression에서 Affine Function의 output은 pass에 대한 logit이라고 칭하자.)
$$
z = \overrightarrow{\theta^T} * \overrightarrow{x} == logit(pass)
$$
Affine Function은 분명이 weighted sum이지만, 뒤에 어떤 function을 붙여주느냐에 따라서 그 역할이 달라짐을 이해할 수 있다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/40.jpg?raw=true)

위 그림에서 마지막 Perceptron들이 반쪽 모양임을 볼 수 있다. 이는 Multilayer Perceptron으로부터 Affine Function(weighted sum)을 input으로 받은 output layer에 Activation Function을 적용하지 않았음을 표현한 것이다. 이 Activation Function에 어떤 Function을 적용하느냐에 따라서 학습 과정이 달라지게 되는 것이다.

그리고 이 Activation Function을 Logistic Function으로 결정하게 되면, Affine Function은 Logit의 역할을 하게 되는 것이다.





## Sigmiod Function

Sigmiod Function의 역할

Logit의 역함수 구해주는 역할이다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/37.jpg?raw=true)

왜 Logit의 역함수를 구하는 것일까? Loss를 구하려면 Binary Cross Entropy를 사용해야 하는데, 이  Binary Cross Entropy를 사용하려면 input이 확률(pass)여야 한다.

그렇기 때문에 **Activation Function에 Sigmiod Function을 사용함으로써 Affine Function의 weighted sum을 pass로 바꿔주는 것이다. ** 



#### Sigmoid Function 수식 유도

Sigmoid Function 수식 
$$
\sigma(x) = \frac{1}{1+e^{-x}}
$$



- Logit
  $$
  Logit(x) ==> y = log_e\left( \frac{x}{1-x} \right)
  $$

- Logit의 역함수
  $$
  x = log_e \left(\frac{y}{1-y} \right)
  $$
  전개

  - exp의 지수로 올림
    $$
    e^x = e^{log_e \left(\frac{y}{1-y} \right)} = \frac{y}{1-y}
    $$

  - 분모 <=> 분자
    $$
    \frac{1}{e^x} = \frac{1-y}{y} = \frac{1}{y}-1\\
    \frac{1}{e^x}+1 = \frac{1}{y} \\
    \frac{1 + e^x}{e^x} = \frac{1}{y}
    $$

  - 다시 분모 <=> 분자
    $$
    y = \frac{e^x}{1+e^x} = \frac{e^x * \frac{1}{e^x}}{(1+e^x)\frac{1}{e^x}}\\
    y = \frac{1}{1 + e^{-x}} = \sigma(x)
    $$

  이를 통해 Sigmoid Function와 Logit은 서로 역함수임을 알 수 있다.
  $$
  P(x) = \frac{1}{1 + e^{-Logit(x)}}  
  $$
  

**즉, Affine Function을 Logit이라는 가정 하에 역함수를 취하는 Sigmoid Function을 Logistic Function이라고 한다.**



## Softmax Function

각각의 Perceptron에서 나온 Affine Function을 Logit(C) 라고 할 때

![](https://github.com/HibernationNo1/TIL/blob/master/image/41.jpg?raw=true)

> Binary Classification이라는 가정 하에 C가 두 개의 class만 있다고 가정해보자
> $$
> C = \{C_1, C_2 \}\\
> P(C_1) + P(C_2) = 1 \ \ \ \ \ P(C_2) = 1-P(C_1)
> $$
> 이때 C_1의 확률은 Logit의 수식에 의해 아래와 같이 정의될 수 있다. (Logit 을 l 로 표기)
> $$
> P(C_1) = \frac{1}{1+e^{-l(C_1)}}
> $$
> 이를 Logit(C_1)로 표현해보자
> $$
> 1+e^{-l(C_1)} = \frac{1}{P(C_1)} \\
> e^{-l(C_1)} = \frac{1-P(C_1)}{P(C_1)} = \frac{P(C_2)}{P(C_1)}\\
> e^{l(C_1)} =  \frac{P(C_1)}{P(C_2)}
> \\ 양\ 변에\ *ln
> \\ l(C_1) = log_e \left(  \frac{P(C_1)}{P(C_2)} \right )
> $$



#### Softmax 수식 유도

Softmax 수식
$$
Softmax(x_i) == P(C_i) = \frac{e^{l(C_i)}}{\sum_{j=1}^{K}e^{l(C_j)}}
$$


class가 여러개일 때
$$
C = \{C_1, C_2, ..., C_k\} \\
P(C_1), P(C_2),...,P(C_k)  \\
P(C_1)+P(C_2)+...+P(C_k) = 1 \\
l(C_1), l(C_2),...,l(C_k)
$$
일 때
$$
(1) \ \ \ \ \ \  l(C_i) = ln \left( \frac{P(C_i)}{P(C_K)} \right)\\
k =  임의의\ 수 \ \ \ \ \ \ \ \ \ \ \ \ \ i = k 가\ 아닌\ 임의의\ 수
$$

$$
(2) \ \ \ \ \ \ l(C_i) = ln \left( \frac{P(C_K)}{P(C_K)} \right) =1
$$

(1)양 변의 값을 exp의 지수로 올리면
$$
(3)\ \ \ \ \ \ e^{l(C_i)} = e^{ln \left( \frac{P(C_i)}{P(C_K)} \right)} = \frac{P(C_i)}{P(C_K)}
$$

$$
(5)\ \ \ \ \ \  e^{l(C_k)} = 1\\
(6)\ \ \ \ \ \  p(C_i) = e^{l(C_i)}P(C_K)
$$

(3)에 i를 제외한 모든 수를 더하는 sum을 취하면
$$
\sum_{j=1}^{K-1}e^{l(C_i)}  = \sum_{j=1}^{K-1}\frac{P(C_i)}{P(C_K)} = \frac{1-P(C_K)}{P(C_K)} = \frac{1}{P(C_K)}-1\\
1 + \sum_{j=1}^{K-1}e^{l(C_i)}  = \frac{1}{P(C_K)}\\
P(C_K) = \frac{1}{1 + \sum_{j=1}^{K-1}e^{l(C_i)}}
$$
여기서 1에 (5)를 대입한다면
$$
P(C_K) = \frac{1}{e^{l(C_k)} + \sum_{j=1}^{K-1}e^{l(C_i)}} = \frac{1}{\sum_{j=1}^{K}e^{l(C_i)}}
$$
그리고 이 값을 (6)에 대입하면
$$
p(C_i) = \frac{e^{l(C_i)}}{\sum_{j=1}^{K}e^{l(C_i)}} == Softmax(x_i) 
$$
Softmax 수식이 나옴을 알 수 있다.

**즉, C_i 에 대한 Logit을 C_i에 대한 확률로 표현을 한 것이 Softmax Function이다.**

> 위의 식에서 알 수 있듯, P(C_k)는 어짜피 사라지기 때문에 K에 어떤 수를 넣는다 해도 상관이 없다.
>
>  Softmax Function 의 input은 Logit(C_i)고, output은 Pass(C_i)임을 알 수 있다.





---

Affine Function을 Logit이라고 가정하고, Activation Function으로

Sigmoid Function을 사용하면 Logistic Regression이고

Softmax Function을 사용하면 Softmax Regression이다.

