# numpy1

- Numerical python의 줄임말로, 다차원 컨테이너 자료구조로서 Numpy에서 다루는 data structure는 ndarray라고 부른다. 
- 정교한 브로드캐스팅 기능을 제공한다
- 반복문 없이 데이터 배열에 대한 처리를 지원하여 빠르고 편리하다.

```python
import numpy as np
```

```python
np.__version__
```

![](https://media.vlpt.us/images/mingki/post/e0cdf6b1-cfd0-4a64-82d1-0c489237f1c2/array_shape.png)

---

## 1. 기본 함수(1) 및 속성

### 1. 생성

##### 1. 기본 생성함수

- np.array()

  ```python
  python_list = [1, 2, 3, 4, 5]
  ndarr1 = np.array(python_list)
  ndarr2 = np.array() # 빈 ndarray
  ```

- np.zeros()

  모든 원소가 0으로 채워진 ndarray를 만들어낸다.

  `np.zeros(shape = , dtype = )`

  ```python
  zeros_np = np.zeros(shape =(2, 3))
  print(zeros_np)  
  ```

  ```
  [[0. 0. 0.]
   [0. 0. 0.]]
  ```

- np.ones()

  ```python
  ones_np = np.ones(shape =(2, 3, 4))
  print(ones_np) 
  ```

  ```
  [[[1. 1. 1. 1.]
    [1. 1. 1. 1.]
    [1. 1. 1. 1.]]
  
   [[1. 1. 1. 1.]
    [1. 1. 1. 1.]
    [1. 1. 1. 1.]]]
  ```

- np.full()

  통일된 어떤 값으로 채워줄지 결정해서 ndarray를 만드는 함수다.

  `np.full(shape = , fill_value = )`

  ```python
  PI = math.pi
  
  full_np = np.full(shape = (2, 2, 2, 2), fill_value = PI)
  print(full_np)
  ```

  ```
  [[[[3.14159265 3.14159265]
     [3.14159265 3.14159265]]
  
    [[3.14159265 3.14159265]
     [3.14159265 3.14159265]]]
  
  
   [[[3.14159265 3.14159265]
     [3.14159265 3.14159265]]
  
    [[3.14159265 3.14159265]
     [3.14159265 3.14159265]]]]
  ```

- np.empty()

  `np.empty(shape = )`

- np.eye()

  단위행렬을 만든다.

  `np.eye(size)` size는 임임의 정수값.

  단위행렬은 정사각 행렬이기 때문에 shape의 가로세로 axis가 동일하다.



##### 2. like() 생성함수

np.ones_like()

np.zeros_like() 

np.full_like() 

np.empty_like()

기존에 만들어져있던 ndarray를 argument로 사용해서 shape만 따오는 함수다.

```python
test_np = np.array([[1, 2], [3, 4], [5, 6]])
np.ones_like(test_np)
np.zeros_like(test_np) 
np.full_like(test_np) 
np.empty_like(test_np)
```



- 기존에 만들어진 ndarray의 각 원소에 10을 더한 ndarray를 만들 때

  ```python
  test_np = np.array([[1, 2], [3, 4], [5, 6]])
  added_np = np.full_like(test_np, fill_value = 10)
  result_np = test_np + added_np
  print(result_np)
  ```

  ```
  [[11 12]
   [13 14]
   [15 16]]
  ```



##### 3. random 생성 함수

np.random

난수를 만들어주는 함수다.

- np.random.random

  size에 따른 shape을 가진, 각각의 entry가 float인 난수 ndarray를 생성

  `np.random.random(shape)` 매개변수가 size가 아닌 shape이기 때문에 괄호가 두 겹

  ```python
  a1 = np.random.random((2,2))
  ```

  ```
  [[0.57582414 0.02515481]
   [0.9191607  0.10078312]]
  ```

  

- np.random.randint()

  범위 내의 정수 난수를 만든다.

  `np.random.randint(low = , high = , size = ( , ))`

  ```python
  test_np = np.random.randint(low = 0, high = 3, size = (2,3))
  ```

  ```
  [[2 1 0]
   [1 2 1]]
  ```

  

- np.random.normal()

  정규 분포를 고려한, 범위 내의 실수 난수를 만든다

  `np.random.normal(loc = , scale = , size = ( , ))`

  setting mean(loc), standard deviation(scale) value

  ```python
  tmp = np.random.normal(loc = 0, scale = 1, size= (2, 1))
  ```




- np.random.rand()

  균등 분포를 고려한 랜덤한 수의 ndarray 생성

  `np.random.rand(size)`  매개변수가 shape이 아닌 size기 때문에 괄호가 한 겹

  ```python
  a1 = np.random.rand(1, 3)
  ```

  ```
  [[0.93576244 0.07483359 0.04199633]]
  ```

- np.random.randn()

  표준 정규 분포를 고려한 랜덤한 수의 ndarray 생성

  `np.random.randn(size)`

  ```python
  a1 = np.random.randn(2,2)
  ```



##### 4. 범위 생성 함수

- np.arange()

  list에서 for문에 range를 사용해 배열을 만드는것과 비슷한 동작

  `np.arange(start, end, step)`

  ```python
  a1 = np.arange(0, 30, 2)
  # [ 0  2  4  6  8 10 12 14 16 18 20 22 24 26 28]
  ```

- np.linspace()

  범위 내에서 균등간격의 ndarray를 생성한다.

  `np.linspace(start, end, num)`

  ```python
  a1 = np.linspace(0, 1, 5)
  # [0.  0.25   0.5  0.75 1.0]
  ```

- np.logspace()

  범위 내에서 균등간격의 entry값에 각각 log를 취해서 생성한다. 

  ```python
  a1 = np.logspace(0, 1, 5)
  # [ 1.   1.77827941  3.16227766  5.62341325 10.0]
  ```

  

---



### 2. 속성

##### 1. ndim

ndarray의 차원을 반환한다.

##### 2. shape

- 매개변수로 사용될 때

  nparray의 shape을 결정한다

- 속성 자체로 사용될때

  ndarray의 shape을 반환한다.

  `np이름.shape`

##### 3. dtype

- 매개변수로 사용될 때

  nparray의 dtype을 결정한다

  nparray를 만들때는 dtype을 통해 타입을 명시해주는것이 좋다.

  `tmp_np = np.ones(shape = (2,2), dtype = np.int16)` 

- 속성 자체로 사용될때

  ndarray의 data type을 반환한다.

  `np이름.dtype`

###### **표준 데이터 타입**

- `np.bool`

- ``np.int`,  `np.int8~64`, `np.uint8~64`

- `np.float16~64`

- `np.complex`: 복소수

- **날짜, 시간 배열** (Y, M, W, D, m, s )

  `np.datetime64`

  문자열에 대해서 시간에 대한 타입으로 인식한다.

  ```python
  date = np.array('2020-01-01', dtype = np.datetime64)
  print(date.dtype)  # datetime64[D]
  ```

  날짜 기준으로 연산이 가능

  ```python
  print(date + np.arange(25, 35, 1))
  ```

  ```
  ['2020-01-26' '2020-01-27' '2020-01-28' '2020-01-29' '2020-01-30'
   '2020-01-31' '2020-02-01' '2020-02-02' '2020-02-03' '2020-02-04']
  ```

##### 4. size

전체 원소의 개수를 반환한다.

```python
test_np = np.empty(shape = (3,4,5,6,7))
print(test_np)  # 2520 출력
```

##### 5. itemsize

ndarray의 data type을 파악하고 해당 type에 대한 memory의 크기를 반환한다.

ndarray가 `np.uint8`, `np.int16`, `np.float32`, `np.complex64`, `np.bool` 일 때

각각 1, 2, 4, 8, 1 을 반환

- size와 itemsize를 합치면 ndarray가 얼만큼의 memory를 사용하는지 알 수 있다.

  ```python
  a = np.ones(shape = (100,300), dtype = np.int16)
  print(str(a.size*a.itemsize) + " B and", str(a.size*a.itemsize/1024) + " KB")
  ```

  ```
  60000 B and 58.59375 KB
  ```

##### 6. nbytes

ndarray가 사용하는 memory의 크기를 반환한다.

size * itemsize 와 같음

##### 7. strides

다음 차원으로 넘어가는데 필요한 memory의 크기를 반환한다.



**전체 예시**

```python
test_np = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
def foo(a):
    print(a)
    print('ndim:', a.ndim)
    print('shpae: ', a.shape)
    print('dtype: ', a.dtype)
    print('size: ', a.size)
    print('itemsize:', a.itemsize)
    print('nbytes:', a.nbytes)
    print('strides', a.strides)

foo(test_np)
```

```
[[1 2 3]
 [4 5 6]
 [7 8 9]]
ndim: 2
shpae:  (3, 3)
dtype:  int32
size:  9
itemsize: 4
nbytes: 36
strides (12, 4)
```



---



### 3. indexting, slicing

```python
python_matrix = [[1, 2], [3, 4], [5, 6], [7, 8]]
nd_matrix = np.array(python_matrix)
```

- 각각의 경우는 참조를 이용해서 이루어진다.

  ndarray는 큰 data를 다루고, indexing과 slicing이 빈번히 일어나므로 최대한 memory를 아끼려는 모습을 보여준다.

  이 때문에 불필요하게 새로운 ndarray를 만들지 않고 참조를 이용하여 indexing, slicing을 한다.
  
  참조를 하지 않고 새로운 ndarray를 반환하려면 copy()함수를 호출해야 한다.



##### 1. indexting

`ndarray[고차원entry, ... , 저차원entry]`

```python
print(nd_matrix[3, 1], nd_matrix[2, 0])		# 8 5출력
```

- 참조를 이용한 indexting

  기존 ndarray를 수정하면 indexing, slicing된 data에 영향을 미치므로 예기치 않은 결과를 얻을 수 있다는 단점이 있다.

  ```python
  print(nd_matrix)	# [[1, 2], [3, 4], [5, 6], [7, 8]]
  element1 = nd_matrix[0]
  print(element1) 	# [1 2]
  
  nd_matrix[0] = [10, 10]
  print(element1) 	# [10 10]
  print(nd_matrix)	# [[10 10], [3, 4], [5, 6], [7, 8]]
  
  ```

  > element1에 직접 접근하지 않았지만, 참조를 이용해 index에 접근하기 때문에 element1값이 변한다. 

- **copy()**

  ndarray를 복사하는 copy함수를 사용하면 참조에 의한 data변화를 예방할 수 있다.

  ```python
  print(nd_matrix)	# [[1, 2], [3, 4], [5, 6], [7, 8]]
  element1 = nd_matrix[0].copy()
  print(element1) 	# [1 2]
  nd_matrix[0] = [10, 10]
  print(element1) 	# [1 2]
  print(nd_matrix)	# [[10 10], [3, 4], [5, 6], [7, 8]]
  ```



##### 2. slicing

`:` 를 사용해서 특정 차원을 슬라이싱 할 수 있다.

`a[start:stop:step]`

```python
print(nd_matrix)		# [[1, 2], [3, 4], [5, 6], [7, 8]]
print(nd_matrix[0:2])	# [[1 2], [3 4]]   	0부터 1까지
print(nd_matrix[0::2])	# [[1 2],  [5 6]]	0부터 끝까지 2개의 스텝
print(nd_matrix[::-1])	# [[7 8], [5 6], [3 4], [1 2]]  역으로 출력

print(nd_matrix[1,::-1])# [4, 3]
# 2차원에서 1에 위치한 ndarray인 [3, 4]에 [::-1]을 적용한 것
print(nd_matrix[3,:]) 	# [7, 8]
# [7, 8]에 [:](all)을 적용한 것
```

```python
print(nd_matrix[:,0])	# [1 3 5 7]
# 2차원에서 전체 entry에 대해서 0에 위치한 entry만 뽑아낸 것
print(nd_matrix[:,1])	# [2 4 6 8]
# 2차원에서 전체 entry에 대해서 1에 위치한 entry만 뽑아낸 것 
print(nd_matrix[1::2,::-1])
# 2차원에서 1부터 끝까지 2개의 step으로 entry를 뽑아([3, 4], [5, 6]) 역으로 출력
print(nd_matrix[::-1,::-1])
# 2차원 전체를 역으로 뽑고 각각의 entry를 또 역으로 출력
```

3차원에서 생각해보자.

```python
img = np.random.randint(low = 0, high = 255, size = (1080, 1920, 3))
print(img.shape) 	# (1080, 1920, 3)

print(img[:,:,0].shape, img[:,:,1].shape, img[:,:,2].shape)		
# (1080, 1920) (1080, 1920) (1080, 1920)
# 각각의 1, 2차원을 slicing하고 3차원에서 0, 1, 3에 위치한 enrty만 뽑은 ndarray의 shape을 출력했다.

print(img[45,:,:].shape)	# (1920, 3)
# 2, 3차원을 slicing하고 1차원에서 45에 위치한 enrty만 뽑은 ndarray의 shape을 출력
print(img[:,300,:].shape)	# (1080, 3)
# 1, 3차원을 slicing하고 2차원에서 300에 위치한 enrty만 뽑은 ndarray의 shape을 출력
print(img[2,2,:].shape)		# (3,)
# 3차원을 slicing하고 1차원에서 2에 위치하고, 2차원에서 2에 위치한 enrty만 뽑은 ndarray의 shape을 출력
```

#####  3. boolean indexing

ndarray의 각 요소의 선택 여부를 true or false로 지정, true값인 인덱스의 값만 조회

```python
a1 = np.array([1, 2, 3, 4, 5])
b1 = [True, True, False, False, True]
print(a1[b1]) # [1 2 5]
```

True로 지정된 index만 출력됨을 볼 수 있다.

##### 4. fancy indexing

배열에 index의 값을 저장 후 배열 자체를 사용해서 enrty에 접근하는 방법

```python
a1 = np.array([1, 2, 3, 4, 5])
ind1 = [1, 4]
ind2 = [0, 3, -1]
print(a1[ind1])		# [2 5]
print(a1[ind2])		# [1 4 5]
```

ind에 ndarray 타입의 배열을 할당하면 shape을 마음대로 설정할 수 있다.

```python
ind3 = np.array([[0, 1], [2, 3]])
print(a1[ind3])	# [[1 2], [3 4]]
```



---



## 2. 기본 함수(2)

### 1. 값 삽입, 삭제

##### 1. insert

ndarray의 특정 위치에 값 삽입

삽입할 방향을 axis로 조절, axis의 디폴트는 0

레퍼런스 참조가 아닌,  copy방식 (새로운 ndarray 반환)

`np.insert(ndarray, loc , value)`

```python
a1 = np.array([1, 2, 3, 4, 5])
b1 = np.insert(a1, 0, 10)
print(a1)	# [1, 2, 3, 4, 5]
print(b1)	# [10, 1, 2, 3, 4, 5]
```

매개변수로 사용하는 ndarray가 n차원이라도, axis를 설정하지 않으면 1차원으로 만들어버린다.

```python
a1 = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
b1 = np.insert(a1, 0, 10) 	# [10  1  2  3  4  5  6  7  8  9]
```

axis가 설정되면 해당 axis대로 insert

```python
b1 = np.insert(a1, 0, 10, axis = 0) 
b1 = np.insert(a1, 0, 10, axis = 1)
```

```
[[10 10 10]
 [ 1  2  3]
 [ 4  5  6]
 [ 7  8  9]]
 
 [[10  1  2  3]
 [10  4  5  6]
 [10  7  8  9]]
```



##### 2. delete

배열의 특정 위치에 값 삭제

삽입할 방향을 axis로 조절, axis의 디폴트는 0

`np.delete(ndarray, loc)`

매개변수로 사용하는 ndarray가 n차원이라도, axis를 설정하지 않으면 1차원으로 만들어버린다.

레퍼런스 참조가 아닌,  copy방식 (새로운 ndarray 반환)

```python
a1 = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
b1 = np.delete(a1, 0)  # [2 3 4 5 6 7 8 9]
```

```python
b1 = np.delete(a1, 2, axis = 0)
b1 = np.delete(a1, 2, axis = 1)  
```

```
[[1 2 3]
 [4 5 6]]

[[1 2]
 [4 5]
 [7 8]]
```





### 2. axis 변경

> axis는 단수, axes는 복수의 축을 의미함

##### 1. 전치

전치란, 가장 높은 axis와 가장 낮은 axis가 swap되어 재 배열이 되는 것을 의미한다. 

`ndarray.T`

```python
a1 = np.array([[1, 2, 3], [4, 5, 6], [7, 8, 9]])
b1 = a1.T
print(a1)
print(b1)
```

> shape이 (2, 2)라서 배열이 대각선 기준으로 대칭교환 되는것을 볼 수 있다.

```
[[1 2 3]
 [4 5 6]
 [7 8 9]]
 
[[1 4 7]
 [2 5 8]
 [3 6 9]]
```



```python
a1 = np.random.randint(0, 10, size = (3, 3, 2))
b1 = a1.T
print(a1)
print(b1)
```

> shape이 (3, 3, 2)이고, 1차원의 entry는 2개, 3차원의 entry는 3개이기 때문에 1차원과 3차원의 entry가 swap되면 (2, 3, 3)의 shape으로 변한다.

```
[[[9 6]					[[[9 4 5]
  [9 0]					  [9 2 5]
  [9 3]]				  [9 0 1]]
		변경 전 // 변경 후
 [[4 1]					 [[6 1 5]
  [2 0]					  [0 0 6]
  [0 1]]				  [3 1 1]]]

 [[5 5]
  [5 6]
  [1 1]]]
```



##### 2. swapaxse

매개변수로 사용되는 axis1과 axis2가 swap된다.

`swapaxse(axis1, axis2)`

```python
a1 = np.random.randint(0, 10, size = (3, 3, 2))
b1 = a1.swapaxes(2, 0)
print(a1.shape) 	# (3, 3, 2)
print(b1.shape)		# (2, 3, 3)

b1 = a1.swapaxes(2, 1)
print(a1.shape)		# (3, 3, 2)
print(b1.shape)		# (3, 2, 3)

print(a1)
print(b1)
```

> 3차원과 1차원의 entry 구조와 각 entry value도 swap됨을 볼 수 있다.

```
[[[3 8]					[[[3 6 4]
  [6 4]					  [8 4 9]]
  [4 9]]
						 [[0 2 7]
 [[0 1]				      [1 8 8]]
  [2 8]  변경 전  //  변경 후 	
  [7 8]]				 [[6 3 3]
						  [8 0 9]]]
 [[6 8]
  [3 0]
  [3 9]]]
```



##### 3. reshape

shape을 새롭게 구축한 nparray를 **반환**하는 함수다.  

매개변수로 들어가는 정수의 곱은 reshape을 적용할 ndarray의 size의 각 entry 곱과 같아야 한다. (안그럼 오류남)

`nparray.reshape()`  nparray의 size는 변하지 않는다.

```python
test_np = np.random.randint(low = 0, high = 3, size = (3,4))
print(test_np)
```

```
[[2 1 2 0]
 [2 2 1 0]
 [1 0 0 2]]
```

```python
reshaped_np1 = test_np.reshape(12)  
print(reshaped_np1)

reshaped_np2 = test_np.reshape(2,6)	# == test_np.reshape(-1,6)
print(reshaped_np2)

reshaped_np3 = test_np.reshape(4,3) # == test_np.reshape(-1,3)
print(reshaped_np3)
```

> test_np의 size = (3, 4)
>
> `reshape(-1, n)`을 사용하면 n에 알맞게 알아서 차원이 맞춰진다.

```
[0 1 2 2 0 1 0 0 2 1 2 1]
[[0 1 2 2 0 1]
 [0 0 2 1 2 1]]
[[0 1 2]
 [2 0 1]
 [0 0 2]
 [1 2 1]]
```

> reshape은 참조를 사용하기 때문에 reshape을 적용한 nparray 자체에 변화가 생기면 reshape array인 reshaped_np1, 2, 3도 모두 변한다. 
>
> 이를 원치 않으면 copy()함수를 사용할 수 있다.
>
> `test_np.reshape(4,3).copy()`





##### 4. resize

nparray의 size를 재구축하는 함수다.

resize로 인해 크기가 늘어나면 값이 0인 entry로 추가된다. (크기가 줄어들면 그냥 delete)

`nparray.resize()`

```python
test_np = np.random.randint(low = 0, high = 3, size = (3,4))
print(test_np)
```

```
[[2 1 2 0]
 [2 2 1 0]
 [1 0 0 2]]
```

```python
resized_np = test_np.resize(2,6)
print(resized_np) 		# None
```

> 반환값 없음. test_np 자체의size가 변함



##### 5. newaxis

새로운 축을 추가해주는 속성

- row로 축을 추가해줄 때

  `ndarray[np.newaxis, ]`

- column쪽으로 축을 추가해줄 때

  `ndarray[, np.newaxis]`

```python
a1 = np.array([1, 2, 3, 4, 5])
print(a1[np.newaxis, : 3])
print(a1[:4,  np.newaxis])
```

```
[[1 2 3]]
[[1]
 [2]
 [3]
 [4]]
```



##### 6. append

axis 축에 따라서 매개로 사용된 ndarray의 entry를 다른 ndarray의 끝에 insert한 ndarray를 반환한다.

axis를 설정하지 않으면 1차원 ndarray를 반환한다. 

`np.append(ndarray1, ndarray2, axis = )`

```python
a1 = np.random.randint(0, 10, size = (2, 5))
b1 = np.random.randint(0, 10, size = (2, 5))
print(a1)	# [[9 4 9 1 0], [0 5 8 5 6]]
print(b1)	# [[4 5 5 7 1], [9 7 9 5 5]]

c1 = np.append(a1, b1)
print(c1)	# [9 4 9 1 0 0 5 8 5 6 4 5 5 7 1 9 7 9 5 5]
```

```python
d1 = np.append(a1, b1, axis = 0)  	# row가 늘어남
d2 = np.append(a1, b1, axis = 1)	# column이 늘어남
```

```
 print(d1)								print(d2)
[[9 4 9 1 0]					[[9 4 9 1 0 4 5 5 7 1]
 [0 5 8 5 6]					[0 5 8 5 6 9 7 9 5 5]]	
 [4 5 5 7 1]
 [9 7 9 5 5]]
```



##### 6. concatenate

appen와 같은 동작을 수행하지만 매개변수를 list 또는 tuple형태로 가져온다.

`np.concatenate([ndarray1, ndarray2, .. ], axis)`

```python
d1 = np.concatenate([a1, b1], axis = 0)
print(d1)
d2 = np.concatenate([a1, b1], axis = 1)
print(d2)
```

> 출력은 위와 동일함



##### 7. stack

- hstack()

  매개변수로 가져온 ndarray를 1차원으로 append한다.(수평으로 stack)

  append와 concatenate의 axis = 0 으로 이해하면 된다.

  `np.hstack([ndarray1, ndarray2, .. ])`

- vstack()

  매개변수로 가져온 ndarray를 2차원으로 append한다.. (수직으로 stack)

  append와 concatenate의 axis = 1 으로 이해하면 된다.

  `np.vstack([ndarray1, ndarray2, .. ])`

- dstack()

  매개변수로 가져온 ndarray를 3차원으로 append한다.

  `np.dstack([ndarray1, ndarray2, .. ])`

- stack()

  매개변수로 가져온 ndarray의 최대 스택 +1 차원으로 append한다.

  `np.stack([ndarray1, ndarray2, .. ])`



##### 8. split

- split()

  배열을 분할해서 반환한다.

  `np.split(ndarray, [idx])`

  ```python
  a1 = np.arange(0, 10)
  print(a1)			# [0 1 2 3 4 5 6 7 8 9]
  
  b1, c1 = np.split(a1, [5])
  print(b1, c1)		# [0 1 2 3 4] [5 6 7 8 9]
  
  b1, c1, d1 = np.split(a1, [2, 5])
  print(b1, c1, d1)	# [0 1] [2 3 4] [5 6 7 8 9]
  ```

- vsplit()

  수직 분할. 1차원 방향으로 split한다.

  `np.vsplit(ndarray, [idx])`

- hsplit()

  수평 분할. 2차원 방향으로 split한다.

  `np.hsplit(ndarray, [idx])`

- dsplit()

  3차원 방향으로 split한다.

  `np.dsplit(ndarray, [idx])`



---



### 3. ndarray 연산

numpy는 vectorized 연산(Broadcasting)을 사용하기 때문에 배열 각 entry에 대한 반복적인 계산을 효율적으로 수행할 수 있다.

```python
a1 = np.array([1, 2, 3])
print(a1 + 5)  	# [6, 7, 8]
b1 = np.arange(1, 10).reshape(3, 3)
print(a1 + b1)  # [[ 2  4  6], [ 5  7  9],[ 8 10 12]]
# 2차원 안의 각각의 ndarray에 operation이 적용된다.
```

##### 1. 절대값, 제곱, 지수, 로그

- `np.abs()`: 절대값 함수
- `np.sqrt()`: 제곱근 함수
- `np.power()`: 제곱 함수
- `np.exp()` : 밑이 e인 지수 함수  e^(x)
- `np.exp2()` : 밑이 2인 지수 함수  2^(x)
- `np.log()`: 밑이 e인 log 함수  ln(x)
- `np.log10()`: 밑이 10인 log 함수  log(x)
- `np.log2()`: 밑이 2인 log 함수  log_{2}(x)

##### 

##### 2. 삼각함수

- `np.pi`: scale PI 값을 반환함.   (3.14...)

- `np.sin()`
- `np.cos()`
- `np.tan()`
- `np.arcsin()`, `np.arccos()` : 아크 사인, 코사인



##### 3. 집계 함수

###### 1. sum

매개변수로 가져온 ndarray를 axis방향에 따라서 전부 더해준 ndarray를 반환한다.

`np.sum(ndarray, axis = )`  또는 `ndarray.sum(axis)`

```
[[1 2 3]
 [4 5 6]
 [7 8 9]]
```

```python
print(np.sum(a1))				# 45
print(np.sum(a1, axis = 0)) 	# [12 15 18]
print(np.sum(a1, axis = 1))		# [ 6 15 24]
```



###### 2. cumsum 

매개변수로 가져온 ndarray를 axis방향에 따라서 누적합을 반환.

`np.cumsum(ndarray, axis = )` 



```python
print(np.cumsum(a1))		# [ 1  3  6 10 15 21 28 36 45]
print(np.cumsum(a1, axis = 0))
```

###### 3. diff

매개변수로 가져온 ndarray를 axis방향에 따라서 낮은 차원에서 큰 차원 방향으로 차분을 반환

`np.diff(ndarray, axis = )`



###### 4. prod

매개변수로 가져온 ndarray를 axis방향에 따라서 곱한 값을 반환

`np.prod(ndarray, axis = )`



###### 5. cumprod

매개변수로 가져온 ndarray를 axis방향에 따라서 누적으로 곱한 값을 반환

`np.cumprod(ndarray, axis = )`



###### 6. matmul

매개변수로 가져온 ndarray들를 행렬곱해서 반환

`np.matmul(ndarray1, ndarray2, ...)`



###### 7. tensordot 

매개변수로 가져온 ndarray들을 각 entry에 대해서 곱해서 반환

axes(axis 아님) 설정이 안되어있으면 각 ndarray의 상호 entry끼리 곱한 후 더한 값을 반환 

`np.tensordot(ndarray1, ndarray2, axes = )` 

```
			ndarray1						ndarray2
[[1, 2, 3], [4, 5, 6], [7, 8, 9]]	[[2, 2, 2], [2, 2, 2], [2, 2, 3]]
```

> 상호적으로 대응되는 자리의 entry끼리 곱한 후 더한다. (2 + 4 + 6 + ...+ 16 + 27) = 99

axes 설정이 되어있으면 선 매개변수 ndarray의 axes방향의 entry 각각에 후 매개변수 ndarray 자체를 곱한 ndarry를 더욱 높은 차원으로 쌓아서 반환한다.

```
	a1					b1
[[1 2 3]			[[1 1 1]
 [4 5 6]			 [1 1 1]
 [7 8 9]]			 [1 1 1]]
```

```python
print(np.tensordot(a1, b1, axes = 0))
```

```
[[[[1 1 1]
   [1 1 1]
   [1 1 1]]

  [[2 2 2]
   [2 2 2]
   [2 2 2]]

  [[3 3 3]
   [3 3 3]
   [3 3 3]]]


 [[[4 4 4]
   [4 4 4]
   [4 4 4]]

  [[5 5 5]
   [5 5 5]
   [5 5 5]]

  [[6 6 6]
   [6 6 6]
   [6 6 6]]]


 [[[7 7 7]
   [7 7 7]
   [7 7 7]]

  [[8 8 8]
   [8 8 8]
   [8 8 8]]

  [[9 9 9]
   [9 9 9]
   [9 9 9]]]]
```

> 4차원 반환함

```python
print(np.tensordot(a1, b1, axes = 1))
```

```
[[ 6  6  6]
 [15 15 15]
 [24 24 24]]
```



###### 8. mean

매개변수로 가져온 ndarray를 axis방향에 따라서 평균을 반환

`np.mean(ndarray, axis = )`

axis을 지정해주지 않으면 모든 entry에 대한 mean을 반환



###### 9. std

매개변수로 가져온 ndarray를 axis방향에 따라서 표준편차를 반환

`np.std(ndarray, axis = )`

axis을 지정해주지 않으면 모든 entry에 대한 표준편차를 반환



###### 10. var

매개변수로 가져온 ndarray를 axis방향에 따라서 분산을 반환

`np.var(ndarray, axis = )`

axis을 지정해주지 않으면 모든 entry에 대한 분산을 반환



###### 11. min, max

매개변수로 가져온 ndarray를 axis방향에 따라서 최소, 최대값을 반환

`np.min(ndarray, axis = )`,`np.max(ndarray, axis = )`

axis을 지정해주지 않으면 모든 entry에 대한 최소, 최대값을 반환



###### 12. argmin, argmax

매개변수로 가져온 ndarray를 axis방향에 따라서 최소, 최대값을 찾은 후 해당 인덱스를 반환

`np.argmin(ndarray, axis = )`,`np.argmax(ndarray, axis = )`

axis을 지정해주지 않으면 모든 entry에 대한 최소, 최대값을 찾은 후 해당 인덱스를 반환



###### 13. any

매개변수로 가져온 ndarray를 axis방향에 따라서 True가 존재하면 True를, 아니면 False를 반환 (OR 연산)

`np.any(ndarray, axis = )`

axis을 지정해주지 않으면 모든 entry에 대한 any를 적용



###### 14. all

매개변수로 가져온 ndarray를 axis방향에 따라서 False가 존재하면 False를, 아니면 True를 반환 (AND 연산)

`np.all(ndarray, axis = )`

axis을 지정해주지 않으면 모든 entry에 대한 all를 적용



##### 4. 비교

###### 1. 비교 연산자

` == `, `!=`, `<`, `>`, `<=`, `>=`

ndarray에 raight값 조건을 만족하면 True 반환

```python
a1 = np.random.randint(1, 5, size = (5))
print(a1)			# [4 4 2 1 3]
print(a1 == 3)		# [False False False False  True]
print(a1 != 3)		# [ True  True  True  True False]
print(a1 < 3)		# [False False  True  True False]
print(a1 > 3)		# [ True  True False False False]
print(a1 <= 3)		# [False False  True  True  True]
print(a1 >= 3)		# [ True  True False False  True]
```

> sum 과 같은 조건 연산도 가능하다.

```python
print(np.sum(a1 >= 3))  	# 11
print(np.count_nonzero(a1 != 3))  # 4
```

> a1[ ] 안에서 비교하면 Ture인 값을 반환한다.

```python
print(a1[a1 >=3])		# [4 4 3]
```



`&` ,`|`, `^`, `~`

AND, OR, XOR, NOT 연산

```python
print(a1, a2)		# [2 1 2 3 4] [2 4 3 1 3]
print((a1 >=3) & (a2 >=3), a1[(a1 >=3) & (a2 >=3)])
# [False False False False  True] [4]
print((a1 >=3) | (a2 >=3), a1[(a1 >=3) | (a2 >=3)])
# [False  True  True  True  True] [1 2 3 4]
print((a1 >=3) ^ (a2 >=3), a1[(a1 >=3) ^ (a2 >=3)])
# [False  True  True  True False] [1 2 3]
print(~(a1 >=3), a1[~(a1 >=3)])
# [ True  True  True False False] [2 1 2]
```



###### 2. 비교 함수

- isclose()

  `==` 함수를 ndarray 범위로 활용한다.

  `np.siclose(ndarray1, ndarray2)`

  ```python
  a1 = np.random.randint(1, 5, size = (5))
  a2 = np.random.randint(1, 5, size = (5))
  print(a1, a2)		# [2 1 3 3 3] [4 4 3 1 1]
  print(np.isclose(a1, a2))	# [False False  True False False]
  ```

- isnan()

  숫자가 아닌 entry는 Ture 반환

  `np.isnan(ndarray1)`

---



## 3. 기본 함수(3)

### 1. 정렬

##### 1. sort

- `np.sort(ndarray)` : ndarray를 반환 방식으로 정렬한다.

- `ndarray.sort()` : ndarray를 참조 방식으로 정렬한다.

axis를 통해 정렬을 적용할 차원을 정할 수 있다.



##### 2. argsort 

각각의 entry가 정렬된 entry의 원래 자리의 index를 반환한다.

`np.argsort()`



##### 3. partition

배열에서 가장 작은 값 k개만 앞으로 정렬해준다.  (뒤에서부터 탐색)

`np.partition(ndarray, k)` 

axis를 통해 정렬을 적용할 차원을 정할 수 있다.

```python
print(a1)		# [4 7 4 8 9 4 5 3 4]
print(np.partition(a1, 4))		# [4 4 3 4 4 5 7 8 9]
```



### 2. 파일 입출력

##### 1. save, saves

객체를 바이너리 형태로 파일을 저장한다.

- `np.save("이름", ndarray)` : 하나만 저장
- `np.savez("이름", ndarray1, ndarray2)` : 여러개를 저장



##### 2. load

바이너리 형태의 파일로부터 객체를 로딩한다.

`저장할 객체 = np.load("불러올 파일 이름.확장자")`

(savez로 만들어진)여러개의 ndarray를 불러왔다면

`저장할 객체['ndarray1']` 이런 방식으로 ndarray에 접근할 수 있다.

 

##### 3. savetxt

텍스트 형태로 파일을 저장한다.

`np.savetxt("이름", ndarray, delimiter = ',')`

```python
np.savetxt("a.csv", a2, delimiter = ',')
```

**옵션**

- `fmt = '%.2e'` : 소수점 둘째자리까지만 
- `header = 'c1, c2, c3'` : columns name을 c1, c2, c3로



##### 4.  loadtxt

텍스트 형태의 파일로부터 객체를 로딩한다.

`저장할 객체 = np.loadtxt("이름.확장자", delimiter = ',')`

```python
tmp = np.loadtxt("a.csv", delimiter = ',')
```

