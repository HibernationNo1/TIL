https://kserve.github.io/website/0.9/admin/serverless/#recommended-version-matrix





Istio version check 

특정 pod를 들여다보면 알 수 있다.

```
kubectl -n istio-system  get pod istio-ingressgateway-6668f9548d-gn8sd -o yaml
```

`istio/proxyv2:1.14.1`



kubectl version check

```
kubectl version
```

`v1.22.13`



kanaitve version check

```
kubectl -n knative-serving  get pod activator-7c5cd78566-jkv7c -o yaml
```

`serving.knative.dev/release: v1.2.5`









---

1. kubeflow설치
2. istio는 kubeflow꺼 그대로 사용, knative는 아래 순서대로 install



#### knative

1. knative는 [공식 문서](https://knative.dev/docs/install/yaml-install/serving/install-serving-with-yaml/)에 따라 설치(YAML file사용)

   **Install the Knative Serving component**

   1. Install the required custom resources

      ```
      $ kubectl apply -f https://github.com/knative/serving/releases/download/knative-v1.7.1/serving-crds.yaml
      ```

   2. Install the core components of Knative Serving

      ```
      $ kubectl apply -f https://github.com/knative/serving/releases/download/knative-v1.7.1/serving-core.yaml
      ```

   3. Verify

      pod

      ```
      $ kubectl get pods -n knative-serving
      ```

      

      version 확인

      ```
      $ kubectl describe cm config-domain -n knative-serving
      ```

   

   

   **Install a networking layer** 설치 (istio)

   istio를 설치하고 Knative integration를 활성화

   1. Install Knative Istio

      ```
      $ kubectl apply -l knative.dev/crd-install=true -f https://github.com/knative/net-istio/releases/download/knative-v1.7.0/istio.yaml
      $ kubectl apply -f https://github.com/knative/net-istio/releases/download/knative-v1.7.0/istio.yaml
      ```

   2. Install the Knative Istio controller

      ```
      $ kubectl apply -f https://github.com/knative/net-istio/releases/download/knative-v1.7.0/net-istio.yaml
      ```

   3. External IP address 확인

      ```
      $ kubectl --namespace istio-system get service istio-ingressgateway
      ```

      ```
      NAME                   TYPE           CLUSTER-IP       EXTERNAL-IP     PORT(S)                                      AGE
      istio-ingressgateway   LoadBalancer   10.102.229.237   192.168.0.240   15021:31907/TCP,80:31577/TCP,443:30362/TCP   5h57m
      ```

   

   

   knative는 여기까지, **KServe**로 넘어간다

   > 
   >
   > ```
   > $ kubectl get gateway -n knative-serving
   > ```
   >
   > ```
   > NAME                      AGE
   > knative-ingress-gateway   6m52s
   > knative-local-gateway     5h17m
   > ```
   >
   > 그대로 설치하면 Isito gateway 와 연동되지 않는다. 그렇기 때문에 아래와 같이 `knative-ingress-gateway`, `knative-local-gateway` 의 selector 를 수정해 줘야 한다.
   >
   > - `knative-ingress-gateway`
   >
   >   ```
   >   $ kubectl edit gateway -n knative-serving knative-ingress-gateway
   >   ```
   >
   >   ```
   >   spec:
   >     selector:
   >       istio: ingressgateway
   >       istio: ingress          # 추가
   >   ```
   >
   > - `knative-local-gateway`
   >
   >   ```
   >   $ kubectl edit gateway -n knative-serving knative-local-gateway
   >   ```
   >
   >   ```
   >   spec:
   >     selector:
   >       istio: ingressgateway
   >       istio: ingress          # 추가
   >   ```
   >
   >   
   >
   >   ingress gateway는 `istio-system` 에만 존재
   >
   >   ```
   >   $ kubectl get svc istio-ingressgateway -n istio-system
   >   ```
   >
   >   ```
   >   NAME                   TYPE           CLUSTER-IP       EXTERNAL-IP     PORT(S)                                      AGE
   >   istio-ingressgateway   LoadBalancer   10.102.229.237   192.168.0.240   15021:31907/TCP,80:31577/TCP,443:30362/TCP   5h57m
   >   ```
   >
   >   
   >
   > 
   >
   > **Configure DNS**  (Magic DNS (sslip.io)는 minikube에선 안됨. Real DNS를 사용)
   >
   > - `EXTERNAL-IP` 가 실제 IP인 경우
   >
   >   domain에 대한 wildcard A record를 구성
   >
   >   ```
   >   *.kserve-test.example.com == A 192.168.0.240
   >   ```
   >
   >   - `kserve-test` : 배포하고자 하는 model에 대한 `InferenceService`를 띄울 namesapce
   >   - `192.168.0.240` : `istio-ingressgateway`의 `EXTERNAL-IP`
   >
   > - `EXTERNAL-IP` 가 CNAME인 경우

   

---

이 위에꺼 하면 안됨. knative와 istio-system은 kubeflow를 설치 한 상태로 진행



#### **KServe**

**Install KServe**

```
$ kubectl apply -f https://github.com/kserve/kserve/releases/download/v0.9.0/kserve.yaml
```

check

```
$ kubectl get pod -n kserve
```

```
NAME                                         READY   STATUS    RESTARTS   AGE
kserve-controller-manager-5fc887875d-xl7sj   2/2     Running   0          7h3m
```



**Install KServe Built-in ClusterServingRuntimes**

```
kubectl apply -f https://github.com/kserve/kserve/releases/download/v0.9.0/kserve-runtimes.yaml
```

> InferenceService를 생성하는 데 필요

check

```
$ kubectl get clusterservingruntimes
```

```
NAME                        DISABLED   MODELTYPE    CONTAINERS         AGE
kserve-lgbserver                       lightgbm     kserve-container   7h13m
kserve-mlserver                        sklearn      kserve-container   7h13m
kserve-paddleserver                    paddle       kserve-container   7h13m
kserve-pmmlserver                      pmml         kserve-container   7h13m
kserve-sklearnserver                   sklearn      kserve-container   7h13m
kserve-tensorflow-serving              tensorflow   kserve-container   7h13m
kserve-torchserve                      pytorch      kserve-container   7h13m
kserve-tritonserver                    tensorrt     kserve-container   7h13m
kserve-xgbserver                       xgboost      kserve-container   7h13m
```









model배포

1. namespace생성

   ```
   $ kubectl create namespace kserve-test
   ```

   

2. model배포

   ```
   $ kubectl get pod -n kserve
   ```

   ```
   NAME                                         READY   STATUS    RESTARTS   AGE
   kserve-controller-manager-5fc887875d-4f5kb   2/2     Running   0          5m18s
   ```

   `STATUS : Running` 확인 후 진행

   

   배포하고자 하는 model에 대한 InferenceService 작성 후 apply

   ```
   $ kubectl apply -n kserve-test -f - <<EOF
   apiVersion: "serving.kserve.io/v1beta1"
   kind: "InferenceService"
   metadata:
     annotations:
       isdecar.istio.is/inject
     name: "sklearn-iris"
   spec:
     predictor:
       model:
         modelFormat:
           name: sklearn
         storageUri: "gs://kfserving-examples/models/sklearn/1.0/model"
   EOF
   ```

   - `metadata.name` : Knative service name

   

   confirm pod

   ```
   $ kubectl get pods -n kserve-test -w
   ```

   `STATUS : Running` 확인 후 진행

   

   check

   ```
   $ kubectl get inferenceservices sklearn-iris -n kserve-test
   ```

   ```
   NAME           URL                                           READY   PREV   LATEST   PREVROLLEDOUTREVISION   LATESTREADYREVISION                    AGE
   sklearn-iris   http://sklearn-iris.kserve-test.example.com   True           100                              sklearn-iris-predictor-default-00001   5h11m
   ```

   `URL` : 기본 도메인 값은 `http://{Knative service name}.{namespace}.example.com` 이다.

   

3. 수신 IP 및 port 확인

   ```
   $ kubectl get svc istio-ingressgateway -n istio-system
   ```

   ```
   NAME                   TYPE           CLUSTER-IP       EXTERNAL-IP     PORT(S)                                      AGE
   istio-ingressgateway   LoadBalancer   10.102.229.237   192.168.0.240   15021:31907/TCP,80:31577/TCP,443:30362/TCP   7h28m
   ```

   

   

4. port forward

   ```
   kubectl port-forward svc/istio-ingressgateway -n istio-system 8080:80
   ```

   

5. set ingress

   ```
   $ export INGRESS_HOST=127.0.0.1
   $ export INGRESS_PORT=8080
   ```

   > ```
   > $ echo $INGRESS_HOST
   > $ echo $INGRESS_PORT
   > ```

   

   > 
   >
   > ```
   > export INGRESS_HOST=$(kubectl -n istio-system get service istio-ingressgateway -o jsonpath='{.status.loadBalancer.ingress[0].ip}')
   > export INGRESS_PORT=$(kubectl -n istio-system get service istio-ingressgateway -o jsonpath='{.spec.ports[?(@.name=="http2")].port}')
   > 
   > ```
   >
   > `INGRESS_HOST` == 192.168.0.240
   >
   > `INGRESS_PORT` == 80

   

   ```
   cat <<EOF > "./iris-input.json"
   {
     "instances": [
       [6.8,  2.8,  4.8,  1.4],
       [6.0,  3.4,  4.5,  1.6]
     ]
   }
   EOF
   ```

   

   ```
   $ SERVICE_HOSTNAME=$(kubectl get inferenceservice sklearn-iris -n kserve-test -o jsonpath='{.status.url}' | cut -d "/" -f 3)
   ```

   > ```
   > $ echo $SERVICE_HOSTNAME
   > http://sklearn-iris.kserve-test.example.com		# 출력
   > ```

   

   

   ```
   $ CLUSTER_IP=$(kubectl -n istio-system get service istio-ingressgateway -o jsonpath='{.spec.clusterIP}')
   ```

   
   
   
   
   
   
   ```
   curl -v -H "Host: ${SERVICE_HOSTNAME}" http://${INGRESS_HOST}:${INGRESS_PORT}/v1/models/sklearn-iris:predict -d @./iris-input.json
   ```
   
   

```
curl -v -H "Host: ${SERVICE_HOSTNAME}" http://192.168.219.100:${INGRESS_PORT}/v1/models/sklearn-iris:predict -d @./iris-input.json
```





>https://arxiv.org/pdf/2206.13655.pdf
>
>kubeflow 논문
>
>
>
>kserve
>
>https://www.youtube.com/watch?v=FX6naJLaq2Y
>
>
>
>**302 Found**
>
>/dex/auth로 인하여 인증용 Redirect 발생
>
>**solution**: `EnvoyFilter`를 만들어 dex 인증에서 제외해야 한다.
>
>1. 적용된 Auth filter확인
>
>   ```
>   $ kubectl get envoyfilters.networking.istio.io authn-filter -n istio-system
>   ```
>
>   ```
>   NAME           AGE
>   authn-filter   55m
>   ```
>
>   
>
>2. Dex인증을 제외할 URL을 `EnvoyFilter`에 적용
>
>   ```
>   $ kubectl apply -n istio-system -f - <<EOF
>   apiVersion: networking.istio.io/v1alpha3
>   kind: EnvoyFilter
>   metadata:
>     name: bypass-auth-iris-sample
>     namespace: istio-system
>   spec:
>     workloadSelector:
>       labels:
>         istio: ingressgateway
>     configPatches:
>     - applyTo: VIRTUAL_HOST
>       match:
>         routeConfiguration:
>           vhost:
>             name: 192.168.0.240:80
>       patch:
>         operation: MERGE
>         value:
>           per_filter_config:
>             envoy.ext_authz:
>               disabled: true
>   EOF
>   ```
>
>   
>
>   confirm
>
>   ```
>   $ kubectl get envoyfilters -n istio-system bypass-auth-iris-sample
>   ```
>
>   >edit
>   >
>   >```
>   >$ kubectl edit envoyfilters -n istio-system bypass-auth-iris-sample
>   >```
>
>   

