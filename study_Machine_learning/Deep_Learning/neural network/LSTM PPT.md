# LSTM PPT

**page_1**

**page_2**

LSTM이란?

LSTM은 순서에 따라 서로 연관된 정보를 가진 데이터(시계열 데이터)를 다루기 위해 고안된 신경망으로, 가장 기본적인 시퀀스 모델인 RNN의 단점을 해결하고자 하여 탄생했다.



**page_3**

그럼, RNN이란 무엇이냐

기본적인 ANN구조에서

이전 시간(t-1)의 은닉층의 출력값을 다음 시간(t)에 은닉층의 입력값으로 다시 집어넣는 경로가 추가된 형태이다. 



지금 보이는 RNN을 시간의 흐름 순으로 unfold하게 표현하면 그림과 같다.

![](https://wikidocs.net/images/page/22886/rnn_image2_ver3.PNG)