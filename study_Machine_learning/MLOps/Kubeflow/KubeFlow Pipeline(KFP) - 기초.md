# KubeFlow Pipeline(KFP)

[공식](https://kubeflow-pipelines.readthedocs.io/en/stable/source/kfp.client.html)

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

  

**kubeflow pipeline을 작성하는 방법**

1. 경량화 컴포넌트를 작성하는방법 (reate_component_from_fun를 사용)

   - 장점 : 

     하나의 함수가 하나의 컴포넌트가 되는 방식으로, 하나의 파이썬 파일만으로 모든 컴포넌트를 작성할 수 있어 수정이 빠르고 작성이 간편하다.

   - 단점 :

     딥러닝과 같이 코드가 많은 경우에는 오히려 가독성이 떨어진다.

     하나의 함수가 개별적인 컴포넌트이기 때문에 컴포넌트에 사용되는 라이브러리를 함수안에서 설치할 버전을 명시하고 import를 해주어야 한다.

     .py 파일에 한글이 있으면 yaml파일로 작성이 되지 않는다.

   

2. 컴포넌트별로 일반적인 딥러닝 파이썬코드를 작성하고 도커 이미지로 빌드 한 후 간단하게 파이프라인에서 연결만 시켜주는 방법



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



## component

### create_component_from_func

경량화 component를 만들때 사용하며, function을 하나의 component로 만들 수 있다.

```python
from kfp.components import create_component_from_func
```

decorator로도 사용할 수 있으며, function으로 호출할 시 여러 option을 argment로 설정할 수 있다.



- function 호출을 통해 ContainerOP으로 convert

  ```python
  tmp = create_component_from_func(
          func =tmp_function, 
          base_image = 'python:3.8',
          output_component_file="tmp.component.yaml",
  		packages_toinstall=['numpy = 1.22.4', 'tqdm = 4.64.0'])
  ```

  - `finc` : component로 바꾸고자 하는 python function
  
  - `base_image` : component는 k8s pod로 생성되며, 해당 pod 의 image를 설정 (optional)
  
    > - custom image를 사용하려면 docker file을 작성해서 docker hub에 push
    >
    >   ```
    >   $ docker build -t {image_name} {Dockerfile위치}
    >   $ docker tag {image_name}:latest {dockerhub name}/{image_name}:{version}
    >   $ docker push {dockerhub name}/{image_name}:{version}
    >   ```
    >
    >   `base_image = '{dockerhub name}/{image_name}:{version}'`
    >
    > 이 때 docker file에서 `RUN pip install` 을 통해 package를 설치 가능
  
  - `output_comonent_file` : component를 yaml로 compile하여 재사용하기 쉽게 관리 가능
  
  - `packages_toinstall` : base image에는 없지만 python code에 필요한 의존성 package
  
  - `type(tmp) : ContainerOP`



#### resources

하나의 component를 선언 후 해당 instance에 method chaining형태로 pod의 resource를 지정할 수 있다.

component별로 필요한 resource를 할당할 수 있다.

##### CPU, GPU

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



##### Secret

k8s의 동일한 namespace에 Secret을 미리 생성해둔 뒤, 해당 secret과 name과  value를 지정하여 사용

```python

```



이외에도 대부분의 k8s resource를 사용할 수 있다. [Documentation](https://www.kubeflow.org/docs/)



### ContainerOp

이젠 안씀

### func_to_container_op

경량화 component를 만들때 사용하며, function을 하나의 component로 만들 수 있다.

`create_component_from_func` 와 같은 동작. `create_component_from_func`가 제대로 동작 안할 때 사용

```python
func_to_container_op(
        finc =tmp_function, 
        base_image = 'python:customized',
        output_comonent_file="tmp.component.yaml",
		packages_toinstall=['numpy = 1.22.4', 'tqdm = 4.64.0'])
```



### InputPath, OutputPath

component간의 전달할 data가 큰 경우 file을 통해 data를 전달할 때 사용

해당 function의 변수를 사용할 때 반드시 해당 type을 명시해주어야 함

예시는 [아래](exam★)



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

   **Central Dashboard**의 **pipeline** 에서 `+Upload pipeline` , Upload a file 에서 `add_exam.yaml` 선택 >> create

   `+Create run` : 해당 pipeline을 실행 

   > 선택할 experiments가 없으면 Experiments(KFP) 에서 `+Create experiment` 눌러서  experiment만들고 바로 pipeline선택해서 run만들기

   Run이 만들어진 후 시간이 지나면 Graph에서 각 componenet의 상태 확인 가능

   > 모든 output, log는 minio에 저장되며 해당 file을 다운받으면 관련 data를 확인할 수 있다.





## dsl

### pipeline

```python
import kfp
from kfp.dsl import pipeline

@pipeline(name="tmp")
def tmp():
	return None        
```

`name` : pipeline의 name



#### exam★

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





#### metrics

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





