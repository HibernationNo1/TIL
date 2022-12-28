

## log

### 500

#### Invalid input error: Unrecognized 

```
kfp_server_api.exceptions.ApiException: (500)
Reason: Internal Server Error
HTTP response headers: HTTPHeaderDict({'Content-Length': '685', 'Content-Type': 'application/json', 'Date': 'Fri, 12 Aug 2022 02:14:31 GMT', 'Ngrok-Trace-Id': '9cd8d32381328fa4e531e3b07cf45748', 'Server': 'istio-envoy', 'X-Envoy-Upstream-Service-Time': '51', 'X-Powered-By': 'Express'})
HTTP response body: {"error":"Failed to create a new run.: InternalServerError: failed to generate the ExecutionSpec.: Failed to verify parameters.: Invalid input error: Unrecognized input parameter: gs_secret","code":13,"message":"Failed to create a new run.: InternalServerError: failed to generate the ExecutionSpec.: Failed to verify parameters.: Invalid input error: Unrecognized input parameter: gs_secret","details":[{"@type":"type.googleapis.com/api.Error","error_message":"Internal Server Error","error_details":"Failed to create a new run.: InternalServerError: failed to generate the ExecutionSpec.: Failed to verify parameters.: Invalid input error: Unrecognized 
input parameter: gs_secret"}]}
```

- **point** : `Invalid input error: Unrecognized `

- pipeline compile됨

- input parameters가 maching되지 않을 때 발생

  > 또는 
  >
  > ```
  > exec_run = client.run_pipeline(
  >             experiment_id = experiment_id,
  >             job_name = cfg.run.name,
  >             version_id = version_id,
  >             params = params
  >             )
  > ```
  >
  > 여기서 version이 맞지 않은 경우에도 발생





#### Incorrect string value

```
kfp_server_api.exceptions.ApiException: (500)
Reason: Internal Server Error
HTTP response headers: HTTPHeaderDict({'Content-Length': '817', 'Content-Type': 'application/json', 'Date': 'Fri, 12 Aug 2022 04:57:57 GMT', 'Ngrok-Trace-Id': '8a3ce8e4ecf960f3eeb77576661a134c', 'Server': 'istio-envoy', 'X-Envoy-Upstream-Service-Time': '119', 'X-Powered-By': 'Express'})
HTTP response body: {"error":"Failed to create a new run.: InternalServerError: Failed to store run hibernation-project-tc998 to table: Error 1366: Incorrect string value: '\\xEC\\x97\\xAC\\xEA\\xB8\\xB0...' for column 'WorkflowRuntimeManifest' at row 1","code":13,"message":"Failed to create a new run.: InternalServerError: Failed to store run hibernation-project-tc998 to table: Error 1366: Incorrect string value: '\\xEC\\x97\\xAC\\xEA\\xB8\\xB0...' for column 'WorkflowRuntimeManifest' at row 1","details":[{"@type":"type.googleapis.com/api.Error","error_message":"Internal Server Error","error_details":"Failed to create a new run.: InternalServerError: Failed to store run hibernation-project-tc998 to table: Error 1366: Incorrect string value: '\\xEC\\x97\\xAC\\xEA\\xB8\\xB0...' for column 'WorkflowRuntimeManifest' at row 1"}]}
```

- **point** : `Incorrect string value `
- pipeline compile후 업로드 할 때 발생
- component에 한글이 포함되어 있을 때(주석이라도) 발생



#### connection reset by peer

```
kfp_server_api.exceptions.ApiException: (500)
Reason: Internal Server Error
HTTP response headers: HTTPHeaderDict({'Content-Length': '1687', 'Content-Type': 'application/json', 'Date': 'Mon, 22 Aug 2022 08:53:44 GMT', 'Ngrok-Trace-Id': '76dad60dda92d1205c9a3a524115a174', 'Server': 'istio-envoy', 'X-Envoy-Upstream-Service-Time': '426', 'X-Powered-By': 'Express'})
HTTP response body: {"error":"Failed to authorize the request: Failed to authorize with API resource references: InternalServerError: Failed to create SubjectAccessReview for user 'winter4958@gmail.com' (request: \u0026ResourceAttributes{Namespace:project-pipeline-1,Verb:get,Group:pipelines.kubeflow.org,Version:v1beta1,Resource:runs,Subresource:,Name:hibernation-project-ftxnr,}): Post \"https://10.96.0.1:443/apis/authorization.k8s.io/v1/subjectaccessreviews\": read tcp 172.17.0.27:59254-\u003e10.96.0.1:443: read: connection reset by peer","code":13,"message":"Failed to authorize the request: Failed to authorize with API resource references: InternalServerError: Failed to create SubjectAccessReview for user 'winter4958@gmail.com' (request: \u0026ResourceAttributes{Namespace:project-pipeline-1,Verb:get,Group:pipelines.kubeflow.org,Version:v1beta1,Resource:runs,Subresource:,Name:hibernation-project-ftxnr,}): Post \"https://10.96.0.1:443/apis/authorization.k8s.io/v1/subjectaccessreviews\": read tcp 172.17.0.27:59254-\u003e10.96.0.1:443: read: connection reset by peer","details":[{"@type":"type.googleapis.com/api.Error","error_message":"Internal Server Error","error_details":"Failed to authorize the request: Failed to authorize with API resource references: InternalServerError: Failed to create SubjectAccessReview for user 'winter4958@gmail.com' (request: \u0026ResourceAttributes{Namespace:project-pipeline-1,Verb:get,Group:pipelines.kubeflow.org,Version:v1beta1,Resource:runs,Subresource:,Name:hibernation-project-ftxnr,}): Post \"https://10.96.0.1:443/apis/authorization.k8s.io/v1/subjectaccessreviews\": read tcp 172.17.0.27:59254-\u003e10.96.0.1:443: read: connection reset by peer"}]}
```

- Run을 돌리는 와중에 ngrok이 끊겨버린 경우 발생





### 403

#### Unauthorized access

```
kfp_server_api.exceptions.ApiException: (403)
Reason: Forbidden
HTTP response headers: HTTPHeaderDict({'Content-Length': '1443', 'Content-Type': 'application/json', 'Date': 'Thu, 18 Aug 2022 05:01:09 GMT', 'Ngrok-Trace-Id': 'ef5720e4df36764f50135dfe68d2c9e0', 'Server': 'istio-envoy', 'X-Envoy-Upstream-Service-Time': '4', 'X-Powered-By': 'Express'})
HTTP response body: {"error":"Failed to authorize with API resource references: Failed to authorize with API resource references: PermissionDenied: User 'user@example.com' is not authorized with reason:  (request: \u0026ResourceAttributes{Namespace:kubeflow-user-example-com_,Verb:list,Group:pipelines.kubeflow.org,Version:v1beta1,Resource:experiments,Subresource:,Name:,}): Unauthorized access","code":7,"message":"Failed to authorize with API resource references: Failed to authorize with API resource references: PermissionDenied: User 'user@example.com' is not authorized with reason:  (request: \u0026ResourceAttributes{Namespace:kubeflow-user-example-com_,Verb:list,Group:pipelines.kubeflow.org,Version:v1beta1,Resource:experiments,Subresource:,Name:,}): Unauthorized access","details":[{"@type":"type.googleapis.com/api.Error","error_message":"User 'user@example.com' is not authorized with reason:  (request: \u0026ResourceAttributes{Namespace:kubeflow-user-example-com_,Verb:list,Group:pipelines.kubeflow.org,Version:v1beta1,Resource:experiments,Subresource:,Name:,})","error_details":"Failed to authorize with API resource references: Failed to authorize with API resource references: PermissionDenied: User 'user@example.com' is not authorized with reason:  (request: \u0026ResourceAttributes{Namespace:kubeflow-user-example-com_,Verb:list,Group:pipelines.kubeflow.org,Version:v1beta1,Resource:experiments,Subresource:,Name:,}): Unauthorized access"}]}
```

- **point** : `Unauthorized access `
- `client.experiment`에 연결할 때 발생
- clinet에 접속할 때 사용한 NAMESPACE가 없는 경우 발생(NAMESPACE 오타 확인할 것)





### 404

#### Not Found

```
kfp_server_api.exceptions.ApiException: (404)
Reason: Not Found
HTTP response headers: HTTPHeaderDict({'Content-Length': '527', 'Content-Type': 'application/json', 'Date': 'Mon, 22 Aug 2022 05:29:55 GMT', 'Ngrok-Trace-Id': 'ad03d8fc1d55ccdffee47eaabbb39250', 'Server': 'istio-envoy', 'X-Envoy-Upstream-Service-Time': '73', 'X-Powered-By': 'Express'})
HTTP response body: {"error":"Failed to get namespace from pipelineId.: Failed to get namespace from Pipeline ID: ResourceNotFoundError: Pipeline  not found.","code":5,"message":"Failed to get namespace from pipelineId.: Failed to get namespace from Pipeline ID: ResourceNotFoundError: Pipeline  not found.","details":[{"@type":"type.googleapis.com/api.Error","error_message":"Pipeline  not found.","error_details":"Failed to get namespace from pipelineId.: Failed to get namespace from Pipeline ID: ResourceNotFoundError: Pipeline  not found."}]}
```

- **point** : `Pipeline  not found `
- 1. upload하지 않은 pipeline의 name으로 `client.list_pipeline_versions` 을 실행했을 때 발생 
  2. 



### 400

#### Bad Request

```
kfp_server_api.exceptions.ApiException: (400)
Reason: Bad Request
HTTP response headers: HTTPHeaderDict({'x-powered-by': 'Express', 'content-type': 'application/json', 'date': 'Tue, 06 Sep 2022 02:42:34 GMT', 'content-length': '524', 'x-envoy-upstream-service-time': '67', 
'server': 'istio-envoy'})
HTTP response body: {"error":"Validate create run request failed.: Invalid input error: The input parameter length exceed maximum size of 10000.","code":3,"message":"Validate create run request failed.: Invalid input error: The input parameter length exceed maximum size of 10000.","details":[{"@type":"type.googleapis.com/api.Error","error_message":"The input parameter length exceed maximum size of 10000.","error_details":"Validate create run request failed.: Invalid input error: The input parameter length exceed maximum size of 10000."}]}
```

- **point** : `The input parameter length exceed maximum size of 10000.`

  input parameters값의 길이를 줄이면 됨(str이 너무 길어서 발생한 경우)



## code

### client

#### 'authservice_session'

```
session_cookie = session.cookies.get_dict()["authservice_session"]
KeyError: 'authservice_session'
```

- clinet접속 시 username또는 passward가 맞지 않은 경우 발생







## bashboard

#### must specify cpu,memory

```
This step is in Error state with this message: task 'hibernation-project-9kj4p.set-config' errored: pods "hibernation-project-9kj4p-3036383870" is forbidden: failed quota: kf-resource-quota: must specify cpu,memory
```

- 새로 만든 namespace(profile)의 resourceQuotaSpec부분이 잘못됨

  - 변경 전

    ```
      resourceQuotaSpec:
        hard:
          cpu: "2"
          memory: 2Gi
          persistentvolumeclaims: "1"
          requests.nvidia.com/gpu: "1"
          requests.storage: "10Gi"
    ```

  - 변경 후

    ```
    resourceQuotaSpec: {}
    ```

    고쳐짐





#### secret

해당 RUN process가 진행되는 namespace에 secrets가 있는지 확인



#### STRING [{] to VARIABLE [???]

```
This step is in Error state with this message: Invalid 'when' expression '"{"dvc": {"remote": 1}}" != "None"': Cannot transition token types from STRING [{] to VARIABLE [dvc]
```

이와 같은 error는 

1. 하나의 component에 input이 두개이고

2. 두 개의 type이 모두 dict인 경우이고

3. 두 개의 dict이 모두 하나 이상의 key를 가지고 있는 경우

   > 하나라도 dict: {} 처럼 빈 dict이면 에러발생 안함

발생한다.

```
 _check_status_op = recode_op(cfg_1, cfg_2)
```

- `cfg_1`, `cfg_2` 두개 다 하나 이상의 key를 가지고 있음 >> error발생

왜?

component가 input을 dict으로 받는 경우 `'{'key':value}'`형식으로 받게 되는데, 이러한 input을 두 개 이상 받을 경우 구분을 위해서 큰따옴표`"` 도 사용하게 된다.

이 때 따옴표`' or "` 간의 간섭이 일어나 `{` 라는 기호가 dict을 구분짓는 역할을 하지 못하게 되는 것.



해결법: 

가능하면 dict을 하나로 합쳐 input을 하나로 하자. 