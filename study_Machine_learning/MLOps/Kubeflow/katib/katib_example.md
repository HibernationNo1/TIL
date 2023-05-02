

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
RUN apt-get update

# for isntall opencv
RUN apt-get -y install libgl1-mesa-glx
RUN apt-get -y install libglib2.0-0
RUN pip install opencv-python-headless

COPY ./ ./
RUN pip install -r requirements.txt

# Install MMCV
RUN pip install --no-cache-dir --upgrade pip wheel setuptools
RUN pip install --no-cache-dir mmcv-full==1.5.3 -f https://download.openmmlab.com/mmcv/dist/cu113/torch1.11.0/index.html
# RUN pip install mmdet     # if run this line, get 'MMCV CUDA Compiler: not available'

RUN apt-get install -y git
RUN git clone https://github.com/HibernationNo1/hibernation_no1.git

ENTRYPOINT ["python", "main.py"]
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

- ```
  RUN apt-get install -y git
  RUN git clone https://github.com/HibernationNo1/hibernation_no1.git
  ```

  container안에서 사용할 custom packages를 git clone으로 불러오기

- `ENTRYPOINT ["python", "main.py"]` : container가 run되자마자 실행되는 command

  해당 command가 실행되면 막힘없이 code가 진행되어야 한다.



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
  namespace: pipeline
  name: katib-local             # katib-docker
spec:
  objective:
    type: maximize
    goal: 0.99
    objectiveMetricName: dv_mAP
    additionalMetricNames:
      - mAP
    metricStrategies:
    - name: mAP
      value: max
    - name: dv_mAP
      value: max
  algorithm:
    algorithmName: random
  parallelTrialCount: 1
  maxTrialCount: 20
  maxFailedTrialCount: 5
  parameters:
    - name: lr
      parameterType: categorical
      feasibleSpace:
        list:
          - "0.0001"
          - "0.0005"
          - "0.00005"
          - "0.00001"
          - "0.000005"
    - name: swin_drop_rate
      parameterType: categorical
      feasibleSpace:
        list:
          - "0.0"
          - "0.1"
          - "0.2"
          - "0.3"
          - "0.4"
    - name: swin_window_size
      parameterType: categorical
      feasibleSpace:
        list:
          - "7"
          - "9"
          - "11"
          - "13"
    - name: swin_mlp_ratio      
      parameterType: categorical
      feasibleSpace:
        list:
          - "3"
          - "4"
          - "5"
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
      - name: lr
        description: learning rate
        reference: lr
      - name: swin_drop_rate
        description: drop_rate of SwinTransformer
        reference: swin_drop_rate
      - name: swin_window_size
        description: window_size of SwinTransformer
        reference: swin_window_size
      - name: swin_mlp_ratio
        description: mlp_ratio of SwinTransformer
        reference: swin_mlp_ratio
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
                image:  localhost:5000/katib:0.1     # docker.io/hibernation4958/katib:0.1
                command:
                  - "python"
                  - "main.py"
                  - "--katib"
                  - "--cfg_train=config/train_cfg.py"
                  - "--model=MaskRCNN"
                  - "--epoch=25"
                  - "--lr=${trialParameters.lr}"
                  - "--swin_drop_rate=${trialParameters.swin_drop_rate}"
                  - "--swin_window_size=${trialParameters.swin_window_size}"
                  - "--swin_mlp_ratio=${trialParameters.swin_mlp_ratio}"
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

   katib 관련 pod확인 (`| grep katib`를 사용해 experiment 이름이 포함된 pod를 검색)

   ```
   $ kubectl -n project-pipeline get pods | grep katib
   ```

   > namespace는 katib yamlfile에 명시한 namespace여야한다.

   ```
   katib-local-95frxdkc-bzs9h                        2/2     Running   0          103s
   katib-local-random-76cdf89cb8-v7lfv               1/1     Running   0          115s
   ```
   
   `katib-local-random-76cdf89cb8-v7lfv` : 먼저 만들어진 pod는 experiment에 의해 정의된 pod이다.

   `katib-local-95frxdkc-bzs9h` : experiment에 의해 정의된 pod이후 만들어진 pod는 `Trial`을 진행하는 pod로, 실제 code에 대한 log를 확인하고자 할 때 해당 pod의 log를 확인하면 된다.

   - error

     ```
     NAME                                              READY   STATUS    RESTARTS   AGE
     katib-bvr7gkjw-5l9xg                              0/2     Error     0          3m11s
     katib-bvr7gkjw-b5hg9                              0/2     Error     0          2m40s
     katib-bvr7gkjw-bsl66                              0/2     Running     0          107s
     ```
   
     위 처럼 error 발생시 
   
     - image가 잘못된 경우
     
     - dockerfile의 `ENTRYPOINT`의 명령어 입력 시 code가 정상적으로 학습 진행이 안되는 경우
     
       > ex) dockerfile의 `ENTRYPOINT`가 아래와 같은 경우
       >
       > ```
       > ENTRYPOINT ["python", "main.py", "--katib"]
       > ```
       >
       > 해당 명령어를 `main.py`가 있는 위치에서 직접 입력해보자.
       >
       > ```
       > $ python main.py --katib
       > ```
       >
       > 위 명령어에 의해 code가 정상 실행이 되어야 한다.
   
   
   
   
   
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



- delete

  ```
  kubectl delete experiment -n pipeline <experiment-name>
  ```

  

★★★★★

experiment의 hyperparameter조합 결과는 해당 experiment의 Type이 `Succeeded`인 경우에만 알 수 있다.

```
$ kubectl get experiment -n pipeline <experiment-name>
```

```
NAME              TYPE        STATUS   AGE
experiment-name   Succeeded   True     23m
```

`Succeeded`가 뜨려면 해당 두 가지 조건이 만족해야 한다.

1.  experiment의 실행 code의 학습이 전부 끝나거나 `exit()`로 인해 실행히 멈춘 상태
2. `spec.objective.goal`의 조건을 만족한 경우 



#### check status

```
$ kubectl -n project-pipeline get experiment katib -o yaml
```



Experiment details의 Best trial performance값은 Latest value가 출력되는데

```
$ kubectl describe experiment -n pipeline katib-local
```

위 명령을 통해 아래 결과를 확인할 수 있다.

```
Observation:
      Metrics:
        Latest:  0.6567
        Max:     0.8567
        Min:     0.0
        Name:    mAP
        Latest:  0.2408
        Max:     0.4542
        Min:     0.0
        Name:    dv_mAP
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

