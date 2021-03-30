# Optimizer



cost function을 최소화 하기 위해 반복을 통해 y = wx + b에서 파라미터값을 변경하는 과정을 최적화 라고 하며 가장 간단한 optimizer(최적화)는 gradient descent(경사하강법)이다.

- 한 개의 파라미터 값을 한 번 업데이트 하는 것을 1 **Iteration**이라고 한다.
- 전체 파라미터 값을 한 번 업데이트 하는 것을 1 **Epoch**라고 한다.

$$
gradient\ descent => x:=x- \alpha \frac{dy}{dx}\ \ 동작을\ 반복하며\ 기울기가\ 0인\ 지점으로\ x값을\ 이동시키는\ 것
$$
여기서 alpha는 learning rate를 의미하며, learning rate값을 결정해서 gradient descent method가 발산하는 것을 예방할 수 있다. 

> learning rate의 값에 의해 발산 여부, 학습 속도가 결정될 수 있다. 가장 이상적인 learning rate의 값은 gradient의 변화가 한 방향으로만 진행되며 학습 횟수가 낮도록 하는 값이다.
>
> learning rate값이 크면 학습 속도가 빠르지만, 그럼에도 불구하고 learning rate를 낮게 잡는 이유: 우리가 학습시키는 파라미터는 수많은 weight와 하나의 bias인데, 각각의 파라미터의 학습 속도가 다르면 전체적인 학습이 불안정할 수 있다.(weight 하나만 발산해도 전체적인 Loss와 Cost가 발산을 하게 되기 때문에 잘못된 학습이 이루어지게 된다.)

$$
Loss\ function\ \ L^{(i)}(\theta) = (y^{(i)} - \theta x^{(i)})^2\\
Loss\ function\ 에\ 대한\ gradient\ descent=>\ \theta = \theta - \alpha\frac{\partial L^{(i)}(\theta)}{\partial \theta}
$$

$$
Cost\ function\ \ J^{(i)}(\theta) =\frac{1}{n}\sum_{i=1}^{n} (y^{(i)} - \theta x^{(i)})^2\\
Cost\ function\ 에\ 대한\ gradient\ descent=>\ \theta = \theta - \alpha\frac{\partial J^{(i)}(\theta)}{\partial \theta}
$$

실제 최적화는 cost function의 개형을 알지 못하는 상황에서 특정 point의 gradient만 보고 theta를 업데이트 시켜야 한다.

**입력 데이터가 n개일때의 gradient descent method for theta**

이미지 9

- Loss에 대해서

  이미지 10

- Cost에 대해서

  이미지 11



텐서플로우에서 손실 함수를 최소화하기 위해 조금씩 variable들을 변경해주는 optimizer을 제공한다.

### 종류

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

$$
\frac{\partial}{\partial \theta_1}Cost(\theta_0, \theta_1) = \frac {\partial}{\partial \theta_1} \frac{1}{2n}\sum_{i = 1}^{n}(\widehat{y_i} - y_i)^2
$$

실제 문제를 다룰 때는 트레이닝 데이터의 개수가 매우 많아질 수 있어 BGD를 사용할 경우 파라미터를 한 스텝 업데이트하는데 많은 시간이 걸리게 된다.(최적의 파라미터를 찾는데 오랜 시간이 걸림)



##### 2.  SGD(Stochastic Gradient Descent)

`tf.optimizers.SGD` : 확률적 경사 하강법(Stochastic Gradient Descent, SGD) optimizer

> 모멘텀과 네스테로프 모멘텀(Nesterov momentum), 그리고 학습률 감소 기법(learning rate decay)을 지원한다.

파라미터를 자주 업데이트 할 수 있지만 파라미터를 한 번 업데이트 할 때 전체 트레이닝 데이터의 특성을 고려하지 않고 각각의 트레이닝 데이터의 특성만을 고려하므로 부정확한 방향으로 업데이트가 진행될 수도 있다.

ex) 선형회귀에서의 손실함수의 미분값
$$
\frac{\partial}{\partial \theta_0}Cost(\theta_0, \theta_1) = \frac {\partial}{\partial \theta_0} \frac{1}{2n}(\widehat{y} - y)^2
$$

$$
\frac{\partial}{\partial \theta_1}Cost(\theta_0, \theta_1) = \frac {\partial}{\partial \theta_1} \frac{1}{2n}(\widehat{y} - y)^2
$$



**Batch Gradient Descent와의 차이**

- BGD(Batch Gradient Descent)
  - 경사하강법의 한 스텝 업데이트를 할 때 모든 데이터를 계산한다 => 소요시간 길다
  - 최적의 한스텝을 나아간다.
  - 6 스텝 * 1시간 = 6시간
  - 확실한데 너무 느리다.
- SGD(Stochastic Gradient Descent)
  - 경사하강법의 한스텝 어베이트를 진행할 때 1개의 트레이닝 데이터만 사용하는 기법 => 소요시간 5분
  - 빠르게 전진한다.
  - 10 스텝 * 5분 => 50분
  - 조금 헤메지만 그래도 빠르게 간다!



![](https://t1.daumcdn.net/cfile/tistory/9961913359D86B9833)

GD의 경우 항상 전체 데이터 셋을 가지고 한발자국 전진할 때마다(learning rate) 최적의 값을 찾아 나아가고 있는 모습을 볼수 있지만, SGD는 Mini-batch 사이즈 만큼 조금씩 돌려서 최적의 값으로 가고 있다. 

그러나 최적값을 찾아 나아가는 과정을 봤을 때는 약간 뒤죽 박죽의 형태로 찾아가지만 속도는 GD 보다 훨씬 빠르다.

**코드**

```python
# 확률적 경사 하강법(Stochastic Gradient Descent, SGD) optimizer 정의
optimizer = tf.optimizers.SGD(a)  # 여기서 a는 learning rate임 (상수여야함) 
```



##### 3. MGB(Mini - Batch Gradient Descent)

 Batch Gradient Dsecent와 Stochastic Gradient Descen의 절충적인 기법으로 **가장 많이 사용된다**.

 MGB는 전체 트레이닝 데이터Batch가 1000(n)개라면 이를 100(m)개씩 묶은 Mini-batch개수만큼 손실 함수 미분값 평균을 이용해서 파라미터 한 스텝을 업데이트 하는 기법

ex) 선형회귀에서의 손실함수의 미분값
$$
\frac{\partial}{\partial \theta_0}Cost(\theta_0, \theta_1) = \frac {\partial}{\partial \theta_0} \frac{1}{2m}\sum_{j = 1}^{m}(\widehat{y_i} - y_i)^2
$$

$$
\frac{\partial}{\partial \theta_1}Cost(\theta_0, \theta_1) = \frac {\partial}{\partial \theta_1} \frac{1}{2m}\sum_{j = 1}^{m}(\widehat{y_i} - y_i)^2
$$

#### 2. Adam

기본 SGD를 조금 더 발전시킨 optimizer라고 생각하면 됨

RMSprop의 특징인 gradient의 제곱에 지수평균한 값을 사용하며 Momentum의 특징으로 gradient를 제곱하지 않은 값을 사용하여 지수평균을 구하고 수식에 활용한다.

기본 SGD은 미분값이 0이 되는 지점에서 더 나아가지 못하지만, Adam은 미분값이 0인 지점을 넘어서 계속해서 탐색한다.

> 2차 함수와 같은 형태는 미분값이 0인 지점이 2개이기 때문에 더 나아가는 최적화가 필요하다.



#### 3. RMSprop

RMSProp 은 아다그라드의 G(t)의 값이 무한히 커지는 것을 방지하고자 제안된 방법으로, 기울기를 단순 누적하지 않고 지수 가중 이동 평균 Exponentially weighted moving average 를 사용하여 최신 기울기들이 더 크게 반영되도록 하였다.

> 지수 이동 평균: 최근 값을 더 잘 반영하기 위해 최근 값과 이전 값에 각각 가중치를 주어 계산하는 방법

