# numpy

다차원 컨테이너 자료구조로서 Numpy에서 다루는 data structure는 ndarray라고 부른다. 

```python
import numpy as np
```

---

### 1. 기본 함수 및 속성



#### 1. 생성

##### 기본 생성함수

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

- np.random

  난수를 만들어주는 함수다.

  - np.random.randint()

    정수 난수를 만든다.

    `np.random.randint(low = , high = , size = ( , ))`

    ```python
    test_np = np.random.randint(low = 0, high = 3, size = (2,3))
    print(test_np)
    ```

    ```
    [[2 1 0]
     [1 2 1]]
    ```


  - np.random.normal()

    실수 난수를 만든다.

    `np.random.normal(low , high , size = ( , ))`

    ```python
    tmp = np.random.normal(0, 1, size= (2, 1))
    print(tmp)
    ```

    

##### like() 생성함수

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

---



#### 2. 속성

- shape

  - 매개변수로 사용될 때

    nparray의 shape을 결정한다

  - 속성 자체로 사용될때

    ndarray의 shape을 반환한다.

    `np이름.shape`

- dtype

  - 매개변수로 사용될 때

    nparray의 dtype을 결정한다

    nparray를 만들때는 dtype을 통해 타입을 명시해주는것이 좋다.

    `tmp_np = np.ones(shape = (2,2), dtype = np.int16)` 

    `np.uint8`, `np.int16`, `np.float32`, `np.complex64`, `np.bool`

  - 속성 자체로 사용될때

    ndarray의 data type을 반환한다.

    `np이름.dtype`

- size

  전체 원소의 개수를 반환한다.

  ```python
  test_np = np.empty(shape = (3,4,5,6,7))
  print(test_np)  # 2520 출력
  ```

- itemsize

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

---



#### 3. indexting, slicing

```python
python_matrix = [[1, 2], [3, 4], [5, 6], [7, 8]]
nd_matrix = np.array(python_matrix)
```

- 각각의 경우는 참조를 이용해서 이루어진다.

  ndarray는 큰 data를 다루고, indexing과 slicing이 빈번히 일어나므로 최대한 memory를 아끼려는 모습을 보여준다.

  이 때문에 불필요하게 새로운 ndarray를 만들지 않고 참조를 이용하여 indexing, slicing을 한다.



##### indexting

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



##### slicing

`:` 를 사용해서 특정 차원을 슬라이싱 할 수 있다.

```python
print(nd_matrix)		# [[1, 2], [3, 4], [5, 6], [7, 8]]

print(nd_matrix[:,0])	# [1 3 5 7]
# 2차원에서 0에 위치한 entry만 뽑아낸 것
print(nd_matrix[:,1])	# [2 4 6 8]
# 2차원에서 1에 위치한 entry만 뽑아낸 것
print(nd_matrix[1,:])	# [3 4]
# 1차원에서 1에 위치한 entry만 뽑아낸 것
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



---



#### 4. reshape, resize

```python
test_np = np.random.randint(low = 0, high = 3, size = (3,4))
print(test_np)
```

```
[[2 1 2 0]
 [2 2 1 0]
 [1 0 0 2]]
```



##### reshape

shape을 새롭게 구축한 nparray를 **반환**하는 함수다.  

매개변수로 들어가는 정수의 곱은 reshape을 적용할 ndarray의 size의 각 entry 곱과 같아야 한다. (안그럼 오류남)

`nparray.reshape()`  nparray의 size는 변하지 않는다.

```python
reshaped_np1 = test_np.reshape(12)
print(reshaped_np1)

reshaped_np2 = test_np.reshape(2,6)
print(reshaped_np2)

reshaped_np3 = test_np.reshape(4,3)
print(reshaped_np3)
```

> test_np의 size = (3, 4)

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



##### resize

nparray의 size를 재구축하는 함수다.

매개변수로 들어가는 정수의 곱은 resize을 적용할 ndarray의 size의 각 entry 곱과 같아야 한다. (안그럼 오류남)

`nparray.resize()`

```python
resized_np = test_np.resize(2,6)
print(resized_np) 		# None
```

> 반환값 없음. test_np 자체의size가 변함



자료 출처: https://shinslab.tistory.com/51?category=834200

---



### 2. 기능 함수

#### 1. ndarray 연산

##### 1. sum()

매개변수로 가져온 ndarray를 axis방향에 따라서 전부 더해준다.

`np.sum(data, axis = )`



##### 2. hstack()

매개변수로 가져온 ndarray를 쌓는 형태로 합쳐준다.

`np.hstack(tuple)`

```python
x_data = np.random.normal(0, 1, size = (100, 1))
y_data = x_data+1

data = np.hstack((x_data, y_data))
print(data.shape)  # (100, 2)
```



