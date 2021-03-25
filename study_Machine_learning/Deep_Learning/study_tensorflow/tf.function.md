# tf.function

- 텐서플로 2에서는 즉시 실행(eager execution)이 기본적으로 활성화되어 있다. 하지만 tf.function을 사용하면 즉시 실행 모드 보다 빠르게 동작한다.

- @tf.function으로 정의한 함수 안에서 연산은 기본 텐서플로 연산으로 이루어진다. 즉시 실행 모드로 실행하거나 그레이디언트를 계산할 수 있다.

  > @tf.function으로 정의하면 그래프 최적화 (Graph Optimization) 하여 연산을 수행할 수 있도록 @tf.function 과 AutoGraph 모듈을 사용하여 자동으로 그래프로 변환하여 연산이 진행된다.
  >
  > @tf.function을 사용하면 파이썬 함수를 TF operation처럼 정의 할 수 있다. eagerly 실행 할 수 있고, graph 내에서 사용 할 수 있으며 물론 gradients도 갖는다.
  >
  > @tf.function 을 사용하면 함수처럼 호출 되지만 graph로 컴파일 된다. 그 말인 즉슨, GPU나 TPU위에서 빠른 실행을 시킬 수 있고 SaveModel을 통해 export도 가능하단 것.

- @tf.function 안에서 넘파이와 파이썬 호출은 상수로 바뀐다.

- @데코레이션을 사용해서 tf.function으로 정의할 수 있다.

**덧셈 예시**

```python
import tensorflow as tf

@tf.function 
def add(a, b):
  return a + b

add(tf.2*ones([2, 2]), tf.ones([2, 2]))  #  [[3, 3], [3, 3]]
```

