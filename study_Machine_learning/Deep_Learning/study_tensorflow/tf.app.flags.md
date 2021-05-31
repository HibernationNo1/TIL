# tf.app

## tf.app.flags

Tensorflow 에서 제공하는 flags 객체를 사용하면 고정값으로 되어 있는 기본적인 data를 편리하게 사용할 수 있다.

flags 객체는 int, float, boolean, string 의 값을 저장하고, 터미널로 file 실행 시 해당 data를 argument로 가져다 사용하기 쉽게 해준다.

```python
flags = tf.app.flags
FLAGS = flags.FLAGS
```

`flags` : method를 define할 instance

`FLAGS` : parameter를 define할 instance



##### **flags**

```python
flags.DEFINE('name', 'Value', 'explain')
```

`DEFINE` : 함수 이름. 관리할 argument의 보통 data type을 명시함

`'name'` : argument로 관리할 변수 이름

`'Value'` : 코드 실행 시 argument에 주어지는 값이 없으면 사용할 default value

`'explain'` : 해당 argument에 대한 설명



##### **FLAGS**

```python
FLAGS.name = 'test'
```



**예시**

ex.py

```python
import tensorflow as tf
flags = tf.app.flags
FLAGS = flags.FLAGS


flags.DEFINE_integer('learning_rate', 0.02, 'initial learning rate')
flags.DEFINE_string('name', 'test', 'train or validation or test')

print(FLAGS.learning_rate) # 0.02
print(FLAGS.name) # 'test'
```

터미널에서

```
$ python3 ex.py --learning_rate=0.01 --name=train
```





