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



## 0. 기초 개념

plot은 그림(figure)과 축(axes)으로 구성되어 있다.

#### plot 구성 요소

- figure

  > 전체 창을 의미한다. 그 안에 axes를 할당해서 기본 plot이 완성되는 것이다.

- axes

  > plot에 속한 list라고 생각하면 된다. 이 axse안에 그림을 할당해서 기본 plot을 완성시키는 것이다.

- tick

  > plot를 구성하는 '칸' 을 의미한다.

- label

  > 각각의 data의 이름을 의미한다.

- title

  > plot의 이름을 의미한다.

- line

  > plot 안에 수치를 그림으로 표현하는 것을 의미한다. 이는 점, 선, 박스 등 다양한 형태의 그림으로 표현될 수 있다.

- spines

  > plot의 가장자리 선을 의미한다. plot의 틀이라고 생각하면 된다.

- legend

  > plot 안에 표현되는 Line의 이름이다. '범주' 라고 한다.

- grid

  > plot 안에 tick에 따라 위치를 좌표처럼 표현해주는 격자를 의미한다.



#### plot의 종류

- plot

  > line plot을 의미한다.

---

## 코드

### 1. figure, axes

#### 1. plt.figure

```python
fig = plt.figure()
```

> plt.plot() 과의 차이 : instance를 사용하므로써 더욱 다양한 함수를 호출해가며 사용할 수 있다.

 **속성**

- `figsize = (n, m)` : figure의 크기를 결정한다.

- `facecolor = ` : figure의 특정 color를 결정한다.

  > 여러 코드를 통해 색상을 지정할 수 있다.
  >
  > - `'r'` 빨강
  > - `'g'` 초록
  > - `'b'` 파랑
  > - `'#색상코드'` 
  > - `(R수치, G수치, B수치)`
  >
  > - `'색상이름'`
  >
  > ```python
  > fig = plt.figure(facecolor = 'r')
  > fig = plt.figure(facecolor = 'g')
  > fig = plt.figure(facecolor = 'b')
  > fig = plt.figure(facecolor = '#1243FF')
  > fig = plt.figure(facecolor = (0.2, 0.4, 0.6))  # 각각 R G B 값을 의미함
  > fig = plt.figure(facecolor = 'darkblue')
  > ```
  >
  > ![](https://mblogthumb-phinf.pstatic.net/MjAxNzA2MDJfMTg5/MDAxNDk2Mzk0OTQxNjYy.scwSCt72W3lW-32VrUH6Vi6tXBzSEPH86d5NfCwPe6Ug.MEWCQsPL2xBQQU3675ELH1y1xB4unFG0Mes-CBvkJSsg.PNG.radii26omg/named_colors.png?type=w2)



#### 2. fig.add_subplot

```python
fig = plt.figure()
ax = fig.add_subplot  # axis를 하나 추가
```

axis의 instance를 만듦으로써 ax위에 여러 plot을 할당할 수 있게 되는 것이다.

ex)`ax.plot()`

- axis의 grid system을 활용하자

  ```python
  ax = fig.add_subplot([3, 3]) # [3, 3] 형태의 axis를 ax에 할당
  ax[0] # 9개의 ax중 첫 번째 ax에 접근
  ax = fig.add_subplot(3, 3, 1)  
  # 첫 번째 argument는 rows를, 두 번째 argument는 columns를, 세 번째 argument는 axis가 위치할 자리를 의미한다.  
  # ax = fig.add_subplot(331) 과 같이 사용할 수 있다.
  ```

  아래처럼 grid system을 활용해서 figure에 여러 크기의 axes를 구성할 수 있다.

  ```python
  ax1 = fig.add_subplot(221)
  ax2 = fig.add_subplot(222)
  ax3 = fig.add_subplot(212)
  ```

 **속성**

- `facecolor = ` : axis의 특정 color를 결정한다.

- `sharex = ax ` : xlim에 대해서 **axis sharing**를 사용. 

  즉, ax는 add_subplot에 의해 만들어진 axis와 같은 xlim을 사용한다. (디폴트 False)

  > **axis sharing** : 다수의 axes를 공유하면서 한 번에 정보를 다꿀 수 있는 기능
  >
  > sharex 또는 sharey를 설정 후 set_xlim 또는 set_ylim을 사용하면 모든 axes가 한 번에 변한다.
  >
  > `sharey = ax` 도 있음

  ```python
  ax1 = fig.add_subplot(211)
  ax2 = fig.add_sibplot(212, sharex = ax1)
  ax2.set_xlim([0, 100])  # 다른 모든 ax1도 같이 set_xlim이 적용됨
  ```

  



#### 3. plt.subplots

figure과 axes를 한 번에 반환한다.

```python
fig, ax = plt.subplots()		# 1개의 figure과 axis를 반환한다.
fig, ax = plt.subplots(2, 2)  	# (2, 2) shape의 axes를 반환한다.
# 즉 첫 번째 argument는 rows를, 두 번째 argument는 columns를 의미한다.
fig, (ax1, ax2) = plt.subplots(2, 2)  
```

> 이때 반환되는 ax는 ndarray type이다.

```python
fig, ax = plt.subplots(2, 2) # 여기서 첫 번째 ax에 접근하기 위해서는
# ax가 ndarray type이기 때문에
ax[0, 0] # 이런 식으로 접근해야 한다.
```

위의 접근방식을 list 다룰때처럼 하기 위해`enumerate`,  `flat` 을 사용해보자.

```python
fig, axes = plt.subplots(2, 3)

for ax_idx, ax in enumerate(axes.flat):
    print(ax_idx, ax)
# 또는
ax = list()
for axs in axes.flat:
    ax.append(axs) 
```

단, plt.subplots은 grid system을 사용하기 어렵다.



 **속성**

- `figsize = (n, m)` : figure의 크기를 결정한다.
- `facecolor = ` : figure의 특정 color를 결정한다.(axis color 아님)

- `sharex = True ` : xlim에 대해서 **axis sharing**를 사용. 

  즉, 모든 axes는 같은 xlim을 사용한다. (디폴트 False)

  > `sharey = True` 도 있음

  ```python
  fig, axes = plt.subplots(2, 2, figsize = (7, 7), sharex = True, sharey = True)
  axes[1].set_xlim([0, 100])  # 다른 모든 axes도 같이 set_xlim이 적용됨
  ```

  





#### 4. plt.subplot2grid

grid system을 사용하기 위해 plt.subplot2grid를 사용해보자.

이는 fig인스턴스로부터 subplots를 호출하는 것 보다 더욱 진보적인 함수다.

`ax = plt.subplot2grid(shape, loc, rowspan = ,  colspan = , fig = )`

```python
fig = plt.figure()
ax1 = plt.subplot2grid((2, 1), (1, 0), fig = fig)
ax2 = plt.subplot2grid((2, 1), (2, 0), fig = fig)
```

- `colspan =` : 오른쪽 방향으로 몇 개의 column을 차지할건지를 의미한다.

  ```python
  ax1 = plt.subplot2grid((3, 3), (0, 1), colspan =2, fig = fig)
  ```

- `rowspan =` : 아래 방향으로 몇 개의 row를 차지할건지를 의미한다.

  ```python
  ax2 = plt.subplot2grid((3, 3), (1, 1), rowspan =2, fig = fig)
  ```

두 속성을 같이 사용하면 사각형 형태로 axes를 차지하게 된다.

```python
ax = plt.subplot2grid((3, 3), (1, 1), colspan =2, rowspan =2, fig = fig)
```

- `sharex = ax `: add_subplot에서의 axis sharing 동작과 동일하다.





#### 5. fig.add_axse

각 plot간의 간격을 자유롭게 결정할 수 있다.

plot 안에 또 다른 plot을 삽입할 수 있다.

plot 안의 특정 부분을 확대해서 plot안에 삽입할 수 있다.

`ax = fig.add_axes([left, bottom, width, height])`

```python
fig = plt.figure()
```

각 속성의 최대 기준값은 1이다.

- `left좌표` : plot이 시작할 왼쪽 축의 기준 좌표
- `bottom좌표`: plot이 시작할 아래 축의 기준 좌표
- `width` : plot의 가로축 길이
- `height`: plot의 세로축 길이

```python
ax = fig.add_axes([0.1, 0.1, 0.8, 0.8])
# 전체 figure의 가로, 세로 길이가 1일 때
# (0.1, 0.1) 의 좌표를 기준으로 가로 길이가 0.8, 세로 길이가 0.8인 plot을 추가한다.
```

이 기능을 더욱 편리하게 사용하기 위해 이미 list를 할당해 놓자

```python
rect = [0.1, 0.1, 0.8, 0.8]
ax = fig.add_axes(rect)
```

또는 각각의 값을 변수로 할당해서 사용할수도 있다.

```python
left, bottom = 0.1, 0.1
spacing = 0.005

width1, height1 = 0.65, 0.65
width2 = 1 - (2*left + width1 + spacing)
height2 = 1 - (2*bottom + height1 + spacing)

rect1 = [left, bottom, width1, height1]
rect2 = [left, bottom + height1 + spacing, width1, height2]
rect3 = [left + width1 + spacing, bottom, width2, height1]

fig = plt.figure(figsize = (7, 7))
ax1 = fig.add_axes(rect1)
ax2 = fig.add_axes(rect2)
ax3 = fig.add_axes(rect3)
```



### 2. title, label, layout

#### 1. ax.set_title

`ax.set_title(' ', fontsize = )`

```python
fig, ax = plt.subplots(figsize = (7, 7))
ax.set_title('Title', fontsize = 20)
```





#### 2. ax.set_x(y)label

`ax.set_xlabel(' ', fontsize = )`

`ax.set_ylabel(' ', fontsize = )`

```python
fig, ax = plt.subplots(figsize = (7, 7))
ax.set_xlabel('X Label!', fontsize = 15)
ax.set_ylabel('X Label!', fontsize = 15)
```



#### 3. fig.tight_layout

axes를 figure안에 균등하고 적절하게 위치하게 한다.  axes들의 label, title이 겹칠 때 사용

`fig.tight_layout()`

**속성**

`pad = ` : figure과 axes사이의 간격, axes와 axes간의 거리를 의미한다. 디폴트는 0.5



#### 4. fig.subplot_adjust

tight_layout과는 다르게 각각의 빈 공간의 거리를 따로따로 결정할 수 있다.

##### 1. ax.get_x(y)axis

axis의 x축 또는 y축을 반환한다.

`ax.get_xaxis()`

`ax.get_yaxis()`

##### 2. x(y)axis.set_visible

x축(또는 y축)의 값을 안보이게 한다. 디폴트는 True

`xaxis.set_visible(False)` 

`yaxis.set_visible(False)`

```python
fig, axes = plt.subplots(2, 2, figsize = (10, 10))

for ax_idx, ax in enumerate(axes.flat):
    ax.get_xaxis().set_visible(False)
    ax.get_yaxis().set_visible(False)
```

##### 3. fig.subplots_adjust

**속성**

- `bottom = ` 하단 axis의 시작 지점의 y좌표 

  > bottom = 0.01  : 전체 fig의 y길이 중 0.01 비율의 길이만큼 하단 빈 공간을 생성

- `top = ` 상단 axis의 끝 지점의 y좌표

  > top = 0.99  : 전체 fig의 y길이 중 0.01 비율의 길이만큼 상단 빈 공간을 생성

- `left = ` 좌측 axis의 시작 지점의 x좌표

- `right = ` 우측 axis의 끝 지점의 x좌표

- `hspace = ` axes간의 상하 거리
- `wspace = ` axes간의 좌우 거리

```python
fig.subplots_adjust(bottom = 0.1, top = 0.99, left = 0.01, right = 0.99, hspace = 0.2, wspace = 0.05)
```





## 연습 코드

1. 

```python
import matplotlib.pyplot as plt
import numpy as np

fig = plt.figure(figsize = (18, 9))
n_row, n_col = 3, 4
axes = np.empty(shape = (0, n_col))
xlabel_list = ['one', 'two', 'three', 'four']
ylabel_list = ['five', 'six', 'seven']

for r_idx in range(n_row):
    axes_row = np.empty(shape = (0, ))
    if r_idx == 0:
        for c_idx in range(n_col):
            if c_idx == 0:
                ax = fig.add_subplot(n_row, n_col, r_idx*n_col + c_idx + 1)
            else :
                ax = fig.add_subplot(n_row, n_col, r_idx*n_col + c_idx + 1, 
                                    sharey = axes_row[0])
            axes_row = np.append(axes_row, ax) 
    else:
        for c_idx in range(n_col):
            if c_idx  == 0:
                ax = fig.add_subplot(n_row, n_col, r_idx*n_col + c_idx + 1,
                                    sharex = axes[0, c_idx])
            else : ax = fig.add_subplot(n_row, n_col, r_idx*n_col + c_idx + 1, 
                                    sharex = axes[0, c_idx],
                                    sharey = axes_row[0])
            axes_row = np.append(axes_row, ax)
    axes = np.vstack((axes, axes_row))

axes[0, 0].set_ylim([0, 1])
axes[1, 0].set_ylim([1, 2])
axes[2, 0].set_ylim([2, 3])
axes[0, 0].set_xlim([0, 100])
axes[0, 1].set_xlim([0, 200])
axes[0, 2].set_xlim([0, 300])
axes[0, 3].set_xlim([0, 400])

for ax_idx, ax in enumerate(axes.flat):
    if ax_idx % n_col == 0:
        ax.set_ylabel(ylabel_list[ax_idx // n_col], fontsize = 20)
    else :
        ax.get_yaxis().set_visible(False)
    
    if ax_idx >= 2*n_col :
        ax.set_xlabel(xlabel_list[ax_idx - 2*n_col], fontsize = 20)
    else :
        ax.get_xaxis().set_visible(False)
fig.tight_layout()
fig.subplots_adjust(hspace = 0.2, wspace = 0.01)
plt.show()
```