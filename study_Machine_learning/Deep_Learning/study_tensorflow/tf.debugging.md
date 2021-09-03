# tf.debugging



### Assert

tensor type에 대해서 예외적인 사항이 없는지 확인

condition가 False인 경우 data에 대한 tensor 항목을 return

```python
import tensorflow as tf
from tf.debugging import Assert

asserts = [Assert(condition, data, summarize=None, name=None)]
```

- `condition` : `True` or `False`

  > `True` or `False`를 반환하는 tf. 함수를 통해 data의 조건을 명시
  >
  > ex) 
  >
  > `tf.greater(tf.shape(proposals)[0], 0)`  : proposals의 첫 번째 dim의 크기가 0보다 크지 않다면 False

- `data` : condition가 False인 경우 tensor항목을 return할 tensor data



```python
# proposals : [tmp1, tmp2, tmp3], tensor
asserts = [ tf.Assert(tf.greater(tf.shape(proposals)[0], 0),
                [proposals], name="roi_assertion"), 
          ]
```

> tmp1 > 0 이 아닌 경우 proposals의 항목 return