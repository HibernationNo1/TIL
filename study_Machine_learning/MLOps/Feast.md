{:toc}



# Feast

현재까진 image dataset에 사용하기엔 무리

filesource는 `.parquet` 형식의 file로부터 data를 가져오는데, 이 때 parquet는 dataframe의 구조를 가지고 잇다.

image dataset의 전달 포맷은 json이고, json을 dataframe으로 변환하기 위해서는 모든 array의 length가 같도록 dataset을 만들어야 한다. 

이후 pandas를 통해 json을 dataframe으로, dataframe에서 parquet으로 변환해야 한다. original image 같은 경우는 어떻게 store에 넣을지 방법이 없다.





##### instll

```
$ pip install feast
```

설치 후 반드시 runtime restart 필요

check

```
$ feast version
```







### Introduction

[Introducing Feast](https://cloud.google.com/blog/products/ai-machine-learning/introducing-feast-an-open-source-feature-store-for-machine-learning), [공식](https://feast.dev/)

feature store tool, operational data system for managing and serving machine learning features to models in production.



![](https://1650793599-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F63geyz0MgpJmggxj7jnT%2Fuploads%2Fgit-blob-af58d3cf3809fcc5e69119de273668f715f27538%2Fimage%20(7).png?alt=media)



**Feature Service**

여러 개의 Feature View를 포함할 수 있으며, ML model 당 하나를 생성하여 model이 사용하는 Feature를 추적, 관리한다.

- Feature View : data 원본에서 발견되는 논리적 그룹

  0개 이상의 Entitis, 1개 이상의 Features, 그리고 1개의 Data Source로 이루어져 있다.

  - Feature
  - Entity : `key : list` 형태의 dict type
  - Data Source



**Online Store**

latency가 낮은 Online feature조회에 사용된다.

Online Store의 feature저장 방식은 data원천의 저장 방식을 그대로 따르지만, entity key마다의 최신 Feature값만 저장된다. (누적값들이 저장되지 않음)



**Offline Store**

누적되는 Feature들로부터 훈련 data를 생성할 때 사용

빠른 inference를 위해 feature들이 필요할 때 Offline Store로부터 feature들을 materializing하여 load한다.



**registry**

- 모든 feature들의 정의와 meta data가 모여있는 공간
- 작업자드르이 공동 작업을 가능하게 한다.
- feast배포마다 하나의 registry가 존재한다.

- entities, feature views, feature services 등의 registry구성 요소들은 apply명령에 의해 update되지만, 각 구성 요소들의 meta data는 materialization과 같은 작업에 의해 update가 가능하다.

- registry 내 모든 Feature View를 확인

  ```python
  from feast import FeatureStore
  fs = FeatureStore("my_feature_repo/")
  print(fs.list_feature_views())
  ```

- registry 내 특정 Feature View를 확인

  ```python
  from feast import FeatureStore
  fs = FeatureStore("my_feature_repo/")
  print(fs.get_feature_view("my_fv1"))
  ```



**사용법**

1. `feast init {repo_name}`으로 사용할 feature store repository를 만들 수 있다.
2. 해당 repo안에서 feast SDK와 python을 이용하려 feature을 정의할 수 있다.
   - python
     - `data source`지정 (file, Big Query 등)
     - `Entity`(feature그룹의 대표 ID) 를 정의
     - `feature view` 정의 : `data source`, `Entity`으로 feature를 만든다. 이 feature은 Feature store생성 시 Feature store에 저장된다.
     - `feature service` 지정 :  `feature view`이 Feature store에 저장될 수 있도록 하는 code
   - 
3. `feast apply` 로 Feature store를 생성 및 업데이트 할 수 있다.
4. `feast meterialize`로 최산 feature값들을 저장 및 version관리할 수 있다.
5. ML code를 설계할 때 feast SDK로 위 feature store에 정의한 feature들을 가져올 수 있다.





### Feature Store

#### **Create a feature repository**

repository : feature store에 담을 feature들을 생성하는 code가 모여있는 곳

```
$ feast init feature_repo
$ cd feature_repo
```

> `feature_repo` 안에 기본 sample file들이 생성됨

```
__init__.py  data  example.py  feature_store.yaml
```

- `data` : feast에서 제공하는 demo data

  > 안에 `driver_stats.parquet` 가 들어있다.
  >
  > ```python
  > import pandas as pd
  > pd.read_parquet("data/driver_stats.parquet")
  > ```
  >
  > ![](https://1650793599-files.gitbook.io/~/files/v0/b/gitbook-x-prod.appspot.com/o/spaces%2F63geyz0MgpJmggxj7jnT%2Fuploads%2Fgit-blob-b2961c773e43f78f59e993ebde00b25a3ff7aca7%2Fscreen-shot-2021-08-23-at-2.35.18-pm.png?alt=media)

- `example.py` : 

  demo data의 feature 정의 : **feature store 정의**

  저장할 feature에 대한 정의를 담는다.

  ```python
  # This is an example feature definition file
  
  from datetime import timedelta
  
  from feast import Entity, FeatureView, Field, FileSource, ValueType
  from feast.types import Float32, Int64
  
  # Read data from parquet files. Parquet is convenient for local development mode. For
  # production, you can use your favorite DWH, such as BigQuery. See Feast documentation
  # for more info.
  # data source로부터 data를 읽어오는 code. 
  driver_hourly_stats = FileSource(
      path="/feature_repo/data/driver_stats.parquet",
      timestamp_field="event_timestamp",
      created_timestamp_column="created",
  )
  
  # Define an entity for the driver. You can think of entity as a primary key used to
  # fetch features.
  # Entity has a name used for later reference (in a feature view, eg)
  # and join_key to identify physical field name used in storages
  # 사용할 feature들의 대표 ID
  driver = Entity(name="driver", value_type=ValueType.INT64, join_keys=["driver_id"], description="driver id",)
  
  # Our parquet files contain sample data that includes a driver_id column, timestamps and
  # three feature column. Here we define a Feature View that will allow us to serve this
  # data to our model online.
  # 위 FileSource에서 가져온 data source에서 구체적인 feature를 정의한다.
  driver_hourly_stats_view = FeatureView(
      name="driver_hourly_stats",
      entities=["driver"],  # reference entity by name
      ttl=timedelta(seconds=86400 * 1),
      schema=[
          Field(name="conv_rate", dtype=Float32),
          Field(name="acc_rate", dtype=Float32),
          Field(name="avg_daily_trips", dtype=Int64),
      ],		# feature정의
      online=True,
      source=driver_hourly_stats,		# data source
      tags={},
  )
  
  driver_stats_fs = FeatureService(
      name="driver_activity",
      features=[driver_hourly_stats_view]
  )
  ```

- `feature_store.yaml`

  feature repo가 어떻게 실행될 지 등의 설정 값을 담는다.
  
  ```
  project: my_project
  registry: data/registry.db
  provider: local
  online_store:
      path: data/online_store.db
  ```
  
  `project`, `registry`, `provider`, `online_store`를 정의





#### deploy feature

feature repo를 delpoy하는 동작

`.py` file로 인해 define된 feature store에 등록하는 과정

```
$ feast apply
```

```
Created entity driver
Created feature view driver_hourly_stats
Created feature service driver_activity

Created sqlite table feature_repo_driver_hourly_stats
```

이렇게 해서 하나의 registry가 등록이 된다.

> `feature_store.yaml`에서 설정된 값에 따라 추가적인 file생성



### Load feature

#### offline

```python
from feast import FeatureStore

store = FeatureStore(repo_path = ".")
```



#### online