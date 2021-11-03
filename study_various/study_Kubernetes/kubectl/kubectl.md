# kubectl

kubenetes에서 cluster 조작은 모두 kubenetes master의 API를 통해 이루어진다. 직접 API에 요청을 보내거나 클라이언트 라이브러리를 사용하여 cluster를 조작할 수도 있지만, 수동으로 조작하는 경우에는 CLI 도구인 kubectl을 사용하는 것이 일반적이다.



kubectl이 kubenetes master와 통신할 때는 접속 대상의 서버 정보, 인증 정보 등이 필요하다. kubectl은 kubecofig(기본 위치는 ~/.kube/config)에 쓰여 있는 정보를 사용하여 접속한다. 

> kubeconfig도 manifest와 동일한 형식으로 작성된다.

kubeconfig에서 구체적으로 설정이 이루어지는 부분은 clusters, users, contexts 세 가지다. 이 세 가지 설정 항목은 모두 배열로 되어 있어 여러 대상을 등록할 수 있다.





#### install 

1. WSL설치

2. Docker Desktop for windows설치

3. Docker Desktop for windows의 preference에서 kubernetes에

   Enable Kubernetes 선택 (활성화)

   > 왼쪽 하단에 docker running과 kubenetes running이 떠야 한다.

4. kubectl 설치

   **직접 설치**

   - windows
   
     ```
     $ curl -LO "https://dl.k8s.io/release/v1.22.0/bin/windows/amd64/kubectl.exe"
     ```

     설치됐는지 버전 확인
   
     ```
     $ kubectl version --client
     ```
   
     




### initial

- 컨텍스트 전환(local에서 kind사용시)

  여러 kubernetes를 사용하는 경우에는 kubectl의 컨텍스트를 전환하여 사용해야 한다.

  ```
  $ kubectl config use-context docker-desktop
  ```

  위 명령어로 컨텍스트를 전환한 후에는 kubectl을 사용하여 Docker Desktop Cluster를 조작할 수 있다.



- 노드 확인

  ```
  $ kubectl get nodes
  ```

  kubectl에서는 local mashin에 기동 중인 docker host를 kubernetes node로 인식한다.



- component 확인

  Docker Desktop for windows의 preference에서 kubernetes에

  `Enable Kubernetes` 선택 (활성화)할 때 `show system container(advanced)`를 선택하면 `docker container ls`명령어로 구성 요소를 확인할 수 있다.

  ```
  $ docker container ls
  ```

  

## command

#### api-resources

사용 가능한 resource목록을 가져온다.

```
$ kubectl api-resources
```

- namespace에 속하는 resource 확인

  ```
  $ kubectl api-resources --namespace=true
  ```

- namespace에 속하지 않는 resource 확인

  > cluster수준의 resource

  ```
  $ kubectl api-resources --namespace=false
  ```



#### create

resource를 생성하는 명령어

```
$ kubectl create -f [manifest_file]
```

> 해당 리소스가 존재할 경우 에러 발생
>
> `manifest_file` : recource정보를 담은 yaml형식의 file

**기본적으로 create보다  `$ kubectl apply`가 더 편하고 안전하기 때문에 apply만 사용하자.**



#### delete

resource를 제거하는 명령어

- manifest file 사용

  ```
  $ kubectl delete -f [manifest_file]
  ```

  > 해당 리소스가 존재하지 않을 경우 에러 발생
  >
  > `manifest_file` : recource정보를 담은 yaml형식의 file

- manifest file 사용 안할 때

  resource종류, resource이름 을 지정하여 삭제

  ```
  $ kubectl delete pod [pod_name]
  ```

  > `pod [pod_name]` : resource종류 중 pod 중에서 pad_name이라는 pod만 제거

  ```
  $ kubectl delete pod --all
  ```

  > pod라는 resource를 종류에 해당되는 것을 모두 제거

**--wait**

kubectl명령어 실행은 바로 완료되지만, kubenetes에 의한 실제 resource 처리는 비동기로 실행되기 때문에 바로 완료되지 않는다. 

`--wait` 옵션을 사용하면 resource의 삭제 완료를 기다렸다가 명령어 실행을 종료할 수 있다.

> delete명령이 끝난 후 `$ kubectl wait` 명령이 진행되는 것임

```
$ kubectl delete -f sample-pod.yaml --wait
```

> resource삭제 완료 대기

**--force**

resource를 강제로 즉시 삭제하는 옵션이다. 

```
$ kubectl delete -f sample-pod.yaml --force
```



#### apply

manifest file에 변경 사항이 있을 경우 resource updata를 하는 명령어

> manifest file에 변경 사항이 있을 경우 태그를 붙여 백업한다.
>
> ```
> $ cp -av sample-pod.yaml{, .lod}
> ```
>
> `sample-pod.yaml` 라는 manifest file이 `$ kubectl create`에 의해 이미 등록되어 있는 상태에서 `sample-pod.yaml`에 변경이 있을 경우
>
> 변경된 `sample-pod.yaml` 라는 manifest file을 `sample-pod.yaml.old` 로 태그를 붙여 백업한다.

- **diff**

  두 개의 manifest file을 비교하여 변경 사항이 있는지 확인

  ```
  $ diff sample-pod.yaml.old sample-pod.yaml
  ```

  > `sample-pod.yaml.old` : 변경된 후 .old라는 태그가 붙여진 sample-pod.yaml file
  >
  > `sample-pod.yaml` : 변경되기 전 `$ kubectl create`에 의해 등록된 resource

```
$ kubectl applty -f sample-pod.yaml
```

> 기존에 등록된 `sample-pod.yaml`라는 파일에 변경사항이 있다면 업데이트
>
> 등록된 resource가 없는 경우 `$ kubectl create` 와 같은 동작을 한다.

kubenetes는 생성한 resource 상태를 내부에 기록한다. 한 번 기록된 resource의 field대부분은 변경 가능하지만, 변경 불가능한 field도 있다는 점을 기억하자.



#### wait

kubectl 명령어를 연속적으로 실행하여 resource를 조작할 때, 다음 명령령어를 실행하기 전에 그때까지 작업한 resource가 의도한 상태가 된 후 다음 명령어를 실행하도록 한다.

> pod를 예시로 들어본다. (pod외 어떠한 resource에 대해서도 똑같이 사용 가능)

- `--for` : 특정 상태를 지정

  - `condition=Ready pod` : pod가 기동(ready)하는 상태

    ```
    $ kubectl wait --for=condition=Ready pod/sample-pod
    ```

    > sample-pod가 정상적으로 기동할 때 까지 대기

  - `condition=PodScheduled pod` : pod가 PodScheduled 하는 상태

    ```
    $ kubectl wait --for=condition=PodScheduled pod --all
    ```

    > 모든 pod가 스케줄링 될 때 까지 대기 

  - `delete pod` :  pod 가 삭제되는 상태

    ```
    $ kubectl wait --for=delete pod --all
    ```

    > 모든 pod가 삭제될 때 까지 대기

- `--timeout` : 기다리는 마지노선 시간. 할당한 시간까지 명령어 실행이 안되면 timeout한다.

```
$ kubectl wait --for=delete pod --all --timeout=5s
```

> 모든 pod가 삭제될 때 까지 pod마다 최대 5초씩 대기.



```
$ kubectl wait --for=condition=Ready -f manifest_file.yaml
```

> manifest file을 지정하고 resource가 정상적으로 기동할 때 까지 대기



#### label

- 추가

  ```
  $ kubectl label pods sample-label label3=val3
  ```

  > `kubectl label` : annotation추가 명령어
  >
  > `pods` : taget file의 resource종류
  >
  > `sample-label` :  taget file의 name
  >
  > `label3=val3` : 추가할 label

- 덮어 쓰기 허용

  ```
  $ kubectl label pods sample-annotations label3=val3-new --overwrite
  ```

  > `-new ` : label3이 존재하지 않으면 추가
  >
  > `--overwrite` : 이미 label3이 존재하면 덮어쓰기

- 확인

  ```
  $ kubectl get pod sample-annotations -o json | jp .metadata.labels
  ```

- delete

  ```
  $ kubectl label pods sample-label label-
  ```

  > `label3-` : 삭제할 label의 이름 (뒤에 `-`가 붙으면 삭제명령어)





#### annotate

- 추가

  ```
  $ kubectl annotate pods sample-annotations annotation3=val3
  ```

  > `kubectl annotate` : annotation추가 명령어
  >
  > `pods` : taget file의 resource종류
  >
  > `sample-annotations` :  taget file의 name
  >
  > `annotation3=val3` : 추가할 annotation

- 덮어 쓰기 허용

  ```
  $ kubectl annotate pods sample-annotations annotation3=val3-new --overwrite
  ```

  > `-new ` : annotation3이 존재하지 않으면 추가
  >
  > `--overwrite` : 이미 annotation3이 존재하면 덮어쓰기

- 확인

  ```
  $ kubectl get pod sample-annotations -o json | jp .metadata.annotation
  ```

- delete

  ```
  $ kubectl anotata pods sample-annotations annotation3-
  ```

  > `annotation3-` : 삭제할 annotation의 이름 (뒤에 `-`가 붙으면 삭제명령어)



#### edit

편집기 상에서 변경 작업이 가능하게 하는 명령어 

> 편집기는 환경 변수 EDITOR 또는 KUBE_EDITOR로 지정할 수 있다.

```
$ export EDITOR=vim
```

>  환경 변수  EDITOR에 vim을 일시적으로 정의 (~/.bashrc등에 추가하면 영구적으로 가능)

**서식** : `kubectl edit resource종류 resource명`

```
$ kubectl edit pod sample-pod
```

> kind : pod 중  name : sample-pod 인 것을 편집기로 편집 시작



#### set

manefest file을 updata하지 않고 일부 설정값(또는 이 설정값을 가진 특정 resource)만 간단히 동작 상태를 변경할 수 있다.

**변경 가능한 설정값**

- env
- image
- resources
- selector
- serviceaccount
- subject

**서식** : `kubectl set 설정값 resource종류 resource명 container명=container_이미지`

```
$ kubectl set image pod sample-pod nginx-container=nginx:1.16
```



#### get

resource정보를 가져오는 명령어

**서식** : `kubectl get resource종류 resource명`

```
$ kubectl get pods 
```

> pod 목록 가져오기

```
$ kubectl get pods sample-pod
```

> sample-pod라는 이름의 특정 pod가져오기

```
$ kubectl get pods -l label=val1, label2 --show-labels
```

> labels에 label=val1의 key-value값과 label2가 포함된 pod를 label을 표시하여 출력

```
$ kubectl get nodes
```

> node 정보 출력

```
$ kubectl get all
```

> all 카테고리에 속하는 resource목록을 출력

**`-o`** : 출력 옵션

- `-o wide` : 더 상세히 표시

  ```
  $ kubectl get pods -o wide
  ```

- `-o yaml` : 아주 상세히 표시

  ```
  $ kubectl get pods -o yaml
  ```

  ```
  $ kubectl get pods sample-pod -o yaml 
  ```

- `-o jsonpath="{}"` : 특정 값 검색

  ```
  $ kubectl get pods -o jsonpath="{.metadata.name}"
  ```

  > 모든 pod의 matadata.name을 출력





#### describe

특정 resource를 자세히 출력한다.

**서식** : `kubectl describe resource종류 resource명`

```
$ kubectl describe pod sample-pod
```

> kind : pod 중  name : sample-pod 인 것을 관련 event와 자세한  information을 포함하여 출력



#### diff

'실제로 kubenetes cluster에 등록된 정보''와 'local에 있는 manifest'내용의 차이를 확인할 수 있다.

`kubel diff`명령어의 종료 코드는 '실제 cluster에 등록된 정보'와 'local에 있는 manifest file'간에 차이가 있으면 1을 retrun, 차이가 없으면 0을 return한다.

**서식** : `kubectl diff -f [manifest_name]`

```
$ kubectl diff -f sample-pod.yaml
```

> 상태 코드 확인
>
> ```
> $ echo $?
> 1
> ```
>
> > 1반환 : 차이 있음



#### top

실제 resource사용량을 확인하는 명령어로, kubenetes가 resource에 확보한 값을 나타낸다. 

resource사용량은 node와 pod단위로 확인한다.

```
$ kubectl top node
$ kubectl top pod
```

- `-n namespace` 옵션 사용

  ```
  $ kubectl -n kube-system top pod
  ```

  > `kube-system` 이라는 namespace로 기동중인 pod의 현황 조회

- `--containers` : container별 resource사용량 확인

  ```
  $ kubectl -n kube-system top pod --containers
  ```

  

#### exec

pod내부의 container에서 명령어 실행

`/bin/bash`등의 shell을 실행함으로써 container에 로그인 한 것과 같은 상태를 만들 수 있다.

**`-it`** : `-i` : 표준 입출력을 패스스루 , `-t` :가상 터미널 생성 

**서식** : `kubectl exet -it resource명 -- /bin/command명령어`

```
$ kubectl exet -it sample-pod -- /bin/ls
```

> `sample-pod` 라는 pod안의 container에서 bin/ls실행

```
$ kubectl exet -it sample-pod  -c sample-container -- /bin/ls
```

> `sample-pod` 라는 pod안의 `sample-container` 라는 container에서 bin/ls실행

```
$ kubectl exet -it sample-pod -- /bin/bash
root@sample-pod:/#
```

> pod 내부의 container에서 bin/bash실행



#### logs

container의 log를 확인하는 명령어

```
$ kubectl logs sample-pod
```

> pod내의 container log출력

```
$ kubectl logs sample-pod -c sample-container
```

> pod내의 특정container log출력



```
$ kubectl logs -f sample-pod
```

> pod내의 container의 실시간 log출력

````
$ kubectl logs --since=1h --tail=10 --timestamps=true sample-pod
````

> 최근 1시간 이내, 10건의 log를 타임스탬프와 함께 출력



#### cp

container와 local mashin간의 file복사

container에서 local mashin으로, local mashin에서 container로(양방향) 파일 복사가 가능하다.

**서식** : 

- container > local host : `kubectl cp pod명:file_path local_path `

  ```
  $ kubectl cp sample-pod:etc/hostname ./hostname
  ```

  > file 확인
  >
  > ```
  > $ cat hostname
  > ```

- local host > container  : `kubectl cp local_file_path pod명:container_path`

  ```
  $ kubectl cp hostname sample-pod:/tmp/newfile
  ```

  > 확인
  >
  > ```
  > $ kubectl exec -it sample-pod -- ls /tmp
  > ```





#### debug

container image로 경량의 Distroless나 Scratch image등을 사용하는 경우 debuging용 도구 등이 전혀 들어 있지 않기 때문에, 문제가 발생했을 때 kubectl exec명령어를 사용하여 컨테이너 안으로 들어가도 디버깅을 수행하기가 어렵다. 이 문제를 해결하는 명령어가 debug이다.

이 명령어는 pod에 추가 임시 container를 기동하고 그 container를 사용하여 디버깅이나 troubleshooting을 수행한다.

p.151



#### port-forward

kubectl을 실행하는 local mashin에서 특정 pod로 트래핃을 전송하는 명령어

p.152



### tips

**option : `-v`**

kubectl명령어를 실행할 때 -v옵션으로 log level을 지정하면 명령어 실행 내용을 좀 더 상세히 볼 수 있다.

- `-v=6` : resource등을 생성했을 때 HTTP Request/Response내용을 표시하는 경우
- `-v=8` : Request Bocy/Response Body까지 확인할 때

```
$kubectl -v=6 get pod
```



**alias생성**

서식 : `alias 대체명령어='기존명령어'`

```
$ alias k='kubectl'
$ alias k='pods'

$ k get po 	
```

>  kubectl get pods 와 같은 명령어



**pod가 기동하지 않는 경우의 디버깅**

kubenetes환경에서 pod가 기동하지 않는 경우에는 세 가지 방법의 디버깅 방법이 주로 사용된다.

1. `kubectl logs`명령어를 사용하여 container가 출력하는 log를 확인하는 방법

   주로 application에 문제가 있을 떄 유용하다.

2. `kubectl describe` 명령어로 표시되는 Events항목을 확인하는 방법이다. 

   주로 kubenetes 설정이나 resource설정에 문제가 있을 때 유용하다.

3. `kubectl run` 명령어를 사용하여 실제 container shell로 확인하는 방법이다.

   container환경이나 application에 문제가 있을 때 유용하다
