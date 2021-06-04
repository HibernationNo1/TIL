# Labeling

**객체 단위 분석 방법 종류**

- object 단위 분석

  object를 분할하여 특징을 분석

  object 위치 및 크기 정보, ROI추출, 모양 분석 등

- Connected Component Labeling (레이블링)

  서로 연결되어 있는 object pixel에 고유한 번호를 지정(label map)

  영역 기반 모양 분석

  label map, bounding box, pixel 개수, 무게중심 coordinate를 반환

- Contour Tracing

  각 object의 외곽선 좌표를 모두 검출

  외각선 기반 모양 분석

  다양한 외곽선 처리 함수에서 활용 가능(근사화, 컨벡스헐 등)

---



**Labeling** : 동일 object에 속한 모든 pixel에 고유한 번호를 주는 작업 (Connected component labeling 이라고도 함)

input image가 주어지면, label map으로 output한다.

> 일반적으로 binary image에서 수행한다.
>
> 외관선 검출보다 빨라서 자주 사용됨

![](https://github.com/HibernationNo1/TIL/blob/master/image/c16.jpg?raw=true)

- pixel의 연결 관계

  1. 4-neighbor connectivity
  2. 8-neighbor connectivity

  ![](https://slidetodoc.com/presentation_image/4bfe2a0d3404ae2f0e6eb83fd760fe07/image-14.jpg)

#### cv2.connectedComponents()

labeling method

```python
retval, labels = cv2.connectedComponents(image, labels = None, connectivity = None, Itype = None)
```

- `image` : 8bit 1 channel image

- `labels` : input image와 같은 size의 label map matirx (ndarray)

- `connectivity` : pixel의 연결 관계. 4 ro 8

  > default = 8

- `Itype` : labels의 type

  > `cv2.CV_32S` 또는 `cv2.CV_16S`
  >
  > default = `cv2.CV_32S`

- `retval` : object의 개수

  > n을 반환하면 [0, n-1]의 label이 존재하며, 0은 backdround를 의미
  >
  > 실제 object 개수는 n-1



#### cv2.onnectedComponentsWithStats()

object 정보를 함께 return하는 labeling method 

> cv2.connectedComponents 보다 많이 사용됨

```python
retval, labels, stats, centroids = cv2.connectedComponentsWithStats(image, labels = None, stats = None, centroids = None, connectivity = None, Itype = None)
```

- `image` : 8bit 1 channel image

- `retval` : object의 개수

  > n을 반환하면 [0, n-1]의 label이 존재하며, 0은 backdround를 의미
  >
  > 실제 object 개수는 n-1

- `labels` : input image와 같은 size의 label map matirx (ndarray)

- `stats` : 각 object의 bounding box와 pixel 개수 정보를 담은 metrix

  > ndarray, shape = (N, 5), dtype = numpy.int32
  >
  > N : object 개수 + 1  (0번째 index는 background에 대한 정보를 담고 있다.)
  >
  > 5 : bounding box info == (x, y, width, height, 면적)
  >
  > x, y는 좌측 상단 꼭지점의 좌표

- `centroids` : 각 object의 무게 중심 위치 정보를 담은 metrix

  > ndarray, shape = (N, 2), dtype = numpy.float64
  >
  > N : object 개수 + 1  (0번째 index는 background에 대한 정보를 담고 있다.)
  >
  > 2 : 무게 중심의 x, y coordinate

- `Itype` : labels의 type

  > `cv2.CV_32S` 또는 `cv2.CV_16S`
  >
  > default = `cv2.CV_32S`



#### ex)

```python
src = cv2.imread("image.png", cv2.IMEAD_GRAYSCALE)

if src is None:
    print('Image load failed!')
    sys.exit()
    
    
_, src_bin = cv2.threshold(src, 0, 255, cv2.THRESH_BINARY or cv2.THRESH_OTSU) 
# src_bin : binary image

dst1 = cv2.morphologyEx(src_bin, cv2.MORPH_OPEN, None)
# opening 수행 (noise 제거)

cnt, labels, stats, centroids = cv2.connectedComponentsWithStats(dst1)

dst2 = cv2.cvtColor(src, cv2.COLOR_GRAY2BGR)
# object에 빨간삭 bounding box를 적용
for i in range(1, cnt):
    x, y, w, h, a = states[i]
    
    if a < 20: # area가 20 pixel보다 작으면
        continue
        
    cv2.rectangle(dst, (x, y, w, h), color = (0, 0, 255), 2)
    # src_bin 에서 뽑은 bounding box의 정보로 dst위에 draw rectangle

cv2.imshow('src', src)
cv2.imshow('dst2', dst2)

cv2.waitKey()
cv2.destroyAllWindows()
```

