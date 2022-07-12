# KubeFlow Pipeline(KFP)

#### Introduction

- component : 재사용 가능한 형태로 분리된 하나의 작업 단위

  > resource : Pod

  kfp sdk를 사용하여  component를 구현하면, 그 component를 사용하는 pipeline을 compile했을 때 생성되는 workflow의 yaml file의 `spec.templates` 에 대항 components를 감싼 (containerized)부분이 추가된다.

  하나의 component는 k8s상에서 하나의 독립적인 pod로 생성되어 component내부에 작성된 code를 components dectorator에 작성한 base_image환경에서 실행하게 된다.

  > base_image 지정을 통해 항상 동일한 환경에서 정해진 code가 실행되는 것을 보장할 수 있다.
  >
  > 따라서 하나의 pipeline내에서 연속된 component라고 하더라도 memory를 공유하는 일은 일어나지 않으며, 일반적으로 서로 다른 component간의 data공유는 input/output변수 혹은 file path로 넘겨주는 방식을 사용한다.

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
minikube
type: Control Plane
host: Running
kubelet: Running
apiserver: Running
kubeconfig: Configured
```

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



### create_component_from_func

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



### pipeline

```python
from kfp.dsl import pipeline

@pipeline(name="tmp")
def tmp():
	return None        
```

`name` : pipeline의 name





### exam

app.py

```python
from kfp.components import create_component_from_func
                          
def add(value_1:int, value_2:int)->int:		# 반드시 input, output의 type을 명시해야함
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

- `task_1.output` : output -> input 으로 연결하면 DAG 상에 연결됨

```
$ dsl-compile --py add.py --output add_exam.yaml
```

```
$ ls  			# add_exam.yaml 가 있는걸 확인 가능
```



