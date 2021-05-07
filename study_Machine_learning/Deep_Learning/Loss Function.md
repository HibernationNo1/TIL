# Loss Function

Loss Function이란? 

적절한 파라미터값을 알아내기 위해서는 현재 파라미터값이 우리가 풀고자 하는 목적에 적합한 값인지 측정이 가능해야 한다. 이를 수학적으로 표현한 것이 Loss Function이다. 

정답(Label data)을 목표로 두고 Training data가 자신의 위치와 Label data위치의 '차이'를 인지하고그 차이를 좁혀 나가는 방식으로 기계 학습이 이루어 지는데, 여기서 말하는 '차이'가 바로 Loss Function이라고 이해하면 된다.

> 예시)
>
> H(W, b) = Wx+b라는 식이 있을 때
>
> W =  2 이고 b = 1인, 즉 y = 2x+1인 함수를 컴퓨터에게 학습시키는 과정에서
>
> 임의로 전달된 W와 b가 정답과는 얼마나 다른지를 알려주는 함수를 **Loss Function(손실함수)** 라고 한다.

- Cost: Loss들의 평균 값

  > 예시 - 평균제곱오차에서 
  >
  > Loss: 실제 y값과 prediction value와의 차이 Loss는 (y-y')에 제곱을 취해준다. Loss값은 양수여야 하기 때문이다.
  >
  > loss값이 2차 함수이기 때문에 cost function는 밥그릇 같은 그래프가 형성되고, cost function이 가장 적으려면 함수의 기울기가 0이 되는 지점이여야 한다. (cost function이 크다는 것은 예측값과 정답값의 오차가 크다는 것이다.)
  > $$
  > Loss = (y^{(i)} - (wx^{(i)}+b))^2 \\ Cost = \frac{1}{n} \sum_{i=1}^{n}(y^{(i)} - (wx^{(i)}+b))^2
  > $$
  > 위의 두 식은 weight가 1개, bias가 1개인 2차 식임을 알 수 있다.`y'`는 아래처럼 벡터로 표현될 수 있다.)
  > $$
  > Loss = (y^{(i)} - \overrightarrow{\theta^T}\overrightarrow{x}^{(i)})^2 \\ Cost = \frac{1}{n} \sum_{i=1}^{n}(y^{(i)} - \overrightarrow{\theta^T}\overrightarrow{x}^{(i)})^2
  > $$
  >
  > $$
  > 여기서\ \overrightarrow{\theta^T} = (\theta_0,\ \theta_1,\ \theta_2,\ \theta_3)이고\\
  > \theta_0 = b,\ \ (\theta_1,\ \theta_2,\ \theta_3) = \overrightarrow{w} 이라면\\ 
  > Loss와\ Cost는\ \theta_0,\ \theta_1,\ \theta_2,\ \theta_3에\ 대한\ 2차 함수이다.\\
  > 즉,\ 4차원\ 공간에서\ 아래로\ 볼록한\ 모양의\ 함수라는\ 것을\ 알\ 수\ 있다.
  > $$
  >
  > 이 때 b != 0 인 함수를 affine function(아핀 함수)이라고 한다.



- 추가

  y'에 activation function과 affine function이 둘 다 포함된다면 이를 **Logistic Regression**(LOR)이라고 한다.

  affine function만 포함되어 있으면 **Linear Regression**이라고 한다. 

  > y'가 다변수이면 Multi-variate Linear Regression(MVLR) 이라고 하고
  >
  > y'가 변수값 하나에만 영향을 받으면 single-variate Linear Regression(SVLR) 이라 한다.

  y'의 변수가 하나이고, b = 0이면 single-variate Linear Regression Without Bias Term (SVLR Without Bias Term)이라고 한다.





>  cost function 4차 함수와 같이 기울기가 0인 지점이 2개 이상인 그래프를 그린다면, 기울기가 0인 지점을 지나서 다시 기울기가 0이며 함수값이 가장 적은 지점을 찾아야 한다.
>
> 아래 그래프는 전부 y>0 이라는 가정 하에 예를 든다,

![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcQ5BZAzwyJ88eEujeYBzXGlrzH_saUt4mRb_w&usqp=CAU)



## 종류

### 1. MSE

머신러닝 뿐만 아니라 영상처리 영역에서도 자주 사용되는 **추측값에 대한 정확성 측정 방법**이다. 

간단히 말하면 오차의 제곱에 대해 평균을 취한 것이다. 

Regression에서 사용된다.
$$
Loss  = (y - \widehat{y})^2
\\ Cost = \frac {1} {n} \sum_{j=1}^{n}(y^{(i)} - \widehat{y}^{(i)})^2
$$

$$
y: 참값, \ \ \widehat{y}: 모델의\ 예측\ 값
$$



**code implementation**

slmple ver

```python
import tensorflow as tf

from tensorflow.keras.losses import MeanSquaredError

loss_object = MeanSquaredError()

batch_size = 32

predictions = tf.random.normal(shape = (batch_size, 1))
labels = tf.random.normal(shape = (batch_size, 1))

mse = loss_object(labels, predictions)
```



with Model, dataset

```python
import tensorflow as tf

from tensorflow.keras.layers import Dense
from tensorflow.keras.losses import MeanSquaredError

N, n_feature = 100, 5
batch_size = 32

X = tf.random.normal(shape = (N, n_feature))
Y = tf.random.normal(shape = (N, 1))

dataset = tf.data.Dataset.from_tensor_slices((X, Y))
dataset = dataset.batch(batch_size)

model = Dense(units = 1, activation = 'linear')
loss_object = MeanSquaredError()

for x, y in dataset:
    predictions = model(x)
    loss = loss_object(y, predictions)
    print(loss.numpy())
```





### 2. BCE

**Binary Cross Entropy** Function은 모델의 예측값이 참값과 비슷하면 작은 값, 참값과 다르면 큰 값을 갖는 형태의 함수로 나타내 수 있다.

BCE는 data를 두 개의 class로 구분해서 나누는 학습을 할 때 사용된다.
$$
Loss =-[y log(\widehat{y}) + (1 - y)log(1 - \widehat{y})]\\
Cost = -\sum_{i=1}^{N}[y^{(i)}log(\widehat{y}^{(i)}) + (1-y^{(i)})log(1-\widehat{y}^{(i)})]
$$

$$
y: 참값, \ \ \widehat{y}: 모델의\ 예측\ 값
$$

BCE Function은 data를 Logit으로 가정하고 Label에 Ont-hot encoding을 적용하여 x_data가 0인지 1인지에 대한 probability를 결정하는 방식의 Classification을 수행할 때 사용한다.

> y = 0이면 (정답이 아니면) Loss가 증가한다.



**code implementation**

simple ver

```python
import tensorflow as tf

from tensorflow.keras.losses import BinaryCrossentropy

batch_size = 32
n_class = 2

predictions = tf.random.uniform(shape = (batch_size, 1), 
                                minval = 0, maxval = 1, 
                                dtype = tf.float32)

labels = tf.random.uniform(shape = (batch_size, 1), 
                                minval = 0, maxval = n_class, 
                                dtype = tf.int32)

loss_object = BinaryCrossentropy()
loss = loss_object(labels, predictions)

print(loss.numpy())
```



with Model, dataset

```python
import tensorflow as tf

from tensorflow.keras.layers import Dense
from tensorflow.keras.losses import BinaryCrossentropy

N, n_feature = 100, 5
batch_size = 32

t_weights = tf.constant([1, 2, 3, 4, 5], dtype = tf.float32)
t_bias = tf.constant([10], dtype = tf.float32)

X = tf.random.normal(mean = 0, stddev = 1, shape = (N, n_feature))
Y = tf.reduce_sum(t_weights*X, axis = 1) + t_bias
Y = tf.cast(Y>5, tf.int32)  # Dicision Boundary = 5

dataset = tf.data.Dataset.from_tensor_slices((X, Y))
dataset = dataset.batch(batch_size)

model = Dense(units = 1, activation = 'sigmoid')
loss_object = BinaryCrossentropy()

for x, y in dataset:
    predictions = model(x)
    loss = loss_object(y, predictions)
    print(loss.numpy())
```





### 3. CCE

**Categorical Cross Entropy** Function은 data를 두 개 이상의, 여러개의  class로 classification 할 때 사용하는 Loss Function이다.  (그냥 Cross Entropy라고 불리기도 한다.)
$$
Loss = H(\vec{y}, \vec{\widehat{y}}) =  - \sum_{i=1}^{K} y_i log(\widehat{y}_i)
\\Cost = H(Y^T, \widehat{Y}^T) = -\frac{1}{N}\sum_{i=1}^{N}\sum_{j=1}^{K} y^{(i)}_j log(\widehat{y}^{(i)}_j)
$$
Label data는 one-hot encoding이 적용된 data가 입력된다.



- label data
  $$
  (\overrightarrow{y}^{(1)})^T = (1 \ 0 \ .. 0), \ \alpha = 1 \\
  (\overrightarrow{y}^{(2)})^T = (0 \ 1 \ .. 0), \ \alpha = 2 \\
  \vdots\\
  (\overrightarrow{y}^{(K)})^T = (0 \ 0 \ .. 1), \ \alpha = K \\
  $$

- predicts
  $$
  (\vec{\widehat{y}})^T = (\widehat{y}_1\ \widehat{y}_2\ \dots \ \widehat{y}_K) \ \ \ \  0\leq \widehat{y}_i \leq 1\\ 
  = (P(C_1), P(C_2),\ \dots,\ P(C_K) )
  $$

즉, (0 0 0 1) 이라는 Label에 의해 CCE는
$$
H = -log(\widehat{y}_4) = -log(P(C_4))
$$


**code Implementation**

simple ver

```python
import tensorflow as tf

from tensorflow.keras.losses import CategoricalCrossentropy

batch_size, n_class= 16, 5

predictions = tf.random.uniform(shape = (batch_size, n_class), 
                                minval = 0, maxval = 1, 
                                dtype = tf.float32)
pred_sum = tf.reshape(tf.reduce_sum(predictions, axis = 1), (-1, 1))
predictions = predictions / pred_sum
# to make the sum of predictions to 1

labels = tf.random.uniform(shape = (batch_size, ), 
                                minval = 0, maxval = n_class, 
                                dtype = tf.int32)

labels = tf.one_hot(labels, n_class)
# print(labels)

loss_object = CategoricalCrossentropy()
loss = loss_object(labels, predictions)
print(loss.numpy())  

# or
loss = tf.reduce_mean(tf.reduce_sum(-labels*tf.math.log(predictions), axis = 1))
print(loss.numpy()) # same loss
```



with model, dataset

```python
import tensorflow as tf

from tensorflow.keras.layers import Dense
from tensorflow.keras.losses import CategoricalCrossentropy

N, n_feature = 16, 2 
n_class = 5
batch_size = 16

X = tf.zeros(shape = (0, n_feature))
Y = tf.zeros(shape = (0, ), dtype = tf.int32)

for class_idx in range(n_class):
    center = tf.random.uniform(minval = -15, maxval = 15, shape = (2, ))

    x1 = center[0] + tf.random.normal(shape = (N, 1))
    x2 = center[1] + tf.random.normal(shape = (N, 1))

    x = tf.concat((x1, x2), axis = 1)   # [x1, x2]
    y = class_idx*tf.ones(shape = (N, ), dtype = tf.int32)  # for expression number of class

    X = tf.concat((X, x), axis = 0)
    Y = tf.concat((Y, y), axis = 0)

Y = tf.one_hot(Y, depth = n_class, dtype = tf.int32)


dataset = tf.data.Dataset.from_tensor_slices((X,Y))
dataset = dataset.batch(batch_size)

model = Dense(units = n_class, activation = 'softmax')
loss_object = CategoricalCrossentropy()



for x, y in dataset:
    predictions = model(x)
    loss = loss_object(y, predictions)
    print(loss.numpy())
```







##### SCCE

Sparse Caregorical Cross Entropy

categorical cross entropy(CCE) and sparse categorical cross entropy(SCCE) have the same loss function. The only difference is the format labels.

if One-hot encoding is not applied, use SCCE. On the ather hand, use CCE if One-hot encoding applied. 



**code Implementation**

simpe ver

```python
import tensorflow as tf

from tensorflow.keras.losses import SparseCategoricalCrossentropy

batch_size, n_class= 16, 5

predictions = tf.random.uniform(shape = (batch_size, n_class), 
                                minval = 0, maxval = 1, 
                                dtype = tf.float32)
pred_sum = tf.reshape(tf.reduce_sum(predictions, axis = 1), (-1, 1))
predictions = predictions / pred_sum
# to make the sum of predictions to 1

labels = tf.random.uniform(shape = (batch_size, ), 
                                minval = 0, maxval = n_class, 
                                dtype = tf.int32)

print(labels)  # not applied ont-hot encoding
loss_object = SparseCategoricalCrossentropy()
loss = loss_object(labels, predictions)

print(loss.numpy())

cross_etropy = 0
for label, prediction in zip(labels, predictions): 
    ce += -tf.math.log(prediction[label])
ce /= batch_size  # cost 
print(ce.numpy())
```



with model, dataset

```python
import tensorflow as tf

from tensorflow.keras.layers import Dense
from tensorflow.keras.losses import SparseCategoricalCrossentropy

N, n_feature = 32, 2 
n_class = 3
batch_size = 16

X = tf.zeros(shape = (0, n_feature))
Y = tf.zeros(shape = (0, 1), dtype = tf.int32)

for class_idx in range(n_class):
    center = tf.random.uniform(minval = -15, maxval = 15, shape = (2, ))

    x1 = center[0] + tf.random.normal(shape = (N, 1))
    x2 = center[1] + tf.random.normal(shape = (N, 1))

    x = tf.concat((x1, x2), axis = 1)   # [x1, x2]
    y = class_idx*tf.ones(shape = (N, 1), dtype = tf.int32)  # for expression number of class

    X = tf.concat((X, x), axis = 0)
    Y = tf.concat((Y, y), axis = 0)

dataset = tf.data.Dataset.from_tensor_slices((X,Y))
dataset = dataset.batch(batch_size)

model = Dense(units = n_class, activation = 'softmax')
loss_object = SparseCategoricalCrossentropy()

for x, y in dataset:
    predictions = model(x)
    loss = loss_object(y, predictions)
    print(loss)
```

