# Worker Job

[katib 공식](https://www.kubeflow.org/docs/components/katib/overview/#worker-job), [kubernetes 공식](https://kubernetes.io/docs/concepts/workloads/controllers/job/)

**Worker job** : 

kubenetes에서 실제 model의 training을 수행할 때 사용하는 kubernetes custom resource로, 하나 이상의 pod를 생성하고 pod가 성공적으로 종료(학습 완료)될 때까지 실행을 계속 재시도한다. 

pod의 training이 성공적으로 완료되면 job은 해당 완료를 추적한다.

job을 삭제하면 생성된 pod또한 삭제되며, job을 일시 중단하면 다시 재개될 때가지 activation pod가 삭제된다. 

**katib의 experiment에서 job의 의미: `Trial`을 평가하고 목표 값을 계산하는 프로세스를 의미하며, 제안된 hyper parameter조합을 넘겨 받아서 실제로 모델을 학습한다.**



이러한 job은 여러 type이 있다.

type of `Worker Job`

- [Kubernetes `Job`](https://kubernetes.io/docs/concepts/workloads/controllers/job/) 
- [Kubeflow `TFJob` ](https://www.kubeflow.org/docs/components/training/tftraining/) (분산처리 지원)
- [Kubeflow `PyTorchJob`](https://www.kubeflow.org/docs/components/training/pytorch/) (분산처리 지원)

그 외 많지만 `Kubeflow PyTorchJob` 에 대해서 공부







## PyTorchJob





### confirm PyTorch Operator

1. Check `PytorchJob` custom resource is installed

   ```
   $ kubectl get crd pytorchjobs.kubeflow.org
   ```

   ```
   NAME                       CREATED AT
   pytorchjobs.kubeflow.org   2022-09-22T06:24:08Z
   ```

   

2. Check that the Training operator is running

   ```
   $ kubectl get pods -n kubeflow | grep training-operator
   ```

   ```
   training-operator-6c9f6fd894-s4klv                       1/1     Running   0             27h
   ```

   

### Creating a PyTorch training job

**example**

```
apiVersion: "kubeflow.org/v1"
kind: PyTorchJob
metadata:
  name: pytorch-simple
  namespace: kubeflow
spec:
  pytorchReplicaSpecs:
    Master:
      replicas: 1
      restartPolicy: OnFailure
      template:
        spec:
          containers:
            - name: pytorch
              image: docker.io/kubeflowkatib/pytorch-mnist:v1beta1-45c5727
              imagePullPolicy: Always
              command:
                - "python3"
                - "/opt/pytorch-mnist/mnist.py"
                - "--epochs=1"
          restartPolicy: Never
    Worker:
      replicas: 1
      restartPolicy: OnFailure
      template:
        spec:
          containers:
            - name: pytorch
              image: docker.io/kubeflowkatib/pytorch-mnist:v1beta1-45c5727
              imagePullPolicy: Always
              command:
                - "python3"
                - "/opt/pytorch-mnist/mnist.py"
                - "--epochs=1"
```

- `kind:` PyTorchJob 명시

- `metadata:` 이름과 namespace결정

- `spec:` 

  - `pytorchReplicaSpecs:` node가 여러개일 때 사용하는 flag

    - **`template.spec:`**

      - `name:` 가져올 container의 이름을 결정

      - `image:` container화 한 training code image

      - `command:` python code를 실행할 때 사용할 command line

      - `imagePullPolicy:` image를 pull할 때 kubelet에 의해 동작될 option을 명시한다.

        > - `IfNotPresent` : image가 local에 없는 경우에만 image를 pull한다.
        > - `Always` : local에 container가 있으면 해당 contianer를 사용하고, 없는 경우에는 registry에서  pull한다.
        > - `Never` : image를 pull하지 않는다. image가 local에 있는 경우에만 contianer가 실행된다.  

      - `restartPolicy:` container가 종료되었을 때 kubelet에 의한 container 재시작 정책을 관리한다.

        선언하지 않을 시 default는 `Always`

        > - `Always` :  container가 종료되면 항상 재시작 (정상 종료여도)
        > - `OnFailure` :  container가 비정상적으로 종료시 재시작 
        > - `Never` : 어떠한 경우에도 재시작 하지 않음

      