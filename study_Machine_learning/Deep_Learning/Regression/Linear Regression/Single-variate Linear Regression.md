# SVLR(단일 변수 선형 회귀)

## 개념

input data에 대한 output data가 training data로 인해 이루어진 연속된 값으로 나타나는 것을 Linear Regression이라고 한다.

**단일 변수 선형 회귀 모델**: 입력 데이터 x가 column vector의 형태로, 변수가 1개인 선형 회귀 모델을 의미한다.



### Finding Optimal 과정

Single-variate  Linear Regession에서의 Finding Optimal 과정은 아래 순서를 따라간다.

1. forward propagation 
   1. data를 입력받는다.
   2. 입력된 data에  weight와 bias를 dot product해서 Affine Function을 만든다.
2. back propagation
   1. Affine Function으로부터 Loss function을 구한다.
   2. Loss function으로부터 Cost function을 구한다.
   3. Cost function의 gradient desent를 구한다.
   4. gradient desent를 통해 gradient desent mothod를 만들어 theta를 updata한다.

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
  ![](https://github.com/HibernationNo1/TIL/blob/master/image/22.jpg?raw=true)

  
  
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
이 과정 속에서의 back propagation에서, 벡터의 chain rule은 벡터끼리의 곱이 아닌 hadamard product이 적용되어야 한다. 



##### **standardiztion**

cost는 data 각각의 loss들의 평균이기 때문에 function 자체가 하나만 존재함을 기억해보자. (가장 이상적인 function 모양은 구 형태의 밥그릇 모양임을 기억하자.)

- 가장 이상적인 cost function을 구하기 위한 조건 2가지

  1. mean이 0인 data set

     > mean의 절대값이 커질수록 cost fuction의 모습이 접히는(계곡) 형태로 만들어지게 된다. 

  2. std 가 1인 data set 
  
     > std 가 0에 가까워지면 theta_0의 학습만 효율적이게 되고, std가 1보다 커질수록  theta_1의 학습만 효율적이게 된다.
  
  

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

![](https://github.com/HibernationNo1/TIL/blob/master/image/23.jpg?raw=true)





---



## 코드 구현

### 1. basic_node

```python
import numpy as np

class plus_node():
    def forward(self, x, y):
        self._x, self._y = x, y
        self._z = self._x + self._y
        return self._z
    
    def backward(self, dz):
        return dz

class mul_node():
    def forward(self, x, y):
        self._x, self._y = x, y
        self._z = self._x*self._y
        return self._z

    def backward(self, dz):
        return (dz*self._y, dz*self._x)

class minus_node():
    def forward(self, x, y):
        self._x, self._y = x, y
        self._z = self._x - self._y
        return self._z

    def backward(self, dz):
        return -1*dz

class square_node():
    def forward(self, x):
        self._x = x
        self._z = self._x*self._x
        return self._z

    def backward(self, dz):
        return (2*dz*self._x)

class mean_node():
    def forward(self, x):
        self._x = x
        self._z = np.mean(self._x)
        return self._z

    def backward(self, dz):
        dx = dz*1/len(self._x)*np.ones_like(self._x)
        return dx 
```



### 2. SVLR

```python
import basic_node as nodes
import numpy as np

class SVLR:
    def __init__(self, th1, th0):
        self.th1, self.th0 = th1, th0

    def model_imp(self):
        self.node1 = nodes.mul_node()
        self.node2 = nodes.plus_node()
    
    def cost_imp(self):
        self.node3 = nodes.minus_node()
        self.node4 = nodes.square_node()
        self.node5 = nodes.mean_node()

    def forward(self, mini_batch): 
        Z1 = self.node1.forward(self.th1, mini_batch[:, 0])
        Z2 = self.node2.forward(Z1, self.th0)
        Z3 = self.node3.forward(mini_batch[:, 1], Z2)
        L = self.node4.forward(Z3)
        J = self.node5.forward(L)

    def backward(self, lr):
        dL = self.node5.backward(1)
        dZ3 = self.node4.backward(dL)
        dZ2 = self.node3.backward(dZ3)
        dZ1, dTh0 = self.node2.backward(dZ2)
        dTh1 = self.node1.backward(dZ1) 

        self.th1 = self.th1 - lr*np.sum(dTh1)
        self.th0 = self.th0 - lr*np.sum(dTh0)

```



### 3. main

```python
import numpy as np
import basic_node as nodes
from dataset_generator import dataset_generator
import SVLR

np.random.seed(0)

t_th1, t_th0 = 5, 5     # target theta
th1, th0 = 1, 1

distribution_params = {'feature_0': {'mean' : 0, 'std' : 1}}

lr = 0.01
epochs = 10
batch_size = 4

def get_data_batch(data, batch_idx):
    if batch_idx is n_batch-1:
        batch = data[batch_idx*batch_size : ]
    else :
        batch = data[batch_idx*batch_size : (batch_idx + 1) * batch_size]
    return batch


dataset_gen = dataset_generator()
dataset_gen.set_coefficient([t_th1, t_th0])
dataget_gen.set_distribution_params(distribution_params)
x_data, y_data = dataset_gen.make_dataset()
data = np.hstack((x_data, y_data))
n_batch = np.ceil(data.shape[0] / batch_size).astype(int)


model = SVLR(th1, th0)

for epoch in range(epochs): 
    np.random.shuffle(data)

    for batch_idx in range(n_batch):
        batch = get_data_batch(data, batch_idx)

        model.forward(batch)
        model.backward(lr)
```


