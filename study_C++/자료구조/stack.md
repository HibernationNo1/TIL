# STACK

first in first out 구조



```c++
#include<stack>

stack<int> sta;

sta.push(3);  	// top에 3이라는 값 추가
sta.push(2);	// top에 2이라는 값 추가

sta.top();		// top에 있는 값 반환
sta.pop(); 		// top에 있는 원소를 삭제

sta.empty();	// stack이 비어있으면 1, 아니면 0을 반환
sta.size();		// sta의 사이즈 반환
```

