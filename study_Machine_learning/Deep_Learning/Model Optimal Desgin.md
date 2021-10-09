# Model Optimal Desgin



- 목적에 알맞은 parameters의 개수를 가진 model 설계

  parameters가 너무 많으면 dataset의 noise까지 learning하게 되어 overfitting이 발생하고,

  parameters가 너무 적으면 dataset에 대해서 제대로 된 learning을 하지 못한다.

  그렇기에 dataset의 목적에 알맞는 model을 설계해야 하는 것이다.



- model selection

  model을 training할 때 eveluation metrics와 monitering 기능을 갖춘다면, 

  model이 원하는 성능에 도달했을 때, model의 상태를 고정시켜 놓고 training, hyper change paramerters등의 구성/훈련 전략의 실험을 진행할 수 있다.

  이러한 과정을 통해 select한 model이 최선의 모델이며, 이러한 과정을 model selection이라고 한다.

