# Template matching

**template image** : 찾을 대상이 되는 작은 영상

**Template matching** : input image에서 template image와 일치하는 부분을 찾는 기법

![](https://www.researchgate.net/profile/Yoshiaki-Ohyama/publication/270964026/figure/fig3/AS:669228717854727@1536567968353/Template-matching-algorithm-in-MTT-software.jpg)

template image를 kernel로서 사용하며 window slicing을 통해 유사도(or 비유사)도 값을 metrix 형태로 저장 후 해당 image에서 max값(or min값)을 찾은 후 initial image의 해당 좌표에 making을 하면 matching이 완료된다.

> initial image에 padding을 적용하지 않기 때문에 유사도 image는 좀 작은 size를 가지고 있다.



#### cv2.matchTemplate()

```python
result = cv2.matchTemplate(image, templ, method, result = None, mask = None)
```

- `result` :  유사도 또는 비유사도 map image

  > ndarray, dtype = numpy.float32
  >
  > initial image의 width = W이고, templ의 width 가 w일 때
  >
  > result의 width = (W - w + 1)
  >
  > H도 마찬가지

- `image` : input image. 8bit or 32bit

- `templ` :  template image

  > input image보다 같거다 낮은 size, 같은 type

- `method` : 비교 방법

  > 유사도를 지정할건지 비유사도를 지정할건지 결정하는 flag 할당
  >
  > ![](https://i2.wp.com/theailearner.com/wp-content/uploads/2020/12/comp_methods1.png?resize=625%2C577&ssl=1)
  >
  > `cv2.TM_CCOEFF_NORMED` 가 가장 많이 쓰이고 가장 성능이 좋다





**예시**

```python
src = cv2.imread('image.bmp', cv2.IMREAD_GRAYCALE)
templ = cv2.imread('image_templ.bmp', cv2.IMREAD_GRAYCALE)

if src is None or templ is None:
    print('Image load failed!')
    sys.exit()
    
# input image의 밝기 50증가, 가우시안 잡음(sigma = 10) 추가  // 약간의 변형을 줌
noise = np.zeros(src.shape, np.int32)
cv2.randn(noise, 50, 10)  
src = cv2.add(src, noise, dtype = cv2.CV_8UC3) # noise 추가

# template matching
res = cv2.matchTemplate(src, templ, cv2.TM_CCOEFF_NORMED)
# res : 유사도를 의미하는 -1 ~ 1 실수형 metrix (template map)

res_norm = cv2.normalize(res, None, 0, 255, cv2.NORM_MINMAX, cv2.CV_8U)
# 따로 template map을 시각화 하기 위해 res의 각 pixel 값을 0~255로 scaling

# res에서 최대값을 찾기 위해
_, maxv, _, maxloc = cv2.minMaxLoc(res)
print(maxv)
print(maxloc)
# 실제 찾고자 하는 object가 없는 iamge에서도 maxv는 존재하기 때문에, maxv는 특정 값 이상일때만 rectangle를 그리는 함수를 호출하도록 코딩하자.

# matching 결과를 빨간색 사각형으로 표시
th, tw = templ.shape[:2]
dst = cv2.cvtColor(src, cv2.COLOR_GRAY2BGR)
cv2.rectangle(dst, maxloc, (maxloc[0] + tw, maxloc[1] + th), (0, 0, 255), 2)


# 결과 출력
cv2.imshow('src', src)
cv2.imshow('res_norm', res_norm)
cv2.imshow('dst', dst)

cv2.waitKey()
cv2.destroyAllWindows()
```





##### cv2.randn()

가우시안 형태의 random number을 generation함

```python
cv2.randn(image, mean, sigma)
```

- `image` : input image

- `mean` : 평균
- `sigma` : 시그마



##### cv2.minMaxLoc()

input image에서 가장 큰(작은) value와 해당 value를 가진 pixel location을 return

```python
min_value, max_value, min_loc, max_loc = cv2.minMaxLoc(image)
```





