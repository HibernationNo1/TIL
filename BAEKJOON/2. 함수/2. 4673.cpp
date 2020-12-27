#include <iostream>
#include <string>
#include <vector>

using namespace std;

int d(int n)
{
	int s=0, sum = 0;
	string num = to_string(n);
	for (auto& x : num)
	{
		s = s + x - 48;      // x에 저장된 숫자를 문자로서 저장한 것. 아스키 코드 0 == 48   
    }
	sum = n + s;

	return sum;	
}

int main(void)
{
	vector<int> arr = {};    // 크기가 크고 cin으로 입력받을 필요가 없는 배열은 동적할당 vector
	arr.resize(9974);
	vector<int>  Nself_number = {};
	Nself_number.resize(10002);

	int Nself = 0;
	for (int i = 1; i <= 9973; i++)
	{
		arr[i] = i;     //1~9973
		Nself = d(i);     // N에 넘버를 할당. 최대 10001
		if (Nself < 10001)          // Nself가 10002를 넘어가는 숫자가 있을때를 대비
		{
			Nself_number[Nself] = 1;    //  n[넘버] 에 1;     . 최대 10000
		}
	}

	for (int i = 1; i <= 10000; i++)
	{
		if (Nself_number[i] == 0)       //  n[넘버] = 0이면 self number
		{
			cout << i << endl;
		}
		else
			continue;
	}

	return 0;
}