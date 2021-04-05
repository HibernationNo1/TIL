# Linear Regression(선형 회귀)

## 개념

input data에 대한 output data가 training data로 인해 이루어진 연속된 값으로 나타나는 것을 Linear Regression이라고 한다.

**선형 회귀 모델**: 함수f(x)에서, 우리가 알고 있는 x의 값과 y의 값을 데이터로 사용하여 우리가 알지 못하는 x의 값에 대한 y의 값을 유추할 수 있는 모델

- 예)

  함수 f(x)를 H(W, b)라는 함수라고 지칭하고, H(W, b) = Wx+b라는 수식이 있을 때

  W =  2 이고 b = 1인, 즉 y = 2x+1인 함수를 컴퓨터에게 학습시키는 과정

  **목표**  y = Wx+b가 y = 2x+1이 되는 W, b값을 컴퓨터가 알게 한다.

  **과정**  반복적인 회귀를 통해 W, b값을 찾아나가며 올바른 값에 가까워지도록 컴퓨터에 학습시킨다.

- 가설 정의

  y = Wx+b 형태의 식이 만족함을 컴퓨터에게 알려주고, W와 b를 임의의 값으로 전달해준다.

  임의로 전달된 W와 b가 정답과는 얼마나 다른지를 알려주는 함수를 **cost function(손실함수)** 라고 한다.



### Finding Optimal 과정

- **Model**
  $$
  Model => \ \  \widehat{y} = \theta_1 x + \theta_0\\
  $$

- **Loss function**
  $$
  Loss => \ \ L = (y^{(i)} - \widehat{y}^{(i)})^2 = (y^{(i)}-(\theta_1 x^{(i)} + \theta_0))^2 \\
  즉,\ L^{(i)}(\theta_1, \theta_0) = (y^{(i)}-(\theta_1 x^{(i)} + \theta_0))^2 \\
  $$

- **Cost function**
  $$
  Cost => \ \  J(\theta_1, \theta_0) = \frac{1}{n}\sum_{i=1}^{n}\left [ (y^{(i)}-(\theta_1 x^{(i)} + \theta_0))^2 \right ]
  $$

- **Gradients**
  $$
  \bigtriangledown _{(\theta_1, \theta_0)}L^{(i)}(\theta_1, \theta_0) = \left (    \frac{\part L^{(i)}(\theta_1, \theta_0)}{\part \theta_1}\ , \  \frac{\part L^{(i)}(\theta_1, \theta_0)}{\part \theta_0}  \right )\\
  \bigtriangledown _{(\theta_1, \theta_0)}  J(\theta_1, \theta_0) =\left ( \frac{\part J(\theta_1, \theta_0)}{\part \theta_1}\ ,\ \ \frac{\part J(\theta_1, \theta_0)}{\part \theta_0} \right )
  $$
  각각의 theta에 대한 Gradient를 원소로 갖는 벡터가 만들어진다.

  - Gradients Descent Method
    $$
    (\theta_1, \theta_0):= (\theta_1, \theta_0) - \alpha \left ( \frac{\part J(\theta_1, \theta_0)}{\part \theta_1}\ ,\ \ \frac{\part J(\theta_1, \theta_0)}{\part \theta_0} \right )
    $$
    각각의 theta(n)은 target theta(n)에 가까워지는 updata가 이루어질 것이다. 



- **Loss Function에 대한 Gradient Descent Method**

  **Loss Partial Derivates** 

  여기서 Loss에서 theta에 대한 partial derivate는 theta_1(= weight), theta_2(= bais) 이렇게 두 가지가 있다. 
  $$
  \frac{\part L(\theta_1, \theta_0)}{\part \theta_1} = -2x(y-(\theta_1 x + \theta_0)) \\ = -2x(y - \widehat{y})
  \\
  \frac{\part L(\theta_1, \theta_0)}{\part \theta_0} = -2(y-(\theta_1 x + \theta_0)) \\ = -2(y - \widehat{y})
  $$
  **Loss Gradient**

   theta_1(= weight), theta_2(= bais)에 대해서 각각 적용되어야 한다.
  $$
  \bigtriangledown _{(\theta_1, \theta_0)}L(\theta_1, \theta_0) = \left (\frac{\part L(\theta_1, \theta_0)}{\part \theta_1}, \ \frac{\part L(\theta_1, \theta_0)}{\part \theta_0}  \right ) =  \left ( -2x(y - \widehat{y}) ,\ -2(y - \widehat{y})  \right )\
  $$
  이고, 
  $$
  \overrightarrow{\theta}:= \overrightarrow{\theta} - \alpha \bigtriangledown _{\overrightarrow{\theta}}L(\overrightarrow{\theta}) \ \\
  $$
  이므로 아래의 식이 성립된다.
  $$
  (\theta_1, \theta_0) := (\theta_1, \theta_0) -\alpha\left (\frac{\part L(\theta_1, \theta_0)}{\part \theta_1}, \ \frac{\part L(\theta_1, \theta_0)}{\part \theta_0}  \right )
  $$
  즉, Gradient Descent Method는 아래 식으로 표현할 수 있다.
  $$
  \theta_1 := \theta_1 + 2\alpha x(y - \widehat{y})\\
  \theta_0 := \theta_0 + 2\alpha (y - \widehat{y})
  $$
  여기서 theta_1의 parameter updata의 방향은 x, y값의 양 또는 음의 값에 따라서 달라진다.

  ![](https://github.com/HibernationNo1/TIL/blob/master/image/18.jpg?raw=true)

  하지만 theta_2의 parameter updata의 방향은 y값에만 영향을 받는다.

  ![](https://github.com/HibernationNo1/TIL/blob/master/image/19.jpg?raw=true)



- **Cost Function에 대한 Gradient Descent Method**

  **Cost Partial Derivates** 
  $$
  \frac{\part J(\theta_1, \theta_0)}{\part \theta_1} = \frac{\part}{\part \theta_1} \left [\frac{1}{n}\sum_{i=1}^{n} \frac{\part L(\theta_1, \theta_0)}{\part \theta_1}  \right ] =-\frac{1}{n}\sum_{i=1}^{n}\left [2x^{(i)}(y^{(i)} - \widehat{y}^{(i)})\right ]\\
  \frac{\part J(\theta_1, \theta_0)}{\part \theta_0} = \frac{\part}{\part \theta_1} \left [\frac{1}{n}\sum_{i=1}^{n} \frac{\part L(\theta_1, \theta_0)}{\part \theta_0}  \right ] =-\frac{1}{n}\sum_{i=1}^{n}\left [2(y^{(i)} - \widehat{y}^{(i)})\right ]
  $$
  

  **Cost Gradient**
  $$
  \bigtriangledown _{(\theta_1, \theta_0)}J(\theta_1, \theta_0) = \left ( -\frac{1}{n}\sum_{i=1}^{n}\left [2x^{(i)}(y^{(i)} - \widehat{y}^{(i)})\right ],\ -\frac{1}{n}\sum_{i=1}^{n}\left [2(y^{(i)} - \widehat{y}^{(i)})\right ] \right )
  $$
  이므로 
  $$
  (\theta_1, \theta_0) := (\theta_1, \theta_0) -\alpha\left (\frac{\part J(\theta_1, \theta_0)}{\part \theta_1}, \ \frac{\part J(\theta_1, \theta_0)}{\part \theta_0}  \right )
  $$
  즉, Gradient Descent Method는 아래 식으로 표현할 수 있다.
  $$
  \theta_1 := \theta_1 -\frac{\alpha}{n}\sum_{i=1}^{n}\left [2x^{(i)}(y^{(i)} - \widehat{y}^{(i)})\right ]\\
  \theta_0 := \theta_0 -\frac{\alpha}{n}\sum_{i=1}^{n}\left [2(y^{(i)} - \widehat{y}^{(i)})\right ]
  $$



이 과정에서 data semple(x_i, y_i)에 값을 할당하면 알 수 있듯, x값을 계수로 갖는 theta_1과 계수가 없는 theta_0은 data값에 따라서 학습속도에 차이를 보일 수 밖에 없다. 

그리고 learning rate는 x값을 계수로 갖는 theta_1과 계수가 없는 theta_0 둘 다에 적용되기 때문에 발산에 대한 문제도 발생할 수 있다.

> theta_1에 알맞은 크기의 learning rate을 적용하면 theta_0의 학습속도가 너무 느릴 수 있고, theta_0에 알맞은 크기의 learning rate을 적용하면 theta_1이 너무 커져서 발산할 위험이 있다.



---



## 구현(tensorflow)

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

