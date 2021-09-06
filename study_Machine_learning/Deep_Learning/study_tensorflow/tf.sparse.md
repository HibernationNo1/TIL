# tf.sparse

SparseTensor : 특정 값을 제외하곤 전부 0인 tensor



### SparseTensor

Represents a sparse tensor.



```python
tf.sparse.SparseTensor(indices, values, dense_shape)
```

`indices` : `values`를 위치시키기 위한 indeices

`values` : 0이외의, 표현할 값

`dense_shape` : SparseTensor의 shape



```python
sp_input = tf.SparseTensor( dense_shape=[3, 5], values=[7, 8, 9], 
                           indices =[[0, 1], [0, 3], [2, 0]])

sp_input
# [[0, 7, 0, 8, 0],
#  [0, 0, 0, 0, 0]
#  [9, 0, 0, 0, 0]]

```





### to_dense

Converts a `SparseTensor` into a dense tensor.

```python
dense_output = tf.sparse.to_dense(sp_input, 
                                  default_value=1, 
                                  validate_indices=True, name=None )
```

`sp_input` : SparseTensor

`default_value` : scalar value, 0인 값을 대신해서 채울 값

> default = None  (0), 설정 안하면 다 0으로 채워짐

```python
dense_output
# [[1, 7, 1, 8, 1],
#  [0, 1, 1, 1, 1]
#  [9, 1, 1, 1, 1]]
```

