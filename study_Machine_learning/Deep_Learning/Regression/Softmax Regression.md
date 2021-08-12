# Softmax Regression(소프트맥스 회귀)

소프트맥스 회귀는 n개의 레이블을 분류하기 위한 가장 기본적인 모델이다. 

모델의 output에 Softmax함수를 적용해서 모델의 출력값이 각각의 레이블에 대한 확인의 정도를 출력하도록 만들어주는 기법이다.

> Softmax함수는 Normalization 함수로써 출력값들의 합을 1로 만들어준다. 
> $$
> 수식\ : \ \ Softmax(x_i) == P(C_i) = \frac{e^{l(C_i)}}{\sum_{j=1}^{K}e^{l(C_j)}}
> $$
> 출력값으로 나온 모든 확률을 더하면 1이 되는 것이다.



#### Softmax 수식 유도

Softmax 수식
$$
Softmax(x_i) == P(C_i) = \frac{e^{l(C_i)}}{\sum_{j=1}^{K}e^{l(C_j)}}
$$


class가 여러개일 때
$$
C = \{C_1, C_2, ..., C_k\} \\
P(C_1), P(C_2),...,P(C_k)  \\
P(C_1)+P(C_2)+...+P(C_k) = 1 \\
l(C_1), l(C_2),...,l(C_k)
$$
일 때
$$
(1) \ \ \ \ \ \  l(C_i) = ln \left( \frac{P(C_i)}{P(C_K)} \right)\\
k =  임의의\ 수 \ \ \ \ \ \ \ \ \ \ \ \ \ i = k 가\ 아닌\ 임의의\ 수
$$

$$
(2) \ \ \ \ \ \ l(C_i) = ln \left( \frac{P(C_K)}{P(C_K)} \right) =1
$$

(1)양 변의 값을 exp의 지수로 올리면
$$
(3)\ \ \ \ \ \ e^{l(C_i)} = e^{ln \left( \frac{P(C_i)}{P(C_K)} \right)} = \frac{P(C_i)}{P(C_K)}
$$

$$
(5)\ \ \ \ \ \  e^{l(C_k)} = 1\\
(6)\ \ \ \ \ \  p(C_i) = e^{l(C_i)}P(C_K)
$$

(3)에 i를 제외한 모든 수를 더하는 sum을 취하면
$$
\sum_{j=1}^{K-1}e^{l(C_i)}  = \sum_{j=1}^{K-1}\frac{P(C_i)}{P(C_K)} = \frac{1-P(C_K)}{P(C_K)} = \frac{1}{P(C_K)}-1\\
1 + \sum_{j=1}^{K-1}e^{l(C_i)}  = \frac{1}{P(C_K)}\\
P(C_K) = \frac{1}{1 + \sum_{j=1}^{K-1}e^{l(C_i)}}
$$
여기서 1에 (5)를 대입한다면
$$
P(C_K) = \frac{1}{e^{l(C_k)} + \sum_{j=1}^{K-1}e^{l(C_i)}} = \frac{1}{\sum_{j=1}^{K}e^{l(C_i)}}
$$
그리고 이 값을 (6)에 대입하면
$$
\frac{e^{x_i}}{\sum_{k=1}^{K}e^{x_i}} = Softmax(x_i)
$$
Softmax 수식이 나옴을 알 수 있다.

**즉, C_i 에 대한 Logit을 C_i에 대한 확률로 표현을 한 것이 Softmax Function이다.**

> 위의 식에서 알 수 있듯, P(C_k)는 어짜피 사라지기 때문에 K에 어떤 수를 넣는다 해도 상관이 없다.
>
>  Softmax Function 의 input은 Logit(C_i)고, output은 Pass(C_i)임을 알 수 있다.



Affine Function에서 받은 Logit을 Sigmoid Function에 대입하고 이를 Cross Entropy  Loss Function에 대입하는 과정이 바로 Single Variate Softmax Regression이다.



#### 요약

Softmax함수를 씌우게 되면 모델의 출력값이 레이블에 대한 확률을 나타내게 된다.(출력값들의 합이 1이 되므로)

**회귀 구조**

![](http://aidev.co.kr/files/attach/images/186/841/9d980c2c870140d5b4aedea73036b97d.png)

![](https://resources.codeonweb.com/bucket/cached/19/a0/19a03ef08b6bc80a9b65d5891fb5afea.png)



Logits 에 Softmax함수를 적용하면 sum to 1 형태로 output값을 정리해주기 때문에 이를 확률적 개념으로 이해할 수 있게 된다.



- Softmax 회귀를 비롯한 분류 문제에는 크로스 엔트로피(Cross-Entropy) 손실함수를 많이 사용한다.
- softmax 활성화 함수는 다중 클래스 분류 시 사용한다.



#### 코드로 설명

```python
import tensorflow as tf
from tensorflow.feras.layers import Activation

logit = tf.random.uniform(shape = (1, 5), minval = -10, maxval = 10)
# 5개 class에 대한 1개의 data semple

softmax_value = Acivation('softmax')(logit)
softmax_sum = tf.reduce_sum(softmax_value, axis = 1)

print("Logits: ", logit.numpy())				
print("probabilities: ", softmax_value.numpy())	# 각 확률의 값
print("Sum of softmax values", softmax_sum)		# 모든 확률의 합 = 1에 가까운 값 
```



use Dense

```python
import tensorflow as tf
from tensorflow.feras.layers import Dense

logit = tf.random.uniform(shape = (1, 5), minval = -10, maxval = 10)
# 5개 class에 대한 1개의 data semple

dense = Dense(units = 8, activation = 'softmax')

Y = dense(logit)
```



## 코드 구현(Multi-class Classifier)

```python
import tensorflow as tf

from tensorflow.keras.models import Model
from tensorflow.keras.layers import Dense

class TestModel(Model):
    def __init__(self): 
        super(TestModel, self).__init__()

        self.dense1 = Dense(units = 8, activation = 'relu')
        self.dense2 = Dense(units = 5, activation = 'relu')
        self.dense3 = Dense(units = 3, activation = 'softmax') # 3개의 class를 분류
        # 마지막 layer에만 softmax activation 적용

    def call(self, x):
        print(f"X: {x.shape} \n, {x.numpy()} \n")

        x = self.dense1(x)
        print(f"X: {x.shape} \n, {x.numpy()} \n")
        
        x = self.dense2(x)
        print(f"X: {x.shape} \n, {x.numpy()} \n")

        x = self.dense3(x)
        print(f"X: {x.shapee} \n, {x.numpy()} \n")
        print(f"sum of vectors {tf.reduce_sum(x, axis = 1)}\n")
        return x

model = TestModel()

X = tf.random.uniform(shape = (8, 5), minval = -10, maxval = 10)
Y = model(X)
```

출력을 확인해보면 

x_data

```
X: (8, 5)
, [[ 5.078247    3.6812572   3.4688902   5.475504   -0.49888134]
 [ 9.259651   -7.1174836  -4.874556   -0.02946663  4.761875  ]
 [-2.8033328  -0.3299408  -5.08451     7.5884285  -5.276699  ]
 [ 8.864445   -6.3580728   9.760931   -6.574049   -3.9082956 ]
 [-6.299641   -3.3285165   9.284933   -5.502827    8.822647  ]
 [-6.6491866   9.026583    4.260845   -0.25538635 -1.7791634 ]
 [-8.961771    5.297777   -1.611619   -4.9916863  -0.76620865]
 [-3.5544968   4.3313484  -8.299551   -2.9858947   6.3275375 ]]
```



dense layer 1을 통과한 x_data

```
X: (8, 8) 
, [[3.2006586  0.         4.0548368  1.0098346  0.         0.
  3.2924485  3.266006  ]
 [4.2121015  6.4383445  0.         0.         0.         0.
  3.5497625  7.691199  ]
 [1.530852   4.000815   1.17051    0.         0.         5.9650645
  0.         0.        ]
 [0.         3.700261   0.         6.5730233  7.506935   0.
  7.352618   2.9707932 ]
 [0.         0.         1.2863406  0.         0.         0.
  4.681222   0.69082844]
 [0.         0.         3.055755   3.1548195  1.9683249  1.2204959
  0.         0.        ]
 [0.         0.         0.         2.2302346  1.4577997  3.5814095
  0.         0.        ]
 [5.1651783  0.         5.0865903  0.         0.         2.9486299
  0.         0.        ]]
```

> 8개의 neuron으로 인해 8개의 cols가 된 것을 볼 수 있다.



dense layer 2을 통과한 x_data

```
X: (8, 5)
, [[0.         0.         2.719185   1.7694728  1.6167226 ]
 [3.0043662  0.         4.4817557  2.9345589  8.16365   ]
 [2.9774191  0.         3.731237   0.         0.        ]
 [4.254131   0.         5.178421   4.306243   7.3503237 ]
 [0.5648164  0.09151176 1.4998931  0.14860022 0.12280792]
 [0.         0.         2.1814466  0.81757444 0.10802191]
 [1.505584   0.         0.5333323  0.         0.        ]
 [0.         0.         3.1576104  0.03980994 0.        ]]
```

> 5개의 neuron으로 인해 5개의 cols가 된 것을 볼 수 있다.



dense layer 3을 통과한 x_data

```
X: (8, 3)
, [[0.2801364  0.4297622  0.29010132]
 [0.06073103 0.11108198 0.828187  ]
 [0.171719   0.71279705 0.11548404]
 [0.10346349 0.59419924 0.3023372 ]
 [0.31862938 0.39301965 0.28835097]
 [0.30660465 0.46553043 0.22786494]
 [0.27897632 0.51202065 0.20900299]
 [0.28445974 0.37455374 0.34098658]]
```

> 3개의 neuron으로 인해 3개의 cols가 된 것을 볼 수 있다.

그리고 위 출력을 각 cols기준으로 더해보면 1의 값이 나오는걸 확인할 수 있다.

```
sum of vectors [0.9999999  1.         1.0000001  0.9999999  1.         1.
 0.99999994 1.0000001 ]
```





## 코드 구현(MNIST classifier)

1. MNIST 데이터 받아와서 batch단위로 묶기
2. 가설정의
3. 손실함수 정의
4. 최적화 정의
5. 테스트 정의

#### 코드 설명

##### 1. MNIST 데이터 받아와서 batch단위로 묶기

```python
(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data() 
x_train, x_test = x_train.astype('float32'), x_test.astype('float32') 
x_train, x_test = x_train.reshape([-1, 784]), x_test.reshape([-1, 784])
x_train, x_test = x_train / 255., x_test / 255.
y_train, y_test = tf.one_hot(y_train, depth=10), tf.one_hot(y_test, depth=10)

train_data = tf.data.Dataset.from_tensor_slices((x_train, y_train))
train_data = train_data.repeat().shuffle(60000).batch(100)
train_data_iter = iter(train_data)
```

**우리가 가진 dataset을 batch단위로 묶는 과정**

1. tf.data API를 이용해서 데이터를 섞고 batch 형태로 가져온다.

   `train_data = tf.data.Dataset.from_tensor_slices((x_train, y_train))`

   > tf.data.dataset: mini-batch단위로 묶는 과정을 손쉽게 수행할 수 있도록 제공하는 class 
   >
   > from_tensor_slices(사용할 전체 데이터)

   `train_data = train_data.repeat().shuffle(60000).batch(100)`

   > batch: tf.data.dataset 내부의 메서드. 묶고싶은 mini-batch 단위 지정 가능
   >
   > shuffle: 한 번 에폭이 끝날때마다 데이터를 섞어주는 함수

2.  이후 next()함수를 이용해서 mini-batch를 순차적으로 가져와서 학습에 사용할 수 있도록 함

   `train_data_iter = iter(train_data)`

   > iter()을 사용하면 next()함수를 이용해서 mini-batch를 순차적으로 가져와서 학습에 사용할 수 있도록 한다.
   >
   > for문으로도 가능

##### 2. 가설정의

**tf.keras.Model을 이용해서 Softmax Regression 모델을 정의**

```python
# 케라스 서브클래싱
class SoftmaxRegression(tf.keras.Model):  #클래스 생성 후 tf.keras.Model을 상속
    def __init__(self): #생성자
        super(SoftmaxRegression, self).__init__()
        # super: tf.keras.Model의 생성자를 호출해주는 메서드
        self.softmax_layer = tf.keras.layers.Dense(10, activation = None, kernel_initializer='zeros', bias_initializer='zeros')
        
        def call(self, x):
        	logits = self.softmax_layer(x)
        	return tf.nn.softmax(logits)
```

> `self.softmax_layer = tf.keras.layers.Dense(10, activation = None, kernel_initializer='zeros', bias_initializer='zeros')`: **만들고자 하는 모델 구조 정의해서 멤버 변수에 할당** (tf.keras.layers의 하위 API 중 Dense 지정해서 사용 )
>
> Dense API는 y = Wx+b 형태의 모델에 여러 activation을 적용해주는 API
>
> - 1번째 인자값: 내가 받고자 하는 output 크기 (784크기를 10의 크기의 softmax 회귀 형태로 변경하는 연산 수행)
> - activation = None  : activation을 적용하지 않음
> - kernel_initializer='zeros': Wx+b 에서 W의 파라미터. 초기값을 0으로 채우겠다. = 초기 이니셜라이지션을 진행을 하겠다.
> - bias_initializer='zeros': Wx+b 에서 b의 파라미터
>
> `def call(self, x):` : 클래스가 호출될때 자동으로 실행됨(인자값으로 input데이터를 받는다.)
>
> `logits = self.softmax_layer(x)` : input데이터를 그래프 끝까지 연산을 수행한 뒤 나오는 연산 결과값(생성자에서 수행)을 변수에 할당.
>
> `return tf.nn.softmax(logits)` : softmax를 구현해주는 tensorflow API를 사용해서 결과값에 softmax를 적용

##### 3. 손실함수 정의

```python
@tf.function
def cross_entropy_loss(y_pred, y): #크로스 엔트로피 손실함수
    return tf.reduce_mean(-tf.reduce_sum(y * tf.math.log(y_pred), axis=[1]))
	# 크로스 엔트로피 식 구현
```

> `return tf.reduce_mean(-tf.reduce_sum(y * tf.math.log(y_pred), axis=[1]))` 대신에 `return tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits = logits, labels = y))`를 사용해도 된다.
>
> - `tf.nn.softmax_cross_entropy`를 사용해서 크로스 엔트로피 손실함수를 사용할 수 있다.
> - `tf.nn.softmax_cross_entropy`를 사용하면 가설 정의 부분에서 call함수의 return값을 logits으로 해줘야 한다. 

##### 4. 최적화 정의

```python
optimizer = tf.optimizers.SGD(0.5)

#최적화를 위한 function을 정의
@tf.function
def train_step(model, x, y):
    with tf.GradientTape() as tape:
        y_pred = model(x)
        loss = cross_entropy_loss(y_pred, y)
    gradients = tape.gradient(loss, model.trainable_variables)
    optimizer.apply_gradients(zip(gradients, model.trainable_variables))
```

> ` optimizer.apply_gradients(zip(gradients, model.trainable_variables))`: 
>
> - tf.keras.Model를 상속받아서 trainable_variables 속성을 사용할 수 있다.
> - trainable_variables: 위에서 정의된 모델구조에 관련된 파라미터의 전체 list를 반환한다.

##### 5. 테스트 정의

**정확도 측정**

```python
@tf.function 
def compute_accuracy(y_pred, y): 
    correct_prediction = tf.equal(tf.argmax(y_pred, 1), tf.argmax(y, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
       
    return accuracy
```

> `correct_prediction = tf.equal(tf.argmax(y_pred, 1), tf.argmax(y, 1))`: 모델이 예측한 값과 정답값이 일치하는지 비교
>
> y는 one-hot encoding 데이터, y_pred는 모든 요소에 값이 들어있는 데이터기 때문에 argmax를 취해서 비교
>
> `return accuracy`: 0~1사이의 정확도 반환
>
> 모델이 예측한 값과 정답이 100% 일치하면 1 반환, 10%만 일치하면 0.1 반환

```python
#SoftmaxRegression 모델 선언 (class 객체 선언: 위에서 정의된 클래스를 메모리에 할당)
SoftmaxRegression_model = SoftmaxRegression()

for i in range(1000):
    batch_xs, batch_ys = next(train_data_iter)
    train_step(SoftmaxRegression_model, batch_xs, batch_ys)

# 학습이 끝난 SoftmaxRegression_model를 가진 상태에서 학습된 모델의 정확도 출력
print(f"정확도(Accuracy): {compute_accuracy(SoftmaxRegression_model(x_test), y_test)}")
```

> `batch_xs, batch_ys = next(train_data_iter)` : next함수를 이용해서 위의 iter()를 통해 mini-batch를 순차적으로 가져옴
>
> - batch_xs = [100, 784] 로 표현된 MNIST 데이터
> - batch_ys = [100]의 one-hot encoding로 표현된 MNIST 데이터
>
> `SoftmaxRegression_model(x_test)`: SotfmaxRegression_model의 인자로 test input을 넣으면 call부분의 반환값인 모델의 예측 결과값이 반환
>
> `compute_accuracy(SoftmaxRegression_model(x_test), y_test)`: compute_accuracy(모델의 예측 결과값, 실제 정답값) = 모델의 정확도



#### 전체 코드(주석O)

```python
# 스프트맥스 회귀(Softmax Regression) 알고리즘

import tensorflow as tf

#----------MNIST 데이터를 사용하기 적합한 상태로 변경하는 작업----------
# MNIST 데이터를 다운로드
(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data() 

# load_data()에 의해 반환된 데이터는 numpy 타입이기 때문에 이미지들을 float32 데이터 타입으로 변경
x_train, x_test = x_train.astype('float32'), x_test.astype('float32')
# astype: numpy 모듈에서 제공하는 데이터타입 변경 메서드  

# 28*28 형태의 이미지를 784개의 1차원 데이터로 flattening 한다.  
x_train, x_test = x_train.reshape([-1, 784]), x_test.reshape([-1, 784])
# 2차원의 mnist 데이터는 softmax에 사용할 수 없기 때문에 1차원의 데이터로 변경하는 과정
# reshape: numpy 모듈에서 제공하는 데이터 차원 변경 메서드
# reshape([-1, 784]): -1을 넣으면 reshape함수가 알아서 몇 개(6만개) 데이터의 차원을 변경해야 하는지 인지한다

# [0, 255] 사이의 값을 [0, 1] 사이의 값으로 Normalize한다.
x_train, x_test = x_train / 255., x_test / 255.
# int 타입이 float32타입으로 변경됐기 때문에 Pixel Intensity 값을 0~255에서 0~1로 변경한다.

# 레이블 데이터에 one-hot encoding을 적용한다.
y_train, y_test = tf.one_hot(y_train, depth=10), tf.one_hot(y_test, depth=10)
# 정답 데이터가 interger Encoding으로 되어있기 때문에 해당 데이터 각각에 one-hot encoding을 적용해서 [[60000] * 10]으로 변환한다.

#----------우리가 가진 dataset을 batch단위로 묶는 과정----------
#tf.data API를 이용해서 데이터를 섞고 batch 형태로 가져온다.
train_data = tf.data.Dataset.from_tensor_slices((x_train, y_train))
# tf.data.dataset: mini-batch단위로 묶는 과정을 손쉽게 수행할 수 있도록 제공하는 class 
# from_tensor_slices(사용할 전체 데이터)
train_data = train_data.repeat().shuffle(60000).batch(100)
# batch: tf.data.dataset 내부의 메서드. 묶고싶은 mini-batch 단위 지정 가능
train_data_iter = iter(train_data)
# iter(): 이후 next()함수를 이용해서 mini-batch를 순차적으로 가져와서 학습에 사용할 수 있도록 함
# for문으로도 가능

##----------가설 정의----------
#----------tf.keras.Model을 이용해서 Softmax Regression 모델을 정의 ----------
# 케라스 서브클래싱
class SoftmaxRegression(tf.keras.Model):  #클래스 생성 후 tf.keras.Model을 상속
    def __init__(self): #생성자
        super(SoftmaxRegression, self).__init__()
        # super: tf.keras.Model의 생성자를 호출해주는 메서드
        self.softmax_layer = tf.keras.layers.Dense(10, activation = None, kernel_initializer='zeros', bias_initializer='zeros')
        # 멤버 변수에 만들고자 하는 모델 구조 정의
        # tf.keras.layers의 하위 API 중 Dense 지정해서 사용 
        # Dense API는 y = Wx+b 형태의 모델에 여러 activation을 적용해주는 AIP
        # 1번째 인자값: 내가 받고자 하는 output 크기 (784크기를 10의 크기의 softmax 회귀 형태로 변경하는 연산 수행)
        # activation = None  : activation을 적용하지 않음
        # kernel_initializer='zeros': Wx+b 에서 W의 파라미터. 초기값을 0으로 채우겠다. = 초기 이니셜라이지션을 진행을 하겠다.
        # bias_initializer='zeros': Wx+b 에서 b의 파라미터

    def call(self, x):
        # 클래스가 호출될때 자동으로 실행됨(인자값으로 input데이터를 받는다.)
        logits = self.softmax_layer(x)
        # input데이터를 그래프 끝까지 연산을 수행한 뒤 나오는 연산 결과값(생성자에서 수행)을 변수에 할당.
        return tf.nn.softmax(logits)
        # softmax를 구현해주는 tensorflow API를 사용

##----------손실함수 정의----------
@tf.function
def cross_entropy_loss(y_pred, y): #크로스 엔트로피 손실함수
    return tf.reduce_mean(-tf.reduce_sum(y * tf.math.log(y_pred), axis=[1]))
    # return tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits = logits, labels = y))
    # tf.nn.softmax_cross_entropy를 사용해서 크로스 엔트로피 손실함수를 사용할 수 있다.
    # tf.nn.softmax_cross_entropy를 사용하면 가설 정의 부분에서 call함수의 return값을 logits으로 해줘야 한다. 


##----------최적화 정의----------

optimizer = tf.optimizers.SGD(0.5)

#최적화를 위한 function을 정의
@tf.function
def train_step(model, x, y):
    with tf.GradientTape() as tape:
        y_pred = model(x)
        loss = cross_entropy_loss(y_pred, y)
    gradients = tape.gradient(loss, model.trainable_variables)
    optimizer.apply_gradients(zip(gradients, model.trainable_variables))
# tf.keras.Model를 상속받아서 trainable_variables 속성을 사용할 수 있다.
# trainable_variables: 여기서 정의된 모델구조에 관련된 파라미터의 전체 list를 반환한다.


##----------테스트 정의----------
#----------정확도 측정----------
@tf.function 
def compute_accuracy(y_pred, y): 
    correct_prediction = tf.equal(tf.argmax(y_pred, 1), tf.argmax(y, 1))
    # 모델이 예측한 값과 정답값이 일치하는지 비교
    # y는 one-hot encoding 데이터, y_pred는 모든 요소에 값이 들어있는 데이터기 때문에 argmax를 취해서 비교
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
       

    return accuracy
    # 0~1사이의 정확도 반환
    # 모델이 예측한 값과 정답이 100% 일치하면 1 반환, 10%만 일치하면 0.1 반환


#SoftmaxRegression 모델 선언 (class 객체 선언: 위에서 정의된 클래스를 메모리에 할당)
SoftmaxRegression_model = SoftmaxRegression()

for i in range(1000):
    batch_xs, batch_ys = next(train_data_iter)
    # next함수를 이용해서 위의 iter()를 통해 mini-batch를 순차적으로 가져옴
    # batch_xs = [100, 784] 로 표현된 MNIST 데이터
    # batch_ys = [100]의 one-hot encoding로 표현된 MNIST 데이터
    train_step(SoftmaxRegression_model, batch_xs, batch_ys)


# 학습이 끝난 SoftmaxRegression_model를 가진 상태에서 학습된 모델의 정확도 출력
print(f"정확도(Accuracy): {compute_accuracy(SoftmaxRegression_model(x_test), y_test)}")
# SotfmaxRegression_model의 인자로 test input을 넣으면 call부분의 반환값인 모델의 예측 결과값이 반환
# compute_accuracy(모델의 예측 결과값, 실제 정답값) = 모델의 정확도
```



#### 전체 코드(주석X)

```python
# 스프트맥스 회귀(Softmax Regression) 알고리즘
import tensorflow as tf

(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data() 
x_train, x_test = x_train.astype('float32'), x_test.astype('float32').  
x_train, x_test = x_train.reshape([-1, 784]), x_test.reshape([-1, 784])
x_train, x_test = x_train / 255., x_test / 255.
y_train, y_test = tf.one_hot(y_train, depth=10), tf.one_hot(y_test, depth=10)
train_data = tf.data.Dataset.from_tensor_slices((x_train, y_train))
train_data = train_data.repeat().shuffle(60000).batch(100)
train_data_iter = iter(train_data)

##----------가설 정의----------
class SoftmaxRegression(tf.keras.Model):  
    def __init__(self): 
        super(SoftmaxRegression, self).__init__()
        self.softmax_layer = tf.keras.layers.Dense(10, activation = None, kernel_initializer='zeros', bias_initializer='zeros')

    def call(self, x):
        logits = self.softmax_layer(x)
        return tf.nn.softmax(logits)
  

##----------손실함수 정의----------
@tf.function
def cross_entropy_loss(y_pred, y): #크로스 엔트로피 손실함수
    return tf.reduce_mean(-tf.reduce_sum(y * tf.math.log(y_pred), axis=[1]))

##----------최적화 정의----------
optimizer = tf.optimizers.SGD(0.5)

@tf.function
def train_step(model, x, y):
    with tf.GradientTape() as tape:
        y_pred = model(x)
        loss = cross_entropy_loss(y_pred, y)
    gradients = tape.gradient(loss, model.trainable_variables)
    optimizer.apply_gradients(zip(gradients, model.trainable_variables))

##----------테스트 정의----------
@tf.function 
def compute_accuracy(y_pred, y): 
    correct_prediction = tf.equal(tf.argmax(y_pred, 1), tf.argmax(y, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))
    return accuracy

SoftmaxRegression_model = SoftmaxRegression()

for i in range(1000):
    batch_xs, batch_ys = next(train_data_iter)
    train_step(SoftmaxRegression_model, batch_xs, batch_ys)

print(f"정확도(Accuracy): {compute_accuracy(SoftmaxRegression_model(x_test), y_test)}")
```

