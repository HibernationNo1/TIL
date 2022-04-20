# logging



 logging은 소프트웨어가 작동 중일 때 발생하는 여러 ‘예외 사건’을 추적한다.

예외 사건을 레벨에 따라 중요도를 결정하여 구분한다.



- Logger 오브젝트는 `logging.getLogger(name)` method 를 통해 사용할 수 있다.

  - `name`이 주어진 경우, 해당 이름에 해당하는 logger를, `name`이 주어지지 않은 경우 root logger를 전달받는다.

  - `name`은 마침표(`.`)로 구분되는 계층구조를 가지고 있다.

    > 예를 들어, `getLogger('foo.bar')`는 `getLogger('foo')`의 자식 logger를 반환한다.



#### logging.INFO

프로그램의 정상 작동중에 발생하는 level 출력

> ex 
>
> ```
> print(logging.INFO) # 20을 출력
> ```
>
> 프로그램이 이상이 없을 땐 logging.INFO는 항상 20을 출력한다.



### create_logger

예외 사건에 대한 log를 저장한다.

```python
from logger import create_logger
logger = create_logger(output_dir=config.OUTPUT, dist_rank=dist.get_rank(), name=f"{config.MODEL.NAME}")
```

- output_dir : log를 저장할 dir path
- dist_rank : 사용된 GPU의 rank (단일 GPU라면 dist_rank = 0)
- name : `create_logger` 안의 `getLogger`의 argument로 사용될 name



#### logger

##### isEnabledFor

```python
logger.isEnabledFor(logging.INFO)
```

level을 인자로 받는다. 정상 작동중인 level이면 `True`를, 아니면 `False`을 반환



##### info

`print()`와 같은 역할을 하지만, **년-월-일 시:분:초 사용자,  어느 file의 몇 line**인지 표시하며 출력한다.

```python
logger.info("test!")
```

> ```
> [2022-04-20 17:43:13 ITC](main.py 93): INFO test!
> ```

