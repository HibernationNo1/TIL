# List

- 노드 기반 컨테이너로, 순서를 유지하는 구조다.
- **double linked list**와 구조가 같다.

- vecotr, deuqe과는 다르게 정렬(sort, merge), 이어붙이기(slpice)를 사용할 수 있다.
- insert(), erase() 멤버 함수를 통해서 노드 중간에서도 삽입, 삭제가 가능하다.
- 원소를 탐색할때 임의접근 반복자(ar[], [])는 불가능하고, 양방향 반복자(++, --) 를 이용해서 탐색한다.

**선언의 기본**

```c++
#include<list>  //헤더파일 필수

list foo;  //foo라는 list 생성  
list foo(10);  //원소 10개를 가진 foo라는 list 생성  (원소의 default값: 0)
list foo(3, 2); //2값으로 초기화 된 원소 3개를 가진 list 생성
list bar(foo);  // foo라는 list를 bar라는 list에 복사

//어떠한 배열을 list에 넣을 때
string s;
cin >> s; 
list<char> str(s.begin(), s.end());  // list<자료형> 이름(배열의 시작주소, 끝 주소)

// 아래는 list의 begin과 end를 선언하는 코드
// list<int>::iterator 대신 auto를 사용해도 된다.
list<int>::iterator iter1 = str.begin();  
//<자료형>은 할당받을 list의 자료형과 동일해야한다.
// foo라는 이름을 가진 list의 시작 주소를 iter1이라는 변수에 할당
list<int>::iterator iter2 = str.end();
// 이건 마지막 노드를 가리키는 것이 아닌, 마지막 주소임. 마지막 주소 -- 가 마지막 노드를 가리키고 있음


/*세 번째 노드에 접근할 때
foo.insert(begin()+2)  이건 안됨
대신 위에서 선언한 포인터를 사용
단, foo.insert(iter1+2) 이건 안됨. 노드 하나 씩 옮겨야함.

즉, 
iter1++;
iter1++;
foo.insert(iter1);  이런 식으로 접근해야 한다.
*/

cout << *iter1 << endl;  //  str의 첫 번째 노드의 값 출력
iter++;
cout << *iter1 << endl; // str의 두 번째 노드의 값 출력
```



**관련 메서드**

- foo.front() 처럼 마침표 `.`를 사용해서 함수 호출

- assign, front, back, begin, end, size  사용 가능

-  push_back(m), push_front(m), pop_back(), pop_front() 사용 가능

  > m이라는 값이 있을 때

- insert(), erase()

  > insert()함수는 지금 위치의 노드를 다음 원소로 밀어내고, 새 노드를 삽입한다.
  >
  > erase 하고 나서의 주소 iter은 그 자리에 존재 (어딘지 모를 곳).
  >
  > erase() 함수는 원소를 삭제한 후 삭제된 위치에 채워진 다음 원소의 주소를 반환하기 때문에
  >
  > iter = str.erase(iter); 을 통해 노드의 위치를 잃어버리지 않아야 한다.

- remove(k)

  > k와 같은 원소를 모두 제거

- reverse(), sort()

- foo.swap(bor)

- lt2.splice(iter2, lt1)
  >
  > * lt2에서 iter2이 가리키는 곳에 lt1의 모든 원소를 잘라 붙인다.
  > * lt2.splice(iter2, lt1, iter1) : lt2의 iter2가 가리키는 곳에 lt1의 iter1이 가리키는 원소를 잘라 붙인다.
  > *  lt2.splice(iter2, lt1, iter1_1, iter1_2) : lt2의 iter2가 가리키는 곳에 lt1의 [iter1_1 , iter1_2) 까지의 원소를 잘라 붙인다.

