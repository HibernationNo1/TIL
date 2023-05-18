# DataBase

## 관계형 DataBase

RDB는 사전에 엄격하게 정의된 DB schema를 요구하는 table기반 data구조를 갖는다.



### N:M

#### 1:N

두 table간 일방향으로 1:N 관계를 갖는 구조

주로 proimary key - foreing key를 사용하여 관계를 맺는다.

- **고객-주문** 의 관계

  `고객 table`의 primary key(고객 번호)를 참조하는 `주문내역 table`의 foreing key.

  `고객 table`에는 고객의 번호(1)가 있고 `주문내역 table`에는 해당 고객의 주문내역(N)이 있다.







#### N:M

두 table간 양방양으로 1:N의 관계를 갖는 구조.

주로 새로운 table(Mapping table)을 통해서 관계를 맺는다.

- **학생 - 수업**의 관계

  `학생 table`의 primary key(학생 번호)는 ` 수업 table`의 특정 과목을 여러개 수강한다.(1:N)

  ` 수업 table`의 primary key(과목 이름)는 `학생 table`의 특정 학생들 여러명이 수강한다.(1:N)

  위와 같은 관계에서 mapping table을 하나 만든다.

  - mapping table

    각각 table의 primary key를 참조하는 foreing key만으로 구성된 table을 만든다.



### join

join이란 두 개 이상의 table을 서로 연결하여 하나의 결과를 만들어 보여주는 것을 의미한다.



#### inner join

두 table에 도무 있는 내용만 join되는 방식(**교집합**만 모은다.)

```
SELECT * FROM table_A INNER JOIN table_B ON table_A column_A = table_B column_B;
```

table_A의 `column_A`와 table_B의 `column_B`가 같은 data만 모아서 합친다. 

>  두 table의 모든 column이 같지 않고 존재하지 않는(Null) data가 있을 수 있다.
>
> 때문에 두 table에 공통된 data가 존재하는 column에 대해서만 select한다.



#### left outer join

왼쪽 table의 모든 행에 대해서 join을 진행하는 방식(교집합 + 왼쪽 table의 data를 모은다.)

```
SELECT * FROM table_A LEFT JOIN table_B ON table_A column_A = table_B column_B;
```

table_A가 왼쪽 table이 된 상황

table_A와  '`column_A`와 table_B의 `column_B`가 같은 data'를 합친다.

> table_B에는 table_A에 없는 값은 NULL로 표시된다.





## NoSQL

Not Only SQL 

비관계형 database

table형식이 아닌, 비정형 data를 저장할 수 있도록 지원한다.

> RDB는 엄격한 schema로 인해 data중복이 없기 떄문에 data update가 많을 때 유리하다. (mySQL)
>
> NoSQL은 data중복이 많아 date update시 모든 컬렉션에서 수정이 필요하게 된다. (MongoDB)



### key-value storage system

NoSQL은 json document와 같은 key-value형식으로 data를 저장한다(table형식이 아님).

- 장점
  - 유연하고 자유로운 data구조
  - 새로운 필드 추가가 자유롭다.
  - scale out이 가능함으로 data양이 매우 많은 경우에 사용하면 좋다.
- 단점
  - data중복 발생 가능성이 높다
  - 중복 data가 많기 때문에 변경시 모든 컬렉션에서 수정이 필요하다
  - 명확한 data구조가 보장되지 않는다.



