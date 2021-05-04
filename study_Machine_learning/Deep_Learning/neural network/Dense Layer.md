# Dense Layer

### Dense Layer

![](https://wikidocs.net/images/page/49071/multilayerperceptron.PNG)

위 그림처럼 Layer 안의 각각 neuran에 이전 Layer의 다수 neuran이 전부 연결되는 형태를 Dense Layer라고 한다. 

##### 1. Dense()

Dense Layer를 생성한다.

`object = Dense(unit = , activation = ' ')`

- `object` : Dense Layer를 저장할 객체

- `unit` : Layer 안에 들어갈 neuron의 갯수

- `activation ` : 각 neuron에 적용할 activation 함수 

> 해당 Dense Layer을 통과할 때는 객체에 input을 넣어줘야 한다.
>
> `output = object(input)`



##### 2. get_weights()

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



### Cascaded Dense Layer

```python
import tensorflow as tf

from tensorflow.keras.layer import Dense

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

from tensorflow.keras.layer import Dense

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



### Model

##### 1. Sequential()

Dense Layer이 몇개든 Model 안에 포함되게 만드는 함수

model이라는 박스 안에 각각의 Dense Layers를 차례로 connection해주는 함수이다.

```python
from tensorflow.keras.layer import Dense

from tensorflow.keras.models import Sequential

X = tf.random.normal(shape = (4, 10))

model = Sequential()
model.add(Dense(units = 10, activation = 'sigmoid'))
model.add(Dense(units = 20, activation = 'sigmoid'))

Y = model(X)
```

위의 list를 사용한 다수 Dense layer 형성과 같은 구조이지만, 이렇게 사용하도록 하자. 







##### 2. class: Model

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

 

###### 1. layers

Model Object에서 .layers를 통해 각각의 dense에 접근할 수 있다.

```python
model.layers[0]  # dense1 에 접근
```

> model.layers는 list형태로 Dense가 저장되있음을 알 수 있다.





###### 2. trainable_variables

Model Object에서 .trainable_variables를 통해 weight, bias 등등의 학습에 필요한 정보들에 접근할 수 있다.

```python
model.trainable_variables
# (weight, bias, ...)
```

> model.trainable_variables역시 list의 형태로 각각의 정보가 들어있다.



`Sequential()`과 `class: Model`의 차이점은 forward propagation에 있다.

- Sequential(): model이라는 박스 안에 각각의 Dense Layers를 차례로 connection한다.
- class: Model : model이라는 박스 안에 각각의 Dense Layers의 connection 순서를 내 마음대로 설정할 수 있다.

