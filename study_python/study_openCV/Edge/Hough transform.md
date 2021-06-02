# Hough transform

edge 모양의 분포를 통해 직선, 원과 같은 더욱 고차원적인 형태 정보를 얻고싶을때 사용하는 algorithm 



## Hough transform line detection

허프 변환 직선 검출 

2 dimension image coordinate에서 직선의 방정식을 parameter 공간으로 변환해서 직선을 찾는 algorithm
$$
y = ax+b \ \ \ \ \rightarrow \ \ \ \ b = -xa + y
$$
![](https://miro.medium.com/max/700/1*Y9ljU_--SdFe7on9W_axrA.png)

#### accumulation array

축적 배열

직선 성분과 관련된 원소 값을 1씩 증가시키는 배열

![](https://lh3.googleusercontent.com/proxy/XI6rmQK0rLoDgYlF2k5FafNtpR5ZQxT-D5CgMFQ5T0GUBj0mBUaAIRP8M14-GX4u-clviw3UvqCH1nqSG0xyL2DMvZbZHsVoqnAs8QzO1A4GRS3FBeUi-vwO2a6rnZC1gdxWI1VI82shAgaukrPM_smF3M1-Ftt5OXSvFrRCIzi_wkW4FhYM85Fu3PFWhAMFOhd37vQDH14PexKINSMDOnL444my1--xcKmKCYihjnz1VV-_a4pdKxq8YoKXHeMJgmfRMXdZWI-P94C12dGlJ7ClUcgXqzSIjcIFhg)

> 오른쪽 배열에서 계속된 축적에 의해 값이 가장 큰 element의 a축 값 = a', b축 값 = b'이라 할 때
> $$
> y = a'x+b' 
> $$
> 로 표현할 수 있다.

단, 위와 같은 직선의 방정식을 사용하면 y죽과 평행한 수직선을 표현하지 못한다. 그렇기 때문에 극좌표계 직선의 방정식을 사용한다.

![](https://github.com/HibernationNo1/TIL/blob/master/image/c14.jpg?raw=true)
$$
x \cos\theta + y\sin\theta = \rho
$$


![](https://github.com/HibernationNo1/TIL/blob/master/image/c15.jpg?raw=true)



##### cv2.HoughLines()

Hough transform에 의한 line detection method

```python
lines = cv2.HoughLines(src, rho, theta, threshold, srn = None, stn = none, 
              min_theta = None, max_theta = None)
```

`src` : input adge image (보통 Canny adge image)

`rho` : accumulation array 에서 rho 값의 간격 (1.0 == 1pixel 간격)

`theta` : accumulation array 에서 theta 값의 간격 (np.pi/180 == 1 degree 간격)

> `rho`, `theta` 값을 작게 주게 되면 accumulation array 가 작아지게 된다.
>
> accumulation array 이 크면 Hough transform을 수행할 때 시간이 오래 걸리지만 정교한 직선을 표현할 수 있다.
>
> 보통 `rho = 1.0`, `theta = np.pi/180 `

`threshold` : accumulation array 에서 line으로 판단할 threshold

`lines` : 직선 parameter(rho, theta) 정보를 담고 있는 ndarray (3 dimension)

> shape = (N, 1, 2), dtype = numpy.float32
>
> N : line의 개수

`srn`, `stn` : multi scale Hough transform에서 rho 해상도, theta 해상도를 나누는 값.

> 기본값 = 0 (이 경우 일반 Hough transform 수행)

`min_theta` ,  `max_theta` : 검출할 선분의 최소, 최대 theta 값 (직선 값의 범위)



##### cv2.HoughLinesP()

probability Hough transform에 의한 line detection method

위의 cv2.HoughLines() 보다 성능이 좋음

```python
lines = cv2.HoughLinesP(src, rho, theta, threshold, minLineLength = None, maxLineGap = None)
```

`minLineLength` : 검출할 선분의 최소 길이

`maxLineGap` : 직선으로 간주할 최대 edge 점 간격

> edge image에서 끊어진 Line을 최대 몇 길이까진 이어주어 line으로 간주할것인지
>
> 0을 줘버리면 한 pixel만 직선이 떨어져 있어도 직선 1개로 안봄
>
> 보통 5 pixel정도 줌

`lines` : 직선의 시작과 끝 좌표(x1, y1, x2, y2) 정보를 담고 있는 ndarray (3 dimension)

> shape = (N, 1, 4), dtype = numpy.int32
>
> N : line의 개수



**Code**

```python
scr = cv2.imread('image.bmp', cv2.IMREAD_GRAYSCALE)

if src is None:
    print('Image load faild!')
    sys.exit()
    
edges = cv2.Canny(src, 50, 150)

lines = cv2.HoughLinesP(edges, rho = 1.0, theta = np.pi / 180, threshold = 160, 
                       minLineLength = 50, maxLineGap = 5)

# 검출한 line을 화면에 보여주기 위한 code

dst = cv2.cvtColor(edges, cv2.COLOR_GRAY2BGR)

if lines is not None:
    for i in range(lines.shape[0]):
        pt1 = (lines[i][0][0], lines[i][0][1])
        pt2 = (lines[i][0][2], lines[i][0][3])
        cv2.line(dst, pt1, pt2, (0, 0, 255), 2, cv2.LINE_AA)
        # 시작 좌표 = pt1, 끝 좌표 = pt2, 빨간색

cv2.imshow('src', src)
cv2.imshow('dst', dst)

cv2.destroyAllWindows()
```





## Hough transform circle detection

허프 변환 원 검출 
$$
(x-a)^2(y-b)^2 = c^2
$$
원의 방정식을 parameter 공간으로 변환하면 3차원 accumulation array를 만들게 되기 때문에 시간이 너무 오래 걸림

속도 향상을 위해 **Hough gradient method**를 사용

- input image와 동일한 2 dimension 평면 공간에서 축적 image를 생성
- edge pixel에서 compute gradient 
- edge direction에 따라 line을 그리면서 값을 누적

원의 중심을 먼저 찾고, 적절한 반지름을 검출한다.

> 단점: 여러개의 동심원을 검출하진 못함(가장 작은 원 하나만 검출)



##### cv2.HoughCircles()

```python
circles = cv2.HoughCircles(image, method, dp, minDist, param1 = None, 
                param2 = None, minRadius = None, maxRadius = None)
```

`image` : input image (edge image 아님)

> method 내부에서 Canny edge 검출을 알아서 진행

`method` : 

> OpenCV 4.2 이하에서는 `cv2.HOUGH_GRADIENT`만 지정 가능

`dp` : input image와 accumulation array의 size ratio

> dp = 1이면 동일 size
>
> 2이면 accumulation array의 가로, 세로 크기가 input image의 절반

`minDist` : 검출된 원 중심점들의 최소 거리

`circles` :  (cx, cy, r) 정보를 담은 ndarray

> shape = (1, N, 3), dtype = np.float32

`param1` : Canny edge 검출기의 높은 treshold

`param2` : accumulation array에서 원 검출을 위한 treshold

`minRadius` , `maxRadius` : 검출할 원의 최소, 최대 반지름 





