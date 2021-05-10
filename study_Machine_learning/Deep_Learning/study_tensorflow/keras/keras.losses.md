# keras.losses

### MSE

```python
from tensorflow.keras.losses import MeanSquaredError
```



ex)

```python
import tensorflow as tf

from tensorflow.keras.losses import MeanSquaredError

loss_object = MeanSquaredError()

batch_size = 32

predictions = tf.random.normal(shape = (batch_size, 1))
labels = tf.random.normal(shape = (batch_size, 1))

mse = loss_object(labels, predictions)
```





### BCE

```python
from tensorflow.keras.losses import BinaryCrossentropy
```

ex)

```python
import tensorflow as tf

from tensorflow.keras.losses import BinaryCrossentropy

batch_size = 32
n_class = 2

predictions = tf.random.uniform(shape = (batch_size, 1), 
                                minval = 0, maxval = 1, 
                                dtype = tf.float32)

labels = tf.random.uniform(shape = (batch_size, 1), 
                                minval = 0, maxval = n_class, 
                                dtype = tf.int32)

loss_object = BinaryCrossentropy()
loss = loss_object(labels, predictions)

print(loss.numpy())
```





### CCE

```python
from tensorflow.keras.losses import CategoricalCrossentropy
```



ex)

```python
import tensorflow as tf

from tensorflow.keras.losses import CategoricalCrossentropy

batch_size, n_class= 16, 5

predictions = tf.random.uniform(shape = (batch_size, n_class), 
                                minval = 0, maxval = 1, 
                                dtype = tf.float32)
pred_sum = tf.reshape(tf.reduce_sum(predictions, axis = 1), (-1, 1))
predictions = predictions / pred_sum
# to make the sum of predictions to 1

labels = tf.random.uniform(shape = (batch_size, ), 
                                minval = 0, maxval = n_class, 
                                dtype = tf.int32)

labels = tf.one_hot(labels, n_class)
# print(labels)

loss_object = CategoricalCrossentropy()
loss = loss_object(labels, predictions)
print(loss.numpy())  

# or
loss = tf.reduce_mean(tf.reduce_sum(-labels*tf.math.log(predictions), axis = 1))
print(loss.numpy()) # same loss
```



