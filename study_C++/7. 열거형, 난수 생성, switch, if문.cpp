#include <iostream>
#include <ctime>  // 시간을 사용
#include <cstdlib> // C표준 유틸리티 함수 포함 https://modoocode.com/121
 
using namespace std;

// 열거형  https://blog.naver.com/gnqo7598/221331932542 ,   https://blog.naver.com/dhdnjswnd/222015088838
enum SRP
{
	SRP_S = 1,		//가위
	SRP_R,			//바위
	SRP_P,			//보
	SRP_END			// 마지막.  ;안써도 됨. 
};

int main(void)
{

	int iPlayer;  //플레이어 선언
	int iAI; // 상대(컴퓨터)선언

	while (1) // 무한루프
	{
		cout << "1. 가위" << endl;
		cout << "2. 바위" << endl;
		cout << "3. 보" << endl;
		cout << "4. 종료" << endl;
		cout << "메뉴를 선택하세요: " << endl;
		cin >> iPlayer;

		if (iPlayer < SRP_S || iPlayer > SRP_END)  // 듈 다 1이면 true. 1보다 작은 값OR 4보다 큰 값
		{
			cout << "잘못된 값을 입력하였습니다." << endl;

			system("pause"); //일시정지  >> "계속하려면 아무 키나 누르십시오" 출력
			continue; // 반복문 안에서 선언 시 반복문의 시작점으로 이동시켜주는 기능
		}
		else if (iPlayer == SRP_END)  // while문을 빠져나오는 방법 4 입력
		{
			break;
		}

		//난수 테이블 생성해야 
		srand((unsigned int)time(NULL));   // 난수 초기화. (넣지 않을 경우 재실행 시에도 같은 숫자가 나온다.)
		//time(0 또는 NULL(원칙)): UCT기준 1970년 1월 1일 0시 0분 0초부터 경과된 시간을 초로 변환해 반환한다.
		//srand: 난수값을 생성한다. 랜덤으로 값을 생성. srand(초기값)으로 사용
		//srand의 초기값에 time을 unsigned int형으로 형변환 해서 넣는다. >> 초기값이 계속 바뀐다.


		// 봇이 선택할 차례
		iAI = rand() % 3 + 1; // 난수 1~3생성  (3으로 나누면 나머지 0~2 여기에 +1하면 1~3)

		switch (iAI)  //봇이 선택한걸 보여준다.
		{
		case SRP_S:
			cout << " AI: 가위" << endl;
			break;
		case SRP_R:
			cout << " AI: 바위" << endl;
			break;
		case SRP_P:
			cout << " AI: 보" << endl;
			break;
		}

		int iWin = iPlayer - iAI;

		if (iWin == 1 || iWin == -2)
		{
			cout << "iPlayer 승리" << endl;
		}
		else if (iWin == 0)
		{
			cout << "비김" << endl;
		}
		else
		{
			cout << "AI 승리" << endl;;
		}
		system("pause");

	}