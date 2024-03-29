# Anchor box

anchor box는 원본 image의 각 grid cell의 중심을 기준으로 생성하고, 각각의 비율에 대해 각각의 scale을 적용하여 정의한다.



**Delta**
기본 Anchor의 크기와 위치를 조정하기 위한 값으로, model을 통해 학습되는 parameter이다.

즉, object에 대한 (y, x, h, w)이다.

Anchor하나에 Delta가 하나씩 대응되며, Delta하나의 값의 구성은 (deltaCenterY, deltaCenterX, deltaHeight, deltaWidth)형식의 구조를 갖는다.



Probability

각 Anchor 내부에 객체가 존재할 확률이다.



### Generate Anchors

`anchor_scales`: feature map에서의 anchor의 size

`anchor_ratios` : feature map에서의 anchor의 ratio

> anchor_ratios = [0.5, 1, 2] 이면 ratio는 `1:0.5`, `1:1`, `1:2`

`feature_strides` :  image를 기준으로 어느 정도 간격으로 Anchor를 생성할 것인지 나타내는 값

> 주로 image와 feature map의 크기의 비율(sub sampling ratio)값을 사용

`anchor_stride` : anchor가 이동하는 간격 (feature map기준)

- feature map에서의 Anchor_base_size를 결정하는 요인 == scale, ratio
- feature map의 size는 image의 w, h를 stride로 나눈 값이기 때문에, 이 것이 반영된 원본 image에서 Anchor의 크기는 Anchor_base_size + stride 이다.

>예시 ::
>
>Fast R-CNN에서는 3개의 스케일[128, 256, 512]과 3개의 비율[1:1, 1:2, 2:1]을 사용하여 k=9개의 앵커를 사용하였다.
>
>![](https://media.vlpt.us/images/suminwooo/post/49fa1d5a-d59c-4272-b43d-4af416134bf3/image.png)
>
>원본 image의 크기가 600×800이고, sub-sampling ratio = 1/16일 때
>
>CNN에 의한 feature map은 38×50이다. (38, 50가 곧 stride)
>
>그렇기에 Fast R-CNN에서는 각 cell마다 9개의 anchor box를 만들었다. (총 개수 17100 = 38×50×9 ) 



**Mask R-CNN에서의 `generate_pyramid_anchors`**

```python
anchor_scales = [32, 64, 128, 256, 512]  			# config
anchor_ratios = [0.5, 1, 2]							# config

feature_strides = [4, 8, 16, 32, 64] 				# config
# subsampled_ratio
# feature map = [256, 128, 64, 32, 16]

anchor_stride = 1									# config

feature_shapes = [[256 256], [128, 128], [64,  64], [32,  32], [16,  16]]
# backbone_shapes from `compute_backbone_shapes`

def generate_anchors(anchor_scale, anchor_ratios, feature_shape, feature_stride, anchor_stride):
  	
    # anchor_scale * anchor_ratio의 모든 경우의 수 도출
	anchor_scale, anchor_ratios = np.meshgrid(np.array(anchor_scale), np.array(anchor_ratios))
    anchor_scale = anchor_scale.flatten()  	# [anchor_scale, anchor_scale, anchor_scale]
    anchor_ratios = anchor_ratios.flatten() # [0.5, 1, 2] == anchor_ratio
    
    # anchor의 ratio에 따른 각각의 w, h
    widths = anchor_scale * np.sqrt(anchor_ratios)
    heights = anchor_scale / np.sqrt(anchor_ratios)
    
    # anchor가 image위에서 sliding하는 x, y범위
    shifts_y = np.arange(0, feature_shape[0], anchor_stride) * feature_stride
    shifts_x = np.arange(0, feature_shape[1], anchor_stride) * feature_stride
    shifts_x, shifts_y = np.meshgrid(shifts_x, shifts_y)
	
    # 각 pixel 위치에서의 x, y, w, h
    box_widths, box_centers_x = np.meshgrid(widths, shifts_x)
    box_heights, box_centers_y = np.meshgrid(heights, shifts_y)
    
    # Reshape to get a list of (y, x) and a list of (h, w)
    box_y_x_centers = np.stack([box_centers_y, box_centers_x], axis=2).reshape([-1, 2])
    box_h_w = np.stack([box_heights, box_widths], axis=2).reshape([-1, 2])
    # feature_strides = 32 기준 box_y_x_centers.shape == box_h_w.shape : (196608, 2)

    # Convert to corner coordinates (y1, x1, y2, x2)
    anchor_boxes = np.concatenate([box_centers - 0.5 * box_sizes,
                            	   box_centers + 0.5 * box_sizes], axis=1)
    return anchor_boxes

def generate_pyramid_anchors(anchor_scales, anchor_ratio, feature_shape, feature_strides, anchor_stride):
    anchors = list()
    for i in range(len(anchor_scale)):
        anchor_boxes = generate_anchors(anchor_scales[i], anchor_ratio, feature_shapes[i],
                                        feature_strides[i], anchor_stride)
        anchors.append(boxes)
        
        return np.concatenate(anchors, axis=0)
```





### Set positive/negative anchor

foreground anchor는 1로 (iou가 0.7보다 클 때)

background anchor는 -1로  (iou가 0.3보다 작을 때)

사용하지 않을 anchor는 0으로 만들어 분류한다.

```python
RPN_TRAIN_ANCHORS_PER_IMAGE = 256
# How many anchors per image to use for RPN training

def Set_p_n_anchor(anchors, gt_boxes):
	"""
	anchors: [anchor_count, (y1, x1, y2, x2)]
	gt_boxes : [instance_count, (y1, x1, y2, x2)]
	"""
	
    # RPN Match: 1 = positive anchor, -1 = negative anchor, 0 = neutral
    # [anchor_count]
    rpn_match = np.zeros([anchors.shape[0]], dtype=np.int32)
    
    # RPN bounding boxes: [max anchors per image, (dy, dx, log(dh), log(dw))]
    rpn_bbox = np.zeros((RPN_TRAIN_ANCHORS_PER_IMAGE, 4))
    
    # Compute overlaps [num_anchors,  num_IOU]  num_IOU == num_gt_boxes
    overlaps = compute_overlaps(anchors, gt_boxes)

    # Match anchors to GT Boxes
    # If an anchor overlaps a GT box with IoU >= 0.7 then it's positive.
    # If an anchor overlaps a GT box with IoU < 0.3 then it's negative.
    # Neutral anchors don't influence the loss function.
    ## However, don't keep any GT box unmatched (rare, but happens).
    # Instead, match it to the closest anchor (even if its max IoU is < 0.3).
    #
    # 1. Set negative anchors first. 
    # They get overwritten below if a GT box is matched to them.
    # anchor방향으로 slicing
    anchor_iou_argmax = np.argmax(overlaps, axis=1)
    anchor_iou_max = overlaps[np.arange(overlaps.shape[0]), anchor_iou_argmax]
    rpn_match[(anchor_iou_max < 0.3)] = -1
    
    # 2. Set an anchor for each GT box (regardless of IoU value).
    # If multiple anchors have the same IoU match all of them
    # np.max(overlaps, axis=0) : [num_anchors], 
    # gt_iou_argmax : where about max iou anchor in from each gt_boxes
    # gt_boxes 방향으로 slicing
    gt_iou_argmax = np.argwhere(overlaps == np.max(overlaps, axis=0))[:,0]
    rpn_match[gt_iou_argmax] = 1
    
    # 3. Set anchors with high overlap as positive.
    rpn_match[anchor_iou_max >= 0.7] = 1
    # 예시 anchor_count = 4, instance_count = 2
    # [[0.1  0.8]			# max > 0.7
 	# [0.2  0.5]        	# 3 < max < 0.7
 	# [0.25 0.9 ]			# max > 0.7
 	# [0.1  0.2]]			# max < 0.3		
    # rpn_match : [ 1  0  1 -1]    
```



#### compute_overlaps

```python
def compute_overlaps(anchors, gt_boxes):
    """
	Computes IoU overlaps between two sets of boxes.
	anchors : [anchor_count, (y1, x1, y2, x2)]
	gt_boxes : [instance_count, (y1, x1, y2, x2)]
	
	Return [anchor_count, number of IOU equal to instance_count]
		overlaps: 
	"""
    boxes1, boxes2 =  anchors, gt_boxes
    
    
    area1 = (boxes1[:, 2] - boxes1[:, 0]) * (boxes1[:, 3] - boxes1[:, 1])
    area2 = (boxes2[:, 2] - boxes2[:, 0]) * (boxes2[:, 3] - boxes2[:, 1])
    
    # Compute overlaps to generate matrix [boxes1 count, boxes2 count]
    # Each cell contains the IoU value.
    overlaps = np.zeros((boxes1.shape[0], boxes2.shape[0])) 
    for i in range(overlaps.shape[1]):	# instance_count
        box2 = boxes2[i]				# (y1, x1, y2, x2)
        overlaps[:, i] = compute_iou(box2, boxes1, area2[i], area1)
    return overlaps	
```





### Anchor subsample

positive/negative anchor 비율을 1:1로 맟춘다.

```python
RPN_TRAIN_ANCHORS_PER_IMAGE = 256
# How many anchors per image to use for RPN training


def subsample_anchor(rpn_match):
    """
    rpn_match.shape : [anchor_count] 
    1 = positive anchor, -1 = negative anchor, 0 = neutral
    ex) anchor_count = 4, rpn_match : [1  0  1 -1] 
    """
    
    # Subsample to balance positive and negative anchors
    # Don't let positives be more than half the anchors
    # positive : negative == 1 : 1
    ids = np.where(rpn_match == 1)[0]
    extra = len(ids) - (RPN_TRAIN_ANCHORS_PER_IMAGE // 2)
    if extra > 0: 	 
        # positives anchor중에서 (RPN_TRAIN_ANCHORS_PER_IMAGE // 2) 개를 제외하곤 다 버림
        ids = np.random.choice(ids, extra, replace=Fale)
        rpn_match[ids] = 0
    # Same for negative proposals
    ids = np.where(rpn_match == -1)[0]
    extra = len(ids) - (RPN_TRAIN_ANCHORS_PER_IMAGE -
                        np.sum(rpn_match == 1))
    if extra > 0:
    # negative anchor중에서 (RPN_TRAIN_ANCHORS_PER_IMAGE // 2) 개를 제외하곤 다 버림
        ids = np.random.choice(ids, extra, replace=False)
        rpn_match[ids] = 0
```



### Compute Delta

anchor를 GT_boxes에 대응시키 위한 값인 Delta를 구하기 위해 

positive anchor에 대해서  shift와 scale을 compute한다.



##### Delta

Box_1과 Box_2가 있고, 각각의 left-top, right down의 coordinate가 아래와 같다고 할 때
$$
Box_1 = [y_{B1-1}, x_{B1-1}, y_{B1-2}, x_{B1-2}] \\
Box_2 = [y_{B2-1}, x_{B2-1}, y_{B2-2}, x_{B2-2}]
$$
right, width, y_center, x_center를 계산해서 구했다고 가정해보자.
$$
Box_1(h, w, x, y) = (h_{B1}, w_{B1}, x_{B1}, y_{B1}) \\
Box_2(h, w, x, y) = (h_{B2}, w_{B2}, x_{B2}, y_{B2})
$$


그럼 Box1의 모양을 Box2에 대응시키는 변환값 Delta의 계산법은 아래와 같다



**Delta = (dy, dx, dh, dw)**
$$
dy = \frac{y_{B2} - y_{B1}}{h_{B1}} \\
dx = \frac{x_{B2} - x_{B1}}{w_{B1}} \\
dh = log\frac{h_{B2}}{h_{B1}}\\
dw = log\frac{w_{B2}}{w_{B1}}
$$


```python
def box_refinement_graph(box, gt_box):
    """
    box를 gt_box의 좌표에 맞추도록 하는 변환값(delta)을 계산
    box : [N1, (y1, x1, y2, x2)]
    gt_box : [N2, (y1, x1, y2, x2)]
    """
    
    box = tf.cast(box, tf.float32)
    gt_box = tf.cast(gt_box, tf.float32)
    
    height = box[:, 2] - box[:, 0]
    width = box[:, 3] - box[:, 1]
    center_y = box[:, 0] + 0.5 * height
    center_x = box[:, 1] + 0.5 * width
    
    gt_height = gt_box[:, 2] - gt_box[:, 0]
    gt_width = gt_box[:, 3] - gt_box[:, 1]
    gt_center_y = gt_box[:, 0] + 0.5 * gt_height
    gt_center_x = gt_box[:, 1] + 0.5 * gt_width

    dy = (gt_center_y - center_y) / height
    dx = (gt_center_x - center_x) / width
    dh = tf.log(gt_height / height)
    dw = tf.log(gt_width / width)
    
    result = tf.stack([dy, dx, dh, dw], axis=1)
    return result
```



### Apply Delta to Anchor

위의 Delta를 Box1에 적용시키면 Box1을 Box2에 대응시킨, 새로운 Box1의 left-top, right down의 coordinate를 계산할 수 있다. 

그리고 이 새로운 left-top, right down의 coordinate를 아래처럼 표현한다고 하면
$$
기존 Box_1 = [y_{1}, x_{1}, y_{2}, x_{2}]\\
새로운\ Box_1 = [y_{B1-1}, x_{B1-1}, y_{B1-2}, x_{B1-2}]
$$
각각의 좌표를 구하는 식은 아래와 같다.  

 **Box1에 Delta를 적용해서 새로운 Box1의 좌표를 구함**
$$
y_{B1-1} = y_1 + 0.5(y_2-y_1) + dy*(y_2-y_1) - 0.5e^{dh} \\
x_{B1-1} = x_1 + 0.5(x_2-x_1) + dx*(x_2-x_1) - 0.5e^{dw} \\
y_{B1-2} = y_1 + 0.5e^{dh}\\
x_{B1-2} = x_1 + 0.5e^{dw}
$$


```python
def apply_box_deltas_graph(Anchor, deltas):
    # Anchor: [N, (y1, x1, y2, x2)]
    # deltas: [N, (dy, dx, dh, dw)] refinements to apply
    
    # Convert to y, x, h, w
    height = boxes[:, 2] - boxes[:, 0]
    width = boxes[:, 3] - boxes[:, 1]
    center_y = boxes[:, 0] + 0.5 * height
    center_x = boxes[:, 1] + 0.5 * width
    
    # Apply deltas
    center_y += deltas[:, 0] * height
    center_x += deltas[:, 1] * width
    height *= tf.exp(deltas[:, 2])
    width *= tf.exp(deltas[:, 3])
    
    # Convert back to y1, x1, y2, x2
    y1 = center_y - 0.5 * height
    x1 = center_x - 0.5 * width
    y2 = y1 + height
    x2 = x1 + width
    
    result = tf.stack([y1, x1, y2, x2], axis=1)
    return result
```

