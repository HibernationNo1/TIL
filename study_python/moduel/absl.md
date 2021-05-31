# absl

```python
pip install absl-py
```





## flags

터미널로 python 코드를 호출할 때 고정값으로 되어 있는 기본적인 data를 편리하게 사용할 수 있다.

```python
from absl import flags

FLAGS = flags.FLAGS

flags.DEFINE('name', default = 'Value', help = 'explain')

print(FLAGS.name)
```

`DEFINE` : 함수 이름. 관리할 argument의 보통 data type을 명시함

`'name'` : argument로 관리할 변수 이름

`'Value'` : 코드 실행 시 argument에 주어지는 값이 없으면 사용할 default value

`'explain'` : 해당 argument에 대한 설명

`FLAGS` : flags에 의해 define된 변수를 호출할때 사용할 instance



사용 예시

**ex.py**

```python
from absl import flags

FLAGS = flags.FLAGS

flags.DEFINE_integer('foo', default = 135, help = 'just explain')
print(FLAGS.foo)  # 135
```



**터미널에서**

```
$ python3 ex.py --foo=150 
```

> ex를 호출하며 foo라는 data에 150을 할당



