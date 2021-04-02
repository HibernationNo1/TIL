# numpy2

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



##### 4. 비교 현산