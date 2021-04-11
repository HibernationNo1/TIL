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
x_2, x_1의 값이 크면 theta_2, theta_1의 학습 속도가 빨라지지만, theta_0의 학습 속도는 느려지게 된다. 이를 통해 x_2와 x_1의 크기는 theta_0에는 영향을 주는 것을 알 수 있다.



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
  



## No batch

### 코드 구현(non class)

> 3가지의 feature



#### main.py

> Loss만 사용해서 learning 진행 (cost 사용 안함)

```python
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

import basic_node as nodes

plt.style.use('seaborn')
np.random.seed(0)

n_sample = 1000     # data의 개수  
feature_dim = 3     # 변수의 개수: 3개
coefficient_list = [3, 3, 3, 3]     # 각 변수의 계수(target teta)  y = 3x_3 + 3x_2 + 3x_1 + 3
distribution_params = {             # 각 변수의 mean, std
    1: {'mean': 0, 'std': 1},
    2: {'mean': 0, 'std': 1},
    3: {'mean': 0, 'std': 1}}

y_data = np.zeros(shape = (n_sample, 1))
x_data = np.zeros(shape = (n_sample, 1))

for feature_idx in range(1, feature_dim + 1):
    feature_data = np.random.normal(loc = distribution_params[feature_idx]['mean'],
                                    scale = distribution_params[feature_idx]['std'],
                                    size = (n_sample, 1))
    x_data = np.hstack((x_data, feature_data))            # 위에서 만든 normal dataset을 수평으로 stack 
    y_data += coefficient_list[feature_idx]*feature_data  # weight * x 입력값


y_data += coefficient_list[0]  # y_data 안의 각각의 모든 element에 bais를 더함  (정답 데이터 셋 완성)
# x_data.shape == (100, 4),    y_data.shape == (100, 1)
# x_data의 (100, 1)은 zeros임(idx를 맞추기 위해서)

# 모델(\widehat{y})을 구성할 노드 호출
node1 = [None] + [nodes.mul_node() for _ in range(feature_dim)]     # [None]은 idx맞추기 용
node2 = [None] + [nodes.plus_node() for _ in range(feature_dim)]

# Loss를 구성할 노드 호출
node3 = nodes.minus_node()
node4 = nodes.square_node()
# Cost를 구성할 노드 호출
# 없음

th_list = [0.5, 0.5, 0.5, 0.5]  # initial theta
epochs, lr = 5, 0.001

# 나중에 updata가 어떻게 이루어졌는지 확인하기 위함
th_accum = np.array(th_list).reshape(-1, 1)
loss_list = list()

for epoch in range(epochs):
    for data_idx, (x, y) in enumerate(zip(x_data, y_data)):
    # x_data, y_data의 idx_0은 None이기 때문에, 자연스럽게 idx_1부터 값이 할당됨
        
        # 모델(\widehat{y}) 구현
        z1_list = [None]*(feature_dim + 1)
        z2_list, dz1_list, dz2_list, dth_list = z1_list.copy(), z1_list.copy(), z1_list.copy(), z1_list.copy()
        
    # forward propagation   
        for node_idx in range(1, feature_dim + 1):
            z1_list[node_idx] = node1[node_idx].forward(th_list[node_idx], x[node_idx])
        
        for node_idx in range(1, feature_dim + 1):
            if node_idx == 1:
                z2_list[node_idx] = node2[node_idx].forward(th_list[0], z1_list[node_idx])
            else :
                z2_list[node_idx] = node2[node_idx].forward(z2_list[node_idx-1], z1_list[node_idx])

        # Loss function 구현
        z3 = node3.forward(y, z2_list[-1])
        Loss = node4.forward(z3)

        # Cost function 구현
        # 없음

    # backward propagation
        dz3 = node4.backward(1)
        _, dz2_list[-1] = node3.backward(dz3)  # _ == y

        for node_idx in reversed(range(1, feature_dim + 1)): 
            # 1, 2, 3 >> 3, 2, 1
            if node_idx == 1:
                dth_list[0], dz1_list[node_idx] = node2[node_idx].backward(dz2_list[node_idx])
            else: 
                dz2_list[node_idx -1], dz1_list[node_idx] = node2[node_idx].backward(dz2_list[node_idx])

        for node_idx in reversed(range(1, feature_dim + 1)): 
            dth_list[node_idx], _ = node1[node_idx].backward(dz1_list[node_idx])

    # params updata
        for th_idx in range(len(th_list)):
            th_list[th_idx] = th_list[th_idx] - (lr*dth_list[th_idx])
        
        # paramas updata 흔적 확인용
        th_next = np.array(th_list).reshape(-1, 1)
        th_accum = np.hstack((th_accum, th_next))
        loss_list.append(1)

fig, ax = plt.subplots(2, 1, figsize = (20, 10))

for i in range(feature_dim + 1):
    ax[0].plot(th_accum[i], label = r'$\theta_{%d}$' %i, linewidth = 5)

ax[1].plot(loss_list)

ax[0].legend(loc = 'lower right', fontsize = 30)
ax[0].tick_params(axis = 'both', labelsize = 30)
ax[1].tick_params(axis = 'both', labelsize = 30)

ax[0].set_title(r'$\vec{\theta}$', fontsize = 40)
ax[1].set_title(r'Loss', fontsize = 40)
plt.show()
```



#### basic_node.py

```python
import numpy as np

class plus_node():
    def forward(self, x, y):
        self._x, self._y = x, y
        self._z = self._x + self._y
        return self._z
    
    def backward(self, dz):
        return (dz, dz)

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
        return (-1*dz, -1*dz)

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





### 코드 구현(use class)

#### main.py

```python
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

import Function_implementation as function
import basic_node as nodes
import dataset_generator as dataset

feature_dim = 3
n_sample = 1000 
coefficient_list = [5, 5, 5, 5]

data_gen = dataset.Dataset_Generator(feature_dim, n_sample, coefficient_list )
x_data, y_data = data_gen.make_dataset()

Th = data_gen.make_theta()
epochs, lr = 20, 0.001

th_accum = Th.reshape(-1, 1)
loss_list = list()

affine = function.Affine_Function(feature_dim, Th)
loss = function.Square_Error_Loss()

for epoch in range(epochs):
    for (x, y) in (zip(x_data, y_data)):

        pred = affine.forward(x)
        los = loss.forward(y, pred)

        dpred = loss.backward()
        affine.backward(dpred, lr)
    
        th_accum = np.hstack((th_accum, affine._Th))
        loss_list.append(los)

function.result_visualization(th_accum, loss_list, feature_dim)
```



#### basic_node.py

```python
import numpy as np

class plus_node():
    def forward(self, x, y):
        self._x, self._y = x, y
        self._z = self._x + self._y
        return self._z
    
    def backward(self, dz):
        return (dz, dz)

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
        return (-1*dz, -1*dz)

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



#### dataset_generator.py

```python
import numpy as np

class Dataset_Generator:
    def __init__(self, feature_dim, n_sample, coefficient_list):
        self._feature_dim = feature_dim
        self._n_sample = n_sample
        self._coefficient_list = coefficient_list

        self.dataset_imp()

    def dataset_imp(self):
        self._x_data = np.zeros(shape = (self._n_sample, 1))
        self._y_data = np.zeros(shape = (self._n_sample, 1))

    def make_dataset(self):
        distribution_params = dict()
        for idx in range(1, self._feature_dim + 1):
            
            distribution_params[idx] = {'mean': 0, 'std': 1}

        for feature_idx in range(1, self._feature_dim + 1):
            feature_data = np.random.normal(loc = distribution_params[feature_idx]['mean'],
                                            scale = distribution_params[feature_idx]['std'],
                                            size = (self._n_sample, 1))
            self._x_data = np.hstack((self._x_data, feature_data))            # 위에서 만든 normal dataset을 수평으로 stack 
            self._y_data += self._coefficient_list[feature_idx]*feature_data  # weight * x 입력값

        self._y_data += self._coefficient_list[0]
        return self._x_data, self._y_data
    
    def make_theta(self):
        Th = np.random.normal(size = (self._feature_dim + 1)).reshape(-1, 1)
        return Th

```





#### Function_implementation.py

```python
import numpy as np
import basic_node as nodes
import matplotlib.pyplot as plt

class Affine_Function:
    def __init__(self, feature_dim, Th):
        self._feature_dim = feature_dim
        self._Th = Th

        self._z1_list = [None]*(self._feature_dim + 1)
        self._z2_list = self._z1_list.copy()
        self._dz1_list, self._dz2_list = self._z1_list.copy(), self._z1_list.copy()
        self._dth_list = self._z1_list.copy()

        self.affine_imp()

    def affine_imp(self):
        self._node1 = [None] + [nodes.mul_node() for _ in range(self._feature_dim)]
        self._node2 = [None] + [nodes.plus_node() for _ in range(self._feature_dim)]

    def forward(self, x):
        for node_idx in range(1, self._feature_dim + 1):
            self._z1_list[node_idx] = self._node1[node_idx].forward(self._Th[node_idx], x[node_idx])
        
        for node_idx in range(1, self._feature_dim + 1):
            if node_idx == 1:
                self._z2_list[node_idx] = self._node2[node_idx].forward(self._Th[0], self._z1_list[node_idx])
            else :
                self._z2_list[node_idx] = self._node2[node_idx].forward(self._z2_list[node_idx-1], self._z1_list[node_idx])

        return self._z2_list[-1]

    def backward(self, dz2_last, lr):
        for node_idx in reversed(range(1, self._feature_dim + 1)): 
            if node_idx == 1:
                self._dth_list[0], self._dz1_list[node_idx] = self._node2[node_idx].backward(self._dz2_list[node_idx])
            elif node_idx == self._feature_dim:
                self._dz2_list[node_idx -1], self._dz1_list[node_idx] = self._node2[node_idx].backward(dz2_last)
            else: 
                self._dz2_list[node_idx -1], self._dz1_list[node_idx] = self._node2[node_idx].backward(self._dz2_list[node_idx])

        for node_idx in reversed(range(1, self._feature_dim + 1)): 
            self._dth_list[node_idx], _ = self._node1[node_idx].backward(self._dz1_list[node_idx])

        
        self._Th = self._Th - (lr*np.array(self._dth_list).reshape(-1, 1))
        return self._Th

class Square_Error_Loss:
    def __init__(self):
        self.loss_imp()

    def loss_imp(self):
        self._node3 = nodes.minus_node()
        self._node4 = nodes.square_node()

    def forward(self, y, z2_last):
        z3 = self._node3.forward(y, z2_last)
        loss = self._node4.forward(z3)
        return loss

    def backward(self):
        dz3 = self._node4.backward(1)
        _, dz2_last = self._node3.backward(dz3)
        return dz2_last

def result_visualization(th_accum, loss_list, feature_dim):
    plt.style.use('seaborn')

    fig, ax = plt.subplots(2, 1, figsize = (20, 10))

    for i in range(feature_dim + 1):
        ax[0].plot(th_accum[i], label = r'$\theta_{%d}$' %i, linewidth = 5)

    ax[1].plot(loss_list)

    ax[0].legend(loc = 'lower right', fontsize = 30)
    ax[0].tick_params(axis = 'both', labelsize = 30)
    ax[1].tick_params(axis = 'both', labelsize = 30)

    ax[0].set_title(r'$\vec{\theta}$', fontsize = 40)
    ax[1].set_title(r'Loss', fontsize = 40)
    plt.show()
```



## Mini-batch

### 코드 구현(use class)

#### main.py

```python
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

import Function_implementation as function
import basic_node as nodes
import dataset_generator as dataset

# data set 만들기
feature_dim = 3
n_sample = 1000 
coefficient_list = [5, 5, 5, 5]     # target theta
data_gen = dataset.Dataset_Generator(feature_dim, n_sample, coefficient_list )
x_data, y_data = data_gen.make_dataset()

# batch 작업
batch_size = 8
data = np.hstack((x_data, y_data))   # data shuffle을 위해
n_batch = np.ceil(data.shape[0]/batch_size).astype(int)

Th = data_gen.make_theta()
epochs, lr = 20, 0.001

th_accum = Th.reshape(-1, 1)
cost_list = list()

affine = function.Affine_Function(feature_dim, Th)
loss = function.Square_Error_Loss()
cost = function.Cost()

for epoch in range(epochs):
    np.random.shuffle(data)

    for batch_idx in range(n_batch):
        batch = function.get_data_batch(data, batch_idx, n_batch, batch_size)
        x, y = batch[:, : -1], batch[:, -1]
        

        pred = affine.forward(x)
        los = loss.forward(y, pred)
        J = cost.forward(los)

        dlos = cost.backward()
        dpred = loss.backward(dlos)
        affine.backward(dpred, lr)
    
        th_accum = np.hstack((th_accum, affine._Th))
        cost_list.append(los)

function.result_visualization(th_accum, cost_list, feature_dim)
```





#### basic_node.py

```python
import numpy as np

class plus_node():
    def forward(self, x, y):
        self._x, self._y = x, y
        self._z = self._x + self._y
        return self._z
    
    def backward(self, dz):
        return (dz, dz)

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
        return (-1*dz, -1*dz)

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



#### dataset_generator.py

```python
import numpy as np

class Dataset_Generator:
    def __init__(self, feature_dim, n_sample, coefficient_list):
        self._feature_dim = feature_dim
        self._n_sample = n_sample
        self._coefficient_list = coefficient_list

        self.dataset_imp()

    def dataset_imp(self):
        self._x_data = np.zeros(shape = (self._n_sample, 1))
        self._y_data = np.zeros(shape = (self._n_sample, 1))

    def make_dataset(self):
        distribution_params = dict()
        for idx in range(1, self._feature_dim + 1):
            
            distribution_params[idx] = {'mean': 0, 'std': 1}

        for feature_idx in range(1, self._feature_dim + 1):
            feature_data = np.random.normal(loc = distribution_params[feature_idx]['mean'],
                                            scale = distribution_params[feature_idx]['std'],
                                            size = (self._n_sample, 1))
            self._x_data = np.hstack((self._x_data, feature_data))            # 위에서 만든 normal dataset을 수평으로 stack 
            self._y_data += self._coefficient_list[feature_idx]*feature_data  # weight * x 입력값

        self._y_data += self._coefficient_list[0]
        return self._x_data, self._y_data
    
    def make_theta(self):
        Th = np.random.normal(0, 1, size = (self._feature_dim + 1)).reshape(-1, 1)
        return Th

```





#### Function_implementation.py

```python
import numpy as np
import basic_node as nodes
import matplotlib.pyplot as plt

class Affine_Function:
    def __init__(self, feature_dim, Th):
        self._feature_dim = feature_dim
        self._Th = Th

        self._z1_list = [None]*(self._feature_dim + 1)
        self._z2_list = self._z1_list.copy()
        self._dz1_list, self._dz2_list = self._z1_list.copy(), self._z1_list.copy()
        self._dth_list = self._z1_list.copy()
        
        self.affine_imp()

    def affine_imp(self):
        self._node1 = [None] + [nodes.mul_node() for _ in range(self._feature_dim)]
        self._node2 = [None] + [nodes.plus_node() for _ in range(self._feature_dim)]

    def forward(self, x):
        for node_idx in range(1, self._feature_dim + 1):
            self._z1_list[node_idx] = self._node1[node_idx].forward(self._Th[node_idx], x[:, node_idx])
        
        for node_idx in range(1, self._feature_dim + 1):
            if node_idx == 1:
                self._z2_list[node_idx] = self._node2[node_idx].forward(self._Th[0], self._z1_list[node_idx])
            else :
                self._z2_list[node_idx] = self._node2[node_idx].forward(self._z2_list[node_idx-1], self._z1_list[node_idx])

        return self._z2_list[-1]

    def backward(self, dz2_last, lr):
        for node_idx in reversed(range(1, self._feature_dim + 1)): 
            if node_idx == 1:
                self._dth_list[0], self._dz1_list[node_idx] = self._node2[node_idx].backward(self._dz2_list[node_idx])
            elif node_idx == self._feature_dim:
                self._dz2_list[node_idx -1], self._dz1_list[node_idx] = self._node2[node_idx].backward(dz2_last)
            else: 
                self._dz2_list[node_idx -1], self._dz1_list[node_idx] = self._node2[node_idx].backward(self._dz2_list[node_idx])
        

        for node_idx in reversed(range(1, self._feature_dim + 1)): 
            self._dth_list[node_idx], _ = self._node1[node_idx].backward(self._dz1_list[node_idx])
        dth = np.sum(self._dth_list)
        
        self._Th = self._Th - (lr*np.array(dth).reshape(-1, 1))
        return self._Th

class Square_Error_Loss:
    def __init__(self):
        self.loss_imp()

    def loss_imp(self):
        self._node3 = nodes.minus_node()
        self._node4 = nodes.square_node()

    def forward(self, y, z2_last):
        z3 = self._node3.forward(y, z2_last)
        loss = self._node4.forward(z3)
        return loss

    def backward(self, dlos):
        dz3 = self._node4.backward(dlos)
        _, dz2_last = self._node3.backward(dz3)
        return dz2_last
     
class Cost:
    def __init__(self):
        self.cost_imp()
    
    def cost_imp(self):
        self._node5 = nodes.mean_node()

    def forward(self, los):
        J = self._node5.forward(los)
        return J

    def backward(self):
        dlos = self._node5.backward(1)
        return dlos


def get_data_batch(data, batch_idx, n_batch, batch_size):
    if batch_idx is n_batch -1:
        batch = data[batch_dix*batch_size:]
    else:
        batch = data[batch_idx*batch_size : (batch_idx + 1)*batch_size]
    return batch

def result_visualization(th_accum, cost_list, feature_dim):
    plt.style.use('seaborn')

    fig, ax = plt.subplots(2, 1, figsize = (20, 10))

    for i in range(feature_dim + 1):
        ax[0].plot(th_accum[i], label = r'$\theta_{%d}$' %i, linewidth = 5)

    ax[1].plot(cost_list)

    ax[0].legend(loc = 'lower right', fontsize = 30)
    ax[0].tick_params(axis = 'both', labelsize = 30)
    ax[1].tick_params(axis = 'both', labelsize = 30)

    ax[0].set_title(r'$\vec{\theta}$', fontsize = 40)
    ax[1].set_title(r'Loss', fontsize = 40)
    plt.show()


```

