# seaborn

Seaborn은 matplotlib 패키지를 기반으로 하여 보다 편하게 통계를 시각화할 수 있는 도구로, 데이터 사이언스에서 사용하는 대부분의 그래프를 지원한다.

기본적인 시각화 기능은 Matplotlib 패키지에 의존하며 통계 기능은 Statsmodels 패키지에 의존한다. 

- [seaborn 웹사이트](http://seaborn.pydata.org/)

```python
import seaborn as sns
```

## 메소드

kaggle 에서 csv파일을 다운받은 후 `df`라는 변수에 csv파일을 할당했다고 가정

##### 매개변수

- hue: 만약 컬럼(또는 카테고리)형 데이터에서 다른 컬럼과의 관계를 확인하고 싶다면 `hue` 매개변수에 컬럼(카테고리)이름을 지정하여 카테고리 값에 따라 색상을 다르게 할 수 있다.
  
  - hue_order: hue에 할당한 컬럼의 범주를 나누어 관계를 확인할 수 있다.
  
- kde: 밀집도를 나타낸다. (실선으로 그려줌)

- loc: 범위를 조절한다.

- bins: plot의 크기를 조절한다.

- alpha: scatter plot에서 각 점을 투명하게 찍어준다.

- palette: 그래프의 색을 바꿀 수 있다.

  > palette = 'RdBu' 는 앞은 빨강, 뒤는 파랑색으로 색을 변경할 수 있다. 
  >
  > 그 외에도 색깔은 많음



### 1. 수치형 그래프

##### 1. histplot()

히스토그램(도수 분포표) 그래프를 생성.

`sns.histplot(x = '컬럼명', data = csv파일이 할당된 변수)`

```python
sns.histplot(x = 'age', data =df)
plt.show()

sns.histplot(data =df['age'])
plt.show()
#두 경우 다 됨
```

- hue라는 매개변수에 컬럼을 할당하여 추가하면 hue에 해당되는 그래프를 겹쳐서 볼 수 있다.

- kde라는 매개변수에 Ture를 할당하여 추가하면 **밀집도**를 볼 수 있다.

  ```python
  sns.histplot(x = 'age', data =df, hue = 'DEATH_EVENT', kde = True)
  plt.show()
  ```

  - hue에 해당되는 칼럼이 범주형일때, hue_order 매개변수를 활용해서 해당 칼럼의 내부 결과에 따라서 다시 또 구분할 수 있다.

    `hue_order = ['범주1', '범주2' , '범주3']`

- `변수명.loc`을 사용해 보고싶은 값의 범위를 조절할 수 있다.

  ```python
  sns.histplot(data =df.loc[df['creatinine_phosphokinase']<3000, 'creatinine_phosphokinase'])
  plt.show()
  ```

- bins라는 매개변수를 사용해 plot크기를  조절할 수 있다.

  ```python
  sns.histplot(data = df['ejection_fraction'], bins= 13)
  plt.show()
  ```

  > bins를 할당하지 않으면 ejection_fraction의 중간 데이터가 비어있는것을 볼 수 있다. 이건 데이터가 없는것이 아니라 plot의 크기가 너무 작아서 plot자체적으로 빈 것으로 표현해버린 것.

###### + kdeplot

커널이라는 함수를 겹치는 방법으로 히스토그램보다 부드러운 분포 곡선으로 시각화해준다.

```python
sns.kdeplot(x = 'age', data =df)
plt.show()
```



##### 2. joinplot

- scatter plot: 두 개의 변수 각각의 분포를 보여주는 그래프

scatter 그래프를 보여주며 그래프 밖으로는 히스토그램 그래프도 보여준다.

`sns.jointplot(x = '컬럼명1', y = '컬럼명2', data = csv파일이 할당된 변수)`

```python
sns.jointplot(x = 'platelets', y = 'creatinine_phosphokinase', hue = 'DEATH_EVENT', data = df)
plt.show()
```

- alpha라는 매개변수에 값을 할당해 투명도를 조절할 수 있다.

  ```python
  sns.jointplot(x = 'platelets', y = 'creatinine_phosphokinase', hue = 'DEATH_EVENT', data = df, alpha = 0.3)
  plt.show()
  ```

##### 3. pairplot()

dataframe의 데이터를 그리도(grid)형태로 각 컬럼에 대해 히스토그램과 분포도를 그린다.

수치형 column에 대해서만 그려준다.

`sns.pairplot(변수명)`

```python
sns.pairplot(df)
plt.show()
```



##### 4. heatmap()

각 데이터 값에 비례하여 색깔을 다르게 해서 2차원으로 자료를 시각화하는 히트맵(Heatmap). 각 컬럼의 관계를 색으로 보며 알 수 있다.

각 데이터의 상관관계를 보고자 할 때는 pandas의 corr함수에 heatmap를 씌워서 볼 수 있다.

```python
sns.heatmap(df.corr(), )
plt.show()
```

- annot 매개변수에 Ture값을 할당하면 각 값에 대해서 숫자또한 볼 수 있음

  ```py
  sns.heatmap(df.corr(), annot = True)
  plt.show()
  ```

  > 이렇게 하면 모든 데이터의 상관관계에 대해 모드 숫자로 표기하게 되기 때문에
  >
  > 대부분은 한 가지 데이터에 대한 모든 데이터의 수치만 확인한다.

  ```python
  fig = plt.figure(figsize = (5, 10))
  sns.heatmap(df.corr()[['blueWins']], annot=True)
  plt.show()
  ```

  > 잘 보기 위해서 그래프의 크기도 조절

##### 5. rugplot()

자료의 분포를 묘사하기 위한 그래프로, 데이터 위치를 x축 위에 작은 선분(rug)로 나타내어 실제 데이터의 위치를 보여준다.

```python
sns.rugplot(x ='age', data = df)
```

hieght라는 매개변수에 실수를 할당해서 선분의 최대크기 표현을 정할 수 있다.



#### + 그래프 활용

##### 1. groupby()

pandas에서 제공하는 특정 컬럼값을 그룹화하는 함수

- mean

  `gb = df.groupby('컬럼1').mean()['컬럼2']`

  컬럼1에 속한 범주마다 컬럼2에 대한 평균값을 확인할 수 있다.

  ```python
  gb = df.groupby('gender').mean()['Class_value']
  print(gb)
  ```

  - sort_values 를 활용하면 그래프가 정렬된다.

    ```python
    gb = df.groupby('Topic').mean()['Class_value'].sort_values(ascending = False)
    plt.barh(gb.index, gb)
    ```

    > ascending이 True면 내림차순, False면 오름차순이다. 디폴트는 Ture







---



### 2. 범주형 그래프

##### 1. Boxplot

직관적으로 두 컬럼의 관계를 볼 수 있다. (보고할때 많이 씀)

`sns.boxplot(x = '컬럼명1',y = '컬럼명2', data = 변수명)` 

```python
sns.boxplot(x = 'smoking', y = 'ejection_fraction', data = df)
plt.show()
```

> 흡연 여부에 따른 박출계수 분포



##### 2. violinplot

히스토그램의 정보와 Boxplot의 정보를 묶어서 볼 수 있다.

`sns.violinplot(x = '컬럼명1',y = '컬럼명2', data = 변수명)` 

```python
sns.violinplot(x = 'smoking', y = 'ejection_fraction', data = df)
plt.show()
```



##### 3. swarmplot

violin plot을 scatter plot 형식으로 보여준다.

`sns.swarmplot(x = '컬럼명1',y = '컬럼명2', data = 변수명)` 

```python
sns.swarmplot(x = 'DEATH_EVENT', y = 'platelets', data = df)
plt.show()
```

- hue를 사용하면 얼마나 hue에 해당되는 데이터가 분포되어 있는지 한 눈에 볼 수 있어 편한 plot이다.

  ```python
  sns.swarmplot(x = 'DEATH_EVENT', y = 'platelets', hue = 'smoking', data = df)
  plt.show()
  ```



##### 4. countplot

범주형 데이터에서 각 범주를 막대그래프 형태로 표현한다.

`sns.countplot(x = '컬럼명', data = df, order = ['범주1', '범주2', '범주3'])`

```python
sns.countplot(x='Class', data=df, order=['L', 'M', 'H'])
plt.show()
```

- 각 컬럼의 class의 범주 비율을 알고자 한다면? hue를 사용하자

  ```python
  sns.countplot(x='gender', data=df, hue='Class', hue_order=['L', 'M', 'H'])
  ```

  > x축에 gender컬럼의 범주 안에서 Class컬럼의 각 범주가 다시 나뉘는 그래프를 볼 수 있다.

- 각 컬럼의 막대그래프를 등장 숫자를 기준으로 내림차순 정렬해보자

  ```python
  sns.countplot(x='Class', data=df, order=['L', 'M', 'H'].value_counts().index)
  ```

  > `value_counts().index`가 sort의 역할을 해준다.

- 그래프의 x축을 y축과 바꾸려면 매개변수 x를 단순이 y로 바꿔주면 된다.



#### + 그래프 활용

##### 1. map

범주형 컬럼을 수치형으로 바꾸어 표현하기 (DataFrame의 map 메소드 활용)

`df['새로운 컬럼명'] = df['컬럼명'].map(dict(범주1=범주1에 할당하고자 하는 값, 범주2=범주2에 할당하고자 하는 값, 범주3=범주3에 할당하고자 하는 값))`

```python
df['Class_value'] = df['Class'].map(dict(L=-1, M=0, H=1))
```

> Class 컬럼이 사라지는것이 아니라, Class_value라는 새로운 컬럼이 csv안에 생성된다