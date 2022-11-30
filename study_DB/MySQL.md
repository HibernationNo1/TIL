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



e.g.

```sql
CREATE DATABASE database_name DEFAULT CREATE=utf8 COLLATE=utf8_bin
```

- `DEFAULT CREATE`: 문자 incording과 관련된 설정

  `utf8`: 한글 data의 정확한 처리를 위해

- `COLLATE`: 특정 문자 셋에 의해 database에 저장된 값들을 비교 검색하거나 정렬 등의 작업을 위해 문자들을 서로 `비교`할때 사용하는 규칙들의 집합을 의미

> 한글을 포함하는 data가 있는 경우 위 예시처럼 만들자.



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
    >
    > 전체 columns중에 단 하나에만 지정할 수 있다. 

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





###### exam_1

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



###### exam_2

```sql
USE database_name;
DROP TABLE IF EXISTS table_name;
CREATE TABLE table_name(
    column_name_1 ENUM('foo, bar') NOT NULL PRIMARY KEY,
    column_name_2 TINYINT,
    column_name_3 VARCHAR(20),
) ENDINE=InnoDB DEFAULT CHARSET=utf8;"
```

- `DROP TABLE IF EXISTS table_name;`: table을 만들기 전에 기존 table이 있다면 삭제하도록 설정
- `PRIMARY KEY` : PRIMARY KEY로 삼고자 하는 column에 option으로 명시해도 됨
- `ENUM`: 특정 값 중에서만 data를 넣을 수 있음을 명시(choices in)

- `ENDINE `: storage engine을 결정. 

  - ` InnoDB`: default storage engine

- `DEFAULT CHARSET=UTF8`: table생성 시 문자 incording과 관련된 설정

  



##### FOREIGN KEY

두 table간의 column을 참조하여 data의 무결성(두 table간 관례에 있어서, data의 정확성을 보장하는 제약 조건을 거는 것이다.)을 보장한다.

```sql
USE database_name;
CREATE TABLE table_1 (
    foreign_key INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
    column_1_1 TINYINT,
    column_1_2 VARCHAR(20),
    column_1_3 VARCHAR(10)
	) DEFAULT CHARSET=utf8;

CREATE TABLE table_2 (
    id INT UNSIGNED NOT NULL AUTO_INCREMENT PRIMARY KEY,
    foreign_key INT UNSIGNED NOT NULL AUTO_INCREMENT
    column_2_1 TINYINT,1_b VARCHAR(20),
    column_2_2 VARCHAR(10),
    FOREIGN KEY(foreign_key) REFERENCES table_1(foreign_key)
	) DEFAULT CHARSET=utf8;

```

- `FOREIGN KEY`: 다른 table의 column과 값을 참조한다.

  참조하는 column의 options를 그대로 적용해야 한다.

  > 위 예시는 foreign_key라는 column을 `FOREIGN KEY`로 지정

  - `REFERENCES table_1(foreign_key)` :
    - `table_1`: FOREIGN KEY에 연결할 column이 속한 table
    - `foreign_key`: FOREIGN KEY에 연결할 column의 이름



table_1에 아래 data가 있고

```
foreign_key  column_1_1 column_1_2 column_1_3
0            1           0      9079f       1297
1            2          10      5043k        720
2            3          20      7929P       1132
3            4          30      2237Z        319
4            5          40      5991S        855
5            6          50      7832a       1118
6            7          60      1836c        262
7            8          70      7574b       1082
8            9          80      4802l        686
9           10          90      3315y        473
```



table_2에 아래 data가 있다고 하자.

```
   id  foreign_key column_2_1 column_2_2
0   1           10          V          r
1   2            9          I          w
2   3            8          b          r
3   4            7          l          h
4   5            6          j          r
5   6            5          D          J
6   7            4          P          E
7   8            3          V          W
8   9            2          c          I
9  10            1          W          Q
```



- `table_2`의 foreign_key라는 column에 속한 data는 반드시 `table_1`의 foreign_key라는 column에 속한 data중에 하나여야 한다. 

  즉,  `table_1`의 foreign_key안에 없는 data를 table_2의 foreign_key에 insert하려고 하면 에러가 발생한다. 

- `table_2`에서 `table_1` 의 foreign_key를 참조하고 있기 때문에

  data의 insert는 `table_1`이 먼저 이루어져야 한다.

  > `table_1`안에 아무 data가 없는 상태에서 `table_2`에 특정 값을 넣고자 하면 참조하는 foreign_key값이 없기 때문에 error발생



###### DROP

FOREIGN KEY로 인해 다른 table을 참조하고 있는 column이 있는 table은 DROP이 바로 되지 않는다.

이는 Mysql이 테이블 간 관계가 있는 데이터를 함부로 수정하거나 삭제할 수 없도록 안전장치를 해두었기 때문

그럼에도 불구하고 데이터를 삭제하고자 한다면 `foreign_key_checks` 의 값을 설정하면 된다.

```sql
SET foreign_key_checks = 0;	 # 안전장치 해제
DROP TABLE table_name;		# table삭제
SET foreign_key_checks = 1;	 # 안전장치 적용
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





###### **options**

option은 FROM뒤에 위치

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





###### conditional

**WHERE**

특정 조건에 부합하는 data만 select

```sql
WhERE tmp_value > 1; 
```

```sql
WhERE tmp_value > 1 AND tmp_value < 3;
```

>  `AND`사용



```sql
x WHERE tmp_value =1 ;
```



**HAVING**

집계함수에 대한 조건비교를 할 때 사용한다.

```sql
SELECT COUNT(*) FROM peaple GROUP BY gender HAVING COUNT(*) >=100;
```







###### aggregate

집계 함수

**AVG**

평균값 계산

```sql
SELECT AVG(price) FROM items;
```



**SUM**

합산

```sql
SELECT SUM(price) FROM items;
```



**MAX**

````sql
SELECT MAX(price) FROM items;
````



**MIN**

```sql
SELECT MIN(price) FROM items;
```



**COUNT**

SELECT결과의 row수를 계산

```sql
SELECT COUNT(price) FROM items;
```





###### by

aggregate function과 같이 쓰인다.

**GROUP BY**

그룹을 지어서 DATA를 분석하고자 할 때 사용

```sql
SELECT AVG(age) FROM peaple GROUP BY gender;
```

 `GROUP BY`의 target column의 data종류별로 나누어 보여준다.

> 위 예시의 `gender`처럼 data의 종류(범위)가  적은(man, woman) column에 적용하기 좋다



**ORDER BY**

```sql
ORDER BY column_name DESC;
```

오름차순, 내림차순 정렬

- `DESC`: 내림차순
- `ASC`: 오름차순 정렬



##### UPDATE

특정 data를 수정

```sql
UPDATE test_table SET value='tmp' WHERE conditional_value='conditional';
```

- `SET value='tmp'` : value라는 이름의 data의 값을 tmp로 변경
- `WHERE`문을 통해 특정 조건에 부합하는 경우에만 적용



##### DELETE

특정 data삭제

```sql
DELETE FROM test_table WHERE value = 1;
```

- `DELETE FROM test_table`: FROM 앞에 `*` 를 사용하는것이 아닌, 어떤 teble에 delete를 적용할것인지 바로 명시
- `WHERE value = 1` : value가 1인 data는 전부 삭제







#### JOIN

##### INNER JOIN

두 TABLE간에 각각의 column값이 매칭되는 row만 select할 때 사용한다.

```sql
SELECT * FROM table_name_1 INNER JOIN table_name_2 ON table_name_1.column_1 = table_name_2.column_2 WHERE table_name_1.column_1 > 100;
```

- `FROM table_name_1 INNER JOIN table_name_2` :  table_name_1 과 table_name_2를 JOIN

- `ON table_name_1.column_1 = table_name_2.column_2` : 두 table간의 select조건

  >  table.column의 형식으로 table과 그에 속한 column을 명시한다.



약칭 사용 가능(as문처럼)

```sql
SELECT * FROM table_name_1 i INNER JOIN table_name_2 j ON i.column_1 = j.column_2 WHERE table_name_1.column_1 > 100;
```

- `table_name_1 i` : `table_name_1 `을 `i` 라고 명시
- `table_name_2 j`: `table_name_2`을 `j` 라고 명시



##### OUTER JOIN

pass





### SubQuery

`()`를 사용해서 SQL문 안에 추가적인 SQL문을 추가하는 것 

table간의 검색 시, 검색 범위를 좁히는 기능에 주로 사용

```sql
SELECT column_1 FROM table_name_1 IN(SELECT table_name_2 FROM column_2 WHERE column_1 > 100) ;
```

> ```sql
> SELECT * FROM table_name_1 i INNER JOIN table_name_2 j ON i.column_1 = j.column_2 WHERE table_name_1.column_1 > 100;
> ```
>
> `JOIN`을 사용한 SQL문과 같은 동작을 한다.
