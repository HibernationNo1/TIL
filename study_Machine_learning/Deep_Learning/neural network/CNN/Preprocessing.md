# Preprocessing

![](https://teddylee777.github.io/images/2020-01-16/2020-01-16-001.png)



## gray scale

### Image normalization

each pixel of gray scale image has value between 0 and 255 

so we have to change the pixel value to between 0 and 1

```python
def get_Image_normalization(images, labels):
    images = np.array(iamges/255.0, dtype = np.float32)
    labels = np.array(labels, dtype = np.float32)
    
    return images, labels
```

> dtype is always float32



### One-hot encoding

#### to_categorical

One-hot encoding meaning  change from categorical value to binary value

```python
from tensorflow.keras.utils import to_categorical
train_oh_labels = to_categorical(train_labels)
test_oh_labels = to_categorical(test_labels)
```

> class의 종류를 알아서 인지 후 분할



#### tf.one_hot

```python
import tensorflow as tf
oh_labels = tf.one_hot(labels, 10)
# 10개의 calss로 분할해서 one-hot
```

> class의 종류를 결정 후 분할



---

#### example

```python
from tensorflow.keras.utils import to_categorical

def get_Image_normalization(images, labels):
    images = np.array(iamges/255.0, dtype = np.float32)
    labels = np.array(labels, dtype = np.float32)
    return images, labels

def get_one_hot_encoding(images, labels):
    images, labels = get_Image_normalization(images, labels)
    labels = to_categorical(labels)
    return labels

def get_train_valid_test_set(train_images, train_labels, test_images, test_labels, valid_ratio = 0.15, random_state = 0)
	train_images, train_oh_labels = get_one_hot_encoding(train_images, train_labels)
    test_images, test_oh_labels = get_one_hot_encoding(test_images, test_labels)
    
    train_images, valid_images, train_oh_labels, valid_oh_images = train_test_split(train_images, train_oh_labels, test_size = valid_ratio, random_state = random_state)
    # sklearn
    
    return (train_images, train_oh_labels), (valid_images, valid_oh_labels), (test_images, test_oh_labels)
```

