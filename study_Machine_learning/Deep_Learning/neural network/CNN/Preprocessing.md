# Preprocessing



### Image normalization

#### gray scale

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

One-hot encoding meaning  change from categorical value to binary value

```python
from tensorflow.keras.utils import to_categorical
train_oh_labels = to_categorical(train_labels)
test_oh_labels = to_categorical(test_labels)
```

