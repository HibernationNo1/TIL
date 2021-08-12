# tensorflow 기초

tensors에는 두 개의 클래스가 있다.

1. **constant tensors** : 변화가 불가능한 값

   > 클래스: EagerTensor 
   >
   > input, 이미지와 같은 data set 은 EagerTensor로 사용한다.

2. **Variable tensors** : 변화가 가능한 값

   > 클래스: ResourceVariable
   >
   > 업데이트가 필요한 파라미터는 ResourceVariable로 사용한다.

**예시**

```python
import tensorflow as tf
foo = [1, 2, 3]

t1 = tf.constant(foo)  
# t1은 EagerTensor 클래스의 list [1, 2, 3] 이 된다 
print(t1) # tf.Tensor([1 2 3], shape=(3,), dtype=int32 출력
print(type(t1))


t2 = t1 = ft.constant(foo, dtype = tf.float32)
# 이런 식으로 데이터 타입을 치환할 수 있다.
# t2은 ResourceVariable 클래스의 list [1, 2, 3] 이 된다 
print(t2)
print(type(t2))

t3 = tf.constant(t2)
# t2는 변화가 가능한 ResourceVariable 클래스이기 때문에 EagerTensor 클래스로 변환이 가능하다.
# t3은 EagerTensor 클래스의 list [1, 2, 3] 이 된다 
print(t3)
print(type(t3))

#=============================덧셈 연산
t3 = t1 + t2  #EagerTensor + ResourceVariable
print(t3) # [1,2,3,1,2,3] 이 아닌, [2, 4, 6]이 출력된다.
print(type(t3))  #EagerTensor + ResourceVariable = EagerTensor 클래스
```

> tensor끼리의 연산은 각 원소끼리의 연산이 적용된다.





+ 추가

  constant 대신 convert_to_tensor를 사용하는사람도 많다.

  ```python
  import tensorflow as tf
  foo = [1, 2, 3]
  t1 = tf.convert_to_tensor(foo)
  print(type(t1))  #EagerTensor 클래스
  ```

  > constant와 convert_to_tensor의 output은 동일하다



### 1. Tensor 생성

##### **tf.ones()** 

모든 원소가 1

```python
t1 = tf.ones(shape=(100, ))
# 1의 원소를 100개 가진 Rank 1 형태의 배열

t2 = tf.ones(shape=(100,3))
# 1의 원소를 3개 가진 배열이 100개 있는 Rank 2 형태의 배열(2차원)

t3 = tf.ones(shape=(100,100, 3))
# 1의 원소를 3개 가진 배열이 100개 있는 행렬이 100개 있는 Rank 3 형태의 배열(3차원)

foo = [[1,2,3], [4,5,6]]
t4 = tf.Variable(foo)	# shape = (2, 3) 형태의 텐서

tmp = tf.ones(shape = (1, 4))
# 4행 1열 형태의 2차원 텐서 
tmp = tf.ones(shape = (4, 1))
# 1행 4열 형태의 2차원 텐서 
```

- 원소에 스칼라 적용하여 값 할당하기

  ```python
  t1 = 5*tf.ones(shape = (128, 103, 10))
  # 여기서 5는 스칼라, tf.ones(shape = (128, 128, 10))는 벡터이므로
  # 스칼라 * 벡터 = 각 요소마다 스칼라를 곱해주기 때문에
  # 5의 원소를 10개 가진 배열이 103개 있는 행렬이 128개 있는 Rank 3 형태의 배열(3차원)
  ```

  

##### tf.ones_like()

  원소가 1인, 매개변수로 받은 텐서와 같은 형태의 텐서를 만든다.

  ```python
  t1 = 3*tf.ones(shape=(100,100, 3))
  # 3의 원소를 3개 가진 배열이 100개 있는 행렬이 100개 있는 Rank 3 형태의 배열(3차원)
  
  t2 = tf.ones_like(t1)
  # 1의 원소를 3개 가진 배열이 100개 있는 행렬이 100개 있는 Rank 3 형태의 배열(3차원)
  ```



##### **tf.zeros()** 

모든 원소가 0

  > 보통은 텐서에 0을 곱해서 모든 원소가 0인 텐서를 만든다.
  >
  > zeros_like() 도 지원한다.



##### **tf.random.normal()** 

 정규분포로부터 추출한 무작위의 실수값을 할당

```python
t1 = tf.random.normal(shape = (10, 10))
# 각 원소에 무작위의 값을 할당한 텐서
```



##### tf.random.set_seed(0) 

무작위 값이 고정 후 반복적으로 할당

```python
tf.random.set_seed(0) 
t1 = tf.random.normal(shape = (3, 3)) 
# 이후 계속 t = tf.random.normal(shape = (3, 3)) 을 선언해도 각 원소는 고정된 값이 할당된다.
```

> 랜텀 이펙트를 준 후 같은 결과를 내보내고 싶을 때 사용

- mean(평균)과 stddev(표준편차) 적용

  ```python
  t1 = tf.random.normal(mean = 3, stddev = 1, shape = (10, 10))
  #평균이 3이고 표준편차가 1인 Rank 2 텐서 생성
  ```



##### **tf.random.uniform()** 

균등분포로부터 추출한 무작위의 실수값을 할당 (디폴트 = 0부터 1까지)

  ```python
  t1 = tf.random.uniform(shape = (3, 3, 3))
  ```

  - minval(최소값), maxval(최대값) 적용

    ```python
    t1 = tf.random.uniform(shape = (10, 10, 10), minval = -10, maxval = 10)
    #최소값이 -10이고 최대값이 10인 Rank 3 균등분포 텐서 생성
    ```



##### **tf.constant**()

list를 constant tensor로 변경하거나 새로운 tensor 생성

constant는 immutable object이기 때문에 learning이 되지 않는 parameters에 적용해야 한다. (data set)

```
tmp = [1, 2, 3]
t1 = tf.constant(tmp)
t2 = tf.constant([1, 2, 3, 4])
```



##### tf.Variable()

mutable object이기 때문에 learning 되는 parameters에 적용해야 한다. (wieght, bias)

```python
tmp = [1, 2, 3]
t1 = tf.Variable(tmp)
t2 = tf.Variable([1, 2, 3, 4])
```



##### tf.convert_to_tensor()

constant tersor와 같은 type을 가지고 있다.

Difference from constant : constant에서는 Variable로 type change가 가능하지만, Variable에서 constant로는 type change가 불가능하다. 하지만 convert_to_tensor로 만들어진 tensor는 Variable로 type change가 가능하다.

```python
t1 = tf.Variable([1, 2, 3, 4])
t2 = tf.convert_to_tensor(t1)  # no error
```



### 2. Tensor에서 정보 추출

##### **shape** 

shape을 반환

```python
t1 = tf.random.uniform(shape = (10, 10, 10), minval = -10, maxval = 10)

print(t1.shape)  # (10, 10, 10) 출력
```



##### dtype

데이터 타입을 반환

```python
print(t1.dtype) # <dtype: 'float32'> 출력
```

> tensorflow 는 dtype: 'float32' 를 데이터로 사용하기를 원함

```python
t1 = ft.constant(foo, dtype = tf.float32)
# 이런 식으로 데이터 타입을 치환할 수 있다.
```



### 3. 형 변환

##### **cast()**

```python
t1 = tf.random.normal(shape = (3, 4), mean = 3, stddev = 1)
t2 = tf.random.normal(shape = (3, 4), mean = 3, stddev = 1)

t1 = tf.cast(t1, dtype = tf.int16)  # 실수를 정수로 변환
t2 = tf.cast(t2, dtype = tf.int16)
print(t1+t2) # 정수에 대한 결과가 나옴
```

> numpy에서 astype()을 사용했던 것 처럼 tensorflow에서는 tf.cast()를 사용



조건도 사용 가능

```python
tf.cast( (t2 > 3), dtype = tf.float32)
```

위 조건이 True면 1, False면 0을 return





### 4. dim change

##### reshape()

원하는 shape을 직접 설정해서 기존 object의 shape을 변경할 수 있다.



##### squeeze()

dimension 중 size 가 1인 것을 찾아 scalar 값으로 바꿔 해당 dimension을 제거한다.



##### expend_dims

axis로 지정된 차원을 추가한다.



### 5. Tensor 연산

##### 1. broadcasting

**기본적으로 Tensor의 연산은 각 원소끼리 적용되는 동작을 수행한다.**

```python
import tensorflow as tf

t1 = tf.constant([1, 2, 3])
t2 = tf.constant([11, 22, 33])
# 연산이 적용될 원소가 없으면 오류  //  t2 = tf.constant([22, 33]) 와 같이

print(t1+t2) # tf.Tensor([12 24 36], shape=(3,), dtype=int32) 출력
print(t1-t2) # tf.Tensor([-10 -20 -30], shape=(3,), dtype=int32)
print(t1*t2) # tf.Tensor([11 44 99], shape=(3,), dtype=int32)
print(t1/t2) # tf.Tensor([0.09090909 0.09090909 0.09090909], shape=(3,), dtype=float64)
print(t1%t2) # tf.Tensor([1 2 3], shape=(3,), dtype=int32)
print(t1//t2)# tf.Tensor([0 0 0], shape=(3,), dtype=int32)
```



- broadcasting 적용

```python
t1 = 2*tf.ones(shape = (1, 4)) 
# 4행 1열 형태의 2차원 텐서 
t2 = 5*tf.ones(shape = (3, 1))
# 1행 3열 형태의 2차원 텐서
t3 = t1 + t2
# 2차원이기 때문에 

# 			  5		2 2 2 2	  5 5 5 5	  7 7 7 7
# 2 2 2 2  +  5  => 2 2 2 2 + 5 5 5 5  == 7 7 7 7   의 계산결과가 된다
# 			  5		2 2 2 2   5 5 5 5	  7 7 7 7
# 
```



##### 2. axis

axis는 연산하고 싶은 차원을 의미한다.

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



##### 3. tf.concat()

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
>  [4 5 6]], shape=(2, 3), dtype=int32)



