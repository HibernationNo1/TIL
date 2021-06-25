# numpy 



##### np.expand_dim()

dimension을 1 expand한다.

```python
np.expand_dim(data, axis = )
```

> `data` : input data
>
> `axis` : 몇 번째 dimension을 push해서 expand할지 결정
>
> ```python
> data.shape # (28, 28)
> np.expand_dim(data, axis = 0) # data.shape = (1, 28, 28)
> np.expand_dim(data, axis = 1) # data.shape = (28, 1, 28)
> np.expand_dim(data, axis = 2) # data.shape = (28, 28, 1)
> np.expand_dim(data, axis = -1) # data.shape = (28, 28, 1)
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

