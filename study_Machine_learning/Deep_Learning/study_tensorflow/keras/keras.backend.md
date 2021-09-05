# keras.backend



### shape

tensor의 shape을 반환한다.

```python
from tf.keras.backend import shape
x = shape(x)
```





### int_shape

tensor의 shape을 int 또는 None 항목의 tuple로 반환한다.

```python
from tf.keras.backend import int_shape
x = int_shape(x)
```





### switch

```python
from tf.keras.backend import switch

output = switch(condition, then_expression, else_expression)
```

`condition` : True or False를 반환하는 조건. 	int or boolean

`then_expression` : condition = True일때 실행되는 function

`else_expression` : condition = False일때 실행되는 function





#### mean

```python
from tf.keras.backend import mean

output = mean(input)
```

