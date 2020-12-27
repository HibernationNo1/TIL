#include <iostream>
#include <vector>

using namespace std;

int main(void)
{
	int* my_arr = new int[10];		// 배열 동적할당
	delete my_arr;					// 동적할당을 하면 반드시 delete해줘야 한다.
	// cin으로 배열의 갯수를 받아서 할당할때 용이

	vector<int> arr1 = { 1, 2, 3, 4, 5 };	// vector함수는 동적할당임. 자기가 알아서 delete해준다.
	// 형태: vector<자료형> 배열이름 
	cout << arr1.size() << endl;				// 5개 원소 할당됨을 확인


	vector<int> arr2 = { 1,2,3 };
	for (auto& n : arr2)  // 자동으로 arr2의 원소 n회 만큼 실행 / new를 사용한 동적할당 된 배열은 사용불가
	{
		cout << n << " ";  // arr2[0] 부터 마지막 원소까지 차례로 출력
	}
	cout << endl;

	arr2.resize(10);  // arr배열의 원소 갯수를 10개로 다시 지정. 값이 없는 원소는 0으로 자동 초기화
	for (auto& n : arr2)
	{
		cout << n << " ";  
	}
	cout << endl;
	
	arr2.resize(2);  // arr배열의 원소 갯수를 3개로 다시 지정
	for (auto& n : arr2)
	{
		cout << n << " ";      // 2개 출력. 단, 메모리가 지워진건 아님. 출력만 2개 될 뿐
	}
	cout << endl;
	
		return 0;
		
}