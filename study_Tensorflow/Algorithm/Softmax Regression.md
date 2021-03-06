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



## 코드 구현

**MNIST 숫자분류기 구현**

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
y_train, y_tset = tf.one_hot(y_train, depth=10), tf.one_hot(y_test, depth=10)
# 정답 데이터가 interger Encoding으로 되어있기 때문에 해당 데이터 각각에 one-hot encoding을 적용해서 [[60000] * 10]으로 변환한다.

#----------우리가 가진 dataset을 batch단위로 묶는 과정----------
#tf.data API를 이용해서 데이터를 섞고 batch 형태로 가져온다.
train_data = tf.data.Dataset.from_tensor_slices((x_train, y_train))
# tf.data.dataset: mini-batch단위로 묶는 과정을 손쉽게 수행할 수 있도록 제공하는 class 
# from_tensor_slices(사용할 전체 데이터)
trina_data = train_data.repeat().shuffle(60000).batch(100)
# batch: tf.data.dataset 내부의 메서드. 묶고싶은 mini-batch 단위 지정 가능
train_data_iter = iter(train_data)
# iter(): 이후 next()함수를 이용해서 mini-batch를 순차적으로 가져와서 학습에 사용할 수 있도록 함
# for문으로도 가능

```

