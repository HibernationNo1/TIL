# dataset

- 사용된 data set : **PASCAL VOC 2007, 2012**

  Reference : https://stackoverflow.com/questions/54567986/python-numpy-remove-empty-zeroes-border-of-3d-array



Code

```python
import tensorflow as tf
import numpy as np

def bounds_per_dimension(ndarray):
	return map(
    	lambda e: range(e.min(), e.max() + 1),
    	np.where(ndarray != 0)
  	)
# 받아온 ndarray(image)에서 0인 부분(zero padding)을 전부 제거
# zero padding이 있는 이유: batch_size로 받아오기 때문에, 작은 size의 image는 dims에 맞게 묶기기 위해서 (zero padding)으로 감싸져서 batch에 묶이게 된다.


def zero_trim_ndarray(ndarray):
	return ndarray[np.ix_(*bounds_per_dimension(ndarray))]


# process ground-truth data for YOLO format
def process_each_ground_truth(original_image, # resizing 하기 전 image
                              bbox, # 전체 bounding box
                              # (max_object_num_in_batch, 4) = [max_object_num_in_batch, [ymin / height, xmin / width, ymax / height, xmax / width]]
                              # image 기준 normalize 상대좌표. x좌표 처음과 끝, y좌표 처음과 끝
                              class_labels,
                              # one-hot encoding 되지 않은 class labels
                              input_width,   # input으로 들어가는 image의 width
                              # image resizing에 사용됨
                              input_height
                              ):

        
    image = original_image.numpy()
    image = zero_trim_ndarray(image)
    # image에 rero padding 제거

    # set original width height
    original_w = image.shape[1] # original image의 width
    original_h = image.shape[0] # original image의 height

    width_rate = input_width * 1.0 / original_w 
    # (input으로 들어가는 image의 width == 448)/ original image의 width
    height_rate = input_height * 1.0 / original_h

    image = tf.image.resize(image, [input_height, input_width])
        # YOLO input size로 image resizing

    object_num = np.count_nonzero(bbox, axis=0)[0]
    # 전체 bounding box에서 object가 있는 box의 개수 (즉, object 개수)
    # zero element가 있는 이유 : batch_size로 받아오기 때문에, 어떤 image는 object가 3개이고, 다른 image에서는 object가 1개일 때 [1 1 1], [1 0 0] 이런 식으로 dimension을 맞추기 위해 zero가 있게 된다. 이를 빼주기 위해 count_nonzero 을 하는 것
    labels = [[0, 0, 0, 0, 0]] * object_num
    # labels 의 그릇 = object 개수 * 5가지 요소(x, y, w, h, class num) 이기 때문에
    # labels 의 그릇 element를 0으로 initialize
    for i in range(object_num):
        # 각각의 object의 coordinate를 image기준의 상대좌표에서 image기준의 절대좌표로 변경 
        xmin = bbox[i][1] * original_w
        ymin = bbox[i][0] * original_h
        xmax = bbox[i][3] * original_w
        ymax = bbox[i][2] * original_h

        class_num = class_labels[i] # 실제 class labels

        # PASCAL VOC 의 labels coordinate는 image의 꼭지점 좌표로 표현되어 있다. 
        # 하지만 YOLO model은 bounding box의 중앙 coordinate로 표현하기 때문에
        # 이를 위해 x, y의 center coordinate를 계산
        xcenter = (xmin + xmax) * 1.0 / 2 * width_rate 
        ycenter = (ymin + ymax) * 1.0 / 2 * height_rate

        # bounding box의 width, height 
        box_w = (xmax - xmin) * width_rate
        box_h = (ymax - ymin) * height_rate
		
        # YOLO format형태의 5가지 labels 완성
        labels[i] = [xcenter, ycenter, box_w, box_h, class_num]

    return [image.numpy(), labels, object_num]
```

