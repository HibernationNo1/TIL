## MySQL

{:toc}





https://www.inflearn.com/course/%EC%96%84%EC%BD%94-%EB%A7%88%EC%9D%B4%EC%97%90%EC%8A%A4%ED%81%90%EC%97%98/lecture/86855?tab=curriculum&volume=0.29&speed=1.25

---



### install

[여기](https://dev.mysql.com/downloads/) 

- windows : [MySQL Installer for Windows](https://dev.mysql.com/downloads/windows/) 다운로드

  > [참고](https://www.inflearn.com/course/%EC%96%84%EC%BD%94-%EB%A7%88%EC%9D%B4%EC%97%90%EC%8A%A4%ED%81%90%EC%97%98/lecture/86854?tab=curriculum&volume=0.49&quality=auto&speed=1.25)



### Workbench

sql 파일에 접근할 수 있도록 하는 tool

#### Connection

Workbench를 통해 local에 설치된 mysql에 연결한다.

> - Connection Name : ainsoft
> - port : 3307
> - password : ain7679



##### create database

- ```sql
  CREATE SCHEMA 'mydatabase' DEFAULT CHARACTER SET utf8mb4 COLLATE utf8mb4_general_ci ;
  ```

  > `utf8mb4` : 한글을 포함한 전세계 문자 + 이모티콘 사용 가능
  >
  > `utf8mb4_general_ci` : 정확하진 않지만 정렬 속도 빠름

- schemas 부분에서 우클릭 > create schema 클릭



##### delect database

- ```sql
  DROP DATABASE 'mydatabase' ;
  ```

- schemas 부분에서 삭제할 database 우클릭 > drop schema





## Command

- mysql 실행

  ```
  $ C:\Program Files\MySQL\MySQL Server 8.0\bin 
  ```

  에서 

  ```
  $ ./mysql -u root -p
  ```

  > mysql에 root로 접속, pw입력

  ```
  mysql>
  ```

  위 처럼 입력 word가 달라진다.





- `show databases`

  ```
  mysql> show databases;
  ```

  현재 내 mysql에 깔려있는 database들이 나온다.
  
  ```
  mysql> show databases; 
  +--------------------+
  | Database           |
  +--------------------+
  | agritech_db        |
  | information_schema |
  | mysql              |
  | performance_schema |
  | sys                |
  | world              |
  +--------------------+
  ```
  
  여기서 `agritech_db  ` 라는 database에 접근하고자 한다면
  
  ```
  mysql> use agritech_db
  ```
  
  라고 입력, `Database changed` 가 뜰 것이다.



#### CREATE TABLE

database에 table을 만드는 명령어

```sql
CREATE TABLE people (
	person_id INT,
	person_name VARCHAR(10),
	age TINYINT,
	birthday DATE
);
```



또는 mysql의 table위에서 우클릭 > create table 클릭



#### ALTER TABLE

table을 변경하는 명령어

```sql
-- 테이블 명 변경
ALTER TABLE people RENAME TO friends;
```



#### column 정보 변경

##### CHANGE COLUMN

column 정보 변경

```sql
CHANGE COLUMN {변경 전 컬럼명} {변경 후 컬럼명} {변경할 자료형},
```

```sql
CHANGE COLUMN column_1 column_2 TINYINT;
```

> 자료형 변경을 원치 않을 경우 column의 기존 자료형을 그대로 입력

##### DROP/ADD COLUMN

```sql
DROP COLUMN column_1,
ADD COLUMN column_3 TINYINT AFTER column_2
```

> `ADD COLUMN` 사용 시 자료형 기재, `AFTER`을 사용하여 column위치 결정 가능



#### INSERT INTO 

data 삽입

```sql
INSERT INTO {테이블 명}
	(컬럼명1, 컬럼명2, 컬럼명3, 컬럼명4)
    VALUES (컬럼명1의 값, 컬럼명2의 값, 컬럼명3의 값, 컬럼명4의 값);
```

```sql
INSERT INTO table_1
	(column_1, column_2, column_3, column_4)
    VALUES (1, 'foo', 18, '2022-01-14');
```

또는 column 순서대로`VALUES`만 적어도 된다.

```sql
INSERT INTO table_1
    VALUES (1, 'foo', 18, '2022-01-14');
```



여러 data를 insert할 때

```sql
INSERT INTO table_1
    VALUES 
    (1, 'foo', 18, '2022-01-14'),
    (2, 'bar', 19, '2022-01-13'),
    (2, 'buz', 19, NULL);
```

> 2개의 data 입력





