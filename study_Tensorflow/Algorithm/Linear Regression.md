# Linear Regression(선형 회귀)

```python
# 선형 회귀(Linear Regression) 알고리즘

import tensorflow as tf

# 선형회귀 모델(Wx + b)을 위한 tf.Variable을 선언
W = tf.Variable(tf.random.normal(shape = [1]))
b = tf.Variable(tf.random.normal(shape = [1]))

#-----------가설 정의(모델 구조 정의)-----------
@tf.function
def linear_model(x):   # x: input 데이터
    return W*x + b     # Linear Regression 수식 정의

#-----------손실함수 정의-----------
# MSE 손실함수
@tf.function
def mse_loss(y_pred, y): # y_pred: 모델이 예측한 값,  y실제 값
    return tf.reduce_mean(tf.square(y_pred - y))   #(y'-y)^2 의 평균


#-----------최적화 정의-----------

# 최적화를 위한 경사하강법 최적화(그라디언트 디센트 옵티마이저)를 정의
optimizer = tf.optimizers.SGD(0.01) #확률적 경사하강법 사용, learing rage = 0.01

# 최적화를 위한 function
@tf.function
def train_step(x, y):  # 경사하강법을 한번 실행해주는 함수를 관례적으로 train_step이라고 이름을 짖는다.
    with tf.GradientTape() as tape: # GradientTape scope 정의
        y_pred = linear_model(x)    # linear_model 함수에 기반한 예측결과
        loss = mse_loss(y_pred, y)  # 예측결과값과 실제 값을 매개로 MSE 손실함수 적용
    gradients = tape.gradient(loss, [W, b])     # loss에 대한 w, b 파라미터의 gradient(편미분)값
    optimizer.apply_gradients(zip(gradients, [W, b]))
    #apply_gradients함수: gradient 값을 통하여 theta 값을 얻어내기 위한 그래프 생성
    # SGD에 apply_gradients함수 적용  zip(계산한 gradient, 갱신 대상으로 사용할 파라미터 )
    # >> optimizer.apply_gradients 에 의해 파라미터 갱신이 이루어지게 된다.


#-----------트레이닝 과정-----------
# 트레이닝을 위한 입력값과 출력값(정답 데이터)
x_train = [1, 2, 3, 4]  
y_train = [2, 4, 6, 8]
#그래프로 그려보면 y = 2x의 그래프가 정답이 되는 것

# 경사하상법 1000번 수행
for i in range(1000):
    train_step(x_train, y_train)

# 테스트를 위한 입력값 준비
x_test = [3.5, 5, 5.5, 6]
# 테스트는 데이터를 이용해 학습된 선형회귀 모델이 데이터의 경향성(y = 2x)을 잘 학습했는지 측정
# 예상되는 참값: [7, 10, 11, 12]
print(linear_model(x_test))
```

