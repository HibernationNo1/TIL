# Istio

### introduction

Ingress 및 Egress gateway를 관리하며, user의 custom gateway를정의하는 사용자 정의 resource를 작성할 수 있다.

[istio_github](https://github.com/istio/istio) , [공식](https://istio.io/latest/docs/setup/getting-started/)



**용어**

- `Load Balancing` : 하나의 internet service가 발새하는 traffic이 많을 때 여러 대의 server가 분산처리하여 server의 로드율 증가, 부라향, 속도저하 등을 고려하여 적절히 분산처리하여 해결해주는 service
  - `Load Balancer` : 여러 대의 server에게 균등하게 traffic을 분산신켜주는 역할을 한다.
- 





**install** 

kubeflow설치하면서 포함시켜야 된다.

[kubeflow_github](https://github.com/kubeflow/manifests) 



설치 후 istio-system의 name space확인

- pod확인

  ```
  $ kubectl get pod -n istio-system
  ```

  ```
  NAME                                    READY   STATUS    RESTARTS   AGE
  authservice-0                           1/1     Running   3          8d
  istio-ingressgateway-67fbc66cb7-pvzdz   1/1     Running   3          8d
  istiod-7594cc8c9-q2mc5                  1/1     Running   3          8d
  ```

- service확인

  ```
  $ kubectl get svc -n istio-system
  ```

  ```
  NAME                    TYPE           CLUSTER-IP       EXTERNAL-IP   PORT(S)                                                                      AGE
  authservice             ClusterIP      10.107.157.106   <none>        8080/TCP                                                                     8d
  istio-ingressgateway    LoadBalancer   10.106.103.15    <pending>     15021:30997/TCP,80:30887/TCP,443:32470/TCP,31400:30325/TCP,15443:31737/TCP   8d
  istiod                  ClusterIP      10.103.224.118   <none>        15010/TCP,15012/TCP,443/TCP,15014/TCP                                        8d
  knative-local-gateway   ClusterIP      10.109.209.244   <none>        80/TCP                                                                       8d
  ```

  minikube로 확인

  ```
  $ minikube service list -n istio-system
  ```

  ```
  
  |--------------|-----------------------|-------------------|---------------------------|
  |  NAMESPACE   |         NAME          |    TARGET PORT    |            URL            |
  |--------------|-----------------------|-------------------|---------------------------|
  | istio-system | authservice           | No node port      |
  | istio-system | istio-ingressgateway  | status-port/15021 | http://192.168.49.2:30997 |
  |              |                       | http2/80          | http://192.168.49.2:30887 |
  |              |                       | https/443         | http://192.168.49.2:32470 |
  |              |                       | tcp/31400         | http://192.168.49.2:30325 |
  |              |                       | tls/15443         | http://192.168.49.2:31737 |
  | istio-system | istiod                | No node port      |
  | istio-system | knative-local-gateway | No node port      |
  |--------------|-----------------------|-------------------|---------------------------|
  ```

  



#### istio-ingressgateway

kubernetes환경에서 사용하는 Load Balancer resource. 

istio-ingressgateway는 ckluster의 entry point가 된다

- `$ kubectl get svc -n istio-system` 를 통해 `istio-ingressgateway`의 `EXTERNAL-IP`이 `<pending>`인 것을 확인할 수 있는데, 이는 모든 것이 로컬에서 실행되기 때문에 실제로 실제 외부 로드 밸런서가 없기 때문이다.

  > cluster가 외부 load balancer를 지원하지 않는 환경(minikube)일 경우 이렇다.
  >
  > EXTERNAL-IP를 얻기 위해서는 
  >
  > 1. port-forwarding
  > 2. use **NodePort** To access the gateway

  



##### resource

`istio-ingressgateway` service 에 대한 yaml 

```
$ kubectl get svc -n istio-system istio-ingressgateway -o yaml
```

```
apiVersion: v1
kind: Service
metadata:
  # 생략
spec:
  clusterIP: 10.106.103.15
  externalTrafficPolicy: Cluster
  ports:
  - name: status-port
    nodePort: 30997
    port: 15021
    protocol: TCP
    targetPort: 15021
  - name: http2
    nodePort: 30887
    port: 80
    protocol: TCP
    targetPort: 8080
  - name: https
    nodePort: 32470
    port: 443
    protocol: TCP
    targetPort: 8443
  - name: tcp
    nodePort: 30325
    port: 31400
    protocol: TCP
    targetPort: 31400
  - name: tls
    nodePort: 31737
    port: 15443
    protocol: TCP
    targetPort: 15443
  selector:
    app: istio-ingressgateway
    istio: ingressgateway
  sessionAffinity: None
  type: LoadBalancer
status:
  loadBalancer: {}

```

> 특정 값을 수정하거나 추가할 때
>
> 예시
>
> - type을 LoadBalancer에서 NodePort으로 변경
>
>   ```
>   kubectl patch svc -n istio-system istio-ingressgateway -p '{"spec": {"type": "NodePort"}}'
>   ```
>
> - spec에 externalIPs 추가 (예시일 뿐이다. 추가해도 바로 사용 못함)
>
>   ```
>   kubectl patch svc -n istio-system istio-ingressgateway -p '{"spec":{"externalIPs":["your_external_ip"]}}'
>   ```
>
>   > externalIPs는 list로 넣어줘야 한다. 
>   >
>   > `your_external_ip`는 `192.168.0.200 `같은거
>
> - externalIPs 삭제 
>
>   ```
>   kubectl patch svc -n istio-system istio-ingressgateway --type=json -p='[{"op": "remove", "path": "/spec/externalIPs/0"}]'
>   ```
>
>   json type으로 접근하기 때문에 `"op": "{mode}`와 `path`를 사용하여 변경



##### port forward

```
$ kubectl port-forward svc/istio-ingressgateway -n istio-system 8080:80
```













