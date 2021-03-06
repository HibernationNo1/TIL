# 임베딩(Embedding)

## 개념

임베딩은 머신러닝 알고리즘을 사용할 때, 그 중에서도 측히 자연어 처리 문제를 다룰 때 널리 사용되는 기법이다.

머신러닝 알고리즘을 사용할 때 데이터를 표현하는 일반적인 방법은 one-hot Encoding이지만, 이는 데이터의 표현 형태가 Sparse(희소)하다는 문제점이 있다.

> 데이터를 표현 할 때 의미있는 데이터는 전체 데이터 중 극히 일부분이다. 또한 one-hot  Encoding은 유사한 의미를 가진 단어간의 연관성도 표현할 수 없다.

임베딩은 이러한 문제점을 해결하기 위해서 Sparse한 One-hot Encoding의 데이터 표현을 Dense한 표편형태로 변환하는 기법이다. 이를 위해서 Dense한 입베딩 행렬을 곱해서 데이터의 표현형태를 변환한다.

- 수식
  $$
  x_{embedding} = W_{embedding}x_{one-hot}
  $$
  

- 원리

  값이 채워져 있는 임베딩 매트릭스를 만든 후 Sparse한 데이터에 곱하면 더 작은 차원의 빽빽한 데이터로 변환된다.

- 장점

  1. Sparse한 데이터 표현형을 Dense한 데이터 표현형으로 변환해서 딥러닝 알고리즘에 학습하기 적합한 빽빽한 행렬형태로 변환한다.
  2. dimension reduction(차원 축소)효과가 있다.
  3. 임베딩 매트릭스가 잘 학습된, 의미있는 매트릭스일때  해당 매트릭스와 곱해서 변환환 매트릭스가 유의미한 데이터의 연관성을 표현할 수 있다. 