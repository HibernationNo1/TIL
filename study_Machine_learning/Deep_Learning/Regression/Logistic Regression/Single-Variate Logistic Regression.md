# Single-Variate Logistic Regression

> Single-Variate Logistic Regression이기 때문에 이 문서의 모든 내용은 Single-Variate 기준으로 작성했음

Affine Function	->		Sigmoid Function	->	Binary Cross Entropy Loss
$$
Affine\ Function \ \ \ \ \ \ \ \ z = \theta_1 x + \theta_0 \\
Sigmoid\ Function\ \ \ \ \ \ \ \ \widehat{y} = \frac{1}{1+e^{-z}}\\
Binary\ Cross\ Entropy\ Loss\ \ \ \ \ \ \ \ L =-[y log(\widehat{y}) + (1 - y)log(1 - \widehat{y})]
$$

$$
data\ set \ \ \ \ \ \  (x^{(i)}, y^{(i)}) = (x, y) \ \ 단, \ y는\ 0\ or\ 1
$$





### Sigmoid Function

- Sigmoid Function의 shape

$$
\sigma({y}) = \frac{1}{1+e^{-(\theta_1 x + \theta_0)}} = \frac{1}{1+e^{-\theta_1(x- (- \frac{\theta_0}{\theta_1})})}
$$

1. **weight의 변화량에 따른 Sigmoid Function 모양의 변화**

   weight의 절대값이 커질수록 Sigmoid Function의 S모양이 더욱 Sharply 된다.

   즉, Model이 이상적인 classifier가 되기 위해서는 weight가 무한대로 발산해야 한다. (updata가 계에에에속해서 일어난다.)

2. **Bias의 변화량에 따른 Sigmoid Function 모양의 변화**

   Bias가 +(또는 -)방향으로 커지면 Sigmoid Function의 Decision Boundary가 +(또는 -)방향으로 이동한다.

   ![](https://github.com/HibernationNo1/TIL/blob/master/image/45.jpg?raw=true)

   하지만 Decision Boundary값을 결정하는 것은 -(bias/weight)이기 때문에 weight와 bias가 변한다 하더라도 둘의 ratio(비율)이 동일하게 유지된다면 Decision Boundary는 제 자리에 유지된다. 그렇기 때문에 weight가 무한대로 발산하며 끊임없이 updata된다면 bias도 Decision Boundary를 유지시키기 위해 끊임없이 updata가 일어난다. 

   그리고 Decision Boundary가 음수일때는  weight의 updata 방향과 bias의 updata 방향은 서로 같은 방향으로 (둘 다 +Infinity 또는 -Infinity),

   Decision Boundary가 양수일때는  weight의 updata 방향과 bias의 updata 방향은 서로 다른 방향으로 (weight가 +Infinity면 bias는 -Infinity) 업데이트 되게 된다.

   ![](https://github.com/HibernationNo1/TIL/blob/master/image/46.jpg?raw=true)



- Linear Regrassion과의 차이점

  Linear Regrassion의 weight와 bias는 각각 label에 맞게 학습하기 위해서 label의 weight와 bias를 찾아간다.

  하지만 Losistic Regrassion의 weight는 label에 맞게 학습하기 위해서 Infinity로 발산하게 되고, bias는 Decision Boundary에 맞게 학습하기 위해서 + 또는 - 방향으로 Infinity하게 발산한다는 것이다.



- x data에 대해서 

  - x의 절대값이 1보다 작을때 theta의 updata

    Decision Bundary보다 Sigmoid Function의 sharply가 더욱 영향을 받는다.

    즉, weight보다 bias의 updata 크기가 더욱 크다.

  - x의 절대값이 1보다 클때 theta의 updata

    Sigmoid Function의 sharply보다 Decision Bundary가 더욱 영향을 받는다.

    즉, bias보다 weight의 updata 크기가 더욱 크다.

​	

### Loss Function

$$
Affine\ Function \ \ \ \ \ \ \ \ z^{(i)} = \theta_1 x^{(i)} + \theta_0 \\
Sigmoid\ Function\ \ \ \ \ \ \ \ \widehat{y}^{(i)} = \frac{1}{1+e^{-z^{(i)}}} = \sigma(z^{(i)})\\
Binary\ Cross\ Entropy\ Loss\ \ \ \ \ \ \ \ L =-[y log(\widehat{y}) + (1 - y)log(1 - \widehat{y})]
$$

Loss Function은 두 가지의 경우가 있다.

1. y = 0인 경우
   $$
   L =-log(1 - \widehat{y})
   $$
   
2. y = 1인 경우
   $$
   L =log(\widehat{y})
   $$



- Linear Regrassion과의 차이점

  Linear Regrassion은 noise에 대해서도 Loss Function이 줄어드는 모습을 볼 수 있지만, Logistic Regression에서는 noise에 대한 Loss는 점점 커진다는 것이다. (이로 인해 Model이 제대로 된 학습을 하고 있어도 Noise에 의한 Loss가 증가하는 모습이 plot에 그려지게되면 Loss가 증가하는 모습처럼 보이는 착시효과가 발생할 수 있다.)



- x data에 대해서 

  x의 절대값이 Decision Boundary에 가까울 수록 Loss Function이 더욱 크기 때문에 Sigmoid Function이 더욱Sharply하게 Updata된다.

  즉, data의 mean이 Decision Boundary와 일치했을 때 std가 작을수록 학습이 잘 됨을 알 수 있다.

  단, a*x(y-y_hat) 의 관점에서는 x가 너무 작아지기 때문에 data의 std는 적당한 타협point가 필요하다. 
  
  



### GDM

1. 각각의 Partial Derivative를 구해보자.
   $$
   data\ set \ \ \ \ \ \  (x^{(i)}, y^{(i)}) = (x, y) \ \ 단, \ y는\ 0\ or\ 1\
   $$

   $$
   Affine\ Function \ \ \ \ \ \ \ \ z = \theta_1 x + \theta_0 \\
   Sigmoid\ Function\ \ \ \ \ \ \ \ \widehat{y} = \frac{1}{1+e^{-z}}\\
   Binary\ Cross\ Entropy\ Loss\ \ \ \ \ \ \ \ L =-[y log(\widehat{y}) + (1 - y)log(1 - \widehat{y})]\\
   Cost\ Function\ \ \ \ \ \ \ \  J= mean(L)
$$
   
   

$$
\frac{\part z}{\part \theta_1} = x , \ \ \ \ \ \frac{\part z}{\part \theta_0} = 1\\ 
\frac{\part \widehat{y}}{\part z} = \widehat{y}(1-\widehat{y})\\
\frac{\part L}{\part \widehat{y}} = \frac{1-\widehat{y}}{\widehat{y}(1-\widehat{y})}\\
\frac{\part J}{\part L} = \frac{1}{n}
$$

2. Back Propagation을 진행해서 GDM을 구해보자.

$$
\frac{\part J}{\part \theta_1}  = \frac{\part J}{\part L}\frac{\part L }{\part \widehat{y}} \frac{\part \widehat{y}}{\part z} \frac{\part z}{\part \theta_1} = \frac{1}{n}*x*(\widehat{y} - y) \\
\frac{\part J}{\part \theta_1}  =\frac{\part J}{\part L} \frac{\part L }{\part \widehat{y}} \frac{\part \widehat{y}}{\part z} \frac{\part z}{\part \theta_0}  = \frac{1}{n}*(\widehat{y} - y)\\
$$

$$
\theta_1 := \theta_1 + \frac{1}{n}\alpha x_ (y - \widehat{y})\\
\theta_0 :=\theta_{0}+ \frac{1}{n}\alpha (y - \widehat{y})\\
$$

![](https://github.com/HibernationNo1/TIL/blob/master/image/47.jpg?raw=true)

![](https://github.com/HibernationNo1/TIL/blob/master/image/48.jpg?raw=true)



## 코드 구현

##### 1. main.py

```python
import numpy as np
import matplotlib as mpl
import matplotlib.pyplot as plt


import basic_node as nodes
import dataset_generator as dataset
import visualization as visual
import Function_implementation as function

np.random.seed(0)

visual_plot = visual.Visualization()

x_dict = {'mean' : 1, 'std' : 1, 'n_sample' :100 , 'noise_factor': 0.3,
            'cutoff': 1 , 'direction': 1}
# cutoff: pass 조건 (1초과, 1미만)
# direction : 1  1이상을 pass  (direction = 0 이면 1미만을 pass)

data_gen = dataset.Dataset_Generator()
data = data_gen.dataset_generator(x_dict)

batch_size = 8


# visual_plot.data_visualization(data)

logistic = function.SVLoR()
sigmoid = function.Sigmoid()
BCE_loss = function.BinaryCrossEntropy()

th_accum = logistic.get_Th()

loss_list = list()
iter_idx, check_freq = 0, 2
epochs, lr = 100, 0.01

for epoch in range(epochs):
    np.random.shuffle(data)
    for data_idx in range(data.shape[0]):
        batch = data_gen.get_data_batch(batch_size, data, data_idx)
        x, y =data[data_idx, 1], data[data_idx, -1]

        # forward propagation
        pred = logistic.forward(x)
        loss = BCE_loss.forward(y, pred)

        # backward propagation
        dpred = BCE_loss.backward()
        logistic.backward(dpred, lr)

        # result Tracking
        if iter_idx % check_freq == 0:
            th_accum = np.hstack((th_accum, logistic.get_Th()))
            loss_list.append(loss)
        iter_idx +=1

visual_plot.result_visualization(th_accum, loss_list, data)

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

class Dataset_Generator:
    def dataset_generator(self, x_dict):
        x_data = np.random.normal(x_dict['mean'], x_dict['std'], x_dict['n_sample'])
        x_data_noise = x_data + x_dict['noise_factor']*np.random.normal(0, 1, x_dict['n_sample'])

        if x_dict['direction'] > 0:
            y_data = (x_data_noise > x_dict['cutoff']).astype(np.int)  # x_data_onise > cutoff 는 bool형 반환 
        else :
            y_data = (x_data_noise < x_dict['cutoff']).astype(np.int) 

        data = np.zeros(shape = (x_dict['n_sample'], 1))
        data = np.hstack((data, x_data.reshape(-1, 1), y_data.reshape(-1, 1)))

        return data

    def get_data_batch(self, batch_size, data, batch_idx):
        n_batch = np.ceil(data.shape[0]/batch_size).astype(int)
        
        if batch_idx is n_batch -1:
            batch = data[batch_idx * batch_size:]
        else:
            batch = data[batch_idx * batch_size: (batch_idx + 1)*batch_size]
        return batch

```



##### 4. Function_implementation.py

```python
import numpy as np

import basic_node as nodes

class Affine:
    def __init__(self):
        self._feature_dim = 1
        self._Th = None

        self.node_imp()
        self.random_initialization()

    def node_imp(self):
        self._node1 = nodes.mul_node()
        self._node2 = nodes.plus_node()

    def random_initialization(self):
        r_feature_dim = 1 / self._feature_dim

        self._Th = np.random.uniform(low = -1*r_feature_dim,
                                        high = r_feature_dim, 
                                        size = (self._feature_dim + 1, 1))

    def forward(self, x):
        self._z1 = self._node1.forward(self._Th[1], x)
        self._z2 = self._node2.forward(self._Th[0], self._z1)
        return self._z2
    
    def backward(self, dz, lr):
        dth0, dz1 = self._node2.backward(dz)
        dth1, dx = self._node1.backward(dz1)

        self._Th[1] = self._Th[1] - lr*np.sum(dth1)
        self._Th[0] = self._Th[0] - lr*np.sum(dth0)     

    def get_Th(self):
        return self._Th

class Sigmoid:
    def __init__(self):
        self._pred = None

    def forward(self, z):
        self._pred = 1/(1 + np.exp(-1*z))       
        return self._pred
        
    def backward(self, dpred):
        dz = dpred*(self._pred*(1-self._pred))
        return dz

class SVLoR:
    def __init__(self):
        self._feature_dim = 1

        self._affine= Affine()
        self._sigmoid = Sigmoid()
    
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
        self._mean_node = nodes.mean_node()

    def forward(self, y, pred):
        self._y, self._pred = y, pred
        loss = -1*(self._y*np.log(self._pred) + (1-self._y)*np.log(1-self._pred))
        J = self._mean_node.forward(loss)
        return J

    def backward(self):
        dloss = self._mean_node.backward(1)
        dpred = dloss*(self._pred-self._y) / (self._pred *(1-self._pred))
        return dpred
```



##### 5. visualization.py

```python
import matplotlib as mpl
import matplotlib.cm as cm
import matplotlib.pyplot as plt 
import numpy as np

class Visualization:
    def __init__(self):
        plt.style.use('seaborn')
        mpl.rcParams['xtick.labelsize'] = 20
        mpl.rcParams['ytick.labelsize'] = 20
        mpl.rcParams['axes.labelsize'] = 30
        mpl.rcParams['axes.titlesize'] = 40
        mpl.rcParams['legend.fontsize'] = 30

    def data_visualization(self, data):
        fig, ax = plt.subplots(figsize = (30, 10))
        ax.set_title("Dataset for Binary Classification")
        ax.set_xlabel("X Value")
        ax.set_ylabel("Y Value")
        ax.scatter(data[:, 1], data[:, -1], 
                s = 200, alpha = 0.5)
        plt.show()

    def result_visualization(self, th_accum, loss_list, data):
        fig, ax = plt.subplots(2, 1, figsize = (15, 7))
        fig.subplots_adjust(hspace = 0.3)
        ax[0].set_title(r'$\vec{\theta}$' + ' Updata')

        ax[0].plot(th_accum[1, :], label = r'$\theta_{1}$')
        ax[0].plot(th_accum[0, :], label = r'$\theta_{0}$')

        ax[0].legend()
        iter_ticks = np.linspace(0, th_accum.shape[1], 10).astype(np.int)
        ax[0].set_xticks(iter_ticks)

        ax[1].set_title(r'$\mathcal{L}$')
        ax[1].plot(loss_list)
        ax[1].set_xticks(iter_ticks)

        n_pred = 1000
        fig, ax = plt.subplots(figsize = (10, 7))
        ax.set_title('Predictor Updata')
        ax.scatter(data[:,1], data[:, -1])

        ax_idx_arr = np.linspace(0, len(loss_list)-1, n_pred).astype(np.int)
        cmap = cm.get_cmap('rainbow', lut = len(ax_idx_arr))

        x_pred = np.linspace(np.min(data[:, 1]), np.max(data[:, 1]), 1000)
        for ax_cnt, ax_idx in enumerate(ax_idx_arr):
            z = th_accum[1, ax_idx]*x_pred + th_accum[0, ax_idx]
            a = 1/(1+np.exp(-1*z))
            ax.plot(x_pred, a, color = cmap(ax_cnt), alpha = 0.2)
        y_ticks = np.round(np.linspace(0, 1, 7), 2)
        ax.set_yticks(y_ticks)
        plt.show()
```

