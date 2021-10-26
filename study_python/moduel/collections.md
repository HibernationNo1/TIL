# collections

### UserDict

```python
from collections import UserDict
```

더 위운 dictionary sub-calssing을 위해 dictionary instance를 감싼다.

하나의 dict가 선언된다고 보면 된다.

```python
class foo(UserDict):   
```



**e.g.**

> ```python
> class _DatasetCatalog(UserDict): # UserDict을 상속
>     # UserDict을 상속받아 하나의 dictionary가 만들어졌다.
> 
>     def register(self, name, func):
>         """
>         Args:
>         	self : dict라고 생각하면 됨
>             name (str): the name that identifies a dataset, e.g. "coco_2014_train".
>             func (callable): a callable which takes no arguments and returns a list of dicts.
>                 It must return the same results if called multiple times.
>         """
>         
>         # func이 호출 가능한 function인지 확인
>         assert callable(func), "You must register a function with `DatasetCatalog.register`!"
>         
>         # dict안에 name이라는 key가 이미 존재하는지 확인
>         assert name not in self, "Dataset '{}' is already registered!".format(name)
> 
>         self[name] = func
> ```
>
> 