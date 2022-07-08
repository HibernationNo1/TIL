# manifest

쿠버네티스 마스터에 resource를 등록하는 file



### 설계

#### 동시 적용

**multi resource**

한 개의 menifest file에 여러 resource를 정의하거나 여러 menifest file을 동시에 적용할 수 있다.

> 특정 service에서 사용할 여러 종류의 resource를 한 개의 menifest file로 통합할 수 있다.

실행 순서를 정확하게 지켜야 하거나 리소스 간의 결합도를 높이고 싶다면 한 개의 매니페스트를 사용하는 것이 좋다. 

그러나 공통으로 사용하는 설정 파일(configmap resource)이나 패스워드 등은 여러 resource에서 사용되는 경우가 있다. 이렇게 공통으로 사용되는 리소스는 별도 매니페스트로 분리하는 것이 좋다.

**e.g.**  (`---`로 구분하여 작성)

```
---	# 첫 번째 resource
apiVersion : apps/v1
kind: Deploment
metadata : 
	name: ...
...

--- # 두 번째 resource
apiVersion : v1
kind : Service
metadata:
	name: ...
	...
	
```





manifest는 위에서부터 정의된 resource순서대로 적용된다.

manifest file내의 일부 resource정의 부분에 문법 에러 등으로 문제가 발생한 경우, 이후에 정의된 resource는 적용되지 않는다는 점에 주의해야 한다.



**multi manifest file**

manifest file을 동시에 적용하려면 directory 안에 적용하고 싶은 여러 manifest file을 배치해 두고 `$ kubectl apply`명령어를 실행할 때 해당 directory를 지정한다.

> file이름 순으로 manifest file이 적용되기 때문에 순서를 제어하고 싶을 때는 파일명 앞에 연번의 index번호 등을 지정하여 사용하면 된다.

**e.g.**

```
$ kubectl apply -f ./dir
```



dir안에 또 다른 dir이 있고, 이 안의 menifest까지 적용하고자 할 때

```
cwd - dir1 ┬ sample-pod1.yaml
		   ├ sample-pod2.yaml
		   └ dir2 - sample-pod3.yaml
```

```
$ kubectl apply -f ./dir -R
```

> 가장 깊은 위치의 manifest부터 실행
>
> sample-pod3.yaml
>
> sample-pod1.yaml
>
> sample-pod2.yaml





#### manufest file설계 패턴 

1. 하나의 dir에 통합

   아주 규모가 크지 않을 경우에는 system 전체를 구성하기 위한 모든 마이크로서비스의 매니페스트 파일을 하나의 dir로 통합하여 사용하면 좋다.

   한 개의 매니페스트 파일을 적용하면 특정 마이크로서비스를 updata할 수 있고, 디렉터리를 지정하면 전체 파이크로서비스, 즉 system 전체를 updata할 수 있다.

   ```
   cwd - dir  ┬ microservice-A.yaml
   		   ├ microservice-B.yaml
   		   └ microservice-C.yaml
   ```



2. 여러 dir로 분리

   한 개의 dir에 통합이 어려울 정도로 거대한 system인 경우, 분리가 가능하다면 서브 system이나 부서별로 dir를 나눠서 사용하는 것도 하나의 방법이다.

   또한 내부 정책에 따라 grouping이 팔요할 경우 나눠서 관리해도 좋다.

   ```
   cwd - dir  ┬ subsystem-A  ┬ microservice-A.yaml
   		   │			  ├ microservice-B.yaml
   		   │ 			  └ microservice-C.yaml
   		   └ subsystem-B  ┬ microservice-D.yaml
   		   				  ├ microservice-F.yaml
   		   				  └ microservice-E.yaml
   ```



3. 마이크로서비스 별로 dir를 분리

   각각의 마이크로서비스는 한 개의 manifest file로 모든 resource를 관리해도 좋지만, 마이크로서비스마다 dir로 구분하여 resource 종류별로 파일을 생성할 수도 있다.

   이 방법은 가독성이 높아진다는 장점이 있지만, 적용 순서 제어가 어렵다는 단점도 있다.

   ```
   cwd - dir  ┬ microservice-A  ┬ deployment.yaml
   		   │			     └ service.yaml
   		   │ 			     
   		   └ microservice-B  ┬ deployment.yaml
   		   	  			     └ service.yaml			
   ```



## 구성

### apiVersion

### Kind



### metadata

#### annotation

resource에 대해 metadata에 부여할 수 있는 data

system 구성 요소가 사용하는 metadata로, resource에 대한 메모 같은 것이다.

##### purpose

- system 구성 요소를 위한 data 저장
- 모든 환경에서 사용할 수 없는 설정 
- 정식으로 통합되기 전의 기능을 설정



##### 직접 typing

**서식** : [접두사]/키:값

annotation 자체는 단순한 key-value값이기 때문에 annotation값으로 어떤 처리를 하는 system구성 요소가 없을 경우에는 아무 일도 일어나지 않는다.

> 그러므로 resource에 의미를 가지지 않는 메모를 하고 싶을 경우에도 사용할 수 있다.

```yaml
apiVersion : v1
kind : Pod
metadata: 
	name: sample-annotation
	annotation1: val1	# annotation = 접두사, 1 = 키, val = 값
	annotation2: "200"	# 값이 숫자일 경우 ""로 감싸준다.
```



##### kubectl 사용

`$ kubectl annotate`

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





#### label

resource에 대해 metadata에 부여할 수 있는 data

resource관리에 사용하는 metadata로, resource를 구분하기 위한 정보이며 `metadata.labels`에 설정할 수 있다.



##### 직접 typing

**서식** : [접두사]/키:값

```yaml
apiVersion : v1
kind : Pod
metadata: 
	name: sample-annotation
	labels:		# metadata.labels 아래 설정
		label1:	val1	# label = 접두사, 1 = 키, val = 값
		label2:	val2
```



##### kubectl 사용

`$ kubectl label`

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



##### grouping

container는 하나의 process와 거의 같은 아주 작은 resource다. 또한 pod도 여러 container로 이루어진 작은 resource다. cluster는 pod와 같이 작은 resource를 대량으로 처리한다.

label은 이러한 수많은 resource에 대해 동일한 label로 grouping하여 처리하거나 어떤 처리에 대한 조건으로 사용되기 때문에 resource를 효율적으로 관리할 수 있는 구조를 가지고 있다.

- **개발자가 사용하는 label**

  resource에 부여된 label을 사용하여 대상 resource를 filtering함으로써 운영한다.

  **filtering option** : `-l`

  `-l`으로 label을 지정하면 해당 label이 있는 resource만 가져온다.

  ```
  $ kubectl get pods -l label1
  ```

  > labels안에 label1이 있는 resource

  ```
  $ kubectl get pods -l label1=val
  ```

  > labels안에 label1=val이 있는 resource

  ```
  $ kubectl get pods -l label1=val, label2
  ```

  > labels안에 label1=val이 있고, 동시에 label2가 있는  resource

  **지정한 label확인** : `-L`

  목록을 표시하는 option이다.  (단, filtering기능을 사용하지 않아서 다른 resource도 같이 표시된다.)

  ```
  $ kubectl get pods -L label1
  ```

  

  ```
  $ kubectl get pods -l label1 -L label2
  ```

  > label1이 저장된 pod의 label2를 확인

  

  **모든 label표시** : `--show-labels`

  ```
   $ kubectl get pods --show-labels
  ```

  

- **system이 사용하는 label**

   label 자체는 단순한 key-value값이지만, 실수로 label을 지정하면 label 값이 충돌하여 예상하지 못한 문제가 발생할 수 있다. 

  이를 방지하기 위해 처음부터 system에 따라 label을 지정할 정책을 정하고 설계하는 것이 좋다.

  **권장되는 label-key 이름**

  | label key name              | overview                             |
  | --------------------------- | ------------------------------------ |
  | app.kubenetes.io/name       | app이름                              |
  | app.kubenetes.io/version    | app버전                              |
  | app.kubenetes.io/component  | app내 구성 요소                      |
  | app.kubenetes.io/part-of    | app이 전체적으로 구성하는 system이름 |
  | app.kubenetes.io/instance   | app이나 system을 식별하는 instance명 |
  | app.kubenetes.io/managed-by | app을 관리하는데 사용되는 도구       |

  



### spec