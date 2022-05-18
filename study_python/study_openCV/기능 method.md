# 기능 method



### 시간 측정

#### cv2.TickMeter()

```python
instance = cv2.TickMeter() # 객체 생성
instance.start() # 측정 시작
instance.stop() # 측정 종료
instance.reset() # 측정시간 initial
time = instance.getTimemilli()  # 측정 시간 ms단위로 return

print(f'GFTT: {instance.getTimemilli()}ms')
```





### random

#### cv2.randn()

가우시안 형태의 random number을 generation함

```python
cv2.randn(image, mean, sigma)
```

- `image` : input image

- `mean` : 평균
- `sigma` : 시그마





### math

#### cv2.minMaxLoc()

input image에서 가장 큰(작은) value와 해당 value를 가진 pixel location을 return

```python
min_value, max_value, min_loc, max_loc = cv2.minMaxLoc(image)
```





### 그 외

#### cv2.setNumThreads()

OpenCV의 연산을 parallel하게 진행할때 사용.

input = 0 이면 모든 function이 기존과 같이 sequentially하게 동작하지만, input > 0 인 경우 tread 최적화를 적용한다.

```python
opencv_num_threads = 0 	# or 2
cv2.setNumThreads(opencv_num_threads)
```

