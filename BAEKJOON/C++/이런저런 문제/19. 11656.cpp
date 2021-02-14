#include<iostream>
#include<string>
#include<vector>
#include<algorithm>


using namespace std;

#define endl '\n'


int main(void)
{
	string str;
	cin >> str;
	vector<string> arr(str.size());

	for (int i = 0; i<int(str.size()); i++) {
		arr[i] = "";
		for (int j = i; j<int(str.size()); j++) {
			arr[i] += str[j];
		}
	}

	
	sort(arr.begin(), arr.end());

	for (int i = 0; i<int(str.size()); i++) {
		cout << arr[i] << endl;
	}

	return 0;
}