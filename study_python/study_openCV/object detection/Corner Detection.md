# Corner Detection

object의 코너 검출

평탄한 영역이나 edge 영역은 고유한 위치를 찾기 어려우나 corner는 변별력이 높은 편이며, 영상의 이동, 회전 변환에 강인함



- 다양한 코너 검출 방법

  ![](https://github.com/HibernationNo1/TIL/blob/master/image/c20.jpg?raw=true)

  > image의 크기 변환에 취약함



#### cv2.cornerHarris()

해리스 corner 응답 method

```python
dst = cv2.cornerHarris(src, blockSize, ksize, k, dst = None, borderType = None)
```

- `src` : input image

- `blackSize` : corner 응답 method에서 고려할 이웃 pixel size

  > 보통 2~5

- `ksize` : (derivate를 위한) Sobel operator를 위한 kernel size

  > 보통 3

- `k` : 해리스 코너 검출 상수

  > 보통 0.04 ~ 0.06

- `dst` : 해리스 코서 응답 계수

  > ndarray, numpy.float32

- `borderType` : 가장자리 픽셀 확장 방식

  > default : `cv2.BORDER_DEFAULT`



#### cv2.goodFeatureToTrack()

corner detection에는 `cv2.cornerHarris()` 보다 더욱 뛰어난 성능을 가짐

```python
corners = cv2.goodFeatureToTrack(image, maxCorners, qualityLevel, minDistance, corners = None, mask = None, blockSize = None, useGarrisDetector = None, k = None)
```

- `corners` : detection된 corner의 점 좌표

  > ndarray, shzpe = (N, 1, 2), dtype = numpy.float32
  >
  > N : corner point의 개수

- `image` : 단일 chennal image

- `maxCorners` : 최대 코너 개수

  > `maxCorners <=0` 이면 무제한

- `qualityLevel` : 코너점 결정을 위한 값

  > 보통 0.01 ~ 0.1

- `minDistance` : 코너점 사이의 최소 거리

- `mask` : mask image

- `blackSize` : corner detection을 위한 block size

  > default = 3

- `useGarrisDetector` : 해리스 코너 방법 사용 여부

  > default = False

- `k` : 해리스 코너 검출 시 사용할 상수 k값

  > 보통 0.04 ~ 0.06



#### FAST corner detection

성능이 뛰어나고 빠른 코너검출 방법. (noise에 민감함)

class 형태로 구현되어 있다.

##### cv2.FastFeatureDetector_create()

```python
retval = cv2.FastFeatureDetector_create(threshold = None, nonmaxSuppression = None, type = None)
```

- `retval` : instance

- `threshold` : 중심 pixel 값과 주변 pixel 값의 차이 threshold

  > default = 10
  >
  > 추천값은 30~60

- `nonmaxSuppression` : 주변 pixel에서 바로 corner가 검출될 가능성에 대해서, True이면 corner less가 높은 놈을 찾아서 하나만 선택

  > default = True

- `type` : corner detection 방법

  > default = `cv2.FAST_FEATURE_DETECTOR_TYPE_9_16`
  >
  > 주변 16개 pixel 중에서 9개 이상 연속적으로 더 밝으면 corner로 검출하는 method



##### detect()

```python
keypoints = retval.detect(image)
```

- `retval` : cv2.FastFeatureDetector_create()의 instance

- `image` : gray scale input image

- `keypoints` : 검출된 corner point information.

  > cv2.KeyPoint 객체를 담은 list
  >
  > `cv2.KeyPoint` 의 `pt` member method를 이용해서 corner의 coordinate 추출

```python
for kp in ketpoints:
    pt = (int(kp.pt[0]), int(kp.pt[1]))
	# x좌표, y좌표
```





**예제**

```python
src = cv2.imread('image.jpg', cv2.IMREAD_GRAYSCALE)

if src is None:
    print('Image load failed!')
    exe.exit()

tm = cv2.TickMeter() # 시간 측정 함수

# GFTT
tm.start()

corners = cv2.goodFeaturesToTrack(src, 400, 0.01, 10)

tm.stop()
print(f'GFTT: {tm.getTimemilli()}ms') # 코너 검출 시간 측정

dst1 = cv2.cvtColor(src, cv2.COLOR_GRAY2BGR)

if corners is not None: # corner에 원을 그려서 표시
    for i in range(corners.shape[0]):
        pt = (int(corners[i, 0, 0]), int(corners[i, 0, 1]))
        cv2.circle(dst1, pt, 5, (0, 0, 255), 2)

tm.reset()

# FAST
fast = cv2.FastFeatureDetector_create(60)
tm.start()

keypoints = fast.detect(src)

tm.stop()
print(f'FAST: {tm.getTimemilli()}ms') # 코너 검출 시간 측정

dst2 = cv2.cvtColor(src, cv2.COLOR_GRAY2BGR)

for kp in ketpoints:
    pt = (int(kp.pt[0]), int(kp.pt[1]))
    cv2.circle(dst2, pt, 5, (0, 0, 255), 2)

cv2.imshow('src', src)
cv2.imshow('dst1', dst1)
cv2.imshow('dst2', dst2)

cv2.waitKey()
cv2.destroyAllWindows()
```

> 성능은 GFTT와 FAST가 비슷하지만
>
> 계산 시간은 FAST가 훨씬 빠르다.

