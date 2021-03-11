# 컨볼루션 신경망 (Convolution neural network, CNN)

### 개념

컨볼루션 신경망은 이미지 분야를 다루기에 최적화된 인공신경망 구조이다.

컨볼루션 신경망은 크게 컨볼루션층(풀링), 풀링층(서브샘플링)으로 구성되어 있다.

![](https://t1.daumcdn.net/cfile/tistory/277CEA48573525252F)

컨볼루션과 풀링레이어로 이미지로부터 특징을 축출하고 기존의 ANN구조로 넘긴 후 Softmax 회귀를 적용한다.

- **컨볼루션**

  컨볼루션 연산을 통해서 이미지의 특징을 추출해내는 역할을 한다.

  컨볼루션은 우리말로 합성곱이라고 불리는데 **커널** 또는 **필터**라고 불리는 윈도우 크기만큼의 X * X 크기의 행렬을 Y * Y크기의 이미지 행열의 X * X 크기 부분과 곱해서 모두 더하는 수학 연산임

  행렬곱의 결과로 이미지 행렬의 X * X 크기 부분의 값들은 모두 더해져 하나의 값으로 모아지게 되고, 이런 X * X 크기의 행렬 곱셈을 Y * Y 크기의 이미지 행렬의 가장 외쪽 위부터 가장 오른쪽 아래까지 순차적으로 수행하는 연산이 컨볼루션층에서 이루어진다.

  ![](https://blog.kakaocdn.net/dn/sSowL/btqCLeODqbH/0VNYdYkafga04UZhgxliv0/img.png)

  원본 이미지에 커널을 이용해서 컨볼루션을 수행하면 커널의 종류에 따라 원본 이미지의 특징들이 활성화맵으로 추출되게 된다. 이때 어떤 커널을 사용하느냐에 따라 원본 이미지에서 다향한 특징을 추출할 수 있다.(흑백만을 추출하는 커널, 더욱 선명한 이미지 특징만을 추출하는 커널, 더욱 흐린 특징만들 추출하는 커널)

  커널을 통해 추출한 **활성화 맵(feature map)**은 원본 이미지에서 명확히 들어자니 않았던 특징들을 보여준다. 

  **사용하는 API**: `Conv2D`

- **풀링**

  풀링은 최대값 풀링, 평균값 풀링, 최소값 풀링 세 가지가 있다.

  - 최대값 풀링

    이미지의 X * X 크기 부분에서 가장 큰 값 하나를 추출해서 원본 이미지의 X * X 개의 값을 1개의 값으로 축소한다.

  - 평균값 풀링

    최대값 풀링과 동일한 원리로  평균 값 하나를 추출해서 원본 이미지의 X * X 개의 값을 1개의 값으로 축소한다.

  - 최소값 풀링

    최대값 풀링과 동일한 원리로  최소 값 하나를 추출해서 원본 이미지의 X * X 개의 값을 1개의 값으로 축소한다.

  풀링층 역시 이미지의 좌측 상단에서 우측 하단으로 순차적으로 전체 이미지에 대해 풀링을 수행한다.

  풀링층은 **이미지의 차원을 축소함으로써 필요한 연산량을 감소**시킬 수 있고, **이미지의 가장 강한 특징만을 추출하는 특징 선별 효과**가 있다.
  
  **사용하는 API**: `MaxPool2D`  (최대값 풀링)

### 신경망의 동작 과정

**컨볼루션층을 거치면 인풋 이미지의 가로, 세로 차원이 축소된다. **

- 가로 인풋 이미지 축소

$$
W_{out} = \frac{W_{in} - F + 2P}{S} + 1 \\
인풋\ 이미지의\ 가로 길이 : W_{in} \ , \ \ \ 출력\ 이미지의 가로 길이:\ W_{out}\\
필터의 크기:\ F\ , \ \ 스트라이드:\ S
$$

> - 스트라이드: 컨볼루션 연산시 건너뛰는 정도
>   스트라이드를 크게 잡으면 이미지를 성큼성큼 건너뛰어서 컨볼루션을 수행하게 되어 차원이 많이 축소되고, 작게 잡으면 이미지를 촘촘히 건너뛰면서 차원이 조금 축소된다.
>
> - \frack {W_{in} - F} {S} 의 차원이 정수로 나누어떨어지지 않을 수도 있기 때문에 인풋 이미지의 상하좌우 모서리에 P만큼 0을 채워주는 제로패딩을 P만큼 적용해준다.
>
>   > 제로패딩 1을 적용한 이미지
>   
>   ![](https://t1.daumcdn.net/cfile/tistory/993372345B5977F410)
>   
>   > padding에 'same' 값을 할당하면 변환된 사이즈의 이미지를 원본 사이즈와 동일한 사이즈의 활성화 맵이 나오도록 해줌

- 세로 인풋 이미지 축소
  $$
  H_{out} = \frac{H_{in} - F + 2P}{S} + 1 \\
  인풋\ 이미지의\ 세로 길이 : H_{in} \ , \ \ \ 출력\ 이미지의\ 세로 길이:\ H_{out}\\
  필터의 크기:\ F\ , \ \ 스트라이드:\ S
  $$

컨볼루션층의 출력결과의 3번째 차원은 컨볼루션 필터 개수 **K**가 된다.

따라서 컨볼루션층의 결과로 출력되는 차원은
$$
[W_{out},H_{out}, K] 
$$
가 된다.

> 예를 들어
>
> [28 * 28 * 1] MNIST 이미지에 4 * 4 크기의 필터 (F=4)에 스트라이드 가 2 이고(S = 2) 제로패딩을 1만큼(P = 1) 적용한, 64개의 필터개수(K = 64)를 가진 컨볼루션층을 적용하면 출력 결과로 [14, 14, 64], 즉 14 * 14 크기의 64개의 활성화 맵이 추출될 것이다.
> $$
> W_{out} = \frac{28 - 4 + 2*1}{2} + 14 \\
> H_{out} = \frac{28 - 4 + 2*1}{2} + 14\\
> K = 64
> $$
> 



**정리**

![](https://t1.daumcdn.net/cfile/tistory/277CEA48573525252F)

1. 컨볼루션과 풀링 연산을 이용해서 특징추출을 한다.
2. 1의 연산에 의해 K갯수 만큼 나온 활성화 맵을 한 픽셀씩 펼치는 과정(Flatten)을 거쳐 매우 긴 백터로 변경한다.
3. 위의 백터를 ANN구조에 넘긴다.
4. 레이블 갯수만큼의 Softmax 회귀를 수행한다.



### 코드 구현

#### **MNIST 숫자 분류를 위한 CNN 구현**

```python
# Convolutional Neural Networks(CNN)을 이용한 MNIST 분류기(Classifier) - Keras API를 이용한 구현

import tensorflow as tf

(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data()
x_train, x_test = x_train.astype('float32'), x_test.astype('float32')
x_train, x_test = x_train.reshape([-1, 784]), x_test.reshape([-1, 784])
x_train, x_test = x_train / 255., x_test / 255.
y_train, y_test = tf.one_hot(y_train, depth=10), tf.one_hot(y_test, depth=10)

#tf.data API를 이용해서 데이터를 섞고 batch 형태로 가져온다
train_data = tf.data.Dataset.from_tensor_slices((x_train, y_train)) 
train_data = train_data.repeat().shuffle(60000).batch(50)
train_data_iter = iter(train_data) # 50개씩 batch 를 가져올 수 있는 iter

# tf.keras.model을 이용해서 CNN모델을 정의
class CNN(tf.keras.Model):
    def __init__(self):
        super(CNN, self).__init__()
        # Convolution -> pooling -> Convolution -> pooling -> Flatten -> Dense -> Dense 형태

        # 첫 번째 Convolution Layer
        # 5*5 kernel Size를 가진 32개의 Filter를 적용한다.
        self.conv_layer_1 =tf.keras.layers.Conv2D(filters=32, kernel_size = 5, strides = 1, padding = 'same', activation = 'relu')
        # 32개의 필터 사이즈를 가지고 커널사이즈가 5*5, 스트라이드 = 1
        self.pool_layer_1 = tf.keras.layers.MaxPool2D(pool_size=(2, 2), strides=2)
        # 2 * 2 인 pooling

        # 두 번째 Convolution Layer
        # 5*5 kernel Size를 가진 64개의 Filter를 적용한다.
        self.conv_layer_2 =tf.keras.layers.Conv2D(filters=64, kernel_size = 5, strides = 1, padding = 'same', activation = 'relu')
        self.pool_layer_2 = tf.keras.layers.MaxPool2D(pool_size=(2, 2), strides=2)

        # Fully Connected Layer
        # 7*7 크기를 가진 64개의 activation map을 1024개의 특징들로 변환한다.
        self.flatten_layer = tf.keras.layers.Flatten()
        self.fc_layer_1 = tf.keras.layers.Dense(1024, activation='relu')

        # Output Layer
        # 1024개의 특징(feature)을 10개의 클래스-one-hot encogin으로 표현된 숫자 0~9로 변환
        self.output_layer = tf.keras.layers.Dense(10, activation=None)

    def call(self, x):
        # MNIST데이터를 3차원 형태로 reshape한다. MNIST 데이터는 grayscale(흑백) 이미지기 때문에 3번째 차원(컬러채널)의 값은 1임
        x_image = tf.reshape(x, [-1, 28, 28, 1])
        # 이미지 차원을 데이터로 바로 받는다.
        
        # 28*28 -> 28*28*32
        h_conv1 = self.conv_layer_1(x_image)
        # 28*28*32 -> 14*14*32
        h_pool1 = self.pool_layer_1(h_conv1)
        
        # 14*14*32 -> 14*14*64
        h_conv2 = self.conv_layer_2(h_pool1)
        # 14*14*64 -> 7*7*64
        h_pool2 = self.pool_layer_2(h_conv2)

        # 7*7*64(3136) -> 1024
        h_pool2_flat = self.flatten_layer(h_pool2)
        h_fc1 = self.fc_layer_1(h_pool2_flat)
        #1024 -> 10의 softmax
        logits = self.output_layer(h_fc1)
        y_pred = tf.nn.softmax(logits)
        # output = input data의 Classification 결과

        return y_pred, logits

#----------손실함수 정의----------
# 크로스 엔트로피 손실함수 정의
@tf.function
def cross_entropy_loss(logits, y): 
    return tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits = logits, labels = y))
# 오토인코더에서는 정답 데이터가 input데이터임 : y_true

#----------최적화 정의----------
# Adam사용
optimizer = tf.optimizers.Adam(1e-4) # 0.0001


@tf.function
def train_step(model, x, y):
    with tf.GradientTape() as tape:
        y_pred, logits = model(x)
        loss = cross_entropy_loss(logits, y)
    gradients = tape.gradient(loss, model.trainable_variables)
    optimizer.apply_gradients(zip(gradients, model.trainable_variables))


#----------학습 정의---------- 
# 모델 정확도 출력하는 함수
@tf.function
def compute_accuracy(y_pred, y):
    correct_prediction = tf.equal(tf.argmax(y_pred,1), tf.argmax(y,1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

    return accuracy

# 모델 선언
CNN_model = CNN()

# 10000 step 만큼 최적화
for i in range(10000):
    # 50개씩 MNIST 데이터를 불러온다
    batch_x, batch_y = next(train_data_iter)
    # 1000 step마다 training 데이터셋에 대한 정확도를 출력한다.
    if i % 1000 == 0:
        train_accuracy = compute_accuracy(CNN_model(batch_x)[0], batch_y)
        print(f"반복(Epoch): {i}, 트레이닝 정확도:  {train_accuracy}")
    # 최적화를 실행해 파라미터를 한스텝 업데이트
    train_step(CNN_model, batch_x, batch_y)

# 학습이 끝나면 학습된 모델의 정확도 출력
print(f"정확도: {compute_accuracy(CNN_model(x_test)[0], y_test)}")
```





#### CIFAR-10 이미지 분류를 위한 CNN 구현

dropout을 적용했음.

```python
# CIFAR-10 Convolutional Neural Networks(CNN) 예제

import tensorflow as tf

# CIFAR-10 데이터를 다운로드하고 데이터를 불러옴
(x_train, y_train), (x_test, y_test) = tf.keras.datasets.cifar10.load_data()
# 이미지들을 float32 데이터 타입으로 변경
x_train, x_test = x_train.astype('float32'), x_test.astype('float32')
# [0, 255] 사이의 값을 [0, 1]사이의 값으로 Normalize
x_train, x_test = x_train / 255., x_test / 255.
# scalar 형태의 레이블(0~9)을 One-hot Encoding 형태로 변환
y_train_one_hot = tf.squeeze(tf.one_hot(y_train, 10), axis=1)
y_test_one_hot = tf.squeeze(tf.one_hot(y_test, 10), axis=1)

# tf.data API를 이용해서 트레이닝 데이터를 섞고 batch 형태로 가져온다.
train_data = tf.data.Dataset.from_tensor_slices((x_train, y_train_one_hot))
train_data = train_data.repeat().shuffle(50000).batch(128)
train_data_iter = iter(train_data)

# tf.data API를 이용해서 테스드 데이터를 섞고 batch 형태로 가져온다.
test_data = tf.data.Dataset.from_tensor_slices((x_test, y_test_one_hot))
test_data = test_data.batch(1000)
test_data_iter = iter(test_data)
# CIFAR-10 데이터 셋은 MNIST보다 차원이 크기 때문에 수많은 이미지를 GPU메모리에 올리면 
# out of memory가 발생해 프로그램이 종료될 수 있기 때문에 batch(1000)를 통해 데이터를 묶어서
# 1000개 단위로 측정한 정확도의 평균으로 최종 평균을 결정한다.

# tf.keras.model을 이용해서 CNN모델을 정의
class CNN(tf.keras.Model):
    def __init__(self):
        super(CNN, self).__init__()
        # Conv2D -> MaxPool2D -> Conv2D -> MaxPool2D -> Conv2D -> Conv2D -> Conv2D -> Flatten() 형태로 구성

        # 첫번째 convolutional layer - 하나의 RGB 이미지를 64개의 특징들(feature)으로 맵핑(mapping)
        # 64개의 노드를 가진 layer에 넘긴다는 뜻
        self.conv_layer_1 = tf.keras.layers.Conv2D(filters=64, kernel_size=5, strides=1, padding='same', activation='relu')
        self.pool_layer_1 = tf.keras.layers.MaxPool2D(pool_size=(3, 3), strides=2)
        # 두번째 convolutional layer - 64개의 특징들(feature)을 64개의 특징들(feature)로 맵핑(mapping)
        self.conv_layer_2 = tf.keras.layers.Conv2D(filters=64, kernel_size=5, strides=1, padding='same', activation='relu')
        self.pool_layer_2 = tf.keras.layers.MaxPool2D(pool_size=(3, 3), strides=2)
        # 세번째 convolutional layer
        self.conv_layer_3 = tf.keras.layers.Conv2D(filters=128, kernel_size=3, strides=1, padding='same', activation='relu') 
        # 네번째 convolutional layer
        self.conv_layer_4 = tf.keras.layers.Conv2D(filters=128, kernel_size=3, strides=1, padding='same', activation='relu')
        # 다섯번째 convolutional layer
        self.conv_layer_5 = tf.keras.layers.Conv2D(filters=128, kernel_size=3, strides=1, padding='same', activation='relu')

        # Fully Connected Layer 1 - 2번의 downsampling 이후에, 우리의 32x32 이미지는 8x8x128 특징맵(feature map)이 됨
        self.flatten_layer = tf.keras.layers.Flatten()
        # 이를 384개의 특징들로 맵핑(mapping)
        self.fc_layer_1 = tf.keras.layers.Dense(384, activation='relu')
        # 384개의 노드가 있는 layer에 dropout 적용 (20%)
        self.dropout = tf.keras.layers.Dropout(0.2)

        # Fully Connected Layer 2 - 384개의 특징들(feature)을 10개의 클래스로 맵핑(mapsping)
        self.output_layer = tf.keras.layers.Dense(10, activation=None)
        # 10개의 노드는 airplane, automobile, bird...의 특징을 가진 클래스

    def call(self, x, is_training):
    # is_training는 bool형 변수
        h_conv1 = self.conv_layer_1(x)
        h_pool1 = self.pool_layer_1(h_conv1)
        h_conv2 = self.conv_layer_2(h_pool1)
        h_pool2 = self.pool_layer_2(h_conv2)
        h_conv3 = self.conv_layer_3(h_pool2)
        h_conv4 = self.conv_layer_4(h_conv3)
        h_conv5 = self.conv_layer_5(h_conv4)
        h_conv5_flat = self.flatten_layer(h_conv5)
        h_fc1 = self.fc_layer_1(h_conv5_flat)
        # Dropout - 모델의 복잡도를 컨트롤. (특징들의 co-adaptation을 방지)
        h_fc1_drop = self.dropout(h_fc1, training=is_training)
        # dropout 안의 training이 Ture면 dropout적용
        logits = self.output_layer(h_fc1_drop)
        y_pred = tf.nn.softmax(logits)

        return y_pred, logits

#----------손실함수 정의----------
# 크로스 엔트로피 손실함수 정의
@tf.function
def cross_entropy_loss(logits, y):
  return tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits=logits, labels=y))

#----------최적화 정의----------
# 최적화를 위한 RMSprop 옵티마이저를 정의
optimizer = tf.optimizers.RMSprop(1e-3)

# 최적화를 위한 function을 정의
@tf.function
def train_step(model, x, y, is_training):
    with tf.GradientTape() as tape:
        y_pred, logits = model(x, is_training)
        # is_training을 사용해서 training시점과 test시점의 dropout 적용을 결정한다.
        loss = cross_entropy_loss(logits, y)
    gradients = tape.gradient(loss, model.trainable_variables)
    optimizer.apply_gradients(zip(gradients, model.trainable_variables))


#----------학습 정의---------- 
# 모델 정확도 출력하는 함수
@tf.function
def compute_accuracy(y_pred, y):
    correct_prediction = tf.equal(tf.argmax(y_pred,1), tf.argmax(y,1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

    return accuracy

# 모델 선언
CNN_model = CNN()

# 10000 step 만큼 최적화
for i in range(10000):
    batch_x, batch_y = next(train_data_iter)
    # 1000 step마다 training 데이터셋에 대한 정확도를 출력한다.
    if i % 1000 == 0:
        train_accuracy = compute_accuracy(CNN_model(batch_x, False)[0], batch_y)
        loss_print = cross_entropy_loss(CNN_model(batch_x, False)[1], batch_y)
        print(f"반복(Epoch): {i}, 트레이닝 정확도:  {train_accuracy}")
    # 최적화를 실행해 파라미터를 한스텝 업데이트
    train_step(CNN_model, batch_x, batch_y, True)

# 학습이 끝나면 학습된 모델의 정확도 출력
test_accuracy = 0.0
for i in range(10):
    test_batch_x, test_batch_y = next(test_data_iter)
    # 1000개 단위로 묶은 테스트 데이터를 가져온다.
    test_accuracy = test_accuracy + compute_accuracy(CNN_model(test_batch_x, False)[0], test_batch_y).numpy()
test_accuracy = test_accuracy / 10

print(f"테스트 데이터 정확도: {test_accuracy}")
```

