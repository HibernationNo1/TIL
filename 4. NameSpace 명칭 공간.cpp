#include <iostream>
using namespace std;
// 같은 이름을 가졌지만 다른 기능을 가진 함수를 사용해야 할 때 namespace를 사용한다.
namespace MySpace
{
	namespace innerSpace  // namespace안에 또 다른 namespace를 만들 수 있다.
	{
		int my_function()
		{
			return 0;
		}
	}
	int doSomething(int a, int b)
	{
		return a + b;

	}
}

//namespace MySpace2
//{
int doSomething(int a, int b)
{
	return a * b;

}
//}
int main()
{


	cout << doSomething(3, 4) << endl;  // 곱하기의 doSomething이 실행이 된다
	cout << MySpace::doSomething(3, 4) << endl; // MySpace안의 doSomething이 실행이 된다.
	cout << MySpace::innerSpace::my_function(); // MySpace안의 innerSpace안의 my_function();을 사용할 때

	// using namespace MySpace;  // using namespace 를 사용하면 
	// doSomething(3, 4);        // MySpace::을 생략할 수 있다.
	// 단, 모든 doSomething이 namespace안에 존재할때만 가능.
	// 하나의 doSomething이라도 namespace 밖에 선언되어 있다면 using namespace을 사용했을 때 오류 발생
	// 

}
