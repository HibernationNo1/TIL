# Softmax Regression(소프트맥스 회귀)

소프트맥스 회귀는 n개의 레이블을 분류하기 위한 가장 기본적인 모델이다. 

모델의 output에 Softmax함수를 적용해서 모델의 출력값이 각각의 레이블에 대한 확인의 정도를 출력하도록 만들어주는 기법이다.

> Softmax함수는 Normalization 함수로써 출력값들의 합을 1로 만들어준다. 
> $$
> 수식\ : \ \ softmax(x)_i = \frac{exp(x_i)}{\sum_jexp(x_j)}
> $$
> 출력값으로 나온 모든 확률을 더하면 1이 되는 것이다.

Softmax함수를 마지막에 씌우게 되면 모델의 출력값이 레이블에 대한 확률을 나타내게 된다.(출력값들의 합이 1이 되므로)

**회귀 구조**

![](http://aidev.co.kr/files/attach/images/186/841/9d980c2c870140d5b4aedea73036b97d.png)

![](https://resources.codeonweb.com/bucket/cached/19/a0/19a03ef08b6bc80a9b65d5891fb5afea.png)



Logits 에 Softmax함수를 적용하면 sum to 1 형태로 output값을 정리해주기 때문에 이를 확률적 개념으로 이해할 수 있게 된다.

> Softmax함수를 적용하기 전의 출력값을 Logits이라고 한다.



- Softmax 회귀를 비롯한 분류 문제에는 크로스 엔트로피(Cross-Entropy) 손실함수를 많이 사용한다.
- softmax 활성화 함수는 다중 클래스 분류 시 사용한다.



## 코드 구현

**MNIST 숫자분류기 구현**

#### 기본 순서

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

