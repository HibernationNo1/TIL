# keras.regularizers

regularization을 수행한다.

**keras.regularizers의 객체**

y=Wx+b 일 때

- `kernel_regularizer` : weight를 줄인다
- `bias_regularizer` : bias를 줄인다.
- `activity_regularizer` : y를 줄인다.

weight에 대한 ragularization이 크게 진행 되더라도 function을 modeling이 가능하기 때문에 보통 `kernel_regularizer`를 사용한다.



## L1 regularization

1. layer의 weight에 적용될 때

```python
from tensorflow.keras.regularizers import L1
tf.keras.layers.Dense(512, activation = 'relu', use_bias=True,  kernel_regularizer = L1( l=0.01))
```

`kernel_regularizer = L1( l=0.01)` : weight kernel의 모든 원소의 절대값에 0.01을 곱한 후 network 전체 cost에 더해진다는 의미



2. model의 weight에 적용될 때.

```python
import tensorflow.keras.regularizers as KR
weight = (KR.l2(0.01)(w) / tf.cast(tf.size(w), tf.float32)
			for w in model.trainable_weights
			if 'gamma' not in w.name and 'beta' not in w.name)
```

특정 Model의 instnace인 model의 attribute를 통해 weight를 얻어낸 후 

`KR.l2(0.01)(w)` :  `l = 0.01` 인 L1을 적용하고 전부 더한다.

` /  tf.cast(tf.size(w), tf.float32)` : weight의 size를 나누어 줘야 각 weight에 대한 제대로 된 L1이 적용된다.

`if 'gamma' not in w.name and 'beta' not in w.name` : 해당 weight 중 batch normalization에서 사용되는 weight인 gamma, beta에는 L1을 적용하지 않는다.





## L2 regularization

```python
from tensorflow.keras.regularizers import L2
tf.keras.layers.Dense(512, activation = 'relu', use_bias=True,  kernel_regularizer = L2( l=0.01))
```

`kernel_regularizer = L2( l=0.01)` : weight kernel의 모든 원소의 제곱에 0.01을 곱한 후 network 전체 cost에 더해진다는 의미





## L1 + L2 regularization

```python
from tensorflow.keras.regularizers import L1L2
tf.keras.layers.Dense(512, activation = 'relu', use_bias=True,  kernel_regularizer = L1L2(l1=0.02, l2 = 0.01))
```

`kernel_regularizer = L1L2(l1=0.02, l2 = 0.01)` :  weight kernel의 모든 원소의 절대값에 0.02를 곱하고, weight kernel의 모든 원소의 제곱에 0.01을 곱한 후

network 전체 cost에 더해진다는 의미

