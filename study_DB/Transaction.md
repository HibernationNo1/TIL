# Transaction

database내에서 수행되는 작업의 최소 단위

> 예시
>
> 은행 업무에서 A가 B에게 송금을 할 때 
>
> 1. A의 계좌에서 출금
> 2. B의 계좌로 입금
>
> 위 동작이 이루어져야 한다.
>
> 만일 위 동작 중 하나라도 이루어지지 않는 경우는 큰 문제가 발생할 수 있는데, 이를 예방하기 위해 두 동작을 하나로 묶어버리는 것이 더욱 안전하다. 
>
> 이러한 것 처럼, 여러 행위를 분리할 수 없는 하나의 행위로 이루어지는 것을 **단일 업무**라 하며 업무의 최소 단위로 정의된다.
>
> 이를 Transaction이라고 한다.

database의 무결성을 유지하며 BD상태를 변화시키는 기능을 수행한다.

> 무결성
>
> database에 저장된 data의 일관성과 정확성을 지키는 것

Transaction은 하나 이상의 query를 포함해야 하고, ACID라 칭해지는 **원자성**, **일관성**, **고립성**, **지속성**의 4가지 규칙을 만족해야 한다.



## ACID

- Atomicity(원자성)

  Transaction에 포함된 작업은 전부 수행되거나 아니면 전부 수행되지 말아야 한다.

- Consistency(일관성)

  Transaction이 실행을 성공적으로 완료하면 언제나 일관성 있는 database상태로 유지한다.

  > 송금 전 후의 data type은 interger이여야 한다는 것

- Isolation(고립성)

  여러 Transaction은 동시에 수행될 수 있다.

  이 때 각 transaction은 다른 transaction의 연산 작업이 끼어들지 못하도록 보장하여 독립적으로 작업을 수행한다.

  따라서 동시에 수행되는 transaction이 있더라도 동일한 data를 가지고 출돌하지 않도록 제어해줘야 한다.

- Durability(지속성)

  성공적으로 수행된 transaction은 database에 영원히 반영되어야 함을 의미한다. transaction이 완료되어 저장이 된 database는 저장 후에 생기는 정전, 장애, 오류 등에 영향을 받지 않아야 한다.



## concurrency control

동시성 제어

여러 개의 transaction이 한 개의 data를 동시에 update한다면, 어느 한 transaction의 갱신이 무효화 될 수 있다. 이를 갱신손실이라고 하는데, 이러한 갱신손실을 막는 것을 concurrency control이라고 한다.

- transaction이 동시에 수행될 떄 일관성을 해치지 않도록 transaction의 date 접근을 제어하는 DBMS의 기능이다.



## Commit, Rollback

database는 데이터 무결성을 보장하기 위해 commit과 rollback명령어를 수행한다.

**Commit**

transaction작업을 완료했다고 확정하는 명령어.

transaction작업 내용을 실제 DB에 저장한다.

**Rollback**

transaction작업 중 문제가 발생했을 때 처리 과정에서 발생한 변경 사항을 취소하고 이전의 commit상태로 되돌린다.





## Deadlock