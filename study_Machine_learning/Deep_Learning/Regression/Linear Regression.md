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

#### 식 표현

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
  \frac{\part J(\theta_1, \theta_0)}{\part \theta_1} = \frac{\part}{\part \theta_1} \left [\frac{1}{n}\sum_{i=1}^{n} L(\theta_1, \theta_0)  \right ] =-\frac{1}{n}\sum_{i=1}^{n}\left [2x^{(i)}(y^{(i)} - \widehat{y}^{(i)})\right ]\\
  \frac{\part J(\theta_1, \theta_0)}{\part \theta_0} = \frac{\part}{\part \theta_1} \left [\frac{1}{n}\sum_{i=1}^{n} L(\theta_1, \theta_0) \right ] =-\frac{1}{n}\sum_{i=1}^{n}\left [2(y^{(i)} - \widehat{y}^{(i)})\right ]
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



#### 식 전개, 분석

위 식은 간단하게 표현한 것으로, 해당 식을 전개해보면 아래와 같다.

##### **Loss**

Loss function은 아래와 같다.
$$
L^{(i)}(\theta_1, \theta_0) = (y^{(i)}-(\theta_1 x^{(i)} + \theta_0))^2 \\
= x^2(\theta_1)^2 + (\theta_0)^2 - 2xy\theta_1 - 2y\theta_0 + 2x\theta_1 \theta_0 + y^2
$$
위 식에 partial derivates를 적용하면 
$$
\frac{\part L(\theta_1, \theta_0)}{\part \theta_1}  = 2x(x\theta_1 + \theta_0 - y)
\\
 \frac{\part L(\theta_1, \theta_0)}{\part \theta_0} = 2(\theta_0 + x\theta_1 - y)
$$
 Loss에 대한 Gradient Descent Method는 아래와 같다.
$$
\theta_1 := \theta_1 + 2\alpha x(x\theta_1 + \theta_0 - y)\\
\theta_0 := \theta_0 + 2\alpha (\theta_0 + x\theta_1 - y)
$$

> 이 때 x에 어떤 값을 넣느냐에 따라서 theta_0과 theta_1의 학습 속도의 차이를 확인할 수 있다. (y는 크게 의미가 없기 때문에 y = 0이고, learning rate은 고정을 위해 1 이라고 가정)
>
> ![](https://github.com/HibernationNo1/TIL/blob/master/image/20.jpg?raw=true)
>
> 왼쪽 이미지는 x의 값이 음수인 경우, 오른쪽 이미지는 x의 값이 양수인 경우에 따라 각 theta값의 학습 속도의 차이를 보여준다.
>
> - x의 값이 음수인 경우 
>
>   x값의 절대값이 작을수록 theta_1의 학습 속도보다 theta_0의 학습 속도가 높고
>
>   x값이 절대값이 클수록 theta_0의 학습 속도보다 theta_1의 학습 속도가 빠름을 알 수 있다.
>
> - x의 값이 양수인 경우
>
>    x의 값이 음수인 경우와 반대의 결과을 볼 수 있다.
>
> 즉 x의 절대값이 클수록 발산의 위험이 커지고, x의 절대값이 작을수록 학습속도가 느려진다는 것이며 더욱 중요한 것은, x의 절대값이 1에 가까울수록 두 theta의 학습 속도가 비슷해진다는 것이다.
>
> 그래서 우리는 두 theta의 학습 속도를 맞추기 위해 입력 data의 절대값을 1로 맞추기 위한 작업인 **Feature Scaling**을 하는 것이다.

각각의 data에 대해서 loss function에서 Gradient Descent Method를 통해 theta를 updata하기 때문에 하나의 큰 값의 data에 의해서 발산할 위험또한 높음을 알 수 있다. 이를 방지하기 위해 Cost를 활용해보자.



##### **Cost**

위의 Loss식에 의해 Cost function의 partial derivates는 아래와 같다.
$$
\frac{\part J(\theta_1, \theta_0)}{\part \theta_1} = \frac{\part}{\part \theta_1} \left [\frac{1}{n}\sum_{i=1}^{n} L(\theta_1, \theta_0) \right ] = \frac{1}{n}\sum_{i=1}^{n} \frac{\part L(\theta_1, \theta_0)}{\part \theta_1} \\ 
= -\frac{1}{n}\sum_{i=1}^{n}\left [2x(x\theta_1 + \theta_0 - y)\right ]
\\
\frac{\part J(\theta_1, \theta_0)}{\part \theta_0} = \frac{\part}{\part \theta_0} \left [\frac{1}{n}\sum_{i=1}^{n} L(\theta_1, \theta_0)  \right ] =\frac{1}{n}\sum_{i=1}^{n} \frac{\part L(\theta_1, \theta_0)}{\part \theta_0} \\ 
=-\frac{1}{n}\sum_{i=1}^{n}\left [2(\theta_0 + x\theta_1 - y)\right ]
$$
즉, Gradient Descent Method는 아래 식으로 표현할 수 있다
$$
\theta_1 := \theta_1 -\frac{\alpha}{n}\sum_{i=1}^{n}\left [2x(x\theta_1 + \theta_0 - y)\right ]\\
\theta_0 := \theta_0 -\frac{\alpha}{n}\sum_{i=1}^{n}\left [2(\theta_0 + x\theta_1 - y)\right ]
$$



cost는 data 각각의 loss들의 평균이기 때문에 function 자체가 하나만 존재함을 기억해보자. (가장 이상적인 function 모양은 구 형태의 밥그릇 모양임을 기억하자.)

- 가장 이상적인 cost function을 구하기 위한 조건 2가지

  1. 0에 대칭적인 data set

  2. 양, 음의 평균 절대값이 1인 data set

  
즉, 0에 대칭적이면서 양, 음수 data들의 평균에 절대값을 씌우면 1이 나오는 data set이 학습이 가장 이상적인 data set이라는 것을 알 수 있다.
  
이러한 data set이 바로 **standard normal distribution**(표준 정규분포)이다.
  
![](https://cdn.scribbr.com/wp-content/uploads/2020/10/standard-normal-distribution-1024x633.png)

그렇다면 normal distribution에서 어떻게 standard normal distribution으로 값을 바꿀 수 있을까?  

- Feature Scaling - standardiztion(표준화)
  $$
  x : data, \ \ \ \mu: mean, \ \ \ \sigma: std
  \\ x:= \frac{x - \mu}{\sigma}
  $$
  

이 때, Feature Scaling을 통해 새롭게 만들어진 data set은 우리가 처음에 선택한 data set과는 전혀 다른 data를 가지고 있기 되기 때문에, 이 data set으로 training을 하게 되면 해당 모델은 실제 test data set을 그대로 받았을 때 전혀 다른 prediction을 보여준다.

그렇기 때문에 우리는 traning data set을 Feature Scaling하고, 학습이 끝난 모델에 test data set을 입력할 때도 Feature Scaling을 수행해주어야 한다. 이후 결과로 나온 prediction은 Feature Scaling의 역 연산을 통해 우리가 최종적으로 기대하는 올바른 prediction으로 바꿔주여야 한다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/21.jpg?raw=true)



###### Batch size

data 전체를 batch로 결정한다면 cost function의 모양은 가장 이상적이겠지만, 이후에 사용하게 될 artificial에서 batch size가 너무 크면 복잡한 함수의 연산이 이루어지기 때문에 모델이 너무 무거워진다는 단점이 있다. 그렇기 때문에 batch size를 적당히 작게 결정하는 mini batch size의 원리에 따르는 것이 좋다. (보통 batch size는 32로 결정한다고 한다.)



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

