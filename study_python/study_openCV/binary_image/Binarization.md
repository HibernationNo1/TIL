# 이진 영상 처리

**영상의 이진화(binarization)**

 image의 pixel값을 0(False) 또는 255(True)로 만들어 분리하는 영상

> background vs object
>
> 관심 영역 vs 비관심 영역
>
> mask image가 이진 영상의 한 종류



- binarization of gray scale image
  $$
  g(x, y) = \left\{\begin{matrix}
  0\ \ \ \ if\ \ f(x, y) < T
   & \\ 
  255\ \ \ \ if\ \ f(x, y) > T
  \end{matrix}\right.
  $$

  > T : threshold



## 전역 binarization



### THRESH_BINARY

#### cv2.threshold()

완전히 binarization을 하는 method는 아니지만, threshold를 이용해서 할 수 있는 연산을 다 지원하는 함수

보통 `cv2.THRESH_BINARY` 을 수행하는데 사용

```python
retval, dst = cv2.threshold(src, thresh, maxval, type)
```

`retval` : 사용된 threshold

`dst` : output image

> input image 와 동일 size, type, 같은 channel 수

`src` : input image

`thresh` : 사용자 지정 threshold

`maxval` : cv2.THRESH_BINARY 또는 cv2.THRESH_BINARY_INV 방법 사용 시 최댓값

> 보통 255로 지정

`type` : 'cv2.THRESH' 로 시작하는 flag

> 보통 cv2.THRESH_BINARY 또는 cv2.THRESH_BINARY_INV 방법 사용
>
> -  `cv2.THRESH_BINARY` : threshold보다 낮은 pixel값은 0으로, 큰 부분은 255
> -  `cv2.THRESH_BINARY_INV` : threshold보다 낮은 pixel값은 255으로, 큰 부분은 0 (`cv2.THRESH_BINARY` 의 인버스)
>
> ![](https://programmer.ink/images/think/576d0cf8d74bfcc5549da49a600b62b5.jpg)



```python
src = cv2.imread("image.png", cv2.IMEAD_GRAYSCALE)

if src is None:
    print('Image load failed!')
    sys.exit()
    
_, dst1 = cv2.threshold(src, 210, 255, cv2.THRESH_BINARY)
_, dst2 = cv2.threshold(src, 100, 255, cv2.THRESH_BINARY)

cv2.imshow('src', src)
cv2.imshow('dst1', dst1)
cv2.imshow('dst2', dst2)

cv2.waitKey()
cv2.destroyAllWindows()
```



### THRESH_OTSU

Otsu binarization 방법

input image가 background와 object 두 개로 구성되어 있을 때 (즉, Bimodal histogram), arbitrary threshold T에 의해 나눠지는 두 pixel distribution group의 분산이 최소가 되는 T를 선택 

> 일종의 optimization algorithm이다.

![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcRZHVhhdWQ5tw2hRhYRxnQR82-fY2U-h34sSg&usqp=CAU)



**Within-class variance**

분리하고자 하는 class 각각의 variance을 계산 해서 합한 값.
$$
\sigma^2_{Within}(t) = w_1(t)\sigma^2_1(t) +  w_2(t)\sigma^2_2(t)
$$

$$
n번\ 클래스\ 가중치 \ \ \ : \ \  w_n(t) = \sum^t_{i=0} p(i)\\
n번\ 클래스\ 분산 \ \ \ : \ \  \sigma_n\\
픽셀\ 값\ i가\ 나타날\ 확률 \ \ \ : \ \  p(i)
$$

**Otsu threshold**

Within-class variance 를 최소화 하는 T값
$$
T_{Otsu} = \underset{t\in\{0, 1, ..., L-1 \}}{argmin}\ \sigma^2_{Within}(t)
$$
단점: 위 계산을 direct로 진행하면 Within-class variance 의 계산시간 소요가 크다

이런 소요를 줄이기 위해 Between-calss variance 를 고안해냈다.



**Between-calss variance**

전체 variance에서  Within-class variance을 뺀 값
$$
\sigma^2_{Bitween}(t) = \sigma^2 - \sigma^2_{Within}(t) \\
$$


Within-class variance 최소화 하는 T값을 찾아야 하는데, 이 T값은 Between-calss variance을 최대로 만드는 T값이다. 이러한 T값을 찾기 위해 위 식을 다르게 표현해 보면 아래와 같다.
$$
\sigma^2_{Bitween}(t) = w_i(t)(1-w_1(t))(\mu_1(t)- \mu_2(t))^2 \\
\mu_n(t) \ \ \ : \ \ \ n번\ class의\ histogram\  평균값
$$
위 식에서, 모든 t값에 대해 평균을 구하며 Between-calss variance를 계산하여 최적의 T를 구하는 선택은 느리지만, Recursion을 이용한 계산은 효율적이며 빠르다.

- Recursion을 이용한 계산(점화식)
  $$
  w_1(0) = p(0),\ \ \  \mu_1(0) = 0\\
  w_1(t) = w_1(t-1) + p(t)\\
  \mu_1(t) = \frac{w_1(t-1)\mu_1(t-1) + t*p(t)}{w_1(t)} \ \ \ \ \ \ \ \mu_2(t) = \frac{\mu -w_1(t)\mu_1(t) }{1-w_1(t)}
  $$
  t = 0 일때(초기값) 계산 후, t 가 1보타 크거나 같을 땐 이전에 계산한 값 사용



즉, **Otsu threshold** 는 **Within-class variance** 최소화 하는 T값이며, 이 T값은 **Between-calss variance**를 최대화 하는 T값이고 이를 빠르게 계산하기 위해 Recursion을 이용한 점화식을 사용한다.

![](https://upload.wikimedia.org/wikipedia/commons/thumb/3/34/Otsu%27s_Method_Visualization.gif/220px-Otsu%27s_Method_Visualization.gif)

> 위 영상은 input image의 histogram에서 t값을 0부터 증가시키며 Between-calss variance값을 보여주고 있다.  
>
> Between-calss variance가 가장 큰 T값이 바로 Otsu threshold가 되는 것이다.



**Otsu 방법을 이용한 자동 binarization**

#### cv2.threshold()

```python
retval, dst = cv2.threshold(src, thresh, maxval, type)
```

-  `thresh`는 0으로, `maxval`은 255로 고정

- `type` 

  -  image의 histogram이 bimodal이면  `cv2.THTESH_BINARY | cv2.THRESH_OTSU` 할당 (or 연산)

    ```python
    th, dst = cv2.threshold(src, 0, 255, cv2.THTESH_BINARY | cv2.THRESH_OTSU)
    print(th)  # print computed threshold
    ```

  - 아니면 `cv2.THRESH_OTSU`

    ```python
    th, dst = cv2.threshold(src, 0, 255, cv2.THRESH_OTSU)
    print(th)  # print computed threshold
    ```

    

  

  

## 지역 binarization

**지역 이진화** : 균일하지 않은 조명 환경에서 촬영된 image의 binarization

how? : image를 grid 형태로 나눈 후, 각각의 cell에 Binarization을 적용한 후 다시 이어 붙인다.

> 단점: cell안에 background 또는 object만 존재한다면 해당 cell의 pixel 값이 전부 0 또는 255로 이진화되는 오동작이 있을 수 있다.



#### grid cell 적용

```python
src = cv2.imread("image.png", cv2.IMEAD_GRAYSCALE)

if src is None:
    print('Image load failed!')
    sys.exit()

# 전역 이진화
_, dts1 = cv2.threshold(src, 0, 255, cv2.THRESH_BINARY or cv2.THRESH_OTSU)

# 지역 이진화
dts2 = np.zeros(src.shape, np.uint8) # grid cell로 나누지 않은 빈 그릇

w_grid = 4
h_grid = 4

bw = src.shape[1] // h_grid
bh = src.shape[0] // w_grid

for y in range(h_grid):
    for x in range(w_grid):
        src_ = src[y*bh:(y+1)*bh, x*bw:(x+1)*bw] 
        dst_ = dst2[y*bh:(y+1)*bh, x*bw:(x+1)*bw] # 그릇도 grid cell로 나누어야 한다. (입력 영상과 출력 영상은 크기가 같아야 하기 때문)
        cv2.threshold(src_, 0, 255, cv2.THRESH_BINARY or cv2.THRESH_OTSU, dst_ )
        # _, dts_ = cv2.threshold 이런 형태로 할당하면 dst_는 for문 안의 지역변수이기 때문에 전역에선 사라진다. 
        # dst_를 cv2.threshold(dst_) 형태로 줘야 input으로 받고, output으로 자동 할당되며 전역에서 사용할 수 있는 변수가 된다. 
        
cv2.imshow('src', src)
cv2.imshow('dst1', dst1) # 전역 이진화
cv2.imshow('dst_', dst_) # 지역 이진화

cv2.waitKey()
cv2.destroyAllWindows()
```



#### 적응형 이진화

#### cv2.adaptiveThreshold()

T = (image의 x, y 좌표에서 계산된 평균 값) - C  

위 방법으로 계산된 T를 사용해서 grid cell로 나눈 각 cell마다 binarization을 적용

```python
cv2.adaptiveThreshold(src, maxValue, adaptiveMethod, thresholdType, 
                     blockSize, C, dst = None)
```

`src` : input image(gray scale)

`maxValue` : threshold의 max값 

> 보통 255

`adaptiveMethod` : 블록 평균 계산 방법 지정

> binarization을 하기 전에 src에 블러 효과를 적용할하는데, 이때 사용할 계산법 지정
>
> `cv2.ADAPTIVE_THRESH_MEAN_C` : 산술 평균 계산
>
> `cv2.ADAPTIVE_THRESH_GAUSSIAN_C` : 가우시안 가중치 평균 계산

`thresholdType` : 

> `cv2.THRESH_BINARY` 또는 `cv2.THRESH_BINARY_INV`

`blockSize` : cell 갯수 (3이상의 홀수)

> 크게 줘야한다. 51 줄때도 있음

`C` : `adaptiveMethod` 으로 계산된 값에서 뺄 값

> (x, y) pixel의 threshold로 T(x, y) = 평균값 - C



```python
src = cv2.imread("image.png", cv2.IMEAD_GRAYSCALE)

if src is None:
    print('Image load failed!')
    sys.exit()
    
C = 5    
def on_trackbar(pos) : 
    bsize = pos
    if bsize % 2 == 0:  # 짝수면 홀수로 만들어준다.
        bsize =bsize -1
    if bsize < 3 :
        bsize = 3
	
    dst = cv2.adaptiveThreshold(src, 255, cv2.ADAPTIVE_THRESH_GAUSSIAN_C,
                               CV2.THRESH_BINARY, bsize, C)
    cv2.imshow('dst', dst)
    
    
cv2.imshow('src', src)
cv2.namedWindow('dst')
cv2.crateTrackbar('block size', 'dst', 0, 200, on_trackbar)
cv2.setTrackbarPos('block size', 'dst', 11)

cv2.waitKey()
cv2.destroyAllWindows()
```

