# 오토인코더(Autoencoder)

- 오토인코더는 대표적인 비지도 학습을 위한 인공신경망 구조 중 하나

  > 비지도 학습은 어떤 값을 예측하거나 분류하는 것이 목적인 지도 학습과는 다르게 데이터의 숨겨진 구조를 발견하는 것이 목표인 학습 방법이다.

- 오토인코더는 출력층의 노드 개수와 입력층의 노드 개수가 동일하고 은닉층의 노드 개수는 입, 출력층의 노드 개수보다 적은 구조를 가지고 있다.

  > 오토인코더의 출력은 원본 데이터를 재구축한 결과가 된다.

![](https://lh3.googleusercontent.com/proxy/BNc05ieNY9dmQZCIOC0oV36K5GzVgcelWKEUzMJ5E_P6yxe8PdLBSj5fCHLluYwYTJoGcJD4s_e9Vd5jMIrexKG4kQhdExyqMdKjZ9xkw81xcKL1s-iGPmGfCVREJgwelESs)

![](https://clickai.ai/assets/img/img_blog_post_3_2.png)
$$
각각의\ 노드에서\ 일어나는\ 연산: \ y = \sigma(Wx + b)
$$

> 활성 함수로 **sigmoid**를 사용

- 은닉층의 노드가 입, 출력층의 노드보다 적기 때문에 더 작은 표현력으로 원본 데이터의 모든 특징들을 학습해야 한다. 결과적의 은닉층의 출력값은 원본 데이터에서 불필요한 특징들을 제거한 입축된 특징들을 학습하게 된다.

  > 오토인코더 은닉층의 출력값은 학습을 통해서 필요한 데이터만을 이용해서 분류를 수행하고 남은 특징들임.
  >
  > 이렇게 압축된 특징을 나타내는 은닉층의 출력값을 원본 데이터 대신에 분류기의 입력으로 사용한다면 더욱 좋은 분류 성능을 기대할 수 있을 것이다.

- 예시)

  동물이 개인지 고양이인지 예측할 때 

  전체 데이터: 동물의 길이, 동물의 몸무게, 동물 주인의 나이, 동물 주인의 몸무게 

  필요한 데이터: 동물의 길이, 동물의 몸무게

  불필요한 데이터: 동물 주인의 나이, 동물 주인의 몸무게

  여기서 필요한 데이터만을 이용해서 분류를 수행

### 코드 예시

오토인코더를 이용한 Mnist 데이터 재구축

```python
# 인공신경망(ANN)을 이용한 숫자분류기 구현

import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt

(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data() 
x_train, x_test = x_train.astype('float32'), x_test.astype('float32')
x_train, x_test = x_train.reshape([-1, 784]), x_test.reshape([-1, 784])
x_train, x_test = x_train / 255., x_test / 255.

# 학습을 위한 설정값들을 정의한다.
learning_rate = 0.02
training_epochs = 50     # 학습 횟수  epochs: 전체 데이터를 1회 순회하는 횟수
batch_size = 256    # 배치개수
display_step = 1    # 손실함수 출력 주기
examples_to_show = 10   #보여줄 MNIST Reconstruction 이미지 개수
input_size = 784    # 28 * 28
hidden1_size = 256
hidden2_size = 128

#tf.data API를 이용해서 데이터를 섞고 batch 형태로 가져온다
train_data = tf.data.Dataset.from_tensor_slices(x_train)  # 정답데이터 필요 없이 x데이터만 묶어줌
train_data = train_data.shuffle(60000).batch(batch_size)


# W와 b의 초기값 지정 함수
def random_normal_intializer_with_stddev_1(): 
    return tf.keras.initializers.RandomNormal(mean=0.0, stddev=1.0, seed=None)

# tf.keras.model을 이용해서 Autoencoder모델을 정의
class Autoencoder(tf.keras.Model):
    def __init__(self):
        super(Autoencoder, self).__init__()
        # 인코딩 - 784 -> 256 -> 128
        self.hidden_layer_1 = tf.keras.layers.Dense(hidden1_size,
                                                    activation='sigmoid',
                                                    kernel_initializer=random_normal_intializer_with_stddev_1(),
                                                    bias_initializer=random_normal_intializer_with_stddev_1())
        self.hidden_layer_2 = tf.keras.layers.Dense(hidden2_size,
                                                    activation='sigmoid',
                                                    kernel_initializer=random_normal_intializer_with_stddev_1(),
                                                    bias_initializer=random_normal_intializer_with_stddev_1())
        # 디코딩 - 128 -> 256 -> 784
        self.hidden_layer_3 = tf.keras.layers.Dense(hidden2_size,
                                                    activation='sigmoid',
                                                    kernel_initializer=random_normal_intializer_with_stddev_1(),
                                                    bias_initializer=random_normal_intializer_with_stddev_1())
        self.output_layer = tf.keras.layers.Dense(input_size,
                                                    activation='sigmoid',
                                                    kernel_initializer=random_normal_intializer_with_stddev_1(),
                                                    bias_initializer=random_normal_intializer_with_stddev_1())
    
    def call(self, x):
        H1_output = self.hidden_layer_1(x)
        H2_output = self.hidden_layer_2(H1_output)
        H3_output = self.hidden_layer_3(H2_output)
        reconstructed_x= self.output_layer(H3_output)

        return reconstructed_x

#----------손실함수 정의----------
# MSE 손실 함수 정의
@tf.function
def MSE_loss(y_pred, y_true): 
    return tf.reduce_mean(tf.pow(y_true - y_pred, 2))
# 오토인코더에서는 정답 데이터가 input데이터임 : y_true

#----------최적화 정의----------
# RMSprop Optimizer사용
optimizer = tf.optimizers.RMSprop(learning_rate)

@tf.function
def train_step(model, x):
    # 타겟 데이터는 input데이터와 같다.
    y_true = x
    with tf.GradientTape() as tape:
        y_pred = model(x)
        loss = MSE_loss(y_pred, y_true)
    gradients = tape.gradient(loss, model.trainable_variables)
    optimizer.apply_gradients(zip(gradients, model.trainable_variables))


#----------학습 정의---------- 
# 모델 선언
Autoencoder_model = Autoencoder()

for epoch in range(training_epochs):
    # Autoencoder는 Unsupervised Learning이므로 타겟 레이블(label) y가 필요없음.
    for batch_x in train_data:
        _, current_loss = train_step(Autoencoder_model, batch_x), MSE_loss(Autoencoder_model(batch_x),batch_x)
    #지정된 epoch마다 학습결과를 출력
    if epoch % display_step == 0:
        print(f"반복(Epoch): {epoch+1}, 손실 함수(loss): {current_loss}")

#----------결과 확인----------
# 테스트 데이터로 Reconstruction을 수행
reconstructed_result = Autoencoder_model(x_test[:examples_to_show])
# 원본 MNIST 데이터와 재구축 결과를 비교
f, a = plt.subplots(2, 10, figsize = (10, 2))
for i in range(examples_to_show):
    a[0][i].imshow(np.reshape(x_test[i], (28, 28)))
    # 원래 이미지
    a[1][i].imshow(np.reshape(reconstructed_result[i], (28, 28)))
    # 재구축된 이미지
f.savefig('reconstructed_mnist_image.png') 
f.show()
plt.draw()  
plt.waitforbuttonpress()    
```