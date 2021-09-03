# tf.image



#### crop_and_resize()

boxe의 영역을 crop하고 원하는 size로 resize해서 출력

(image의 channel은 유지)

```python
output = tf.image.crop_and_resize(
    image, boxes, box_indices, crop_size, method='bilinear',
    extrapolation_value=0, name=None
)
```

`image` : 4-D tensor of shape `[batch, image_height, image_width, depth]`

> mask image일 때  `[batch, image_height, image_width]` 넣어도 됨

`boxes` : 2-D tensor of shape `[num_boxes_, (y1, x1, y2, x2)]`

`box_indices` : A 1-D tensor of shape `[num_boxes]`

> num_boxes의 범위 : [0,num_boxes)

`crop_size` : `[croped_image_height, croped_image_width]`

```python
BATCH_SIZE = 1
NUM_BOXES = 5
IMAGE_HEIGHT = 256
IMAGE_WIDTH = 256
CHANNELS = 3
CROP_SIZE = (24, 24)

image = tf.random.normal(shape=(BATCH_SIZE, IMAGE_HEIGHT, IMAGE_WIDTH,
CHANNELS) )
boxes = tf.random.uniform(shape=(NUM_BOXES, 4))
box_indices = tf.random.uniform(shape=(NUM_BOXES,), minval=0,
maxval=BATCH_SIZE, dtype=tf.int32)
output = tf.image.crop_and_resize(image, boxes, box_indices, CROP_SIZE)
output.shape  #=> (5, 24, 24, 3)
```

