#include<iostream>
#include<algorithm>
#include<vector>

using namespace std;

#define endl '\n'

int Width(vector<vector<char>> &arr, int i, int n) {  //가로 분석, 매개변수(배열, 해당 행, 입력받은 n)
	int count = 1;
	int m = 0;
	
	for (int j = 0; j < n-1; j++) {
		if (arr[i][j] == arr[i][j + 1]) {
			count++;
			m = max(m, count);
		}
		else {
			count = 1;
		}
	}
	
	return m;
}

int Length(vector<vector<char>>& arr, int i, int n) { //세로 분석, 매개변수(배열, 해당 열, 입력받은 n)
	int count = 1;
	int m = 0;

	for (int j = 0; j < n-1; j++) {
		if (arr[j][i] == arr[j+1][i]) {
			count++;
			m = max(m, count);
		}
		else {
			count = 1;
		}
	}
	return m;
}

int main(void)
{
	int n, cnt = 0;
	cin >> n;
	vector<vector<char>> arr(n, vector<char> (n));
	
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			cin >> arr[i][j];
		}
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (j < n-1) {  // 가로로 연속되지 않은 색이 나왔을 때
				swap(arr[i][j], arr[i][j + 1]);			// 두 원소 스왑
				cnt = max(Width(arr, i, n), cnt);		// 해당 행 가로로 체크
				cnt = max(Length(arr, j, n), cnt);		// 해당 열 세로로 체크
				cnt = max(Length(arr, j + 1, n), cnt);	// 해당 열의 다음 열 세로로 체크 (가로로 스왑했기 때문에 다음 열에도 영향을 준다)
				swap(arr[i][j], arr[i][j + 1]);			// 다시 두 원소 제 자리로 스왑
			}
			
			if (i < n-1){	// 세로로 연속되지 않은 색이 나왔을 때
				swap(arr[i][j], arr[i+1][j]);			// 두 원소 스왑
				cnt = max(Width(arr, i, n), cnt);		// 해당 행 가로로 체크
				cnt = max(Width(arr, i+1, n), cnt);		// 해당 행의 다음 행 가로로 체크 (세로로 스왑했기 때문에 다음 행에도 영향을 준다)
				cnt = max(Length(arr, j, n), cnt);		// 해당 행 세로로 체크
				swap(arr[i][j], arr[i+1][j]);			// 다시 두 원소 제 자리로 스왑
			}
		}
	}

	cout << cnt << endl;
	

	return 0;
}