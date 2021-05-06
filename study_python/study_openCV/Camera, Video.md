# Camera, Video

## VideoCapture 

OpenCV에서는 카메라와 동영상으로부터 frame을 받아오는 작업을 `cv2.VideoCapture` 클래스 하나로 처리한다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/c2.jpg?raw=true)

```python
retval = cv2.VideoCapture()
```

instanse 생성



### 1. camera

#### 연결

##### 1. cv2.VideoCapture()

```python
retval = cv2.VideoCapture.open(index, apiPreference = None)
```

`index` : camera_id + domain_offset_id

> 카메라를 열 때는 숫자값이 들어간다.
>
> 동영상을 열 때는 file name이 들어간다.
>
> index에 0을 전달하면 PC에 연결된 기본 camera가 전달된다. (장치 관리자에 연결된)

`apiPreference` : 선호하는 카메라 처리 방법을 지정

`retval` : instance. 성공하면 Ture, 실패하면 False 반환

```python
retval = cv2.VideoCapture(0)
```

> 내 카메라를 받아온다.



##### 2. isOpened()

```python
cv2.VideoCapture.isOpened()
```

카메라가 성공적으로 open됐는지 확인하는 함수. 성공하면 Ture, 실패하면 False 반환



##### 3. read()

open된 camera에서 한 frame을 받아오는 함수.

한 frame을 받아오기 때문에, video를 받으려면 while문을 사용해야 한다.

```python
retval, image = cv2.VideoCapture.read(image = None)
```

`retval` : 성공하면 Ture, 실패하면 False 반환

`image` : 현제 프레임 (ndarray)

두 개의 반환값을 가진다.



##### 4. release()

연결된 camera를 해제한다.

```python
cv2.VideoCapture.release()
```



**예시**

```python
import numpy as np
import cv2
import sys

retval = cv2.VideoCapture(0)		# instance 생성, PC에 연결된 기본 카메라 open
# retval.open(0)	을 한 것과 같다.	

if not retval.isOpened():	# camera가 잘 open 됐는지 확인
    print('camera open failed!')
    sys.exit()

while True:
    ret, frame = retval.read()
    
    if not ret:
        break
        
    cv2.imshow('frame', frame)
    if cv2.waitKey(20) ==  27:  # ESC를 누르면 창이 꺼진다
        break                   # waitKey(20)을 줘야 20ms마다 frame을 가져온다.
        
retval.release()
cv2.destroyAllWindows()
```



#### 속성

##### 1. get()

```python
cv2.VideoCapture.get(propId)
```

>  True or False 반환

`propId`: 속성 상수

![](https://github.com/HibernationNo1/TIL/blob/master/image/c3.jpg?raw=true)

이 외에도 OpenCV document에 가면 더 많은 속성을 볼 수 있다.



**예시**

```python
w = int(retval.get(cv2.CAP_PROP_FRAME_WIDTH))
h = int(retval.get(cv2.CAP_PROP_FRAME_HEIGHT))
```

>get이 double값을 return하기 때문에 int



##### 2. set()

속성을 설정할 수 있다.

```python
cv2.VideoCapture.set(propId, num)
```

>  True or False 반환

`propId`: 속성 상수

`num` : 속성 상수를 결정할 값

**예시**

```python
w = retval.set(cv2.CAP_PROP_FRAME_WIDTH, 320)
h = retval.set(cv2.CAP_PROP_FRAME_HEIGHT, 240)
```

> 폭: 320, 높이: 240 형태로 video가 출력됨을 확인할 수 있다. 



---

### 2. Video File

위의 `cv2.VideoCapture.open(index, apiPreference = )`의 index 대신 file name을 넣으면 된다.



**예시**

```python
import numpy as np
import cv2
import sys

retval = cv2.VideoCapture('video1.mp4')		

if not retval.isOpened():	# video가 잘 open 됐는지 확인
    print('video open failed!')
    sys.exit()

while True:
    ret, frame = retval.read()
    
    if not ret:	# 동영상 마지막에는 자동으로 break
        break
        
    cv2.imshow('frame', frame)
    if cv2.waitKey(20) ==  27:  # ESC를 누르면 창이 꺼진다
        break                   # waitKey(20)을 줘야 20ms마다 frame을 가져온다.
        
retval.release()
cv2.destroyAllWindows()
```





## VideoWriter

OpenCV에서는 cv2.VideiWriter class를 이용해서 일련의 frame을 video file로 저장할 수 있다.

일련의 frame은 모두 size와 data type이 같아야 한다.



**Fourcc(4-문자 코드)**

동영상 파일의 코덱, 압축 방식, color, pixel format등을 정의하는 정수 값

![](https://github.com/HibernationNo1/TIL/blob/master/image/c4.jpg?raw=true)



##### 1. cv2.VideoWriter()

동영상을 저장하는 함수

```python
fourcc = cv2.VideoWriter_fourcc(*'DIVX') # 예시
cv2.VideoWriter(filename, fourcc, fps, frameSize, isColor = )
```

`fps` : 초당 frame 수

`isColor` : color video면 True, 아니면 False



##### 2. isOpened()

video file이 준비되었는지 확인

```python
cv2.VideoWriter.isOpened()
```



##### 3. write()

frame 저장하기

```python
cv2.VideoWriter.write(image)
```

`image` : 저장할 frame (ndarray)



**예시**

camera로부터 일련의 frame(video)를 따서 file에 저장

```python
cap = cv2.VideoCapture(0)

if not cap.isOPend():
    print("camera open failed")
    sys.exit()
    
w = round(cap.get(cv2.CAP_PROP_FRAME_WIDTH))  # 반올림으 사용해서 정수값으로 만듦
h = round(cap.get(cv2.CAP_PROP_FRAME_HEIGHT))
fps = cap.get(cv2.CAP_PROP_FPS)	# 내 camera의 초당 frame수를 get 

fourcc = cv2.VideoWriter_fourcc(*'DIVX')
delay = round(1000 / fps)		# 한 frame과 그 다음 frame 사이의 시간 간격을 계산

out = cv2.VideoWriter('output.avi', fourcc, fps, (w, h))
# VideoWriter instance 생성  (녹화 객체)  
# color영상을 저장하기 위해 속성을 설정했으므로 gray scale 영상은 저장이 안됨

if not out.isOpened():		# 녹화 준비가 잘 됐는지 확인
    print('File open failed!')
    cap.release()
    sys.exit()
	
while True:
    ret, frame = cap.read()
    
    if not ret:
        break
    
    
    
    out.write(frame) # while문이 돌 때마다 frame 저장 
    
    cv2.imshow('frame', frame)
    
    inversed = ~frame 	# frame을 반전. 색상 반전 필터라고 생각하면 됨
    cv2.imshow('inversed', inversed)
    
    if cv2.waitkey(delay) == 27 :
        break

cap.release()
out.release()
cv2.destroyAllWindows()
```

> video만 저장하고 sound는 저장하지 않음





