

```
apiVersion: "serving.kserve.io/v1beta1"
kind: "InferenceService"
metadata:
  annotations:
    isdecar.istio.is/inject: "false"
  name: "sklearn-iris-python2"
spec:
  predictor:
    sklearn:
      image: "kserve/sklearnserver:v0.9.0"
      storageUri: "gs://kfserving-examples/models/sklearn/1.0/model"
```



```
$ kubectl get InferenceService -n project-pipeline
```

> ```
> [400] InferenceService in version "v1beta1" cannot be handled as a InferenceService: v1.ObjectMeta.Annotations: ReadMapCB: expect { or n, but found ", error found in #10 byte of ...|tations":"isdecar.is|..., bigger context ... 
> ```
>
> 문법 틀린 부분이 있는 경우 발생



```
kubectl edit configmaps inferenceservice-config -n kserve 
```

```
ingress: |-
    {
        "ingressGateway" : "knative-serving/knative-ingress-gateway",
        ...
```

```
ingress: |-
    {
        "ingressGateway" : "kubeflow/kubeflow-gateway",
        ...
```





```python

def with_kfp_client():
    from pipeline_utils import connet_client
    import json
    from docker.hibernation_no1.configs.config import Config

    dashboard_cfg = {'user_n': 'winter4958@gmail.com', 'name_space': 'project-pipeline', 'host': 'http://localhost:8080', 'pw': '4958'}
    dashboard_cfg = Config(dashboard_cfg)
    client, session = connet_client(dashboard_cfg, return_session = True)  
        
    session_cookie = session.cookies.get_dict()
    sklear_iris_input = dict(instances = [
    [6.8, 2.8, 4.8, 1.4],
    [6.0, 3.4, 4.5, 1.6]
    ])

    HOST = "https://127.0.0.1:8080"

    headers = {'Host': "http://sklearn-iris-test2.project-pipeline.example.com"}
    res = session.post(f"{HOST}/v1/models/v1/models/sklearn-iris:predict", headers = headers, cookies = session_cookie,
                        data = json.dumps(sklear_iris_input))
    
    # HTTPSConnectionPool(host='127.0.0.1', port=8080): 
    # Max retries exceeded with url: 
    # /v1/models/v1/models/sklearn-iris:predict (Caused by SSLError(SSLError(1, '[SSL: WRONG_VERSION_NUMBER] wrong version number (_ssl.c:1131)')))
    # 또는 신뢰할 수 없는 SSL인증서
    print(f"res.json : {res.json}")

    

# ---

def with_kserve_client():
    from kserve import (utils,
                        KServeClient)

    # 현재 실행중인 notebook의 namespace를 가져온다.
    # esle: default
    # namespace = utils.get_default_target_namespace()     

    namespace = "project-pipeline"


    service_name = "sklearn-iris-test2"
    kserve = KServeClient()     # istio ingressgateway가 연결되어있어야 한다

    # watch = True 를 주면 URL을 확인할 수 있지만 None을 return한다.
    # watch = False를 주면 inference service에 관한 dict을 return한다.
    isvc_resp = kserve.get(service_name, namespace = namespace)


    sklear_iris_input = dict(instances = [
        [6.8, 2.8, 4.8, 1.4],
        [6.0, 3.4, 4.5, 1.6]
    ])

    import requests
    import json

    isvc_url = isvc_resp['status']['address']['url']
    # isvc_url = "http://sklearn-iris.project-pipeline.example.com"
    print(f"isvc_url ; {isvc_url}\n")


    # HTTPConnectionPool(host='sklearn-iris-test2.project-pipeline.svc.cluster.local', port=80): 
    # Max retries exceeded with url: /v1/models/sklearn-iris-test2:predict 
    # (Caused by NewConnectionError('<urllib3.connection.HTTPConnection object at 0x7fe70aa8e9a0>: Failed to establish a new connection: [Errno -2] Name or service not known'))
    response = requests.post(isvc_url, json = json.dumps(sklear_iris_input))        
    print(response.text)


with_kfp_client()
# with_kserve_client()
```





