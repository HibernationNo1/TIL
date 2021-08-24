# segmentation_model

**Python library with Neural Networks for Image Segmentation based on and TensorFlow**

[segmentation_model](https://github.com/qubvel/segmentation_models#simple-training-pipeline)



- image segmentation을 위한 4개의 Neural Network model architectures를 담고 있는 libarary로,  keras와 TensorFlow를 기반으로 설계되어 있다.

  > 각 architectures는 25개의 backbone network를 사용하여 활용될 수 있으며
  >
  > backbone network는 pre-trained weight를 가지고 있다.

- IoU-score, F-score과 같은 계산 알고리즘을 담고 있다.

- Jaccard, Dice, Foca 과 같은 loss 계산 알고리즘을 담고 있다.



**install**

```
$ pip install segmentation_models
```



**import**

```python
import segmentation_models as sm
sm.set_framework('tf.keras')
# frame work를 keras에서 tensorflow.keras로 변경
```



#### basic method

- `get_preprocessing()`

  사용할 backbone network에 알맞게 input data를 preprocessing한다.

  ```python
  BACKBONE = 'resnet34'
  preprocess_input = sm.get_preprocessing(BACKBONE)
  input_train = preprocess_input(train_data)
  input_val = preprocess_input(val_data)
  ```

  



#### Included model

```python
import segmentation_models as sm
model1 = sm.Unet()		# from segmentation_models import Unet
model2 = sm.Linknet()	# from segmentation_models import Linknet
model3 = sm.PSPNet()	# from segmentation_models import PSPNet
model4 = sm.FPN()		# from segmentation_models import FPN
```



- **network model instance 생성**

  ```python
  model = sm.Unet('backbone_name', encoder_weights = 'imagenet')
  ```

  imagenet의 data로 학습된 parameters를 가진 model의 instance를 생성한다.

  - `classes` : integer, number of class for classification

  - `activation` : string, activation function. 

    > `classes = 1, activation = 'sigmoid'`
    >
    > `classes = 3, activation = 'softmax'`

  - `input_shape` 

  > 예시 ::
  >
  > ```python
  > model = sm.Unet('resnet34',input_shape = (256, 256, 3), classes = 1, activation = 'sigmoid', encoder_weights='imagenet')
  > ```

  

**Backbones**

| Type         | Names                                                        |
| ------------ | ------------------------------------------------------------ |
| VGG          | `'vgg16' 'vgg19'`                                            |
| ResNet       | `'resnet18' 'resnet34' 'resnet50' 'resnet101' 'resnet152'`   |
| SE-ResNet    | `'seresnet18' 'seresnet34' 'seresnet50' 'seresnet101' 'seresnet152'` |
| ResNeXt      | `'resnext50' 'resnext101'`                                   |
| SE-ResNeXt   | `'seresnext50' 'seresnext101'`                               |
| SENet154     | `'senet154'`                                                 |
| DenseNet     | `'densenet121' 'densenet169' 'densenet201'`                  |
| Inception    | `'inceptionv3' 'inceptionresnetv2'`                          |
| MobileNet    | `'mobilenet' 'mobilenetv2'`                                  |
| EfficientNet | `'efficientnetb0' 'efficientnetb1' 'efficientnetb2' 'efficientnetb3' 'efficientnetb4' 'efficientnetb5' efficientnetb6' efficientnetb7'` |



##### method

- `load_weights(path)`

  path상에 학습된 model이 있다면, 해당 model의 weight를 가져와 사용한다.

  ```python
  path_base_model = os.path.join(os.getcwd() , 'models')
  
  model = sm.Unet('resnet34',input_shape = (256, 256, 3), classes = 1, activation = 'sigmoid', encoder_weights='imagenet')
  
  model.load_weights(path_base_model + 'model_name')
  ```

  



#### Included metrics

```python
import segmentation_models as sm
from segmentation_models.metrics import IOUScore
from segmentation_models.metrics import FScore
```



#### Included loss

```python
import segmentation_models as sm
from segmentation_models.losses import JaccardLoss, DiceLoss
```



