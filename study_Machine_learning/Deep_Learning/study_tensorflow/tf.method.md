## tf.compat.v1

tensorflow version.1의 code를 version.2의 환경으로 가져와서 사용할 때 생기는 오류를 방지하기 위한 모듈

https://www.tensorflow.org/api_docs/python/tf/compat/v1





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





## math

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





#### tf.exp()

```python
tf.exp(2)	# e^2
```





#### confusion_matrix()

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



#### tf.round

반올림 또는 반내림 하는 함수

```py
output = tf.round(input)
```





---





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

#### tf.cast()

```python
x = tf.constant([1.8, 2.2], dtype=tf.float32)
tf.cast(x, tf.int32)			# [1, 2] 
```





#### tf.squeeze()

numpy.squeeze와 동일



#### tf.argmax()

argument의 최대값을 반환한다.

```python
tf.argmax(predictions, axis = 1)
```

> predictions 이라는 dnarray의 각 column에서 가장 큰 값들만 추려서 반환





#### tf.gether()

```python
tf.gather(params, indices, batch_dims=0, name=None)
```

- `params` : input tensor
- `indices` : tensor about indices



```python
params = tf.constant(['p0', 'p1', 'p2', 'p3', 'p4', 'p5'])
indices = [2, 0, 2, 5]
print(tf.gather(params, indices).numpy())
# ['p2', 'p0', 'p2', 'p5']
```



![](https://www.tensorflow.org/images/Gather.png)



#### tf.gether_nd()

다중 dimension의 params에서, indices와 같은 shape으로 output을 뽑아낸다.

```py
tf.gather_nd(params, indices, batch_dims=0, name=None)
```

- `params` : input tensor
- `indices` : tensor about indices



```python
indices = [[1], [0]]
params = [['a', 'b'], ['c', 'd']]
tf.gather_nd(params, indices, batch_dims=0, name=None)
#    output = [['c', 'd'], ['a', 'b']]

indices = [[0, 1], [1, 0]]
params = [[['a0', 'b0'], ['c0', 'd0']],
          [['a1', 'b1'], ['c1', 'd1']]]
tf.gather_nd(params, indices, batch_dims=0, name=None)
#    output = [['c0', 'd0'], ['a1', 'b1']]
```





#### tf.one_hot()

```python
oh_labels = tf.one_hot(labels, 10)
# 10개의 calss로 분할해서 one-hot
```

> class의 종류를 결정 후 분할





#### tf.identity()

```python
output = tf.identity(input)
```

`input` : a tensor



```python
input = 1
output = tf.identity(input)
print(output) # tf.Tensor(1, shape=(), dtype=int32)
```

동작 결과적으로는 output, input이 tensor일 때 output = input과 같이 보일 수 있지만

tensorflow는 edges와 nodes 로 구조화된 graph로 프로그램이 구성되어 있기 때문에, tf.identity는 edges와 nodes를 만드는 과정이라 이해하면 된다.



`tf.control_dependencies()`를  실행시켜주기 위해 자주 사용된다.



#### tf.control_dependencies()

`with`와 함께 쓰이며, “Operation”이 실행되기 전에 inputs으로 들어온 부분을 처리해준다

```python
tf.control_dependencies(control_inputs):
    operation
```

`control_inputs` : list of function or method

`operation` : function or method



ex)

```python
x = tf.Variable(0.0)
x_plus_1 = tf.assign_add(x, 1)
with tf.control_dependencies([x_plus_1]):
    y = tf.identity(x)
```

> 1. `tf.assign_add`로 x + 1의 동작을 가진 function x_plus_1를 선언
>
> 2. `with tf.control_dependencies([x_plus_1]):` 에 의해
>
>    `y = tf.identity(tf.assign_add(x, 1))` 와 같이 된다.



```python
asserts = [
        tf.Assert(tf.greater(tf.shape(proposals)[0], 0), [proposals],
                  name="roi_assertion"),
]
with tf.control_dependencies(asserts):
     proposals = tf.identity(proposals)
```





#### tf.boolean_mask()

```python
output = tf.boolean_mask(input, mask, name)
```

`input` : tensor

`mask` : same shape as input, boolean

`output` : input의 indices중, mask의 같은 indices가 False인 elements가 제거된 tensor

```python
tensor = [0, 1, 2, 3]  # 1-D example
mask = np.array([True, False, True, False])
tf.boolean_mask(tensor, mask)		# [0, 2]
```





#### tf.repeat()

input으로 받은 data를 element wise로 반복한다.

```python
tf.repeat(
    input, repeats, axis=None, name=None
)
```

`input` : An `N`-dimensional Tensor.

`repeats` : An 1-D `int` Tensor.

`axis` : integer, 반복할 axis결정

```python
input = tf.constant([1, 2, 3])
repeats=[1, 2, 3]
tmp = tf.repeat( input, repeats, axis=0, name=None ) # [1 2 2 3 3 3]

input = tf.constant([[1, 2, 3], [4, 5, 6]])
repeats=[1, 3]
tmp = tf.repeat(input, repeats, axis=0, name=None )
# [[1 2 3]
#  [4 5 6]
#  [4 5 6]
#  [4 5 6]]

input = tf.constant([[1, 2, 3], [4, 5, 6]])
repeats=[1, 2, 3]
tmp = tf.repeat(input, repeats, axis=1, name=None)
# [[1 2 2 3 3 3]
#  [4 5 5 6 6 6]]
```



#### tf.tile()

input으로 받은 data를 순서대로 반복한다.

```python
tf.tile(input, multiples, name=None)
```

`input` : An `N`-dimensional Tensor.

`multiples` :

```python
input = tf.constant([1, 2, 3])
repeats= [3]
tmp = tf.repeat( input, repeats, axis=0, name=None )	# [1 1 1 2 2 2 3 3 3]
tmp = tf.tile(input, repeats, name=None)				# [1 2 3 1 2 3 1 2 3]

input = tf.constant([[1, 2, 3], [4, 5, 6]])
repeats=[2]
tmp = tf.repeat(input, repeats, axis=0, name=None )
# [[1 2 3]
#  [1 2 3]
#  [4 5 6]
#  [4 5 6]]
repeats=[2, 1]
tmp = tf.tile(input, repeats, name=None)
# [[1 2 3]
#  [4 5 6]
#  [1 2 3]
#  [4 5 6]]

```



#### tf.cond()

```py
tf.cond(pred, true_fn=None, false_fn=None, name=None)
```

`pred` : 조건, True or False를 return하는 조건이여야 함

`true_fn` : pred가 True일때 동작하는 function

`false_fn` : pred가 False일때 동작하는 function

```python
z = tf.multiply(a, b)
result = tf.cond(x < y, lambda: tf.add(x, z), lambda: tf.square(y))
```



#### tf.transpose()

input의 shape을 바꿔주는 함수 

```py
output = tf.transpose(input, perm=None, conjugate=False, name='transpose')
```

`input` : 

`perm` : list of input.shape

> `perm = None` 인 경우 
>
> - `input.shape = (2, 3)`은 `shape = (3, 2)` 로
> - `input.shape = (4, 2, 3)`은 `shape = (3, 2, 4)` 로 변환
>
> `perm = list` 인 경우 list의 각 element는 가져올 shape을 의미한다.
>
> ```python
> print(x.shape)	# (4, 2, 3)
> tmp = tf.transpose(x, [2, 0, 1])
> print(tmp)		# (3, 4, 2)
> # x.shape.[2]가 tmp.shape[0] 이 되었고
> # x.shape.[0]가 tmp.shape[1] 이 되었고
> # x.shape.[1]가 tmp.shape[2] 이 되었다.
> ```





#### tf.range()

```python
tf.range(limit, delta=1, dtype=None, name='range')
tf.range(start, limit, delta=1, dtype=None, name='range')
```

tensor list반환



#### tf.pad

tensor에 특정 값으로 둘러싸는 함수

```py
output_tensor = tf.pad(input_tensor, paddings, mode='CONSTANT', constant_values=0, name=None)
```

`paddings` : D x 2 tensor , int32

> D mean dimension of input_tensor 
>
> paddings[D, N]  : D차원의 방향으로 N겹을 둘러싸겠다는 의미

`mode` : pad value를 결정함

> `mode='CONSTANT'` : 0으로 둘러쌈

```python
t = tf.constant([[1, 2, 3], [4, 5, 6]])
paddings = tf.constant([[1, 1,], [2, 2]])	
# 1차원은 앞 뒤로 1겹씩, 2차원은 앞 뒤로 2겹씩 둘러싸겠다는 의미

tf.pad(t, paddings, "CONSTANT")  # [[0, 0, 0, 0, 0, 0, 0],
                                 #  [0, 0, 1, 2, 3, 0, 0],
                                 #  [0, 0, 4, 5, 6, 0, 0],
                                 #  [0, 0, 0, 0, 0, 0, 0]]
```



#### tf.stop_gradient()

Stops gradient computation.

network의 특정 파트만 학습시키고 싶을 때 사용

```py
output = tf.stop_gradient(input, name=None)
```





#### tf.concat()

Function that stack serveral matrices

```python
res = tf.concat(value, axis = )
```

`value` : the tuple containing the metrices to stack

`axis` : stacking direction



```python
x1 = tf.constant([1, 2, 3])
x2 = tf.constant([4, 5, 6])

x = tf.concat((x1, x2), axis =0)
print(x) 
```

> tf.Tensor([1 2 3 4 5 6], shape=(6,), dtype=int32)

```python
x1 = tf.constant([[1, 2, 3]])
x2 = tf.constant([[4, 5, 6]])

x = tf.concat((x1, x2), axis =0)
print(x) 
```

> [[1 2 3]
> [4 5 6]], shape=(2, 3), dtype=int32)



**issue**

```python
t1 = [1, 1, 1, 1]
t2 = [2, 2, 2, 2]
t3 = [3, 3, 3, 3]
t4 = [4, 4, 4, 4]
pooled = [t1, t2, t3, t4]
pooled = tf.concat([t1, t2, t3, t4], axis=0)
print(pooled.shape)	# (16,)

t1 = tf.ones(shape = (1, 4))*1
t2 = tf.ones(shape = (1, 4))*2
t3 = tf.ones(shape = (1, 4))*3
t4 = tf.ones(shape = (1, 4))*4
pooled = [t1, t2, t3, t4]
pooled = tf.concat([t1, t2, t3, t4], axis=0)
print(pooled.shape) # (4, 4)  제대로 동작하지 않음  ????

t1 = tf.constant([1, 1, 1, 1])
t2 = tf.constant([2, 2, 2, 2])
t3 = tf.constant([3, 3, 3, 3])
t4 = tf.constant([4, 4, 4, 4])
pooled = [t1, t2, t3, t4]
pooled = tf.concat([t1, t2, t3, t4], axis=0)
print(pooled.shape) 	# (16,) 제대로 동작함
```

