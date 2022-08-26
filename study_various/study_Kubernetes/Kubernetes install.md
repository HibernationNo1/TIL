# Kubernetes install

## Install

##### 



### nvidia device plugin

[github](https://github.com/NVIDIA/k8s-device-plugin)

install version확인할 것(지금은 11.0설치)

1. download .yaml file

   ```
   $ kubectl create -f https://raw.githubusercontent.com/NVIDIA/k8s-device-plugin/v0.12.2/nvidia-device-plugin.yml
   ```

   check

   ```
   $ kubectl get pod -A | grep nvidia
   ```

   

   

   edit

   ```
   $ kubectl edit pod nvidia-device-plugin-daemonset-jlml2 -n kube-system
   ```

2. check GPU

   ```
   $ kubectl get nodes "-o=custom-columns=NAME:.metadata.name,GPU:.status.allocatable.nvidia\.com/gpu"
   ```

   ```
   NAME       GPU
   minikube   <none>
   ```

   위 처럼 뜨면 gpu가 사용 가능하도록 설정되지 않은 경우 (`1` 이 떠야함)

   

   

