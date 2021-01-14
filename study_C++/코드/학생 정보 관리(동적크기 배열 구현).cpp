#include <iostream>
#include <algorithm>   
#include <string>
#include <sstream>

using namespace std;
template <typename T>

class DynamicArray
{
private:
	T* data;
	int n;

public:


	DynamicArray(int n)   //기본 생성자
	{
		this->n = n;
		data = new T[n];
	}
	DynamicArray(const DynamicArray<T>& other)   // 깊은 복사 생성자
	{
		n = other.n;    // 객체의 멤버변수n 복사
		data = new T[n];	  // data의 포인터를 힙에 저장된 배열로 향하게 만듦

		for (int i = 0; i < n; i++)   //데이터 배열 각 원소 복사
		{
			data[i] = other[i];   //[]연산자 오버로딩 호출
			// T data.operator[](i) = const T other.data.operator[](i)
		}
	}


	T& operator[](int index)   // 위 data[i] = other[i]; 에서 촤즉변에 사용됨
	{
		return data[index];
	}

	const T& operator[](int index) const  // 위 data[i] = other[i]; 에서 우측변에 사용됨
	{
		return data[index];
	}

	T& at(int index)  //예외처리를 위한 함수
	{
		if (index < n)
		{
			return data[index];
		}
		throw ("Index out of range");
	}


	int size() const  // 단순 n를 리턴하기 위한 함수
	{
		return n;
	}

	~DynamicArray()  //소멸자
	{
		delete[] data;
	}

	T* Begin() { return data; }  // data 배열의 첫 번째 주소 복사
	const T* Begin() const { return data; }  //operator+ 함수의 첫 번째 매개변수 객체에서 호출될 함수
	T* End() { return data + n; }		// data 배열의 n번째 주소 복사
	const T* End() const { return data + n; }	//operator+ 함수의 첫 번째 매개변수 객체에서 호출될 함수

	friend DynamicArray<T> operator+(const DynamicArray<T>& arr1, DynamicArray<T>& arr2)  // + 연산자 오버로딩
	{		//객체를 매개변수로 가져오고 클래스 내부에서 정의되었으니 friend 적용
		DynamicArray<T> result(arr1.size() + arr2.size());
		copy(arr1.Begin(), arr1.End(), result.Begin());
		copy(arr2.Begin(), arr2.End(), result.Begin() + arr1.size());
		return result;
	}



	string to_string(const string& sep = ", ")
	{
		if (n == 0)
		{
			return "";
		}

		ostringstream os;				//ostringstream클래스 객체 os생성, <sstream> 포함 필요
		os << data[0]; 

		for (int i = 1; i < n; i++)
		{
			os << sep << data[i];		// so << sep은 string으로 바로 대입후 os로 리턴
		}								// os << data[i] 연산자 오버로딩 
		return os.str();				// os에 대입된 문자열 리턴 <sstream> 포함 
	}

	

};

class student
{
public:
	string name;
	int standard;
};

ostream& operator<<(ostream& os, const student& s)	// << 연산자 오버로딩
{													// 객체가 호출하는것이 아니기 때문에 전역위치에서 정의
	return (os << "[" << s.name << "," << s.standard << "]");
}


int main(void)
{
	int nStudents;
	cout << "1반 학생 수를 입력하세요:";
	cin >> nStudents;

	DynamicArray<student> class1(nStudents);  //class1객체 생성 (구분은 DynamicArray<student>타입, 실제 용도는 student타입
	for (int i = 0; i < nStudents; i++)
	{
		string name;
		int standard;
		cout << i + 1 << "번째 학생 이름과 나이를 입력하세요: ";

		cin >> name >> standard;
		class1[i] = student{ name, standard };  
		// student타입 = student타입이기 때문에 = 는 연산자 오버로딩 아님
	}

	try  
	{
		class1.at(nStudents);  
	}
	catch (...)  //모든 예외를 받는 문법
	{
		cout << "예외 발생!" << endl;
	}

	auto class2 = class1;  //복사 생성자 호출 (깊은 복제)
	cout << "1반을 복사하여 2반 생성: " << class2.to_string() << endl;

	auto class3 = class1 + class2;  // operator+연산자 호출 후 깊은복제.  class3 = class.operator+(class2);
	cout << "1반과 2반을 합쳐 3반 생성:" << class3.to_string() << endl;


	return 0;
}