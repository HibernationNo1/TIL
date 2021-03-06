# tensorflow 시작

## 1. 시작

### 1. tensorflow 설치

1. 가상환경 만든 후 활성화 (권장)

   > [가상환경 만들기](https://github.com/HibernationNo1/TIL/blob/master/%EA%B0%80%EC%83%81%ED%99%98%EA%B2%BD%20%EB%A7%8C%EB%93%A4%EA%B8%B0.md)

2. 텐서플로우 설치

   > 명령 프롬프트에서 
   >
   > $ pip install tesorflow

3. 파이썬 터미널 열기

   > 명령 프롬프트에서 
   >
   > $ python

4. 텐서플로우 패키지를 임포트

   > 명령 프롬프트에서 
   >
   > $ import tensorflow as tf
   >
   > 이후 
   >
   > $ print(tf.__version__)
   >
   > 를 입력하면 텐서플로우의 설치 여부 및 버전을 확인할 수 있다.

   

### 2. VScode에서 tensorflow 시작

```python
import tensorflow as tf

print(tf.__version__)
```

위와 같은 코드를 VScode에 입력 후 저장, Ctrl+Alt+N 을 했을 때 vscode의 터미널은 code터미널이 실행이 되며 tensorflow 모듈이 없다고 뜬다.

그러므로 코드 위에서 우클릭 후 Run python File in Terminal 을 클릭해서 코드를 실행해야만 한다.



## 2. TensorFlow의 알고리즘 구현 2가지 방식

[텐서플로우 학습 방법](https://www.tensorflow.org/overview?hl=ko)

### 1. Beginner style(초보자용)

사용자에게 친숙한 Sequential API로 시작하는 것이 가장 좋습니다. 구성요소를 연결하여 모델을 만들 수 있습니다. 

> 간결하게 구현이 가능하다.
>
> 디테일한 부분들은 직접 컨트롤을 하는데 제한이 있다.

### 2. expert style(전문가용)

Subclassing API는 고급 연구를 위한 define-by-run 인터페이스를 제공합니다. 모델에 대한 클래스를 만든 다음 명령형으로 순방향 패스를 작성합니다. 맞춤형 레이어, 활성화 및 학습 루프를 쉽게 만들 수 있습니다. 

> 케라스 서브클래싱 방식(케라스 모델을 상속받는 클래스를 생성 후 코딩)
>
> 알고리즘의 디테일한 부분을 컨트롤할 수 있다.
>
> 복잡한 코드구조를 가지고 있다.
>
> 구글에서 장려하는 방법