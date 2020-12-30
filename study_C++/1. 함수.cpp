#include <iostream>
using namespace std;

//함수 안에서 함수는 선언이 안된다.

int addTwoNumbers(int num_a, int num_b) // 2개의 숫자를 더하는 함수, 2개의 값을 받는 형태. 
// 이 때 num_a와 num_b는 매개변수라고 불린다.
{
	int sum = num_a + num_b;     // 함수가 int로 선언됐으니 int로 받는다.

	return sum;       // sum값을 리턴한다.
}

void printHellowWorld(void)  //얘는 main에 return해줄 값이 없는, 기능을 수행하는 함수
//void를 써준다
{
	cout << "Hellow World" << endl;

	// retrun; 을 써도 되고 안써도 문제 없다. 'void 함수' 형태이기 때문에
//void인데 함수가 int값을 받도록 하면 오류. 함수가 값을 받는다면 그 값의 형태(int든 뭐던)로 함수를 만들어야 한다.
}

int main(void)
{
	int x;
	x = 123;
	cout << 1 + 2 << endl;
	cout << addTwoNumbers(1, 2) << endl;  // 함수에 들어가는 값 1, 2는 인수라고 불린다
	cout << x << endl;
	cout << x + 4 << "\t 값 \n";
	cout << 8 + 13 << endl;
	printHellowWorld();
	return 0;
}