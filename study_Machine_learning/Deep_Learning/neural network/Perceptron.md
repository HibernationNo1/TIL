# Perceptron

## 개념

- 퍼셉트론은 생물학적 뉴런을 공학적인 구조로 변형한 것이다.
- artificial neural network에서는 하나의 artificial neural이 바로 perceptron이다.

퍼셉트론은 입력층과 출력층을 가지고 있다.

> 입력층에서 인풋 데이터 x를 받고, 이를 가중치 W와 곱한 후, 이 값에 바이어스 b를 더한다. 그리고 이 값을 **활성 함수**의 입력값으로 대입해서 출력층은 최종적으로 0 또는 1의 값을 출력한다. 



- 퍼셉트론의 동작 (입력 1개)
  $$
  수식 : \ y = \sigma(Wx + b) \\ \sigma: 활성\ 함수
  $$
  여기서 활성함수로 계단함수를 사용하여 퍼셉트론의 출력을 0 또는 1만 출력하게 하기 때문에**선형 이진분류기**라고 한다.

- artificial neural의 동작(입력 다수)

$$
  수식 : \ y = \sigma(W_1x_1 +W_2x_2 +W_3x_3 +W_4x_4 +... + b) \\ \sigma: 활성\ 함수
$$


    1. 이전 layer의 artificial neural들로부터 받은 weight들을 합한다.

    2. weighted sum에 activation function을 적용해서 다음 layer의 artigicial neural에게 전달한다.



- 퍼셉트론의 가중치란, input의 중요도를 의미한다.

  어떠한 동작에 대한 의사결정 모델을 퍼셉트론을 이용해서 만든다면, 의사결정에 고려해야 하는 사항이 3가지 있다고 가정할 때 (w1, w2, w3) 가장 중요하게 고려하는 사항에 가장 큰 비율의 값을 할당하는 것이다.

  ex) w3이 가장 중요할 때: w1 = 2, w2 = 2, w3 = 6

- 단일 퍼셉트론은 선형 분리가 불가능한 문제는 해결할 수 없다.



## 코드 구현

단일 perceptron 코드 (예. +, *, 평균 구하기 동작을 하는 perceptron)

```python
# z = x+y perceptron
import numpy as np

class mul_node:
    def __init__(self):
        self._x, self._y = None, None
        self._z = None
    
    def forward(self, x, y):
        self._x, self._y = x, y
        self._z = self._x + self._y
        return self._z

    def backward(self, dz):
        return dz, dz   # x, y에 대한 back propagation
```

> $$
> z = x+y\ 일\ 때\\
> x\ 방향의\ back\ propagation:\ \frac{\partial J}{\partial x} = \frac{\partial J}{\partial z}\frac{\partial z}{\partial x}(x+y) = \frac{\partial J}{\partial z}*1\\
> y\ 방향의\ back\ propagation:\ \frac{\partial J}{\partial y} = \frac{\partial J}{\partial z}\frac{\partial z}{\partial y}(x+y) = \frac{\partial J}{\partial z}*1\\
> 위\ 코드의\ dz는\  \frac{\partial J}{\partial z}를\ 의미한다.
> $$

```python
# z = x*y perceptron
import numpy as np

class plus_node:
    def __init__(self):
        self._x, self._y = None, None
        self._z = None
    
    def forward(self, x, y):
        self._x, self._y = x, y
        self._z = self._x * self._y
        return self._z

    def backward(self, dz):
        return dz*self._y, dz*self._x   # x, y에 대한 back propagation
```

> $$
> z = x*y\ 일\ 때\\
> x\ 방향의\ back\ propagation:\ \frac{\partial J}{\partial x} = \frac{\partial J}{\partial z}\frac{\partial z}{\partial x}(x*y) = \frac{\partial J}{\partial z}*y\\
> y\ 방향의\ back\ propagation:\ \frac{\partial J}{\partial y} = \frac{\partial J}{\partial z}\frac{\partial z}{\partial y}(x*y) = \frac{\partial J}{\partial z}*x\\
> $$

```python
# z = x의 mean perceptron
import numpy as np

class mean_node:
    def __init__(self):
        self._x= None
        self._z = None
    
    def forward(self, x, y):
        self._x = x
        self._z = np.mean(self._x)
        return self._z

    def backward(self, dz):
        dx = dz*1/len(self._x)*np.ones_like(self._x)
        # shape은 _x의 것을 그대로 따고, entry를 1로 채운 후 1/n을 곱해준다. 
        return dx
```

> $$
> x = [x_1,\ x_2,\ x_3,\ ..., x_n]\ 일때\ z = \frac{1}{n}\\
> back\ propagation:\ \frac{\partial J}{\partial x_1} = \frac{\partial J}{\partial z}\frac{\partial z}{\partial x_1}(\frac{1}{n}) = \frac{\partial J}{\partial z}*\frac{1}{n}\\
> \vdots \\
>  \frac{\partial J}{\partial x_n} = \frac{\partial J}{\partial z}\frac{\partial z}{\partial x_n}(\frac{1}{n}) = \frac{\partial J}{\partial z}*\frac{1}{n}\\
> $$

basic_node는 덧셈, 뺄셈, 곱셈, 제곱, 평균 이 5개의 동작을 하는 perception들을 의미한다.