## MySQL pyhton

**install**

```
$ pyp install pymysql
```

```py
import pymysql
```





### connect

```python
import pymysql
db = pymysql.connect(host='localhost', port=3306, user='root', passwd='test4958', db='test_db', charset='utf8')


```

- `host`
- `port`
- `user`: mysql에 접속할 user account
- `passwd`
- `db`: 접속하고자 하는 database
- `charset`: 지원 언어 유니코드





#### cursor

`cursor()`: cursor객체의 `execute()`를 사용하여 sql문장을 DB server에 전송한다.

```python
cursor = db.cursor()
```



##### execute

sql구문을 직접 실행하는 method

```python
schema = """
                CREATE TABLE ann_dataset (
                id INT UNSIGNED NOT NULL AUTO_INCREMENT,
                json_name VARCHAR(50),
                image_name VARCHAR(50),
                PRIMARY KEY(ID)
                );
            """
cursor.execute(schema)
```



##### fetch

**fetchall**

cursor에 의한 결과값을 모두 출력한다.

```python
result = cursor.fetchall()
```



**fetchone**

cursor에 의한 결과값중 상위 1개만 가져온다.

```
result = cursor.fetchone()
```





#### pandas

##### read_sql

`pandas.read_sql`를 이용하면 cursor보다 더욱 편리하고 사용이 가능하고, 출력도 더욱 보기 좋다.

단, `SELECT`구문만 사용 가능

```python
import pymysql
import pandas as pd

database = pymysql.connect(host="localhost",
                            port=3306, 
                            user="root", 
                            passwd="7679", 
                            database="test_db", 
                            charset="utf8")

sql = "SELECT * FROM ann_dataset"
df = pd.read_sql(sql, database)
print(df)
```

- ```python
  df = pd.read_sql(sql, database)
  ```

  - `read_sql`: sql을 읽어오는 method
  - `sql`: sql 구문
  - `database`: 연결된 DB



##### to_csv

```python
df = pd.read_sql(sql, database)
df.to_csv("svc_file_name.svc", sep = ",", index = False, encoding="utf-8")
```

- `index`:  csv file로 저장할 때 pandas에 의해 붙는 index column을 표시할것인지 여부. `True`: 표시함



#### commit

이제까지 실행한 sql구문에 문제가 없다고 판단될 경우 data를 commit하여 완전히 적용시키는 method

```python
db.commit()
```



#### close

db와의 connection을 끊는 method

```python
db.close()
```



