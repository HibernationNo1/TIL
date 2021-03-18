# seaborn

Seaborn은 matplotlib 패키지를 기반으로 하여 보다 편하게 통계를 시각화할 수 있는 도구로, 데이터 사이언스에서 사용하는 대부분의 그래프를 지원한다.

기본적인 시각화 기능은 Matplotlib 패키지에 의존하며 통계 기능은 Statsmodels 패키지에 의존한다. 

- [seaborn 웹사이트](http://seaborn.pydata.org/)

```python
import seaborn as sns
```

## 메소드

데이터 출처: https://www.kaggle.com/andrewmvd/heart-failure-clinical-data 에서 csv파일을 다운받은 후 `df`라는 변수에 csv파일을 할당했다고 가정

- hue: 만약 컬럼(또는 카테고리)형 데이터가 섞여 있는 경우에는 `hue` 인수에 카테고리 변수 이름을 지정하여 카테고리 값에 따라 색상을 다르게 할 수 있다.
- kde: 밀집도를 나타낸다.
- loc: 범위를 조절한다.
- bins: plot의 크기를 조절한다.

- alpha: scatter plot에서 각 점을 투명하게 찍어준다.



### 1. 수치형 그래프

##### 1. histplot()

히스토그램(도수 분포표) 그래프를 생성.

`sns.histplot(x = '컬럼명', data = csv파일이 할당된 변수)`

컬럼명은 존재하는 컬럼이여야 함

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

숫자형 column에 대해서만 그려준다.

**column이 많으면 그래프가 많아져 효용성이 없다.**

`sns.pairplot(변수명)`

```python
sns.pairplot(df)
plt.show()
```

---



### 범주형 그래프

- 

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

