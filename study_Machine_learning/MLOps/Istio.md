# Istio

Ingress 및 Egress gateway를 관리하며, user의 custom gateway를정의하는 사용자 정의 resource를 작성할 수 있다.



**install** 

kubeflow설치하면서 포함시켜야 된다.

[github](https://github.com/kubeflow/manifests)



설치 후 istio-system namespace를 확인하면 service resource(pod)가 있음을 확인할 수 있다.

```
$ kubectl get svc -n istio-system
```

```
NAME                    TYPE           CLUSTER-IP       EXTERNAL-IP   PORT(S)
istio-ingressgateway    LoadBalancer   10.102.172.178   <pending>     15021:32503/TCP,80:30116/TCP,443:31897/TCP,31400:31214/TCP,15443:30902/TCP  
```

