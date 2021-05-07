# matplotlib기초2

### 1. text

#### 1. ax.text()

```python
 ax.text(x, y, s = , fontsize = )
```

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



### 2. ticks, label

```python
fig, ax = plt.subplots(figsize = (7, 7))
```

#### 1. ax.tick_params

위의 code로 figure을 만들면, 각각의 x, y axis에는 main label만 표현되어 있는 것을 볼 수 있다.

이 main label(major ticks) 또는 minor ticks의 글씨를 키우는 함수가 **ax.tick_params()** 이다.

```python
ax.tick_params(속성)
```

> x, y 중 axis에 적용할건지 명시를 안하면 둘 다 적용됨

- `labelsize` : main label의 size를 결정

- `length` : label 표시 막대(tick)의 길이를 결정
- `width` : label 표시 막대(tick)의 굵기를 결정

- `bottom` : False를 주면 x axis의 tick을 표시 안함 (default = True)

  > `left` : y axis에 적용
  >
  > `top` : 상단 x axis에 적용 (default = False) 
  >
  > `right` : 우측 y axis에 적용 (default = False) 

- `labelbottom` : False를 주면 x axis의  main label을 표시 안함 (default = True)

  > `labelleft`: : y axis에 적용
  >
  > `labeltop` : 상단 x axis에 적용 (default = False) 
  >
  > `labelright` : 우측 y axis에 적용 (default = False) 

- `rotation` : label을 반시계방향으로 회전시킴 (적용하는 각도만큼)

  주로 label이 길 때 사용한다. 90을 주면 수직방향으로 회전

- `axis` : 특정 axis에만 위 속성들이 적용되도록 할 수 있다.

  axis = 'x' or 'y'

```python
ax.tick_params(labelsize = 20, length = 10, width = 3, 
               left = False, labelleft = False, 
               right = True, labelright =  True, 
               rotation = 30, axis = y)
```

- `which` : 속성을 major에 적용할 것인지, minor에 적용할 것인지를 결정한다. (defualt = major)

  > which ='minor'
  >
  > 물론 ax.set_xticks(minor = 'True') 가 이미 선언되어있어야 한다.



#### 2. ax.set_x(y)lim

x(또는 y)의 data 범위를 조절

`ax.set_xlim([start, end])`

```python
fig, ax = plt.subplots(figsize - (7, 7))
ax.set_xlim([-10, 10])
ax.set_ylim([0, 1])
```

> 표현되는 label 범위는 결정되지만 표현되는 label의 개수는 변함이 없다.



#### 3. ax.set_x(y)ticks

표현되는 main label의 개수를 결정할 수 있다.

```python
xticks = [i for i in range(10)]
ax.set_xticks(xticks)  
```

> 0~1 까지 6개로 표현되던 x axis의 label이 0~9까지 10개로 표현됨

```python
ax.set_xticks([0, 1, 5, 10])  
```

> 0부터 10까지 크기게 알맞는 간격으로 label이 표현된다.

또한 minor ticks까지 등장시켜 표현할 수 있다.

- `minor` : minor ticks 표현 (default = False)

  > `major` : default = True

```python
major_yticks = [i for i in range(0, 101, 20)]
minor_yticks = [i for i in range(0, 101, 5)]
ax.set_yticks(major_yticks)
ax.set_yticks(minor_yticks, minor = True)
```



**예시**

```python
fig, ax = plt.subplots(figsize = (7, 7))

major_xticks = [i for i in range(0, 101, 20)]
minor_xticks = [i for i in range(0, 101, 5)]
major_yticks = [i for i in range(0, 11, 2)]
minor_yticks = [i for i in range(0, 11, 1)]

ax.set_xticks(major_xticks)
ax.set_xticks(minor_xticks, minor = True)

ax.tick_params(axis = 'x', labelsize = 20, length = 10, width = 3, 
               rotation = 30)
ax.tick_params(axis ='x', which = 'minor', length = 5, width = 2)

ax.set_yticks(major_yticks)
ax.set_yticks(minor_yticks, minor = True)

ax.tick_params(axis = 'y', labelsize = 20, length = 10, width = 3)
ax.tick_params(axis = 'y', which = 'minor', length = 5, width = 2)
```



#### 4. ax.set_x(y)tickslabels

실질적인 값을 나타내는 label을 결정한다.

> ticks를 이미 설정 한 후에 설정해야 한다.

```python
ax.set_xtickslabel(label이름)
```

label 이름은 ticks가 존재하는 개수 만큼 동일한 개수의 string 원소로 이루어진 list형태다.

```python
xticks = [i for i in range(10)]
xtick_labels = ['class' + str(i) for i in xticks]

ax.set_xticks(xticks)
ax.set_xtickslabels(xtick_labels)
```

- `ha`(horizontalalignment) : text의 기준점을 text안의 수평 위치로 잡는다.  default는 left

  `{'center', 'right', 'left'}`

- `vs`(vertiacalaligment) : text의 기준점을 text안의 수직 위치로 잡는다. default는 bottom

  `{'center', 'top', 'bottom', 'baseline', 'center_baseline'}`



#### 5. ax.set_x(y)scale()

ticks의 scale을 결정

```python
ax.set_xscale('log')
```





### 4. grid

#### 1. ax.grid

tick을 따라서 plot 안에도 선을 표현해준다.

```python
ax.grid(속성)
```

- `axis` : 'x' or 'y'   (default = 둘 다)

- `linewidth` : line 굵기

- `linestyle` 

  > ':' 점선
  >
  > '-.' 실, 점 혼합선
  >
  > '--' 짧은 실선
  >
  > '-' 실선

```python
ax.grid(axis = 'y', linewidth = 2, linestyle = '--')
```

- `which` : 속성을 적용할 tick을 결정 'minor' or 'major'  



**예시**

yticks를 logscale로 표현한 ax (0부터 10^5까지)

```python
import numpy as np
import matplotlib.pyplot as plt

m_exp, M_exp = 0, 5
n_inter_yticks = 4 		# 칸 안에 표현하고자 하는 minor ticks의 개수

n_major_yticks = M_exp - m_exp + 1  # 표현하고자 하는 y의 major ticks의 개수
n_minor_yticks = (n_major_yticks -1)*(n_inter_yticks + 1) + 1 
# (표현하고자 하는 y의 major ticks에 의해 만들어지는 칸) * (칸 마다 표현하고자 하는 minor ticks의 개수) + bottom의 줄

major_yticks = np.logspace(m_exp, M_exp, n_major_yticks) # 10^(m_exp)부터 10^(M_exp)까지 n_major_yticks개로 표현
minor_yticks = np.logspace(m_exp, M_exp, n_minor_yticks)

fig, ax = plt.subplots(figsize = (7, 7))
ax.set_yscale('log')
ax.set_ylim([10**m_exp, 10**M_exp])

ax.set_yticks(major_yticks)
ax.set_yticks(minor_yticks, minor = True)

ax.tick_params(axis = 'y', which = 'major', length = 10)
ax.tick_params(axis = 'y', which = 'minor', length = 3)

ax.grid(axis = 'y', which = 'major', linewidth = 1.5)
ax.grid(axis = 'y', which = 'minor', linestyle = ':')

plt.show()
```



또는

```python
fig, ax = plt.subplots(figsize = (10, 10))
ax.set_yscale('log')
ax.set_xscale('log')

ax.set_ylim([10**(-10), 10**3]) # 10^(-13)부터 10^3 까지
ax.set_xlim([10**0, 10**4])

major_yticks = [10**i for i in [-10, -5, 0]]
minor_yticks = [10**i for i in range(-10, 4)]
major_xticks = [10**i for i in range(0, 5)] \
```



### 5. Spine

#### 1. ax.spines

Spine objects means the edge axis of plot.

Sepine object type is **dictionary**

```python
fig, ax = plt.subplots(figsize = (5, 5))
print(ax.spines.keys()) 
```

> odict_keys(['left', 'right', 'bottom', 'top'])

so, we need to as a dictonary when access to spine 



**property**

- `ax.spines[spine_loc].set_visible(False)`

  keep the selected axis invisible

  > ticks, labels are not invisible
  >
  > need to use `ax.tick_params` if you make invisible the ticks, labels

- `ax.spines[spine_loc].set_linewidth(int)`

- `ax.spines[spine_loc].set_alpha(float)`

- `ax.spines[spine_loc].set_color('navy')`

  

**ex**

```python
ax.spines['right'].set_visible(False)
```

```python
for spine_loc, spine in ax.spines.items():
    if spine_loc in ['left', 'bottom']
    spine.set_linewidth(3)
    spine.set_alpha(0.5)
	
    if spine_loc in ['right', 'top']
    spine.set_visible(False)
```

> using items()



if you jsut want to see only img (no ticks, no spine)

```python
fig, ax = plt.subplots(figsize = (5, 5))

for spine_loc spine in ax.spines.items():
    spine.set_visible(False)

ax.tick_params(left = False, labelleft = False, bottom = Falsem labelbottom = False)
```



###### 1. set_position('center')

> one of the property 

if you want the tick and label locate to center of plot, using this property

`ax.spines[spine_loc].set_position('center')`

this property change locate of spine

```python
fig, ax = plt.subplots(figsize = (5, 5))

for spine_loc, spine in ax.spines.items():
    if spine_loc in ['right', 'top']:
        spine.set_visible(False)

    if spine_loc in ['left', 'bottom']:
        spine.set_position('center')
```

but this method have one drawback; the standard point of label is not fit



###### 2. set_position(('axse', 0.5))

to solve this problem, use tuple argument

```python
ax.spines[spine_loc].set_position(('axse', 0.5))
```

this means the standard of spine position fit by axse. not figure

so, the corrected code is

```python
fig, ax = plt.subplots(figsize = (5, 5))

for spine_loc, spine in ax.spines.items():
    if spine_loc in ['right', 'top']:
        spine.set_visible(False)

    if spine_loc in ['left', 'bottom']:
        spine.set_position(('axes', 0.5))
```



###### 3. set_position(('data', 0))

this means the standard of label value(data) fit to 0 

```python
for spine_loc, spine in ax.spines.items():
    if spine_loc in ['right', 'top']:
        spine.set_visible(False)

    if spine_loc in ['left']:
        spine.set_position(('axes', 0.5))
    
    if spine_loc in ['bottom']:
        spine.set_position(('data', 0)) # left spine label value start from 0
```

