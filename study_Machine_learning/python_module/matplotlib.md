# matplotlib

데이터를 시각화(그래프)할 수 있는 기능을 지원해주는 라이브러리

```python
import matplotlib as plt
```

- `plt.show()` : 설정된 그래프를 보여주는 함수

- `fig = plt.figure()` : fig라는 변수에 figure을 할당한다.

  > figure는 하나의 그래프로, figure()은 빈 그래프를 의미한다.
  >
  > fig = plt.figure(figsize  = (9, 9)) : 그래프 창의 크기를 가로, 세로 9인치를 설정

- `ax = plt.gca()` : ax라는 변수에 

  > gca는 '축'을 의미한다. 그래프는 없지만 축 만을 변수 ax에 할당한 것이다. 
  >
  > 위의 figure함수 호출 후  `ax = fig.gca()` 을 사용하면 축이 있는 그래프 1개가 만들어 진다.
  >
  > 이  ax를 다른 plot에서 매개변수 ax에 할당하면(ax = ax) 해당 plot은 ax라는 변수에 할당된 그래프 위에 그려지게 되는 것이다. 여러 plot에 ax를 매개변수로 할당하면 하나의 그래프에 여러plot이 그려지게 되는 것이다.



- `plt.plot(xx, yy)` : x축엔 xx, y축엔 yy로 표현된 실선 그래프
- `plt.bar(xx, yy)` : x축엔 xx, y축엔 yy로 표현된 막대 그래프
  - `plt.barh(xx, yy)`: 막대 그래프를 수평 방향으로 표현한다.





- `plt.xticks(rotation=90)` : x축의 각 데이터 이름을 90도 회전
- `plt.yticks(rotation=m)` : x축의 각 데이터 이름을 m도 만큼 회전

