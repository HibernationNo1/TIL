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



#### Condition

```python
@dsl.pipeline(name="hibernation_project")
def project_pipeline(input):    
    _exam_1_op = exam_1_op()
    
    with dsl.Condition(input == True) :  
        _exam_2_op = exam_2_op()
        
```

- `input == True` 을 할 때 True는 bool type으로 인식하지 않고 str로 인식한다.( 'True')

- 특정 component의 output으로 condition의 조건을 찾으면 AttributeError발생.

  ```python
  with dsl.Condition(_exam_op.output == True) : 
  ```

  ```
  AttributeError: 'bool' object has no attribute 'operand1'
  ```

  



### RUN

#### Condition

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



#### ParallelFor

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



### Volume

#### VolumeOp

```python
import kfp.dsl as dsl

@dsl.pipeline(name="exam")
def exam_pipeline(input_1: int, input_2: str):  
    vop = dsl.VolumeOp(name="pipeline-volume",
                       resource_name="pipeline-pvc",
                       modes=dsl.VOLUME_MODE_RWO,
                       size="10Gi")
    
    _exam_op = exam_op(cfg_train).add_pvolumes({'/mount_path': vop.volume})
```

- `name`: volume의 name   `volume_name`은 없는 arg

- `resource_name`: 생성될 PVC의 원하는 이름

- `modes`: Access Mode 결정

  - `dsl.VOLUME_MODE_RWO`: ReadWriteOnce
  - `dsl.VOLUME_MODE_RWM`: ReadWriteMany
  - `dsl.VOLUME_MODE_ROM`: ReadOnlyMany

- `storage_class`: PVC에 사용할 storage_class결정

  > default: `None` == `local_path`

- `size` : volume의 크기



**tip)**

- pipeline function안에서 위 PVC가 선언되면 kubeflow dashboard의 volumes에 pvc가 생성된 것을 확인할 수 있고, `/opt/local-path-provisioner`에서 `~~~pipeline-pvc`라는 dir을 확인할 수 있다.

- 같은 name의 volume은 중복되어 create될 수 없으며, 한 번 생성된 `VolumeOp`를 그대로 두고 사용하게 된다. 

  이 때 modes, size같은 부분을 변경하여 선언하여도 기존 생성된 volume에 변경점 없이 그대로 사용된다.

