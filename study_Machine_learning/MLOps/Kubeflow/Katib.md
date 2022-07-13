# Katib

> 2022.07에 beta version



## Introduction

이미 구현이 되어있는 HPO search package들을 사용할 때 kubernetes의 자원을 효율적으로 활용하여 HPO를 하고 service화 할 수 있도록 하는 인프라를 구축하는것을 담당한다.



- Cluster Management

  kubernetes에서 알아서 오케스트레이션을 진행하여 자동화가 가능하도록 한다.

- Agnostic to ML Framework

  tensorflow, pytorch 등 어떠한 framework로 개발이 되었든 상관 없이 해당 code를 container화만 할 수 있다면 하이퍼 파라미터 최적화(HPO)를 code의 수정 없이 외부에서 가능하다 .

- 하이퍼 파라미터 최적화(HPO) tools을 k8s상에서 할 수 있도록 support한다 





**Experiments(AutoML)** : kubeflow에서 Experiments(AutoML)은 Katib를 사용하여 HPO를 1회 하는 개념이며, 

이는 Objective, Saerch space, Search algo 가 이루어지는 과정이다.

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



**강의 더 보기 (kubeflow katib)실습, 또는 katib관련 다른 강의. 또는 공식 문서 확인**