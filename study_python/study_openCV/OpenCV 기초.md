# OpenCV 기초

OpenCV 함수 검색 웹사이트 https://docs.opencv.org/master/

> 기본적으로 C++형태로 나옴



```python
import cv2
```



##### color space model

![](https://t1.daumcdn.net/cfile/tistory/017E584E5199F0A436)

1. Gray 모델

   색(color) 정보를 사용하지 않고 밝기 정보만으로 영상을 표현하는 것이다. 검정색 0부터 흰색 255까지 총 256단계의 밝기값(intensity)으로 영상 픽셀값을 표현한다.



2. RGB 모델

   가장 기본적인 색상모델로서 색(color)을 Red, Green, Blue의 3가지 성분의 조합으로 생각하는 것이다. RGB 모델에서 검은색은 R=G=B=0, 흰색은 R=G=B=255, 빨강색은 R=255, G=B=0, 노란색은 R=G=255, B=0로 표현된다. R=G=B인 경우는 무채색인 Gray 색상이 된다. R, G, B 각각은 0 ~ 255 사이의 값을 가질 수 있기 때문에 RGB 색상 모델을 사용하면 총 256*256*256 = 16,777,216가지의 색을 표현할 수 있다.

   OpenCV에서는 RGB 대신 BGR으로 사용한다.



3. HSV 모델

    Hue(색조), Saturation(채도), Value(명도)의 3가지 성분으로 색을 표현한다. Hue는 색조(예: 붉은색 계열인지 푸른색 계열인지, ...)를, Saturation은 그 색이 얼마나 선명한(순수한) 색인지를, Value는 밝기(intensity)를 나타낸다. HSV 모델은 우리가 색을 가장 직관적으로 표현할 수 있는 모델이며 또한 머리속에서 상상하는 색을 가장 쉽게 만들어낼 수 있는 모델이다. 영상처리/영상인식에서 HSV 모델을 사용할 때, H, S, V 각각은 0 ~ 255 사이의 값으로 표현된다. H 값은 색의 종류를 나타내기 때문에 크기는 의미가 없으며 단순한 인덱스(index)를 나타낸다. S 값은 0이면 무채색(gray 색), 255면 가장 선명한(순수한) 색임을 나타낸다. V 값은 작을수록 어둡고 클수록 밝은 색임을 나타낸다. HSV 색상 모델은 그림과 같이 원뿔(conic) 형태, 원기둥(cylindric) 형태가 있다. 

   

4. YCbCr 모델

   RGB 색에서 밝기성분(Y)과 색차정보(Cb, Cr)를 분리하여 표현하는 색상모델이다. 위 5번째 그림을 보면,  Y=128일 때의 CbCr 색상평면이다. 디지털 영상에서 Y, Cb, Cr은 각각 0 ~ 255 사이의 값을 가지며 Y가 커지면 위 그림이 전체적으로 밝아지고 Y가 작아지면 전체적으로 어두워진다. YCbCr 모델은 mpeg에서 사용되는 색상모델로서 인간의 눈이 밝기차에는 민감하지만 색차에는 상대적으로 둔감하다는 점을 이용해서 Y에는 많은 비트수(해상도)를 할당하고 Cb, Cr에는 낮은 비트수를 할당하는 방식으로 비디오를 압축한다. 따라서 비디오 데이터를 처리할 경우에 YCbCr 모델을 사용하면 별도의 색상변환을 하지 않아도 되는 장점을 갖는다. YCbCr 모델은 YUV 모델로도 불린다.

   OpenCV에서는 YCbCr 대신 YCrCb으로 사용한다



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
> 주로 투명한 속성의 PNG파일을 불러올때 사용한다. 포토샵 작업을 하다 보면 투명한 공간이 나오는데, 그러한 부분이 있는 image를 불러올때 사용한다.
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



###### img.read()

이미지를 그대로 다시 반환

`ret, frame = img.read()`

`ret` : 반환이 정상적으로 되면 True, 아니면 False

`frame` : img 그 자체라고 보면 됨.

이건 주로 while문 안에서 video의 순간순간의 frame을 추출할때 사용

```python
while True:
    ret1, frame1 = video1.read() #

    if not ret1:
        break
    
    # do_composit 플래그가 True일 때에만 합성
    ret2, frame2 = video2.read()

    if not ret2:
        break
```

> 두 개의 영상을 가져왔다고 가정





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

![](https://github.com/HibernationNo1/TIL/blob/master/image/c1.jpg?raw=true)

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



왠만한 영상, image의 자료형은 `np.uint8` 이다.



#### 5. Pixel

##### pixel에 접근

image에서 pixel값 가져오기

```python
img = cv2.imread('cat.bmp')

x = 20
y = 10
pix = img[x, y]
print(pix)  # x, y좌표의 픽셀 BGR scale을 알 수 있다.

# imp를 만약 GRAYSCALE로 받았다면 해당 좌표의 garyscale값을 알 수 있다.
```

index 접근 방법을 이용해서 해당 pixel의 값을 바꿀 수도 있다

```python
img[x, y] = (0, 0, 255)
img[x:, y:] =  (0, 255, 255)
```



##### cv2.resize

```python
src = cv2.resize(src, (w, h))
```

src image의 size를 (w, h) 크기로 변경 후 다시 src에 저장



#### 6. image copy

그냥 = 연산을 통해 메모리에 image를 할당하면 같은 주소를 공유하게 된다. 

아예 복사를 하려면 numpy의 copy() 를 사용해야 한다.

```python
img1 = cv2.imread('cat.bmp')

img2 = img1
img3 = img1.copy()  # image 복사

img4 = img1[40:120, 30:150].copy()  	# img1의 부분만 잘라내서 copy
```

