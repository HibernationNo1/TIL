#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

#define endl '\n'

class Deque
{
public:
	int arr[10000];
	int puf;
	int pub;


	Deque() {
		for (int i = 0; i < 10000; i++) {
			arr[i] = -1;
		}
		puf = 0;
		pub = 0;
	}
	
	void push_front(int x) {
		arr[4999 - puf] = x;
		puf++;
	}

	void push_back(int x) {
		arr[5000 + pub] = x;
		pub++;
	}

	void pop_front() {
		int a = arr[4999 - (puf - 1)];
		arr[4999 - (puf - 1)] = -1;
		puf--; 
		if (pub + puf <= 0) puf = (-1) * pub;
		cout << a << endl;
	}

	void pop_back() {
		int a = arr[5000 + (pub - 1)];
		arr[5000 + (pub - 1)] = -1;
		pub--;
		if (pub + puf <= 0)  pub = (-1) * puf;
		cout << a << endl;
	}


	void size() {
		if (puf + pub <= 0) cout << 0 << endl;
		else cout << abs(puf + pub) << endl;
	}

	void empty() {
		if (puf + pub <= 0) cout << 1 << endl;
		else cout << 0 << endl;
	}

	void front() {
		if (puf + pub <= 0) cout << -1 << endl;
		else cout << arr[4999 - (puf-1)] << endl;
		
	}

	void back() {
		if (puf + pub <= 0) cout << -1 << endl;
		else cout << arr[5000 + (pub - 1)] << endl;
	}
};

int main(void)
{
	int n;
	string str;
	cin >> n;

	Deque myfoo;

	for (int i = 0; i < n; i++) {
		cin >> str;

		if (str == "push_front") {
			int x;
			cin >> x;
			
			myfoo.push_front(x);
		}
		else if (str == "push_back") {
			int x;
			cin >> x;

			myfoo.push_back(x);
		}
		else if (str == "pop_front") {
			myfoo.pop_front();
		}
		else if (str == "pop_back") {
			myfoo.pop_back();
		}
		else if (str == "size") {
			myfoo.size();
		}
		else if (str == "empty") {
			myfoo.empty();
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