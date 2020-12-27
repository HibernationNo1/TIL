#include <vector>
#include <iostream>
using namespace std;
long long sum(vector<int> &a)
{
	long long ans = 0;

	for (int i = 0; i < a.size(); i++)
	{
		ans = ans + a[i];
	}
	return ans;
}