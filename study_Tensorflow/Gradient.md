# Gradient

### 1. GradientTape()

텐서플로는 자동 미분(주어진 입력 변수에 대한 연산의 편미분(gradient)를 계산하는 것)을 위한 **tf.GradientTape** API를 제공한다. 

tf.GradientTape는 컨텍스트(context) 안에서 실행된 **모든 연산**을 테이프(tape)에 "기록" 후 후진 방식 자동 미분(reverse mode differentiation)을 사용해 테이프에 "기록된" 연산의 그래디언트를 계산한다.

**문법** (with as 키워드 사용)

```python
with tf.GradientTape() as tape:
    #가설 함수와 손실함수 실행
gradients = tape.gradient(tmp1, tmp2) #tmp1에 대한 tmp2 파라미터의 gradient(편미분)값
```

> tape.gradient는 편미분 값을 계산한다.



또한 tf.GradientTape 컨텍스트 안에서 계산된 중간값에 대한 그래디언트도 구할 수 있다.

### 2. gradient()

gradient 함수는 인자로 가져온 값에 대한 편미분을 계산한다.

GradientTape()에 의한 스코프 안의 변수를 인자로 가져오기 때문에 `스코프 이름.gradient` 형태임 

- `tape.gradient(tmp1, tmp2)` : #tmp1에 대한 tmp2 파라미터의 gradient(편미분)값 반환

  >`tmp1` 은 GradientTape()에 의한 스코프 안의 손실함수의 결과값 인자로 가져온다.
  >
  >`tmp2` 는 가설정의에 쓰인 파라미터를 인자로 가져온다.

**예시**

```python
with tf.GradientTape() as tape:
    y_pred = linear_model(x)   #가설함수
    loss = mse_loss(y_pred, y) #손실함수
gradients = tape.gradient(loss, [w, b] ) #w, b가 가설함수의 파라미터값이라고 가정 
```





### 3. apply_gradients()

gradient 값을 통하여 theta 값을 얻어내기 위한 그래프를 생성하는 함수다.

최적화 도구에 쓰이기 때문에 `optimizer.apply_gradients` 형태로 사용되며 이를 통해 파라미터 갱신이 이루어지게 된다.
$$
\theta_{i+1} 를\ 구하는\ 과정이다
$$
**예시**

```python
optimizer.apply_gradients(zip(gradients, [w, b]))
```



### 전체 코드 예시(선형 회귀)

> 완성된 코드 아님

```python
# 선형 회귀(Linear Regression) 알고리즘

import tensorflow as tf

# 선형회귀 모델(Wx + b)을 위한 tf.Variable을 선언
W = tf.Variable(tf.randem.normal(shape = [1]))
b = tf.Variable(tf.randem.normal(shape = [1]))

#-----------가설 정의-----------
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

```





