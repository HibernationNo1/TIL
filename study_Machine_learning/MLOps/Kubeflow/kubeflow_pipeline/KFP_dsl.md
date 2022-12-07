{:toc}



# KFP_dsl

### pipeline

```python
import kfp
from kfp.dsl import pipeline

@pipeline(name="tmp")
def tmp():
	return None        
```

`name` : pipeline의 name





### Condition

if문처럼 사용해서 component의 실행 여부를 분기처리 할 수 있다.

```python
from kfp import dsl
with dsl.Condition(조건):
    다음 component
```



```python
import kfp
from kfp.components import create_component_from_func
from kfp import dsl

small_num_op = create_component_from_func(...)		# example
large_num_op = create_component_from_func(...)

@dsl.pipeline(name="conditional pipeline", dsecription = "Small or Large")
def conditional_pipeline():
    import random
    number = random.randint(1, 100)
    
    with dsl.Condition(number < 30) : 	# 조건이 맞는 경우에만 실행됨
        small_num_op(number)
    with dsl.Condition(number > 30) : 
        large_num_op (number)
        
```



### ParallelFor

다수의 동일한 component를 병렬로 실행할 수 있다.

```python
from kfp import dsl
with dsl.ParallelFor(list) as ele:
    다음 component
```



```python
import kfp
from kfp.components import create_component_from_func
from kfp import dsl

exam_op = create_component_from_func(...)


@dsl.pipeline(name="conditional pipeline", dsecription = "Small or Large")
def conditional_pipeline():
    import random
    random_list = []
    for i in range(10):
        random_list.append(random.randint(1, 100))
    
    # type(random_list) == list
    with dsl.ParallelFor(random_list) as item: 		# for문처럼 각각의 item을 받아서 처리
       exam_op(item)
        
```





### VolumeOp

kubernetest PersistentVolumeClaim를 생성하여 volum mount를 진행한다.

```python
import kfp
import kfp.dsl as dsl

from test_1.test_1 import test_1_op
from test_2.test_2 import test_2_op   

@dsl.pipeline(name="Data test example")
def data_example(value_1: int, value_2:int, value_3 : int):
    # pipeline데코된 함수에서 input으로 받는 값은 type을 명시해주어야 한다.
    
    exam_vop = dsl.VolumeOp(
        name="exam-volume",
        resource_name="exam-pvc",
        modes=dsl.VOLUME_MODE_RWM,
        size="1Gi")
    # 전역에 선언 후 instance만 가져오면 안됨
    
    _test_1 = test_1_op(value_1, value_2, value_3)
    
    _test_2 = test_2_op(_test_1.outputs["data_output_dir"]).add_pvolumes({"/test_2": exam_vop.volume})
```

- `add_pvolumes` : `func_to_container_op` 의 instance에 method chaining방식으로 호출하여 특정 path를 mount



