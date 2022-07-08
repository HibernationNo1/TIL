# resource



#### Pod

쿠버네티스는 Pod단위로 스케줄링, 로드밸런싱, 스케일링 등의 관리 작업을 수행한다.

> 쿠버네이트에 어떤 application을 배포하고 싶다면 최소 Pod로 구성해야 한다.

하나의 Pod는 한 개의 container 혹은 여러개의 contrainer로 이루어져 있으며, Pod내부의 여러 container는 자원을 공유한다. 



Pod는 IP를 할당받고 생성되지만, 언제든지 죽었다가 다시 살아날 수 있으며, 그 과정에서 IP는 재할당받는다.(때문에 고정된 IP로는 원하는 Pod에 접근할 수 없다. ) 		stateless함

따라서 cluster외부 혹은 내부에서 Pod에 접근할 때는 Service resource를 통해서 접근하는 방식을 거친다. 



**create**

```
$ minikube start --driver=docker
```

```
$ vi pod.yaml
```



**예시**

counter라는 이름의 pod생성

```yaml
apiVersion: v1
kind : Pod
metadata :
  name : counter	# 띄어쓰기 2칸
spec:
  containers:	
  - name: count		# 띄어쓰기 2칸 - 띄어쓰기 1칸
    image: busybox
    args : [/bin/sh, -c, 'i=0; while true; do echo "$i: $(data)"; i=$((i+1)); sleep 1; done']

```

- `apiVersion` : kubenetes resource의 API version
- `Kind` : kubenetes resource 종류
- `metadata` : name, namespace, labels, annotations 등을 포함
- `spec` : resource의 desired state를 명시
  - `name` : container의 이름
  - `image` : container의 image
  - `args` : 해당 image의 entrypoint의 args로 입력하고 싶은 값

거의 모든 kubenetes의 resource는 `apiVersion`, `Kind`, `metadata`, `spec` 으로 이루어져 있다.



```
$ kubectl apply -f pod.yaml
```

 

check status

```
$ kubectl get pod counter 
```

> Contrainer Creating > running



> delete pod
>
> ```
> $ kubectl delete pod counter
> ```





**pod로 접근**

1. check IP

   ```
   $ kubectl get pod -owide
   ```

   ```
   NAME     READY   STATUS    RESTARTS   AGE   IP           NODE       NOMINATED NODE   READINESS GATES
   counter   1/1     Running  0          34m   172.17.0.7   minikube   <none>           <none>
   
   ```

   > IP가 `172.17.0.7`임을 확인

2. kubenetes 내부로 접속

   minikube인 경우

   ```
   $ minikube ssh
   ```

   > ssh 프로토콜로 kubenetes안으로 접속했음을 의미

   ```
   docker@minikube:~$  ping 172.17.0.6  			# ping 찍어보기
   ```

   kubenetes 외부에서 접근하려면 Service를 이용해야 한다.

   







#### Deployment

deployment

pod와 prelicaset에 대한 관리를 제공하는 단위로, pod를 감싼 개념이다.

pod를 deployment로 배포함으로써 여러 개로 복제된 pod, 여러 version의 pod를 안전하게 관리할 수 있다.



**create**

```
$ vi deployment.yaml
```

```yaml
apiVersion: apps/v1		# kubenetes resource의 API version
kind: Deployment
metadata: 		
  name: nginx-deployment
  labels:
    app: nginx
spec:					# main part
  replicas:  3 		# 동일한 template의 pod를 3개 생성 (copy)
  selector:
    matchLabels:
      app: nginx
  template:			# pod의 template을 의미
    metadata:			
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx				# container의 이름
        image: nginx:1.14.2		# container의 image
        ports:
        - containerPort: 80		# container의 내부 port
```



```
$ kubectl apply -f deployment.yaml
```



check status

```
$ kubectl get deployment nginx-deployment
```

> pod도 함께check
>
> ```
> $ kubectl get deployment,pod 
> ```
>
> ```
> NAME                               READY   UP-TO-DATE   AVAILABLE   AGE
> deployment.apps/nginx-deployment   3/3     3            3           3m9s
> 
> NAME                                    READY   STATUS    RESTARTS   AGE
> pod/nginx-deployment-6595874d85-cd2v4   1/1     Running   0          3m9s
> pod/nginx-deployment-6595874d85-q6f2j   1/1     Running   0          3m9s
> pod/nginx-deployment-6595874d85-qnfzs   1/1     Running   0          3m9s
> ```
>
> 여기서 `nginx-deployment-6595874d85-cd2v4` 처럼 각 pod당 name에 `6595874d85-cd2v4` 와 같은 시리얼 넘버가 붙으며 고유 이름이 만들어짐
>
> 이를 확인하려면
>
> ```
> $ kubectl get pod nginx-deployment-6595874d85-cd2v4
> ```



> delete
>
> ```
> $ kubectl delete deployment <deployment-name>
> ```
>
>  또는
>
> ```
> $ kubectl delete -f <.yaml path>
> ```
>
> 





- Auto-healing

  ```
  $ kubectl delete pod nginx-deployment-6595874d85-cd2v4
  ```

  위 처럼 deployment안의 pod를 삭제해도, 3개가 유지될 수 있도록 새로운 하나가 더 자동으로 생성됨

- Scaling

  위 deployment의 replicas 개수에 변화를 줄 수 있다.

  ```
  $ kubectl scale deployment/nginx-deployment --replicas=5
  ```

  ```
  $ kubectl get deployment,pod  
  ```

  > 3개에서 5개로 늘어난것을 확인. 줄일수도 있다.



#### Service

kubenetes에 배포한 application(Pod)을 외부에서 접근하기 쉽게 추상화 한 resource

Service는 고정된 IP를 가지며, 한 개 이상의 pod와 매칭된다. 

> client가 service의 IP주로소 접근하면 Service에 매칭된 Pod에 접속할 수 있게 된다.



##### type of service

- **NodePort**

  kubernetes cluster외부에서 kubernetes cluster내부에 배포된 serivce에 접근할 수 있게 된다.

  > mapping 된 pod가 scheduling된 node의 IP는 그대로 사용하되, port는 따로 사용할 수 있게 된다.

  none의 ip확인

  ```
  $ minikube ip
  ```

  > minikube 자체가 node가 1개인 cluster

  - 단점

     cluster 내부에 서버가 여러개라, Node또한 여러개가 존재하는 경우  Pod가 어떤 Node에 scheduling될지 모르는 상황에서, Pod가 할당된 후 해당 Node의 IP를 알아야 한다.

- **LoadBalancer**

  LoadBalancing역할을 하는 module이 추가적으로 있는 경우, 외부에서 kubernetes cluster내부에 배포된 serivce에 접근할 수 있게 된다.

  > 실무에서는 주로 kubernetes cluster에 MetalLB와 같은 LoadBalancing역할을 하는 module을 설치한 후 LoadBalancer type으로 service를 expose한다.

- **ClusterIP**

  고정된 IP, Port를 제공하지만, cluster 내부에서만 접근할 수 있는 대역의 주소가 할당



**create**

>  deploment가 있다는 전제
>
> ```
> $ kubectl get deployment,pod -owide  
> ```
>
> ```
> NAME                               READY   UP-TO-DATE   AVAILABLE   AGE   CONTAINERS   IMAGES         SELECTOR
> deployment.apps/nginx-deployment   5/5     5            5           42m   nginx        nginx:1.14.2   app=nginx
> 
> NAME                                    READY   STATUS    RESTARTS   AGE   IP           NODE       NOMINATED NODE   READINESS GATES
> pod/nginx-deployment-6595874d85-2v5kr   1/1     Running   0          32m   172.17.0.7   minikube   <none>           <none>
> pod/nginx-deployment-6595874d85-cd2v4   1/1     Running   0          42m   172.17.0.4   minikube   <none>           <none>
> pod/nginx-deployment-6595874d85-q6f2j   1/1     Running   0          42m   172.17.0.3   minikube   <none>           <none>
> pod/nginx-deployment-6595874d85-qnfzs   1/1     Running   0          42m   172.17.0.5   minikube   <none>           <none>
> pod/nginx-deployment-6595874d85-rxf4m   1/1     Running   0          32m   172.17.0.6   minikube   <none>           <none>
> 
> ```



```
$ vi service.yaml
```

```yaml
apiVersion : v1
kind : Service
metadata:
  name: my-nginx
  labels:
    run: my-nginx
spec:
  type: NodePort		# service의 type을 명시
  ports:
  - port: 80
    protocol: TCP
  
  selector:		# 아래 app와 같은 metadata.labels.app 을 가진 Pod를 모두 매핑한다.
    app: nginx
```

```
$ kubectl apply -f service.yaml
```



**외부에서 service로 접근**

```
$ kubectl get service
```

```
NAME         TYPE        CLUSTER-IP       EXTERNAL-IP   PORT(S)        AGE
kubernetes   ClusterIP   10.96.0.1        <none>        443/TCP        111m
my-nginx     NodePort    10.101.175.134   <none>        80:30256/TCP   34s
```

> 1. service 의 port : `30256`
>
> 2. ```
>    $ minikube ip
>    ```
>
>    `192.168.49.2`

```
$ curl -X GET $(minikube ip):30256
```

> 클러스터 외부임에도 -X GET에 대한 응답이 있다.





#### PVC

Persistent Volume Claim(PVC) 

stateless한 Pod가 영구적으로(persistent)데이터를 보존하고 싶은 경우 사용하는 resource

Pod는 기본적으로 stateless하기에 내부에서 작성한 data가 언제든지 사라잘 수 있다. 이러한 data를 보존하고 싶은 경우 Pod에 PVC를 mount해서 사용해야 한다.

> PVC를 사용하면 pod간의 data공유도 쉽게 가능하다.



**create**

```
$ vi pvc.yaml
```

``` yaml
apiVersion : v1
kind: PersistentVolumeClaim
metadata:
  name: myclaim
spec:						# kind: PersistentVolumeClaim 인 경우 spec : PVC의 정보를 입력하는 part
  accessModes:				# ReadWriteMany 또는 ReadWriteOnce
    - ReadWriteMany
  volumeMode: Filesystem
  resources:
    requests:	
      storage: 10Mi			# storage용량을 설정
  storageClassName: standard		# storageclass의 name을 입력
```

> minukube를 생성하면, 기본적으로 storageclass가 한 개 생성된다.
>
> ```
> $ kubectl get storageclass
> ```
>
> ```
> NAME                 PROVISIONER                RECLAIMPOLICY   VOLUMEBINDINGMODE   ALLOWVOLUMEEXPANSION   AGE
> standard (default)   k8s.io/minikube-hostpath   Delete          Immediate           false                  148m
> 
> ```
>
> 이름 : `standard` 확인  >> spec.storageClassName 의 값으로 할당

```
$ kubectl apply -f pvc.yaml
```



```
$ kubectl get pvc
```

> ```
> $ kubectl get pvc,pv
> ```



**pod에서 PVC사용**

1. 위 pvc를 mount하는 pod생성

   ```
   $ vi pod-pvc.yaml
   ```

   ```yaml
   apiVersion: v1
   kind : Pod
   metadata :
     name : mypod
   spec:
     containers:	
     - name: myfrontend
       image: nginx
       volumeMounts:
       - mountPath: "/var/www/html" 	# persistentVolumeClaim.claimName 라는 PVC를 매칭시킬 경로
         name: mypd					# 어떤 이름이든 상관없으나, 아래 volumes[0].name과 일치해야 함
     volumes:
     - name: mypd						# 어떤 이름이든 상관없으나, 위의 volumeMounts[0].name과 일치해야 함
       persistentVolumeClaim:
         claimName: myclaim				# mount할 pvc의 name을 적는다.
   ```

   > 해당 pod안에는 `/var/www/html` 라는 경로가 있는 상태로 생성되며, 이 경로는 pvc와 바로 매칭된다.

   ```
   $ kubectl apply -f pod-pvc.yaml
   ```

   

   ```
   $ kubectl get pod
   ```

   



2. mount위치에 data 보존 확인

   pod에 접속하여 mount한 path와 그 외의 path에 file생성

   ```
   $ kubectl exec -it mypod -- bash
   ```

   ````
   root@mypod:/# touch hibernation_1		# 기본 위치에 hibernation_1라는 file 생성
   
   root@mypod:/# cd /var/www/html			# mount 한 위치에 hibernation_2라는 file 생성
   root@mypod:/# touch hibernation_2
   ````

   

   pod를 삭제해본다

   ```
   $ kubectl delete pod mypod
   ```

   

   pvc는 그대로 남아있는지 확인

   ```
   $ kubectl get pvc,pv
   ```

   ```
   AME                            STATUS   VOLUME                                     CAPACITY   ACCESS MODES   STORAGECLASS   AGE
   persistentvolumeclaim/myclaim   Bound    pvc-579c1973-6367-4863-bd65-e95ac5c2c79b   10Mi       RWX            standard       32m
   
   NAME                                                        CAPACITY   ACCESS MODES   RECLAIM POLICY   STATUS   CLAIM             STORAGECLASS   REASON   AGE
   persistentvolume/pvc-579c1973-6367-4863-bd65-e95ac5c2c79b   10Mi       RWX            Delete           Bound    default/myclaim   standard                32m
   
   ```

   그대로 남아있음

   

   해당 pvc를 mount하는 pod를 다시 생성

   ```
   $ kubectl apply -f pod-pvc.yaml 
   ```

   

   다시 pod에 접속하여 기본 위치에 생성했던 `hibernation_1` 와  mount한 path에 생성했었던 `hibernation_2`가 존재하는지 확인

   ```
   $ kubectl exec -it mypod -- bash	
   ```

   ```
   root@mypod:/# ls 	
   ```

   > hibernation_1 없음

   ```
   root@mypod:/# cd /var/www/html
   root@mypod:/# ls 	
   ```

   > hibernation_2가 있음

   즉, pod의 특정 path를 pvc와 매칭 시키면, 해당 pod가 삭제되고 다시 생성되더라도 해당 경로에는 모든 data가 남아있다.





