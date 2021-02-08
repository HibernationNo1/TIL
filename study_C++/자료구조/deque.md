# deque

### 개념

덱은 double-ended queue의 줄임말으로, 큐의 앞, 뒤 모두에서 삽입 및 삭제가 가능한 큐를 의미한다. (중간에서 삽입, 삭제가 불가능)

deque는 vector의 단점을 보완하기 위해서 만들어진 container 로, vector와 마찬가지로 배열기반의 구조다.

> vector는 새로운 원소가 추가 될때 메모리 재할당 후 이전 원소를 복사하는 방식으로 인하여,  삽입시에 성능이 저하 하는 단점이 있음.
>
> deque는 이러한 vector의 단점을 보완하기 위해서 여러개의 메모리 블록을 할당하고 하나의 블록처럼 여기는 기능을 제공. (deque는 메모리가 부족할때 마다 **일정한 크기의 새로운 메모리 블록을 할당**)

![](https://postfiles.pstatic.net/MjAxOTA0MThfMjcx/MDAxNTU1NTMxOTk3NjM1.5AEXPRQeNYX8dxSzgTCiATI-xprr8WIQY52DVXk91_gg.lgVBOfBws5gg9nYlLEuotRHLLQv-exifkTNPxdb06YUg.PNG.sooftware/anod.png?type=w773)

###  선언 

**형태**: deque<타입> 변수이름;

```c++
#include<iostream>
#include<deque> // 헤더파일 포함

deque<int> deq;  //비어있는 덱 생성
deque<int> deq(10);  // 0의 값을 가진 10개의 원소를 가진 덱 생성
deque<int> deq(-100, 10); // -100의 값을 가진 10개의 원소를 가진 덱 생성
```



### 멤버 함수

- `deq.[idx]` : idx번째 원소를 참조

- `deq.front()` : 첫 번째 원소를 참조

- `deq.back()` : 마지막 원소를 참조

- `deq.begin()` : 첫 번째 원소를 가리킴

- `deq.end()` : 마지막 원소를 가리킴

- `deq.push_front(3)` : deq의 첫 번째 원소 앞에 3의 값을 가진 원소 삽입

- `deq.push_back(3)` :  deq의 맨 뒤에 3의 값을 가진 원소 삽입

- `deq.clear()` : 모든 원소를 제거

- `deq.pop_front()` : deq의 첫 번째 원소 삭제

- `deq.pop_back()` : deq의 마지막 원소 삭제

- `deq.resize(n)` : 크기를 n 으로 변경

  > 만약 크기가 더 커졌을 경우 비어있는 원소를 default값인 0으로 초기화
  >
  > deq.resize(n, 2) : 만약 크기가 더 커졌을 경우 비어있는 원소를 2로 초기화

- `deq.size()` : 원소의 개수 리턴

- `deq.swap(deq2)` : deq과 deq2를 바꾸어 줌. (swap)

- `deq.insert(begin() + 2, 3)` : 2+1번째 위치에 3의 값을 삽입
- `deq.erase(deq.begin()+n)` : n+1 번째 원소 제거
- `deq.empty()`: deq가 비어있으면 1 반환