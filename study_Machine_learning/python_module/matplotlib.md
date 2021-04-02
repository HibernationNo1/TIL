# matplotlib

**matplotlib.pyplot**모듈은 MATLAB과 비슷하게 명령어 스타일로 동작하는 함수의 모음으로, 데이터를 시각화(그래프)할 수 있는 기능을 지원해주는 라이브러리이다. (pyplot 모듈의 각각의 함수를 사용해서 그래프를 만들고 변화를 줄 수 있다.)

matplotlib 3.3이 Windows에서 제대로 작동하지 않을 수 있기 때문에 `pip install matplotlib==3.2`를 통해 설치하자.

```python
import matplotlib as mpl
import matplotlib.pyplot as plt
```

```python
mpl.__version__
```



- 시작 전 속성 설정

  ```python
  plt.style.use('seaborn-notebook')
  ```

  > seaborn style을 지정한다.

---



### 0. 기초

plot은 그림(figure)과 축(axes)으로 구성되어 있다.

- `plt.figure()` : axes와 그래픽, 텍스트, 레이블을 표시하는 모든 객체를 포함하는 컨테이너
- `plt.axse()`: 눈금과 레이블이 있는 테두리 박스로 시각화를 형성하는 플롯 요소를 포함
- `plt.show`: plot을 팝업 창으로 띄워준다.

```python
fig = plt.figure()
ax = plt.axes()
plt.show()
```

> 빈 그래프창이 나오는걸 볼 수 있다.

- `plt.waitforbuttonpress()` : 아무 버튼이 눌리면 이미지 팝업창 닫음


---



### 1. Graph

#### 1. Graph Type

- `plt.plot()` : 전달인자로 받아온 구성 요소를 선 모양의 그래프로 표현한다.

  ```python
  plt.plot([0, 1, 0.4])
  plt.plot([0, 1, 0.4]*5)  # 위의 그래프를 창 하나 안에 5번 그린다.
  plt.plot(np.random.randn(50))
  ```

  x, y에 대한 그래프도 그릴 수 있다.

  ```python
  x = np.arange(0, 10, 0.01)
  plt.plot(x, np.sin(x))
  plt.plot(x, np.cos(x))
  ```

- `plt.bar(xx, yy)` : 전달인자로 받아온 구성 요소를 막대 모양의 그래프로 표현한다.

  - `plt.barh(xx, yy)`: 막대 그래프를 수평 방향으로 표현한다.



#### 2. plot axis

x, y 축을 설정할 수 있다.

- `plt.xlim(min, max)` x축 범위 설정
- `plt.tlim(min, max)` y축 범위 설정

- `plt.axis([xmin, xmax, ymin, ymax])` x, y축 한 번에 설정
  - `plt.axis('tight')`  x, y축을 알아서 딱 맞게 지정
  - `plt.axis('equal')`  x, y축을 보다 넓은 범위로 지정

```python
plt.plot(np.random.randn(50))
plt.xlim(-1, 50)
plt.ylim(-5, 5)
plt.axis([0, 40, -10, 10])
plt.axis('tight')
```



#### 3. Plot Label

- `plt.title("title이름")` 그래프의 이름
- `plt.xlabel("")`  그래프의 x축 이름
- `plt.ylabel("")`  그래프의 y축 이름

```python
plt.plot(np.random.randn(50))
plt.title("tmp")
plt.xlabel("x!")
plt.ylabel("y!")
```

- `label = "" `  각 범례에 이름을 붙여준다.
- `plt.legend()` 각 범례의 이름을 그래프 위에 표현해준다. (이거 없으면 label 속성 설정해도 안뜸) 

```python
plt.plot(np.random.randn(50), label = "one!")
plt.plot(np.random.randn(50), label = "two!")
plt.legend()
```







- `plt.xticks(rotation=m)` : x축의 각 data 이름을 90도 회전
- `plt.yticks(rotation=m)` : x축의 각 data 이름을 m도 만큼 회전

####  

---



### 2. Line

#### 2. Line Style

plot의 속성값으로 linestyle을 지정할 수 있다. 

`linestyle = `

- `'solid'` 실선  	`'-'`
- `'dashed'` 막대선   `'--'`
- `'dashdot'` 실점선  `'-.'`
- `'dotted'` 점선  `':'`

```python
plt.plot(np.random.randn(50).cumsum(), linestyle = 'solid')
plt.plot(np.random.randn(50).cumsum(), linestyle = 'dashed')
plt.plot(np.random.randn(50).cumsum(), linestyle = 'dashdot')
plt.plot(np.random.randn(50).cumsum(), linestyle = 'dotted')
```



#### 3. Line Color 

plot의 속성값으로 라인의 색상을 지정할 수 있다.

`color = `

- `'r'` 빨강
- `'g'` 초록
- `'b'` 파랑
- `'#색상코드'` 
- `(R수치, G수치, B수치)`

- `'색상이름'`

```python
plt.plot(np.random.randn(50).cumsum(), color = 'r')
plt.plot(np.random.randn(50).cumsum(), color = 'g')
plt.plot(np.random.randn(50).cumsum(), color = 'b')
plt.plot(np.random.randn(50).cumsum(), color = '#1243FF')
plt.plot(np.random.randn(50).cumsum(), color = (0.2, 0.4, 0.6))
plt.plot(np.random.randn(50).cumsum(), color = 'darkblue')
```

![](https://mblogthumb-phinf.pstatic.net/MjAxNzA2MDJfMTg5/MDAxNDk2Mzk0OTQxNjYy.scwSCt72W3lW-32VrUH6Vi6tXBzSEPH86d5NfCwPe6Ug.MEWCQsPL2xBQQU3675ELH1y1xB4unFG0Mes-CBvkJSsg.PNG.radii26omg/named_colors.png?type=w2)

**color와 line 한 번에 지정**

옵션으로 `color linestyle` 을 바로 지정해버린다. 

```python
plt.plot(np.random.randn(50).cumsum(), 'r-')
plt.plot(np.random.randn(50).cumsum(), 'g-.')
plt.plot(np.random.randn(50).cumsum(), 'b:')
```





### 3. Font