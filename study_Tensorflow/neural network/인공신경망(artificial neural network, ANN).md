# 인공신경망(artificial neural network, ANN)

인공신경망은 다중 퍼셉트론을 의미한다.

## 퍼셉트론(perceptron)

- 퍼셉트론은 생물학적 뉴런을 공학적인 구조로 변형한 것이다.

![](https://lh3.googleusercontent.com/proxy/np0krZOO-fAMT21k3tsYjjZ70pFIMpuOd60JYPNniVe1zcvo0hB-Z_QiNw4sG4AKdiA1F7W0WrI2axAqnmqtLzxr42yYmnUApGjwQb7PVRKdEIza_rf6rw)

퍼셉트론은 입력층과 출력층을 가지고 있다.

> 입력층에서 인풋 데이터 x를 받고, 이를 가중치 W와 곱한 후, 이 값에 바이어스 b를 더한다. 그리고 이 값을 **활성 함수**의 입력값으로 대입해서 출력층은 최종적으로 0 또는 1의 값을 출력한다. 



- 퍼셉트론의 동작 과정을 수학적으로 표현
  $$
  수식 : \ y = \sigma(Wx + b) \\ \sigma: 활성\ 함수
  $$
  여기서 활성함수로 계단함수를 사용하여 퍼셉트론의 출력을 0 또는 1만 출력하게 하기 때문에**선형 이진분류기**라고 한다.



- 퍼셉트론의 가중치란, input의 중요도를 의미한다.

  어떠한 동작에 대한 의사결정 모델을 퍼셉트론을 이용해서 만든다면, 의사결정에 고려해야 하는 사항이 3가지 있다고 가정할 때 (w1, w2, w3) 가장 중요하게 고려하는 사항에 가장 큰 비율의 값을 할당하는 것이다.

  ex) w3이 가장 중요할 때: w1 = 2, w2 = 2, w3 = 6

- 단일 퍼셉트론은 선형 분리가 불가능한 문제는 해결할 수 없다.

### 다층 퍼셉트론 (Multi-Layer perceptron, MLP)

- 다층 퍼셉트론을 이용하면 성형 분리가 불가능한 문제도 해결할 수 있다.

- 다층 인공신경망(ANN)은 일반적으로 퍼셉트론(MLP)을 의미한다.

- 다층 퍼셉트론은 입력층, 은닉층, 출력층으로 구성되어 있으며 은닉층은 데이터의 입출력 과정에서 직접적으로 보이진 않지만 숨겨진 특징을 학습하는 역할을 한다.

  > 은닉층을 여러 번 쌓아올린 형태를 **깊은 인공신경망**이라고 부르고 이 구조가 우리가 일반적으로 **딥러닝**이라고 부르는 기법이다.

  ![](https://wikidocs.net/images/page/49071/multilayerperceptron.PNG)

- 다층 퍼셉트론 1개의 층은 여러 개의 노드로 구성되며 1개의 노드에서 일어나는 연산은 퍼셉트론 구조와 동일하다.

  > 단일 퍼셉트론의 연상 과정이 중복적으로 이루어지는 것이다.

  ![](https://clickai.ai/assets/img/img_blog_post_3_2.png)
  $$
  각각의\ 노드에서\ 일어나는\ 연산: \ y = \sigma(Wx + b)
  $$
  이 때 활성함수는 분류기가 **비선형적인 특징을 학습**할 수 있도록 만드는 것이 단일 퍼셉트론과의 차이점이다.

  > 활성 함수로 계단함수를 사용하지 않고 비선형 함수인 시그모이드, 쌍곡탄젠트 혹은 **ReLU**를 사용한다.
  >
  > y는 활성함수의 출력 결과인 **활성값**이라고 한다.

---



## 코드 구현

**인공신경망(ANN)을 이용한 MNIST숫자분류기 구현**

가설 정의를 하지 않고 모델 정의를 한다.

```python
# 인공신경망(ANN)을 이용한 숫자분류기 구현

import tensorflow as tf

(x_train, y_train), (x_test, y_test) = tf.keras.datasets.mnist.load_data() 
x_train, x_test = x_train.astype('float32'), x_test.astype('float32')
x_train, x_test = x_train.reshape([-1, 784]), x_test.reshape([-1, 784])
x_train, x_test = x_train / 255., x_test / 255.
y_train, y_test = tf.one_hot(y_train, depth=10), tf.one_hot(y_test, depth=10)

# 학습을 위한 설정값들을 정의한다.
learning_rate = 0.001
num_epochs = 30     # 학습 횟수  epochs: 전체 데이터를 1회 순회하는 횟수
batch_size = 256    # 배치개수
display_step = 1    # 손실함수 출력 주기
input_size = 784    # 28 * 28
hidden1_size = 256
hidden2_size = 256  # 256개의 노드를 가진 은닉층 2개 사용
output_size = 10

#tf.data API를 이용해서 데이터를 섞고 batch 형태로 가져온다
train_data = tf.data.Dataset.from_tensor_slices((x_train, y_train))
train_data = train_data.shuffle(60000).batch(batch_size)
# shuffle: 한 번 에폭이 끝날때마다 데이터를 섞어주는 함수

#----------모델 정의----------
# tf.keras.initializers를 이용해서 어떤 모양의 분포에서 W와 b를 초기화할지를 지정할 수 있는 함수
def random_normal_intializer_with_stddev_1(): 
    return tf.keras.initializers.RandomNormal(mean=0.0, stddev=1.0, seed=None)
    # 평균 0, 표준편자 1인 RandomNormal분포에서 초기 W와 b값을 뽑는다.

# tf.keras.model을 이용해서 ANN모델을 정의
class ANN(tf.keras.Model):
    def __init__(self):
        super(ANN, self).__init__()
        # Dense의 인자값: (노드 갯수, 활성함수 ReLU사용, W값, b값)
        self.hidden_layer_1 = tf.keras.layers.Dense(hidden1_size,
                                                    activation='relu',
                                                    kernel_initializer=random_normal_intializer_with_stddev_1(),
                                                    bias_initializer=random_normal_intializer_with_stddev_1())
        
        self.hidden_layer_2 = tf.keras.layers.Dense(hidden2_size,
                                                    activation='relu',
                                                    kernel_initializer=random_normal_intializer_with_stddev_1(),
                                                    bias_initializer=random_normal_intializer_with_stddev_1())
        self.output_layer = tf.keras.layers.Dense(output_size,
                                                    activation=None,
                                                    kernel_initializer=random_normal_intializer_with_stddev_1(),
                                                    bias_initializer=random_normal_intializer_with_stddev_1())
    def call(self, x):
        H1_output = self.hidden_layer_1(x)
        H2_output = self.hidden_layer_2(H1_output)
        logits = self.output_layer(H2_output)

        return logits

#----------손실함수 정의----------
# cross-entropty 손실 함수 정의
@tf.function
def cross_entropy_loss(logits, y): #크로스 엔트로피 손실함수
    return tf.reduce_mean(tf.nn.softmax_cross_entropy_with_logits(logits = logits, labels = y))
# tf.nn.softmax_cross_entropy_with_logits를 사용하면 logits에 softmax를 적용하고 y와 비교를 수행하여 cross-entropy를 계산한다.

#----------최적화 정의----------
# Adam optimizer사용
optimizer = tf.optimizers.Adam(learning_rate)

@tf.function
def train_step(model, x, y):
    with tf.GradientTape() as tape:
        y_pred = model(x)
        loss = cross_entropy_loss(y_pred, y)
    gradients = tape.gradient(loss, model.trainable_variables)
    optimizer.apply_gradients(zip(gradients, model.trainable_variables))



#----------테스트 정의----------
#정확도 측정 함수
@tf.function 
def compute_accuracy(y_pred, y): 
    correct_prediction = tf.equal(tf.argmax(y_pred, 1), tf.argmax(y, 1))
    accuracy = tf.reduce_mean(tf.cast(correct_prediction, tf.float32))

    return accuracy
   
# 모델 선언
ANN_model = ANN()

#지정된 횟수만큼 최적화를 수행
for epoch in range(num_epochs):
    average_loss = 0.
    total_batch = int(x_train.shape[0] / batch_size)
    # 모든 배치들에 대해서 최적화를 수행
    for batch_x, batch_y in train_data:
        # 최적화를 실행해서 파라미터를 업데이트
        _, current_loss = train_step(ANN_model, batch_x, batch_y), cross_entropy_loss(ANN_model(batch_x),batch_y)
        # 여기서 train_step은 어디에 값을 할당할 필요 X (파라미터를 업데이트만 하면 됨)
        # current_loss: 해당 파라미터를 가진시점에 ANN모델에 기반한 예측 결과와 실제 결과간 cross_entropy를 계산해서 손실함수를 할당
        # 평균 손실을 측정
        average_loss += current_loss / total_batch
    #지정된 epoch마다 학습결과를 출력
    if epoch % display_step == 0:
        print(f"반복(Epoch): {epoch+1}, 손실 함수(loss): {average_loss}")


# 테스트 데이터를 이용해서 학습된 모델이 얼마나 정확한지 정확도를 출력
print(f"정확도(Accuracy): {compute_accuracy(ANN_model(x_test), y_test)}")
```

