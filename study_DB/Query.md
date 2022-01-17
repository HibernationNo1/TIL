{:toc}

---



### Basic Query

#### SELECT

```sql
SELECT name FROM Tablenames;
```

> column_name : 컬럼 명
>
> Tablenames : table명

```sql
SELECT column_name1, column_name2, column_name3
FROM Tablenames;
```



colum 외에도 SELECT가능

```
SELECT column_name1, 1, "Hello", NULL
FROM Tablenames;
```

> 1 : number
>
> "Hello" : string
>
> NULL : 비어있는것을 의미



- `WHERE`

  조건문

  ```
  SELECT * FROM Tablenames:
  WHERE some_value = 3;
  ```

  > Tablenames안의 모든 columns중 some_value값이 3인 것 들만 SELECT



- `ORDER BY`

  정렬 (default : 오름차순)

  ```sql
  SELECT * FROM Tablename
  ORDER BY some_value;
  ```

  > some_value 값을 오름차순으로 정렬해서 출력 (ASC)

  ```sql
  SELECT * FROM Tablename
  ORDER BY some_value1, some_value2 DSEC;
  ```

  > some_value1, some_value2 값을 내림차순으로 정렬

  

- `LIMIT`

  가져올 row의 개수

  ```
  SELECT * FROM Tablename
  LIMIT 10;
  ```

  > 10개만 가져옴

  ```
  SELECT * FROM Tablename
  LIMIT 30 20;  -- 2개가 주어졌을 때
  ```

  > 앞의 30개를 건너 뛰고 20개만 가져옴



- `AS`

  column명을 다른 이름으로 변환해서 가져온다.

  ```
  SELECT 
   colum_name_1 AS foo,
   colum_name_2 AS bar,
   colum_name_3 AS 'buz'
  FROM Tablename;
  ```

  > Tablenames 안의 column_name_1는 foo라는 이름으로, column_name_2는 bar라는 이름으로,  column_name_3는 'buz'라는 **문자열** 로 가져옴



**예시**

```sql
SELECT 
 colum_name_1 AS 'fruit',
 colum_name_2 AS 'leaf',
 colum_name_3 AS 'flower'
FROM Tablename
WHERE location_id = 3 OR location_id = 4
ORDER BY device_id
LIMIT 0, 10;
```

> Tablename에서 location_id이 3 또는 4 인 것들을 device_id기준으로 오름차순 하여 상위 10개만 출력한다.
>
> 이 때  column_name_1는 fruit라는 **문자열**로, column_name_2는 leaf라는 **문자열**로,  column_name_3는 'flower'라는 **문자열** 로 가져온다.





#### Operater

- `+`, `-`, `*`, `/`, `%` : 각각 더하기, 빼기, 곱하기, 나누기, 나머지 

- boolean

  `True`, `1` : True

  `False` ,  `0` : False

- 논리 

  - `!`, `NOT` : inverse

    > ```sql
    > SELECT
    > !True,  -- output : 0
    > NOT 1, 	-- output : 0
    > !FALSE;  -- output : 1
    > ```

  - `=` : equal

  - `&&`, `AND`

  - `||`, `OR`

  - `IS`

  - `!=`

  - `<`, `>` , `<=`, `>=`

  ```sql
  SELECT 
  	column_name_1, column_name_2,
  	column_name_1 > 20 as tmp
  FROM tablename;
  ```

  > tablename에서 column_name_1, column_name_2을 출력한다. 
  >
  > 단, column_name_1 이 20보다 큰 경우 1을, 아닌 경우 0을 가진 column을  tmp라는 이름으로 하나 더 만들어 출력한다.

  

- `IN`

  list(괄호) 안의 값들 가운데 있는 경우 TRUE 반환

- `LIKE`

  ```sql
  SELECT
  	'HELLO' LIKE "hel%", -- 'HELLO' 가 hel을 포함하고 있다 임으로 True (== 1)
  	'HELLO' LIKE "hel__" -- 'HELLO' 가 hel다음에 두 글자 더 온다 임으로 1
  ```

  ```sql
  SELECT
  	'HELLO' LIKE 'H%O', -- 'HELLO' 가 H로 시작하고 O로 끝난다 임으로 1
  	'HELLO' LIKE 'H_O'; -- 'HELLO' 가 H와 O사이에 글자 한 개만 포함한게 아니기 때문에 0
  ```

  ```sql
  SELECT
  	'HELLO' LIKE '%O',  -- 'HELLO' 가 O로 끝난다 임으로 1
  	'HELLO' LIKE '_____' ; -- 'HELLO' 가 5글자 임으로 1
  ```

  ```sql
  SELECT
  	'HELLO' LIKE '%H', 			-- 0 반환
  	'HELLO' LIKE '%HELLO%';  	-- 0 반환
  ```

  ```sql
  SELECT * FROM Tablename
  WHERE columname_1 LIKE '%an';
  ```

  > Tablename에서 columname_1이 an으로 끝나는 문자열인 것만 출력

  ```sql
  SELECT * FROM Tablename
  WHERE columname_1 LIKE '%detection%';
  ```

  > Tablename에서 columname_1중 detection이라는 단어가 포함된 모든 row를 출력

  ```sql
  SELECT * FROM Tablename
  WHERE columname_1 LIKE '102_', -- columname_1 의 값이 1020번대 인 것들 출력
  WHERE columname_1 LIKE '10_5'; -- columname_1 의 값이 1005, 1015, ...1095 인 것들 출력
  ```

  > column_name_1 값이 숫자여도 문자열로 취급하여 SELECT가능





#### 숫자 관련 

- `ROUND` : 반올림

- `CEIL` : 올림

- `FLOOR` : 내림

  ```sql
  SELECT
  	ROUND(0.5),	-- 1
  	CEIL(0.4),	-- 1
  	FLOOR(0.6);	-- 0
  ```

- `ABS` : 절대값

- `GREATEST` : list안에서 가장 큰 값

- `LEAST` : list안에서 가장 작은 값

- `MAX` , `MIN`

- `COUNT` : 개수(NULL값 제외)

- `SUM`, `AVG` : 총합, 평균값

- `POW(A, B)`: A를 B만큼 제곱

- `SQRT` : 제곱근

- `TRUNCATE` : 값을 잘라냄

  ```sql
  SELECT
  	TRUNCATE(1234.5678, 1), 	-- 1234.5
  	TRUNCATE(1234.5678, 3),		-- 1234.567
  	TRUNCATE(1234.5678, -1),	-- 1230
  	TRUNCATE(1234.5678, -2);	-- 1200
  ```

  

  

#### 문자 관련

- `CONCAT` : 문자를 이어붙임

- `CONCAT_WS` : 문자 사이에 첫 번째 인자를 삽입하여 이어붙임

  ```sql
  SELECT 
  	CONCAT("my", " ", "number", " is ", 456), 	-- my nuber is 456 
  											 	-- 숫자는 문자로 변환
      CONCAT_WS?("_", "my", "number", "is", "456");
      -- my_nuber_is_456 
  ```

- `SUBSTR` 문자열을 특정 자리에 따라 잘라냄

- `LEFT`, `RIGHT` : 문자열을 왼쪽, 오른쪽부터 잘라냄

  ```sql
  SELECT 
  	LEFT("abcde", 3), 	-- abc  	왼쪽부터 3개만 출력
  	RIGHT("abcde", 2),	-- de		오른쪽부터 2개만 출력
  	SUBSTR("abcdefg", 4), 	-- efg  왼쪽부터 4개째부터 출력
      SUBSTR("abcdefg", 3, 2),	-- cd 왼쪽부터 3개째부터 2개만 출력
  	SUBSTR("abcdefg", -4),	-- defg 오른쪽부터 4개째부터 출력
  	SUBSTR("abcdefg", -4, 2);	-- de 오른쪽부터 4개째부터 오른쪽 2개만 출력
  ```

  ```sql
  SELECT
  	LEFT("2022-01-13", 4) as year,
  	SUBSTR("2022-01-13", 6, 2) as month,
  	RIGHT("2022-01-13", 2) as day;
  ```

- `LENGTH` : 문자열의 byte길이

- `CHAR_LENGTH` : 문자열의 문자 길이

- `TRIM` : 양쪽 공백 제거

- `LTRIM`, `RTRIM` : 왼쪽, 오른쪽 공백 제거

  ```sql
  SELECT
  	TRIM(" hello "),		-- 'hello'
  	LTRIM(" hello_ "),		-- 'hello_ '
  	RTRIM(" hello ");		-- ' hello'
  ```

- `LPAD`, `RPAD` : 왼쪽, 오른쪽에 이어붙임

  ```sql
  SELECT 
  	LPAD("abc", 5, '_'), 	-- __abc  # 5글자가 될 때까지 _ 를 왼쪽에 이어붙임
  	RPAD("ab", 7, 'ㅎ');		-- abㅎㅎㅎㅎㅎ # 7글자가 될 때까지 ㅎ 를 오른쪽에 이어붙임
  	
  ```

- `REPLACE` : 첫 번째 인자 안의 2번째 인자를 3번째 인자로 바꿈

  ```sql
  SELECT
  	REPLACE("내 이름은 겨울잠", "겨울잠", "hibernation");
  	-- "내 이름은 hibernation"
  ```

- `INSTR` : 문자열 안에 두 번째 인자가 있는지 확인 후 그 위치 출력

  ```sql
  SELECT
  WHERE	INSTR(columname_1, " ") BETWEEN 1 AND 6,
  	--  columname_1 의 1~6사이에 띄어쓰기가 있는 것들 출력
  WHERE	INSTR(columname_2, " ") BETWEEN 1 AND 10; 
  	--  columname_1 의 1~10사이에 띄어쓰기가 있는 것들 출력
  ```

- `CONBVERT` : 자료형 변경

  ```sql
  SELECT
  	"01" = "1", 	-- 두 문자열은 다름. 0 출력
  	CONVERT('01', DECIMAL) = CONVERT('1', DECIMAL)
  	-- 두 숫자는 같음. 1 출력
  ```

  > `DECIMAL` = 숫자 자료형



#### 시간, 날짜 관련

- `CURDATA` : 현재 날짜 반환

- `CURTIME` : 현재 시간 반환

- `NOW` : 현재 시간과 날짜 반환

  ```sql
  SELECT
  	CURDATA(), CURTIME(), NOW();
  ```

  



#### 조건 함수

- `IF(조건, A, B)` : 조건이 참이라면 A, 거짓이라면 B반환

  ```sql
  SELECT
  	IF(colum_name_1=colum_name_2, "두 컬럼은 같다", "두 컬럼은 다르다.");
  ```

- `CASE` : 여러 조건에 따라 출력

  ```sql
  SELECT
  CASE
  	WHEN colum_name_1 > 0 THEN "colum_name_1은 양수이다.",
  	WHEN colum_name_1 < 0 THEN "colum_name_1은 음수이다.",
  	ELSE "colum_name_1은 음수다"
  END;	
  ```

  > WHEN으로 나누고, THEN으로 결과를 표시하고, ELSE를 통해 예외를 출력한다.
  >
  > END로 CASE를 끝낸다.

- `IFNULL(A, B)`: A가 NULL인 경우 B출력

  



#### 기타

- `GROUP_BY` 값의 **종류**만 뽑아서 정렬하여 출력

  ```sql
  SELECT Column_name FROM Table_name_1
  GROUP BY Column_name;
  ```

  > Table_name_1에서 Column_name만 뽑아내는데,
  >
  > Column_name에서 겹치는 값이 없는, 종류만 뽑아서 출력한다.

  

  ```sql
  SELECT Column_name_1, Column_name_2
  FROM Table_name_1
  GROUP BY Column_name_1, Column_name_2;
  ```

  > 두 가지 컬럼 Column_name_1, Column_name_2을 기준으로 같은 종류가 없도록 뽑아서 출력한다.

  

  ```sql
  SELECT
  Column_name_1, SUM(Column_name_2) AS SUM_Column_2
  FROM Table_name_1
  	GROUP BY Column_name_1
  	ORDER BY SUM_Column_2 DESC;
  ```

  > Table_name_1에서 Column_name_1을 추려내고, 
  >
  > Column_name_2은 추려낸 뒤 그 값을 합친것을 SUM_Column_2이라 한다.
  >
  > Column_name_1의 종류에 따른 SUM_Column_2을 출력한다.(내림차순)

  - `WITH ROLLUP` :  숫자로 된 모든 값들을 row방향으로 SUM한다.

    > 단, `ORDER BY`와 함께 사용할 수 없음

    ```sql
    SELECT
    Colum_namen_1, SUM(Colum_namen_2) AS SUM_Column_2
    FROM Table_name_1
    	GROUP BY Colum_namen_1
    WITH ROLLUP;
    ```

  - `HAVING` : WHERE과 같다. 단, GROUP BY 로 인해 집계 된 data에만 사용된다.

    ```sql
    SELECT
    Colum_namen_1, SUM(Colum_namen_2) AS SUM_Column_2
    FROM Table_name_1
    	GROUP BY Colum_namen_1
    	HAVING SUM_Colum_2 > 30
    ```

    > Column_name_1의 종류에 따른 SUM_Column_2을 출력하는데, 이 때 SUM_Column_2가 30보다 큰 것만 출력한다.

- `DISTINCT` : `GRUOP BY`와 같지만, 정렬하지 않는다.(더 빠름)

  ```sql
  SELECT DISTINCT Column_name 
  FROM Table_name_1
  ```

  > Column_name을 중복되지 않는 것만 출력

  

  ```sql
  SELECT
  	Column_name,		-- Colum_name을 뽑아낸다.
  	COUNT(DISTINCT name)	-- name 을 종류별로 뽑아내고, 종류의 개수를 센다.
  FROM Table_name_1
  GROUP BY Columnn_name
  ```

  > 각 Column_name에 name의 종류가 몇 개씩 있는지 출력한다.





### SELECT 더 깊게

#### 비상관 Sub query

다중 SELECT일 때, FROM 이 각기 다른 상관관계를 맺고 있다고 할 때 비상관 Sub query라고 한다.

```sql
SELECT
 colum_name_1
 (SELECT colum_name_2 FROM table_2 WHERE SOMEID = 1)
FROM table_1
```

> 출력되는column
>
> - column_name_1
>
> - (SELECT column_name_2 FROM table_2 WHERE SOMEID = 1)





```sql
SELECT * FROM table_name_1
WHERE Price < (
    	SELECT AVG(Price) FROM table_name_1
	);
```

> Price가 AVG(Price)보다 큰 경우만 출력





#### 상관 Sub query

다중 다중 SELECT일 때, FROM 끼리 직접적 관계가 있을 경우 Sub query 라고 한다.

```sql
SELECT B.column_name_1, B.column_name_2,
	(
    SELECT A.columns_name_3 FROM table_1 A
    WHERE A.columns_name_2 = B.columns_name_2
   	)
FROM table_2 B;
```

> `FROM table_1 A` : table_1 을 A로 칭함
>
> `FROM table_2 B` : table_2 을 B로 칭함
>
> `WHERE A.columns_name_2 = B.columns_name_2` : table_1 안의 columns_name_2 과 table_2 안의 columns_name_2 가 같은 값을 가진 경우
>
> 위 구문에서 출력되는  column 
>
> - column_name_1, column_name_2, columns_name_3



위 예시 처럼 어떤 table에 별명(A 또는 B 처럼)을 붙인다면, 해당 table에 소속된 모든 column은 해당 table에서 나온 것임을 명시해주도록 하자.



- `EXIST` `NOT EXISTS` : 값이 존재하는 것 들만 출력(조건을 기준으로)

  ```sql
  SELECT B.column_name_1, B.column_name_2,
  	(
      SELECT MAX(A.price) FROM table_1 A
          WHERE A.columns_name_2 = B.columns_name_2
      ) AS Max_Price
  FROM table_2 B
  WHERE EXISTS (
  	SELECT * FROM table_1 A
      WHERE A.columns_name_2 = B.columns_name_2
      AND A.price > 80
  )
  ```

  > 위 구문에서 출력되는  column 
  >
  > - column_name_1
  > - column_name_2
  > - Max_Price
  >
  > 단, table_1의 price가 80이 넘어가고
  >
  > table_1 안의 columns_name_2 과 table_2 안의 columns_name_2 가 같은 값을 가진 경우만 출력함

### JOIN

어느 한 column을 기준으로, 두 테이블을 합치는 구문 (단, NULL이 있는 row는 아예 가져오지 않는다.)

```sql
SELECT * FROM table_1 A
JOIN table_2 B
	ON A.column_1 = B.column_1;
```

> table_1안의 column_1과 table_2안의 column_1은 원래 같은거지만, 다른 table에 속해 있다 >> 원래는 큰 table을 작은 table로 나눈 것인데. 이를 JOIN으로 다시 묶어주는 것.
>
> 두 테이블을 합쳐 출력한다.



```sql
SELECT 
	CONCAT(
    A.column_1, "by", B.column_1
    ) AS foo
    A.column_2, B.column_2
FROM table_1 A
JOIN table_2 B
	ON A.column_3 = B.column_3
WHERE B.price > 50
ORDER BY B.column_3;
```

> table A와 B를 합치고(column_3 기준으로), 그 중 몇 개만 SELECT한다.
>
> 위 구문에서 출력되는  column 
>
> `foo`, `A.column_2`, `B.column_2`



```sql
SELECT
	A.column_1, 
	B.column_2, 
	C.column_3,
	D.Column_4,
FROM table_1 A
JOIN table_2 B		-- A는  column_1을 기준으로 A, B를 합친 table
	ON A.column_1 = B.column_1
JOIN table_3 C		-- B는 column_2을 기준으로 B, C를 합친 table
	ON B.column_2 = C.column_2
JOIN table_4 C		-- C는 column_3을 기준으로 C, D를 합친 table
	ON C.column_3 = D.column_3;
```

> A 에 B를 합치고, B에 C를 합치고, C에 D를 합쳤다.
>
> 
>
> 위 구문에서 출력되는  column 
>
> `A.column_1`, `B.column_2`, `C.column_3`,  `D.column_4`
>
> 만일 `*` 로 표시했다면 A, B, C, D 모든 table의 column이 출력된다.



같은 table을 join하는 것도 가능

> column_1이 숫자(0~9)일 때

```sql
SELECT 
	A.column_1, B.column_2
FROM table_1 A	-- table_1 을 A라는 변수에 할당 
JOIN table_1 B  -- table_1 을 또 다른 B라는 변수에 할당
	ON A.column_1 +1 = B.column_2
```

> A.column_1, B.column_2의 (2~8) 만 가져온다. 



#### LEFT/RIGHT JOIN 

- `LEFT/RIGHT JOIN` 어떤 column을 기준으로 table을 합쳤을 때, NULL이 있는 table을 포함하여 가져온다. (방향에 따라서, NULL은 빈 칸으로)

  ```sql
  SELECT 
  	A.column_1, B.column_2
  FROM table_1 A
  LEFT JOIN table_1 B
  	ON A.column_1 +1 = B.column_2	-- LEFT JOIN이기 때문에, A.column_1 +1 기준
  ```



#### CROSS JOIN

조건 없이 모든 조합 반환





### UNION

합집합, 교집합 등 집합 기준으로 가져오는 함수 









