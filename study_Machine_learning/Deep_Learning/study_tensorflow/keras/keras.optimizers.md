# keras.optimizers

```python
import tensorflow as tf
```



### SGD

Stochastic Gradient Descent

```python
from tensorflow.keras.optimizers import SGD
SGD(lr = 0.01, momentum = None, decay = None, nesterov = False)
```

> default

- `lr` : learning rate





### RMSprop

```python
from tensorflow.keras.optimizers import RMSprop
RMSprop(lr=0.001, rho=0.9, epsilon=None, decay=0.0)
```

> default

- `lr` : learning rate





### Adam

```python
from tensorflow.keras.optimizers import Adam
Adam(lr=0.001, beta_1=0.9, beta_2=0.999, epsilon=None, decay=0.0, amsgrad=False)
```

> default

- `lr` : learning rate



----



opt = optimizer -bject

## opt. Function

#### opt.apply_gradients

```python
opt.apply_gradients(zip(processed_grads, var_list))
```

호출한 optimizer 방법에 따라 optimizer 



ex)

```python
from tensorflow.keras.optimizers import SGD

SGD.apply_gradients(zip(processed_grads, var_list))
# gradient descent method를 통해 optimizer 
```

