# keras.layers

![](https://github.com/HibernationNo1/TIL/blob/master/image/k1..jpg?raw=true)

### Dense

![](https://wikidocs.net/images/page/49071/multilayerperceptron.PNG)

위 그림처럼 Layer 안의 각각 neuran에 이전 Layer의 다수 neuran이 전부 연결되는 형태를 Dense Layer라고 한다. 

```python
from tensorflow.keras.layers import Dense
```

> Dense Layer can receive only one dimension data
>
> and input data to dense layer is all columns



Dense Layer 생성

```python
object = Dense(unit = , activation = ' ')
```

- `object` : Dense Layer를 저장할 객체

- `unit` : Layer 안에 들어갈 neuron의 갯수

- `activation ` : 각 neuron에 적용할 activation 함수 

> 해당 Dense Layer을 통과할 때는 객체에 input을 넣어줘야 한다.
>
> `output = object(input)`

- `name` : Dense의 name을 정할 수 있다.



#### get_weights()

Dense Layer 객체의 weight와 bias를 반환한다.

`W, B = object.get_weights() `

- `object` : Dense Layer가 저장된 객체



```python
import tensorflow as tf

from tensorflow.keras.layers import Dense

N, n_feature = 1, 10  # N: minibatch size
X = tf.random.normal(shape=(N, n_feature))

n_neuron = 3
dense = Dense(unit = n_neuron, activation = 'sigmoid')  # neuron의 개수 = 3
Y = dense(X)

W, B = dense.get_weights()

print("X: ", X.shape)  	# (1, 10)
print("W: ", W.shape)	# (10, 3)
print("B: ", B.shape)	# (3, )
print("Y: ", Y.shape)	# (1, 3)
```

> dense layer의 neuron은 3개가 있고, data는 (1, 10)이기 때문에 
>
> 각 data에 대한 w의 jacobian matrics는 (10, 3)이 된다.

여기서 N을 8로 바꾼다면

```python
print("X: ", X.shape)  	# (8, 10)
print("W: ", W.shape)	# (10, 3)
print("B: ", B.shape)	# (3, )
print("Y: ", Y.shape)	# (8, 3)
```



#### Cascaded Dense Layer

```python
import tensorflow as tf

from tensorflow.keras.layers import Dense

N, n_feature = 4, 10
X = tf.random.normal(shape = (N, n_feature))

n_neurons = [3, 5, 8]
dense1 = Dense(units = n_neurons[0], activation = 'sigmoid')
dense2 = Dense(units = n_neurons[1], activation = 'sigmoid')
dense3 = Dense(units = n_neurons[2], activation = 'sigmoid')

A1 = dense1(X)
A2 = dense2(A1)
Y = dense3(A2)

print(f"X: {X.shape}")		# X: (4, 10)
print(f"A1: {A1.shape}")	# A1: (4, 3)
print(f"A2: {A2.shape}")	# A2: (4, 5)
print(f"Y: {Y.shape}")		# Y: (4, 8)
```

각각의 weight와 bias를 뽑아보자

```python
W1, B1 = dense1.get_weights()
W2, B2 = dense2.get_weights()
W3, B3 = dense3.get_weights()
```



이를 list를 사용해서 구현해보자.

```python
import tensorflow as tf

from tensorflow.keras.layers import Dense

N, n_feature = 4, 10
X = tf.random.normal(shape = (N, n_feature))

n_neurons = [10, 20, 30, 40, 50, 60, 70]

dense_layers = list()
for n_neuron in n_neurons:  	# 여러개의 dense layer 생성
    dense = Dense(units = n_neuron, activation = 'relu')
    dense_layers.append(dense)
    
for dense in dense_layers:		# 각 layer에 input으로 통과
    X = dense(X)
    
```



---



### Activation

```python
from tensorflow.keras.layers import Activation
```



Activation Function을 간단하게 구현할 수 있다.

`Acivation('function name')(x_data)`

```python
import tensorflow as tf
from tensorflow.feras.layers import Activation

X = tf.random.uniform(shape = (1, 5), minval = -10, maxval = 10)

softmax_value = Activation('softmax')(X)
```



**function name**

- sigmoid

- gelu

- get

- linear

- relu

- softmax

- swish

  등등



---



### Conv2D

2D Convolution Layer

Conv2D의 input data는 4 dimensions이어야 한다.  그래서 Conv2D는 input data가 4 dimensions이도록 알아서 받는다. 

(gray scalse image도 3차원으로 입력된다.)

```python
import tensorflow as tf
from tensorflow.keras.layers import Cov2D
```

```python
dense = Cov2D(filters, kernel_size, strides, padding, activation)
```

- `filters`

- `kernel_size`

- `strides `

- `padding  `

  > 'valid' : padding을 적용하지 않음 
  >
  > 'same' : output image의 size가 input과 동일하게끔 padding을 깔아준다. 
  >
  > 단, strides가 2 이상이면 padding에 same을 넣는다 해도 input과 output image의 size는 다를 수 있다.

- `activation`



#### get_weights()

```python
onv = Conv2D(filters = 1, kernel_size = 3, strides = 1, padding = 'valid')
w, b = conv.get_weights()
print(w, b)
```





**ex**

```python
import tensorflow as tf
import numpy as np

from tensorflow.keras.layers import Conv2D

tf.random.set_seed(0)

h_image, w_image= 7, 7
test_image = tf.random.normal(mean = 0, stddev = 1, shape = (1, w_image, h_image, 1))
# (batch_size, width, height, channel 개수) 즉, size = (7, 7) 의 grayscale iamge 1장

pad = 0
filter_size = 3
stride = 1
conv = Conv2D(filters = 1, kernel_size = filter_size, 
                strides = stride, padding = 'valid')
conved = conv(test_image)
# image가 1장 들어왔기 때문에 filter size는 자연스럽게 (1, 3, 3)

# print(conved.numpy().squeeze())
# H, W = (7 - 3)/1 + 1 = 5 임을 알 수 있다.
```



> difference from `tf.nn.Cov2d` : Cov2D는 tf.nn.Cov2d를 포함하여 더욱 다양한 기능을 가진 high level API이다.



unused tf.Conv2D

> gray scale image 1개

```python
import tensorflow as tf
import numpy as np

tf.random.set_seed(0)

batch_size = 2
H, W= 7, 7
test_image = tf.random.normal(mean = 0, stddev = 1, shape = (batch_size, W, H, 1))
# (batch_size, width, height, image 개수) 즉, size = (7, 7) 의 grayscale iamge 1장
# (None, W, H, chennal)
num_of_kernel = 1
pad = 'valid'
kernel_size = 3
stride = 1
filter = 8

w = tf.random.normal(mean = 0, stddev = 1, shape = (kernel_size, kernel_size))
b = tf.random.normal(mean = 0, stddev = 1, shape = (num_of_kernel, ))

test_image = test_image.numpy()
if pad == 'same':
    valid_idx = int(0)  
    H_conved = H
    W_conved = W
elif pad == 'valid':
    valid_idx = int((kernel_size-1)/2)  
    # padding  = 0 이므로 window slicing 시작 자리를 valid_idx로 설정
    H_conved = int((H - kernel_size)/stride) + 1
    W_conved = int((W - kernel_size)/stride) + 1

print(f"W_conved: {W_conved} , H_conved : {W_conved}") 


#test = np.zeros_like(test_image)
# window slicing
conved_images = list()
batch_size = test_image.shape[0]
for filter_idx in range(filter):
    for batch_idx in range(batch_size):
        conved = np.zeros(shape = (H_conved, W_conved))
        cov_r_idx = 0
        for r_idx in range(valid_idx, H - valid_idx, stride):
            cov_c_idx = 0
            for c_idx in range(valid_idx, W - valid_idx, stride): 
                
                receptive_field = test_image[batch_idx, r_idx - valid_idx : r_idx + valid_idx + 1, 
                                            c_idx - valid_idx : c_idx + valid_idx + 1, -1:]
                # print(receptive_field.shape)  
                # filter shape대로 receptive_field가 잘 설정됨을 알 수 있다.

                receptive_field = receptive_field.squeeze()
                conved_tmp = receptive_field*w  # weight
                conved_tmp = np.sum(conved_tmp) + b            
                conved[cov_r_idx,cov_c_idx] = conved_tmp
                #test[r_idx, c_idx] = 1
                #print(test, "\n")
                cov_c_idx +=1
            cov_r_idx +=1
        
        conved = conved[np.newaxis,:, :]
        if batch_idx == 0:
            conved_img_tmp = conved
        else:
            conved_img_tmp = np.vstack([conved_img_tmp, conved])
    if filter_idx == filter-1:
        conved_images.append(conved_img_tmp)
        conved_images = np.stack(conved_images, axis=3)
        #import sys
        #print(conved_images.shape)
        #sys.exit()
    else:
        conved_images.append(conved_img_tmp)
```



---



### Pooling

Max Pooling이나 Average Pooling은 사용법이 동일

#### MaxPool2D

```python
import tensorflow as tf
from tensorflow.keras.layers import MaxPooling2D
```

**property**

- `poolsize = ` 

- `strides = ` 

- `padding = ` : 사용 안함

  > `valid`
  >
  > `same`

- `data_format = `

  > None



```python
test_image = tf.random.normal(mean = 0, stddev = 1, shape = (1, 7, 7, 1))
maxpool = MaxPooling2D(pool_size = 2, strides = 2)
maxpooled = maxpool(test_image)
```





#### AveragePooling2D

```python
import tensorflow as tf
from tensorflow.keras.layers import AveragePooling2D
```

**property**

- `poolsize = (, )` 

- `strides = ` 

- `padding = ` : 사용 안함

  > `valid`
  >
  > `same`

- `data_format = `

  > None



```python
test_image = tf.random.normal(mean = 0, stddev = 1, shape = (1, 7, 7, 1))
avepool = AveragePooling2D(pool_size = 2, strides = 2)
avepooled = avepool(test_image)
```



#### GlobalAveragePooling2D

AveragePooling2D을 전체 feature map에 적용

kernel size == feature map size 이기 때문에 반환되는 값은 scala임

```python
from tensorflow.keras.layers import GlobalAveragePooling2D
x = GlobalAveragePooling2D()(x)
```

> ex) 3 × 3 의 image에 GlobalAveragePooling2D 를 하면 값 1개만 나옴



---



### Flatten

input으로 받은 (1, n) matrix를 (n, ) 과 같은 vector shape으로 변경해준다

```python
import tensorflow as tf
from tensorflow.keras.layers import Flatten
```

딱히 설정해주어야 하는 argument는 없다



```python
Flatten()(x_data)
```

batch size는 그대로 유지하고 data만 flatten 시켜준다.



```python
feature_map = tf.random.normal(mean = 0, stddev = 1, shape = (1, 11, 11, 128))

flatten = Flatten()
flattened = flatten(feature_map)

print(flattened.shape)  # (1, 15488)
# 11 * 11 * 128
```





### Layer

```python
from tensorflow.keras.layers import Layer
```

Layer 한 개를 만드는 Sub-classing이 가능하게 한다.



```python
class ConvLayer(Layer):
    def __init__(self, filters, kernel_size):
        super(ConvLayer, self).__init__()

        self.conv = Conv2D(filters = filters, kernel_size = kernel_size,
                            padding = 'same')
        self.conv_act = Activation('relu')
        self.conv_pool = MaxPooling2D(pool_size = 2, strides = 2)

    def call(self, x):
        x = self.conv(x)
        x = self.conv_act(x)
        x = self.conv_pool(x)
        return x
```



굳이 Model Sub-classing이 있는데 이걸 사용하는 이유

layer 하나하나의 속성을 간편하게 결정할 수 있다.



### Keras Functional API

#### Input

Functional API를 이용한 Model 설계에 사용된다.

what Functional API : model의 input 구조와 output 구조를 개발자가 원하는대로 만드는 model 구현 방법

Keras Functional API (https://www.tensorflow.org/guide/keras/functional)

```python
from tensorflow.keras.layers import Input
input_tensor = Input(shape = (INPUT_SIZE, INPUT_SIZE))
```



**ex1**

Input을 사용한 Model은 keras.models에서 import한 Model이다.

```python
from tensorflow.keras.models import Model
```

그리고 해당 Model은 argument로 Input의 instance을 받아간다.

```python
from tensorflow.keras.layers import Input, Flatten, Dense
from tensorflow.keras.models import Model

input_tensor = Input(shape = (INPUT_SIZE_W, INPUT_SIZE_H)) # create instance

x = Flatten()(input_tensor)
x = Dense(units = 10, activation = 'sigmoid')(x)
output = Dense(units = 20, activation = 'sigmoid')(x)

model = Model(inputs = input_tensor, outputs = output)
```

line 6, 7, 8의 code를 Model-subclassing을 하지 않고도  Model instance를 만들 수 있다.

output부터 역으로 올라가며 학습 과정을 확인할 수 있다.



**ex2**

```python
class YOLOv1(tf.keras.Model):
    def __init__(self, input_height, input_width, cell_size, boxes_per_cell, num_classes):
        super(YOLOv1, self).__init__()
        base_model = tf.keras.applications.InceptionV3(include_top=False, weights='imagenet', input_shape=(input_height, input_width, 3))
        # Bring GoogLeNet ver.3, only feature extractor part
        base_model.trainable = True
        # include parameters of GoogLeNet ver.3 for training
        # To get better performance
        x = base_model.output
```

> model subclassing 안에서 다른 이미 완성된 model(InceptionV3) 을 가져와서 사용할 때 위 처럼 사용
>
> `weights='imagenet'` 사전훈련 된 파라미터를 가져옴



**Model-subclassing**

```python
class TestModel(Model):						# 여기서부터
    def __init__(self):
        super(TestModel, self).__init__() 
        self.flatten = Flatten()
        self.dense1 = Dense(units = 10, activation = 'sigmoid')
        self.dense2 = Dense(units = 20, activation = 'sigmoid')
        
    def call(x)
    	x = self.flatten(x)
        x = self.dense1(x)
        x = self.dense2(x)
        return x
```







### Batch Normalization

why need batch normalization?

Arise 'internal Convariate Shift' issue when data passed through a filter. Batch Normalization need to prevent for this issue

> internal Convariate Shift 
>
> 각 layer를 통과 할 때마다 input 데이터의 분포가 조금씩 변하는 현상



![](https://blog.kakaocdn.net/dn/r5elS/btqBPXN1ib0/SKLvm2ZQj4pky6MyYOst3K/img.png)


$$
layer\ output \Rightarrow \   x \Rightarrow \  \widehat{x} = \frac{x-u}{\sigma} \Rightarrow \  y = \gamma\widehat{x} \\
\Rightarrow y = \gamma\widehat{x} + \beta \ \ \ \ \ (BN)\\ 
\gamma : Scaling\ 파라미터\\
\beta : \ shift\ 파라미터
$$
layer를 통과한 data가 weight에 의해 한 쪽에 치우친 형태로 나오면 Batch Normalization 을 shift 파라미터로 사용해서 data 위치를 보정해준다.

> 동적으로 layer의 output을 조절할 수 있게 된다.



언제 적용할까?

Conv2D -> BN -> Activation Function

단, test data에는 적용하지 않는다.

> Scaling파라미터와 beta 파라미터는 학습시에 최종 결정된 값을 이용 







어떤 효과가 있나?

- performance improvements

- Regularization 

  > Normalization 후에 scaling, shift로 일종의 noise추가 효과

- Weight Initialization설정을 크게 신경 쓸 필요가 없다.



```python
from tensorflow.keras.layers import BatchNormalization
x = Conv2D(filter = 32, kernel_size = 3, padding = 'same')(input)
x = BatchNormalization()(x)
x = Activation('relu')(x)
```

