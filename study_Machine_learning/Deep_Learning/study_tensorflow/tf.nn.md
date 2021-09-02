# tf.nn



#### tf.nn.l2_loss()

```python
tmp = tf.nn.l2_loss(
    t, name=None
)
```

- `tmp` : sum(t ** 2) / 2
- `t` : Tensor,  Must be one of the following types: `half`, `bfloat16`, `float32`, `float64`.





#### tf.nn.top_k

```python
tmp = tf.nn.top_k(input, k = )
```

`k` : threshold number of top value



##### values

value확인할때 사용

```python
result = tf.math.top_k([1, 2, 98, 1, 1, 99, 3, 1, 3, 96, 4, 1],
                        k=3)
result.values.numpy() # [99, 98, 96]
```



##### indices

index확인할때 사용

```python
result.values.numpy()	# [5, 2, 9]
```

