# Non Maximum Suppression

object detection에서는 하나의 instance에 하나의 bounding box가 적용되어야 하는데, 여러 개의 Bbox가 표현되었을 때 1개의 Bbox만을 표현할 수 있도록 하는 방법이 바로 Non Maximum Suppression이다.

Non Maximum Suppression는 IOU가 threshold 이상의 score를 가진 다수의 bounding box중 가장 대표성을 띄는 bounding box만 표현하는 방법이다.



#### 동작 과정

1. confidence 가 0.6 낮은 bounding box를 제거한다
2. class별로 confidence가 가장 높은 bounding box가 앞으로 오도록 전체 bounding box를 내림차순 정렬한다.
3. 가장 confidence가 높은 bounding box와 나머지 bounding bax를 비교해서 2개의 bounding box의 IoU 가 0.5보다 크다면 confidence가 가장 높은 bounding box를 제거한다
4. 제거되지 않는 bounding box 중에서 confidence가 가장 높은 bounding box와 나머지 bounding box간에 3번 과정을 반복한다.
5. 3~ 4번 과정을 전체 bounding box에 대해서 진행한다.
6. 2~5번 과정을 전체 class에 대해서 진행한다.

> 3~4번 과정이 non-*maximum* suppression algorithm이다



##### tf.image.non_max_suppression

```python
selected_indices = tf.image.non_max_suppression(
    boxes, scores, max_output_size, iou_threshold=0.5,
    score_threshold=float('-inf'), name=None
	)
```

- `boxes` : [y1, x1, y2, x2]
- `scores` : probaility
- `max_output_size` :
- `iou_threshold`  : 
- `score_threshold` : 

- `selected_indices` : A 1-D integer `Tensor` of shape `[M]` , return value is indices

  >  `M <= max_output_size`.