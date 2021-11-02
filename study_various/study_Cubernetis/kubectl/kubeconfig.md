# kubeconfig

>  manifest와 kubeconfig 파일은 모두 yaml형식으로 작성된다.



kubeconfig 의 기본 위치는 `~/.kube/config` 이다.

kubeconfig에서 구체적으로 설정이 이루어지는 부분은 clusters, users, contexts 세 가지다. 이 세 가지 설정 항목은 모두 배열로 되어 있어 여러 대상을 등록할 수 있다.





contexts/users/clusters 의 관계

![](https://ssup2.github.io/images/theory_analysis/Kubernetes_kubeconfig/kubeconfig.PNG)

> namespace는 옵션과 같다.



#### apiVersion, kind, preference

```yaml
apiVersion : v1
kind : Config
preference : {}
```



#### clusters

접속 대상 cluster를 결정한다.

```yaml
# kubeconfig.yaml
clusters : 
	- name: sample-cluster # cluster이름
  	cluster : 
  		server : http://localhost:6443	# 접속 대상
        
    - name: ...
```





- **추가 및 변경**

  ```
  $ kubectl config set-cluster [cluster_name] \
  --serve=http://localhost:6443
  ```

  `[cluster_name]` : existing cluster name을 넣으면 안의 내용이 변경되고, new cluster name을 넣으면 새로운 cluster가 추가된다.

  `--serve` : 접속 대상



- **clusters목록 확인**

  ```
  $ kubectl config get-clusters
  ```

  



#### users

인증 정보를 저장한다.

```yaml
# kubeconfig.yaml
users : 
	- name: sample-user # user이름
  	user : 
  		client-certificate-data: LS0...
  		client-key-data: LS0t...
        
    - name: ...
```



- **추가 및 변경**

  ```
  $ kubectl config set-credentials [user_name] \
  --client-certificate=./sample.crt	\
  --client-key=./sample.key	\
  --embed-certs=true
  ```

  `[user_name]` : existing user name을 넣으면 안의 내용이 변경되고, new user name을 넣으면 새로운 user가 추가된다.

  `--client-certificate` : 

  `--client-key` : 

  `--embed-certs` : 



- **users목록 확인**

  ```
  $ kubectl config get-users
  ```



#### contexts

cluster와 user, namespace 등 접속 대상과 인증 정보 조합을 정의한다.

```yaml
# kubeconfig.yaml
contexts : 
	- name: sample-contexts # contexts이름
	contexts :
		cluster : sample_cluster
		namespace : default
		user : sample-user
	
	- name: ...

current-context : sample-contexts	# 현재 context가 자동으로 할당
```



- **추가 및 변경**

  ```
  $ kubectl config set-context [context_name] \
  --cluster=[some_cluster_name]
  --user=[some_user_name]
  --namespace=default
  ```

  `[context_name]` : existing context name을 넣으면 안의 내용이 변경되고, new context name을 넣으면 새로운 context가 추가된다.

  `--cluster` : 접속 대상 cluster의 name

  `--user` : 특정 인증 정보

  `--namespce` : 



- **contexts 목록 표시**

  ```
  $ kubectl config get-contexts
  ```

  

- **context전환**

  ```
  $ kubectl config use-context [context_name]
  ```

  

- **현재 context 표시**

  ```
  $ kubectl config current-context
  ```

  

- **특정 명령어 실행마다 context를 지정할 수 있다.**

  ```
  $ kubectl --context [context_name] get pod
  ```

  > pod를 예시로

