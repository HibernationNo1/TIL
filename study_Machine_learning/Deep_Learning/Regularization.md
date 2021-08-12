# Regularization

OverFitting을 방지할 수 있도록 만들어주는 기법들을 총칭해서 Regularization라고 한다.

- 오버피팅: 학습 과정에서 머신러닝 알고리즘의 파라미터가 트레이닝 데이터에 과도하게 최적화되어 트레이닝 데이터에 대해서는 잘 동작하지만 새로운 데이터인 테스트 데이터에 대해서는 잘 동작하지 못하는 현상.

  (모델이 범용적으로 좋은 방향으로 개선되는것이 아닌, 트레이닝만을 위한 방향으로 개선되는 것

  ![](https://shryu8902.github.io/assets/images/overfit1.png)

- 언더피팅(underfitting): 오버피팅의 반대 상황으로 모델의 표현력이 부족해서 트레이닝 데이터도 제대로 예측하지 못하는 현상



##### Large Dataset

model의 차수가 높아 모든 noise를 정확하게 학습하는 over fitting의 문제를 해결하기 위해, data set에  data의 개수를 더욱 많이 포함시켜서 model의 차수가 data set의 noise를 정확히 캐치하지 못하게 하는 방법이다. (Regularization 기법은 아님)



딥러닝의 경우 모델의 표현력이 강력하기 때문에 오버피팅에 빠지기 쉽기 때문에 오버피팅 문제를 완화하기 위해서 **드롭아웃(dropout)**과 같은 다양한 Regularization 기법을 사용한다.

>  드롭 아웃(Dropout)은 대표적인 Regularization 기법중에 하나임.



## dropout

드롭아웃(dropout)운 학습 과정에서 일부 노드를 사용하지 않는 형태로 만들어서 over fitting을 방지할 수 있도록 만들어주는 Regularization 기법이다.

![](https://miro.medium.com/max/1200/1*iWQzxhVlvadk6VAJjsgXgg.png)

각 층마다 Drop할 노드의 비율을 정하고, 매 순환마다 Drop할 노드를 랜덤하게 바꾸면서 학습을 진행한다.

더 적은 노드로(적은 표현력으로) 학습을 시켜야 하기 때문에 모델의 특징이 더욱 효율적이게 되고, 이로 인해 오버피팅을 방지할 수 있게 된다.

트레이닝 데이터에 대해서는 오버피팅을 방지하기 위해 드롭아웃을 수행하지만 테스트 데이터에 대해서는 드롭아웃을 수행하지 않는다.

> 테스트를 진행할 때는 모든 표현력을 전부 사용한다.
>
> Drop 확률을 0으로 지정해서 테스트를 진행한다.



### tf.nn.dropout

Tensorflow에서는 `tf.nn.dropout` API를 제공한다.

```python
tf.nn.dropout(layer, rate)
```

> dropout의 설정값 중 bool형 값을 training을 통해 dropout적용을 제어할 수 있다.
>
> 트레이닝 데이터에는 dropout을 적용하고, 테스트 데이터에는 dropout을 적용하지 않을때 사용

dropout을 적용한 코드 : [CIFAR-10 이미지 분류를 위한 CNN 구현](https://github.com/HibernationNo1/TIL/blob/master/study_Tensorflow/neural%20network/%EC%BB%A8%EB%B3%BC%EB%A3%A8%EC%85%98%20%EC%8B%A0%EA%B2%BD%EB%A7%9D%20(Convolution%20neural%20network%2C%20CNN).md) 







## Regularizer

**Norm**이란?

Norm 은 벡터의 크기(혹은 길이)를 측정하는 방법(혹은 함수)이다.

- L1 Norm

  두 벡터간의 elements 차이의 절대값의 합

  >p =(3, 1, -3), q = (5, 0, 7) 이라면 p, q의 L1 Norm 은
  >
  >|3-5| + |1-0| + |-3 -7| = 2 + 1 + 10 = 13

- L2 Norm

  두 벡터간의 유클리디안 거리(직선 거리)

**L1 Norm 과 L2 Norm 의 차이**

![](https://ichi.pro/assets/images/max/724/1*oByZreebXMIHHST2YytAKg.png)

검정색 두 점사이의 L1 Norm 은 빨간색, 파란색, 노란색 선으로 표현 될 수 있고, L2 Norm 은 오직 초록색 선으로만 표현될 수 있다. L1 Norm 은 여러가지 path 를 가지지만 L2 Norm 은 Unique shortest path 를 가진다.



Regularizer는 Cost function에 weight에 대한 값을 더해주는 것으로, 가중치가 너무 크지 않는 방향으로 학습 되도록 한다. 이를 Weight decay 라고 한다.

### L1 regularization

$$
Cost = \frac{1}{n} \sum{  \left( Cost + \frac{\lambda}{2}|w|\right)   }
$$

Cost function에 weight의 절대값 을 더해주는 것이다. 가중치의 절댓값에 비례하는 비용이 추가되는 것이다.(가중치의 L1 norm)

편미분을 하면 w값은 상수값이 되어버리고, 그 부호에 따라 +-가 결정된다. 즉, 가중치가 너무 작은 경우는 상수 값에 의해서 weight가 0이 되어버리고 결과적으로 몇몇 중요한 가중치 들만 남게된다.



선형 회귀 모델에서 L1 규제 를 주는 것이 **lasso regression** 



### L2 Regularization

$$
Cost = \frac{1}{n} \sum{  \left( Cost + \frac{\lambda}{2}|w|^2\right)   }
$$

Cost function에 weight의 제곱을 더해준다. 

가중치의 제곱에 비례하는 비용이 추가되는 것이다.(가중치의 L2 norm)

편미분을 하면 Cost 뿐만 아니라 가중치 또한 줄어들게 된다. 즉, 가중치가 비이상적으로 커지는 상황을 방지하며 전체적으로 가중치를 작아지게 하는 것이다.



선형 회귀 모델에서 L2 규제 를 주는 것이 **Ridge regression** 



**L1 Regularization, L2 Regularization 의 차이와 선택 기준**

L2 Norm 은 각각의 벡터에 대해 항상 Unique 한 값을 내지만, L1 Norm 은 경우에 따라 특정 Feature(벡터의 요소) 없이도 같은 값을 낼 수 있다는 뜻이다. 이런 특징이 L1 Regularization, L2 Regularization 사이에도 적용된다. 그렇기 때문에 L1 은 Sparse model(coding) 에 적합하다.

 

| 제약식   | L2 norm                            | L1 norm                        | L1 +L2 norm                           |
| -------- | ---------------------------------- | ------------------------------ | ------------------------------------- |
| 변수선택 | 불가능                             | 가능                           | 가능                                  |
| solution | closed form                        | 명시해 없음                    | 명시해 없음                           |
| 장점     | 변수간 상관관계가 높아도 좋은 성능 | 변수간 상관관계가 높으면 성능↓ | 변수간 상관관계를 반영한 정규화       |
| 특징     | 크기가 큰 변수를 우선적으로 줄임   | 비중요 변수를 우선적으로 줄임  | 상관관계가 큰 변수를 동시에 선택/배제 |
