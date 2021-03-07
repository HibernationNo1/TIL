# Linear Regression(선형 회귀)

모든 딥러닝 모델은 **가설 정의** -> **손실함수 정의** -> **최적화 정의** 를 거쳐야 한다.



### 1. 가설 정의

$$
가설:\ y = Wx+b 
\\ W, b: 파라미터 \ \ \ \ x: input데이터 \ \ \ y: 정답\ 데이터
$$

```python
@tf.function
def linear_model(x):   # x: input 데이터
    return W*x + b     # Linear Regression 수식 정의
```

> x와 y는 정답이 주어지게 되며 이를 통해  가설이 정답에 가까워지는 식이 완성될 것이다.
>
> 내가 설정한 가설 `W*x + b` 을 리턴한다.

초기 파라미터는 랜덤으로 주자.

```python
# 선형회귀 모델(Wx + b)을 위한 tf.Variable을 선언
W = tf.Variable(tf.random.normal(shape = [1]))
b = tf.Variable(tf.random.normal(shape = [1]))
```



### 2. 손실함수 정의

손실함수는 여러 종류 중 MSE를 사용해보자.
$$
MSE 식:\ J(\theta) = \frac {1} {2n} \sum_{j=1}^{n}(\widehat{y_i} - y_i)^{2}
$$

$$
\widehat{y_i} : 모델의\ 예측\ 값, \ \  	y_i : 정답\ 값, \ \ \frac {1} {2n}: 평균 \ 을\ 의미함
$$

```python
# MSE 손실함수
@tf.function
def mse_loss(y_pred, y): # y_pred: 모델이 예측한 값,  y실제 값
    return tf.reduce_mean(tf.square(y_pred - y))   #(y'-y)^2 의 평균
```

> 모델이 예측한 값과 실제 값을 인자로 받아온다.
>
> 손실함수 식:  reduce_mean을 통해 평균을 계산(square를 통해 제곱을 계산(예측한 값 - 실제 값))



### 3. 최적화 정의

최적화를 위한 확률적 경사하강법 최적화(스토우케스틱 그라디언트 디센트 옵티마이저)를 정의해보자.

- 경사하강법은 다음 수식처럼 손실 함수의 미분값과 러닝 레이트의 곱만큼을 원래 파라미터에 뺀 값으로 파라미터를 한 스텝 업데이트 하는 것.

  
  $$
  \theta_{i+1} = \theta_i - \alpha \frac{\partial}{\partial \theta_i}Cost(\theta_0, \theta_1)
  $$
  

  - 선형회귀 모델(y  = Wx)을 사용하고 손실함수로 평균제곱오차(MES)를 사용할 경우  확률적 경사하강법(SGD)의 한 스텝 업데이트를 위해 계산하는 손실함수의 미분값

  $$
  \frac{\partial}{\partial \theta_0}Cost(\theta_0, \theta_1) = \frac {\partial}{\partial \theta_0} \frac{1}{2n}(\widehat{y} - y)^2
  $$

  $$
  \frac{\partial}{\partial \theta_1}Cost(\theta_0, \theta_1) = \frac {\partial}{\partial \theta_1} \frac{1}{2n}(\widehat{y} - y)^2
  $$

**코드**

```python
optimizer = tf.optimizers.SGD(0.01)
```

> `tf.optimizers.SGD()`:여러 optimizer방법 중 확률적 경사하강법(SGD) 사용
>
> learing rage = 0.01



```python
# 최적화를 위한 function
@tf.function
def train_step(x, y): 
    with tf.GradientTape() as tape: 
        y_pred = linear_model(x)    # linear_model 함수에 기반한 예측결과
        loss = mse_loss(y_pred, y)  # 예측결과값과 실제 값을 매개로 MSE 손실함수 적용
    gradients = tape.gradient(loss, [W, b])     
    optimizer.apply_gradients(zip(gradients, [W, b]))
```

> `def train_step`: 경사하강법을 한번 실행해주는 함수. 이러한 함수는 관례적으로 train_step이라고 이름을 짖는다.
>
> `with tf.GradientTape() as tape` : GradientTape에 예측결과값과 손실함수 값을 저장하기 위해 GradientTape scope를 정의한다.
>
> `gradients = tape.gradient(loss, [W, b])` : loss에 대한 w, b 파라미터의 gradient(편미분)값 계산
>
> `optimizer.apply_gradients(zip(gradients, [W, b]))`
>
> - `apply_gradients()`: gradient 값을 통하여 theta 값을 얻어내기 위한 그래프 생성
> - zip의 인자: (계산한 gradient, 갱신 대상으로 사용할 파라미터 )
> - `SGD`에 `apply_gradients()` 적용: `optimizer.apply_gradients` 에 의해 파라미터 갱신이 1회 이루어지게 된다.





### 4. 트레이닝 과정

```python
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





## 전체 코드

```python
# 선형 회귀(Linear Regression) 알고리즘
import tensorflow as tf

# 선형회귀 모델(Wx + b)을 위한 tf.Variable을 선언
W = tf.Variable(tf.random.normal(shape = [1]))
b = tf.Variable(tf.random.normal(shape = [1]))

#-----------가설 정의(모델 구조 정의)-----------
@tf.function
def linear_model(x):  
    return W*x + b    

#-----------손실함수 정의-----------
@tf.function
def mse_loss(y_pred, y): 
    return tf.reduce_mean(tf.square(y_pred - y))  


#-----------최적화 정의-----------
optimizer = tf.optimizers.SGD(0.01) 

@tf.function
def train_step(x, y):  
    with tf.GradientTape() as tape: 
        y_pred = linear_model(x)    
        loss = mse_loss(y_pred, y)  
    gradients = tape.gradient(loss, [W, b])    
    optimizer.apply_gradients(zip(gradients, [W, b]))



#-----------트레이닝 과정-----------
x_train = [1, 2, 3, 4]  
y_train = [2, 4, 6, 8]

for i in range(1000):
    train_step(x_train, y_train)

x_test = [3.5, 5, 5.5, 6]
print(linear_model(x_test))
```

