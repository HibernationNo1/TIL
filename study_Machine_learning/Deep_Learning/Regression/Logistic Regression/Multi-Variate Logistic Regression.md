# Multi-Variate Logistic Regression

- Affine Function
  $$
  z = \theta_{m}x_{m}+\theta_{m-1}x_{m-1}+...+\theta_{1}x_{1} + \theta_0
  $$

- Sigmoid Function
  $$
  \widehat{y} = \sigma(z) \\
  = \frac{1}{1 + e^{(\theta_{m}x_{m}+\theta_{m-1}x_{m-1}+...+\theta_{1}x_{1} + \theta_0))}}
  $$

- Binary Cross Entropy
  $$
  L = - [y log(\widehat{y}) + (1-y)log(1-\widehat{y})]
  $$



---

- feature scaling

  - Linear Regression에서 feature scaling을 하는 이유: x값이 너무 크면 학습 과정에서 발산을 할 위험이 있다.

  - Logistic Regression에서 feature scaling을 하는 이유: x값이 너무 크면 학습에 별 도움이 안되는 data이기 때문이다.

- noise

  data에 noise가 많아진다는 것은 단순히 실제 dataset에 noise가 많아진다는 것 뿐만 아니라, neuron 입장에서는 앞의 layer의 neuron이 noise를 만들어 내는것으로 보인다는 것이다. 그렇기 때문에 noise를 만들어 내는 neuron에 대한 weight는 낮춰가는 방향으로 theta가 updata된다.



### Sigmoid Function

- Decision Boundary
  $$
  D.B. => \ \ \ \ \ z = \theta_{m}x_{m}+\theta_{m-1}x_{m-1}+...+\theta_{1}x_{1} + \theta_0 = 0
  $$
  각각의 theta가 target theta라면, 아래의 식이 만족함을 알 수 있다.
  $$
  \left\{\begin{matrix}
  y = 1, \ \ \ if \ \ \theta_{m}x_{m}+\theta_{m-1}x_{m-1}+...+\theta_{1}x_{1} + \theta_0  > 0
  \\ 
  \\ 
  y = 0, \ \ \ if \ \ \theta_{m}x_{m}+\theta_{m-1}x_{m-1}+...+\theta_{1}x_{1} + \theta_0  < 0
  \end{matrix}\right.
  $$
  또한 각각의 x에 대한 식이 D.B.가 될 수 있다는 것을 통해 D.B.가 Linear한 모양이 나온다는 것을 할 수 있다.
  $$
  x_m = -\frac{\theta_{m-1}}{\theta_{m}}x_{m-1} -\frac{\theta_{m-2}}{\theta_{m}}x_{m-2}-...-\frac{\theta_{1}}{\theta_{m}}x_{1} - \frac{\theta_0}{\theta_{m}}
  $$

  > 예)
  >
  > - target theta가 3개 있고, 각각이 (1, 1, 0)이라 할 때
  >   $$
  >   (\theta_{2}, \theta_{1}, \theta_{0}) = (1, 1, 0)
  >   \\x_2 = -x
  >   $$
  >
  > -  target theta가 3개 있고, 각각이 (2, 1, 0)이라 할 때
  >   $$
  >   (\theta_{2}, \theta_{1}, \theta_{0}) = (1, 1, 0)
  >   \\x_2 = -\frac{1}{2}x
  >   $$
  >
  > -  target theta가 3개 있고, 각각이 (1, 1, 1)이라 할 때
  >   $$
  >   (\theta_{2}, \theta_{1}, \theta_{0}) = (1, 1, 0)
  >   \\x_2 = -x - 1
  >   $$
  >
  > 이를 통해 theta_0는 D.B.의 평행이동에 관여를 한다는 것을 알 수 있다.

  즉, D.B. 는 target theta에 의해서 결정되며 그 모양은 data의 column이 고차원적이라 해도 그 차원에 맞는 Linear한 모양이 만들어진다는 것을 알 수 있다. 



 - Logistic Regression에서 Activation Function으로 Sigmoid만 사용하는 이유

  Sigmoid Function을 사용해야 Binary Cross Entropy를 사용할 수 있기 때문에



### Propagation

![](https://github.com/HibernationNo1/TIL/blob/master/image/37.jpg?raw=true)

>Affine Function
>$$
>z = \theta_{m}x_{m}+\theta_{m-1}x_{m-1}+...+\theta_{1}x_{1} + \theta_0
>\\ = \vec{\theta^T}\vec{x}
>$$
>
>$$
>(\frac{\part z}{\part \theta_{m}}, \frac{\part z}{\part \theta_{m-1}}, ..., \frac{\part z}{\part \theta_{1}}, \frac{\part z}{\part \theta_{0}}) = (x_{m}, x_{m-1},..., x_{1}, 1)
>$$

$$
weight : \ \ \ \ \ \ \frac{\part J}{\part \theta_m} =\frac{1}{n}* \frac{\widehat{y}-1}{\widehat{y}(1-\widehat{y})} * \widehat{y}(1-\widehat{y})*x_m \\
= -\frac{x_m}{n}* (y-\widehat{y}) \ \ \ \ \ ( m \geq 1)\\
bias: \ \ \ \ \ \ \frac{\part J}{\part \theta_0} = \frac{1}{n}*\frac{\widehat{y}-1}{\widehat{y}(1-\widehat{y})} * \widehat{y}(1-\widehat{y})*1 \\
= -\frac{1}{n}*(y - \widehat{y})
$$





**GDM**
$$
\theta_m := \theta_m - \alpha\frac{\part J}{\part \theta_m}  = \theta_m + \frac{\alpha}{n}x_m (y-\widehat{y}) \ \ \ \ \ ( m \geq 1)\\
\theta_0 := \theta_0 - \alpha\frac{\part J}{\part \theta_0}  = \theta_0 + \frac{\alpha}{n}(y-\widehat{y})
$$


## Code

> $$
> \widehat{y} = \theta_2 x_2 + \theta_1 x_1 + \theta_0
> $$



##### 1. main.py

```python
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

import basic_node as nodes
import dataset_generator as dataset
import visualization as visual
import Class_implementation as class_imp

feature_dim = 2
noise_factor = 0.3
direction = 1
n_sample = 100

x_dict = {1: {'mean': 0, 'std': 1}, 
            2: {'mean': 0, 'std': 2}}
t_th_list = [0, 1, 1]

epochs, lr = 300, 0.01
iter_idx, check_freq = 0, 1

data_gen = dataset.DatasetGenerator(feature_dim = feature_dim, 
                                        n_sample = n_sample,
                                        noise_factor = noise_factor,
                                        direction = direction)

data_gen.set_t_th(t_th_list)
data_gen.set_feature_dict(x_dict)
data = data_gen.make_dataset()

model = class_imp.MVLoR(feature_dim)
BCE_loss = class_imp.BinaryCrossEntropy()

loss_list = list()
th_accum = model.get_Th()

for epoch in range(epochs):
    np.random.shuffle(data)

    for data_idx in range(data.shape[0]):
        x, y = data[data_idx,: -1], data[data_idx, -1]

        pred = model.forward(x)
        l = BCE_loss.forward(y, pred)

        dpred = BCE_loss.backward()
        model.backward(dpred, lr)

        if iter_idx % check_freq == 0:
            th_accum = np.hstack((th_accum, model.get_Th()))
            loss_list.append(1)
        iter_idx+=1

visual.result_visualizer(th_accum, loss_list,feature_dim)
visual.plot_classifier(data, th_accum)

```



##### 2. basic_node.py

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



##### 3. dataset_generator.py

```python
import numpy as np

class DatasetGenerator:
    def __init__(self, feature_dim, n_sample = 300, noise_factor = 0., direction = 1):
        self._feature_dim = feature_dim
        self._n_sample = n_sample
        self._noise_factor = noise_factor 
        self._direction = direction

        self._init_feature_dict()
        self._init_t_th()
    
    def _init_feature_dict(self):
        self._feature_dict = dict()
        for feature_idx in range(1, self._feature_dim+1):
            x_dict ={'mean' : 0, 'std': 1}
            self._feature_dict[feature_idx] = x_dict

    def _init_t_th(self):
        self._t_th = [0] + [1 for i in range(self._feature_dim)]

    def set_feature_dict(self, feature_dict):
        if len(feature_dict) != self._feature_dim:
            class FeatureDictError (Exception):
                pass
            raise FeatureDictError('The length of "feature__dict" should be equal to "feature_dim"')
        else:
            self._feature_dict = feature_dict
    
    def set_t_th(self, t_th_list):
        if len(t_th_list) != len(self._t_th):
            class FeatureDictError (Exception):
                pass
            raise FeatureDictError('The length of "t_th_list" should be equal to "feature_dim + 1"')
        else:
            self._t_th = t_th_list

    
    def make_dataset(self):
        x_data = np.zeros(shape = (self._n_sample, 1))
        y = np.zeros(shape = (self._n_sample, 1))

        for feature_idx in range(1, self._feature_dim + 1):
            feature_dict = self._feature_dict[feature_idx]
            data = np.random.normal(loc = feature_dict['mean'], 
                                    scale = feature_dict['std'],
                                    size = (self._n_sample, 1))
            x_data = np.hstack((x_data, data))
            y += self._t_th[feature_idx]*data
        y +=self._t_th[0]
        y_noise = y + self._noise_factor*np.random.normal(0, 1, (self._n_sample, 1))
        
        if self._direction > 0:
            y_data = (y_noise > 0).astype(np.int)
        else:
            y_data = (y_noise < 0).astype(np.int)
        data = np.hstack((x_data, y_data))
        return data
```



##### 4. Class_implementation.py

```python
import numpy as np

import basic_node as nodes

class AffineFunction:
    def __init__(self, feature_dim):
        self._feature_dim = feature_dim

        self._z1_list = [None]*(self._feature_dim + 1)
        self._z2_list = self._z1_list.copy()

        self._dz1_list, self._dz2_list = self._z1_list.copy(), self._z1_list.copy()
        self._dth_list = self._z1_list.copy()

        self.node_imp()
        self.random_theta_initialization()

    def node_imp(self):
        self._node1 = [None] + [nodes.mul_node() for _ in range(self._feature_dim)]
        self._node2 = [None] + [nodes.plus_node() for _ in range(self._feature_dim)]

    def random_theta_initialization(self):
        r_feature_dim = 1/np.power(self._feature_dim, 0.5)
        self._Th = np.random.uniform(low = -1*r_feature_dim, 
                                    high = r_feature_dim, 
                                    size =(self._feature_dim + 1, 1))
        # 초기 ramdom theta의 범위 = 1/np.power(self._feature_mid, 0.5)

    def forward(self, X):
        for node_idx in range(1, self._feature_dim + 1):
            self._z1_list[node_idx] = self._node1[node_idx].forward(self._Th[node_idx], 
                                                                    X[node_idx])
        self._z2_list[1] = self._node2[1].forward(self._Th[0], self._z1_list[1])
        for node_idx in range(2, self._feature_dim + 1): 
            self._z2_list[node_idx] = self._node2[node_idx].forward(self._z2_list[node_idx-1], 
                                                                    self._z1_list[node_idx])
        return self._z2_list[-1]     

    def backward(self, dz2_last, lr):
        self._dz2_list[-1] = dz2_last

        for node_idx in reversed(range(1, self._feature_dim+1)):
            dz2, dz1 = self._node2[node_idx].backward(self._dz2_list[node_idx])
            self._dz2_list[node_idx-1] = dz2
            self._dz1_list[node_idx] = dz1

        self._dth_list[0] = self._dz2_list[0]

        for node_idx in reversed(range(1, self._feature_dim + 1)):
            dth, _ = self._node1[node_idx].backward(self._dz1_list[node_idx])
            self._dth_list[node_idx] = dth

        self._Th = self._Th - lr*np.array(self._dth_list).reshape(-1, 1)
        return self._Th

    def get_Th(self):
        return self._Th     

class SigmoidFunction:
    def __init__(self):
        self._pred = None

    def forward(self, z):
        self._pred = 1/(1 + np.exp(-1*z))       
        return self._pred
        
    def backward(self, dpred):
        dz = dpred*(self._pred*(1-self._pred))
        return dz      


class MVLoR:
    def __init__(self, feature_dim):
        self._feature_dim = feature_dim

        self._affine= AffineFunction(self._feature_dim)
        self._sigmoid = SigmoidFunction()
    
    def forward(self, x):
        z = self._affine.forward(x)
        pred = self._sigmoid.forward(z)
        return pred

    def backward(self, dpred, lr):
        dz = self._sigmoid.backward(dpred)
        self._affine.backward(dz, lr)
    
    def get_Th(self):
        return self._affine.get_Th()



class BinaryCrossEntropy:
    def __init__(self):
        self._y, self._pred = None, None

    def forward(self, y, pred):
        self._y, self._pred = y, pred
        
        loss = -1*(self._y*np.log(self._pred) + (1-self._y)*np.log(1-self._pred))
        return loss

    def backward(self):
        dpred = (self._pred-self._y) / (self._pred *(1-self._pred))
        return dpred
```



##### 5. visualization.py

```python
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt

import Class_implementation as class_imp

def plot_classifier(data, th_accum):
    p_idx = np.where(data[:,-1] > 0)
    np_idx = np.where(data[:,-1] <= 0) 

    fig = plt.figure(figsize = (6, 6))
    ax = fig.add_subplot(projection = '3d')

    ax.plot(data[p_idx, 1].flat, data[p_idx, 2].flat, data[p_idx, -1].flat, 'bo')
    ax.plot(data[np_idx, 1].flat, data[np_idx, 2].flat, data[np_idx, -1].flat, 'rX')

    ax.set_xlabel(r'$x_{1}$' + ' data', labelpad = 20)
    ax.set_ylabel(r'$x_{2}$' + ' data', labelpad = 20)
    ax.set_zlabel('y', labelpad = 20)

    f_th0, f_th1, f_th2 = th_accum[:, -1]
    x1_range = np.linspace(np.min(data[:, 1]), np.max(data[:, 1]), 100)
    x2_range = np.linspace(np.min(data[:, 2]), np.max(data[:, 2]), 100)
    X1, X2 = np.meshgrid(x1_range, x2_range)

    affine = X2*f_th2 + X1*f_th1 + f_th0
    sigmoid = class_imp.SigmoidFunction()
    pred = sigmoid.forward(affine)

    ax.plot_wireframe(X1, X2, pred)
    plt.show()

def result_visualizer(th_accum, loss_list,feature_dim):
    fig, ax = plt.subplots(figsize = (10, 5))
    fig.subplots_adjust(hspace = 0.3)
    ax.set_title(r'$\vec{\theta}$' + ' Updata')

    for feature_idx in range(feature_dim+1):
        ax.plot(th_accum[feature_idx, :], 
                label = r'$\theta_{%d}$' %feature_idx)
    ax.legend()
    iter_ticks = np.linspace(0, th_accum.shape[1], 10).astype(np.int)
    ax.set_xticks(iter_ticks)
    plt.show() 
```

