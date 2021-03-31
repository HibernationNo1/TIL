# Optimizer

loss function 또는 cost function을 최소화 하기 위해 반복을 통해 y = wx + b에서 파라미터값을 변경하는 과정을 최적화 라고 하며 가장 간단한 optimizer(최적화)는 gradient descent(경사하강법)이다.

- 한 개의 파라미터 값을 한 번 업데이트 하는 것을 1 **Iteration**이라고 한다.
- 전체 파라미터 값을 한 번 업데이트 하는 것을 1 **Epoch**라고 한다.

$$
gradient\ descent => x:=x- \alpha \frac{dy}{dx}\ \ 동작을\ 반복하며\ 기울기가\ 0인\ 지점으로\ x값을\ 이동시키는\ 것
$$
여기서 alpha는 learning rate를 의미하며, learning rate값을 결정해서 gradient descent method가 발산하는 것을 예방할 수 있다. 

> learning rate의 값에 의해 발산 여부, 학습 속도가 결정될 수 있다. 가장 이상적인 learning rate의 값은 gradient의 변화가 한 방향으로만 진행되며 학습 횟수가 낮도록 하는 값이다.
>
> learning rate값이 크면 학습 속도가 빠르지만, 그럼에도 불구하고 learning rate를 낮게 잡는 이유: 우리가 학습시키는 파라미터는 수많은 weight와 하나의 bias인데, 각각의 파라미터의 학습 속도가 다르면 전체적인 학습이 불안정할 수 있다.(weight 하나만 발산해도 전체적인 Loss와 Cost가 발산을 하게 되기 때문에 잘못된 학습이 이루어지게 된다.)
>
> 만약 learning rate에 곱해지는 데이터 샘플의 크기가 크면, 학습 과정중에 발산해버리는 모양을 볼 수 있게된다. 운이 좋으면 다시 정상적으로 학습이 되겠지만, 계속해서 발산해버리면 학습이 되지 않게 된다. 가장 좋은 방법은 크기가 큰 데이터를 학습 전에 제외시키는 것이지만, 그러기 쉽지 않기 때문에 learning rate를 작게 잡는 것이 관례이다. 

$$
Loss\ function\ \ L^{(i)}(\theta) = (y^{(i)} - \theta x^{(i)})^2\\
Loss\ function\ 에\ 대한\ gradient\ descent=>\ \theta = \theta - \alpha\frac{\partial L^{(i)}(\theta)}{\partial \theta}
$$

$$
Cost\ function\ \ J^{(i)}(\theta) =\frac{1}{n}\sum_{i=1}^{n} (y^{(i)} - \theta x^{(i)})^2\\
Cost\ function\ 에\ 대한\ gradient\ descent=>\ \theta = \theta - \alpha\frac{\partial J^{(i)}(\theta)}{\partial \theta}
$$

실제 최적화는 lost, cost function의 개형을 알지 못하는 상황에서 특정 point의 gradient만 보고 theta를 업데이트 시켜야 한다.



**입력 데이터가 n개일때의 gradient descent method for theta**

![](https://github.com/HibernationNo1/TIL/blob/master/image/9.jpg?raw=true)

- Loss에 대해서

  ![](https://github.com/HibernationNo1/TIL/blob/master/image/10.jpg?raw=true)

- Cost에 대해서

  ![](https://github.com/HibernationNo1/TIL/blob/master/image/11.jpg?raw=true)

---



## 최적화 예시

### 최적화 동작 순서

1. Loss(또는 Cost) function을 구해야 한다.
   1. forwrd propagation 동작
   2. back propagation 동작
2. gredient descent를 구해야 한다.
3. 앞에서 구한 gredient descent를 target 파라미터에 대입한다.
4. 1, 2, 3번의 동작이 1 Iteration이다.
5. 각각의 target 파라미터마다 1 Iteration를 전부 수행해줘야 1 Epoch이다.

> 예시1) (1 Iteration)
> $$
> \widehat{y} = \theta x\ 일때\ Loss\ 를\ 사용해서\ 파라미터를\ 1회\ 업데이트\ 하는\ 과정\\
> $$
>
> $$
> 1.\\ Loss\ function\ 구현\\
> $$
>
> $$
> foward\ propagation:\\
> Node1\ 의\ 동작: z_1 = \theta x\\
> Node2\ 의\ 동작: z_2 = y - \widehat{y}=y-z_1\\
> Node3\ 의\ 동작: L = (z_2)^2
> $$
>
> $$
> back\ propagation:\\
> \frac{\partial z_1}{\partial  \theta} = x,\ \ \ \ \frac{\partial z_2}{\partial z_1}  = -1,\ \ \ \ \frac{\partial L}{\partial z_2}  = 2z_2\\
> \frac{\partial L}{\partial \theta} = \frac{\partial L}{\partial z_2} \frac{\partial z_2}{\partial z_1}\frac{\partial z_1}{\partial  \theta} = 2z_2*(-1)*x \\
> = -2(y-z_1)*x\\
> = -2x(y- \widehat{y})\\
> = -2x(y-\theta x)\\
> $$
>
> $$
> 2. \\ gradient\ descent\ 구현
> $$
>
> $$
> \theta := \theta - \alpha\frac{\partial L^{(i)}(\theta)}{\partial \theta}\\
> = \theta + 2\alpha x^{(i)}(y^{(i)} - \widehat{y}^{(i)}) \\
> = \theta + 2\alpha x^{(i)}(y^{(i)} - \theta x^{(i)})
> $$
>
> $$
> 이\ 때\ 각각의\ \theta + 2\alpha x^{(i)}(y - \widehat{y})에\ 대해서\\ x >0,\ \ \ x<0,\ \ \  y>\widehat{y},\ \ \  y<\widehat{y}\\
> 이\ 네\ 가지의\ 경우의\ 수에\ 대해서\ 생각을\ 해야한다.\\
> (x = 0이면\ 업데이트가\ 소용 없고,\ y=\widehat{y}이면\ 최적의\ 파라미터임)
> $$
>
> ![](https://github.com/HibernationNo1/TIL/blob/master/image/12.-1.jpg?raw=true)



> 예시 2)
> $$
> \widehat{y} = \theta x^{(i)}\ 이고,\ i=1,\ 2\  일때\ Cost\ 를\ 사용해서\ 파라미터를\ 1회\ 업데이트\ 하는\ 과정\\
> (입력\ 데이터\ 2개)
> $$
>
> $$
> 1.\\ Loss\ function\ 구현\\
> $$
>
> $$
> foward\ propagation:\\
> Node1\ 의\ 동작: z_1 = \theta x\\
> Node2\ 의\ 동작: z_2 = y - \widehat{y}=y-z_1\\
> Node3\ 의\ 동작: L = (z_2)^2\\
> Node4\ 의\ 동작: J=\frac{1}{2}\sum_{i=1}^{2}L = \frac{1}{2}(L^{(1)}+L^{(2)})
> $$
>
> $$
> back\ propagation:\\
> \frac{\partial z_1^{(i)}}{\partial  \theta} = x,\ \ \ \ \frac{\partial z_2^{(i)}}{\partial z_1^{(i)}}  = -1,\ \ \ \ \frac{\partial L^{(i)}}{\partial z_2^{(i)}}  = 2z_2^{(i)},\ \ \ \ \frac{\partial J}{\partial L^{(1)}} = \frac{\partial J}{\partial L^{(2)}} = \frac{1}{2}\\
> \frac{\partial J}{\partial \theta} =\frac{\partial J}{\partial L^{(i)}} \frac{\partial L^{(i)}}{\partial z_2^{(i)}} \frac{\partial z_2^{(i)}}{\partial z_1^{(i)}}\frac{\partial z_1^{(i)}}{\partial  \theta} = \frac{1}{2}*2z_2^{(i)}*(-1)*x^{(i)} \\
> = -\frac{1}{2}*2(y^{(i)}-z_1^{(i)})*x^{(i)}\\
> = -\frac{1}{2}*2x^{(i)}(y^{(i)}- \widehat{y}^{(i)})\\
> = -\frac{1}{2}*2x^{(i)}(y^{(i)}-\theta x^{(i)})\\
> 위의\ 식이\ 입력\ 데이터\ 개수\ 만큼 진행된다.
> $$
>
> ![](https://github.com/HibernationNo1/TIL/blob/master/image/13.jpg?raw=true)
> $$
> 그러므로\ \ \frac{\part J}{\part \theta} = \frac{1}{2} \sum_{i=1}^{2}[-2x^{(i)}(y^{(i)} - \widehat{y}^{(i)})] \ \ 식이\ 성립된다.
> $$
>
> $$
> 2. \\ gradient\ descent\ 구현\\
> \theta := \theta - \alpha\frac{\partial J}{\partial \theta}\\
> = \theta - \frac{\alpha}{2} \sum_{j=1}^{2}\frac{\part L^{(i)}}{\part \theta} \\
> = \theta + \frac{\alpha}{2} \sum_{i=1}^{2}[-2x^{(i)}(y^{(i)} - \widehat{y}^{(i)})]
> $$
>
> ![](https://github.com/HibernationNo1/TIL/blob/master/image/14.jpg?raw=true)

Loss와 Cost의 연산을 통해 알 수 있는것!

Loss만을 사용해서 theta를 업데이트 할 때 특정 data값이 너무 크면 그 순간 발산이 일어나서 학습이 더 안좋게 진행되게 된다. 이는 학습 횟수가 더 필요하게 되고 학습 속도를 늦추는 원인이 된다. 그렇지만 Cost를 사용하면 1/n이 data값을 작게 만들어 주기 때문에 발산 확률이 더욱 내려간다.  



위의 예시와 같은 동작을 데이터가 n개 입력될 때에 적용해보자.

1. forward propagation

   ![](https://github.com/HibernationNo1/TIL/blob/master/image/15.jpg?raw=true)

2. back propagation

   ![](https://github.com/HibernationNo1/TIL/blob/master/image/16.jpg?raw=true)

$$
데이터가\ n개\ 입력될\ 때\ back\ propagation \\
\frac{\part J}{\part \theta} = \frac{1}{n} \sum_{j=1}^{n}\frac{\part L^{(i)}}{\part \theta}\ \ \ 이기\ 때문에\\
gradient\ descent\ 연산은\\
\theta := \theta - \alpha\frac{\partial J}{\partial \theta}\\
= \theta - \frac{\alpha}{n} \sum_{j=1}^{n}\frac{\part L^{(i)}}{\part \theta} \\
= \theta - \frac{\alpha}{n} \sum_{i=1}^{n}[-2x^{(i)}(y^{(i)} - \widehat{y}^{(i)})]\\
임을\ 알\ 수\ 있다.\\
즉,\ \Delta  \theta= \frac{1}{n} \sum_{i=1}^{n} \Delta \theta^{(i)}
$$



### 코드 구현

```python
# basic_node
# basic_node에는 optimizer에 필요한 basic node class가 포함되어 있는 py
import numpy as np

class mul_node():
    def forward(self, x, y):
        self._x, self._y = x, y
        self._z = self._x*self._y
        return self._z

    def backawrd(self, dz):
        return (dz*self._y, dz*self._x)

class minus_node():
    def forward(self, x, y):
        self._x, self._y = x, y
        self._z = self._x - self._y
        return self._z

    def backawrd(self, dz):
        return (dz, -1*dz)

class square_node():
    def forward(self, x):
        self._x = x
        self._z = self._x*self._x
        return self._z

    def backawrd(self, dz):
        return (2*dz*self._x)

class meam_node():
    def forward(self, x):
        self._x = x
        self._z = np.mean(self._x)
        return self._z

    def backawrd(self, dz):
        dx = dz*1/len(self._x)*np.ones_like(self._x)
        return dx 
```



```python
# z = x의 mean perceptron
import matplotlib.pyplot as plt
import numpy as np

from dataset_generator import dataset_generator
import basic_node as nodes

# dataset preparation
dataset_gen = dataset_generator()
dataset_gen.set_coefficient([5, 0])  # y = 5x + 0
x_data, t_data = dataset_gen.make_dataset()

#model implementation
nond1 = nodes.mul_node()  # make mul_node instance 

# MSE loss implementation
node2 = nodes.minus_node()  # make minus_node instance 
node3 = nodes.square_node() # make square_node instance 
node4 = nodes.mean_node()   # make mean_node instance 

# hyperparameter setting
epochs = 50  # total epoch setting
lr = 0.05   # learning rate setting
th = -1     # arbitrary theta

cost_list = list()  # for drow plot
th_list = list()

# learning
for epoch in range(epochs):
    x, y = x_data, y_data

    # forward propagation
    z1 = node1.forward(th, x)
    z2 = node2.forward(y, z1)
    L = node3.forward(z2)
    J = node4.forward(L)

    # back propagation
    dL = node4.backward(1)
    dz2 = node3.backward(dL)
    dy, dz1 = node2.backward(dz2)   # dy는 버릴 값
    dth, dx = node1.backward(dz1)   # dx는 버릴 값

    th = h - lr*np.sum(dth)   # gradient descent(theta updata)
         
    th_list.append(th)      # for drow plot
    cost_list.append(z3)

# REsult Visualization
fig, ax = plt.subplot(2, 1, figsize = (30, 10))
ax[0].plot(th_list)
ax[1].plot(loss_list)

# 그래프로 시각화
title_font = {'size': 30, 'alpha': 0.8, 'color' : 'navy'}
label_font = {'size': 20, 'alpha': 0.8}
plt.style.use('seaborn')

ax[0].set_title(r'$\theta$', fontdict = title_font)
ax[1].set_title('Loss', fontdict = title_font)
ax[1].set_xlabel('Iteration', fontdict = label_font)
```

이때 back propagation의 동작을 numpy로 구현한다면 hadamard product(원소 곱) 연산을 사용해야 한다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/17.jpg?raw=true)

어짜피 numpy의 곱셈 연산은 elementry operation이 적용되기 때문에 partial derivative를 그대로 곱해주고, np.sum() 을 사용해서 전체 entry를 합해주는 연산을 통해 back propagation의 동작을 구현할 수 있다.

---



텐서플로우에서 손실 함수를 최소화하기 위해 조금씩 variable들을 변경해주는 optimizer을 제공한다.

## 종류

![](https://img1.daumcdn.net/thumb/R1280x0/?scode=mtistory2&fname=https%3A%2F%2Fblog.kakaocdn.net%2Fdn%2FbQ934t%2FbtqASyVqeeD%2FozNDSKWvAbxiJb7VtgLkSk%2Fimg.png)

#### 1. 경사하강법(GD)

$$
수식 \ \ : \ \ \theta_{i+1} = \theta_i - \alpha \frac{\partial}{\partial \theta_i}Cost(\theta_0, \theta_1)
$$

##### 1. BGD(Batch Gradient Descent)

트레이닝 데이터 n개의 손실함수 미분값을 모두 더한 뒤 평균을 취해서 파라미터의 한 스텝을 업데이트 하는 것.

ex) 선형회귀에서의 손실함수의 미분값
$$
\frac{\partial}{\partial \theta_0}Cost(\theta_0, \theta_1) = \frac {\partial}{\partial \theta_0} \frac{1}{2n}\sum_{i = 1}^{n}(\widehat{y_i} - y_i)^2
$$



실제 문제를 다룰 때는 트레이닝 데이터의 개수가 매우 많아질 수 있어 BGD를 사용할 경우 파라미터를 한 스텝 업데이트하는데 많은 시간이 걸리게 된다.(최적의 파라미터를 찾는데 오랜 시간이 걸림)



BGD에서 1 Iteration  == 1 epoch다.

##### 2.  SGD(Stochastic Gradient Descent)

`tf.optimizers.SGD` : 확률적 경사 하강법(Stochastic Gradient Descent, SGD) optimizer

> 모멘텀과 네스테로프 모멘텀(Nesterov momentum), 그리고 학습률 감소 기법(learning rate decay)을 지원한다.

파라미터를 자주 업데이트 할 수 있지만 파라미터를 한 번 업데이트 할 때 전체 트레이닝 데이터의 특성을 고려하지 않고 각각의 트레이닝 데이터의 특성만을 고려하므로 부정확한 방향으로 업데이트가 진행될 수도 있다.

**Batch Gradient Descent와의 차이**

- BGD(Batch Gradient Descent)
  - 경사하강법의 한 스텝 업데이트를 할 때 모든 데이터를 계산한다(batch size = 전체 데이터 개수) => 소요시간 길다
  - 최적의 한스텝을 나아간다.
  - 6 스텝 * 1시간 = 6시간
  - 확실한데 너무 느리다. (단, 데이터 개수가 엄청 큰게 아니라면 SGD보다 빠를 수 있다.)
- SGD(Stochastic Gradient Descent)
  - 경사하강법의 한스텝 어베이트를 진행할 때 1개의 트레이닝 데이터만 사용하는 기법 (batch size가 1인 경사하강법이다.) => 소요시간 5분
  - 빠르게 전진한다. 
  - 10 스텝 * 5분 => 50분
  - 조금 헤메지만 그래도 빠르게 간다! (단, 데이터 개수가 엄청 큰게 아니라면 BGD보다 느릴 수 있다.)



![](https://t1.daumcdn.net/cfile/tistory/9961913359D86B9833)

GD의 경우 항상 전체 데이터 셋을 가지고 한발자국 전진할 때마다(learning rate) 최적의 값을 찾아 나아가고 있는 모습을 볼수 있지만, SGD는 Mini-batch 사이즈 만큼 조금씩 돌려서 최적의 값으로 가고 있다. 

그러나 최적값을 찾아 나아가는 과정을 봤을 때는 약간 뒤죽 박죽의 형태로 찾아가지만 속도는 GD 보다 훨씬 빠르다.

**코드**

```python
# 확률적 경사 하강법(Stochastic Gradient Descent, SGD) optimizer 정의
optimizer = tf.optimizers.SGD(a)  # 여기서 a는 learning rate임 (상수여야함) 
```



##### 3. MGD(Mini - Batch Gradient Descent)

Batch Gradient Dsecent와 Stochastic Gradient Descen의 절충적인 기법으로 **가장 많이 사용된다**.

MGB는 전체 트레이닝 데이터Batch가 1000(n)개라면 이를 100(m)개씩 묶은 Mini-batch개수만큼 손실 함수 미분값 평균을 이용해서 파라미터 한 스텝을 업데이트 하는 기법

BGD는 한 번에 모든 데이터를 입력해서 파라미터를 업데이트 한다면, MGD는 데이터를 특정 수의 batch로 나눈 후 한 개의 batch씩 입력한다. 그렇기 때문에 BGD는 serial한 task가 진행되고, MGD는 parallel한 task가 진행되기 때문에 GPU에서 더욱 좋은 성능을 낼 수 있는 것이다.
$$
MGD에서의\ Iteration\ per\ epoch:\ \frac{total\ sample}{mini-batch\ size} \\
여기서 Total\ sample: 1000\ 이고,\ \ \ \ \ Mini-batch\ size: 20이면\\
Iteration\ per\ epoch: \frac{1000}{20} = 50\\ 그리고\ epoch = 5 일때\\
result\ iterations = 5*50 = 250\ Iterations
$$
위의 예시에서 Iteration per epoch가 정수로 떨어지지 않는다면 올림을 통해서 정수로 만들어준다.

batch size가 크면 전체 데이터의 특성을 잘 반영하지만, 연산 속도는 느려진다.



Mini - batch가 어떻게 학습 속도를 빠르게 해줄까?

1. GPU의 다수의 코드에 batch들을 할당해서 동시에 연산을 수행해서 빠른 학습이 가능하게 한다.



#### 2. Adam

기본 SGD를 조금 더 발전시킨 optimizer라고 생각하면 됨

RMSprop의 특징인 gradient의 제곱에 지수평균한 값을 사용하며 Momentum의 특징으로 gradient를 제곱하지 않은 값을 사용하여 지수평균을 구하고 수식에 활용한다.

기본 SGD은 미분값이 0이 되는 지점에서 더 나아가지 못하지만, Adam은 미분값이 0인 지점을 넘어서 계속해서 탐색한다.

> 2차 함수와 같은 형태는 미분값이 0인 지점이 2개이기 때문에 더 나아가는 최적화가 필요하다.



#### 3. RMSprop

RMSProp 은 아다그라드의 G(t)의 값이 무한히 커지는 것을 방지하고자 제안된 방법으로, 기울기를 단순 누적하지 않고 지수 가중 이동 평균 Exponentially weighted moving average 를 사용하여 최신 기울기들이 더 크게 반영되도록 하였다.

> 지수 이동 평균: 최근 값을 더 잘 반영하기 위해 최근 값과 이전 값에 각각 가중치를 주어 계산하는 방법

