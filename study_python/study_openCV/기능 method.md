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

