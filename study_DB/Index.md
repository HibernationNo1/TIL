# Index

Btree, B+tree, Hash, Bitmap 등으로 구현되는 자료구조.

RDBMS(관계형 DB)에서 index를 사용하여 더욱 빠른 검색을 할 수 있다.

`SELECT ~ WHERE` query를 통해 특정 조건을 만족하는 data를 찾을 때 ,full table scan을 하지 않고 정렬되어있는 index에서 훨씬 빠른 속도로 검색을 할 수 있다.

>  index는 B+Tree자료구조로 이루어져 있어, Where조건과 일치하는 data들의 저장위치를 빠르게 찾을 수 있다.

**index를 사용하는 이유**

- table보다 적은 공간을 차지

  index를 생성하게 되면 특정 column의 값을 기준으로 정렬하여 data의 물리적 위치와 함께 별도 file에 저장한다.

  이 때 저장되는 속성 값을 search-key값이라고 하고, 실제 데이터의 물리적 위치를 저장한 값을 pointer라고 한다.

  index는 순서대로 정렬된 search-key값과 pointer값만 저장하기 때문에 table보다 적은 공간을 차지한다.

- 조건 검색 `SELECT ~ WHERE` 을 통한 검색 속도가 굉장히 빠르다

  table에 지속적으로 data를 저장하게 되면 내부적으로 순서 없이 쌓이게 되는데, 이 경우에 `WHERE`절을 사용해 data를 검색하면 table의 row를 처음부터 끝까지 모두 접근하여 검색조건과 일치하는지 비교하는 과정이 수행된다. (Full Table Scan)

  하지만 특정 column에 대한 index를 생성해 놓은 경우 해당 column에 대하여 srearch-key가 정렬되어 저장되어 있기 때문에 조건 검색 속도가 굉장히 빠르다.

**단점**

- 추가 저장공간 필요

  index를 생성하면 index자료구조를 위한 저장 공간이 추가적으로 필요하다.

  보통 table크기의 10%정도의 공간 차지

- data번경 작업이 느리다.

  `INSERT`, `UPDATE`, `DELETE`가 자주 발생하면 성능이 나빠질 수 있다.

  B+Tree구조의 index는 data가 추가 또는 삭제될 때마다 tree의 구조가 변경될 수 있기 때문.

  ​		

#### clustering index

특정 column을 promary key로 지정하면 자동으로 clustering index가 생성되고, table내용 자체가 해당 column기준으로 정렬이 된다.

> clustering index의 srearch-key가 promary key로 결정된 column인 것.



#### secondary index

일반 책의 `찾아보기`와 같이 별도의 공간에 index가 생성된다.

`create index`의 명령을 수행하거나 고유키(unique key)로 지정하면 secondary index가 생성된다.

```
CREATE INDEX idx_name ON table_name (column);
```

> `table_name`이라는 table의 특정 column에 대한 index생성
>
> 해당 column이 srearch-key이고, 해당 key값에 의한 정렬이 된 index table이 하나 만들어진다.





### Q

**어느 Column에 사용하는 것이 좋은가?**

- 자주 조회되는 column
- 수정 빈도가 낮은 column
- data 중복이 적은 column
- data의 양이 많은 경우
- 한 table에 index가 너무 많으면 data수정시 소요되는 시간이 너무 길어질 수 있다.



**b+tree의 시간복잡도는 O(logn)이고, hash table의 시간복잡도는 O(1)으로 더 빠른데 왜 index는 b+tree로 구현되었나?**

hash table은 값이 정렬되어있지 않기 때문에 부등호를 사용하는 query에 대해서는 매우 비효율적이다.

> 하나의 값만 검색할 경우 hash table이 더 나을 수 있지만, 일정 범위 값들을 찾을 때는 b+tree가 적합하다.



**b+tree**

- 항상 정렬된 상태를 유지하여 부등호 연산(query문)에 유리하다
- search뿐 아니라 저장, 수정, 삭제에도 항상 O(logN)의 시간 복잡도를 갖는다.