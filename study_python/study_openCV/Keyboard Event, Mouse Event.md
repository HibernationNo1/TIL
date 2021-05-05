# Keyboard Event, Mouse Event

### Keyboard Event

#### 1. cv2.waitKey()

keyboard 입력이 있을 때 까지 기다린다. 

```python
retval = cv2.waitKey(delay=None)
```

`delay` : 밀리초 단위 대기시간. delay가 0보다 작거나 크면 무한히 기다린다.

>  default 값은 0.  
>
> camera에서 frame을 20ms delay로 받아오면 영상으로 보여진다.

`retval` : 눌린 키 값을 ASCII code로 반환한다.

- `cv2.imshow()`다음에 와야 image를 볼 수 있다.

  ```python
  cv2.imshow()
  cv2.waitKey()
  ```

- ESC의 ASCII code는 27이므로 이를 이용해서 while문을 빠져나올 수 있다.

  ```python
  while True:
      if cv2.waitKey(20) == 27
      break
  ```

  > ESC == 27, ENTER == 13, TAP == 9

- ord 함수를 이용하면 문자를 ASCII code로 바로 변환할 수 있다. 이를 이용해보자. 

  ```python
  while Ture:
      key = cv2.waitkey()
      if key == 27:
          break
      elif key == ord('i'):
      	img = ~img
  ```

  

### Mouse Event

#### 1. cv2.setMouseCallback()

```python
cv2.setMouseCallback(windowName, onMouse, param = None)
```

`windowName` : mouse event를 인지할 창 이름

> `cv2.namedWindow()` 로 특정 창의 name이 정의되어 있어야 한다.

`onMouse` : mouse event 처리를 위한 call back 함수 이름 (이름 자유)

> mouse event call back 함수는 다음 형식을 따라야 한다.
>
> ```python
> def onMouse(event, x, y, flags, param) # 5개의 인자는 항상 있어야 한다.
> ```
>
> `event`: mouse event 종류 (mouse의 움직임, 클릭 등등)
>
> ![](https://github.com/HibernationNo1/TIL/blob/master/image/c5.jpg?raw=true)
>
> `x, y` : mouse event 발생 좌표
>
> `flags`: mouse event 발생 시 상태 (keyboard에서 Ctrl key를 눌렀다던가 등)
>
> ![](https://github.com/HibernationNo1/TIL/blob/master/image/c6.jpg?raw=true)
>
> `param` : cv2.setMouseCallback() 에서 설정한 데이터. default = None

`param` : 콜백 함수에 전달할 데이터



**예시**

```python
import sys
import numpy as np
import cv2

def on_mouse(event, x, y, flags, param): # onMouse function 만든다.
	if event == cv2.EVENT_LBUTTONDOWN:  # x, y에 값이 알아서 할당된다.
        print(f"EVENT_LBUTTONDOWN : {x, y}" ) 
        # 마우스가 창 위에 한 지점을 클릭하면 해당 좌표 출력
	elif event == cv2.EVENT_MOUSEMOVE:
        # 마우스가 창 위에서 움직일 때 마다(event 발생이 엄청 많음)
        if flags & cv2.EVENT_FLAG_LBUTTON:
            # 마우스 왼쪽 버튼이 눌린 상태일 때
        	print(f"EVENT_MOUSEMOVE : {x, y}" ) 
            # flags는 == 연산자로 하면 EVENT_MOUSEMOVE와 EVENT_FLAG_LBUTTON가 같이 인식되어 아예 event 인지가 되지 않는다. 그렇기 때문에 AND 연산자를 사용해야 한다.
        
    
img = np.ones((480, 640, 3), dtype = np.uint8) * 255  # 하얀색 image

cv2.namedWindow('image')

cv2.setMouseCallback('image', on_mouse) 

cv2.imshow('image', img)
cv2.waitKey()

cv2.destroyAllwindows()
```

> event 는 == 연산자를, flags는 AND 연산자를 사용하자. 



image 창 위에 mouse의 움직임에 따라 그림을 그려보자.

> 위 코드에서 조금만 추가하면 된다.

```python
oldx, oldy = -1
def on_mouse(event, x, y, flags, param): 
    global img, oldx, oldy  # image와 x, y,의 그릇의 용도로 쓸 oldx, oldy를 전역 영역에서 가져온다. 
	if event == cv2.EVENT_MOUSEMOVE:  	# mouse가 움직일 때
		if flags & cv2.EVENT_FLAG_LBUTTON:	# mouse의 왼쪽 button이 눌린 상태일 때
            cv2.line(img, (oldx, oldy), (x, y), (0, 0, 255), 5)
            # line그리기 함수((oldx, oldy)에서 (x, y)로. 빨간색, 굵기 5)
            cv2.imshow('image', img)
            oldx, oldy = x, y
```

> mouse의 좌클릭 상태에서 움직일 때 마다 그 위에 선이 그려짐을 볼 수 있다.