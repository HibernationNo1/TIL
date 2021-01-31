//병합정렬 알고리즘, 작은 수 부터 오름차순으로 정렬
#include<iostream>
#include<vector>

using namespace std;

#define endl '\n'

int* arr1;  // arr2 라는 스마트 포인터(배열) 생성 //받은 값을 저장할 배열
int* arr2;  // arr2 라는 스마트 포인터(배열) 생성 //임시로 사용할 배열


void merge(int left, int right)
{
	int mid = (left + right) / 2;

	int i = left;
	int j = mid + 1;
	int k = left; // 임시 배열 arr2 에 사용할 변수

	while (i <= mid && j <= right) {
		// i는 왼쪽부터, j는 중간 + 1부터 진행
		// i가 mid를 넘어가거나, j가 right를 넘어가는 순간 while문 종료
		if (arr1[i] <= arr1[j]) {  // arr1배열에서 두 값 비교
			// arr[i]에 들어있는 값이 arr1[j]에 들어있는 값보다 작으면 
			arr2[k++] = arr1[i++]; // arr2[k]에 arr1[i]의 값을 할당 후 k, i에 각각 ++
		}
		else {
			arr2[k++] = arr1[j++];
		}
	}

	// 위의 while문에서 i가 mid를 넘어버리면, j는 right에 다다르지 못하고 반복문이 끝나기 때문에
	// 남은 데이터를 arr2에 넣어준다
	if (i > mid) {
		for (int t = j; t <= right; t++)
		{
			arr2[k++] = arr1[t];
		}
	}
	else
	{
		for (int t = i; t <= mid; t++)
		{
			arr2[k++] = arr1[t];
		}
	}

	//임시 저장용 배열 arr2에서 원래 배열인 arr1로 값을 넣어준다. 
	for (int t = left; t <= right; t++) {
		arr1[t] = arr2[t];
	}

}

void partition(int left, int right) {  //인자는 맨 왼쪽, 맨 오른쪽을 의미함

	int mid;
	if (left < right) { // left, right 가 같으면
		mid = (left + right) / 2;  //중간지점 잡아놓고, 
		partition(left, mid);  // 맨 왼쪽부터 중간까지 
		partition(mid + 1, right);  //중간부터 맨 오른쪽까지
		// 재귀

		merge(left, right);

	}

	// 계속 쪼개지다 보면,  mid가 인자로 들어갈 때 left또는 right와 같아질 땐 함수 호출해도 동작없음
}

int main(void)
{
	int n;
	cin >> n;

	arr1 = new int[n];  // 힙에(스마트 포인터를 사용해서) 배열 생성
	arr2 = new int[n];

	for (int i = 0; i < n; i++) {
		cin >> arr1[i];
	}

	partition(0, n - 1); // 배열의 시작 index 숫자, 배열의 끝 index숫자 

	for (int i = 0; i < n; i++) {
		cout << arr1[i] << endl;
	}

	return 0;
}