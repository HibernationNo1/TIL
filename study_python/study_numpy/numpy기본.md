# numpy 



##### np.expand_dims()

dimension을 1 expand한다.

```python
np.expand_dims(data, axis = )
```

> `data` : input data
>
> `axis` : 몇 번째 dimension을 push해서 expand할지 결정
>
> ```python
> data.shape # (28, 28)
> np.expand_dims(data, axis = 0) # data.shape = (1, 28, 28)
> np.expand_dims(data, axis = 1) # data.shape = (28, 1, 28)
> np.expand_dims(data, axis = 2) # data.shape = (28, 28, 1)
> np.expand_dims(data, axis = -1) # data.shape = (28, 28, 1)
> #  맨 끝 차원 추가
> ```



##### np.argmin()

ndarray안의 elements 중 min 값의 index를 return

```python
np.argmin(data)
```



##### np.argmax()

ndarray안의 elements 중 max 값의 index를 return

```python
np.argmax(data)
```



##### np.where()

ndarray 안에서 조건에 맞는 value의 index를 return

```python
np.where(조건)
```

또는 ndarray 안에서 조건에 맞으면 True, 아니면 False return

```python
np.where(조건, 조건이 True, 조건이 False)
```



ex)

```python
np.where(ndarray < 10)
```

또는

```python
np.where(ndarray != 'winter', 'True', 'False')
```



##### np.argwhere()

np.where()는 boolean을 return할때도 있지만 np.argwhere()는 조건에 맞는 값의 index를 반환하는것에만 집중

```python
np.where(조건)
```

```python
x = np.arange(6).reshape(2,3)
# array([[0, 1, 2],
#       [3, 4, 5]])

np.argwhere(x>1)
# array([[0, 2],
#       [1, 0],
#       [1, 1],
#       [1, 2]])
```







##### np.arange()

[start, stop) 에서 step 의 크기만큼 일정하게 떨어져 있는 숫자들을 array 형태로 반환

```python
np.arange([start, ] stop, [step, ] dtype=None)
```

`step` default  = 1

ex)

```python
np.arange(3, 7)  # [3, 4, 5, 6]
```





##### np.squeeze()

ndarray안의 dimensions 중 1의 shape을 가진 dimensions를 delete해서 return

```python
data = np.squeeze(data)
```



##### np.savez_compressed()

save file format '.npz' as compressed

```python
np.savez_compressed(path, save_data_name = save_data)
```

> 여러 list를 단일 파일에 저장도 가능

ex)

```python
np.savez_compressed(os.path.join(save_path, 'losses_accs'),
                        a = foo['a'], 
                        b = foo['b'],
                        c = foo['c'],
                        d = foo['d'])
```

> npz 파일 안에 a, b, c, d 라는 column 각각에 foo['a'] 에 저장된 data가 기록되어 saved



##### np.load()

load file

```python
instance = np.load(path + 'name.format') 
print(instance)
```





##### np.count_nonzero()

```python
np.count_nonzero(bbox, axis=0)
```

> bbox의 0 dim에서 0이 아닌 element의 개수를 count





##### np.clip()

input array안의 elements에 대해서 min값 보다 작은 값들을 min값으로, max값 보다 큰 값들을 max값으로 바꿔주는 method

```python
np.clip(array, min, max)
```



##### np.ix_()

첫 번째 parameter는 row를, 두 번째 parameter는 column을 의미하는 index ndarray를 만든다.

```python
tmp = np.ix_(row_in, column_in)
```

out : tuple of ndarrays

만일 세 번째 인자를 준다면, (x, y, z) 와 같이 3차원 index가 된다. (인자가 많아질수록 dimension도 높아짐)



ex)

```python
a = np.arange(10).reshape(2, 5)
# ndarray([[0, 1, 2, 3, 4],
#          [5, 6, 7, 8, 9]])

tmp = np.ix_([0, 1], [2, 4])   # row = 0, 1    column = 2, 4
# tmp = (ndarray([[0],[1]]), ndarray([[2, 4]]))
     
print(a[tmp])  
# array([[2, 4],
#        [7, 9]])   (0, 1) row index,  (2, 4) column index를 뽑는데 사용 
```





##### np.histogram()

data를 histogram으로 표현하는 함수

```python
hist, bins = np.histogram(data, bins= , range= )
```

- `data` : flatten shape의 data

- `bins` : int, 히스토그램 각 차원의 크기(빈(bin)의 개수)를 나타내는 list

  > `bons = [256]` 

- `range` : float, 

- `hist` : 계산된 histogram





##### np.cumsum()

ndarray의 누적합을 계산한다.

>  n번 index의 누적합 결과 = 0~n까지의 element들의 합

```python
tmp = np.array([1, 2, 3, 4, 5, 6])

res1 = np.cumsum(tmp)  # 1 3 6 10 15 21
res2 = tmp.cumsum()
```



##### np.unique()

인자로 받은 ndarray의 element에서 모든 고유 값을 검색하고 이러한 고유 값을 정렬한다.





##### np.meshgrid()

input으로 받은 `x`,` y`의 shape으로 grid cell을 만든 후 `res_x`, `res_y`으로 반환한다.

이 때

`res_x`는 `x`의 각 원소를 1-D로 concatenate후 2-D로 concatenate하고

`res_y`는 `y`의 각 원소를 2-D로 concatenate후 1-D로 concatenate한다.

```python
x = [1, 2, 3]
y = [6, 7, 8, 9, 10]
res_x, res_y = np.meshgrid(np.array(x), np.array(y))
print(res_x.shape) # (5, 3)  == print(res_y.shape)
# == (y.shape, x.shape)

print(res_x)
print(res_y)
```



```
print(res_x)
[[1 2 3]
 [1 2 3]
 [1 2 3]
 [1 2 3]
 [1 2 3]]
```

```
print(res_y)
[[ 6  6  6]
 [ 7  7  7]
 [ 8  8  8]
 [ 9  9  9]
 [10 10 10]]
```





##### np.broadcast_to()

같은 배열을 여러개 복사해서 늘리는 함수

```python
x = np.array([1, 2, 3])
np.broadcast_to(x, (2, 3))
# [[1 2 3]
#  [1 2 3]]

x = np.array([1, 2, 3, 4])
np.broadcast_to(x, (3, 4))
# [[1 2 3 4]
#  [1 2 3 4]
#  [1 2 3 4]]
```



##### np.delete()

index를 이용해서 인자로 받은 array의 특정 부분을 delete

```python
np.delete(arr, indices, axis = None)
```

`axis = None` 일 경우 arr를 1차원으로 변환된 flattened로 reshape 후 받은 index를 삭제한다. 



```python
a = np.arange(12).reshape(3,4)
#[[ 0  1  2  3]
# [ 4  5  6  7]
# [ 8  9 10 11]]
```

```python
print(np.delete(a, 5))
# [ 0  1  2  3  4  6  7  8  9 10 11]  flattened에서 6번째 index 삭제
```

```python
print(np.delete(a, 1, axis=1))
# [[ 0  2  3]
#  [ 4  6  7] 		axis = 1 기준 1번째 index 삭제
#  [ 8 10 11]]
```

