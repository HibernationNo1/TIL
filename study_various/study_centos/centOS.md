{:toc}



# centOS



**check Hardware information**

- check cpu

  ```
  $ lscpu
  ```

  

- check hardware

  ```
  $ lshw
  ```

  

- check RAM

  ```
  $ free -m
  ```

  

- GPU info

  ```
  $ sudo lshw -C display
  ```

  or

  ```
  $ lspci | grep VGA
  ```

  



## install



#### curl, vim

```
$ sudo yum install -y curl vim
```



#### git

```
$ sudo yum install git
$ git --version
```





#### anaconda

[여기](https://repo.anaconda.com/archive/) 에서 아래 버전 선택해서 다운

[Anaconda3-2021.05-Linux-x86_64.sh](https://repo.anaconda.com/archive/Anaconda3-2021.05-Linux-x86_64.sh)

- download 

  ```
  $ wget https://repo.anaconda.com/archive/Anaconda3-2021.05-Linux-x86_64.sh
  ```

  > 년도에 따라 version 알맞게 사용. 	21.05가 현재까진 범용적

- start install process

  ```
  $ sudo bash Anaconda3-2021.05-Linux-x86_64.sh
  ```

  ```
  Please, press ENTER to continue
  >>> 
  뜨면 Enter하고 다 읽어내린 후 
  ```

  ```
  Do you accept the license terms? [yes|no]
  Please answer 'yes' or 'no':'
  >>> 
  뜨면 yes 입력 후 Enter
  ```

  ```
  Anaconda3 will now be installed into this location:
  /home/hibernation/anaconda3
  
    - Press ENTER to confirm the location
    - Press CTRL-C to abort the installation
    - Or specify a different location below
  
  [/home/{user_name}/anaconda3] >>> 		/home/ainsoft/anaconda3
  뜨면 새롭게 만들 directory의 name을 입력 (걍 anaconda3으로 )
  # 이 때 입력 후 바로 뜨는 문구 `PREFIX=/home/ainsoft/anaconda3` 를 아래 기억★★★
  # 만약 [/root/anaconda3] >>>  으로 뜨면 root에 설치된다는 뜻이지
  # [/root/anaconda3] >>> 		/home/ainsoft/anaconda3
  # 으로 입력
  ```

  ```
  Do you wish the installer to initialize Anaconda3
  by running conda init? [yes|no]
  
  no를 입력하면 콘다는 쉘 스크립트를 수정하지 못한다. yes를 누른다
  ```

- path추가

  ```
  $ sudo vi ~/.bashrc
  ```

  text 편집기가 열리면 맨 아래줄에 추가

  ```
  export PATH=/home/ainsoft/ananconda3/bin:$PATH
  ```

  > 위 설치 도중 만났던 PREFIX값에 + '/bin:$PATH'    

  ```
  $ export PATH=~/anaconda3/bin:$PATH
  ```

  

- 설치 확인

  bashrc 실행

  ```
  $ sudo source ~/.bashrc
  ```

  > (base)뜨는지 확인
  >
  > 안뜨면 `conda init`을 해야 함 (그 전에 `conda -V`을 통해 `conda : command not found` 가 뜨는지 확인)
  >
  > ```
  > $ conda init bash
  > ```
  >
  > bash사용
  >
  > > (base) 없애려면 ` $ conda deactivate`

  check version

  ```
  $ conda -V 
  ```

  > 만일 `conda : command not found` 가 뜨면



#### docker

[공식 문서](https://docs.docker.com/engine/install/centos/)

1. Set up the repository

   ```
   $ sudo yum install -y yum-utils
   ```

   ```
   $ sudo yum-config-manager \
       --add-repo \
       https://download.docker.com/linux/centos/docker-ce.repo
   ```

   

2. Install Docker Engine

   ```
   $ sudo yum install docker-ce docker-ce-cli containerd.io docker-compose-plugin
   ```

   

3. check

   start docker

   ```
   $ sudo systemctl start docker
   ```

   docker run

   ```
   $ sudo docker run hello-world
   ```



#### kubernetes

[공식](https://kubernetes.io/docs/setup/production-environment/tools/kubeadm/install-kubeadm/)에는 설명이 이상하게 되어있음. [여기](https://www.hostafrica.co.za/blog/new-technologies/install-kubernetes-delpoy-cluster-centos-7/) 들어가보기

1. **check required ports**

   ```
   $ telnet 127.0.0.1 6443
   ```

   > ```
   > $ yum install telnet
   > ```

   - `Connected to xxx.xxx.xxx.xxx...` : 통신 성공 (사용중)

   - `Trying 1xx.1xx.2xx.1xx...` : 방화벽 open이 안되어있음

   - `telnet: Unable to connect to remote host: Connection refused ` : 방화벽은 열려있으나 해당 port에 어떠한 프로세스도 없다

     (사용 가능)

2. **[install docker](#docker)**

   ```
   $ sudo systemctl status docker
   ```

   ![](https://www.hostafrica.co.za/blog/wp-content/uploads/2020/05/How-to-Install-Docker-on-Linux-and-Windows_html_m4671b902.png)

3. **Set up the Kubernetes Repository**

   kubenetes package는 공식 CentOS 7 repository가 없기 때문에 새 repo file을 추가해야 한다. 

   ```
   $ sudo vi /etc/yum.repos.d/kubernetes.repo
   ```

   ```
   [kubernetes]
   name=Kubernetes
   baseurl=https://packages.cloud.google.com/yum/repos/kubernetes-el7-x86_64
   enabled=1
   gpgcheck=0
   repo_gpgcheck=0
   gpgkey=https://packages.cloud.google.com/yum/doc/yum-key.gpg https://packages.cloud.google.com/yum/doc/rpm-package-key.gpg
   ```

4. **install kubelet**

   ```
   $ sudo yum install -y kubelet
   ```

   ```
   ...
   
   Complete!
   ```

5. **install kubeadm**

   ```
   $ sudo yum install -y kubeadm
   ```

   ```
   ...
   
   Complete!
   ```

6. Set hostnames

   master node위에서 hostname을 set

   ```
   $ sudo hostnamectl set-hostname {master-node-name}
   ```

   - master node가 아니더라도 node이름은 위 명령어로 set가능
   - 



```
[kubernetes]
name=Kubernetes
baseurl=https://packages.cloud.google.com/yum/repos/kubernetes-el7-\$basearch
enabled=1
gpgcheck=1
repo_gpgcheck=1
gpgkey=https://packages.cloud.google.com/yum/doc/yum-key.gpg https://packages.cloud.google.com/yum/doc/rpm-package-key.gpg
exclude=kubelet kubeadm kubectl
EOF
```



kubeadm version

kubectl version --client

kubectl version