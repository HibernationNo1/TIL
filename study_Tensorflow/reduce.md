# reduce

### 텐서를 연산하는 함수

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
- `reduce_min`: 텐서의 차원에서 요소의 최소 값을 반환
- `reduce_mean `: 텐서의 차원에서 요소의 평균 값을 반환

- `reduce_std` : 텐서의 차원에서 요소의 표준편자를 반환
- `reduce_variance` : 텐서의 차원에서 요소의 분산을 반환



[여러 계산 함수](https://m.blog.naver.com/PostView.nhn?blogId=stop2y&logNo=221526715840&proxyReferer=https:%2F%2Fwww.google.com%2F)



### **axis** 활용

axis 의 숫자는 연산하고 싶은 차원 + 1을 의미한다.

- 덧셈에서(덧셈 외의 연산에도 적용)

  0: 1차원을 더한다. => 1차원을 없앤다. => 1차원 방향으로 더한다.

  1: 2차원을 더한다. => 2차원을 없앤다. => 2차원 방향으로 더한다.

  2: 3차원을 더한다. => 3차원을 없앤다. => 3차원 방향으로 더한다.

```python
t1 = tf.random.normal(shape = (3, 4, 5))  # 1차원 길이(y축) = 3, 2차원 길이(x축) = 4, 3차원 길이(z축) = 5
res1 = tf.reduce_sum(t1, axis = 0) # 1차원 방향으로 더한다.(y축)
res2 = tf.reduce_sum(t1, axis = 1) # 2차원 방향으로 더한다.(x축)
res3 = tf.reduce_sum(t1, axis = 2) # 3차원 방향으로 더한다.(z축)
```

