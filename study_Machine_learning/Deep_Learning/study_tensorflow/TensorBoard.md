# TensorBoard

학습 과정을 이미지화 해서 확인할 수 있도록 도와주는 기능

**장점**

1. 실시간으로 학습 과정을 그래프로 확인할 수 있다.

   학습이 시작되고 우리가 원하는 step마다 summary를 실행하는 순간부터 tensorboard에서 학습이 어떻게 되고 있는지 확인 할 수 있다.

2. 기존에 학습했던 것과 동시에 비교 분석이 가능하다.

   같은 step수 안에서 기존과 학습이 더 잘 되고 있는지 또는 performance가 나빠지고 있는지 확인 할 수 있다.

3. 분할 문제를 풀고 있다면 동시에 label과 inference 결과를 실시간으로 image화 해서 확인할 수 있다.

   convolution의 filter나 각 layer에서 나온 결과값들을 실시간으로 확인도 가능하다. 이를 통해 blackbox라고 불리는 신경망을 시각적으로 이해하는데 조금이라도 더 도움이 될 것이다.



## how to use?

### install

```
$ pip install tensorboard
```

> 물론 tensorflow도 설치가 되어있어야 한다.



### execute

```
$ tensorboard --log=log_directory
```

> log_directory안에는 tensorboard에 기록한 data가 존재해야 한다.

오류 없이 tensorboard를 실행하면  http://localhost:6006/ 과 같이 브라우져로 6006번 포트에 들어갈 수 있다.



