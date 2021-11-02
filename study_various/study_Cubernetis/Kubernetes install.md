# Kubernetes install

## Install

쿠버네티스를 사용하기 위한 환경은 두 가지가 있다.

클라우드 서버를 통해 사용하는 Google Kubernetes Engine

또는 로컬을 통해 사용하는 kind



#### Google Kubernetes Engine

GKE cluster만들기

1. GCP용 command도구 (Cloud SDK)설치

   > GEK에서 cluster를 구축하려면 GUI로 구축하거나 Gcloud명령어를 사용해야 한다.

   1. Google Cloud SDK(gcloud 명령어를 포함) 설치

      ```
      $ (New-Object Net.WebClient).DownloadFile("https://dl.google.com/dl/cloudsdk/channels/rapid/GoogleCloudSDKInstaller.exe", "$env:Temp\GoogleCloudSDKInstaller.exe")
      ```

      ```
      $ & $env:Temp\GoogleCloudSDKInstaller.exe
      ```

      > ['자세한 사용 방법'](https://cloud.google.com/sdk/docs/quickstarts) 

   2. 설치할 gcloud 명령어를 사용할 수 있도록 셸을 재기동

      ```
      $ exec -l $SHELL
      ```

   3. gcloud  CLI인증

      ```
      $ gcloud init
      ```
      
   
2. gcloud명령어를 사용하여 구축

   > configurations에 project가 존재해야함

   1. GKE에서 사용 가능한 쿠버네티스 버전 확인

      ```
      $ gcloud container get-server-config --zone asia-northeast3-a
      ```

      > `gcloud config set` 으로 zone을 설정해 놓았으면 `--zone` 생략 가능
      
   2. GKE cluster 'k8s'생성

      ```
      $ gcloud container clusters create k8s --cluster-version 1.18.16-gke.2100 --zone asia-northeast3-a --num-nodes 3
      ```
      
      > `--cluster-version 1.21.5-gke.1300` : 쿠버네티스 버전 지정
      >
      > `--zone asia-northeast3-a` : 존 서울로 지정
      >
      > `--num-nodes 3` : 노드 수 지정
      >
      > Kubernetes Engine API is not enabled for this project라는 에러 메시지가 표시된 경우 : GCP 프로젝트의 Kubernetes Engine API를 활성화 해야 한다. 
      >
      > > 에러 메시지 마지막에 표시된 URL에서 실행할 수 있다.
      
      구축한 쿠버네티스 클러스터에 접속하기 위한 인증 정보는 ~/.kube/config에 자동으로 저장된다.
      
      > GKE클러스터 'k8s'에 접속할 인증 정보를 다시 가져오는 방법
      >
      > ```
      > $ cgloud container cluster get-credentials k8s --zone asia-northeast3-a
      > ```
      
      cluster가 생성되었다면 kubectl을 사용하여 GKE cluster를 관리할 수 있다.

3. GKE cluster를 삭제할 때

   GKE cluster 'k8s'삭제

   ```
   $ gcloud container clusters k8s --zone asia-northeast3-a
   ```




#### Kind

도커 컨테이너를 여러 개 기동하고 그 컨테이너를 쿠버네티스 노드로 사용하는 것으로, 여러 대로 구성된 쿠버네티스 클러스터를 구축한다.



1. WSL설치

2. Docker Desktop for windows설치

3. Docker Desktop for windows의 preference에서 kubernetes에

   Enable Kubernetes 선택 (활성화)

   > 왼쪽 하단에 docker running과 kubenetes running이 떠야 한다.



**직접 설치**

[여기](https://kind.sigs.k8s.io/docs/user/quick-start/) 에서 OS에 맞게 절차대로 다운로드 후 exe file 실행



**명령어로 설치**(windows)

```
$ curl.exe -Lo kind-windows-amd64.exe https://kind.sigs.k8s.io/dl/v0.10.0/kind-windows-amd64
```

이후 

```
$ Move-Item .\kind-windows-amd64.exe c:\some-dir-in-your-PATH\kind.exe
```

> C:바로 위의 some-dir-in-your-PATH로 옮긴다.

설치 됐는지 확인

```
$ kind version
```



**명령어로 설치**(linux)

```
$ curl -Lo ./kind https://kind.sigs.k8s.io/dl/v0.10.0/kind-linux-amd64
$ chmod +x ./kind
```





### kubctl

**직접 설치**(window)

```
$ curl -LO "https://dl.k8s.io/release/v1.22.0/bin/windows/amd64/kubectl.exe"
```

설치됐는지 버전 확인

```
$ kubectl version --client
```





**명령어 설치**

1. OS지정

   ```
   $ OS_TYPE="windows"
   ```

   > `$ OS_TYPE="linux"`

2. version지정

   ```
   $ VERSION="1.18.16"
   ```

   쿠버네티스 버전을 입력

3. kubectl 설치

   ```
   $ curl -O https://storage.googleapis.com/kubernetes-release/release/v${VERSION}/bin/${OS_TYPE}/amd64/kubectl
   $ chmod +x kubectl
   $ sudo mv kubectl /user/ITC/bin/kubectl
   ```

4. 환경설정

   1. shell 자동 완성 기능 (bash)

      ```
      $ source <(kubectl completion bash)
      ```

      > 다음 번 로그인할 떄 다른 shell을 기동했을 경우에도 자동 완성 기능을 활성화하려면 `~/.bashrc` 로 설정해야 한다.
      >
      > ```
      > $ echo 'source <(kubectl completion bash)' >> ~/.bachrc
      > ```

