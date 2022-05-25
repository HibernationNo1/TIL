# input dataset



## coco dataset

train dataset은 `images`, `annotations`, `categories` 세 개의 키로 나눈다.

**`images`** : 각각 image의 information (list)

**`images[0]`**

- `file_name`  : str

- `height` : int

- `width` : int

- `id` : int (image_id)



**`annotations`** : 각각 object의 information (list)

**`annotations[0]`**

- `segmentation` : list(float)

  > [[x_1, y_1, x_2, y_2, ...., x_n, y_n]]

- `iscrowd` : int (0 or 1)

- `image_id` : int

- `bbox` : list(float)

  > `[left_top_y, left_top_x, y_value, x_value]`,
  >
  > `(right_bottom_y = left_top_y + y_value, right_bottom_x = left_top_x + x_value)`

- `category_id` : int 

- `id` : int  (conment id, 의미 없음)



**`categories`** : 각각 label의 information (list)

**`categories[0]`**

- `supercategory` : str
- `id` : int (category_id)
- `name` : str



학습은 **`annotations`** 의 `segmentation`과 `bbox`, `object_id`를 통해서 이루어진다.

- `segmentation`과 `bbox`는 **`annotations`**의 `image_id`를 통해 **`images`**로부터 image를 load하여 연산을 진행한다.
- `object_id`는 **`annotations`**의 `category_id`와 `object_id`를 통해 **`categories`**로부터 label값을 load하여 연산을 진행한다.
- 이 때 batch size는 `annotations`에 적용되며, `batch_size == 1`일 때 `iteration == len(annotations)` 인 경우에 전체 이미지의 전체 instance가 한 번씩 학습 연산이 이루어짐을 기대할 수 있다.

