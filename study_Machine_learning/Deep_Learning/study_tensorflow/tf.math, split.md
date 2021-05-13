# tf.math

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



# tf.split

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





tf.squeeze

numpy와 동일

