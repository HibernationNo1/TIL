# tensor

#### to()

```python
is_cuda = torch.cuda.is_available()
device = torch.devive('cuda' if si_cuda else 'cpu')

for data, target in train_loder:
    data = data.to(device)
    target = target.to(dvice)
```

data를 CUDA에 최적화된 형태로 convert한다.





#### contiguous()





#### view()

tensor의 matrix모양을 변경하여 return한다.

원본 data의 메모리 주소를 공유한다.

**contiguous tensor**에서만 사용할 수 있다.

```python
res = tensor.view(shape)
```

- `shape = [-1, n]` 이면 (?, n)의 size로 알아서 reshape된다.



##### view_as()

```python
foo.view_as(bar)
```

foo라는 tensor의 shape의 bar라는 tensor의 shape으로 변경



#### transpose()

tensor의 matrix모양을 변경하여 return한다.

원본 data의 메모리 주소를 공유한다.

```python
res = tensor.transpose(res_shape)
# res_shape == res.shape
```

> 보통 `(batch_size, hidden_dim, input_dim)` 을 `(batch_size, input_dim, hidden_dim)` 으로 바꿔주는 작업을 할 때에 `transpose` 를 사용한다.



#### reshape()

tensor의 matrix모양을 변경하여 return한다.

단, 원본 data를 copy해서 return한다.

> `reshape() == contiguous().view()` 와 같다.



#### data

`.to(divice)` 로 인해 tensor에 알맞는 형태로 변한 instance를 다시 `data`의 형태의 바꿔준다.

> `torch.cuda.is_available()` == True이면 `to(divice)`는 `.Tensor`와 같다.

- `data` : list나 Numpy의 ndarray 등 array류의 데이터

```python
is_cuda = torch.cuda.is_available()
device = torch.device('cuda' if is_cuda else 'cpu')

model = model.to(divice)
output = model(train_data).data
```





#### math

tensor에 알맞는 operation을 진행한다.

##### max()

```python
tensor.max(dim = )
```

- `dim` : max를 적용할 dimension

  > - 명시 안하면 전체 dimension에 대해서 실행 `tensor.max()`
  >
  > - `dim = 0` 이면 
  >
  >   `tensor.max(dim = 0)[0]` : 각 dimension에서 max값을 return
  >
  >   `tensor.max(dim = 0)[1]` : 각 dimension에서 max값의  index를 return
  >
  >   (argmax)

 

##### min()

```python
tensor.min(dim = )
```





##### mean()

```python
tensor.mean(dim = )
```



##### sum()

```python
tensor.sum(dim = )
```



##### eq()

tensor배열과 data배열이 일치하는지 검사

```python
res = tensor.eq(data)
```

일치하면 `True`, 일치하지 않으면 `False`반환

