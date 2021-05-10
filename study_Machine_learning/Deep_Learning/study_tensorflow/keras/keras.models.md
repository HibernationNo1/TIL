# keras.models

### Sequential()

```python
from tensorflow.keras.models import Sequential
```

Dense Layer이 몇개든 Model 안에 포함되게 만드는 함수

model이라는 박스 안에 각각의 Dense Layers를 차례로 connection해주는 함수이다.

```python
from tensorflow.keras.layers import Dense

from tensorflow.keras.models import Sequential

X = tf.random.normal(shape = (4, 10))

model = Sequential()
model.add(Dense(units = 10, activation = 'sigmoid'))
model.add(Dense(units = 20, activation = 'sigmoid'))

Y = model(X)
```

위의 list를 사용한 다수 Dense layer 형성과 같은 구조이지만, 이렇게 사용하도록 하자. 



#### add()

Dense를 추가하는 함수



#### build()

add를 통해 쌓인 Dense를 기반으로 실질적인 Model을 만드는 함수

```python
model = Sequential()
model.add
..
..

model.build(input_shape = (, ))
```

- `input_shape`: 입력되는 image의 shape



#### summary()

model의 information을 보여주는 함수



---



### Model

```python
from tensorflow.keras.models import Model
```



tensorflow를 활용한 모델 class 생성

```python
from tensorflow.keras.layer import Dense

from tensorflow.keras.models import Model

X = tf.random.normal(shape = (4, 10))

class TestModel(Model):						# 여기서부터
    def __init__(self):
        super(TestModel, self).__init__()  	# 여기까지 고정, 외우자
    
    	self.dense1 = Dense(units = 10, activation ' sigmoid')
    	self.dense2 = Dense(units = 20, activation ' sigmoid')
    
    def call(self, x):  # 이 부분을 내 입맛에 맞게 설정하면 Dense Layers의 connection 순서를 자유롭게 결정할 수 있다.
        x = self.dense1(x)
        x = self.demse2(x)
        return x
    
model = TestModel() 	# Dense Layer이 2개가 있는 Model 생성
Y = model(X)			# call 함수 자동 호출
```

> 위의 Sequential()을 알고, Model class 사용 방법을 알았으면, class로 Model을 만드는 방법을 사용하자.

 

#### layers

Model Object에서 .layers를 통해 각각의 dense에 접근할 수 있다.

```python
model.layers[0]  # dense1 에 접근

w, b = model.layers[0].get_weights() # 이런것도 가능
```

> model.layers는 list형태로 Dense가 저장되있음을 알 수 있다.







#### trainable_variables

Model Object에서 .trainable_variables를 통해 weight, bias 등등의 학습에 필요한 정보들에 접근할 수 있다.

```python
model.trainable_variables
# (weight, bias, ...)
```

> model.trainable_variables역시 list의 형태로 각각의 정보가 들어있다.



`Sequential()`과 `class: Model`의 차이점은 forward propagation에 있다.

- Sequential(): model이라는 박스 안에 각각의 Dense Layers를 차례로 connection한다.
- class: Model : model이라는 박스 안에 각각의 Dense Layers의 connection 순서를 내 마음대로 설정할 수 있다.



#### build()

add를 통해 쌓인 Dense를 기반으로 실질적인 Model을 만드는 함수

```python
class Test_Model(Model):
    def __init__(self):
        super(CNN_Model, self).__init__()
		pass

    def call(self, x):
        pass
        
model = Test_Model()
model.build(input_shape = (None, 28, 28, 1))
model.summary()
```

- `input_shape`: 입력되는 image의 shape



#### summary()

model의 information을 보여주는 함수



### Hybrid

**Model + Sequential**

ex)

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

