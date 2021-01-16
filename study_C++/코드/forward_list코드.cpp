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
	}
	
	
	auto citizens_copy = citizens;  // 객체 얕은 복사
	cout << "전체 시민들: ";
	for (const auto& c : citizens)
	{
		cout << c << " ";
	}
	cout << endl;

	citizens.remove_if([](const Citizen& c) { return(c.age < 19);  }); // 람다함수 [] 나중에 공부
	
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