# tensorflow 시작

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