# Linked List

### 1. 특징

- 노드의 동적 할당과 포인터를 기반으로 구현되기 때문에 필요로 하는 메모리의 크기에 유연하게 대처가 가능하다.

- 불연속적 메모리 공간에 저장하기 때문에 공간의 낭비가 없다.

- 각 원소는 노드(Node) 라고 부르며 List의 모양은 각 노드를 연결된 형태다.

  > - 첫번째 노드를 헤드(Head, 머리), 마지막 노드를 테일(Tail, 꼬리)이라고 함.
  > - 각 노드는 데이터와 다음 노드(이전에 생성된 노드)를 가리키는 포인터로 이루어짐.

- 크기가 고정되어 있지 않다.

- index를 바로 참초가 불가능하고 노드들의 순서를 통해 원하는 노드에 도달할 수 있다. 



###  2. 구현

- **Node의 구조를 구현해보자**

```c++
class Node         // Node 라는 class를 생성해서 Node 자체를 구현
{
public:
	int data; 	 // 데이터 저장 공간		멤버 변수  char, string
	Node* next;  // 다음 노드의 연결을 위한 포인터  
};  
```

> - `int data;` : 노드 안에 데이터를 저장하는 공간이다. 
>
>   > 노드에 어떠한 타입의 데이터를 저장할 것인지에 따라 int, char, string 자유롭게 선언 가능
>
> - `Node* next;` : 이전에 생성된 노드. 즉, 다음 노드의 주소를 저장하는 공간이다.
>
>   > Node라는 class의 주소값을 저장할 수 있는 변수이기 때문에 역참조 연산자`*` 사용. 
>   >
>   > 반드시 `class이름 *변수명` 형식으로 만들어야함.

- **Node 전체를 이루는 List 구현**

```c++
class List     // List라는 class를 생성해서 노드 전체의 구조를 구현
{
public:
	Node* LinkHead;			
	Node* tailPoint;
    
    List()   // 기본 생성자  tail이 ->를 통해 값을 할당받으면 그 때 실행됨
	{
		LinkHead = NULL;      
		tailPoint = NULL;
	}
// ---(아래 이어짐)---
```

> 일단 노드의 주소를 담을 저장소가 두 개 필요하다. (추가 설명은 아래에서)
>
> - `Node* LinkHead;`, `Node* tailPoint;`  :  각 Node의 주소를 담을 그릇. 
>
>   >  `Node* LinkHead`는 다음 노드의 주소를, `Node* tailPoint`는 지금 현재 노드의 주소를 담을 예정
>
> - `List()` :  기본 생성자
>
>   > - 아래에서 선언 될 `tail`이 `->`를 통해 값을 할당받으면 그 때 실행됨
>   >
>   > - 위에서 선언 된 `LinkHead = NULL;` , `tailPoint = NULL;` 를 초기화 시킨다.
>   >
>   > - 이 초기화는 최초 한 번만 실행됨.
>   >
>   > - 두 번째부터는 '이전에 만들어졌던 노드'의 주소가 들어가게 됨 (동작은 아래에서)
>
>
>   **노드를 만드는 함수 구현**
>
> ```c++
> //---(위에서 이어서)---
> 
> void CreatNode(int data)    // 새 노드를 만드는 List라는 class의 멤버 함수 CreatNode (매개변수 == 데이터)
> 	{
> 		Node* tail = new Node;   
> 
> 		tail->data = data;        
> 		tail->next = LinkHead;     
> 
> 		LinkHead = tail;		
> 	}
> 
> // ---(아래 이어짐)---
> ```
>
> - `Node* tail = new Node;` : 새로운 노드 하나 만드는 코드.  이 노드는 마지막(맨 뒷부분)에 위치한다.
>
>   > - List class에서 Node 라는 class의 변수를 선언할 때 `Node *변수명  = new Node`  으로 선언한다. (동적할당)
>   >
>   > - `class이름 변수명;` 으로 선언하면 시작마자마자 바로 List class 의 생성자가 실행되버림
>   > - 새로운 노드가 만들어지면 List의 가장 뒤쪽에 위치하기 때문에 tail이라는 명칭 사용
>   
> - `tail->data = data;` : 생성된 노드에 매개변수로 받아온 data를 넣음
>
>   > Node class의 멤버변수 `data`를 활용해, 받아온 매개변수 값을 노드의 `data`라는 저장소에 할당. 
>
> - `tail->next = LinkHead;` : 생성된 노드의 주소에 이전에 생성된 노드의 주소를 넣음
>
>   > - Node class의 멤버변수 `next`를 활용해, 지금 노드의 `next` 라는 저장소에 다음 노드의 주소를 저장함 
>   >
>   > - 여기서 `next`는 다음 노드의 연결을 위한 포인터역할
>   >
>   > - 처음 노드가 만들어지는 순간  `LinkHead == NULL` 임.
>
> - `LinkHead = tail;` : LinkHead에 (다음차례를 위해)  tail의 주소(지금 노드의 주소)를 저장.
>
> **List를 출력하는 함수 구현**
>
> ```c++
> //---(위에서 이어서)---
> 
> void PrintAll()     // 출력하는 함수 
> 	{
> 		tailPoint = LinkHead;    
>     
> 		while (tailPoint->next != NULL)  
> 		{   
> 			cout << tailPoint->data << " -> ";  
> 			tailPoint = tailPoint->next;    
> 		}  
> 		cout << tailPoint->data << endl; 
> 	}
> 
> //---(아래 이어서)---
> ```
>
> - `tailPoint = LinkHead;` : `LinkHead`를 복사해서 사용.
>
>   > 일단  `LinkHead`를 그냥 하나 더 복사한다고 생각해두면 됨.
>   >
>   > `LinkHead` 에는 마지막에 생성된 노드의 주소가 들어있다.
>
> - `while (tailPoint->next != NULL)` :  next 가 NULL이면 true (다음 주소가 있으면 반복)
>
>   >  Node class의 next 가 NULL이면 flase. 동작 멈춤.
>   >
>   > 즉, 지금 노드에서 '이전에 생성된 노드'의 주소를 봤는데 아무것도 없을 때 == 다음노드가 없다. 
>   >
>   > 데이터가 비어있는 노드가 있어도 Head 노드까지 다 탐색함
>   >
>   > - `cout << tailPoint->data << " -> ";` : 지금 노드에 저장된 data를 출력
>   > - `tailPoint = tailPoint->next;` :  지금 노드의 주소가 있던 저장소에 '이전에 생성된 노드'의 주소를 할당 (비어있는 곳 까지 계속 찾아들어가기 위해)
>
> - `cout << tailPoint->data << endl;` : 현재 data 출력
>
> **List를 탐색해서 비어있는 Node가 있는지 확인하는 함수 구현**
>
> ```c++
> //---(위에서 이어서)---
> 
> void FindEmpty()     // 탑색하는 함수
> 	{
> 		tailPoint = LinkHead;    
>     
> 		while (tailPoint->data != NULL)  
> 		{   
> 			// cout << tempPoint->next << " -> ";  요건 필요 없음
> 			tailPoint = tailPoint->next;    
> 		}  
> 		cout << tailPoint->next << endl;   // 데이터가 없는 Node의 주소 출력
> 	}
> 
> };
> ```
>
> - 위의 출력하는 함수 `void PrintAll()` 의 코드에서  
>
>   `while (tailPoint->next != NULL)` ->  `while (tailPoint->data != NULL)`
>
>   만 바꾸면 됨
>
>   >  Node class의 data 가 NULL이면 flase. 동작 멈춤. (다음 데이터가 있으면 반복)

- **main 함수**

```c++
int main(void)
{
	List* number = new List();  // 동적할당으로 number라는 객체 생성
    							// 이 객체가 곧 Linked List

	number->CreatNode(1);  // 첫 노드 생성, 1이라는 data 저장
	number->CreatNode(2);
    number->CreatNode(33);
    number->CreatNode(48);
    number->CreatNode(100);	// 마지막 노드 생성, 100이라는 data 저장

	number->PrintAll();  // 비어있는 노드가 있는지 확인

	return 0;
}
```



