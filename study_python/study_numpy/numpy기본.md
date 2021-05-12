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





##### np.argmax()

ndarray안의 elements 중 max한 값을 return

```python
np.argmax(data)
```



##### np.squzzez()

ndarray안의 dimensions 중 1의 shape을 가진 dimensions를 delete해서 return

```python
data = np.squzzez(data)
```

