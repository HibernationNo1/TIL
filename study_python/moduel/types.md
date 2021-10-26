# types



### SimpleNamespace

namespace attribute에 access와 완전한 표현(repr)을 제공하는 간단한 클래스

글 쓴 본인이 쉽게 읽고 쓸 수 있는 instance로 dict대신에 사용하거나, inherit하여 사용한다.

```python
from types import SimpleNamespace
```



- dict대신에 사용

  ```python
  data = SimpleNamespace(a = 1, b = 2)
  print(data) 	# namespace(a=1, b=2)
  data.c = 3
  print(data) 	# namespace(a=1, b=2, c=3)
  ```

  

- inherit

  ```python
  class DataBad(SimpleNamespace):
  	...
  data_bag = DataBad(a = 1, b = 2)
  print(data_bag)  	# DataBad(a=1, b=2)
  data_bag.c = 3
  print(data_bag)		# DataBad(a=1, b=2, c=3)
  ```

  

값을 불러낼 때 attribute를 호출하듯 불러낸다.

```python
print(data_bag.c)
```



#### set()

`=` 을 이용한 등식 말고도 `.set()`  method를 통해 새로운 값을 추가할 수 있다.

```python
data_bag.set(tmp = ["tmptmp"])
```

