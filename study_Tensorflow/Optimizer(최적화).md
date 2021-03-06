# Optimizer

텐서플로우에서 손실 함수를 최소화하기 위해 조금씩 variable들을 변경해주는 optimizer을 제공한다.

(가장 간단한 optimizer(최적화)는 gradient descent(경사하강법)다.)



### 종류

#### 1. 경사하강법

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

