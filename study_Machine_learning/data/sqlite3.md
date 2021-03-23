# sqlite3

SQLite는 **파일기반의 임베디드 SQL 데이터베이스 엔진**이다.



## 코드 구현

```python
import sqlite3
```

>  파이썬 내장 모듈임



- **sqlite3.connect**()

  `변수 = sqlite3.connect('파일명')`

  ```python
  conn = sqlite3.connect('database.sqlite')
  ```

  `onnect`는 새로운 세션을 만드는 함수다. 이제 `conn`변수는 `database.sqlite`라는 파일에 연결된 하나의 세션이라고 이해하면 된다.

- **cursor**()

  `변수 = 세션명.cursor()`

  ```python
  curs = conn.cursor() #cursor객체 생성
  ```

  세션에 대한 객체를 만드는 함수다. 이제 curs는  conn에 연결된 파일에 대한 객체라고 이해하면 된다.

- **execute**

  `객체명.execute(sql 명령어)`

  ```python
  curs.execute('DROP TABLE IF EXISTS tblAddr') 
  
  curs.execute("insert into tbladdr values('김상형', '123-4567', '오산')")
  curs.execute("insert into tbladdr values('한경은', '555-1004', '수원')")
  curs.execute("insert into tbladdr values('한주완', '444-1092', '대전')")
  ```

  sql을 파이썬 코드 위에서 실행하는 함수라고 이해하면 된다.



- **pd.read_sql_query**()

  `변수명 = pd.read_sql_query('SELECT * from Country', 세션명)`

  ```python
  df_country = pd.read_sql_query('SELECT * from Country', conn)
  ```

  pandas 라이브러리를 사용해서 세션에 연결된 파일의 DataFrame를 가져오는 함수다. 변수에 데이터를 할당할 수 있다.