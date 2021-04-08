# MVLR(다변수 선형 회귀)

## 개념

input data에 대한 output data가 training data로 인해 이루어진 연속된 값으로 나타나는 것을 Linear Regression이라고 한다.



**단일 변수 선형 회귀 모델**: 입력 데이터 x가 column vector의 형태로, 변수x가 1개인 선형 회귀 모델을 의미한다.
$$
Single\ variate\ Linear\ regession\ 에서의\ Dataset = \{(x^{(i)}, y^{(i)} ) \}\\
$$


**다변수 선형 회귀 모델**: 입력 데이터 x가 column vector의 형태로, 변수x가 2개 이상인 선형 회귀 모델을 의미한다.


$$
Multi\ variate \ Linear\ regession\ 에서의\ dataset = \{(\overrightarrow{x}^{(i)}, y^{(i)}) \} \\
\overrightarrow{x}^{(i)} = \begin{pmatrix}
x^{(i)}_1
\\ 
x^{(i)}_2
\\ 
\vdots 
\\ 
x^{(i)}_m
\end{pmatrix}
$$

---



### Finding Optimal 과정

Multi-variate  Linear Regession에서의 Finding Optimal 과정은 아래 순서를 따라간다.

1. forward propagation 
   1. data를 입력받는다.
   2. 입력된 data에  weight와 bias를 dot product해서 Affine Function을 만든다.
2. back propagation
   1. Affine Function으로부터 Loss function을 구한다.
   2. Loss function으로부터 Cost function을 구한다.
   3. Cost function의 gradient desent를 구한다.
   4. gradient desent를 통해 gradient desent mothod를 만들어 theta를 updata한다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/24.jpg?raw=true)

#### 식 표현

- **Model**
  $$
  \overrightarrow{\theta} = \begin{pmatrix}
  \theta_0
  \\
  \theta_1
  \\ 
  \theta_2
  \\ 
  \vdots 
  \\ 
  \theta_m
  \end{pmatrix}
  \ \ \ \ \ \ \ \ \ \ 
  \overrightarrow{x} = \begin{pmatrix}
  1
  \\
  x_1
  \\ 
  x_2
  \\ 
  \vdots 
  \\ 
  x_m
  \end{pmatrix}
  \\ \overrightarrow{y} = \overrightarrow{\theta^T}\cdot  \overrightarrow{x}
  $$
  즉,
  $$
  \widehat{y} = \theta_n x_n + \theta_{n-1} x_{n-1} + ... +  \theta_{2} x_{2} + \theta_{1} x_{1} + \theta_{0}
  $$
  

- **Loss**
  $$
  L(\overrightarrow{\theta}) = (y-\widehat{y})^2 = (y-\overrightarrow{\theta^T} \overrightarrow{x})^2
  $$



- **Cost**
  $$
  J(\overrightarrow{\theta}) = \frac{1}{n}\sum_{i=1}^{n} (y^{(i)} - \overrightarrow{\theta^{T}} \overrightarrow{x^{(i)}})^2
  $$
  

#### 식 전개

>  x = {x_2, x_1} 만 있다고 가정 (data set이 2개의 값을 가진 x로 이루어져 있다고 가정)
>
> theta는 세 개가 된다. { theta_2, theta_1, theta_0 }  두 개의 wight와 한 개의 bias

- **Loss**

$$
L(\theta_2, \theta_1, \theta_0) = (y - (\theta_2 x_2 + \theta_1 x_1 + \theta_0))^2
$$

​	 Loss의 Partial Derivatives
$$
. \frac{\part L(\theta_2, \theta_1, \theta_0)}{\part \theta_2} = \frac{\part}{\part \theta_2} \left[ (y - (\theta_2 x_2 + \theta_1 x_1 + \theta_0))^2 \right] \\
= (y - (\theta_2 x_2 + \theta_1 x_1 + \theta_0))\frac{\part}{\part\theta_1}\left[(y - (\theta_2 x_2 + \theta_1 x_1 + \theta_0)) \right]\\
= -2x_2(y - (\theta_2 x_2 + \theta_1 x_1 + \theta_0))
$$
​	위의 식 처럼
$$
. \frac{\part L(\theta_2, \theta_1, \theta_0)}{\part \theta_1} = -2x_1(y - (\theta_2 x_2 + \theta_1 x_1 + \theta_0))
$$

$$
. \frac{\part L(\theta_2, \theta_1, \theta_0)}{\part \theta_0} = -2(y - (\theta_2 x_2 + \theta_1 x_1 + \theta_0))
$$

- **Gradient**
  $$
  \bigtriangledown _{(\theta_2, \theta_1, \theta_0)}L(\theta_2, \theta_1, \theta_0) = \left ( \frac{\part L(\theta_2, \theta_1, \theta_0)}{\part \theta_2},\ \frac{\part L(\theta_2, \theta_1, \theta_0)}{\part \theta_1},\ \frac{\part L(\theta_2, \theta_1, \theta_0)}{\part \theta_0}  \right)
  $$
  

- **Gradient Desent Method**
  $$
  (\theta_2, \theta_1, \theta_0):= (\theta_2, \theta_1, \theta_0) - \alpha\bigtriangledown _{(\theta_2, \theta_1, \theta_0)}L(\theta_2, \theta_1, \theta_0)
  $$

  $$
  \theta_2  := \theta_2 + 2\alpha x_2(y - (\theta_2 x_2 + \theta_1 x_1 + \theta_0))\\
  \theta_1  := \theta_1 + 2\alpha x_1(y - (\theta_2 x_2 + \theta_1 x_1 + \theta_0))\\
  \theta_0  := \theta_0 + 2\alpha(y - (\theta_2 x_2 + \theta_1 x_1 + \theta_0))
  $$

  

- **Cost**
  $$
  J(\theta_2, \theta_1, \theta_0) = \frac{1}{n}\sum_{i=1}^{n}(y^{(i)} - (\theta_2 x_2^{(i)} + \theta_1 x_1^{(i)} + \theta_0))^2
  $$
  Coss의 Partial Derivatives
  $$
  \frac{\part J(\theta_2, \theta_1, \theta_0)}{\part \theta_2}= \frac{\part}{\part \theta_2}\left[ \frac{1}{n}\sum_{i=1}^{n}(y^{(i)} - (\theta_2 x_2^{(i)} + \theta_1 x_1^{(i)} + \theta_0))^2 \right]\\
  = \frac{1}{n}\sum_{i=1}^{n}\frac{\part}{\part \theta_2}\left[ (y^{(i)} - (\theta_2 x_2^{(i)} + \theta_1 x_1^{(i)} + \theta_0))^2 \right] \\
  = -\frac{1}{n}\sum_{i=1}^{n} \left[ 2x_2^{(i)}(y^{(i)} - (\theta_2 x_2^{(i)} + \theta_1 x_1^{(i)} + \theta_0)) \right]
  $$
  위의 식 처럼
  $$
  \frac{\part J(\theta_2, \theta_1, \theta_0)}{\part \theta_1} = -\frac{1}{n}\sum_{i=1}^{n} \left[ 2x_1^{(i)}(y^{(i)} - (\theta_2 x_2^{(i)} + \theta_1 x_1^{(i)} + \theta_0)) \right]
  \\
  \frac{\part J(\theta_2, \theta_1, \theta_0)}{\part \theta_0} = -\frac{1}{n}\sum_{i=1}^{n} \left[ 2(y^{(i)} - (\theta_2 x_2^{(i)} + \theta_1 x_1^{(i)} + \theta_0)) \right]
  $$

- **Gradient**
  $$
  \bigtriangledown _{(\theta_2, \theta_1, \theta_0)}J(\theta_2, \theta_1, \theta_0) = \left ( \frac{\part J(\theta_2, \theta_1, \theta_0)}{\part \theta_2},\ \frac{\part J(\theta_2, \theta_1, \theta_0)}{\part \theta_1},\ \frac{\part J(\theta_2, \theta_1, \theta_0)}{\part \theta_0}  \right)
  $$
  

- **Gradient Desent Method**
  $$
  (\theta_2, \theta_1, \theta_0):= (\theta_2, \theta_1, \theta_0) - \alpha\bigtriangledown _{(\theta_2, \theta_1, \theta_0)}J(\theta_2, \theta_1, \theta_0)
  $$

  $$
  \theta_2  := \theta_2 + \frac{\alpha}{n}\sum_{i=1}^{n} \left[ 2x_2^{(i)}(y^{(i)} - (\theta_2 x_2^{(i)} + \theta_1 x_1^{(i)} + \theta_0)) \right]\\
  \theta_1  := \theta_1 + \frac{\alpha}{n}\sum_{i=1}^{n} \left[ 2x_1^{(i)}(y^{(i)} - (\theta_2 x_2^{(i)} + \theta_1 x_1^{(i)} + \theta_0)) \right]\\
  \theta_0  := \theta_0 + \frac{\alpha}{n}\sum_{i=1}^{n} \left[ 2(y^{(i)} - (\theta_2 x_2^{(i)} + \theta_1 x_1^{(i)} + \theta_0)) \right]
  $$

![](https://github.com/HibernationNo1/TIL/blob/master/image/25.jpg?raw=true)



data set이 n개일 때

![](https://github.com/HibernationNo1/TIL/blob/master/image/26.jpg?raw=true)



---

### 각 theta간의 관계

학습이 진행되는 동안 각 theta간의 관계를 고려하면 각각의 theta가 어떤 속도로 학습을 진행하게 되는지 유추해볼 수 있다.
$$
\frac{\part L}{\part \theta_2} = -2 x_2(y - \widehat{y}) \\
\frac{\part L}{\part \theta_1} = -2 x_1(y - \widehat{y})\\
\frac{\part L}{\part \theta_0} = -2(y - \widehat{y})\\
\Delta\theta_2 : \Delta\theta_1 : \Delta\theta_0 = x_2 : x_1 : 1
$$
x_2의 값이 크면 theta_2의 학습 속도가 빨라지지만, theta_0의 학습 속도는 느려지게 된다. 이를 통해 x_2와 x_1의 크기는 theta_0에는 영향을 주지만, weight인 서로에게는 영향을 주지 않음을 알 수 있다.



이를 바탕으로 data set의 mean과 std를 고려함으로써 각각의 theta가 어떤 속도로 학습을 진행하게 되는지 유추해볼 수 있다.

원리는 single-variate Linear Regression과 같다. 단지 data set이 x 에서 x_2, x_1으로 늘어난 것일 뿐이다.  

- **std**

  x_2 data set의 std가 1보다 크고 x_1data set의 std는 1이면 theta_2가 theta_1과 theta_0에 비교해서 더욱 빠른 속도로 학습을 하게 된다.

  마찬가지로 (x_2 std, x_1 std) = (1, 5)일 때 theta_1이 theta_2와 theta_0에 비교해서 더욱 빠른 속도로 학습을 하게 된다.

  역시 (x_2 std, x_1 std) = (3, 5)가 된다면 theta_0 대비 theta_2, theta_1이 더욱 빠른 속도로 학습을 하게 된다. 그리고 theta_2가 theta_1보다 더욱 빠른 속도로 학습을 하게 됨을 알 수 있다.

  이를 통해 data set의 std에 따라서 각각 x의 계수인 theta의 학습 속도가 결정됨을 알 수 있다. (std 는 theta의 학습 속도와 비례하고, 가장 최적의 std는 1이다. ) 

  > x_0 == 1이고, 1의 계수는 bias인 theta_0이다. x_0의 mean은 0이고, std는 1이며 불변임으로 x_0가 최적의 mean과 std의 기준이 되게 된다.

- **mean**

  x_2의 mean이 커지면 theta_2의 updata 변화량이 커지게 된다(학습 속도가 빨라진다).
  $$
  \Delta\theta_2 : \Delta\theta_1 : \Delta\theta_0 = x_2(mean) : x_1(mean) : 1
  $$
   

