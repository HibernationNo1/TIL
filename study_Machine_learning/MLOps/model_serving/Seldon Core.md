# Seldon Core

kubernetes에서 model serving을 쉽게 할 수 있도록 도와주는 Framework중 하나



#### **install** 

ingress

- kubernetes( < v1.18)

- kubectl

- Helm 3

- python > 3.6

- Istio or Ambassador v1

  > Ambassador 는 어떤 version으로 하든 안되니까 하지말자

[공식](https://docs.seldon.io/projects/seldon-core/en/latest/workflow/install.html)

1. start kubernetes (minikube)

   ```
   $ minikube start --driver=docker --cpus='4' --memory='4g'
   ```

2. install Helm

   [공식](https://helm.sh/docs/intro/install/)

   [여기](https://github.com/helm/helm/tags) 에서 원하는 version을 선택 후 뜨는 page에서

   `Installation and Upgrading` 아래 binary file들의 link를 확인할 수 있다.

   `linux amd64` 를 왼쪽 클릭 > 링크 주소 복사 

   ```
   $ wget https://get.helm.sh/helm-v3.5.4-linux-amd64.tar.gz
   ```

   > 예시v 3.5.4

   ```
   $ tar -zxvf helm-v3.5.4-linux-amd64.tar.gz
   ```

   ```
   linux-amd64/
   linux-amd64/helm
   linux-amd64/LICENSE
   linux-amd64/README.md
   ```

   binary PATH로 이동

   ```
   $ sudo mv linux-amd64/helm /usr/local/bin/helm
   ```

   > `linux-amd64/helm` 에서 `/usr/local/bin/helm` 으로

   check

   ```
   $ helm version
   ```

   > [uninstall](https://helm.sh/docs/faq/uninstalling/) :
   >
   > ```
   > $ which helm			# /some/path/to/helm
   > $ rm /some/path/to/helm
   > ```

3. install istio

   [공식](https://istio.io/latest/docs/setup/getting-started/)

   download Istio

   ```
   $ curl -L https://istio.io/downloadIstio | sh -
   ```

   > 최신 version으로 dir이 하나 생김

   ```
   $ cd istio-1.14.1			# version확인
   $ export PATH=$PWD/bin:$PATH
   ```

   install 

   > profile은 default 외에도 여러가지가 있다. 관련 설명은 [여기](https://ubuntu.com/tutorials/install-istio-on-charmed-distribution-of-kubernetes#4-choose-a-configuration-profile)

   ```
   $ istioctl install --set profile=default
   ```

   Add a namespace label to instruct Istio

   ```
   $ kubectl label namespace default istio-injection=enabled
   ```

4. install seldon-core whith Istio  (ambassador은 어떠한 version으로도 설치 안되니 하지 말 것)

   [공식](https://docs.seldon.io/projects/seldon-core/en/latest/workflow/install.html)

   create namespace

   ```
   $ kubectl create namespace seldon-system
   ```

   install delon-core operator (in seldon-system namespace )

   ```
   $ helm install seldon-core seldon-core-operator \
       --repo https://storage.googleapis.com/seldon-charts \
       --set usageMetrics.enabled=true \
       --set istio.enabled=true \
       --namespace seldon-system
   ```

   check

   ```
   $ kubectl rollout status deploy/seldon-controller-manager -n seldon-system		# rollout 잘되었는지 확인
   $ kubectl get pod -n seldon-system
   ```

   ```
   NAME                                         READY   STATUS    RESTARTS   AGE
   seldon-controller-manager-55f7cdf8d9-pzmfx   1/1     Running   0          3m57s
   ```

   Istio로 seldon-core을 설치하면 gateway을 배포해야 함

   ```
   $ vi gateway.yaml
   ```

   ```
   apiVersion: networking.istio.io/v1alpha3
   kind: Gateway
   metadata:
     name: seldon-gateway
     namespace: istio-system
   spec:
     selector:
       istio: ingressgateway # use istio default controller
     servers:
     - port:
         number: 80
         name: http
         protocol: HTTP
       hosts:
       - "*"
   ```

   ```
   $ kubectl apply -f gateway.yaml
   ```

   



## Seldon Deployment

seldon core에서 정의한 Custom Resource중 하나로, 이미 학습이 완료된 model을 load해서 serving하는 server이다.

> flask를 사용해서 작업했던 API를 정의하거나 ip, port를 정의하거나 kubernetes에 배포하기 위한 docker build, push, pod yaml작성과 같은 작업을 할 필요 없이, trained model의 .pkl format file의 path만 전달하면 자동화되는 기술

### example 

[한국어 도움](https://incredible.ai/kubernetes/2020/09/25/Seldon-Core/)

##### create

1. create namespace 

   Seldon Deployment를 생성할 용도의 namespace 

   ```
   $ kubectl create namespace seldon_exam
   ```

2. create SeldonDepolyment yaml

   ```
   $ vi seldon_exam.yaml
   ```

   ```yaml
   apiVersion: machinelearning.seldon.io/v1
   kind: SeldonDeployment
   metadata:
     name: iris-model		# model name
     namespace : seldon_exam
   spec:
     name: iris
     predictors:
     - graph:
         children: []
         implementation: SKLEARN_SERVER		# seldon core에서 sklearn용으로 pre-package된 model server
         modelUri: gs://seldon-models/v1.15.0-dev/sklearn/iris		# gs : google storage. 
         # sklearn에서 제공하는 example model
         name: classifier
       name: default
       replicas: 1		# 로드밸런싱을 위한 replica 개수
   ```

   > Pre-packaged 예시
   >
   > `modelUri` : model이 업로드 되어있는 url이 있어야 한다. 

   ```
   $ kubectl apply -f seldon_exam.yaml
   ```

   ```
   seldondeployment.machinelearning.seldon.io/sklearn created
   ```

   check

   ```
   $ kubectl get seldondeployment -n seldon_exam
   ```

   > delete
   >
   > ```
   > $ kubectl delete seldondeployment <model_name> -n <name_space>
   > ```
   >
   > `<model_name>` : metadata:.name  in .yaml

3. get ingress_url

   ```
   $ INGRESS_HOST=$(kubectl -n istio-system get service istio-ingressgateway -o jsonpath='{.status.loadBalancer.ingress[0].hostname}')
   $ echo ${INGRESS_HOST}		# INGRESS_HOST에 제대로 ingress_url가 할당되어있는지 확인
   ```

   > 예시 : `10.102.253.29` 출력

4. check in seldon external api

   > 기본 형식 : `http://<ingress_url>/seldon/<namespace>/<model-name>/api/v1.0/doc/`

   ```
   $ http://10.102.253.29/seldon/seldon_exam/iris-model/api/v1.0/doc/
   ```

   ```
   $ kubectl get svc istio-ingressgateway -n istio-system 		# 출력 확인해보기
   ```



##### send API request

```
$ INGRESS_HOST=$(kubectl -n istio-system get service istio-ingressgateway -o jsonpath='{.status.loadBalancer.ingress[0].hostname}')
$ curl -X POST http://${INGRESS_HOST}/seldon/seldon/sklearn/api/v1.0/predictions \
	- H 'Content-Type: application/json' \
	- d '{"img" : {"ndarray" : [[...]] }, \
    	  "annotations" : {dict()...}}'		# 예시 input data
```

