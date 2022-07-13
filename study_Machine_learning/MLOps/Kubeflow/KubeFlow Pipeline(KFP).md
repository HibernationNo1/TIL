# KubeFlow Pipeline(KFP)

#### Introduction

- component : 재사용 가능한 형태로 분리된 하나의 작업 단위

  > resource : Pod

  kfp sdk를 사용하여  component를 구현하면, 그 component를 사용하는 pipeline을 compile했을 때 생성되는 workflow의 yaml file의 `spec.templates` 에 대항 components를 감싼 (containerized)부분이 추가된다.

  하나의 component는 k8s상에서 하나의 독립적인 pod로 생성되어 component내부에 작성된 code를 components dectorator에 작성한 base_image환경에서 실행하게 된다.

  > base_image 지정을 통해 항상 동일한 환경에서 정해진 code가 실행되는 것을 보장할 수 있다.
  >
  > 따라서 하나의 pipeline내에서 연속된 component라고 하더라도 memory를 공유하는 일은 일어나지 않으며, 일반적으로 서로 **다른 component간의 data공유는 input/output변수 혹은 file path로 넘겨주는 방식을 사용한다.**

- pipeline : 여러 component들의 연관성, 순서에 따라 연결지은 그래프(DAG)

  > resource : Workflow
  >
  > `Workflow` : 여러 개의 container들을 정해진 순서에 따라 실행시키고, input/output을 전달하는 것을 정의한 DAG

  kfp sdk를 사용하여 pipeline을 구현한 뒤 `kfp의 dsl-compile` 또는 `kfp.compiler.Compile()`명령을 사용해 compile하면 k8s가 이해할 수 있는 형태의 yaml(kind : Workflow)이 생성된다.

  >```
  >$ dsl-compile --py {name}.py --output {yaml_name}.yaml
  >```
  >
  >

  

일반적인 ML의 pipeline

1. data create
2. data Analyzer
3. data Transformer
4. Trainer
5. Predictor



#### envs

pip install

```
$ pip install kfp
```

check

```
$ pip list | grep kfp
```



minikube

```
$ minikube status
```

```
type: Control Plane
host: Running
kubelet: Running
apiserver: Running
kubeconfig: Configured
```

> 아래처럼 출력 될 경우
>
> ```
> type: Control Plane
> host: Stopped
> kubelet: Stopped
> apiserver: Stopped
> kubeconfig: Stopped
> ```
>
> minikube start 
>
> ```
> minikube start --driver=docker \
>  --cpus='4' --memory='7g' \
>  --kubernetes-version=v1.19.3 \
>  --extra-config=apiserver.service-account-signing-key-file=/var/lib/minikube/certs/sa.key \
>  --extra-config=apiserver.service-account-issuer=kubernetes.dafault.svc
> ```

```
$ kubectl get nodes
```

```
NAME       STATUS   ROLES    AGE   VERSION
minikube   Ready    master   29h   v1.19.3
```

kubeflow namespace의 resource check

```
$ kubectl get pod -n kubeflow
```



### component

#### create_component_from_func

function을 하나의 component로 만들 수 있다.

```python
from kfp.components import create_component_from_func
```

decorator로도 사용할 수 있으며, function으로 호출할 시 여러 option을 argment로 설정할 수 있다.



- function 호출을 통해 ContainerOP으로 convert

  ```python
  tmp = create_component_from_func(
          finc =tmp_function, 
          base_image = 'python:3.8',
          output_comonent_file="tmp.component.yaml",
  		packages_toinstall=['numpy = 1.22.4', 'tqdm = 4.64.0'])
  ```

  - `finc` : component로 바꾸고자 하는 python function
  - `base_image` : component는 k8s pod로 생성되며, 해당 pod 의 image를 설정 (optional)
  - `output_comonent_file` : component를 yaml로 compile하여 재사용하기 쉽게 관리 가능
  - `packages_toinstall` : base image에는 없지만 python code에 필요한 의존성 package
  - `type(tmp) : ContainerOP`



##### resources

하나의 component를 선언 후 해당 instance에 method chaining형태로 pod의 resource를 지정할 수 있다.

component별로 필요한 resource를 할당할 수 있다.

###### CPU, GPU

```python
import kfp
from kfp.components import create_component_from_func
from kfp.dsl import pipeline

def component():
    ...
    
def training(learning_rate, num_layesr, optimizer):
    ...
    
component_op = create_component_from_func(component)
training_op = create_component_from_func(training)

@pipeline(name="exam")
def pipeline()
	# CPU 할당
	component_test = component_op.set_cpu_request(2).set_cpu_limit(4).set_memort_request("1G").set_memory_limit("2G")
    
    # GPU 할당
    training_test =  training_op(learning_rate, num_layesr, optimizer).set_gpu_limit(1)
    # GPU사용시에는 반드시 GPU를 사용할 수 있는 docker image를 사용해야 정상적으로 사용이 가능하다.
```



###### PVC

k8s의 동일한 namespace에 PVC를 미리 생성해둔 뒤, 해당 PVC의 name을 지정하여 `ConainerOP`의 argument로 할당하여 사용

```python
import kfp
from kfp.components import create_component_from_func
from kfp import dsl

@dsl.pipline	
def pipeline():
    vop = dsl.VolumeOP(
    	name="v1",
    	resource_name="mypvc",
    	size = "1Gi")
    
    use_volume_op = dsl.ContainerOP(
    	name="test",
    	pvolumes={"/mnt": vop.volume})		# containerOP생성 시 argument로 지정
    
```



###### Secret

k8s의 동일한 namespace에 Secret을 미리 생성해둔 뒤, 해당 secret과 name과  value를 지정하여 사용

```python

```



이외에도 대부부느이 k8s resource를 사용할 수 있다. [Documentation](https://www.kubeflow.org/docs/)





### pipeline

```python
import kfp
from kfp.dsl import pipeline

@pipeline(name="tmp")
def tmp():
	return None        
```

`name` : pipeline의 name



##### exam_1★

app.py

```python
import kfp
from kfp.components import create_component_from_func
                          
def add(value_1:int, value_2:int)->int:		# 반드시 input, output의 type을 명시해야함 (return이 없으면 ->int도 당연히 없음)
    ret = value_1 + value_2	
    return ret
                                                   
def subtract(value_1:int, value_2:int)->int:
    ret = value_1 - value_2
    return ret	   
                            
def multiply(value_1:int, value_2:int)->int:
    ret = value_1 * value_2
    return ret	
                            
add_op = create_component_from_func(add)
subtract_op = create_component_from_func(subtract)
multiply_op = create_component_from_func(multiply)

from kfp.dsl import pipeline

@pipeline(name="add_example")
def my_pipeline(value_1:int, value_2:int)->int:
    task_1 = add_op(value_1, value_2)
    task_2 = subtract_op(value_1, value_2)

    task_3 = multiply_op(task_1.output, task_2.output)  #  output -> input 으로 연결

```

>  **component간의 data공유는 input/output변수 사용** : `task_1.output` : output -> input 으로 연결하면 DAG 상에 연결됨
>
> **실제 code를 compile할 땐 주석에도 한글 자체가 없어야 한다.**

- 이후 `dsl-compile` 로 code를 compile

  ```
  $ dsl-compile --py add.py --output add_exam.yaml
  ```

  > create `add_exam.yaml`

- 또는 code에 compile을 추가

  ```python
  if __name__=="__main"__:
      fkp.compiler.Compiler().compile(my_pipeline, "./add_exam.yaml")
  ```

  > ```
  > $ python app.py
  > ```
  >
  > create `add_exam.yaml`

```
$ ls  			# add_exam.yaml 가 있는걸 확인 가능
```

> `add_exam.yaml` 을 확인하면
>
> - `kind : workflow` 
>
> - `dag` 
>   - `name`, `arguments`등등이 확인 가능





위 예시에서 `create_component_from_func()`에 의해 `add` function이 component가 되는데, 이 때 `add` 안에는 해당 Scope외에 정의된 함수를 사용할 수 없다.

```python
import numpy as np
add_op = create_component_from_func(add)

def add(value_1:int, value_2:int)->int:		
    tmp = np.zeros((1, 3))				# 잘못된 형식
    ret = value_1 + value_2	
    return ret
```

```python
add_op = create_component_from_func(add)

def add(value_1:int, value_2:int)->int:		
	import numpy as np		# add 안에서 선언되어야 함
    tmp = np.zeros((1, 3))				
    ret = value_1 + value_2	
    return ret
```

첫 번째 경우 처럼  import를 add 외부(전역 scope)에서 하고자 하는 경우, base_image로 사용되는 Dorker 이미지에 `pip install numpy`와 같이 install을 넣어줘야 한다.

> `python:3.8` 대신 `python:customized image`를 만든 후 `create_component_from_func` 를 아래처럼 선언

```python
create_component_from_func(
        finc =tmp_function, 
        base_image = 'python:customized',
        output_comonent_file="tmp.component.yaml",
		packages_toinstall=['numpy = 1.22.4', 'tqdm = 4.64.0'])
```







### InputPath, OutputPath

component간의 전달할 data가 큰 경우 file을 통해 data를 전달할 때 사용

해당 function의 변수를 사용할 때 반드시 해당 type을 명시해주어야 함



#### dict

dict형태로 data를 전달

```python
from kfp.components import OutputPath

@create_component_from_func 
def exam_func1( data_output_path : OutputPath("dict")):		# path를 받아온다.
    pass

def exam_func2( data_input_path : InputPath("dict")):		# path를 받아온다.
    pass
```

> `OutputPath("dict")` : path에 저장할 data를 어던 type으로 저장할것인지 명시



##### exam_2★

**component간의 data공유에 file path를 사용**

data_passinf_file_pipeline.py

```python
import kfp
from kfp.components import InputPath, OutputPath, create_component_from_func

@create_component_from_func
def write_file_op(data_output_path: OutputPath("dict")):
    import json
    data = {'a': 300, "b" : 10}		# OutputPath("dict") 이므로 dict 
    with open(data_output_path, "w") as f:
        json.dump(data, f)

@create_component_from_func
def read_file_and_multiply_op(data_input_path: InputPath("dict")) ->float :
    import json
    with open(data_input_path, "r") as f:
        data = json.load(f)
    
    result = data['a'] * data['b']
    print(f"result : {result} ")
    
    return result

@kfp.dsl.pipeline(name="Data Passing by File Example")
def data_passing_file_pipeline():
    write_file_task = write_file_op()
    _ = read_file_and_multiply_op(write_file_task.outputs["data_output"])
    
if __name__=="__main__":
    kfp.compiler.Compiler().compile(
    	data_passing_file_pipeline,
        "./data_passinf_file_pipeline.yaml"
    	)
```

> **실제 code를 compile할 땐 주석에도 한글 자체가 없어야 한다.**

create `data_passinf_file_pipeline.yaml`



#### metrics

component에서 metrics를 남길 수 있다. (excel처럼)

InputPath, OutputPath에 metrics를 명시

1. metrics는 dict으로, `key : metrics`, `value : list of dict()` 으로 한다.

2. list의 각 dict()는 반드시 `name`, `number_Value` 라는 key를 가지고 있어야 한다.
   - `"format"` : 어떤 형태로 출력할 것인지. excel의 표시 형식과 같다.
     - default : "RAW"
     - "PERCENTAGE" : %

##### exam_3★

export_metrics.py

```python
import kfp
from kfp.components import InputPath, OutputPath, create_component_from_func

@create_component_from_func
def export_metric_op(mlpipeline_metric_path:OutputPath("metrics")):
    import json
    metrics = {}
    metrics["metrics"] = []
    metrics["metrics"].append(dict("name" : "name_1", "number_Value" : 0.8))
    metrics["metrics"].append(dict("name" : "name_2", "number_Value" : 0.9, "format":"PERCENTAGE"))
    # "format" : 어떤 형태로 출력할 것인지. excel의 표시 형식과 같다.
    
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



### upload to kubeflow

1. istio-ingressgateway 확인

   ```
   $ kubectl get svc -n istio-system
   ```

   ```
   NAME                    TYPE           CLUSTER-IP       EXTERNAL-IP   PORT(S)
   istio-ingressgateway    LoadBalancer   10.102.172.178   <pending>     15021:32503/TCP,80:30116/TCP,443:31897/TCP,31400:31214/TCP,15443:30902/TCP  
   ```

   > port 80 확인

2. port forward

   ```
   $ kubectl port-forward svc/istio-ingressgateway -n istio-system 8080:80
   ```

3. localhost 8080접속

   ```
   localhost:8080
   ```

   `Eamail Address`, `PW` 입력

   > `user@example.com`, `12341234`

   **pipeline** 에서 `+Upload pipeline` , Upload a file 에서 `add_exam.yaml` 선택 >> create

   `+Create run` : 해당 pipeline을 실행 

   > 선택할 experiments가 없으면 Experiments(KFP) 에서 `+Create experiment` 눌러서  experiment만들고 바로 pipeline선택해서 run만들기

   Run이 만들어진 후 시간이 지나면 Graph에서 각 componenet의 상태 확인 가능

   > 모든 output, log는 minio에 저장되며 해당 file을 다운받으면 관련 data를 확인할 수 있다.





## dsl

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

