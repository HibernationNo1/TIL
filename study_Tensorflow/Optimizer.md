# Optimizer

텐서플로우에서 손실 함수를 최소화하기 위해 조금씩 variable들을 변경해주는 optimizer을 제공한다.

(가장 간단한 optimizer(최적화)는 gradient descent(경사하강법)다.)



### 종류

#### 1. SGD

`tf.optimizers.SGD` : 확률적 경사 하강법(Stochastic Gradient Descent, SGD) optimizer

> 모멘텀과 네스테로프 모멘텀(Nesterov momentum), 그리고 학습률 감소 기법(learning rate decay)을 지원한다.
> $$
> \theta_{i+1} = \theta_i - \alpha \frac{\partial}{\partial \theta_i}Cost(\theta_0, \theta_1)
> $$

**GD(Gradient Descent)와의 차이**

- GD
  - 모든 데이터를 계산한다 => 소요시간 1시간
  - 최적의 한스텝을 나아간다.
  - 6 스텝 * 1시간 = 6시간
  - 확실한데 너무 느리다.
- SGD
  - 일부 데이터만 계산한다 => 소요시간 5분
  - 빠르게 전진한다.
  - 10 스텝 * 5분 => 50분
  - 조금 헤메지만 그래도 빠르게 간다!



**단점** 

- 미니 배치를 통해 학습을 시키는 경우 최적의 값을 찾아 가기 위한 방향 설정이 뒤죽 박죽이다.

- learning rate가 낮으면 학습하는데 오래 걸리고, 너무 크면 최적의 값을 찾지 못하는 문제가 있다. (GD도 마찬가지)

![](https://t1.daumcdn.net/cfile/tistory/9961913359D86B9833)

GD의 경우 항상 전체 데이터 셋을 가지고 한발자국 전진할 때마다(learning rate) 최적의 값을 찾아 나아가고 있는 모습을 볼수 있지만, SGD는 Mini-batch 사이즈 만큼 조금씩 돌려서 최적의 값으로 가고 있다. 

그러나 최적값을 찾아 나아가는 과정을 봤을 때는 약간 뒤죽 박죽의 형태로 찾아가지만 속도는 GD 보다 훨씬 빠르다.

**코드**

```python
# 확률적 경사 하강법(Stochastic Gradient Descent, SGD) optimizer 정의
optimizer = tf.optimizers.SGD(a)  # 여기서 a는 learning rate임 (상수여야함) 
```

