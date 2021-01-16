# forward_list

단방향 연결 리스트 형태로, single linked list 자료구조를 이용하여 만든 시퀀스 컨테이너다.

각 요소는 그 다음 요소를 가리키는 포인터를 하나만 가지고 있다.

원소를 하나 씩 추가한다면, 반복자가 가리키는 원소 앞에 추가할 수 없고 뒤에만 원소를 추가할 수 있다.(역방향 반복자를 지원하지 않음)

양방향 연결 리스트인 std::list 보다 메모리를 적게 사용하고 삽입/삭제 속도가 빠르다. 

한 방향으로만 이동할 수 있으며, 삽입과 삭제는 지정한 요소의 다음 요소에 한해서만 가능하다.

> 관련 자료구조
>
> [자료구조에 관하여](https://github.com/HibernationNo1/TIL/blob/master/Data_structure/%EC%9E%90%EB%A3%8C%EA%B5%AC%EC%A1%B0%EC%97%90%20%EA%B4%80%ED%95%98%EC%97%AC.md)
>
> [Linked List](https://github.com/HibernationNo1/TIL/blob/master/Data_structure/Linked%20List.md)





### **문법**

```
forward_list<타입> 객체 = {};
```

> size 함수를 제공하지 않기 때문에 길이를 구하려면 distance(list.begin(), list.end())로 구한다.
>
> insert와 erase를 제공하긴 하는데, 성능이 너무 좋지 않다.

**예시 1.**

```c++
int main()
{
forward_lsit<int> list1 = {23, 1, 4, 0, };
}
```

**예시 2.**

```c++
class Foo
{
    public:   // Foo 타입으로 바로 할당하기 위해서는 public 선언해야됨
    string name;
    int age;
}

int main()
{
    forward_lsit<Foo> list1 = { {"Kim", 23}, {"Lee", 25}, {"park", 18}, {"jin", 16} };
}
```

**예시3**

```c++
#include <iostream>
#include <string>
#include <forward_list>

using namespace std;

class Citizen
{
public:

	string name;
	int age;
	
};

ostream& operator<<(ostream& os, const Citizen& c)
{
	return ( os << "[" << c.name << ", " << c.age << "]");
}

int main()
{
	int num;
	cout << "등록할 시민의 숫자를 입력: ";
	cin >> num;
	forward_list<Citizen> citizens = {};

	for (int i = 0; i < num; i++)
	{
		string name;
		int age;
		cout << i + 1 << "번째 시민의 이름과 나이를 입력: ";
		cin >> name >> age;
		citizens.push_front({ name, age });
        // .push_front() 사용. 아래 설명 참고
	}
	
	
	auto citizens_copy = citizens;  // 얕은 복사
	cout << "전체 시민들: ";
	for (const auto& c : citizens)
	{
		cout << c << " ";
	}
	cout << endl;

	citizens.remove_if([](const Citizen& c) { return(c.age < 19);  });
    // .remove_if() 사용. 아래 설명 참고
	cout << "투표권이 있는 시민들: ";
	for (const auto& c : citizens)
	{
		cout << c << " ";
	}
	cout << endl;

	citizens_copy.remove_if([](const Citizen& c) {return (c.age != 18); });
	cout << "내년에 투표권이 생기는 시민들: ";
	for (const auto& c : citizens_copy)
	{
		cout << c << " "; 
	}
	cout << endl;
}
```

> `객체.push_front(index)`를 통해서 데이터를 하나 씩 저장할 수 있다.
>
> `객체.remove_if()`를 통해 조건자를 충족하는 요소를 정방향 목록에서 지운다.



### 메서드

```c++
forward_list<int> list = {1, 2, 3};
```

위 객체가 선언되었다고 가정하고,

- `list.push_front(0)` :  맨 앞에 정수 0 추가 {0, 1, 2, 3}
- `list.pop_front()`: 맨 앞에 원소 삭제 

- `list.begin()` : 리스트 첫 번째 원소의 주소
- `list.insert_after(list.begin() + 2, 5)` : 맨 처음 + 2번째(3번째) 원소 뒤에 5 추가
- `list.erase_after(list.begin() + 3)` :  4번째 원소를 삭제
- `list.erase_after(list.begin(), list.end())` : 전체 원소 삭제