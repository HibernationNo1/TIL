#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'

class Queue
{
public:
	int arr[10000];
	int r;
	int f;

	Queue() {
		for (int i = 0; i < 10000; i++) {
			arr[i] = -1;
		}
		r = 0;
		f = 0;
	}
	
	void push(int x) {
		arr[r++] = x;
	}

	int pop() {
		if (r <= f) return -1;
		return arr[f++];
	}

	int size() {
		if (r <= f) return 0;
		return r - f;
	}

	int empty() {
		if (r <= f) return 1;
		else return 0;
	}

	void front() {
		if (empty() == 1) cout << -1 << endl;
		else cout << arr[f] << endl;
		
	}

	void back() {
		if (empty() == 1) cout << -1 << endl;
		else cout << arr[r - 1] << endl;
	}
};

int main(void)
{
	int n;
	string str;
	cin >> n;

	Queue myfoo;

	for (int i = 0; i < n; i++) {
		cin >> str;

		if (str == "push") {
			int x;
			cin >> x;
			
			myfoo.push(x);
		}
		else if (str == "pop") {
			cout << myfoo.pop() << endl;
		}
		else if (str == "size") {
			cout << myfoo.size() << endl;
		}
		else if (str == "empty") {
			cout << myfoo.empty() << endl;
		}
		else if (str == "front") {
			myfoo.front();
		}
		else if (str == "back") {
			myfoo.back();
		}
	}
	
	return 0;
}