# Worker Job

[공식](https://www.kubeflow.org/docs/components/katib/overview/#worker-job)

`Worker Job`은 `Trial`을 평가하고 목표 값을 계산하는 프로세스를 의미하며, 제안된 hyper parameter조합을 넘겨 받아서 실제로 모델을 학습한다.

type of `Worker Job`

- [Kubernetes `Job`](https://kubernetes.io/docs/concepts/workloads/controllers/job/)
- [Kubeflow `TFJob`](https://www.kubeflow.org/docs/components/training/tftraining/)
- [Kubeflow `PyTorchJob`](https://www.kubeflow.org/docs/components/training/pytorch/)

그 외 많지만 `Kubeflow PyTorchJob` 에 대해서 공부



## PyTorchJob



1. Check PytorchJob custom resource is installed

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

   

