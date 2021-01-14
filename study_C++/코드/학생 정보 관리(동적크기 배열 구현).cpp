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


	DynamicArray(int n)
	{
		this->n = n;
		data = new T[n];
	}
	DynamicArray(const DynamicArray<T>& other)
	{
		n = other.n;
		data = new T[n];

		for (int i = 0; i < n; i++)
		{
			data[i] = other[i];
		}
	}


	T& operator[](int index)
	{
		return data[index];
	}

	const T& operator[](int index) const
	{
		return data[index];
	}

	T& at(int index)
	{
		if (index < n)
		{
			return data[index];
		}
		throw ("Index out of range");
	}


	int size() const
	{
		return n;
	}

	~DynamicArray()
	{
		delete[] data;
	}

	T* Begin() { return data; }
	const T* Begin() const { return data; }
	T* End() { return data + n; }
	const T* End() const { return data + n; }

	friend DynamicArray<T> operator+(const DynamicArray<T>& arr1, DynamicArray<T>& arr2)
	{
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

		ostringstream os;
		os << data[0];

		for (int i = 1; i < n; i++)
		{
			os << sep << data[i];    
		}
		return os.str();
	}
};

struct student
{
	string name;
	int standard;
};

ostream& operator<<(ostream& os, const student& s)   
{
	return (os << "[" << s.name << "," << s.standard << "]");
}


int main(void)
{
	int nStudents;
	cout << "1반 학생 수를 입력하세요:";
	cin >> nStudents;

	DynamicArray<student> class1(nStudents);
	for (int i = 0; i < nStudents; i++)
	{
		string name;
		int standard;
		cout << i + 1 << "번째 학생 이름과 나이를 입력하세요: ";

		cin >> name >> standard;
		class1[i] = student{ name, standard };
	}

	try
	{
		class1.at(nStudents);
	}
	catch (...)
	{
		cout << "예외 발생!" << endl;
	}

	auto class2 = class1;
	cout << "1반을 복사하여 2반 생성: " << class2.to_string() << endl;

	auto class3 = class1 + class2;
	cout << "1반과 2반을 합쳐 3반 생성:" << class3.to_string() << endl;



	return 0;
}