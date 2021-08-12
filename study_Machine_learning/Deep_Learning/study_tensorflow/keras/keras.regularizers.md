# keras.regularizers

regularization을 수행한다.

**keras.regularizers의 객체**

y=Wx+b 일 때

- `kernel_regularizer` : weight를 줄인다
- `bias_regularizer` : bias를 줄인다.
- `activity_regularizer` : y를 줄인다.

weight에 대한 ragularization이 크게 진행 되더라도 function을 modeling이 가능하기 때문에 보통 `kernel_regularizer`를 사용한다.



## L1 regularization

```python
from tensorflow.keras.regularizers import L1
tf.keras.layers.Dense(512, activation = 'relu', use_bias=True,  kernel_regularizer = L1( l=0.01))
```

`kernel_regularizer = L1( l=0.01)` : weight kernel의 모든 원소의 절대값에 0.01을 곱한 후 network 전체 cost에 더해진다는 의미



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

