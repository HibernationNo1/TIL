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

  정규 분포를 고려한, 범위 내의 실수 난수를 만든다.

  `np.random.normal(low , high , size = ( , ))`

  ```python
  tmp = np.random.normal(0, 1, size= (2, 1))
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

[기본 함수(2)]()