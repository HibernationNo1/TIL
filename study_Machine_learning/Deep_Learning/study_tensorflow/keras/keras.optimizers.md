# keras.optimizers

Reference : https://www.tensorflow.org/api_docs/python/tf/keras/optimizers

```python
import tensorflow as tf
```



### SGD

Stochastic Gradient Descent

```python
from tensorflow.keras.optimizers import SGD
optimizer = SGD(lr = 0.01, momentum = None, decay = None, nesterov = False)
```

> default

- `lr` : learning rate



### RMSprop

```python
from tensorflow.keras.optimizers import RMSprop
optimizer = RMSprop(lr=0.001, rho=0.9, epsilon=None, decay=0.0)
```

> default

- `lr` : learning rate



### Adam

```python
from tensorflow.keras.optimizers import Adam
optimizer = Adam(lr=0.001, beta_1=0.9, beta_2=0.999, epsilon=None, decay=0.0, amsgrad=False)
```

> default

- `lr` : learning rate



#### optimizer.lr()

`tensorflow.keras.optimizers` 의 instance를 통해 learning rate에 접근

```python
lr = optimizer.lr(step)
```

- `step` : checkpoint 설정을 해놓았다면, 해당 step에 대한 learning rate를 반환



**예시**

```python
from tensorflow.keras.optimizers import Adam
optimizer = Adam(lr=0.001, beta_1=0.9, beta_2=0.999, epsilon=None, decay=0.0, amsgrad=False)

Adam_lr = optimizer.lr()  # 0.001
```







----



## schedules

Reference : https://www.tensorflow.org/api_docs/python/tf/keras/optimizers/schedules



#### ExponentialDecay

Reference : https://www.tensorflow.org/api_docs/python/tf/keras/optimizers/schedules/ExponentialDecay

learning rate detail을 결정, learning rate를 주기적으로 줄이는데 사용한다.

```python
from tensorflow.keras.optimizers import schedules

lr = schedules.ExponentialDecay(
    init_learning_rate,
    decay_steps= , 
    decay_rate= , 
    staircase=)

optimizer = Adam(lr)
```

```
lr = init_learning_rate * decay_rate ^  (global_step / decay_steps)
```

- `init_learning_rate` : initial learning rate

- `decay_steps` : 몇 step마다 learning rate를 바꿀건지

- `decay_rate` : 기존의 learning rate에 곱할 값

- `staircase` : boolean

  > True : (global_step / decay_steps) 이 integer의 결과값을 가진다.



**예시**

```python
from tensorflow.keras.optimizers import schedules
from tensorflow.keras.optimizers import Adam

flags.DEFINE_float('init_learning_rate', default=0.0001, help='initial learning rate')
flags.DEFINE_float('lr_decay_rate', default=0.5, help='decay rate for the learning rate')
flags.DEFINE_integer('lr_decay_steps', default=2000, help='number of steps after which the learning rate is decayed by decay rate')

lr = schedules.ExponentialDecay(
    FLAGS.init_learning_rate,
    decay_steps= FLAGS.lr_decay_steps, 
    decay_rate= FLAGS.lr_decay_rate, 
    staircase=True)

optimizer = Adam(lr)
```





opt = optimizer object

## optimizer. Function

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

