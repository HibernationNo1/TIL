# Matplotlib

**matplotlib.pyplot**모듈은 MATLAB과 비슷하게 명령어 스타일로 동작하는 함수의 모음이다.

pyplot 모듈의 각각의 함수를 사용해서 그래프를 만들고 변화를 줄 수 있다.

matplotlib 3.3이 Windows에서 제대로 작동하지 않을 수 있기 때문에 `pip install matplotlib==3.2`를 통해 설치하자.

```python
import matplotlib.pyplot as plt
```

- `plt.draw(), plt.show()` : 화면에 이미지 팝업창을 띄워주는 함수

  > 차이점
  >
  > `plt.show()` : 작업중인 현재 그림이 표시됨
  >
  > `plt.draw()` : 그림을 다시 그림. 이렇게하면 대화 형 모드에서 작업 할 수 있으며 데이터 나 서식을 변경 한 경우 그래프 자체를 변경할 수 있다.

- `plt.waitforbuttonpress()` : 아무 버튼이 눌리면 이미지 팝업창 닫음

- `plt.subplots` : 한 번에 여러 그래프를 보여주기 위해 사용되는 코드

  > figsize 를 통해 이미지의 크기를 조절할 수 있다.

- `imshow()`: 이미치를 할당하는 함수

  > 다음 plt.show() 를 통해 이미지를 출력할 수 있다.

- `savefig('파일이름.형식')`: 변수에 할당된 이미지를 이름과 형식을 설정하여 파일로 저장

  >  예) 변수 f에 이미지 또는 그래프가 할당되어 있을 때
  > `f.savefig('reconstructed_mnist_image.png')` : Reconstruction 결과를 png로 저장