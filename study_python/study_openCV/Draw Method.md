# Draw Method

OpenCV는 선, 도형, 문자열을 출력하는 그리기 함수를 제공한다.

- 그리기 함수는 그리기 알고리즘을 이용하여 영상의 픽셀 값 자체를 변경하기 때문에, 원본 영상이 필요하면 복사본을 만들어서 그리기&출력 을 해야한다.

  (그리기 함수를 사용하면 원본 영상이 훼손된다.)

- gray scale image에는 color로 그리기는 할 수 없다.



#### 1. Draw line 

`cv2.line(img, pt1, pt2, color, thickness = , lineType = , shift = )`

`img` : 그림을 그릴 image

`pt1, pt2` : 직선의 시작 좌표, 끝 좌표

`color`: 직선의 색상.  (B,G,R) 튜플을 할당하거나 정수값을 넣는다.

`thickness`: line의 두께.  default는 1 pixel

`lineType` : line의 종류.  default는 cv2.LINE_8

> `cv2.LINE_4`
>
> `cv2.LINE_8`
>
> `cv2.LINE_AA`

`shift` : 그리기 좌표 갑스이 축소 비율. default는 0 (일반적으로는 잘 사용 안함)



**예시**

```python
cv2.line(img, (50, 50), (200, 50), (0, 0, 255), 5)
# (50, 50)에서 (200, 50) 으로 빨간색, 두께 5의 직선을 그리고 img로 반환한다.
```



#### 2. Draw rectangle 

- `cv2.rectangle(img, pt1, pt2, color, thickness = , lineType = , shift = )`

  `pt1, pt2` : 사각형의 두 꼭지점(좌측 상단, 우측 하단) 좌표

- `cv2.rectangle(img, rec, color, thickness = , lineType = , shift = )`

  `rec` : 사각형의 위치 정보 (x, y, w, h)의 tuple  x, y는 좌측 상단 꼭지점의 좌표

`thickness = -1` 을 주면 내부가 채워진 채로 그려진다.

**예시**

```python
cv2.rectangle(img, (70, 220), (180, 280), (0, 128, 0), -1)
cv2.rectangle(img, (50, 200, 150, 100), (0, 255, 0), 2)
```



#### 3. Draw circle

`cv2.circle(img, center, radius, color, thickness = , lineType = , shift = )`

`center` : 원의 중심 좌표. (x, y) tuple

`radius` : 원의 반지름. 정수값

`thickness = -1` 을 주면 내부가 채워진 채로 그려진다.



#### 4. Draw polyline

다각형을 그리는 함수

`cv2.ploylines(img, [pts], isClose, color, thickness = , lineType = , shift =)`

`pts` : 다각형 외각 점들의 좌표 배열 

예: np.array([10, 10], [50, 50], [10, 50], dtype = np.int32)

`isClose`: 폐곡선 여부. Ture or False

`thickness = -1` 을 주면 내부가 채워진 채로 그려진다.



#### 5. Write text

문자열 출력 함수

`cv2.putText(img, text, org, fontFace, fontScale, color, thickness = , lineType =, bottomLeftOrigin = )`

`text` : 출력할 문자열

`org` : text의 위치 좌측 하단 좌표

`fontFace` : font 종류  

>  `cv2.FONT_HERSHEY_SIMPLEX`
>
> `cv2.FONT_HERSHEY_PLAIN`
>
> `cv2.FONT_HERSHEY_DUPLEX`
>
> `cv2.FONT_HERSHEY_COMPLEX` 등이 있음 

`fontScale` : font size

`bottomLeftOrigin` : Ture or False. 보통 사용하는 default는 Ture.

문자열을 출력할 때는 `lineType = cv2.LINE_AA` 을 주는게 좋다.