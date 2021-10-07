#include <iostream>

using namespace std;

int main(void)
{
	int T;
	cin >> T;

	for (int i = 1; i <= T; i++)
	{
		int k, n;  // k층 n호 
		cin >> k >> n;

		int** sum = new int* [k + 1];
		for (int j = 0; j < k; j++)    // 2차원 new배열     
		{
			sum[j] = new int[n + 1];
		}

		for (int j = 0; j < n; j++)    
		{
			sum[0][j] = (j+1)*(j+2)/2;  // 1층 값 넣기 ( 0부터 n-1까지 각각 1호~n호에 1~n의 합 할당)
		}
		for (int j = 0; j < k; j++)
		{
				sum[j][0] = 1;      // 1층부터 모든 층의 1호에 1의 값을 넣는다
		}
		
		

		for (int j = 1; j < k; j++)
		{
			for (int jj = 1; jj < n; jj++)      //k층 n호의 값 == 아랫층 + 왼쪽 
			{
				sum[j][jj] = sum[j - 1][jj] + sum[j][jj - 1];          
			}
		}
		

		cout << sum[k-1][n-1] << endl;

		

		for (int i = 1; i < k; i++)
		{
			delete[] sum[i];
		}
		delete[] sum;
	}


//
//3	1	5	15	35	70
//2	1	4	10	20	35
//1	1	3	6	10	15
//0	1	2	3	4	5

	return 0;

}