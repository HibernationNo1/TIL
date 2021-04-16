# Polynomial Regression

다항식 회귀: y값에 대해서 x값이 2개 이상인 회귀모델을 사용해서 곡선에 대한 학습을 하는 것 (ex. y =  sin(x) 또는 n >= 2 인 n차 함수를 다항식 모델을 사용해서 학습)

linear regression과의 차이점은, 곡선으로 표현된 함수(data)를 학습이 가능하다는 것이다.

모델의 차수가 높아질수록 곡선에 대한 학습 정확도가 높아진다.

- 예

  ![](https://github.com/HibernationNo1/TIL/blob/master/image/33.jpg?raw=true)

  왼쪽부터 y  = sin(x)함수에 대한 모델 widehat{y} 의 차수가 1, 2, 3, 4인 회귀의 학습 모습이다.

  모델의 차수가 높아질수록 정확도가 높아지는 것을 알 수 있다. 

  > 차수가 높아진다는 것은 더 많은 곡선으로 모델이 표현될 수 있다는 것이다.
  >
  > 이런 과정에서 차수가 너무 높아지면 over fitting 문제가 발생할 수 있다.



---



- Model

$$
\widehat{y} = \theta_mx^m + \theta_{m-1}x^{m-1} + ...+\theta_2 x^2 + \theta_1 x + \theta_0\\
\overrightarrow{\theta} = \begin{pmatrix}
\theta_m
\\ 
\theta_{m-1}
\\ 
\vdots
\\ 
\theta_1
\\ 
\theta_0
\end{pmatrix} \ \ \ \ \ \ \ \ \ 
\overrightarrow{x} = \begin{pmatrix}
x_m
\\ 
x_{m-1}
\\ 
\vdots
\\ 
x_1
\\ 
1
\end{pmatrix}
$$

​	여기서 알아야 하는 것은, x값 m개와 1에 대해서 각각의 theta가 곱해지던 MVLR과는 달리

​	polynomia는 x값 1개에 대해서 0부터 m까지의 차수가 적용되는 것이고 이에 m+1개의 

​	theta가 곱해지는 것이다.

- Loss
  $$
  Loss = (y - \widehat{y})^2\\
   = (y - (\theta_mx^m + \theta_{m-1}x^{m-1} + ...+\theta_2 x^2 + \theta_1 x + \theta_0))^2
  $$
  
- Partial Derivatives 

  - $$
    \frac{\part L(\overrightarrow{(\theta)})}{\part \theta_0} = -2(y - \widehat{y})\\
    =-2(y - (\theta_mx^m + \theta_{m-1}x^{m-1} + ...+\theta_2 x^2 + \theta_1 x + \theta_0))
    $$

  - $$
    \frac{\part L(\overrightarrow{(\theta)})}{\part \theta_n}|_{n>1} = -2x^n(y - \widehat{y})\\
    = -2x^n(y - (\theta_mx^m + \theta_{m-1}x^{m-1} + ...+\theta_2 x^2 + \theta_1 x + \theta_0)
    $$

- Parameter Updata
  $$
  \theta_0 := \theta_0 + 2\alpha(y - \widehat{y})\\
  \theta_1 := \theta_1 + 2\alpha x(y - \widehat{y})\\
  \theta_2 := \theta_2 + 2\alpha x^2(y - \widehat{y})\\
  \vdots\\
  \theta_m := \theta_m + 2\alpha x^m(y - \widehat{y})\\
  $$
  이를 통해  theta의 변화량은 x의 절대값에 따라서 달라질 수 있음을 알 수 있다.

  - |x| > 1 일 때

    m이 커질수록 theta의 변화량도 크다 -> learning rate는 발산할 확률이 가장 큰 theta_m을 기준으로 잡아줘야 한다.

    (대신 theta_0의 learning 속도가 너무 낮아지게 될 것이다.)

  - |x| < 1 일 때

    m이 0에 가까울수록 theta의 변화량도 크다 -> learning rate는 발산할 확률이 가장 큰 theta_0을 기준으로 잡아줘야 한다.

    (대신 theta_m의 learning 속도가 너무 낮아지게 될 것이다. 이것이 Polynimial Regression의 한계)

  즉, data set의 크기를 1보다 작게 잡으면 몇차식의 모델이든 learning rate의 기준을 bias로 맞추면 된다.

  위와 같은 이유로 Polynimial Regression는 태생적으로 학습 속도가 느릴 수 밖에 없다.



### Theory

forward propagation과 backward propagation의 진행 과정을 확인해보자

![](https://github.com/HibernationNo1/TIL/blob/master/image/27.jpg?raw=true)

![](https://github.com/HibernationNo1/TIL/blob/master/image/28.jpg?raw=true)

![](https://github.com/HibernationNo1/TIL/blob/master/image/29.jpg?raw=true)

즉, 

![](https://github.com/HibernationNo1/TIL/blob/master/image/30.jpg?raw=true)

![](https://github.com/HibernationNo1/TIL/blob/master/image/31.jpg?raw=true)
$$
\frac{\part J}{\part \theta_p} = \sum_{i=1}^{n}[-2 (x^p)^{(i)} (y^{(i)} - \widehat{y}^{(i)})]\\
\theta_p := \theta_p + 2\alpha\sum_{i=1}^{n}[(x^p)^{(i)} (y^{(i)} - \widehat{y}^{(i)})]
$$


- make data set 

  ![](https://github.com/HibernationNo1/TIL/blob/master/image/32.jpg?raw=true)

  x^1에 대해서 각각 x를 한번 곱하고 np.hstack을 통해 수평으로 쌓은 후 이 과정을 반복,  마지막에 y의 data set을 쌓으면 전제 data set을 깔끔하게 구성할 수 있다.



### 코드 구현

거의 모든 code가 MVLR과 비슷하다. (basic_node.py과 Function_implementation.py는 아예 MVLR과 동일)

##### main.py

```python
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.cm as cm

import Function_implementation as function
import basic_node as nodes

# data set 만들기
n_sample = 400
x_data1 = np.linspace(0.05, 1-0.05, n_sample).reshape(-1, 1)
y_data = np.sin(2*np.pi*x_data1) + 0.2*np.random.normal(0, 1, size = (n_sample, 1))

h_order = 3  # Y는 X에 대한 3차식
x_data = np.zeros(shape = (n_sample, 1))
for order in range(1, h_order +1):
    order_data = np.power(x_data1, order)
    x_data = np.hstack((x_data, order_data))

data = np.hstack((x_data, y_data))

# batch 작업
batch_size = 32
n_batch = np.ceil(data.shape[0]/batch_size).astype(int)
feature_dim = x_data.shape[1]-1

Th = np.ones(shape = (feature_dim+1, ), dtype = np.float).reshape(-1, 1)
epochs, lr = 100, 0.01
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
        cost_list.append(J)

function.result_visualization(th_accum, cost_list, feature_dim)
```



##### basic_node.py

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





##### Function_implementation.py

```python
import numpy as np
import basic_node as nodes
import matplotlib.pyplot as plt

class Affine_Function:
    def __init__(self, feature_dim, Th):
        self._feature_dim = feature_dim
        self._Th = Th
        self._dth_sum_list = self._Th.copy()

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
        
            self._dth_sum_list[0] = np.sum(self._dth_list[0])
        for node_idx in reversed(range(1, self._feature_dim + 1)): 
            self._dth_list[node_idx], _ = self._node1[node_idx].backward(self._dz1_list[node_idx])
            self._dth_sum_list[node_idx] = np.sum(self._dth_list[node_idx])

        self._Th = self._Th - (lr*np.array(self._dth_sum_list).reshape(-1, 1))
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

