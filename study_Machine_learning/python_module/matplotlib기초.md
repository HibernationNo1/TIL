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



## 1. 기초

plot은 그림(figure)과 축(axes)으로 구성되어 있다.

- `plt.figure()` : axes와 그래픽, 텍스트, 레이블을 표시하는 모든 객체를 포함하는 컨테이너

- `plt.axse()`: 눈금과 레이블이 있는 테두리 박스로 시각화를 형성하는 플롯 요소를 포함

- `plt.plot()` : 전달인자로 받아온 data를 선 모양의 그래프로 표현한다.

  ```python
  plt.plot([0, 1, 0.4])
  plt.plot([0, 1, 0.4]*5)  # 위의 그림을 plot 하나 안에 5번 그린다.
  plt.plot(np.random.randn(50))
  ```

  x, y에 대한 그래프도 그릴 수 있다.

  ```python
  x = np.arange(0, 10, 0.01)
  plt.plot(x, np.sin(x))
  plt.plot(x, np.cos(x))
  ```

- `plt.subplots()`: plt.figure와 plt.axse에 대한 모든 요소를 포함한다. (subplot아님. subplots임)

- `plt.show()`: plot을 팝업 창으로 띄워준다.

```python
fig = plt.figure()
ax = plt.axes()
fig, ax = plt.subplots()  # 위의 두 줄을 합친 것임
plt.show()
```

> 빈 그래프창이 나오는걸 볼 수 있다.

- `plt.waitforbuttonpress()` : 아무 버튼이 눌리면 이미지 팝업창 닫음




---

## 2. Method 및 Property

### 1. plot

#### 1. axis

x, y 축을 설정할 수 있다.

- `plt.xlim(min, max)` x축 범위 설정
- `plt.tlim(min, max)` y축 범위 설정

- `plt.axis([xmin, xmax, ymin, ymax])` x, y축 한 번에 설정
  - `plt.axis('tight')`  x, y축을 알아서 딱 맞게 지정
  - `plt.axis('equal')`  x, y축을 보다 넓은 범위로 지정
  - `plt.axis(xscale = 'log', yscale = 'log')`  x, y축의 scale를 log로 표현
  - `plt.xaxis.set_major_formatter(plt.NullFormatter)`  x축의 date를 아예 표현하지 않음  (xaxis 대신 yaxis사용하면 y축에 적용)

```python
plt.plot(np.random.randn(50))
plt.xlim(-1, 50)
plt.ylim(-5, 5)
plt.axis([0, 40, -10, 10])
plt.axis('tight')
```





#### 2. Label

- `plt.title("title이름")` 그래프의 이름
- `plt.xlabel("")`  그래프의 x축 이름
- `plt.ylabel("")`  그래프의 y축 이름

```python
plt.plot(np.random.randn(50))
plt.title("tmp")
plt.xlabel("x!")
plt.ylabel("y!")
```

- `label = "" `  각 범례에 이름을 붙여준다. (plot의 속성임)

- `plt.legend()` 각 범례의 이름을 그래프 위에 표현해준다. (이거 없으면 label 속성 설정해도 안뜸) 

  ```python
  plt.plot(np.random.randn(50), label = "one!")
  plt.plot(np.random.randn(50), label = "two!")
  plt.legend()
  ```

  - legend의 위치를 설정 속성 `loc`

  ```python
  plt.legend(loc = 'lower right')
  plt.legend(loc = 'upper center')
  ```

  - legend를 여러 컬럼으로 표현하는 속성 `ncol`

  ```python
  plt.legend(fameon = False , ncol = 2)
  # fameon = False 은 고정, # 두 개의 columns
  ```

  

#### 3. Multiple Subplots

- subplot

  subplot의 argument를 사용해 다중 graph를 표현할 수 있다.

  배열 형태의 다중 plot

  `plt.subplot(abc)` a: 전체 비율 중 행의 개수 //  b: 전체 비율 중 열의 수, c: 전체 비율 중 plot이 위치할 자리의 수

  ```python
  plt.plot(np.random.randn(50).cumsum)
  plt.subplot(411)  # (4, 1) shape에서 첫 번째 위치에 plot 생성
  plt.subplot(3, 3, 8)  # (3, 3) shape에서 8번째 위치에 plot 생성
  ```

  

  - `subplot_adjust`

    ```python
    fig = plt.figure()
    fig.subplot_adjust(hspace = 0.4, wspace = 0.4)
    ```

    > figure 정보에 subplot_adjust를 호출해서 다중 plot을 만들 때 여백을 조절할 수 있다.
    >
    > `hspace` : 각 plot간의 수직 여백
    >
    > `wspace` : 각 plot간의 수평 여백

  

- GridSpec

  다중 plot을 배열처럼 사용하되, 합치는 동작까지 제공

  `plt.GridSpec(a, b)`   a: 전체 비율 중 행의 개수 //  b: 전체 비율 중 열의 수

  ```python
  grid = plt.GridSpec(2, 3, wspace = 0.4, hspace = 0.4)
  # (2, 3) shape의 plot배열
  plt.subplot(grid[0, 0]) 	# 0, 0 자리에 plot 한개 
  plt.subplot(grid[0, 1:])  	# (0, 1), (0, 2) 두 자리를 사용하는 하나의 plot
  plt.subplot(grid[1, :2])	# (1, 0), (1, 1) 두 자리를 사용하는 하나의 plot
  plt.subplot(grid[1, 2])		# 1, 2 자리에 plot 한개 
  plt.show()
  ```

  

#### 4. text

plot 위의 원하는 곳에 text를 삽입할 수 있다.

위치 기준은 Data, Axis, Figure로 나뉜다.

- `ax.transData`

  기준이 Data이기 때문에, 원하는 data값의 위치에 text를 삽입할 수 있다.

  `plt.text(x, y, ". text", transform = ax.transData)`

  x = x_data에 대응되는 값, 		y = y_data에 대응되는 값

  

- `ax.transAxse`

  기준이 Axse이기 때문에, 원하는 Axse 좌표 위치에 text를 삽입할 수 있다.

  `plt.text(x, y, ". text", transform = ax.transAxes)`

  x = x축에 대응되는 값(최소 0, 최대 1), 		y = y축에 대응되는 값(최소 0, 최대 1)

- `fig.transFigure`

  기준이 figure이기 때문에, 원하는 figure 좌표 위치에 text를 삽입할 수 있다.

  `plt.text(x, y, ". text", transform = fig.transFigure)`

  x = 전체 figure에서 x축에 대응되는 값(최소 0, 최대 1)

  y = 전체 figure에서 y축에 대응되는 값(최소 0, 최대 1)

```python
fig, ax = plt.subplots()
ax.axis([0, 6, -1.5, 1.5])  # plot의 axis 범위 설정 
x = np.arange(0, 20, 0.1) 
y = np.sin(x)  	# x에 대한 sin값
plt.plot(x, y)

plt.text(np.pi/2, 1 , ". transData(pi/2,1)", transform = ax.transData)
# x, y값이 (np.pi/2, 1)인 위치에 ". transData(pi/2,1)" 라는 text 삽입

plt.text(0.2, 0.5, ". transAxes(0.2, 0.5)", transform = ax.transAxes)
# x, y축의 전체 비율이 1일때, (0.2/0.5)인 위치에 ". transAxes(0.2, 0.5)" 라는 text 삽입

plt.text(0.2, 0.2, ". transFigure(0.2, 0.2)", transform= fig.transFigure)
# figure에서 x, y축의 전체 비율이 1일때, (0.2/0.2)인 위치에 ". . transFigure(0.2, 0.2)" 라는 text 삽입

plt.show()
```



#### 5. ticks

- `plt.xticks(rotation=m)` : x축의 각 data 이름을 90도 회전
- `plt.yticks(rotation=m)` : y축의 각 data 이름을 m도 만큼 회전

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

- Font 종류 보는법

  ```python
  print(set([f.name for f in mpl.font_manager.fontManager.ttflist]))
  ```

- 폰트 할당

  `변수명 = {'family' : '폰트이름', 'size': 폰트 사이즈, 'color': '폰트 색'}`

  ```python
  font1 = {'family' : 'DEjavu Sans', 'size': 24, 'color': 'black'}
  ```

- 할당된 폰트 사용

  `plt.label("label name", fontdict = forn 변수)`

  ```python
  plt.title("tmp", fontdict = font1)
  ```

  