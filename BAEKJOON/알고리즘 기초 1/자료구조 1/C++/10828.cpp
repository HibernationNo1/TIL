#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'

class stack
{
private:
	int arr[10000];
	int i = 0;

public:

	stack()
	{
		for (int j = 0; j < 10000; j++) {
			arr[i] = -1;
		}
		i = 0;
	}
	
	void push(int x)
	{
		arr[i++] = x;
		
	}

	int pop()
	{
		if (empty() == 1) {
			return -1;
		}
		i--;
		return arr[i];
	}

	int size()
	{
		return i;
	}

	int empty()
	{
		if (arr[i-1] == -1 || i == 0)
		{
			return 1;
		}
		
		return 0;
	}

	int top()
	{
		if (empty() == 1) return -1;

		return arr[i-1];
	}

};

int main(void)
{
	int n, tmp;
	cin >> n;
	string str;

	stack foo;
	for (int i = 0; i < n; i++) {
		cin >> str;
		if (str == "push") {
			cin >> tmp;
			foo.push(tmp);
		}
		else if (str == "pop") {
			cout << foo.pop() << endl;
		}
		else if (str == "size") {
			cout << foo.size() << endl;
		}
		else if (str == "empty") {
			cout << foo.empty() << endl;
		}
		else if (str == "top") {
			cout << foo.top() << endl;
		}
	}
	

	

	return 0;
}