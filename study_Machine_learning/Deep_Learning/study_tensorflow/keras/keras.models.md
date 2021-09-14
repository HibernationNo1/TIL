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





### Functional API

create Model using `keras.layers` import `Input`

```python
from tensorflow.keras.layers import Input, Flatten, Dense
from tensorflow.keras.models import Model

input_tensor = Input(shape = (INPUT_SIZE_W, INPUT_SIZE_H)) # create instance

x = Flatten()(input_tensor)
x = Dense(units = 10, activation = 'sigmoid')(x)
output = Dense(units = 20, activation = 'sigmoid')(x)

model = Model(inputs = input_tensor, outputs = output)
```



```python
class Softmax(Model):
	def __init__(self, cell_size, num_classes):
		super(Softmax, self).__init__()
		input_tensor = Input(shape = (cell_size, cell_size, num_classes))
		pred_P = Flatten()(input_tensor)
		output = Dense(cell_size * cell_size * num_classes , activation = 'softmax')(pred_P)

		model = Model(inputs = input_tensor, outputs=output)
		self.model = model
		# print model structure
		self.model.summary()

	def call(self, pred_P):
		return self.model(pred_P)
```



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

 

#### input, output

model instance의 input, output을 반환

```python
model = KM.Model(input = [input_image, input_image_meta, input_anchors],
							 output = [detections, mrcnn_class, mrcnn_bbox,
									   mrcnn_mask, rpn_rois, rpn_class, rpn_bbox],
									   name='mask_rcnn')

input_list = model.input  	# [input_image, input_image_meta, input_anchors]
output_list = model.output	# [detections, mrcnn_class, mrcnn_bbox, mrcnn_mask, rpn_rois, rpn_class, rpn_bbox]
```





#### losses

`version = 2.0`

model instance에 list타입의 loss저장용 attribute

- 접근 방법

  ```python
  if 100 in model.losses
  ```

  

#### add_loss()

`version = 2.0`

model instance의 losses에 loss값을 더할때 사용

```python
value_loss = 100
model.add_loss(value_loss)
```







#### metrics_names

`version = 2.0`

스칼라 아웃풋에 대한 name을 반환. initial은 [] (비어있음)

metrics의 name을 담아두는 container 용도로 사용함

```python
loss_names = ["rpn_class_loss",  "rpn_bbox_loss",
			  "mrcnn_class_loss", "mrcnn_bbox_loss", "mrcnn_mask_loss"]

print(model.metrics_names) 	# []   initial
for name in loss_names:
	model.metrics_names.append(name)
```



#### add_metric

`version = 2.0`

model instance의 metrics에 metric값을 더할때 사용

```python
model.add_metric(loss, name=name, aggregation='mean')
```





#### metrics_tensors

`version = 2.0`

스칼라 아웃풋에 대한 tensor type의 값을 반환

scalar value를 담아두는 container 용도로 사용함

```python
model.metrics_tensors = []	# initial 선언 해 주어야 함
model.metrics_tensors.append(loss_value)
```









#### layers

Model Object에서 .layers를 통해 각각의 dense에 접근할 수 있다.

```python
model.layers[0]  # dense1 에 접근

w, b = model.layers[0].get_weights() # 이런것도 가능
```

> model.layers는 list형태로 Dense가 저장되있음을 알 수 있다.





```python
layers = model.layers
```

layers = model안에 있는 모든 layer에 접근





##### name

```python
layers = model.layers
for layer in layers:
	print(layer.name)
```

각 layer에 `name = ` 의 prameter로 이름이 지어져 있다면, 해당 이름을 return



##### \_\_class\_\_.\_\_name\_\_

```python
layers = model.layers
for layer in layers:
	print(layer.__class__.__name__)
```

각 layer의 명칭을 return

e.g. `onv2D`, `BatchNormalization`, `Activation`



##### weights

```python
layers = model.layers
for layer in layers:
    layer.weights
```

layer의 wights를 list로 반환



##### trainable

```python
layers = model.layers
for layer in layers:
    layer.trainable = True
```

`True`이면 학습 대상 layer (Conv2같은거)

`False`이면 학습 대상이 아님 

defualt는 `False`



##### layer

TimeDistributed으로 layer안에 하위 layer을 포함한 경우라면 `layer.layer`으로 접근할 수 있다.

```python
layers = model.layers
for layer in layers:
    layer.layer
```





##### output

```python
layers = model.layers
for layer in layers:
    output = layer.output
```

해당 layer의 반환값을 반환



예를 들어, rpn_class_loss라는 이름의 layer의 output을 받으면, rpn_class_loss값을 받는 것이다.

```python
rpn_class_loss = KL.Lambda(lambda x: rpn_class_loss_graph(*x),
									name="rpn_class_loss")([input_rpn_match, rpn_class_logits])
```





#### get_layer

model에서 특정 이름의 layer을 반환한다.

```python
name = rpn_class_loss
layer = model.get_layer(name)
```

`name = ` 의 prameter로 이름이 붙여진 layer만 가능







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



#### trainable_weights

model로부터 훈련 가능한 weight만 반환한다.

```python
for w in model.trainable_weights
```

`w.name` = `gamma` ,  `beta` 등의 이름이 있음



#### build()

add를 통해 쌓인 Dense를 기반으로 실질적인 Model을 만드는 함수

```python
model.build(input_shape = )
```

`input_shape`: 입력되는 data의 shape



ex)

```python
class Test_Model(Model):
    def __init__(self):
        super(CNN_Model, self).__init__()
		pass

    def call(self, x_data):
        pass
        
model = Test_Model()
model.build(input_shape = (None, 28, 28, 1))
model.summary()
```





#### summary()

model의 information을 보여주는 함수

```python
model.build(input_shape = (None, 28, 28, 1))
model.summary()
```

> model이 build 된 이후에 call



#### compiled()

model의 learning process를 설정한다.

```python
model.compile(loss, optimizer, metrics)
```

> `loss` 사용할 loss function을 결정한다
>
> ```python
> from tensorflow.keras.losses import CategoricalCrossentropy
> loss_object = CategoricalCrossentropy()
> ```
>
> `optimizer` 사용할 optimizer를 결정한다.
>
> ```python
> from tensorflow.keras.optimizers import SGD
> optimizer_object = SGD(lr = 0.01)
> ```
>
> `metrics` 사용할 accuracy를 결정한다.
>
> ```python
> from tensorflow.keras.metrics import Mean
> accuracy_object = Mean()
> ```

```python
from tensorflow.keras.losses import CategoricalCrossentropy
from tensorflow.keras.optimizers import SGD
from tensorflow.keras.metrics import Mean

loss_object = CategoricalCrossentropy()
optimizer_object = SGD(lr = 0.01)
accuracy_object = Mean()

model.compile(loss = loss_object,
              optimizer = optimizer_object, 
              metrics = accuracy_object)
```





#### fit()

data를 통해 mode을 learning시키는 함수

```python
loss_accs = model.fit(train_image, train_label, epochs=, batch_size=, verbose = None)
```

- `loss_accs` : loss와 accuracy의 history를 epoch마다 기록, save한다.

- `epochs`

- `batch_size`

- `verbose = ` 1 을 설정해놓으면  학습의 진행 상황을 보여준다.

  > callback 객체에서 verbose 설정해놨다면 None으로 해도 ㄱㅊ

- `validation_data =(val_image, val_label) ` validation data set을 input하고 싶을 때 설정.

  tuple로 argument를 넣어준다.

  loss_accs에도 val_loss와 val_accs를 기록, save한다.
  
- `shuffle` default  = True

- `callback = []`

  fit()을 사용하면 iteration을 반복하기 때문에 중간에 hyperparameters 변경(Learning rate)등의 작업에 어려움이 있다.
  이를 위해 iteration 순간 여러 작업을 하기 위해 **Callback** 객체를 가진다.

```python
loss_acc = model.fit(x = train_iamges, y = train_oh_labels, batch_szie = 128, epoch = 10, validation_data = (val_images, val_oh_labels), callbacks = [mcp_cb])
```

> 여러개 callback instance를 list 형태로 동시에 적용 가능





- 일반적으로 fit() 수행시 별도의 validation data set를 이용해서 Overtiffing이 발생하는지 확인한다. 



##### history

`loss_accs`에 저장된 loss와 accuracy에 acess할 수 있다.

```python
print(loss_accs.history['loss'])
print(loss_accs.history['accuracy'])
```



#### fit_generator()

data를 통해 mode을 learning시키는 함수. 단, batch_size를 개발자가 generator로 생성해서 사용한다면 `fit()`대신 `fit_generator()`를 사용해야 한다.

**fit_generator()의 기능은 이제 fit()에서 전부 지원되며, fit_generator()는 사라질 예정**

단, 아직 generator를 인수로 받는 fit()에 대한 정보가 없음

```python
model.fit_generator(
    train_generator,
    validation_data,
    validation_steps,
    epochs,
    steps_per_epoch,
    initial_epoch, 
    )
```

`train_generator` : training을 위한 generator function

`validation_data` : validation을 진행할 generator function

`validation_steps` : validation을 수행할  특정 step

`epochs` : 진행할 epoch 숫자

`steps_per_epoch` : 1epoch에 사용할 step 수

`callbacks` : callback class를 담은 list 

> e.g. 
>
> ```python
> import tensorflow.keras.callbacks as KC
> callbacks = [KC.TensorBoard(log_dir = self.log_dir,
> 					histogram_freq=0, write_graph=True, write_images=False),
> 			KC.ModelCheckpoint(self.checkpoint_path,
> 					verbose=0, save_weights_only=True)]
> ```
>
> 

`initial_epoch` : 시작 epoch 숫자(이전 학습에 이어서 진행할 때)

`max_queue_size` : generator queue의 최대 크기  default = 10

> sample을 precache하는데 사용되는 내부 훈련 대기열의 최대 크기

`workers` : threading 기반의 처리 과정을 사용하는 경우(multiprocessing를 사용하는 경우) 사용할 thread의 개수

> default = 1
>
> `workers = 0`인 경우 : generator를 메인 스레드에서 실행합니다.

`use_multiprocessing` : boolean, 

> `use_multiprocessing = True` threading 기반 학습을 진행할 때 사용
>
> `use_multiprocessing = False`  default



#### predict()

학습된 model에 test data를 input해서 label 값을 prediction

```python
pred_proba = model.predict(test_data)
print(pred_proba[0]) # test_iamge 중 0번째 index에 대한 각 classicication 결과값을 0~1 사이로 반환한다.
```

> - training data for learning의 category가 10개였다면,  test_images 또한 10개의 categorical data이어야 한다.
>
> - training data의 dimension과 `test_images`의 dimesion이 같아야 함
>
>   gaty scale image가 layer을 통과할땐 3차원으로 자동 converted 때문에 
>
>   `np.expand_dims(test_images, axis = 0)` 를 통해 iamge의 metirx를 3 dimension으로 conversion 해야한다.

```python
print(np.argmax(pred_proba[0]))
```





#### evaluate()

validtion of model performance

```python
result = model.evaluate( input1, input2, batch_size = )
```

- `input1` : images

- `input2` : labels 

  > if your model learning using CCE, input2 have to applid One-hot encoding

```py
print(result)
```



#### save()

method for save model

```python
model.save(path)
```

no need file name. 

file named 'saved_model.pb' automatically



###### load_model()

method for load file when you want load 'saved_model.pd'

```python
from tensorflow.keras.models import load_model
model = load_model(path)
model.summary()
```

- `path` no need file name. just 'path' where saved_model.pd exist



simple ver

```python
model = tf.keras.models.load_model(path)
```



