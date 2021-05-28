# keras.applications 

[about applications](https://www.tensorflow.org/api_docs/python/tf/keras/applications) 

It has standard CNN model implementations



### InceptionV3

https://www.tensorflow.org/api_docs/python/tf/keras/applications/InceptionV3

InceptionV3 means GoogLeNet ver.3

```python
import tensorflow as tf
from tensorflow.keras.applications import InceptionV3

model = InceptionV3(include_top = False, weights = 'imagenet', 
                   input_shape = (input_height, input_width, 3))
```

- `include_top` = False or True

  - False : 전체 model에서 마지막 softmax linear regression은 제외

    GoogLeNet 모델 중 feature extractor부분만 가져오겠단 의미

- `weights = 'imagenet'`  : pre-training 된 model의 parameter를 가져오겠다

- `input_shape` input image의 shape 결정 



#### model.trainable

```python
model.trainable = True
```

training을 할 때 가져온 model안의 weight와 bais까지 학습시키겠단 의미

(뒤에 어떤 model을 붙여도 성능은 좋아지지만 training 시간은 오래걸림)

`False`을 하면 시간은 짧아도 성능은 떨어짐