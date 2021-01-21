# numeric_limits

해당 타입의 표현 한계치를 확이할수 있는 방법이다.



**ex) **`numeric_limits(타입)::**최대** 또는 **최소**()`

```c++
numeric_limits(int)::max();     //  int 형 변수의 최대 표현가능 숫자를 리턴
numeric_limits(int)::min();      //  int 형 변수의 최소 표현가능 숫자를 리턴
```

```c++
#include <iostream>
#include <limits>
using namespace std;

int main()
{
 cout<<"int 형 최대 :"<< numeric_limits<int>::max()<<endl;
 cout<<"int 형 최소 :"<< numeric_limits<int>::min()<<endl;
 cout<<"double 형 최대 :"<<numeric_limits<double>::max()<<endl;
 cout<<"double 형 최소 :"<<numeric_limits<double>::min()<<endl;
 cout<<"long 형 최대 :"<<numeric_limits<long>::max()<<endl;
 cout<<"long 형 최소 :"<<numeric_limits<long>::min()<<endl;
 cout<<"unsigned int 형 최대 :"<< numeric_limits<unsigned int>::max()<<endl;
 cout<<"unsigned int 형 최소 :"<< numeric_limits<unsigned int>::min()<<endl;

 return 0;
}
```

