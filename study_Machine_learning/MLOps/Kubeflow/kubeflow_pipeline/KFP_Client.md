

{:toc}

**install**

pip install

```
$ pip install kfp
```

check

```
$ pip list | grep kfp
```



**resource check**

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
> --cpus='4' --memory='7g' \
> --kubernetes-version=v1.19.3 \
> --extra-config=apiserver.service-account-signing-key-file=/var/lib/minikube/certs/sa.key \
> --extra-config=apiserver.service-account-issuer=kubernetes.dafault.svc
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



[공식 문서](https://kubeflow-pipelines.readthedocs.io/en/1.8.13/source/kfp.client.html)



## Client

kubeflow pipelines api와 통신하기 위한 클라이언트 선언

간단히 선언

```python
import kfp
client = kfp.Client()
```



TODO

```python
import kfp

host = "https://127.0.0.1:8090/pipeline"
namespace = "hibernation"
other_client_id = "exam"
other_client_secret = 4958

client = kfp.Client(host = host, 
                    namespace = namespace, 
                    other_client_id = other_client_id,
                    other_client_secret = other_client_secret,
                    ui_host  )
```

- `host` :  kubeflow Pipelines와 통신하는데 사용할 host name

  **IAP 지원 클러스터에 연결하는 경우** :`https://<your-deployment>.endpoints.<your-project>.cloud.goog/pipeline`

  **proxy 연결** : `<IP>:<port>/<yout-deployment>`  (default 127.0.0.1:8080/pipeline)

  > 설정 안할 경우 cluster 내 service DNS name이 사용되며 관련 pod는 동일한 cluster인 경우에만 작동한다. 그렇기 때문에 자신의 host name을 명시하고 관련 cluster를 생성 및 설정시 인지하여 사용하도록 하자.

  - minikube사용시 cluster의 외부 접근이 번거롭기 때문에 `ngrok` 를 사용해서 임시 URL를 할당받아 사용하도록 하자 

    `host = "https://cc11-1-214-32-67.ngrok.io"`

  - kubernetes사용시 외부로 cluster IP노출이 가능하기 때문에 `istio-ingressgateway` 의  `EXTERNAL-IP`이 할당된다. 이걸 사용하자

    `host = http://192.168.0.167:80"`

    

- `namespace` : kubeflow가 사용자별 분리된 workspace를 가지게 하여 독립 환경을 제공하도록 한다.

  ```python
  print(f"client name : {client.get_user_namespace()}")
  ```

- `other_client_id` : client ID

- `other_client_secret` : client pw (pipeline central dashboard 접속시 사용???) TODO

- `cookies` : pipeline central dashboard에 연결할 때 필요한 kookies

- `ui_host` : TODO

**예시**

```python
import kfp
import requests

USERNAME = "user@example.com"
PASSWORD = "12341234"
NAMESPACE = "kubeflow-user-example-com"
HOST =  "http://127.0.0.1:8080"     # "http://192.168.0.167:80" 
session = requests.Session()
response = session.get(HOST)

headers = {
    "Content-Type": "application/x-www-form-urlencoded",
}

data = {"login": USERNAME, "password": PASSWORD}
session.post(response.url, headers=headers, data=data)				# 요청 보내기
session_cookie = session.cookies.get_dict()["authservice_session"]	# 토큰값 가져오기

# client에 접속
client = kfp.Client(
    host=f"{HOST}/pipeline",
    namespace=f"{NAMESPACE}",
    cookies=f"authservice_session={session_cookie}",
)
print(client.list_pipelines())
```

> 토큰값 직접 확인 : `도구 더 보기 - 개발자 도구 - Application - Storage - Cookies - <localhost:port> - authservice-session`







### pipelines

#### list_pipelines

현재 upload되어있는 pipeline의 list를 return한다.

```python
list_pipelines = client.list_pipelines(page_size = 50)  	

list_pipeline_name = []
for pipeline_index in range(list_pipelines.total_size):
	list_pipeline_name.append(list_pipelines.pipelines[pipeline_index].default_version.name) 
        
```

- `page_size` : 최대 보여줄 pipeline개수 (default = 10)



lenth확인 

```python
list_pipelines.total_size
```



특정 pipeline 접근

```python
i = {some_num}
list_pipelines.pipelines[i]
```



특정 pipeline의 name

```python
list_pipelines.pipelines[i].default_version.name
```





#### get_pipeline_id

```python
pipeline_id = client.get_pipeline_id("{pipelie_name}")
```



#### get_pipeline

```python
info_pipeline = client.get_pipeline(pipeline_id=pipeline_id)
```

- `default_version` 

  ```python
  info_default_version = info_pipeline.default_version
  ```

  



#### list_pipeline_versions

특정 pipeline의 version을 나열한다. (return list)

```python
list_pipeline_versions = client.list_pipeline_versions(pipeline_id=pipeline_id)
```



예시

```
pipeline_name = "exam"
pipeline_version = "exam_version"

pipeline_id = client.get_pipeline_id(pipeline_name)
pipelince_versions = client.list_pipeline_versions(pipeline_id = pipeline_id)

versions = []
for pipeline_index in range(pipelince_versions.total_size):
	versions.append(pipelince_versions.versions[pipeline_index].name)  

if pipeline_version in versions: raise TypeError(f"{pipeline_version} version is exist!")
```





#### upload_pipeline

pipeline을 kubeflow cluster에 upload(kubeflow central dashboard에 upload)

```python
client.upload_pipeline(pipeline_name=, 
                       description=,
                       pipeline_package_path=)
```

- `pipeline_name `: upload할 pipeline에 지어줄 name (이미 존재하는 pipeline의 이름과 중복되면 안된다.)
- `description` : upload할 pipeline에 대한 설명
- `pipeline_package_path` : upload할 pipeline의 path (.yaml format)



#### upload_pipeline_version

같은 pipeline이라도 version별로 따로 관리가 가능한가? TODO

```python
updated_pipeline = client.upload_pipeline_version(pipeline_name=,
                                                  pipeline_version_name=,
                                                  pipeline_package_path=,
                                                  description=)
```

- `pipeline_name` : version updata를 적용할 pipeline의 name

- `pipeline_version_name` : 새로운version의 name (str)

  > "v220721_0.2"

- `pipeline_package_path` : upload할 pipeline의 path (.yaml format)

- `description` : 새로운version의 pipeline에 대한 description





### experiment(KFP)

현재 client에 존재하는 experiment의 list를 return

```python
list_experiments = client.list_experiments()
experiment = list_experiments.experiments[0]
```



- `id` : experiment의 id를 return

  ```python
  experiment.id
  ```

  





#### create_experiment

pipeline experiment를 만들고 experiment instance를 return

```python
experiment = client.create_experiment(name = name)
```

- `name` : 만들어질 experiment의 name



experiment의 id를 return

```python
experiment_id = experiment.id
```



#### get_experiment

client의 experiment정보를 return

```python
info_experiment = client.get_experiment(experiment_id = , experiment_name= , namespace= )
```

- `experiment_id` : 가져올 experiment의 id

- `experiment_name` : 가져올 experiment의 이름

  > `experiment_id`, `experiment_name` 둘 중 하나는 필수

- `namespace` : client가 속한 kubernetes namespace의 이름



#### list_experiments

```python
list_experiments = client.list_experiments(page_size = )
```

- `page_size` : 최대 보여줄 pipeline개수 (default = 10)



### run

#### create_run_from_pipeline_package

pipeline package(.yaml format)을 기반으로 run을 create한다.

```python
exec_run = create_run_from_pipeline_package(pipeline_file = ,
                                            arguments = ,
                                            namespace = ,
                                           )
```

- `pipeline_file` : compile된 pipeline file (.yaml format)

- `arguments` : pipeline에 전달될 arguments (type : dict)

- `namespace` : kubernetes의  namespace를 명시

- `pipeline_root` : pipeline의 outputs을 저장할 path

  > `dsl.PipelineExecutionMode.V2_COMPATIBLE` 또는 `dsl.PipelineExecutionMode.V2_ENGINGE` 으로 compile된 pipeline에만 사용된다.
  >
  > 



#### create_run_from_pipeline_func

**compiler mode가 `kfp.dsl.PipelineExecutionMode.V2_COMPATIBLE` 으로 명시될 때만 사용한다.**

`@dsl.pipeline` 으로 decorator된 pipeline function을 기반으로 run을 create한다.

```python
```





#### run_pipeline

특정 pipeline을 run한다. (create? 아님 이미 있는거?)

>  run이 실행된 것은 아니지만, input parameter까지 전부 갖추어진, 언제 실행해도 되는 run이다???? TODO 

```python
exec_run = client.run_pipeline(
        experiment_id = ,
        job_name =, 
        pipeline_id = ,
    	pipeline_package_path = ,
        pipeline_root = ,
    	params = 
        )
```

- `experiment_id` : pipeline이 소속된 experiment의 id

- `job_name` : run name

- `pipeline_id` : run할 pipeline의 id

- `pipeline_package_path` : run pipeline의 path (.yaml format)

  > `pipeline_id`, `pipeline_package_path` 는 둘 중에 하나만 할당

- `pipeline_root` : pipeline의 outputs을 저장할 path

  > `dsl.PipelineExecutionMode.V2_COMPATIBLE` 또는 `dsl.PipelineExecutionMode.V2_ENGINGE` 으로 compile된 pipeline에만 사용된다.

- `params` : parameters를 `key: value` 형태로 입력할때 사용. (type = dict)



get run id

```python
run_id = exec_run.id
```





#### wait_for_run_completion

Run을 실행하고, 완료될 때까지 기다렸다가 결과를 return

```python
completed_run = client.wait_for_run_completion(run_id=run_id, timeout=345600)
```

- `timeout` : 단위 : 초
- `run_id`:  
- reuturn
  - `completed_run.run.status` : `Failed` 또는 `Succeeded`





#### list_runs

client에 존재하는 모든 run을 return

```null
list_runs = client.list_runs(page_size=50)
```



get run id

```python
run_id = list_runs.runs[i].id
```



#### get_run

```null
info_run = client.get_run(run_id=run_id)
```

> 실행중이면 `{'status': 'Running'}`,  종료되었으면 `{'status': 'Succeeded'}`



#### list_recurring_runs

특정 experiment 안에 속한 모든 **recurring run**을 return

```python
list_recurring_runs = client.list_recurring_runs(experiment_id=experiment_id)
```



recurring run의 job_id return

```null
recurring_job_id = list_recurring_runs.jobs[0].id
```





### namespace

#### get_user_namespace

kubernetes의 namespace를 return

```python
client.get_user_namespace()
```



#### set_user_namespace

kubernetes의 namespace를 변경할때 사용

```python
client.set_user_namespace(namespace="<설정한 NAMESPACE>")
print(f"client name : {client.get_user_namespace()}")
```



**기본 info**

- `client.IN_CLUSTER_DNS_NAME`*= 'ml-pipeline.{}.svc.cluster.local:8888'*

- `client.KUBE_PROXY_PATH`*= 'api/v1/namespaces/{}/services/ml-pipeline:http/proxy/'*

- `client.LOCAL_KFP_CONTEXT`*= '/home/docs/.config/kfp/context.json'*

- `client.NAMESPACE_PATH`*= '/var/run/secrets/kubernetes.io/serviceaccount/namespace'*

```python
print(f"IN_CLUSTER_DNS_NAME : {client.IN_CLUSTER_DNS_NAME}")
print(f"KUBE_PROXY_PATH : {client.KUBE_PROXY_PATH}")
print(f"LOCAL_KFP_CONTEXT : {client.LOCAL_KFP_CONTEXT}")
print(f"NAMESPACE_PATH : {client.NAMESPACE_PATH} \n")
```



