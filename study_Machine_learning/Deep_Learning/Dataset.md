# Dataset

## Make dataset



### Dataset implementation

#### Dataset for Regression

```python
import tensorflow as tf

N, n_feature = 100, 5  # 5개의 feature마다 100개의 sample
t_weights = tf.constant([1, 2, 3, 4, 5], dtype = tf.float32)
t_bias = tf.constant([10], dtype = tf.float32)

X = tf.random.normal(mean = 0, stddev = 1, shape = (N, n_feature))

Y = tf.reduce_sum(t_weights*X, axis = 1) + t_bias

# shape 확인
print(X.shape, t_weights.shape, t_bias.shape, Y.shape)

# print(X)
# print(Y)
```



#### Dataset for Binary Classicifation

```python
import tensorflow as tf

N, n_feature = 20, 5  
t_weights = tf.constant([1, 2, 3, 4, 5], dtype = tf.float32)
t_bias = tf.constant([10], dtype = tf.float32)

X = tf.random.normal(mean = 0, stddev = 1, shape = (N, n_feature))

Y = tf.reduce_sum(t_weights*X, axis = 1) + t_bias
# print(Y)
Y = tf.cast(Y > 10, tf.int32)  # Dicision Boundary = 10
# print(Y)

# shape 확인
print(X.shape, t_weights.shape, t_bias.shape, Y.shape)
```



#### Dataset for Multi-class Classification

make five class and show using matplot

```python
import tensorflow as tf
import matplotlib.pyplot as plt

N, n_feature = 10, 2 
n_class = 5

X = tf.zeros(shape = (0, n_feature))
Y = tf.zeros(shape = (0, 1), dtype = tf.int32)

fig, ax = plt.subplots(figsize = (5, 5))

for class_idx in range(n_class):
    center = tf.random.uniform(minval = -15, maxval = 15, shape = (2, ))

    x1 = center[0] + tf.random.normal(shape = (N, 1))
    x2 = center[1] + tf.random.normal(shape = (N, 1))

    x = tf.concat((x1, x2), axis = 1)   # [x1, x2]
    y = class_idx*tf.ones(shape = (N, 1), dtype = tf.int32)  # for expression number of class
    
    ax.scatter(x[:, 0].numpy(), x[:, 1].numpy())

    X = tf.concat((X, x), axis = 0)
    Y = tf.concat((Y, y), axis = 0)
    print(X.shape, Y.shape)

print(X, Y)
plt.show()
```



and apply One-hot encoding to Labels

the code needs a few modifications because Y_data must be vector shape for apply One-hot encoding

- line 8 

  ```python
  Y = tf.zeros(shape = (0, ), dtype = tf.int32)
  ```

- line 19

  ```python
  y = class_idx*tf.ones(shape = (N, ), dtype = tf.int32)
  ```



```python
import tensorflow as tf
import matplotlib.pyplot as plt

N, n_feature = 10, 2 
n_class = 5

X = tf.zeros(shape = (0, n_feature))
Y = tf.zeros(shape = (0, ), dtype = tf.int32)

fig, ax = plt.subplots(figsize = (5, 5))

for class_idx in range(n_class):
    center = tf.random.uniform(minval = -15, maxval = 15, shape = (2, ))

    x1 = center[0] + tf.random.normal(shape = (N, 1))
    x2 = center[1] + tf.random.normal(shape = (N, 1))

    x = tf.concat((x1, x2), axis = 1)   # [x1, x2]
    y = class_idx*tf.ones(shape = (N, ), dtype = tf.int32)  

    ax.scatter(x[:, 0].numpy(), x[:, 1].numpy())

    X = tf.concat((X, x), axis = 0)
    Y = tf.concat((Y, y), axis = 0)
    print(X.shape, Y.shape)

Y = tf.one_hot(Y, depth = n_class, dtype = tf.int32)
print(X, Y)
plt.show()
```



### Use Dataset API

#### from_tensor_slices((X, Y))

This function only for tensor data that make self (like small size data)

```python
import tensorflow as tf


N, n_feature = 100, 5 
batch_size = 32

t_weights = tf.constant([1, 2, 3, 4, 5], dtype = tf.float32)
t_bias = tf.constant([10], dtype = tf.float32)

X = tf.random.normal(mean = 0, stddev = 1, shape = (N, n_feature))
Y = tf.reduce_sum(t_weights*X, axis = 1) + t_bias

dataset = tf.data.Dataset.from_tensor_slices((X, Y))
dataset = dataset.batch(batch_size).shuffle(100)

for x, y in dataset:
    print(x.shape, y.shape)
```

