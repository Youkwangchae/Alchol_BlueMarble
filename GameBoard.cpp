#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <random>
#include <regex>
using namespace std;
//고정 위치 (x, y)
const int st_x = 15;
const int st_y = 2;

//설명은 따로 빼놓기.
const string adventage[24][24] = { {"다같이 마시기", "네. 전부 마시면 됩니다 ^^" },{"황금열쇠", "우리 조가 걸렸을 때 방어할 수 있는 열쇠에요!"},{"으리~ 게임","걸린 조에서 총 3잔을 마시면 됩니다."},{"물 술 물 술","아까 정하신 순서있죠? 순서대로 물드시고 술드시고 물드시고 술드시면 됩니다~ (또 걸리면 술 물 술 물!)"}
,{"다같이 1잔~","네. 전부 마시면 됩니다^^."},{"술터널 시작","지름길이에요! 빨리 끝낼 수 있겠죠??"},{"술쌓긔 2 Stack","술쌓긔 스택이 +2 되었습니다. 감사합니다."},{"연달아 셀카 찍기","셀카를 찍으시고, 조원에게 보내면 조원이 그 셀카와 같이 셀카를 찍고, 또 그 조원이 받은 셀카와 자신을 같이 찍어서 모든 조원이 다 나오면 됩니다^^ 시간은 3분!"},
	{"황금열쇠","우리 조가 걸렸을 때 방어할 수 있는 열쇠에요!"}
,{"훈민정음","이제부터 외국어 및 외래어를 쓰시는 분들은 한 잔씩 드시면 됩니다. OK?"},{"상대 조 1잔~","네. 상대편 분들이 드시면 됩니다 ^^"},{"무인도 (한 턴 쉬기)","한 턴 쉬어가시겠습니다 :D"},{"의리 게임","걸린 조에서 총 2잔을 마시면 됩니다."},{"갓금열쇠","네. 황금열쇠 입니다."},{"지목 한명 마시기","네. 팀에서 한 명 지목하시면 됩니다! 우리팀 상대팀 아무나 한 명!"}
,{"물술물술","아까 정하신 순서있죠? 순서대로 물드시고 술드시고 물드시고 술드시면 됩니다~ (또 걸리면 술 물 술 물!)"},{"먼저 카톡 보내기!","걸린 조와 상대 조중 더 빨리 진행자에게 카톡으로 \"엣지있게 엣지\"를 보낸 팀이 승리! 걸린 조가 빠르면 살고, 상대 조가 빠르면 걸린 조가 마십니다^^"},{"주사위 던진 수 만큼 앞으로~","나온 수만큼 앞으로~!"},{"쌓은 술 마시긔^^", "여태 쌓인 술 스택 마시면 됩니다~!"},{"술 쌓긔 2 stack","술 스택 +2 되었습니다. 감사합니다."}
,{"갓금열쇠","네. 황금 열쇠입니다 :D"},{"가장 먼저 카톡보내기","걸린 조와 상대 조중 더 빨리 진행자에게 카톡으로 \"두근두근배창호\"를 보낸 팀이 승리!\n 걸린 조가 빠르면 살고, 상대 조가 빠르면 걸린 조가 마십니다^^"},{"처음으로...(숙연)","Ah.. 처음으로 가시겠습니다..^^"},{"START","시작!"} };

const string comments[5] = { "주루마블에 오신 것을 환영합니다." , "주사위를 던져 나온 수만큼 이동합니다." ,"총 2바퀴를 먼저 도는 팀이 승리!", "각 위치마다 여러가지 어드밴티지가 있습니다.", "대충.. 이정도?" };

//모든 키 입력 받기 위한 변수.
int key_value = _getch();

void gotoxy(int x, int y) {
	COORD Pos;
	Pos.X = x;
	Pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE),Pos);
}

void printMap(int a, int b, int r_a, int r_b, int _x, int _y) {
	int x = _x; int y = _y;
	gotoxy(x, y);
	string space[25];
	space[0] = "  START";
	for (int i = 1; i < 10; i++)
		space[i] = "  (" + to_string(i) + ")   │";
	for (int i = 10; i < 12; i++)
		space[i] = "  (" + to_string(i) + ")  │";
	for (int i = 12; i < 20; i++)
		space[i]="  ("+to_string(i)+")  │";
	space[20] = "  (20)  │";
	for(int i=21;i<24;i++)
		space[i] = "  (" + to_string(i) + ")  │";
	//(a, b) 팀의 각 위치에 동그라미, 별 놓기. (a조 : 동그라미, b조 : 별)
	if (r_a >= 24)
		r_a -= 24;
	if (r_b >= 24)
		r_b -= 24;
	if (r_a == r_b)
		space[r_b] = "   ●★ │";
	else
	{
		space[r_a] = "   ●   │";
		space[r_b] = "   ★   │";
	}
	y += 2; gotoxy(x, y);
	cout << "┌";
	for (int i = 0; i < 71; i++)
		cout << "─";
	cout << "┐";
	gotoxy(x, ++y);
	cout << "│";
	for (int i = 12; i < 20; i++)
		cout << space[i];
	gotoxy(x, ++y); cout << "└";
	for (int i = 0; i < 71; i++)
		cout << "─";
	cout << "┘"; gotoxy(x, ++y);

	cout << "│";
	cout<< space[11]+"        /  술  /                                     │" +space[20];
	gotoxy(x, ++y); cout << "└";
	for (int i = 0; i < 8; i++)
		cout << "─";
	cout << "┘";
	for (int i = 10; i < 63; i++)
		cout << " ";
	cout << "└";
	for (int i = 63; i < 71; i++)
		cout << "─";
	cout << "┘"; gotoxy(x, ++y);
	cout << "│";
	cout << space[10] + "      /  터  /                                       │" + space[21];
	gotoxy(x, ++y); cout << "└";
	for (int i = 0; i < 8; i++)
		cout << "─";
	cout << "┘";
	for (int i = 10; i < 63; i++)
		cout << " ";
	cout << "└";
	for (int i = 63; i < 71; i++)
		cout << "─";
	cout << "┘"; gotoxy(x, ++y);
	cout << "│";
	cout << space[9]+"   / NULL /                                          │" + space[22];
	gotoxy(x, ++y); cout << "└";
	for (int i = 0; i < 8; i++)
		cout << "─";
	cout << "┘";
	for (int i = 10; i < 63; i++)
		cout << " ";
	cout << "└";
	for (int i = 63; i < 71; i++)
		cout << "─";
	cout << "┘"; gotoxy(x, ++y);
	cout << "│";
	cout << space[8] + "  /  ♥  /                                           │" + space[23];
	gotoxy(x, ++y); cout << "└";
	for (int i = 0; i < 71; i++)
		cout << "─";
	cout << "┘"; gotoxy(x, ++y);

	cout << "│";
	for (int i = 7; i >= 0; i--)
		cout << space[i];
	cout << " │"; gotoxy(x, ++y);
	cout << "└";
	for (int i = 0; i < 71; i++)
		cout << "─";
	cout << "┘";

	x += 80;
	gotoxy(x, y); cout << "┌";
	for (int i = 0; i < 9; i++)
		cout << "─";
	cout << "┐"; gotoxy(x, ++y);
	cout << "│         │"; gotoxy(x, ++y);
	cout << "│ ● :" + to_string(a) + "조 │"; gotoxy(x, ++y);
	cout << "│ ★ :" + to_string(b) + "조 │"; gotoxy(x, ++y);
	cout << "│         │"; gotoxy(x, ++y);
	cout << "└";
	for (int i = 0; i < 9; i++)
		cout << "─";
	cout << "┘"; x = st_x;
	Sleep(3000);
}

void PrintEdge()
{
	// 엣지 로고
	int x = 45;
	int y = 30;

	gotoxy(x, y); cout << "┌";
	for (int i = 0; i < 60; i++)
		cout << "─";
	cout << "┐"; gotoxy(x, ++y);
	cout << "│           &&@/.%*.(@@#**************&@%###@  .&@%          │" << endl; gotoxy(x, ++y);
	cout << "│       *&       %,      ,&.      (@        @       /@       │" << endl; gotoxy(x, ++y);
	cout << "│     /@      ,@@&,         @.  /&       @@@@          @     │" << endl; gotoxy(x, ++y);
	cout << "│    &*    ,@&&&@&,  &@&     %(&%     @@@&&&@  @@&%     @    │" << endl; gotoxy(x, ++y);
	cout << "│    &     ((((((&,  &@@@/    @&     @&@@@&@@  &@@@@@@@@@@   │" << endl; gotoxy(x, ++y);
	cout << "│   (#           &,  &@@@@    &&    &@&     @            @   │" << endl; gotoxy(x, ++y);
	cout << "│    @    /@@@@@&@,  &@@@.    @&     &@@@   @  @@@@@@@@@@#   │" << endl; gotoxy(x, ++y);
	cout << "│   @*&     &@@@@&,  &@&     @ *&     &@@   @  @@@      &&   │" << endl; gotoxy(x, ++y);
	cout << "│  (%  &        #&,        /@    @      @   @         &% (#  │" << endl; gotoxy(x, ++y);
	cout << "│  @     &@      %,   &    @      @   .     @      .&,    &. │" << endl; gotoxy(x, ++y);
	cout << "│ %*         *&@@&@@&&%&.*@       #@.*@%@@&&@%&&@*         @ │" << endl; gotoxy(x, ++y);
	cout << "│  @           .&(                         .@/             & │" << endl; gotoxy(x, ++y);
	cout << "│   /&.     #&                                 &&        *&  │" << endl; gotoxy(x, ++y);
	cout << "│      .&&@&#                                     .&&@&#     │" << endl; gotoxy(x, ++y);
	cout << "└";
	for (int i = 0; i < 60; i++)
		cout << "─";
	cout << "┘";

	gotoxy(x, y+2); cout << "               PRESS        ANY         KEY !!                ";
	gotoxy(x, y+7); cout << "*    *    *   전체 화면으로 보시길 권장합니다.   *     *    *";
	key_value = _getch();
}

int dice(int x, int y, mt19937 gen)
{
	gotoxy(x, ++y); cout << "아무키나 눌러 주사위를 굴려주세요!";
	key_value = _getch(); gotoxy(x, ++y);
	uniform_int_distribution<int> dis(1, 6);
	int jump = dis(gen);
	cout << jump << "가 나왔습니다!"; Sleep(1000);
	return jump;//이동하는 칸 수
}

int main() {
	PrintEdge();
	system("cls");

//게임 시작
int x = st_x;
int y = st_y;
vector<int> place; //각 조별로 어느 위치인지 저장.

//조 2개 만큼 생성. 모두 0번째 위치로 초기화!
for (int i = 0; i < 2; i++)
	place.push_back(0);

for (int i = 0; i < 5; i++)
{
	gotoxy(x, ++y);
	cout << comments[i] << endl;
	Sleep(1000);
}
system("cls");
y = st_y; gotoxy(x, y);

for (int i = 0; i < 23; i++) {
	gotoxy(x, ++y);
	cout << "("<<(i+1)<<") "<<adventage[i][0];
}

Sleep(3000);
system("cls");
int a, b; // 어느 조가 먼저인지 받기.
regex re("[1-9]");
while (1) {
	y = st_y; gotoxy(x, y);
	cout << "게임 진행 순서를 입력해주세요 (1조 먼저, 3조 나중이면 1 입력 후 3 입력) : ";
	string str, _a, _b;
	getline(cin, _a); gotoxy(x, y+2); getline(cin, _b);
	if (regex_match(_a, re) && regex_match(_b, re))
	{
		a = stoi(_a); b = stoi(_b);
		break;
	}
	else
	{
		gotoxy(x, ++y);  cout << "1이상 10 미만의 양의 정수만 입력 가능합니다. 다시 입력하세요!"; Sleep(500);
		system("cls");
	}
}
int* team_first = new int[2];
team_first[0] = a;
team_first[1] = b;

system("cls");

// 맵 그리기 시작.
printMap(a, b, 0, 0, 15, 2); gotoxy(x, 18);
cout << "참고로 중간에 가로질러 가는 술터NULL도 있습니다 ^0^ (숱터NULL은 총 6칸 입니다.)"; gotoxy(x, 19);
cout << "                               게임 시작 합니다!";
Sleep(3000);
system("cls");

int fin_team = 0; //총 몇 조가 완주했는지 표시
bool mooindo[2]; //각 조가 무인도에 갔는지 여부 표시.
bool soolternull[2];//각 조가 술터널에 갔는지 여부 표시.
int ternull_space[2];//각 조의 술터널에서의 위치 표시.
for (int i = 0; i < 2; i++)
{
	mooindo[i] = false;
	soolternull[i] = false;
	ternull_space[i] = 0;
}
while (true) {
	for (int i = 0; i < 2; i++) 
	{
		random_device rd;
		mt19937 gen(rd());
		system("cls");
		y = st_y; gotoxy(x, y);
		if (place[i] < 48)
		{
			if(mooindo[i])
			{
				cout << "앗! " << team_first[i] << "조 차례네요~???^^";
				gotoxy(x, ++y); Sleep(1000);
				cout << "무인도에 오셨으니 한 턴 쉬어야죠~^_^ ";
				gotoxy(x, ++y); Sleep(1000);
				mooindo[i] = false;
				cout << "아무키나 눌러주세요!";
				key_value = _getch();
			}
			else if (soolternull[i]) 
			{
				cout << (i+1)<<"팀 현재 술터NULL의 위치 "<< ternull_space[i]<<"이군요!";
				int jump = dice(x, y++, gen);//이동하는 칸 수
				ternull_space[i] += jump; gotoxy(x, ++y);
				if (ternull_space[i] >= 6)
				{
					cout << "술터NULL을 나왔습니다.";
					soolternull[i] = false;
					if(place[i]>24)
						place[i] = 38 + ternull_space[i] - 6;
					else
						place[i] = 14 + ternull_space[i] - 6;
					gotoxy(x, ++y); cout << "현재 위치 "<< place[i]<< "입니다.";
					ternull_space[i] = 0;
				}
				else 
				{
					cout << "현재 술터NULL 위치 "<<ternull_space[i] << "입니다."; Sleep(1000);
					cout << "술터NULL 탈출까지 앞으로 "<< 6 - ternull_space[i]<<"칸 남았습니다!"<< endl; Sleep(1000);
					cout << "아무키나 눌러주세요!";
					key_value = _getch();
				}
			}
			else {
				cout << team_first[i] << "조 현재" << "위치 " << place[i] << "입니다."; gotoxy(x, ++y);
				cout << "완주까지 " << 48 - place[i] << "칸 남았습니다.";
				int jump = dice(x, y++, gen);//이동하는 칸 수
				place[i] += jump; Sleep(1000);

				if (place[i] >= 48)
				{
					gotoxy(x, y++); cout << "축하합니다!" << team_first[i] << "조 완주 성공입니다!";
					fin_team++;
				}
				else 
				{
					gotoxy(x, ++y); cout << "위치 " << place[i] << "(으)로 이동했습니다.";
					gotoxy(x, ++y);
					if (place[i] >= 25)
					{
						cout << "이 곳의 어드밴티지는 " << adventage[place[i] - 25][0] << "입니다~";
						gotoxy(x, ++y);
						cout << adventage[place[i] - 25][1] << endl;
					}
					else
					{
						cout << "이 곳의 어드밴티지는 " << adventage[place[i] - 1][0] << "입니다~";
						gotoxy(x, ++y);
						cout << adventage[place[i] - 1][1] << endl;
					}
					if (place[i] == 6||place[i]==30)
						soolternull[i] = true;
					else if (place[i] == 12 || place[i] == 36)
						mooindo[i] = true;
					else if (place[i] == 18 || place[i] == 42)
						place[i] += jump;
					else if (place[i] == 23 || place[i] == 47)
						place[i] = 0;
					
					Sleep(3000);
					gotoxy(x, y+2); cout << "모든 어드밴티지를 수행했다면 아무 키나 눌러주세요!";
					key_value = _getch();
				}
				printMap(a, b, place[0], place[1], x, y);
				if (fin_team >= 1)
					break;
		}
		}
	}
	if (fin_team >= 1)
		break;
}
gotoxy(x, st_y+30);
cout << "주루마블이 종료되었습니다. 수고 많으셨습니다~"<<endl;
	system("pause");
}