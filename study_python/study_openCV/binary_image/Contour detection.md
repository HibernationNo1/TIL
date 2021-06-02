# contour detection

외곽선 검출 : object의 외곽선 좌표를 모두 추출하는 작업

바깥쪽, 안쪽(홀) 외곽선의 좌표 추출(외곽선의 계층 structure도 expression 가능)



- contour object 하나의 expression 방법

  numpy.ndarray

  shape = (k, 1, 2)  

  > k : contour coordinate의 개수
  >
  > 2: x, y 좌표

  dtype = numpy.int32

- 여러 ontour object의 expression 방법

  하나의 contour object 를 element로 갖는 list

  > len(list) =  전체 contour 개수



#### cv2.findContours()

외곽선 검출 method

```python
contours, hierarchy = v2.findContours(image, mode, method, contours = None, hierarchy = None, 
                offset = None)
```

- `image` : input image

  > non-zero pixel을 object로 간주

- `mode` : contour detection mode

  > - 계층 정보를 담고 있지 않은 mode
  >
  >   `cv2.RETR_EXTERNAL`
  >
  >   `cv2.RETR_LIST`
  >
  > - 계층 정보를 담고 있는 mode
  >
  >   `cv2.RETR_CCOMP`
  >
  >   `cv2.RETR_TREE`
  >
  > ![](https://github.com/HibernationNo1/TIL/blob/master/image/c17.jpg?raw=true)

- `method` : contour 근사화 방법

  > contour의 좌표를 간단하게 저장하기 위해 사용(memory save를 위해 사용)
  >
  > `cv2.CHAIN_APPROX_NONE` 을 입력해도 크게 무리 없다.
  >
  > ![](https://github.com/HibernationNo1/TIL/blob/master/image/c18.jpg?raw=true)

- `contours` : detection된 contour의 coordinate

  > ndarray로 구성된 contour object 들의 list
  >
  > len(list) : 전체 contour의 개수
  >
  > contours[i].shape = (k, 1, 2). 	contours[i].dtype = numpt.int32

- `hierarchy` : contour 계층 정보를 numpy.ndarray로 담고 있다.

  > shape = (1, N, 4)  	N : 외각선의 개수
  >
  > dtype = numpy.int8
  >
  > hierarchy[0, i, 0] ~ hierarchy[0, i, 3] 이 순서대로 next, prev, child, parent 외곽선 index를 가리킴 (해당 contour이 없으면 -1)

- `offset` : coordinate value 이동 offset

  > default = (0, 0)



#### cv2.drawContours()

외곽선을 그리는 method

```python
image = cv2.drawContours(image, contours, contourIdx, color,
                        tickness = None, lineType = None, 
                        hierarchy = None, maxLevel = None, 
                        offset = None)
```

- `image` : input, output image

- `contours` : `cv2.findContours()` 로 구한 contour coordinate 정보

- `contourIdx` : 그리고자 하는 특정 외곽선의 index. -1을 지정하면 모든 contour을 그림

- `color`

- `tickness` : 두께

- `lineType` : LINE_4, LINE_8, LINE_AA 중 하나 지정

- `hierarchy` :  contour의 계층 정보

  > `cv2.findContours()` 로 구한 `hierarchy` 값을 그대로 입력

- `maxLevel` : draw를 수행할 최대 contour 레벨



#### ex1)

while loop

```python
src = cv2.imread("image.png", cv2.IMEAD_GRAYSCALE)

if src is None:
    print('Image load failed!')
    sys.exit()

contours, hier = cv2.findContours(src, cv2.RETR_TREE, cv2.CHAIN_APPROX_NONE)
# 모든 계층 정보를 표현하는 cv2.RETR_TREE 를 사용

dst = cv2.cvtColor(src, cv2.COLOR_GRAY2BGR)

idx = 0
while idx >= 0:
    c = (random.radint(0, 255), random.randint(0, 255), random.randint(0, 255)) # 색을 random하게 줌
    cv2.drawContours(dst, contours, idx, c, 2, cv2.LINE_8, hier)
    # hier을 주지 않으면 idx로 접근하지 않은 외곽선은 그리지 않음
    # hier을 주면 idx가 건너뛰어도 하위 계층의 외곽선은 상위 계층 외곽선의 그림 옵션을 그대로 따라서 그려짐
    idx = hier[0, idx, 0]
    # hier의 세 번째 index가 0이면 next를 의미함. 현 idx의 외곽선 기준, 같은 계층의 다음 외각선 index를 idx에 할당

cv2.imshow('src', src)
cv2.imshow('dst', dst)

cv2.waitKey()
cv2.destroyAllWindows()
```

> ![](https://github.com/HibernationNo1/TIL/blob/master/image/c17.jpg?raw=true)
>
> 0번과 그 하위 계증 외곽선이 같은 색으로 그림이 그려지고
>
> 4번과 그 하위 계증 외곽선이 같은 색으로 그림이 그려진다.





#### ex2)

for loop

```python
src = cv2.imread("image.png", cv2.IMEAD_GRAYSCALE)

if src is None:
    print('Image load failed!')
    sys.exit()
    
_, src_bin = cv2.threshold(src, 0, 255, cv2.THRESH_OTSU)

contours, _ = cv2.findContours(src, cv2.RETR_LIST, cv2.CHAIN_APPROX_NONE)

h, w = src.shape[:2]
dst = np.zeros((h, w, 3), np.uint8)  # 3개의 channel이 있는 그릇 만들기

for i in range(len(contours)):
    c = (random.radint(0, 255), random.randint(0, 255), random.randint(0, 255)) # 색을 random하게 줌
    
    cv2.drawContours(dst, contours, i, c, 1, cv2.LINE_AA)
    # hier을 주지 않으면 idx로 접근하지 않은 외곽선은 그리지 않음

cv2.imshow('src', src)
cv2.imshow('dst', dst)

cv2.waitKey()
cv2.destroyAllWindows()
```

