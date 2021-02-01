#include<iostream>
#include<vector>

#include<algorithm>

using namespace std;
#define endl '\n'

class dic
{
public:
	string name;
	int k, e, m;
};

bool cmp(const dic &a, const dic &b)
{
	if (a.k > b.k) {
		return true;
	}
	else if (a.k == b.k) {
		if (a.e < b.e) {
			return true;
		}
		else if (a.e == b.e) {
			if (a.m > b.m) {
				return true;
			}
			else if (a.m == b.m) {
				return a.name < b.name;
			}
			else {
				return false;
			}
		}
		else return false;
	}
	else return false;
		
}

int main(void)
{
	int n;
	cin >> n;

	vector<dic> arr(n);

	for (int i = 0; i < n; i++) { // 이름, 국, 영, 수  순서
			cin >> arr[i].name >> arr[i].k >> arr[i].e >> arr[i].m;
	}

	sort(arr.begin(), arr.end(), cmp);

	
	for (int i = 0; i < n; i++) {
		cout << arr[i].name << endl;
	}


	return 0;
}