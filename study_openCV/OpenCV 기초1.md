# OpenCV 기초

OpenCV 함수 검색 웹사이트 https://docs.opencv.org/master/

> 기본적으로 C++형태로 나옴



```python
import cv2
```



#### 1. 영상 가져오기

##### 1. cv2.imread()

영상 파일을 불러오는 함수

`cv2.imread(filename, flags = IMEAD_COLOR)`

`filename`: 불러올 파일 이름(문자열)

`flags`: 영상 파일 불러오기 옵션 이건 default가 `IMEAD_COLOR`이다.  (None으로 주거나, 아예 입력 안해도 됨)

> `flags = IMEAD_COLOR` : BGR 컬러 영상으로 읽기(default)   // shape = (rows, cols, 3)
>
> `flags = IMEAD_GRAYSCALE` : 흑백 영상으로 읽기	// shape = (rows, cols)
>
> `flags = IMEAD_UNCHANGED` : 영상 파일 속성 그대로 읽기 	 // shape = (rows, cols, 4)
>
> 주로 투명한 속성의 PNG파일을 불러올때 사용한다.
>
> 
>
> 불러온 영상 데이터는 ndarray 형태로 불러오게 된다.
>
> 
>
> 이 외에도 수많은 flags 옵션이 있지만, 위 세개가 가장 많이 쓰인다.

```python
img = cv2.imread('cat.bmp')
#	img = cv2.imread('cat.bmp', IMEAD_GRAYSCALE)
#	img = cv2.imread('cat.bmp', IMEAD_COLOR)   # 'flags =' 는 뺴도 됨 

if img is None:  		# image를 불러오면 항상 이런 식으로 잘 load 됐는지 확인하자.
    print('Image load failed!')
    sys.exit()
```



##### 2. cv2.imwrite()

영상 파일을 저장하는 함수. (정상적으로 저장하면 Ture, 실패하면 False 반환)

`cv2.imwrite(filename, img, params = None)`

`img` : 저장할 영상 데이터

`params`: 파일 저장 옵션 지정 (대부분의 경우 지정 잘 안함)

```python
cv2.imwrite('cat_gray.png', img)
```



> 아래에서 설명하는, 창을 띄운 상태에서 ctrl+s 를 누르면 해당 창의 image를 file로 저장할 수 있다.



#### 2. 창 띄우기, 닫기, 크기 변경

##### 1. cv2.namedWindow()

창을 띄우고 고유 이름(title)을 정한다. (창을 띄우는 것이지 image를 띄우는 게 아님)

> figure의 title이라고 생각하면 됨

`cv2.namedWindow(winname, flags = None)`

`winname` : image 창의 title

`flags` : 창 속성 지정 플래그

> `flags = cv2.WINDOW_NORMAL` : 영상 크기를 창 크기에 맞게 지정 (마우스로 창 크기 조정 가능. 영상이 너무 클 때만 사용하자)
>
> `flags = cv2.WINDOW_AUTOSIZE` : 창 크기를 영상 크기에 맞게 변경 (default)



##### 2. cv2.destroyWindow()

지정한 image 창 하나를 닫는다.

`cv2.destroyWindow(winname)`

`winname`: 닫고자 하는 창 이름

> 띄워져 있는 모든 창을 닫을땐 아래 함수를 사용
>
> `cv2.destroyAllWindows()` 



##### 3. cv2.resizeWindow()

image 창 크기를 고정

`cv2.resizeWindow(winname, width, height)`

단, 생성된 창이 `flags = cv2.WINDOW_NORMAL` 의 옵션을 가진 cv2.namedWindow() 로 만들어져야 한다.



#### 3. image 출력

##### 1. cv2.imshow()

`cv2.imshow(winname, img)`

`winname`: 영상을 출력할 대상 창 이름

`img`: 출력할 영상 데이터 (numpy의 ndarray)

> 여기서 img의 data type이 uint 8이 아니면 영상이 이상하게 출력될 수 있다. 그러므로 영상 데이터를 출력할 때는 uint 8로 type을 변셩해서 넣지

실제 영상이 창 위에 띄워지려면 `cv2.waitKey()`함수도 호출해야 한다.

```python
cv2.imshow('image', img)
cv2.waitKey()



- `cv2.waitKey()` 창이 띄워진 상태에서 키보드 아무 키나 누르면 창이 닫힌다.

  이 함수에는 delay 옵션이 있다.

  delay 옵션은 숫자값의 입력을 ms로 환산해서 시간으로 인지하고, 해당 시간이 지나면 자동으로 창이 닫히게 된다.

  ```python
  cv2.imshow('image', img)
  cv2.waitKey(3000) # 3초 후 자동으로 창 닫힘
```

  > return 값으로 입력된 키보드 값의 아스키 코드를 return한다.
  >
  > 이를 통해 특정 키를 입력할때만 창이 닫히게 코드를 짤 수 있다.
  >
  > ```python
  > while True:
  >     if cv2.waitKey() == 27:  # 27은 esc의 아스키 코드임
  >         break
  > ```

창이 띄워져 있는 상태에서 Ctrl+c를 누르면 그림이 클립보드에 복사된 상태로 창은 닫치게 된다.



##### 2. matplotlib을 사용한 출력

openCV에서 컬러 영상의 색상 정보가 BGR 순서이지만, matplot에서는 컬러 영상의 색상 정보가 RGB순서이기 때문에 

`cv2.imread()` 함수로 불러온 영상의 BGR순서를 RGB순서로 바꿔줘야 한다.

이 때 사용하는 것이 `cv2.cvtColor()` 이다.

- `cv2.cvtColor(imagename, cv2.COLOR_BRG2RGB)` : BGR순서를 RGB순서로 바꿔주는 역할

- `plt.imshow()` : 영상 출력 함수  // plt.show() 가 아님.

  > 흑백 영상은 cmap = 'gray'로 지정해줘야 한다.

```python
imgBGR = cv2.imread('cat.bmp')
imgRGB = cv2.cvtClolor(imgBGR, cv2.COLOR_BGR2RGB)

plt.axis('off')  	# 축을 아예 없애버린다.
plt.imshow(imgRGB)  # plt.imshow(imgRGB, cmap = 'gray')
plt.show()
```





#### 4. 데이터 자료형

이미지 1

cv2.imread() 를 통해 불러온 데이터는 ndarray type이기 때문에 numpy 메서드를 이용할 수 있음을 기억하자.

```python
img = cv2.imread('cat.bmp')

if img is None:
    print('Image load fialed!')
    sys.exit()
    
print(type(img1)) 	# numpy.ndarray
print(img.shape) 	# (480, 640, 3)
print(img.dtype)	# uint8 
```

