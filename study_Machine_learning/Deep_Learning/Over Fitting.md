# Over Fitting

오버피팅: 학습 과정에서 머신러닝 알고리즘의 파라미터가 트레이닝 데이터에 과도하게 최적화되어 트레이닝 데이터에 대해서는 잘 동작하지만 새로운 데이터인 테스트 데이터에 대해서는 잘 동작하지 못하는 현상.

(모델이 범용적으로 좋은 방향으로 개선되는것이 아닌, 트레이닝만을 위한 방향으로 개선되는 것



over fitting이 발생하는 이유 (polynimial regression를 예로 들어 설명)

![](https://github.com/HibernationNo1/TIL/blob/master/image/34.jpg?raw=true)

위의 모습은 polynimial regression에서 모델이 y = sin(x) 함수를 학습하는 모습이다.

( y  = sin(x)함수에 대한 모델 widehat{y} 의 차수가 1, 2, 3, 9인 회귀의 학습)

모델의 차수가 높아질 수록 더 많은 곡선을 표현할 수 있게 되고, 그로 인해 모든 noise data point까지 정확하게 지나가도록 학습되는 모습을 볼 수 있다. 

> 4번째 그림에서 9개의 data point를 9차식으로 설계된 모델이 9개의 곡선을 그리며 지나가는 모양을 볼 수 있다.

즉, noise를 완벽하게 지나게 되기 때문에(noise를 학습하게 되기 때문에) 또 다른 data set 에 대해서 정확한 학습이 진행되지 않게 된다.



이러한 over fitting을 해결하기 위한 기법을 [Regularization](https://github.com/HibernationNo1/TIL/blob/master/study_Machine_learning/Deep_Learning/Regularization.md)이라고 한다.

