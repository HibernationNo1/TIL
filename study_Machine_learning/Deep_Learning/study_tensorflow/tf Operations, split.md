## tf.reduce

텐서를 연산하는 함수

```python
import tensorflow as tf

t1 = tf.random.normal(shape = (3, 4))

t1 = tf.cast(t1, dtype = tf.int16)
```

- `reduce_sum` : 텐서의 차원을 가로지르는 원소의 합을 반환

  ```python
  res = tf.reduce_sum(t1)
  print(res)
  ```

- `reduce_prod`: 텐서의 차원을 가로지르는 원소의 곱을 반환

- `reduce_max`: 텐서의 차원에서 요소의 최대 값을 반환

  ```python
  tf.reduce_max(input_tensor, axis = None, keepdims = False)
  ```

  - `keepdims` : If true, retains reduced dimensions with length 1.

    > 결정된 axis 외의 dimension은 그대로 냅둠

- `reduce_min`: 텐서의 차원에서 요소의 최소 값을 반환

- `reduce_mean `: 텐서의 차원에서 요소의 평균 값을 반환

- `reduce_std` : 텐서의 차원에서 요소의 표준편자를 반환

- `reduce_variance` : 텐서의 차원에서 요소의 분산을 반환

[여러 계산 함수](https://m.blog.naver.com/PostView.nhn?blogId=stop2y&logNo=221526715840&proxyReferer=https:%2F%2Fwww.google.com%2F)





## tf.math

#### tf.minimun()

```python
tf.minimun(x, y)
```

tf.math.min() 과 같다



#### tf.maximum()

```python
tf.maximum(x, y)
```

tf.math.max() 와 같다



#### tf.equal()

argument로 받아온 두 값이 같으면 True, 다르면 False 반환

```python
tmp = tf.equal(a, b)
```

> a, b가 matrix면 element wise로 compute



#### tf.not_equal()

argument로 받아온 두 값이 다르면 True, 같으면 False 반환

```python
tmp = tf.not_equal(a, b)
```

> a, b가 matrix면 element wise로 compute



#### tf.greater()

argument로 받아온 두 x, y값 중 (x>y)가 만족하면 True값을 return

```python
tmp = tf.greater(x, y)
```





### confusion_matrix()

분류 모델 성능 평가 지표

> 자세한 설명은 [여기](https://leedakyeong.tistory.com/entry/%EB%B6%84%EB%A5%98-%EB%AA%A8%EB%8D%B8-%EC%84%B1%EB%8A%A5-%ED%8F%89%EA%B0%80-%EC%A7%80%ED%91%9C-Confusion-Matrix%EB%9E%80-%EC%A0%95%ED%99%95%EB%8F%84Accuracy-%EC%A0%95%EB%B0%80%EB%8F%84Precision-%EC%9E%AC%ED%98%84%EB%8F%84Recall-F1-Score)

```python
tf.math.confusion_matrix(labels, predictions)
```

- labels, predictions 각각의 shape은 같아야 한다.

- confusion_matrix()은 (2, 2) shape의 matrix이다.

- columns는 prediction labels를 나타내고, row는 real labels를 나타낸다.

- ex)

  ```
   tf.math.confusion_matrix([1, 2, 4], [2, 2, 4]) ==>
        [[0 0 0 0 0]
         [0 0 1 0 0]
         [0 0 1 0 0]
         [0 0 0 0 0]
         [0 0 0 0 1]]
  ```

  먼저 size = (4, 4) 의 metrix가 만들어진 다음

  index[1, 2], index[2, 2], index[4, 4] 자리에 1이, 나머지는 0이 채워진다.



## tf.split

method for split data

```python
object = tf.split(input_data, num_or_size_spits = , axis = )
```

- `num_or_size_spits` if gaven integers, split equally

  if gaven list, split by elements

ex)

```python
input_data = tf.Variable(tf.random.uniform([5, 30], -1, 1))
object1, object2, object3 = tf.split(input_data, num_or_size_spits = 3, axis = 1)
# object1.shape == object2.shape == object3.shape == (5, 10)

object1, object2 = tf.split(input_data, num_or_size_spits = [2, 3], axis = 0)
# object1.shape == (2, 30)
# object2.shape == (3, 30)
```









## others

#### tf.squeeze()

numpy.squeeze와 동일



#### tf.argmax()

argument의 최대값을 반환한다.

```python
tf.argmax(predictions, axis = 1)
```

> predictions 이라는 dnarray의 각 column에서 가장 큰 값들만 추려서 반환





#### tf.nn.l2_loss()

```python
tmp = tf.nn.l2_loss(
    t, name=None
)
```

- `tmp` : sum(t ** 2) / 2
- `t` : Tensor,  Must be one of the following types: `half`, `bfloat16`, `float32`, `float64`.

