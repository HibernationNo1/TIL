# Katib

## Introduction

### abstract

[공식](https://www.kubeflow.org/docs/components/katib/hyperparameter/), [깃헙](https://github.com/kubeflow/katib), [논문](https://arxiv.org/pdf/2006.02085.pdf)

이미 구현이 되어있는 HPO search package들을 사용할 때 kubernetes의 자원을 효율적으로 활용하여 HPO를 하고 service화 할 수 있도록 하는 인프라를 구축하는것을 담당한다.



**장점:** 

- Cluster Management

  kubernetes에서 알아서 오케스트레이션을 진행하여 자동화가 가능하도록 한다.

- Agnostic to ML Framework

  tensorflow, pytorch 등 어떠한 framework로 개발이 되었든 상관 없이 해당 code를 container화만 할 수 있다면 하이퍼 파라미터 최적화(HPO)를 code의 수정 없이 외부에서 가능하다 .

- 하이퍼 파라미터 최적화(HPO) tools을 k8s상에서 할 수 있도록 support한다 



### detail

Katib는 실험(Experiment), 제안(Suggestion), 시도(Trial) 및 작업(Job)의 개념이 있다.



#### Experiment

목표로 하는 값(accuracy같은)을 찾기 위해서 hyper parameters 조합의 최적값을 찾는 탐색 작업

`kind: Experiment` 의 resource를 정의한다.

- `Objective` hyper parameter tuning 작업 통해서, 이루고자 하는 목표를 정의한다.

  yaml에서 [objective](#objective)

- `Search Space`: hyper parameter tuning 작업시 사용해야 할 모든 hyper parameter 값과 hyper parameter의 제약 조건을 정의한다.

  > - Learning rate는 `min: 0.1`, `max: 0.5`
  > - optimizer는 `[sgd, adam]`

  yaml에서 [parameters](#objective)

- `Search Algorithm`: hyper parameter tuning 작업시 사용할 알고리즘을 정의

  yaml에서 [algorithm](#algorithm)

  



#### Suggestion

Katib는 각 `Experiment` resource마다 하나의 `Suggestion` resource를 생성하는데, 이`Suggestion`으로 인해 search algorithm이 hyper parameter조합을 제안하게 된다.

Katib 는 제안된 hyper parameter조합을 세트별로 평가하기 위한 `Trial`을 작성한다.



#### Trial

`Trial`은 제안된 hyper parameter조합을 평가하기 위한 하나의 작업을 의미하는 resource이다.

제안된 hyper parameter조합을 `Woker Job` instance에 할당해서 실행한다.

각 `Experiment` 는 여러 번의 `Trial`을 수행한다. `Experiment` 는 목표나 설정한 최대 시도 횟수에 도달 할 때까지 `Trial` 을 계속된다.



#### Worker Job

[공식](https://www.kubeflow.org/docs/components/katib/overview/#worker-job)

**Worker job** : kubeflow에서 training을 수행할 때 사용하는 kubernetes custom resource이다.

katib의 experiment에서 job의 의미는 `Trial`을 평가하고 목표 값을 계산하는 프로세스를 의미하며, 제안된 hyper parameter조합을 넘겨 받아서 실제로 모델을 학습한다.

이러한 job은 여러 type이 있다.

type of `Worker Job`

- [Kubernetes `Job`](https://kubernetes.io/docs/concepts/workloads/controllers/job/)
- [Kubeflow `TFJob`](https://www.kubeflow.org/docs/components/training/tftraining/)
- [Kubeflow `PyTorchJob`](https://www.kubeflow.org/docs/components/training/pytorch/)









**central dashboard: Experiments(AutoML)** : central dashboard에서 Experiments(AutoML)은 Katib를 사용하여 HPO를 1회 하는 개념이며,  이는 Objective, Saerch space, Search algo 가 교체되는 과정이 이루어진다.

- Objective : optimizer할 metric function

- Saerch space : 각 hyper parameter별로 range space를 지정하고, 그 범위 안에서의 결과를 알 수 있도록 하는 것

  >  ex) 
  >
  > `optimizer` choices in [SGD, ADAM, ...],
  >
  > `tmp_value` choices in [0.5, 1, 0.5, ...], ...

- Search algo : Katib에서 제공하는, 이미 구현이 되어있는 search algorithm중에서 선택



**Suggestion** : search algorithm으로부터 추천 된 Hyper Parameters(HP)조합 1개 세트를 의미한다.

**Trial** : 후보 HP조합에 따른 학습 및 평가 1개 세트

**Worker Jop** : container화 된 training 또는 inferece code를 1회 돌리는 것



## install

1. install katib component

   kubeflow설치 시 포함됨

   katib component확인 (만약 설치 안되어있으면 [공식](https://www.kubeflow.org/docs/components/katib/hyperparameter/)에서 설치)

   ```
   $ kubectl get deploy -n kubeflow |grep katib
   ```

   ```
   katib-controller                     
   katib-db-manager                      
   katib-mysql                           
   katib-ui  
   ```

   - `katib-controller` : katib와 관련된 CR(Experiments(AutoML), Suggestion, Trial 등)을 관리하고 이전 작업과 지금 작업에 대해 status가 다르면 맞춰주는 component
   - `katib-mysql  ` : katib관련 resource를 관리하는 DB
   - `katib-db-manager ` : `katib-mysql` 에 접근할 수 있도록 하는 component
   - `katib-ui ` : `katib-db-manager`를 거쳐서 `katib-mysql`에 저장된 정보를 바탕으로 frontend를 랜더링

   > install 명령어
   >
   > `katib-cert-generator` 는독립 실행형 설치를 위한 인증서 생성기. 필수가 아니며 성치 안해도 무방

   

## create Experiment

그 외 [예시](https://velog.io/@moey920/Katib-random-example)

### yaml

```
---
apiVersion: kubeflow.org/v1beta1
kind: Experiment
metadata:
  namespace: project-pipeline
  name: random
spec:
  objective:
    type: maximize
    goal: 0.99
    objectiveMetricName: Validation-accuracy
    additionalMetricNames:
      - Train-accuracy
  algorithm:
    algorithmName: random
  parallelTrialCount: 3
  maxTrialCount: 12
  maxFailedTrialCount: 3
  parameters:
    - name: lr
      parameterType: double
      feasibleSpace:
        min: "0.01"
        max: "0.03"
    - name: num-layers
      parameterType: int
      feasibleSpace:
        min: "2"
        max: "5"
    - name: optimizer
      parameterType: categorical
      feasibleSpace:
        list:
          - sgd
          - adam
          - ftrl
  trialTemplate:
    primaryContainerName: training-container
    trialParameters:
      - name: learningRate
        description: Learning rate for the training model
        reference: lr
      - name: numberLayers
        description: Number of training model layers
        reference: num-layers
      - name: optimizer
        description: Training model optimizer (sdg, adam or ftrl)
        reference: optimizer
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
                image: docker.io/kubeflowkatib/mxnet-mnist:latest
                command:
                  - "python3"
                  - "/opt/mxnet-mnist/mnist.py"
                  - "--batch-size=64"
                  - "--lr=${trialParameters.learningRate}"
                  - "--num-layers=${trialParameters.numberLayers}"
                  - "--optimizer=${trialParameters.optimizer}"
            restartPolicy: Never
```

- change namespace to Kubeflow user profile

  ```
  metadata:
    namespace: project-pipeline
  ```

  > `project-pipeline` 라는 namespace에 Experiment 생성하도록 설정



#### objective

Hyper parameter Tuning작업을 통해 이루고자 하는 목표 정의

`objectiveMetricName`와 `additionalMetricNames` 를 사용하여 Hyper parameter 가 model과 어떻게 작동하는지 monitering한다.

```
objective:
    type: maximize
    goal: 0.99
    objectiveMetricName: Validation-accuracy
    additionalMetricNames:
      - Train-accuracy
    metricStrategies:
      - name: accuracy
        value: latest
```

- `type: maximize` 최대값을 얻는 것이 목표임을 의미

  목표 유형이 `maximize` 인 경우 Katib은 모든 최대 메트릭 값을 비교한다.

  > 유형에 따라 `minimize` 를 사용할 수 있음
  >
  > 목표가 없으면 `MaxTrialCount = TrialsSucceeded` 인 상태까지 experiment 진행됨 

- `goal: 0.99` 목표로 하는 최대값

- `objectiveMetricName`  최적화할 기본 experiment의 metric을 명시

  Hyper parameter Tuning과정에서 Validation-accuracy가 목표(`goal`)값에 도달하면  Hyper parameter 조합 시도를 중지한다.

  **type**

  - `Validation-accuracy`
  - `train-accuracy`
  - `accuracy`

- `additionalMetricNames:` `objectiveMetricName` 에서 명시한 metric외에 수집할 metrics를 명시

  여기서 명시된 metric의 값은 `goal`에 충족한다 해도 Hyper parameter 조합 시도는 계속된다.

  > `objectiveMetricName` 에 명시한 metric의 정보만을 얻을 경우엔 생략 

- `MetricStrategies` : 특정 metrics의 값을 추출하기 위해 min, max or latest과 같은 규칙을 정의

  비어있으면  experiment defaulter (webhook)가 알아서 값 채움

  ```
  metricStrategies:
    - name: accuracy
      value: latest		# min, max or latest
  ```

  `accuracy` 라는 metrics 의 마지막 값을 추출

  



#### algorithm

[공식](https://www.kubeflow.org/docs/components/katib/experiment/#sobols-quasirandom-sequence)

`algorithm` 에서 적용할 **Hyper parameter Tuning** 최적화 algorithm을 결정할 수 있다.

```
  algorithm:
    algorithmName: {algorithm}
```

**type**

- `grid` 

  모든 가능성에 대해 철저한 조합 검색을 수행한다.

  모든 변수가 불연속적이고(min, max값처럼 범위가 아닌 경우), 조합 할 수 있는 parameter의 종류가 적을 때 사용하기 적합하다.

- `random`

  `grid`를 대체하기 위해 사용되며, 각 parameter를 random하게 돌린 후 evaluate를 진행한다. 

  연속적인 변수가 많고, 조합할 수 있는 parameter의 종류가 많을 때 사용하기 적합하다.

- `bayesianoptimization` 

  Gaussian process regression를 사용하여 탐색 공간을 모델링한다.

  탐색 공간의 모든 지점에서 손실 함수의 추정치와 해당 추정치의 불확실성을 계산하는데, 이는 현재 유망한 hyper parameter 구성을 반복적으로 평가해서, 최적값에 대한 정보를 나타내는 관측치를 수집하는 등의 확률적 추정 결과를 바탕으로 최적의 값을 찾는다.

  예상 loss와 불확실성(uncertainty)을 모두 modeling하기 때문에 search algorithm이 몇 단계로 수렴되므로 시간이 오래 걸린다. 

  parameter의 종류가 적고 각 parameter의 범위가 적을 때 적합하다.

  > 추가적인 이해 필요

- `hyperband`

  `bayesianoptimization`를 대체하기 위해 사용되며, resource할당을 최적화 하여 평가할 수 있는 구성의 수를 최대화 한다. 빠르게 목적에 도달해서 조기 중지(early stopping)를 달성하기 위해 사용한다.

  parameter의 종류가 적을때 적합하다.

- `tpe` (Tree of Parzen Estimators)

  정방향 및 역방향 gradient기반 검색을 제공한다.

- `multivariate-tpe`

  `tpe` 의 상위호환

  탐색 공간에서 hyper parameter간의 종속성(dependencies)을 찾는다.

- `cmaes`(Covariance Matrix Adaptation Evolution Strategy)

  derivative-free methods for numerical optimization of non-linear or non-convex continuous optimization problems. 

  > 추가적인 이해 필요

- `sobol`

  > 추가적인 이해 필요



#### parallelTrialCount

Katib이 병렬로 train하는 hyper parameter 조합의 최대 수입니다. 

> default: `3`



#### maxTrialCount

실행 할 최대 시도 횟수. Katib가 model을 test하기 위해 생성해야 하는 hyper parameter 조합의 수.

> 값을 생략하면 목표에 도달하거나 실험이 실패한 시도의 최대 수에 도달할 때까지 experiment가 실행된다.



#### maxFailedTrialCount

Katib가 model을 test하는 도중 실패하는 경우의 count최대값

Katib는 상태가 Failed 또는 MetricsUnavailable인 경우 실패한 시도로 인식하고, 실패한 시도의 수가 maxFailedTrialCount에 도달하면 Katib은 실패 상태로 실험을 중지한다.



#### parameters

experiment search space. 

`parameters` 에서 optimizer할 parameter를 정의할 수 있다.



```
  parameters:
    - name: lr
      parameterType: double
      feasibleSpace:
        min: "0.01"
        max: "0.03"
    - name: num-layers
      parameterType: int
      feasibleSpace:
        min: "2"
        max: "5"
    - name: optimizer
      parameterType: categorical
      feasibleSpace:
        list:
          - sgd
          - adam
          - ftrl
```

- `name:` 적용할 hyper parameter 명시

- `parameterType:`  hyper parameter의 data type

- `feasibleSpace:` hyper parameter의 범위 또는 종류를 정의한다.

  

**name: optimizer** 인 경우 `feasibleSpace.list` 의 종류는 아래와 같다.

`sgd`, `adam`, `ftrl`



#### [metricsCollectorSpec](https://www.kubeflow.org/docs/components/katib/experiment/#metrics-collector)

얻고자 하는 metrics를 어떤 방식으로 얻을것인지, metrics collector에 대한 사양(specification)를 정의한다.

```
  metricsCollectorSpec:
    source:
      filter:
        metricsFormat:
        - "([\\w|-]+)\\s*=\\s*((-?\\d+)(\\.\\d+)?)"
      fileSystemPath:
        path: /mnist-with-summaries-logs/metric.json
        kind: File
        format: JSON
    collector:
      kind: StdOut
```

##### Source  

- `fileSystemPath:`

  - `path` 

  - `kind:` 위의 path가 directory인지, file인지를 명시

    - `Directory` : `collector.kind: TensorFlowEvent` 인 경우 사용되는 [예시](https://github.com/kubeflow/katib/blob/master/examples/v1beta1/kubeflow-training-operator/tfjob-mnist-with-summaries.yaml#L16-L22) 

    - `File` : `collector.kind: File` 인경우 사용됨

      `.log`, `.json`등의 format으로 저장 가능

  - `format` :  `kind: File`인 경우 file의 format결정 

    > `path: "/katib/mnist.log"` 처럼 `.log` format이면 `format` 은 정의 안해도 됨

- `filter:` metric의 형식을 지정

  - `metricsFormat`

    `"([\\w|-]+)\\s*=\\s*((-?\\d+)(\\.\\d+)?)"` : default metric형식으로, `{{MetricsName}}={{MetricsValue}}` 이다. (위 code와 같은 경우 생략해도 됨)



##### collector

metrics collector를 정의한다.

kind type

- `StdOut` default metrics collector

  system의 기본 출력 위치에서 metrics를 collect

- `File` 

  `.source.fileSystemPath.path` 에서 정의된 file위치에 metric을 기록, 저장

  path가 json format일 경우 metric의 형식은 아래 두 가지 규칙을 따라야 한다.

  - 구분 단위는 epoch 또는 step으로 하며, 줄로 구분한다.
  - 시간 값의 key는 `timestamp`으로 고정한다.

  예시

  ```
  {"epoch": 0, "foo": "bar", "fizz": "buzz", "timestamp": 1638422847.28721…}
  {"epoch": 1, "foo": "bar", "fizz": "buzz", "timestamp": 1638422847.287801…}
  {"epoch": 2, "foo": "bar", "fizz": "buzz", "timestamp": "2021-12-02T14:27:50.000035161+09:00"…}
  {"epoch": 3, "foo": "바", "fizz": "buzz", "timestamp": "2021-12-02T14:27:50.000037459+09:00"…}
  ```

- `TensorFlowEvent` : tensflow사용할 때 공부 ([공식](https://www.kubeflow.org/docs/components/katib/experiment/#metrics-collector)) ([예시](https://github.com/kubeflow/katib/blob/master/examples/v1beta1/kubeflow-training-operator/tfjob-mnist-with-summaries.yaml#L16-L22))

- `None` 

  Katib의 metric 수집기를 사용할 필요가 없는 경우 이 값을 지정

- `Custom` 

##### 





#### trialTemplate

test 시도를 정의한다. 



##### primaryContainerName

training container의 이름 명시

```
  trialTemplate:
    primaryContainerName: training-container
```



##### trialParameters

experiment 실행 중 trial template에서 사용되는 parameters의 목록

```
  trialTemplate:
    trialParameters:
      - name: learningRate
        description: Learning rate for the training model
        reference: lr
      - name: numberLayers
        description: Number of training model layers
        reference: num-layers
      - name: optimizer
        description: Training model optimizer (sdg, adam or ftrl)
        reference: optimizer
```

- `name:` Template에서 대체되는 hyper parameter parameter이름
- `description:` hyper parameter에 대한 설명
- `reference:` experiment search space인 `sepc.parameters` 에 명시된 hyper parameters와 동일해야 한다.



##### trialSpec

job resource를 따로 생성한 후 가져오지 않고, `trialTemplate.trialSpec`에서 job을 정의한다.

`trialSpec`에 정의된 hyper parameters는 command-line arguments 또는 environment variables으로 수신이 가능하다.

```
  trialTemplate:
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
                image: docker.io/kubeflowkatib/mxnet-mnist:latest
                command:
                  - "python3"
                  - "/opt/mxnet-mnist/mnist.py"
                  - "--batch-size=64"
                  - "--lr=${trialParameters.learningRate}"
                  - "--num-layers=${trialParameters.numberLayers}"
                  - "--optimizer=${trialParameters.optimizer}"
            restartPolicy: Never
```

- `kind:` Job의 종류 중 하나 결정

  - `job`
  - `TFJob` : tensorflow를 사용한 code를 통해 training을 진행할 때 사용
  - `PyTorchJob` : PyTorchJob를 사용한 code를 통해 training을 진행할 때 사용

- `spec:`

  - `name:` 가져올 container의 이름을 결정

  - `image:` container화 한 training code image

  - `command:` python code를 실행할 때 사용할 command line

    > `--lr`, `--num-layers`, `--optimizer` 를 args로 받는 code이기 때문에, `--` flag를 통해 `trialParameters` value를 전달하고 있다.

  

- `sidecar.istio.io/inject: "false"`

  add `sidecar.istio.io/inject: "false"`

  kubeflow를 istio와 함께 사용하기 때문에 pod에 istio-proxy가 자동으로 추가된다. 이를 방지하기 위해 `sidecar.istio.io/inject: "false"`가 포함되어야 한다.

  ```
    ...
      
      trialSpec:
        apiVersion: batch/v1
        kind: Job
        spec:
          template:
            metadata:
              annotations:
                sidecar.istio.io/inject: "false"
            spec:
            ...
  ```

  > `spec.trialTemplate.trialSpec.spec.template.metadata` 에 `annotations.sidecar.istio.io/inject: "false" `를 추가



### Example

**using random search algorithm**

1. Download the example

   ```
   $ curl https://raw.githubusercontent.com/kubeflow/katib/master/examples/v1beta1/hp-tuning/random.yaml --output random.yaml
   ```

   

   Edit `random.yaml`

   ```
   $ vi random.yaml
   ```

   - change namespace to Kubeflow user profile

     ```
     metadata:
       namespace: project-pipeline
     ```

     > `project-pipeline` 라는 namespace에 Experiment 생성하도록 설정

    - add `sidecar.istio.io/inject: "false"`

      kubeflow를 istio와 함께 사용하기 때문에 pod에 istio-proxy가 자동으로 추가된다. 이를 방지하기 위해 `sidecar.istio.io/inject: "false"`가 포함되어야 한다.

      ```
        ...
          
          trialSpec:
            apiVersion: batch/v1
            kind: Job
            spec:
              template:
                metadata:
                  annotations:
                    sidecar.istio.io/inject: "false"
                spec:
                ...
      ```

      > `spec.trialTemplate.trialSpec.spec.template.metadata` 에 `annotations.sidecar.istio.io/inject: "false" `를 추가

2. Deploy the example

   ```
   $ kubectl apply -f random.yaml
   ```

   

   

#### check status

check the experiment status

```
$ kubectl -n kubeflow-user-example-com get experiment random -o yaml
```



##### conditions

 `status.conditions`의 마지막`type` 값이 `Succeeded` 이면 experiment가 완료된 것



##### currentOptimalTrial

`status.currentOptimalTrial`에서 algorithm에 의해 얻어진 가장 성능이 좋은 trial를 확인할 수 있다.

- `bestTrialName` : trial name
- `observation.metrics` : 목표 및 추가 metrics에 기록된 값 및 정보를 확인할 수 있다.
- `parameterAssignments` : 해당 parameters의 조합

관련 값은 kubeflow central dashboard에서도 확인이 가능하다.