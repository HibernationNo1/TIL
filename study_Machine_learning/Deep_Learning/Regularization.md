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



## 드롭아웃(dropout)

드롭아웃(dropout)운 학습 과정에서 일부 노드를 사용하지 않는 형태로 만들어서 over fitting을 방지할 수 있도록 만들어주는 Regularization 기법이다.

![](https://miro.medium.com/max/1200/1*iWQzxhVlvadk6VAJjsgXgg.png)

각 층마다 Drop할 노드의 비율을 정하고, 매 순환마다 Drop할 노드를 랜덤하게 바꾸면서 학습을 진행한다.

더 적은 노드로(적은 표현력으로) 학습을 시켜야 하기 때문에 모델의 특징이 더욱 효율적이게 되고, 이로 인해 오버피팅을 방지할 수 있게 된다.

트레이닝 데이터에 대해서는 오버피팅을 방지하기 위해 드롭아웃을 수행하지만 테스트 데이터에 대해서는 드롭아웃을 수행하지 않는다.

> 테스트를 진행할 때는 모든 표현력을 전부 사용한다.
>
> Drop 확률을 0으로 지정해서 테스트를 진행한다.



### 코드 구현

Tensorflow에서는 `tf.nn.dropout` API를 제공한다.

```python
tf.nn.dropout(적용할 레이어, 비율, )
```

> dropout의 설정값 중 bool형 값을 training을 통해 dropout적용을 제어할 수 있다.
>
> 트레이닝 데이터에는 dropout을 적용하고, 테스트 데이터에는 dropout을 적용하지 않을때 사용

dropout을 적용한 코드 : [CIFAR-10 이미지 분류를 위한 CNN 구현](https://github.com/HibernationNo1/TIL/blob/master/study_Tensorflow/neural%20network/%EC%BB%A8%EB%B3%BC%EB%A3%A8%EC%85%98%20%EC%8B%A0%EA%B2%BD%EB%A7%9D%20(Convolution%20neural%20network%2C%20CNN).md) 





