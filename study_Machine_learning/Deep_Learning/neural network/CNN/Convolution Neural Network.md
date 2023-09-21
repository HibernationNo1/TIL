# Convolution Neural Network, CNN

CNN은 image를 data set으로 가진 Mashine learning을 하기에 최적화 된 Deep learning model이다.

> Convolution Neural Network는 Correlational Neural Network가 더 맞는 이름이라고 할 수 있다.
>
> why? Convolution은 input data를 180도 회전 시킨 다음에 Filter에 input하지만, 
>
> Correlation은 input data를 그대로 Filter에 input시키기 떄문에다. 그리고 Deep Learning의 CNN에서의 Convolution Operation은 실제로 Image 를 180도 회전시키지 않기 때문에 엄연히 말하자면 Correlation Operation이라고 할 수 있다.



- CNN의  Classification과정

  input	 -->	Feature Extractor	-->	Classifier(ANN)	-->	Classification Result

![](https://t1.daumcdn.net/cfile/tistory/277CEA48573525252F)

>  위 그림의 Subsampling 까지가 Feature Extractor 과정이고, 그 이후부터 Output까지가 Classifiaction 과정이다.



### Feature Extractor

(특징을 추출하는 과정)

image에서 특정 features를 추려내서 여러 Class로 분류한다. 

그리고 이 fearture extractor 과정에서 Convolution과 Pooling Operation이 진행된다.



#### Convolution

image의 특정 영역만 똑 떼서 Filter와 곱 연산을 통해 Feature을 Extraction하는 연산을 Convolution Operation이라고 한다. 

**Convolution process**

Size = (X, X) 인 Filter를 size = (Y, Y)인 image의 좌측 상단에 dotted(element wise) product 한 후 Sum을 적용한다. 그리고 우측으로 한 칸 이동하고 위 과정을 iteration하며 Filter가 image를 전부 지날 때 까지 iteration하는 것이다. 또한 output matrix의 각각의 elements에 bias를 add하게 된다.

![](https://blog.kakaocdn.net/dn/sSowL/btqCLeODqbH/0VNYdYkafga04UZhgxliv0/img.png)

이 과정에서 Filter의 각 elements와  image의 특정 영역의 각 elements의 value가 비슷하면 해당 matrix의 sum이 커지는 것이다.

> image의 영역 중 kerenel과 convolution 되는 영역을 **Receptive Field** 라고 한다.
>
> Convolution Operation : Receptive Field를 따라서 kerenel과 correlation 연산을 진행하는 것

그리고 위 과정을 통해 얻어진 output matrix에 Activation Function(sigmoid나 Tanh 등)을 Operation하면 각각의 element가 0또는 1을 가진 matrix가 됨을 알 수 있다.  (0이면 deactivate, 1이면 activate) 

> image에  kerenel을 통해 convolution operate를 할 때 kerenel의 종류에 따라 image에서 extraction하는 feature가 달라지게 된다. (gray scale을 extraction하는 kerenel, 더욱 선명한 image feature만을 extraction하는 kerenel 등)



##### Filter Bank

여러개의 filter를 만들어 놓고, image가 각 filter를 통과하도록 하는 것이 filter bank의 의미이다.

> ANN에서는, Dense Layer의 각각의 perceptron이 바로 이 filter 역할을 하는 것이다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/dc1.jpg?raw=true)

filter bank를 통과하고 나온 output을 모아놓은 것이 바로 feature map이다. (filter bank에 10개의 filter가 있다고 하면 10개의 feature map이 나오게 되는것이다.)

> filters을 통해 추출한 **활성화 맵(feature map)**은 원본 image에서 명확히 들어나지 않았던 특징들을 보여준다. 

kernel은 filter의 채널을 의미하는 것이다.



- Shape of Filter Bank

  image의 pixel이 (W, H)라고 할 때

  

##### Multi-channel input

color image는 (B, G, R)3개의 channel이 있는데, 이러한 image가 input되면 각각의 channel에 대해서 filter bank가 적용된다.(이 때 1개의 filter당 3개의 kernel이 있다.)

그 과정에서 sum(receptive field * kernel) == output의 1 pixel이 된다. receptive field가 한 칸씩 이동해 가며 compute를 해서 완성된 output의 개수는 filter bank에 존재하는 filter의 개수와 동일하다. 이것이 Multi-channel input에서의 Convolution이다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/dc4.jpg?raw=true)

> color image 가 convolution layer의 input일 때, fieter가 1개라면 kernel은 3개. 
>
> 각각의 kernel을 전부 더한 후 마지막에 bias를 add ==> ouput은 1개
>
> filter bank에 10개의 filter가 있다고 하면 10개의 feature map이 나오게 되는것이다.

![](https://debuggercafe.com/wp-content/uploads/2019/06/LeNet-5.png)

위 이미지에서 input이 grays cale임을 알 수 있다.

첫 convolutions를 통해 feature map이 6개가 생김을 보면 filter가 6개가 있었음을 알 수 있다.

그 다음 subsampling을 거친 후 두 번째 convolutions를 통과하자 feature map이 16개가 생겼다. 이는 두 번째 convolutions 과정에서 filter bank안의 filter가 16개가 있음을 알 수 있다.

>  각각의 filter는 6개의 input에 전부 operations됐고 그  result를 sum한 것이 한 개의 feature map이다.



위 그림에서 알 수 있듯, 각각의 operations가 진행될 때마다 filter bank를 거치기 때문에 CNN은 cascaded filter bank를 통해 convolution 연산을 통해 원하는 신호를 뽑아내는 구조이다.



##### Zero padding

image에 filter sliding을 하게 되면 그 output matrix의 shape은 더욱 작아지게 된다.(변화가 있다.)

그렇기 때문에 이를 방지하기 위해 image의 가장자리에 0의 값을 가진 pixel을 두르는 것을 zero padding이라고 한다.

![](https://t1.daumcdn.net/cfile/tistory/993372345B5977F410)

> 제로패딩 1을 적용한 이미지

size를 보존하기 위한 padding의 크기는 (F-1)/2 만큼 하면 된다.

F : size of filter





##### Stride

Convoltion 과정에서 filter silding을 진행할 때, 옆으로 한 칸 이동하는 과정을 skep하고 더 이동하는 것을 의미한다. 이는 찾고자 하는 feature이 Receptive Field에 없을 때 convolution operation을 줄이기 위해서 적용한다. 

> 한 칸씩 이동하는 것은 stride ==1 을 의미한다. (두 칸씩 stride == 2) 
>
> 옆으로 이동하는 stride 말고도 아래로 이동하는 stride도 설정할 수 있다.



#### Sub-sampling

Pooling은 feature map 위에 receptive field를 결정하고 inout으로 받으며 silding 하면서 특정 값만 ouput으로 내보내는 방식으로, 이로 인해 만들어지는 matrix는 기존의 matrix보다 더욱 가벼워지고 덕분에 amount of computations을 reduce하는 효과와 image의 강한 feature만을 extraction하는 효과가 있다. 

![](https://github.com/HibernationNo1/TIL/blob/master/image/dc3.jpg?raw=true)

> stride = 2



##### Max Pooling

receptive field에서 가장 큰 value만을 추려낸다.



##### Average Pooling

receptive field에서 average만을 추려낸다.

> Reason why Average pooling isn't working well :
>
> Tanh activation function을 사용할 때 그 값이 서로 상쇄되거나, Relu activation function을 사용할 때 0이라는 value 때문에 activation average가 상쇄되는 문제가 발생할 수 있다.
>
> 즉 activation의 영향 때문에 잘 사용하지 않는다.





---



#### Numerical expression

- Kerenel shape of convolution layer

  kerenel의 height, width가 (H, W)이고, 이러한 kerenel이 D_in개 만큼 있다고 할 때
  $$
  shape\ of\ kerenel\\
  = (H_f, W_f, D_{in})
  $$
  그리고 내가 만들고 싶은 feature map의 개수를 D_out이라고 하면

  Filter Bank의 shape은 다음과 같다.
  $$
  shape\ of\ Filter\ Bank \\
  = (H_f, W_f, D_{in}, D_{out})
  $$
  4 dimension임을 알 수 있다.

  그리고 이 shape이 곧 **weight의 shape**이다.

  > bias의 shape = (D_out, )



- Input / Output shape

  image가 convolution layer을 한 번 통과하게 되면 그 shape에는 변화가 생긴다.
  $$H_n = \left[ \frac{H_{n-1} + 2p - k}{s}  \right] + 1 \\
  W_n = \left[ \frac{W_{n-1} + 2p - k}{s}  \right] + 1$$

  > H : height of image 
  >
  > W : width of image
  >
  > p : padding width
  >
  > s : stride
  >
  > k : size of kerenel  // size = (3, 3) 이면 k == 3
  >
  > 각 수식이 float으로 떨어지면 int를 씌워서 정수로 만들어야 한다. (28/3 +1 == 9 + 1)
  >
  > ex)
  >
  > H_n, W_n = (128, 128)
  >
  > p = 1, s = 2, k = 3
  >
  > H_n-1  = int((128+2-3)/2) + 1 = 64,  	W_n-1  = int((128+2-3)/2) + 1 = 64

  이 공식은 pooling layer에서도 동일하게 사용할 수 있다.
  $$
  H_n = \left[ \frac{H_{n-1} + 2p - k}{s}  \right] + 1 \\
  W_n = \left[ \frac{W_{n-1} + 2p - k}{s}  \right] + 1
  $$

  만약 padding의 'same'이라는 argument를 주고, strides가 1이면
  
  layer을 통과해도 image의 size는 변하지 않는다.





- Convolution Matrix

  Convolution computation 을 Matrix 의 multiplication으로 표현하는 방법

  ![](https://github.com/HibernationNo1/TIL/blob/master/image/dc2.jpg?raw=true)

---



### Fully connected

Feature Extractor을 통과하고 나온 data를 input으로 받는다.

Fully connected는 ANN이라고 생각하면 됨

마지막에 Softmax와 같은 Activation Function을 적용함으로써 output을 각각의 class에 대한 probability로 만들어준다.



##### Flatten

Feature Extractor의 마지막 단계

이 때의 shape은 (1, 1, n) 형태이기 때문에

(n, ) 의 shape으로 (vector) 만들어주는 작업





---



## CNN Implement

**simple ver**

```python
import tensorflow as tf
from tensorflow.keras.layers import Conv2D, MaxPooling2D
from tensorflow.keras.layers import Flatten, Dense

test_image = tf.random.normal(mean = 0, stddev = 1, shape = (32, 50, 50, 3))
conv =Conv2D(filters = 8, kernel_size = (3, 3), 
            padding = 'same', activation = 'relu')
conv_pool = MaxPooling2D(pool_size = 2, strides = 2)
flatten = Flatten()
dense = Dense(units = 10, activation = 'softmax')

print(f"test_image : {test_image.shape}")

x = conv(test_image)
print(f"after conv: {x.shape} ")

x = conv_pool(x)
print(f"after conv_pool: {x.shape} ")

x = flatten(x)
print(f"after flatten : {x.shape}")

x = dense(x)
print(f"after danse: {x.shape}")
```



**CNN with Model**

##### sequential()

```python
import tensorflow as tf

from tensorflow.keras.models import Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D
from tensorflow.keras.layers import Flatten, Dense

model = Sequential()

# feature extractor
model.add(Conv2D(filters = 8, kernel_size = 5, padding = 'same', activation = 'relu'))           
model.add(MaxPooling2D(pool_size = 2, strides = 2))

model.add(Conv2D(filters = 32, kernel_size = 5, padding = 'same', activation = 'relu'))       
model.add(MaxPooling2D(pool_size = 2, strides = 2))

# classifier
model.add(Flatten())
model.add(Dense(units = 64, activation = 'relu'))
model.add(Dense(units = 10, activation = 'softmax'))

model.build(input_shape = (None, 28, 28, 1))
model.summary()
```

```
Model: "sequential"
_________________________________________________________________
Layer (type)                 Output Shape              Param #
=================================================================
conv2d (Conv2D)              (None, 28, 28, 8)         208
_________________________________________________________________
max_pooling2d (MaxPooling2D) (None, 14, 14, 8)         0
_________________________________________________________________
conv2d_1 (Conv2D)            (None, 14, 14, 32)        6432
_________________________________________________________________
max_pooling2d_1 (MaxPooling2 (None, 7, 7, 32)          0
_________________________________________________________________
flatten (Flatten)            (None, 1568)              0
_________________________________________________________________
dense (Dense)                (None, 64)                100416
_________________________________________________________________
dense_1 (Dense)              (None, 10)                650
=================================================================
Total params: 107,706
Trainable params: 107,706
Non-trainable params: 0
_________________________________________________________________
```



##### Model Sub-classing

```python
import tensorflow as tf

from tensorflow.keras.models import Model
from tensorflow.keras.layers import Conv2D, MaxPooling2D
from tensorflow.keras.layers import Flatten, Dense

class CNN_Model(Model):
    def __init__(self):
        super(CNN_Model, self).__init__()

        # feature extractor
        self.conv1 = Conv2D(filters = 8, kernel_size = 5, padding = 'same', activation = 'relu')
        self.conv1_pool =  MaxPooling2D(pool_size = 2, strides = 2)
        self.conv2 = Conv2D(filters = 32, kernel_size = 5, padding = 'same', activation = 'relu')       
        self.conv2_pool = MaxPooling2D(pool_size = 2, strides = 2)

        # classifier
        self.flatten = Flatten()
        self.dense1 = Dense(units = 64, activation = 'relu')
        self.dense2 = Dense(units = 10, activation = 'softmax')

    def call(self, x):
        x =self.conv1(x)
        x =self.conv1_pool(x)
        x =self.conv2(x)
        x =self.conv2_pool(x)

        x =self.flatten(x)
        x =self.dense1(x)
        x =self.dense2(x)
        return x
        
model = CNN_Model()
model.build(input_shape = (None, 28, 28, 1))
model.summary()
```

```
Model: "cnn__model"
_________________________________________________________________
Layer (type)                 Output Shape              Param #
=================================================================
conv2d (Conv2D)              multiple                  208
_________________________________________________________________
max_pooling2d (MaxPooling2D) multiple                  0
_________________________________________________________________
conv2d_1 (Conv2D)            multiple                  6432
_________________________________________________________________
max_pooling2d_1 (MaxPooling2 multiple                  0
_________________________________________________________________
flatten (Flatten)            multiple                  0
_________________________________________________________________
dense (Dense)                multiple                  100416
_________________________________________________________________
dense_1 (Dense)              multiple                  650
=================================================================
Total params: 107,706
Trainable params: 107,706
Non-trainable params: 0
_________________________________________________________________
```



##### M-Sub + Seq

```python
import tensorflow as tf

from tensorflow.keras.models import Model, Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D
from tensorflow.keras.layers import Flatten, Dense

class CNN_Model(Model):
    def __init__(self):
        super(CNN_Model, self).__init__()

        # feature extractor
        self.fe = Sequential()
        self.fe.add(Conv2D(filters = 8, kernel_size = 5, padding = 'same', activation = 'relu'))  
        self.fe.add(MaxPooling2D(pool_size = 2, strides = 2))
        self.fe.add(Conv2D(filters = 32, kernel_size = 5, padding = 'same', activation = 'relu'))        
        self.fe.add(MaxPooling2D(pool_size = 2, strides = 2))

        # classifier
        self.classifier = Sequential()
        self.classifier.add(Flatten())
        self.classifier.add(Dense(units = 64, activation = 'relu'))
        self.classifier.add(Dense(units = 10, activation = 'softmax'))

    def call(self, x):
        x = self.fe(x)
        x = self.classifier(x)
        return x
        
        
model = CNN_Model()
model.build(input_shape = (None, 28, 28, 1))
model.summary()
```

```
Model: "cnn__model"
_________________________________________________________________
Layer (type)                 Output Shape              Param #
=================================================================
sequential (Sequential)      (None, 7, 7, 32)          6640
_________________________________________________________________
sequential_1 (Sequential)    (None, 10)                101066
=================================================================
Total params: 107,706
Trainable params: 107,706
Non-trainable params: 0
_________________________________________________________________
```



##### M-Sub + L-Sub + Seq

```python
import tensorflow as tf

from tensorflow.keras.models import Model, Sequential
from tensorflow.keras.layers import Conv2D, MaxPooling2D
from tensorflow.keras.layers import Flatten, Dense
from tensorflow.keras.layers import Layer, Activation

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

class CNN_Model(Model):
    def __init__(self):
        super(CNN_Model, self).__init__()

        # feature extractor
        self.fe = Sequential(name = 'feature_extractor')
        self.fe.add(ConvLayer(8, 3))
        self.fe.add(ConvLayer(16, 3))
        self.fe.add(ConvLayer(32, 3)) 

        # classifier
        self.classifier = Sequential(name = 'classifier')
        self.classifier.add(Flatten())
        self.classifier.add(Dense(units = 64, activation = 'relu'))
        self.classifier.add(Dense(units = 10, activation = 'softmax'))

    def call(self, x):
        x = self.fe(x)

        x = self.classifier(x)
        return x
        
        
model = CNN_Model()
model.build(input_shape = (None, 28, 28, 1))
model.summary()
```



---



Deep Learning process in CNN:

Convolution 과정에서 사용되는 Kerenel에는 W와 B가 있을 것이고, 이를 Learning 시키는 과정이 바로 CNN의 Deep Learning process이다.



Difference between ANN and CNN : 

ANN은 각각의 filter의 weight 위치가 정해져 있기 때문에 tesk image안의 feature가 traning data와는 다른location(구석탱이라던가)에 있다면 이를 인식하지 못한다.

하지만 CNN은 weight의 location이 달라진다 해도 features가 남아있다면 filter sliding을 통해 detection이 가능하다.

또한 ANN은 각 perceptron이 전부 connected 되어있기 때문에 weight, bias가 엄정 많아지지만, CNN은 filter를 사용하기 때문에 Model이 더욱 가볍다





CNN 입문시 읽으면 좋을 논문

A guide to convolution arithmetic for deep learning

Vinsent Dumoulin and Francesco Visin

January 12, 2018

