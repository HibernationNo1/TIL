# Exploratory Data Analysis, EDA

**데이터 분석 과정**

모델의 학습 이전에, 데이터의 각 컬럼을 분석해서 어떤 컬럼이 결과에 큰 영향을 미치는지, 각 컬럼은 어떤 관계를 가지고 있는지에 대한 분석을 하는 과정이다.



### 1. 데이터 확인

csv파일을 직접 들여다 보며 어떤 컬럼이 있는지 확인하거나 코드로 구현해서 각 컬럼을 확인할 수 있다.

코드로 구현시 pandas 라이브러리의 각 메소드를 사용한다.

- df변수에 데이터를 할당하는 법

  ```python
  df = dp.read_csv('파일 위치\파일 이름')
  ```

  > pandas 라이브러리를 활용해서 df에 dataframe을 할당한다.

- 컬럼의 종류 확인하는 법

  **columns** 메소드 사용

  ```python
  print(df.columns)
  ```

  > dataframe에 어떤 컬럼이 있는지 알 수 있다.

- 모든 데이터를 확인하고자 할 때

  데이터가 광범위할때, 출력을 하면 중간이 `...`으로 생략되어 출력된다. 이러한 데이터도 다 보기 위해서 설정값을 미리 호출해야 한다.

  1. 모든 열을 다 보고자 할 때.

     `pd.set_option('display.max_columns', None)`

  2. 모든 행을 다 보고자 할 때.

     `pd.set_option('display.max_rows', None)`

- **head()**

  dataframe의 상위 n개를 반환한다. (디폴트 5개)

  `df.head()`

- **info()**

   데이터의 information을 반환한다.

  `df.info()`

- **describe()**

  수치형 데이터들의 통계를 반환한다.

  `df.describe()`

- **value_counts()**

  특정 칼럼의 정보를 알 수 있다.(범주형, 수치형 상관 없음)

  `df['컬럼명'].value_counts()`

> 자세한 내용은 [pandas](https://github.com/HibernationNo1/TIL/blob/master/study_Machine_learning/python_module/Pandas.md)

### 2. 데이터 분석

데이터의 구성을 수치형, 범주형으로 나눈 후 seaborn 라이브러리를 통해 dataframe을 시각화해서 데이터를 분석한다.

#### 수치형 데이터 분석

- histplot()

  히스토그램(도수 분포표) 그래프를 생성.

  `sns.histplot(x = '컬럼명', data = csv파일이 할당된 변수)`

- joinplot()

  scatter 그래프를 보여주며 그래프 밖으로는 히스토그램 그래프도 보여준다.

  `sns.jointplot(x = '컬럼명1', y = '컬럼명2', data = csv파일이 할당된 변수)`

- pairplot()

  dataframe의 데이터를 그리도(grid)형태로 각 컬럼에 대해 히스토그램과 분포도를 그린다.

  `sns.pairplot(변수명)`

#### 범주형 데이터 분석

- Boxplot()

  직관적으로 두 컬럼의 관계를 볼 수 있다. (보고할때 많이 씀)

  `sns.boxplot(x = '컬럼명1',y = '컬럼명2', data = 변수명)` 

- violinplot()

  히스토그램의 정보와 Boxplot의 정보를 묶어서 볼 수 있다.

  `sns.violinplot(x = '컬럼명1',y = '컬럼명2', data = 변수명)` 

- swarmplot

  violin plot을 scatter plot 형식으로 보여준다.

  `sns.swarmplot(x = '컬럼명1',y = '컬럼명2', data = 변수명)` 

- countplot

  범주형 데이터에서 각 범주를 막대그래프 형태로 표현한다.

  `sns.countplot(x = '컬럼명', data = df, order = ['범주1', '범주2', '범주3'])`



> 자세한 내용은 [seaborn](https://github.com/HibernationNo1/TIL/blob/master/study_Machine_learning/python_module/seaborn.md)



### 3. 데이터 분류

완전히 반대되는 값을 가진 칼럼이 동시에 존재를 하는 상태에서 regression을 하게 되면 Multicollinearity문제가 발생할 수 있다.