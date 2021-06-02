# Edge Detection

**Edge**

- image에서 pixel의 밝기값이 급격하게 변하는 부분
- 일반적으로 background와 object, 또는 object끼리의 경계를 의미한다.



**에지 검출(Edge Detection)**

image에서의 특징 추출 방법 중 하나.

image를 (x, y) 변수의 function으로 간주했을 때, 이 function의 1차 derivative가 크게 나타나는 부분을 검출

![](https://encrypted-tbn0.gstatic.com/images?q=tbn:ANd9GcSyvX8vI4qpe4s_i96t3eMxZRuulTVM-iEeYQ&usqp=CAU)
$$
f(x, y) \rightarrow derivative \\ \rightarrow f_x(x, y)  \rightarrow apply\ image \\
\rightarrow I_x(x, y)
$$
derivative value가 T 값 보다 클 때 해당 부분을 edge라고 여긴다. 

![](https://github.com/HibernationNo1/TIL/blob/master/image/c11.jpg?raw=true)

> 위 그림에서, T(Threshold)값에 의해 검출된 edge는 3개의 pixel이다.



### image의 derivative

image에서의 미분 계산 방법

**image에선 변화량의 최소 단위가 pixel이기 때문에, \Delta x는 1이라고 봐도 무방하다.**

##### Forward difference

전진 차분 (일반적인 function에서의 derivative)


$$
\frac{\part I}{\part x} \cong \frac{I(x + \Delta x) - I(x)}{\Delta x}
$$


##### Backward difference

후진 차분

현재 위치에서 이전 위치의 pixel 값을 빼는 방법
$$
\frac{\part I}{\part x} \cong \frac{ I(x) - I(x - \Delta x)}{\Delta x}
$$


##### Centered difference

중앙 차분

현재 위치에서 (다음 위치의 pixel값) - (이전 위치의 pixel 값)
$$
\frac{\part I}{\part x} \cong \frac{ I(x + \Delta x) - I(x - \Delta x)}{2 * \Delta x}
$$
세 가지 방법 중 Centered difference 방법이 가장 정확하다고 알려져 있다.

![](https://blog.kakaocdn.net/dn/o9PBw/btqLE11N0JO/tatJQV3d5f3QKMHWwGsWp1/img.png)

derivative mask는 x성분과 y성분 두 가지 경우가 있다.

위와 같은 형태의 mask를 선언해 주고 OpenCV의 filter2D 함수를 호출하면 해당 성분의 derivative를 구할 수 있다.



### derivative mask

하지만 (1, 3) shape의 mask를 사용하면 noise에 취약하기 때문에, 일반적으로는  (3, 3) shape의 mask를 사용해서 mean값을 사용하고 있다.

![](https://t1.daumcdn.net/cfile/tistory/126CEB244C8C633227)



#### sobel mask

(3, 3) shape에서 elements의 값을 1:2:1의 비율로 사용하는 mask를 sobel mask라고 한다.

![](https://mblogthumb-phinf.pstatic.net/20150916_85/roboholic84_1442364979771XXm8h_PNG/filters.png?type=w2)

> image에서 미분을 구하는데 가장 많이 사용되는 mask



##### cv2.Sobel()

```python
dst = cv2.Sobel(src, ddepth, dx, dy, dst = None, ksize = None, scale = None, 
         delta =None, borderType = None)
```

`src` : input image (gray scale)

`ddepth` : output image의 data type. `ddepth = -1` 이면 input image와 같은 type

> `ddepth = cv2.CV_32F`

`dx` : x방향 derivative 차수

`dy` : y방향 derivative 차수

`dst` : output image (metrix)

`ksize` : kernel 의 size. 보통 3 

`scale` : 연산 결과에 추가적으로 곱할 값. 보통 1 

`delta` : 연산 결과에 추가적으로 더할 값. 보통 0

`borderType ` : 가장자리 pixel 확장 방식  보통  cv2.BORDER_DEFAULT



> 대부분 `dx = 1, dy = 0, ksize = 3` 또는 `dx = 0, dy = 1, ksize = 3 ` 으로 지정



**ex**

```python
dx = cv2.Sobel(src, -1, 1, 0, 128)
dy = cv2.Sobel(src, -1, 0, 1, 128)
# dx = cv2.Sobel(src, ddepth = -1, dx = 1, dy = 0, delta = 128)
# dy = cv2.Sobel(src, ddepth = -1, dx = 0, dy = 1, delta = 128)

# Implementation
kernel = np.array([
    [-1, 0, 1], 
    [-2, 0, 2],
    [-1, 0, 1]], dtype = np.float32)
dx = cv2.filter2D(src, -1, kernel, delta = 128)
```

> 128을 더해주는 이유 : input image의 밝기가 낮다면, 낮은 값에서 더욱 낮은 값으로 밝기가 변하는 부분은 표현이 되지 않을 수 있기 때문에 전체 image의 밝기를 128만큼 높혀준 것



#### scharr mask

가우시안을 더욱 잘 표현한다고 알려진 derivative mask

![](https://blog.kakaocdn.net/dn/bQKU2i/btqDvzL5qvw/hnEcP6wtEBaOzqLLigV401/img.jpg)



##### cv2.Scharr()

```python
dst = cv2.Scharr(src, ddepth, dx, dy, dst = None, ksize = None, scale = None, 
         delta =None, borderType = None)
```





### gradient 

gradient : function을 x, y축으로 각각 partial derivative하여 vector 형태로 표현한 것
$$
\triangledown f  = \begin{bmatrix}
f_x\\ 
f_y
\end{bmatrix} = \vec{f_x} + \vec{f_y}
$$
 gradient의 크기 (pixel값 변화량의 크기)
$$
|\triangledown f| = \sqrt{{f_x}^2+{f_y}^2}
$$
 gradient의 방향 (pixel값이 가장 급격하게 **증가**하는 방향)
$$
\theta = tan^{-1}(\frac{f_y}{f_x})
$$
![](https://github.com/HibernationNo1/TIL/blob/master/image/c12.jpg?raw=true)



##### cv2.magnitude()

2D vector의 크기 계산 method

```python
mag = cv.magnitude(x, y, magnitude = None)
```

`x` : 2D vector의 x coordinate metrix (실수형)

`y` : 2D vector의 y coordinate metrix (실수형, x와 같은 크기)

`mag` : 2D vector의 scale metrix (x와 같은 크기, 같은 type)

> $$
> magnitude(I) = \sqrt{x(I)^2+y(I)^2}
> $$
>
> 계산 과정은 Euclidean Distance 계산법과 동일



##### cv2.phase()

2D vector의 방향 계산 method

```python
angle = cv2.phase(x, y, angle = None, angleInDegrees = None)
```

`x` : 2D vector의 x coordinate metrix (실수형)

`y` : 2D vector의 y coordinate metrix (실수형, x와 같은 크기)

`angle` : 2D vector의 scale metrix (x와 같은 크기, 같은 type)

> $$
> angle(I) = atan2(y(I), x(I))
> $$
>
> 만약 x(I) = y(I) = 0이면 angle은 0으로 설정됨

`angleInDegrees` : True 이면 degree 단위, False이면 radian 단위



## edge detection

gray scale image를 input으로 edge detection

- Sobel와 magnitude 사용

```python

scr = cv2.imread('image.bmp', cv2.IMREAD_GRAYSCALE)

if src is None:
    print('Image load faild!')
    sys.exit()

# src와 같은 size의 각 방향의 derivative value를 가진 metrix를 create
dx = cv2.Sobel(src, cv2.CV_32F, 1, 0)
dy = cv2.Sobel(src, cv2.CV_32F, 0, 1)

# compute scale of derivative
mag = cv.magnitude(dx, dy)
# mag = np.clip(mag, 0, 255).astype(np.uint8)
# cv2.imshow('mag', mag)

edge = np.zeros(mag.shape[:2], np.uint8) # mag의 2차원 shape만 따서 zeros
# edge 안에서, mag안에서 120보다 큰 값을 가진 elements와 같은 위치의 elements에 255를 할당 (Threshold = 120)
edge[mag>120] = 255
# 즉, 내가 찾고자 하는 edge만 하얀색으로 검출

cv2.imshow('src', src)
cv2.imshow('edge', edge)

cv2.destroyAllWindows()
```

> Threshold 값이 낮을수록 검출되는 egde의 pixel 수가 많아져 egde가 두껍게 검출된다. 이를 위한 해결책으로 케니 edge detection이 고안되었다.



## Canny edge detection

좋은 edge detector의 조건

- 정확한 검출

  egde가 아닌, 점을 edge로 찾거나 또는 edge인데 edge로 인식하지 못하는 확률을 최소화

- 정확한 위치

  실제 edge의 중심을 detection

- 단일 edge

  하나의 edge는 하나의 점으로 표현



Canny edge detection

위 세 가지의 조건을 만족하기 위해 고안된 edge detection

Canny edge detection은 4가지의 단계가 있다. 

1. **Gaussian filtering**

   noise 제거를 목적으로 사용한다. (Optional) 
   $$
   G_{\sigma} = \frac{1}{2 \pi \sigma} \exp(-\frac{x^2 + y^2}{2\sigma^2})
   $$

2. compute gradient

   주로 Sobel mask를 사용, x와 y방향의 derivative를 각각 계산 후 gradient의 magnitude과 phase를 계산

   > 단, phase는 전체 360도 방향에서 4구역으로 단순화

3. **Non-maximum suppression(비최대 억제)**

   - 하나의 edge가 여러 개의 pixel로 표현되는 현상을 없애기 위해 magnitude가 local maximum인 pixel만을 edge로 결정

   - phase에 위치한 두 개의 pixel을 조사해서 local maximum을 조사

   threshold 를 만족하는 pixel 중 derivative가 가장 큰 값을 찾기 위해, 각각의 pixel의 derivative값을 phase 방향 위에 있는 좌, 우 pixel의 derivative값과 비교 

4. **Hysteresis edge tracking(히스테리시스 에지 트래킹)** 

   - 두 개의 threshold값을 사용해서 egde를 세 영역으로 정의
     $$
     T_{Low}, T_{High}
     $$

     - strong edge : High_threshold 보다 높은 edge
     - weak edge : High_threshold 보다 낮은, Low_threshold보다 높은 edge
     - None edge : Low_threshold보다 낮은 edge 

   - edge gradient의 magnitude가 위로 볼록한 형태이고 strong edge보다 높으면 최종 edge로 선정, magnitude가 weak edge면 다시 검사

     - magnitude가 weak edge일 때, 아래로 볼록한 형태이고 최대값이 strong edge보다 높으면 최종 edge로 선정

       ![](https://github.com/HibernationNo1/TIL/blob/master/image/c13.jpg?raw=true)



##### cv2.Canny()

```python
edge = cv2.Canny(src, threshold1, threshold2, edges = None, apertureSize = None, L2grdient = None)
```

`src` : input image

> gray scale 또는 color image를 넣어도 된다. 
>
> color image를 input으로 넣으면 R, B, G 채널 따로따로 검사를 한 후 최대값을 선택해서 output
>
> 가급적이면 gray scale로 변환해서 input하자 

`threshold1` : High_threshold

`threshold2` : Low_threshold

> threshold1 : threshold2 == 1:2 or 1:3

`edge` : edge image

`apertureSize` Sobel 연산을 위한 kernel size. 보통 3

`L2grdient` = `True`이면 L2 norm사용, `False`이면 L1 norm 사용. 보통 False

> - L2 norm
>   $$
>   L2\ norm = \sqrt{(\frac{dI}{dx})^2+(\frac{dI}{dy})^2}
>   $$
>
> - L1 norm
>   $$
>   L1\ norm = |\frac{dI}{dx}|+|\frac{dI}{dy}|
>   $$
>
> 정확한건 L2 norm이지만 빠른건 L1 norm



**implementation**

```python
scr = cv2.imread('image.bmp', cv2.IMREAD_GRAYSCALE)

if src is None:
    print('Image load faild!')
    sys.exit()
    
dst = cv2.Canny(src, 50, 150)

cv2.imshow('src', src)
cv2.imshow('Canny', dst)

cv2.destroyAllWindows()
```

> threshold는 50, 150 정도 주면 적절

