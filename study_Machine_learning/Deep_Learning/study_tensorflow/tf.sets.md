# tf.sets

### intersection

두 input의 element 교집합을 구한다.

> 단, 마지막 dimension에서 계산이 이루어진다.
>
>  a, b가 0차원이라면 
>
> a = tf.expand_dims(a, 0), 	b = tf.expand_dims(b, 0) 을 통해 최소한 1차원으로 올려주어야 한다.

```py
tf.sets.intersection(a, b, validate_indices=True)
```

