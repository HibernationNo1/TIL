

## dockerfile

**only for Ubuntu**

#### build

```
ARG PYTORCH="1.11.0"
ARG CUDA="11.3"
ARG CUDNN="8"  

FROM pytorch/pytorch:${PYTORCH}-cuda${CUDA}-cudnn${CUDNN}-devel	


ENV TORCH_CUDA_ARCH_LIST="7.5"
ENV TORCH_NVCC_FLAGS="-Xfatbin -compress-all"
ENV CMAKE_PREFIX_PATH="$(dirname $(which conda))/../"	


# To fix GPG key error when running apt-get update
RUN apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu2004/x86_64/3bf863cc.pub
RUN apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/machine-learning/repos/ubuntu2004/x86_64/7fa2af80.pub

# for install opencv
RUN apt-get update && apt-get install ffmpeg libsm6 libxext6  -y  


# COPY ./requirements.txt ./requirements.txt
COPY ./ ./
RUN pip install -r requirements.txt

# Install MMCV
RUN pip install --no-cache-dir --upgrade pip wheel setuptools
RUN pip install --no-cache-dir mmcv-full==1.5.3 -f https://download.openmmlab.com/mmcv/dist/cu113/torch1.11.0/index.html

# ENTRYPOINT python train.py --cfg configs/swin_maskrcnn.py --epo 50 --val_iter 50
```



- `TORCH_CUDA_ARCH_LIST`: 해당 device의 GPU compute capability를 설정 

  > [여기](https://developer.nvidia.com/cuda-gpus#compute) 에서 CUDA-Enabled GeForce and TITAN Products를 누르면 각 CPU에 대한 compute capability 확인 가능

- `TORCH_NVCC_FLAGS`: 추가 NVIDIA CUDA compiler driver flag를 의미한다.

  - `"-Xfatbin -compress-all"`

- `CMAKE_PREFIX_PATH` : dependencies에 대한 search path

  - `"$(dirname $(which conda))/../"` : conda 위치 명시

- ```
  RUN apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/cuda/repos/ubuntu1804/x86_64/3bf863cc.pub
  RUN apt-key adv --fetch-keys https://developer.download.nvidia.com/compute/machine-learning/repos/ubuntu1804/x86_64/7fa2af80.pub
  ```

  To fix GPG key error when running apt-get update

- `RUN apt-get update`

-   `apt-get install ffmpeg libsm6 libxext6  -y  `:  for install opencv in container



```
$ docker build . -t hibernation4958/katib:0.1
```

> if you want push, run
>
> ```
> $ docker push hibernation4958/katib:0.1
> ```



#### test

docker container안에서 code를 실행하여 training을 진행하기 위해 run하는 경우

```
$ docker run --shm-size 8G -v $(pwd):/test-vol -it hibernation4958/katib:0.1
```

- `--shm-size 8G`: container의 share memory를 할당

  ```
  root@5498dddbf5cc:/workspace# df -h| grep shm
  ```

  ```
  shm             8.0G     0  8.0G   0% /dev/shm
  ```

  > 충분한 shared memory를 할당하지 않으면 image load, model save과 같은 과정에서 멈추게 될 수도 있음

- `$(pwd):/test-vol`: volume mount

  





## Katib

### create resource 

```
$ vi katib.yaml
```

```
apiVersion: kubeflow.org/v1beta1
kind: Experiment
metadata:
  namespace: project-pipeline
  name: katib
spec:
  objective:
    type: maximize
    goal: 0.85
    objectiveMetricName: mAP
    metricStrategies:
    - name: mAP
      value: latest
  algorithm:
    algorithmName: random				
  parallelTrialCount: 2
  maxTrialCount: 12
  maxFailedTrialCount: 5
  parameters:
    - name: drop_rate
      parameterType: double
      feasibleSpace:
        min: "0.0"
        max: "0.3"
    - name: attn_drop_rate
      parameterType: double
      feasibleSpace:
        min: "0.0"
        max: "0.3"
    - name: drop_path_rate
      parameterType: double
      feasibleSpace:
        min: "0.1"
        max: "0.3"
  metricsCollectorSpec:
    collector:
      kind: StdOut
    source:
      filter:
        metricsFormat:
        - "([\\w|-]+)\\s*=\\s*((-?\\d+)(\\.\\d+)?)"  
  trialTemplate:
    primaryContainerName: training-container
    trialParameters:
      - name: drop_rate
        description: drop_rate of SwinTransformer
        reference: drop_rate
      - name: drop_path_rate
        description: drop_path_rate of SwinTransformer
        reference: drop_path_rate
      - name: attn_drop_rate
        description: attn_drop_rate of SwinTransformer.SwinBlockSequence.ShiftWindowMSA.WindowMSA
        reference: attn_drop_rate 
    trialSpec:
      apiVersion: batch/v1
      kind: Job
      spec:
        template:
          metadata:
            annotations:
              sidecar.istio.io/inject: "false"
          spec:
            containers:
              - name: training-container
                image: hibernation4958/katib_it:0.1
                command:
                  - "python3"
                  - "/workspace/train.py"
                  - "--cfg=configs/swin_maskrcnn.py"
                  - "--epo=50"
                  - "--katib"
                  - "--drop_rate=${trialParameters.drop_rate}"
                  - "--drop_path_rate=${trialParameters.drop_path_rate}"
                  - "--attn_drop_rate=${trialParameters.attn_drop_rate}"                  
            restartPolicy: Never
```

```
$ kubectl apply -f katib.yaml
```





#### confirm running

아래 명령어를 통해 conditions가 running으로 정상 작동하더라도 katib controller또는 pod내부에서 error가 발생한 경우가 있을 수 있다.

```
$ kubectl -n project-pipeline get experiment katib -o yaml
```



1. check katib-controller

   ```
   $ kubectl get pod -n kubeflow|grep katib-controller
   ```

   ```
   katib-controller-7dd48fc8f-bplkz                         1/1     Running   0               2d3h
   ```

   **log확인**

   yaml file의 특정한 값에 의해 error가 발생한 경우를 확인이 가능하다.

   ```
   $ kubectl logs -n kubeflow katib-controller-7dd48fc8f-bplkz
   ```

   

2. check pod

   katib 관련 pod확인

   ```
   $ kubectl -n project-pipeline get pods
   ```

   > namespace는 katib yamlfile에 명시한 namespace여야한다.

   ```
   NAME                                              READY   STATUS    RESTARTS   AGE
   katib-bvr7gkjw-5l9xg                              0/2     Error     0          3m11s
   katib-bvr7gkjw-b5hg9                              0/2     Error     0          2m40s
   katib-bvr7gkjw-bsl66                              0/2     Running     0          107s
   ```

   error가 발생한 특정 pod의 log를 확인해보자

   

   - **training-container**

     container를 load하거나 run하는 과정에서 발생한 error를 보여준다. 

     아무 출력 안뜨면 error없음

     ```
     kubectl logs -n project-pipeline katib-bvr7gkjw-5l9xg training-container
     ```

   - **metrics-logger-and-collector**

     ```
     kubectl logs -n project-pipeline katib-bvr7gkjw-5l9xg metrics-logger-and-collector
     ```

     image에 포함된 code의 진행 상황을 log로 보여준다.

     code에 의한 error를 확인할 수 있다.



#### check status

```
$ kubectl -n project-pipeline get experiment katib -o yaml
```



##### conditions

experiment의 `Created`, `Running`,  `Succeeded`여부를 확인할 수 있다.

- `lastTransitionTime` 
- `status`: `True`일 경우 정상적으로 run
- `type`:
  -  `Created`:
  - `Running`: 
  -  `Succeeded`: 정상적으로 experiment가 끝났을 경우만 생성



##### currentOptimalTrial

- `bestTrialName`: name of best trial

- `observation`: best trial의 `objectiveMetricName`, `additionalMetricNames` metrics value를 보여준다.

  > `observation: {}` 으로 출력되면 아직 metrics값을 얻지 못한 것

- `parameterAssignments`: `parameters` 의 조합 중 가장 좋은 조합을 제시한다.



##### others

- **`runningTrialList`** : 진행중인 trial의 list를 출력

- **`succeededTrialList`** : 성공한 trial list를 출력



### TODO

- algorithmName에서 random말고 딴것도 사용해보기

- job대신 pytorch job사용

- metricsCollectorSpec 에서 file로 받기 사용

  



#### delete

```
$ kubectl -n project-pipeline delete experiment katib
```

