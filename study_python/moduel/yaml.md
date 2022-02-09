# yaml, yacs

```
$ pip install pyyaml, yacs
```



```python
import yaml, yacs
```



#### load

- `load(f, Loader=)`

  - `Loader = yaml.FullLoader` 

  - `Loader = yaml.SafeLoader` 

    > ```python
    > yaml.load(f, Loader=yaml.FullLoader) 
    > == 
    > yaml.safe_load(f)
    > ```

```python
with open('test.yml') as f:
    test_yaml = yaml.load(f, Loader=yaml.FullLoader)
    print(test)
```



`test.yml`의 구조가 아래와 같다면

```
main_name:
	sub_name_1: "foo"
	sub_name_2: "bar"
	number : 3
```

`print(test)` 의 출력은 다음과 같다.

```python
{'main_name' : ['sub_name_1' : 'foo', 'sub_name_2' : 'bar', 'number' : 3]}
```

> dict로 출력됨





#### yacs _ CfgNode

`yaml.load`를 통해 생성된 instance를 출력하면 dict형식으로 출력되지만, 정리되지 않은 채 출력되기 때문에 읽기에는 적합하지 않다. 이를 위해 yacs를 사용한다.

```python
from yacs.config import CfgNode
import yaml

with open('test.yml') as f:
    test_yaml = yaml.load(f, Loader=yaml.FullLoader)

cfg = CfgNode(init_dict=more_cfg)
print(cfg) # 더 깔끔하게, 계층간 표현으로 출력됨
```

