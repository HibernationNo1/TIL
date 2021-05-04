# matplotlib기초2

### 1. text

#### 1. ax.text()

`ax.text(x, y, s = , fontsize = )`

`x, y` : text의 좌측 하단 좌표

`s` : 넣고자 하는 text(문자열)

```python
fig, ax = plt.subplots(figsize = (7, 7))
ax.text(x = 0, y = 0, s = "Hellow", fontsize = 30)
```



#### 2. Text Alignment

text 좌표의 기준을 text기준 좌측 하단에서 다른 위치로 바꿀 수 있다. 이것이 **Text Alignment** 이다.

- Text Alignment 속성 종류

  - ha(horizontalalignment) : 좌표의 기준점을 text안의 수평 위치로 잡는다.  default는 left

    `{'center', 'right', 'left'}`

  - vs(vertiacalaligment) : 좌표의 기준점을 text안의 수직 위치로 잡는다. default는 bottom

    `{'center', 'top', 'bottom', 'baseline', 'center_baseline'}`

**예시**

```python
ax.text(x=0, y=0, va='center', ha ='left', s="Hello", fontsize = 30)
```

>  (0, 0)의 좌표가 Hello 라는 text의 왼쪽 중간 높이의 지점에 놓이게 된다.



#### 3. Title Alignment

Title 좌표의 기준을 title text기준으로 바꿀 수 있다.

vs의 default는 bottom이다.

```python
fig, ax = plt.subplots(figsize = (7, 7))

fig.suptitle('Title', fontsize = 30, y = 0.9, vs = 'top')
```

> 전체 fig의 size가 1로 가정되며, Title의 기준 위치가 (0.5, 0.9)이고 Title text의 상단 면이  (0.5, 0.9)에 위치하게 된다.

```python
fig, ax = plt.subplots(figsize = (7, 7))
title_bottom = 0.9
fig.suptitle('Title', fontsize = 30, y = title_bottom, vs = 'bottom')

fig.subplots_adjust(top = title_bottom)
```

> title_bottom object를 통해 title의 위치와 plot의 top위치가 동일하게 통일되어 보기 좋은 figure이 만들어질 수 있다.



#### 4. Text Properties(font)

##### 1. fontfamily

fontfamily라는 속성을 통해 font를 결정할 수 있다.

matplotiob document에 가면 다양한 font를 확인할 수 있다.

>대표적
>
>{ 'serif', 'sans-serif', 'cursive', 'fantasy', 'monospace'}

```python
ax.text(0, 0, ha = "center", s = 'fontfamily', fontsize  = 30, fontfamily = 'fantasy')
```



##### 2. fontweight

fontweight라는 속성을 통해 font의 굵기를 결정할 수 있다.

>{'normal', 'bold'}

```python
ax.text(0, 0, ha = "center", s = 'fontweight', fontsize  = 30, fontweight = 'bold')
```



##### 3. alpha

alpha라는 속성을 통해 font의 투명도를 결정할 수 있다.

투명도 0% == 1, 100% == 0

```python
ax.text(0, 0, ha = "center", s = 'alpha', fontsize  = 30, alpha = 0.3)
```



##### 4. color

color라는 속성을 통해 font의 색상을 결정할 수 있다.

여러 코드를 통해 색상을 지정할 수 있다.

- `'r'` 빨강

- `'g'` 초록

- `'b'` 파랑

- `'#색상코드'` 

- `(R수치, G수치, B수치)`

- `'색상이름'`

  ![](https://mblogthumb-phinf.pstatic.net/MjAxNzA2MDJfMTg5/MDAxNDk2Mzk0OTQxNjYy.scwSCt72W3lW-32VrUH6Vi6tXBzSEPH86d5NfCwPe6Ug.MEWCQsPL2xBQQU3675ELH1y1xB4unFG0Mes-CBvkJSsg.PNG.radii26omg/named_colors.png?type=w2)

```python
ax.text(0, 0, ha = "center", s = 'color', fontsize  = 30, color = 'navy')
```



##### 5. Font Dictionary

Font Dictionary라는 속성을 통해 여러 font 속성을 한 번에 설정할 수 있다.

```python
title_font_dict = {'fontsize': 30, 'fontfamilt': 'serif', 
                  'color': 'darkblue', 'alpha':  0.8}
font_dict = {'fontsize': 20, 'fontfamilt': 'serif', 'fontweight' : 'bold'
             'color': 'darkblue', 'alpha':  0.8}

ax.set_title("font dict", fontdict = title_fint_dict)
ax.text(x = 0.1, y = 0.1, s = "font dict", fontdict = font_dict)
# 한 번에 여러 속성이 결정된다.
```

