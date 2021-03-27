# matplotlib

**matplotlib.pyplot**모듈은 MATLAB과 비슷하게 명령어 스타일로 동작하는 함수의 모음으로, 데이터를 시각화(그래프)할 수 있는 기능을 지원해주는 라이브러리이다. (pyplot 모듈의 각각의 함수를 사용해서 그래프를 만들고 변화를 줄 수 있다.)

matplotlib 3.3이 Windows에서 제대로 작동하지 않을 수 있기 때문에 `pip install matplotlib==3.2`를 통해 설치하자.

```python
import matplotlib as plt
# 또는
import matplotlib.pyplot as plt
```

##### 기본 메서드

- `plt.draw(), plt.show()` : 화면에 이미지 팝업창을 띄워주는 함수

  > 차이점
  >
  > `plt.show()` : 작업중인 현재 그림이 표시됨
  >
  > `plt.draw()` : 그림을 다시 그림. 이렇게하면 대화 형 모드에서 작업 할 수 있으며 데이터 나 서식을 변경 한 경우 그래프 자체를 변경할 수 있다.

- `imshow()`: 이미치를 할당하는 함수

  > 다음 plt.show() 를 통해 이미지를 출력할 수 있다.

- `plt.waitforbuttonpress()` : 아무 버튼이 눌리면 이미지 팝업창 닫음

- `savefig('파일이름.형식')`: 변수에 할당된 이미지를 이름과 형식을 설정하여 파일로 저장

  >  예) 변수 f에 이미지 또는 그래프가 할당되어 있을 때
  >  `f.savefig('reconstructed_mnist_image.png')` : Reconstruction 결과를 png로 저장



##### multi plot

- `plt.subplots` : 한 번에 여러 그래프를 보여주기 위해 사용되는 코드

  > figsize 를 통해 이미지의 크기를 조절할 수 있다.

- `fig = plt.figure()` : fig라는 변수에 figure을 할당한다.

  > figure는 하나의 그래프로, figure()은 빈 그래프를 의미한다.
  >
  > fig = plt.figure(figsize  = (9, 9)) : 그래프 창의 크기를 가로, 세로 9인치를 설정

- `ax = plt.gca()` : ax라는 변수에 

  > gca는 '축'을 의미한다. 그래프는 없지만 축 만을 변수 ax에 할당한 것이다. 
  >
  > 위의 figure함수 호출 후  `ax = fig.gca()` 을 사용하면 축이 있는 그래프 1개가 만들어 진다.
  >
  > 이  ax를 다른 plot에서 매개변수 ax에 할당하면(ax = ax) 해당 plot은 ax라는 변수에 할당된 그래프 위에 그려지게 되는 것이다. 여러 plot에 ax를 매개변수로 할당하면 하나의 그래프에 여러plot이 그려지게 되는 것이다.



##### plot attribute

- `plt.plot(xx, yy)` : x축엔 xx, y축엔 yy로 표현된 실선 그래프
- `plt.bar(xx, yy)` : x축엔 xx, y축엔 yy로 표현된 막대 그래프
  - `plt.barh(xx, yy)`: 막대 그래프를 수평 방향으로 표현한다.

- `plt.grid()`: 그래프에 수직선을 그려준다.

- `plt.xticks(rotation=90)` : x축의 각 데이터 이름을 90도 회전
- `plt.yticks(rotation=m)` : x축의 각 데이터 이름을 m도 만큼 회전

- `plt.title('제목')`: 그래프에 제목 써줌