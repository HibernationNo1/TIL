# MySQL

## introduce

Relational Database Management System

> DBMS: DB를 관리하는 시스템
>
> - Oracle, MySQL, MongoDB등 (이것들도 전부 RDBMS이다.)



용어

- `Relational Database`(관계형 DB): 각각의 테이블 안의 data가 관계를 갖은 상태의 DB

- `Primary Key`: 한 table의 각 Row를 유일하게 식별해주는 column

  각 table마다 Primary Key가 존재해야 하며, NULL값을 허용하지 않고, 각 Row는 모두 유일한 값이어야 한다.

- `Foreign Key`: Primary Key를 제외한 각각의 column을 의미한다.

- `Schema`: database의 구조 및 형식, 관계 등의 정보를 형식 언어(formal language)로 기술한 것

  **설계도**라고 이애하면 되는데, 처음에 DB를 설계할 때 tables, 각 table에 들어갈 columns, 그리고 각 table간에 관계를 어떻게 맺을지를 결정 후 Schema 로 기술한다.

- `SQL`(Structured Query language): RDBMS에서 data를 관리하기 위해 사용되는 표준 프로그래밍 language로, DB schema생성, table관리, data추가, 수정, 삭제 등의 DB관련 모든 작업을 위해 사용되는 언어

- `CRUD`: 데이터 조작 언어들의 준말 `Create`, `Read`, `Update`, `Delete`



### MySQL

**install**

[여기](https://dev.mysql.com/downloads/) 

- windows : [MySQL Installer for Windows](https://dev.mysql.com/downloads/windows/) 다운로드

  > [참고](https://www.inflearn.com/course/%EC%96%84%EC%BD%94-%EB%A7%88%EC%9D%B4%EC%97%90%EC%8A%A4%ED%81%90%EC%97%98/lecture/86854?tab=curriculum&volume=0.49&quality=auto&speed=1.25)





**Workbench**

sql 파일에 접근할 수 있도록 하는 tool

Workbench를 사용하기 위해서는 mysql에 구동중이어야 한다.

- 접속할 DB를 새로 생성하기

  MySQL connection에서 + 클릭

  `Connection name`: sql이름 결정

  `connection method`: 건들필요 없음

  `hostname`: 내 PC의 IP

  `port`: 할당할 port 번호

  `Username`, `pw`

> commend에서도 mysql을 실행할 수 있지만, tool을 사용한다면 Workbench이다.
>
> - commend로 mysql 실행
>
>   ```
>   $ C:\Program Files\MySQL\MySQL Server 8.0\bin 
>   ```
>
>   에서 
>
>   ```
>   $ ./mysql -u root -p
>   ```
>
>   > mysql에 root로 접속, pw입력
>
>   ```
>   mysql>
>   ```
>
>   위 처럼 입력 word가 달라진다.
>



**Connection**

Workbench를 통해 local에 설치된 mysql에 연결한다.

> - Connection Name : ainsoft
> - port : 3306
> - password : 4958



## SQL

아래 모든 명령어는 commend에서도 실행이 가능하다. 아래 설명은 workbench에서 실행하는 것을 기준으로 적어놓는다.



### DATABASE

##### SHOW 

현 device에 존재하는 DB를 출력

```sql
SHOW DATABASES;
```

```
+--------------------+
| Database           |
+--------------------+
| information_schema |
| mysql              |
| performance_schema |
| sys                |
+--------------------+
```

위 4개의 DB는 mysql설치 시 자체적으로 설치되는 DB들임





##### CREATE

```sql
CREATE DATABASE database_name;
```

- `database_name`: 새로 만들고자 하는 DB이름





##### DROP

DB삭제

```sql
DROP DATABASE database_name;
```

- `database_name`: 삭제하고자 하는 DB이름

- `IF EXISTS` : database_name앞에 위치시키면 해당 DB가 없더라도 오류 발생하지 않음



##### USE 

해당 명령어 아래서부터 어떤 DB에 적용을 할 것인지 명시

```sql
USE database_name;
```

- `database_name`: 삭제하고자 하는 DB이름



### TABLE

#### CREATE

```sql
USE database_name;

CREATE TABLE table_name (
	column_name_1 type_1,
	column_name_2 type_2,
	column_name_3 type_3,
	column_name_4 type_4 NOT NULL,
    PRIMARY KEY(column_name_primary)
);
```

- `USE database_name`: 어떤 dataset에 적용할 명령어인지 명시
- ``table_name` : 만들고자 하는 table의 이름
- `column_name_1` :구성하고자 하는  column중 1개의 이름
- `type_1` : `column_name_1` 의 data type
- `PRIMARY KEY`
  - `column_name_primary`: PRIMARY_KEY로 사용할 column의 이름



- **options**

  - `NOT NULL`: NULL값을 허용하지 않음

    > PRIMARY_KEY로 지정할 column은 반드시 `NOT NULL`을 지정해야 한다.

  - `AUTO_INCREMENT`: INT type의 column에만 사용 가능

    다른 column의 row가 추가되면, 해당 row에 자동으로 마지막 숫자의 +1을 넣어 값이 채워진다.

    > 보통 PRIMARY_KEY에 지정한다.

  - `UNSIGNED`: 숫자형 type의 column에만 사용 가능

    모든 숫자는 양수만 취급

  보통 PRIMARY_KEY에 적용되는 options

  ```python
  ...	
  	ID INT UNSIGNED NOT NULL AUTO_INCREMENT
  ...
  	PRIMARY KEY(ID)
  ```

  



#####  data type

- 숫자형

  - `INT`: int형 (4byte)
    - `SMALLINT`:  int형 (2byte)
    - `TINYINT`:  int형 (1byte)
  - `FLOAT(정수부 길이, 소수부 자릿수)`: float
  - `DOUBLE(정수부 길이, 소수부 자릿수)`: double

- 문자

  - `STRING` : 고정 길이 문자열(255이하)

  - `VARCHAR(n)`: 가변 길이 (n값 이하,  n<=65535)  

    > n길이 이하의 문자열이 할당되면, 딱 그만큼의 size만 사용

- 시간형

  - `DATE`: 날짜(YYYY-MM-DD)
  - `TIME`: (hh:mm:ss)
  - `DATATIME`: (YYYY-MM-DD hh:mm:ss)
  - `TIMESTAMP`: 70년도부터 시스템 초 단위 누적 값
  - `YEAR`:

**`KEY`** : primary key의 data type





**e.g.**

```sql
USE test_db;

CREATE TABLE ann_dataset (
    ID INT UNSIGNED NOT NULL AUTO_INCREMENT,
	json_name VARCHAR(50),
	image_name VARCHAR(50),
    PRIMARY KEY(ID)
);

DESC ann_dataset;
```





#### SHOW, DROP

```sql
SHOW TABLES;
DROP TABLE table_name
```



#### DESC

table에 대한 자세한 출력

```sql
DESC table_name;
```



#### ALTER

table구조 수정

##### ADD COLUMN

새로운 column추가

```sql
ALTER TABLE table_name ADD COLUMN column_name column_type
```

- `table_name` : ALTER를 적용할 table 명시
- `column_name`: 추가할 column명
- `column_type`: 추가할 column에 적용할 data type
- 추가 option가능(`NOT NULL `같은)



##### MODIFY COLUMN

column type변경

```sql
ALTER TABLE table_name MODIFY COLUMN column_name column_type
```

- `table_name` : ALTER를 적용할 table 명시
- `column_name`: 수정할 column명
- `column_type`: 수정할 column에 적용할 data type
- 추가 option가능(`NOT NULL `같은)



##### CHANGE COLUMN

column name변경

```sql
ALTER TABLE table_name MODIFY COLUMN be_column_name af_column_name column_type
```

- `table_name` : ALTER를 적용할 table 명시
- `be_column_name`: 수정할 column명
- `af_column_name`: 수정한 column명
- `column_type`: 수정한 column에 적용할 data type
- 추가 option가능(`NOT NULL `같은)



##### DROP COLUMN

delete column

```sql
ALTER TABLE table_name MODIFY COLUMN column_name
```

- `table_name` : ALTER를 적용할 table 명시
- `column_name`: 삭제할 column명





#### CRUD

USE로 어떤 database에 적용할지 명시

```sql
USE test_db;
```



##### INSERT 

e.g. 1

```sql
INSERT INTO test_table VALUES(1, '2', 'test_value');
```

- `test_table` : data를 inserte할 table명시

- `VALUES()`: inserte할 data를 명시

  > row방향으로 insert가능
  >
  > 숫자는 `''` 없이, string인 경우 `''`로 구분
  >
  > 위 예시처럼 3개의 data를 넣으려면, column이 3개인 경우에만 가능



e.g. 2

```sql
INSERT INTO test_table (column_1, column_2, column_3) VALUES(data_1, data_2, data_3);
```

특정 columns에만 data를 넣을 경우



##### SELECT 

e.g. 1

```sql
SELECT * FROM test_table;
```



e.g. 2

```sql
SELECT test_value FROM
```





- **conditional options**

  option은 FROM뒤에 위치

  - `ORDER BY`

    ```sql
    ORDER BY column_name DESC;
    ```

    오름차순, 내림차순 정렬

    - `DESC`: 내림차순
    - `ASC`: 오름차순 정렬

  - `WHERE`

    ```sql
    WhERE tmp_value > 1; 
    ```

    ```sql
    WhERE tmp_value > 1 AND tmp_value < 3;
    ```

    - `AND`사용

    ```
    x WhERE tmp_value =1 ;
    ```

    특정 조건에 부합하는 data만 select

  - `LIKE`

    ```sql
    LIKE '%test%'; 
    ```

    > `'%test'`: 단어의 앞에 %가 있으면, 해당 단어로 끝나는 경우
    >
    > `'test%'`: 단어의 뒤에 %가 있으면, 해당 단어로 끝나는 경우
    >
    > `'%test%'` : 단어의 앞 뒤에 %가 있으면 해당 단어를, 가운데 포함하는 경우
    >
    > `'_test'`: 단어의 앞에 어떤 글자 1개가 있는 경우 
    >
    > %는 전체 str에 영향을 받는다면, `_`는 한 글자씩을 표현

  - `LIMIT`

    ```sql
    LIMIT 10;
    ```

    상위 10개만 출력



e.g. 3

```sql
SELECT id, name From mytable
WHERE id < 4 AND name LIKE '%i%'
ORDER BY name DESC
LIMIT 5;
```

> `;`로 구분하면 여러 줄 이어서 명령입력 가능



##### UPDATE

특정 data를 수정

```sql
UPDATE test_table SET value='tmp' WHERE conditional_value='conditional';
```

- `SET value='tmp'` : value라는 이름의 data의 값을 tmp로 변경
- `WHERE`문을 통해 특정 조건에 부합하는 경우에만 적용



##### DELET

특정 data삭제

```sql
DELETE FROM test_table WHERE value = 1;
```

- `DELETE FROM test_table`: FROM 앞에 `*` 를 사용하는것이 아닌, 어떤 teble에 delete를 적용할것인지 바로 명시
- `WHERE value = 1` : value가 1인 data는 전부 삭제





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



##### fetchall

CRUD에 의한 결과값을 모두 출력한다.

```python
result = cursor.fetchall()
```





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



