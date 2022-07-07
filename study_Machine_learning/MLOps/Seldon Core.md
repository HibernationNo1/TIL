# Seldon Core

kubernetes에서 model serving을 쉽게 할 수 있도록 도와주는 Framework중 하나



**install** 

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

   

3. Helm을 사용한 ambassador install [공식 ](https://www.getambassador.io/docs/edge-stack/latest/topics/install/) **Ambassador v1 (v2 not currently supported)**

   1. ambassadir를 install하기 위해 pubilc하게 저장된 helm repository를 등록

      Add this Helm repository to your Helm client

      ```
      $ helm repo add datawire https://www.getambassador.io
      ```

      ```
      "datawire" has been added to your repositories
      ```

      

      check

      ```
      $ helm repo list
      ```

      ```
      NAME    	URL                         
      datawire	https://www.getambassador.io
      ```

      > `$ helm version`

      

      helm repo updata

      ```
      $ helm repo update
      ```

      ```
      Hang tight while we grab the latest from your chart repositories...
      ...Successfully got an update from the "datawire" chart repository
      Update Complete. ⎈Happy Helming!⎈
      ```

      

      

      ```
      $ kubectl create namespace seldon-system
      ```

      

      

      

      1. 

   2. check

      ```
      
      ```

      > 관련 pot가 running이 될 때까지 시간이 좀 걸림 

   