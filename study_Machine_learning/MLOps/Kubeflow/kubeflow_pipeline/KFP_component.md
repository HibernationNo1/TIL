# component

[공식](https://kubeflow-pipelines.readthedocs.io/en/stable/source/kfp.components.html)

pipeline을 구성하는 component를 만들 때 사용하는 package

```python
import kfp.components as components
```



## component

### create_component_from_func

(경량 component)

python function을 component로 convert하고 task fctory를 return한다.

```python
func_op = components.create_component_from_func(func = ,
                                               base_image =,
                                                output_component_file = ,
                                                packages_to_install = ,
                                                annotations = 
                                               )
```

- `func` : component로 convert할 function

- `base_image` : component가 동작할 특정한 custom Docker container의 images

- `output_component_file` : 만들어질 component의 정의가 저장된 file (.yaml format)

  `func_name.component.yaml`

- `packages_to_install` : docker안에서 RUN pip install으로 저장되지 않는 package는 여기서 명시하여 install하면 간편 (type : list)

  `packages_to_install = [opencv-python, numpy, 'pandas==0.24']`

  



decorator형태로도 사용 가능

```python
@create_component_from_func
def add_op(a: float, b: float) -> float:
    """Returns sum of two arguments"""
    return a + b
```



#### func

해당 `create_component_from_func` 의 `func` argu로 할당되는 function은 몇 가지 규칙을 따라야 한다.

1. input argument가 API를 통해 받은 data라면, 해당 data는 type을 명시해주어야 한다.
2. 해당 function에 return값이 존재한다면, 반드시 해당 return값의 type을 명시해주어야 한다.
3. 해당 function에서 사용하는 package를 import할 때는 function안의 scope안에서 해야 한다.

```python
import kfp
from kfp.components import OutputPath, create_component_from_func

def data_test_1(value_1: int, value_2: int, value_3 : int,		# 규칙 1. 
           data_output_dir_path: OutputPath("dict")): -> int:	# 규칙 2.
    
    import json
    import os
    import numpy as np
    # 규칙3. 모든 import는 해당 funtion안에서 선언되어야 한다.
    
    class NpEncoder(json.JSONEncoder):
        def default(self, obj):
            if isinstance(obj, np.integer):
                return int(obj)
            elif isinstance(obj, np.floating):
                return float(obj)
            elif isinstance(obj, np.ndarray):
                return obj.tolist()
            else:
                return super(NpEncoder, self).default(obj)
        
    tmp_np = np.ones(shape = (value_1, value_2, value_3))
    data_dict = {"1" : tmp_np, "2" : 2}   
    
    json.dump(data_dict, open(data_output_dir_path, "w"), indent=4, cls=NpEncoder) 
    
    reutrn 356	# 예시 return

data_test_1_op  = create_component_from_func(
            func =data_test_1,
            base_image = 'hibernation4958/test:0.1',		# image명시, pip install포함
            output_component_file="test_1.component.yaml")   
```



만약 return값이 2개 이상이라면 `NameTuple` 을 사용해서 명시해야 한다.

```
NamedTuple('Output', [("{discription}", type), ('discription', type)])
```

각각의 return값에 대한 discription과 type을 `'key' : value`형식으로 명시한다.

> 위의 code의 return 값이 아래와 같다면
>
> ```python
> 	return 365, "exam"
> ```
>
> 명시는 아래처럼
>
> ```python
> from typing import NamedTuple
> 
> def data_test_1(value_1: int, value_2: int, value_3 : int,		# 규칙 1. 
>         data_output_dir_path: OutputPath("dict")) -> NamedTuple('Output', [("day", int), ('example', str)]):	# 규칙 2.
> ```



- return으로 내보낸 값은 `_data_test_1_op.outputs['outputs']` 으로 call할 수 있다.

```python
@dsl.pipeline(name="hibernation_project")
def project_pipeline(input_mode : str, input_dict : dict):
    _data_test_1_op = data_test_1_op(input_dict)
    # _data_test_1_op.outputs['outputs']
```





### create_component_from_func_v2

(경량 component version 2)

python function을 component로 convert하고 task fctory를 return한다.

> 아직 이해가 잘 안됨. 





## Input

component로 만들어진 finction은 input의 type과 format에 따라 명시가 달리되어야 한다.

### basic

input argument가 API를 통해 받은 data라면, 해당 data는 type을 명시해주어야 한다.

```python
import kfp
import kfp.components as components

def exam(value_1: int, value_2: str, value_3 : dict):		# type명시
    pass


exam_op = components.create_component_from_func(func = exam)
```



### InputPath

커다란 file을 input으로 받을 땐 해당 file의 path를 명시하여 받는다.

이는 이전에 `components.OutputPath` 로 인해 docker container 안에 크기가 큰 file이 만들어진 적이 있을 경우에, 해당 file을 load하고자 할 때 사용한다.

> `components.OutputPath` 을 먼저 확인

```python
from kfp.components import InputPath
def exam(args : dict, 
            exam_1: InputPath("dict"),
            exam_2: InputPath("dict")):
    
         
```

> 





## Output

### OutputPath



```python
from kfp.components import OutputPath

def exam(args : dict,
            exam_1_path: OutputPath("dict"),
            exam_2_path: OutputPath("dict")):   
    
    import json
    exam_dict_1 = {'one' : 1}
    json.dump(exam_dict_1, open(exam_1_path, "w"), indent = 4)
    
    exam_dict_2 = {'two' : 2}
    json.dump(exam_dict_2, open(exam_2_path, "w"), indent = 4)
    
exam_op = create_component_from_func(func = exam,
                                        base_image = SETUP_IMAGE)

```

>`exam_1_path`, `exam_2_path` : 이름은 항상 `_path`라는 단어로 끝나야 한다.
>
>`OutputPath("dict")` : `"dict"` 는 개발자가 알기 쉽도록 명시해놓은 것일 뿐, 실제 `exam_1_path` 는 str로서 ` {workspace}/outputs/exam_1/data` 의 값을 가지고 있다. 



```python
@dsl.pipeline(name="hibernation_project")
def project_pipeline(input_mode : str, input_dict : dict):
    _exam_op = exam_op(input_dict)
    # _exam_op.outputs["exam_1"], _exam_op.outputs["exam_2"]
```

>위에서 `OutputPath`로 저장한 file은 해당 name에서 뒷 부분 `_path`를 제외한 이름을 key로 가진 `.outputs` 함수로 불러낼 수 있다. 







## pipeline exam



#### exam

##### 1

`test_1/test1.py`

```python
import kfp
from kfp.components import OutputPath, func_to_container_op

def data_test_1(value_1: int, value_2: int, value_3 : int,
           data_output_dir_path: OutputPath("dict")):
    
    import json
    import os
    import numpy as np
    # 모든 import는 해당 funtion안에서 선언되어야 한다.
    
    class NpEncoder(json.JSONEncoder):
        def default(self, obj):
            if isinstance(obj, np.integer):
                return int(obj)
            elif isinstance(obj, np.floating):
                return float(obj)
            elif isinstance(obj, np.ndarray):
                return obj.tolist()
            else:
                return super(NpEncoder, self).default(obj)
        
    tmp_np = np.ones(shape = (value_1, value_2, value_3))
    data_dict = {"1" : tmp_np, "2" : 2}   
    
    json.dump(data_dict, open(data_output_dir_path, "w"), indent=4, cls=NpEncoder) 

test_1_op  = func_to_container_op(
            func =data_test_1,
            base_image = 'hibernation4958/test_4:0.1',		# image명시, pip install포함
            output_component_file="test_1.component.yaml")    
```

> import를 함수 외부(전역 scope)에서 하고자 하는 경우, base_image로 사용되는 Dorker 이미지에 `pip install numpy`와 같이 install을 넣어줘야 한다.
>
> `hibernation4958/test_4:0.1` : 
>
> ```yaml
> FROM python:3.8
> ENV PYTHONUNBUFFERED 1
> 
> RUN pip install numpy
> ```
>
> ```
> $ docker build -t test_1 ./test_1
> $ docker tag test_1:latest hibernation4958/test_1:0.1
> $ docker push hibernation4958/test_1:0.1
> ```



`test_2/test2.py`

```python
import kfp
from kfp.components import InputPath, OutputPath, func_to_container_op

def data_test_2(data_input_dir_path: InputPath("dict")) -> list :
    # return이 있을 땐 해당 return값의 type명시
    # return값은 .output으로 반환 가능
    
    
    import json
    import numpy as np
    import glob
    # 모든 import는 해당 funtion안에서 선언되어야 한다.
    
    
    with open(data_input_dir_path, "r", encoding='utf-8') as f:
        data = json.load(f)
            
    img = data["1"]    
    img = np.array(img)
    
    file_list = glob.glob("/test_2")
	for file in file_list:
        print(f"file : {file})
    
    return list(img.shape)

test_2_op  = func_to_container_op(
            func =data_test_2,
            base_image = 'hibernation4958/test_2:0.2',
            output_component_file="test_2.component.yaml")
```

> ` InputPath("dict")` : file하나의 path
>
> - `OutputPath("dict")` 로 인해 만들어진 file하나의 path를 다시 받을 때 사용
> - `"dict"` : file을 load했을 때 얻는 변수의 type
> - `"metrics"` 형태도 있다. 자세한 설명은 아래
>
> `hibernation4958/test_2:0.2`
>
> ```yaml
> FROM python:3.8
> ENV PYTHONUNBUFFERED 1
> 
> 
> RUN pip install numpy
> ```
>
> ```
> $ docker build -t test_2 ./test_2
> $ docker tag test_2:latest hibernation4958/test_2:0.2
> $ docker push hibernation4958/test_2:0.2
> ```



`./pipeline.py`

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
    # VolumeOP는 미리 선언
    
    
    _test_1 = test_1_op(value_1, value_2, value_3)
    
    _test_2 = test_2_op(_test_1.outputs["data_output_dir"]).add_pvolumes({"/test_2": exam_vop.volume})
    # test_1_op의 input중 data_output_dir_path가 OutputPath("dict")형으로 있기 때문에, outputs의 key값은 _path를 뺀  data_output_dir가 된다.
    # add_pvolumes를 통해 특정 path를 mount
    
    print(_test_2.output)	# data_test_2의 return값


    
if __name__=="__main__":
    kfp.compiler.Compiler().compile(
    	data_example,
        "./data_test.yaml"
    	)
    # 해당 pipeline.py를 실행하면 data_test.yaml이 생긴다.
    
```

> **실제 code를 compile할 땐 주석에도 한글 자체가 없어야 한다.**
>
> compile code를 삭제하고 명령어로 pipeline yaml을 만드려면
>
> `dsl-compile --py add.py --output add_exam.yaml`





##### 2





1. case 1: return single value, type of `<T>`

   ```pytohn
   from kfp.components import func_to_container_op   
   # I make component using `kfp.components.func_to_container_op`
   
   def case_1(value_1: int, value_2: int) -> int:  # to use return, write '-> {type}' 
       result = value_1 + value_2		
   
       return result    # it can be int, float, bouble, str, bool, .... 
   
   case_1_op = func_to_container_op(func = case_1,
                                    base_image = 'case_1/tag:0.1',
               					 output_component_file="case_1.component.yaml")
   ```

2. case 2: return multiple value

   ```pytohn
   from kfp.components import func_to_container_op   
   from typing import NamedTuple
   
   # If there are multiple return values, wrap them in a tuple.
   # And use `NamedTuple`
   def case_2(value_1: int) -> NamedTuple('Output', [("key_of_foo", int), 
                                                     ('key_of_bar', str),
                                                     ('key_of_baz', bool)]):
       foo = value_1 		# int
       bar = "2"	        # str
       baz = True	        # bool
       
       return (foo, bar, baz)      #  wrap them in a tuple.
   
   case_2_op = func_to_container_op(func = case_2,
                                    base_image = 'case_2/tag:0.1',
               					 output_component_file="case_2.component.yaml")
   ```

3. case 3: save data to file using `kfp.components.OutputPath`.

   ```pytohn
   def case_3(value_1: str, value_2: int, value_3: bool,
       	   file_path: OutputPath("dict")):      
       	   # 'OutputPath' has a naming rule: it must end with `_path`.
       
       import json
       exam_dict = dict(one = value_1,
                  		 two = [value_2, value_3])
       
       json.dump(exam_dict, open(file_path, "w"), indent=4) 
   	
   case_3_op = func_to_container_op(func = case_3,
                                    base_image = 'case_3/tag:0.1',
               					 output_component_file="case_3.component.yaml")
   ```

4.  case 4: load data from file using `kfp.components.InputPath`.

   ```pytohn
   def case_4(data_input: InputPath("dict")): 
       import json
       
       with open(data_input, "r", encoding='utf-8') as f:
           data = json.load(f)
       
       print(data)     # {'one': '2', 'two': [1, True]}
   	
   case_4_op = func_to_container_op(func = case_4,
                                    base_image = 'case_4/tag:0.1',
               					 output_component_file="case_4.component.yaml")
   ```

   

**pipeline**

```python
import kfp.dsl as dsl

@dsl.pipeline(name="example")
def data_example(value_1: int, value_2:int):
    _case_1_op = case_1_op(value_1, value_2)
    
    # case of input from single return
    _case_2_op = case_2_op(_case_1_op.output)   
    
    # case of input from multi value return. input value using key.
    # key name must match each key in the NamedTuple.
    _case_3_op = case_3_op(_case_2_op.outputs['key_of_bar'], _case_2_op.outputs['key_of_foo'], _case_2_op.outputs['key_of_baz'])
    
    # case of input from path. input path using key.
    # The key name must match the OutputPath name without '_path'.
    _case_4_op = case_4_op(_case_3_op.outputs["file"])  
```







#### metrics

> 동작 안하는거 확인

component에서 metrics를 남길 수 있다. (excel처럼)

InputPath, OutputPath에 metrics를 명시

1. metrics는 dict으로, `key : metrics`, `value : list of dict()` 으로 한다.

2. list의 각 dict()는 반드시 `name`, `number_Value` 라는 key를 가지고 있어야 한다.
   - `"format"` : 어떤 형태로 출력할 것인지. excel의 표시 형식과 같다.
     - default : "RAW"
     - "PERCENTAGE" : %

##### exam_metrics★

export_metrics.py

```python
import kfp
from kfp.components import OutputPath, create_component_from_func

@create_component_from_func
def export_metric_op(mlpipeline_metric_path:OutputPath("metrics")):
    import json
    metrics = {}
    metrics["metrics"] = []
    metrics["metrics"].append(dict("name" : "name_1", "number_Value" : 0.8))
    metrics["metrics"].append(dict("name" : "name_2", "number_Value" : 0.9, "format":"PERCENTAGE"))
    # "format" : 어떤 형태로 출력할 것인지. excel의 '표시' 형식과 같다.
    
    with open(mlpipeline_metric_path, "w") as f:
        json.dump(metrics, f)

@kfp.dsl.pipeline(name"Export Metrics Example")
def export_metrics_pipeline():
    write_file_task = export_metric_op()

if __name__=="__main__":
    kfp.compiler.Compiler().compile(export_metrics_pipeline, 
                                    "./export_metrics_pipeline.yaml")
```

> |                  | name_1 | name_2  |
> | ---------------- | ------ | ------- |
> | export_metric_op | 0.800  | 90.000% |
>
> 위 처럼 metrics 형태로 data를 넘기고 받을 수 있다.





