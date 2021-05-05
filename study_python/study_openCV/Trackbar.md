# Trackbar

trackbar : 프로그램 동작 중 사용자가 지정한 범위 안의 값을 선택할 수 있는 컨트롤 바

OpenCV에서 제공하는 그래픽 사용자 인터페이스다.



#### cv2.createTrackbar()

trackbar 생성 함수

```python
cv2.createTrackbar(trackbarName, windowName, value, count, onChange)
```

`trackbarName` : trackbar 이름. 문자열

`windowName` : trackbar를 포함할 창 이름

`value` : trackbar 위치 초기값

`count` : trackbar 최대값. (min은 0임)

`onChange` : trackbar 위치가 변경될 때마다 호출할 call back 함수 이름

> trackbar event call back 함수는 다음 형식을 따름
>
> ```python
> onChange(pos)
> ```



**예시**

> trackbar의 조절로 gray scale을 조절하는 창 만들기

```python
import numpy as np
import cv2

def on_level_changed(pos):
    global img
    # print(pos) # trackbar를 움직일 때마다 bar의 위치를 pos에 반환함을 알 수 있다.
    img[:, :] = pos * 16		# 1, 16, 32, ... 256 까지 
    
img = np.zeros((480, 640), np.uint8)

cv2.namedWindow('image')

cv2.createTrackbar('level', 'image', 0, 16, on_level_changed)

cv2.imshow('image', img)
cv2.waitKey()

cv2.destroyAllWindows()
```

> trackbat를 16까지 올리면 256의 값이 각 pixel에 할당된다. 하지만 image의 type은 uint8이기 때문에 최대 255까지가 max이며, 256을 받으면 0으로 값을 인지해서 창의 색이 검은색으로 된다.
>
> 이를 방지하기 위해서 256의 값이 할당되도 창의 색이 검은색으로 변하지 않도록 해보자.

```python
def on_level_changed(pos):
    global img
    
   	level = pos * 16
    if level >=255:
        level = 255
    img[:, :] = level	# 1, 16, 32, ... 256 까지 
```

