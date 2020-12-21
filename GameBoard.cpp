#include <iostream>
#include <vector>
#include <conio.h>
#include <Windows.h>
#include <string>
#include <random>
#include <regex>
using namespace std;
//���� ��ġ (x, y)
const int st_x = 15;
const int st_y = 2;

//������ ���� ������.
const string adventage[24][24] = { {"�ٰ��� ���ñ�", "��. ���� ���ø� �˴ϴ� ^^" },{"Ȳ�ݿ���", "�츮 ���� �ɷ��� �� ����� �� �ִ� ���迡��!"},{"����~ ����","�ɸ� ������ �� 3���� ���ø� �˴ϴ�."},{"�� �� �� ��","�Ʊ� ���Ͻ� ��������? ������� ����ð� ����ð� ����ð� ����ø� �˴ϴ�~ (�� �ɸ��� �� �� �� ��!)"}
,{"�ٰ��� 1��~","��. ���� ���ø� �˴ϴ�^^."},{"���ͳ� ����","�������̿���! ���� ���� �� �ְ���??"},{"���ױ� 2 Stack","���ױ� ������ +2 �Ǿ����ϴ�. �����մϴ�."},{"���޾� ��ī ���","��ī�� �����ð�, �������� ������ ������ �� ��ī�� ���� ��ī�� ���, �� �� ������ ���� ��ī�� �ڽ��� ���� �� ��� ������ �� ������ �˴ϴ�^^ �ð��� 3��!"},
	{"Ȳ�ݿ���","�츮 ���� �ɷ��� �� ����� �� �ִ� ���迡��!"}
,{"�ƹ�����","�������� �ܱ��� �� �ܷ�� ���ô� �е��� �� �ܾ� ��ø� �˴ϴ�. OK?"},{"��� �� 1��~","��. ����� �е��� ��ø� �˴ϴ� ^^"},{"���ε� (�� �� ����)","�� �� ����ðڽ��ϴ� :D"},{"�Ǹ� ����","�ɸ� ������ �� 2���� ���ø� �˴ϴ�."},{"���ݿ���","��. Ȳ�ݿ��� �Դϴ�."},{"���� �Ѹ� ���ñ�","��. ������ �� �� �����Ͻø� �˴ϴ�! �츮�� ����� �ƹ��� �� ��!"}
,{"��������","�Ʊ� ���Ͻ� ��������? ������� ����ð� ����ð� ����ð� ����ø� �˴ϴ�~ (�� �ɸ��� �� �� �� ��!)"},{"���� ī�� ������!","�ɸ� ���� ��� ���� �� ���� �����ڿ��� ī������ \"�����ְ� ����\"�� ���� ���� �¸�! �ɸ� ���� ������ ���, ��� ���� ������ �ɸ� ���� ���ʴϴ�^^"},{"�ֻ��� ���� �� ��ŭ ������~","���� ����ŭ ������~!"},{"���� �� ���ñ�^^", "���� ���� �� ���� ���ø� �˴ϴ�~!"},{"�� �ױ� 2 stack","�� ���� +2 �Ǿ����ϴ�. �����մϴ�."}
,{"���ݿ���","��. Ȳ�� �����Դϴ� :D"},{"���� ���� ī�庸����","�ɸ� ���� ��� ���� �� ���� �����ڿ��� ī������ \"�αٵαٹ�âȣ\"�� ���� ���� �¸�!\n �ɸ� ���� ������ ���, ��� ���� ������ �ɸ� ���� ���ʴϴ�^^"},{"ó������...(����)","Ah.. ó������ ���ðڽ��ϴ�..^^"},{"START","����!"} };

const string comments[5] = { "�ַ縶�� ���� ���� ȯ���մϴ�." , "�ֻ����� ���� ���� ����ŭ �̵��մϴ�." ,"�� 2������ ���� ���� ���� �¸�!", "�� ��ġ���� �������� ����Ƽ���� �ֽ��ϴ�.", "����.. ������?" };

//��� Ű �Է� �ޱ� ���� ����.
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
		space[i] = "  (" + to_string(i) + ")   ��";
	for (int i = 10; i < 12; i++)
		space[i] = "  (" + to_string(i) + ")  ��";
	for (int i = 12; i < 20; i++)
		space[i]="  ("+to_string(i)+")  ��";
	space[20] = "  (20)  ��";
	for(int i=21;i<24;i++)
		space[i] = "  (" + to_string(i) + ")  ��";
	//(a, b) ���� �� ��ġ�� ���׶��, �� ����. (a�� : ���׶��, b�� : ��)
	if (r_a >= 24)
		r_a -= 24;
	if (r_b >= 24)
		r_b -= 24;
	if (r_a == r_b)
		space[r_b] = "   �ܡ� ��";
	else
	{
		space[r_a] = "   ��   ��";
		space[r_b] = "   ��   ��";
	}
	y += 2; gotoxy(x, y);
	cout << "��";
	for (int i = 0; i < 71; i++)
		cout << "��";
	cout << "��";
	gotoxy(x, ++y);
	cout << "��";
	for (int i = 12; i < 20; i++)
		cout << space[i];
	gotoxy(x, ++y); cout << "��";
	for (int i = 0; i < 71; i++)
		cout << "��";
	cout << "��"; gotoxy(x, ++y);

	cout << "��";
	cout<< space[11]+"        /  ��  /                                     ��" +space[20];
	gotoxy(x, ++y); cout << "��";
	for (int i = 0; i < 8; i++)
		cout << "��";
	cout << "��";
	for (int i = 10; i < 63; i++)
		cout << " ";
	cout << "��";
	for (int i = 63; i < 71; i++)
		cout << "��";
	cout << "��"; gotoxy(x, ++y);
	cout << "��";
	cout << space[10] + "      /  ��  /                                       ��" + space[21];
	gotoxy(x, ++y); cout << "��";
	for (int i = 0; i < 8; i++)
		cout << "��";
	cout << "��";
	for (int i = 10; i < 63; i++)
		cout << " ";
	cout << "��";
	for (int i = 63; i < 71; i++)
		cout << "��";
	cout << "��"; gotoxy(x, ++y);
	cout << "��";
	cout << space[9]+"   / NULL /                                          ��" + space[22];
	gotoxy(x, ++y); cout << "��";
	for (int i = 0; i < 8; i++)
		cout << "��";
	cout << "��";
	for (int i = 10; i < 63; i++)
		cout << " ";
	cout << "��";
	for (int i = 63; i < 71; i++)
		cout << "��";
	cout << "��"; gotoxy(x, ++y);
	cout << "��";
	cout << space[8] + "  /  ��  /                                           ��" + space[23];
	gotoxy(x, ++y); cout << "��";
	for (int i = 0; i < 71; i++)
		cout << "��";
	cout << "��"; gotoxy(x, ++y);

	cout << "��";
	for (int i = 7; i >= 0; i--)
		cout << space[i];
	cout << " ��"; gotoxy(x, ++y);
	cout << "��";
	for (int i = 0; i < 71; i++)
		cout << "��";
	cout << "��";

	x += 80;
	gotoxy(x, y); cout << "��";
	for (int i = 0; i < 9; i++)
		cout << "��";
	cout << "��"; gotoxy(x, ++y);
	cout << "��         ��"; gotoxy(x, ++y);
	cout << "�� �� :" + to_string(a) + "�� ��"; gotoxy(x, ++y);
	cout << "�� �� :" + to_string(b) + "�� ��"; gotoxy(x, ++y);
	cout << "��         ��"; gotoxy(x, ++y);
	cout << "��";
	for (int i = 0; i < 9; i++)
		cout << "��";
	cout << "��"; x = st_x;
	Sleep(3000);
}

void PrintEdge()
{
	// ���� �ΰ�
	int x = 45;
	int y = 30;

	gotoxy(x, y); cout << "��";
	for (int i = 0; i < 60; i++)
		cout << "��";
	cout << "��"; gotoxy(x, ++y);
	cout << "��           &&@/.%*.(@@#**************&@%###@  .&@%          ��" << endl; gotoxy(x, ++y);
	cout << "��       *&       %,      ,&.      (@        @       /@       ��" << endl; gotoxy(x, ++y);
	cout << "��     /@      ,@@&,         @.  /&       @@@@          @     ��" << endl; gotoxy(x, ++y);
	cout << "��    &*    ,@&&&@&,  &@&     %(&%     @@@&&&@  @@&%     @    ��" << endl; gotoxy(x, ++y);
	cout << "��    &     ((((((&,  &@@@/    @&     @&@@@&@@  &@@@@@@@@@@   ��" << endl; gotoxy(x, ++y);
	cout << "��   (#           &,  &@@@@    &&    &@&     @            @   ��" << endl; gotoxy(x, ++y);
	cout << "��    @    /@@@@@&@,  &@@@.    @&     &@@@   @  @@@@@@@@@@#   ��" << endl; gotoxy(x, ++y);
	cout << "��   @*&     &@@@@&,  &@&     @ *&     &@@   @  @@@      &&   ��" << endl; gotoxy(x, ++y);
	cout << "��  (%  &        #&,        /@    @      @   @         &% (#  ��" << endl; gotoxy(x, ++y);
	cout << "��  @     &@      %,   &    @      @   .     @      .&,    &. ��" << endl; gotoxy(x, ++y);
	cout << "�� %*         *&@@&@@&&%&.*@       #@.*@%@@&&@%&&@*         @ ��" << endl; gotoxy(x, ++y);
	cout << "��  @           .&(                         .@/             & ��" << endl; gotoxy(x, ++y);
	cout << "��   /&.     #&                                 &&        *&  ��" << endl; gotoxy(x, ++y);
	cout << "��      .&&@&#                                     .&&@&#     ��" << endl; gotoxy(x, ++y);
	cout << "��";
	for (int i = 0; i < 60; i++)
		cout << "��";
	cout << "��";

	gotoxy(x, y+2); cout << "               PRESS        ANY         KEY !!                ";
	gotoxy(x, y+7); cout << "*    *    *   ��ü ȭ������ ���ñ� �����մϴ�.   *     *    *";
	key_value = _getch();
}

int dice(int x, int y, mt19937 gen)
{
	gotoxy(x, ++y); cout << "�ƹ�Ű�� ���� �ֻ����� �����ּ���!";
	key_value = _getch(); gotoxy(x, ++y);
	uniform_int_distribution<int> dis(1, 6);
	int jump = dis(gen);
	cout << jump << "�� ���Խ��ϴ�!"; Sleep(1000);
	return jump;//�̵��ϴ� ĭ ��
}

int main() {
	PrintEdge();
	system("cls");

//���� ����
int x = st_x;
int y = st_y;
vector<int> place; //�� ������ ��� ��ġ���� ����.

//�� 2�� ��ŭ ����. ��� 0��° ��ġ�� �ʱ�ȭ!
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
int a, b; // ��� ���� �������� �ޱ�.
regex re("[1-9]");
while (1) {
	y = st_y; gotoxy(x, y);
	cout << "���� ���� ������ �Է����ּ��� (1�� ����, 3�� �����̸� 1 �Է� �� 3 �Է�) : ";
	string str, _a, _b;
	getline(cin, _a); gotoxy(x, y+2); getline(cin, _b);
	if (regex_match(_a, re) && regex_match(_b, re))
	{
		a = stoi(_a); b = stoi(_b);
		break;
	}
	else
	{
		gotoxy(x, ++y);  cout << "1�̻� 10 �̸��� ���� ������ �Է� �����մϴ�. �ٽ� �Է��ϼ���!"; Sleep(500);
		system("cls");
	}
}
int* team_first = new int[2];
team_first[0] = a;
team_first[1] = b;

system("cls");

// �� �׸��� ����.
printMap(a, b, 0, 0, 15, 2); gotoxy(x, 18);
cout << "����� �߰��� �������� ���� ����NULL�� �ֽ��ϴ� ^0^ (����NULL�� �� 6ĭ �Դϴ�.)"; gotoxy(x, 19);
cout << "                               ���� ���� �մϴ�!";
Sleep(3000);
system("cls");

int fin_team = 0; //�� �� ���� �����ߴ��� ǥ��
bool mooindo[2]; //�� ���� ���ε��� ������ ���� ǥ��.
bool soolternull[2];//�� ���� ���ͳο� ������ ���� ǥ��.
int ternull_space[2];//�� ���� ���ͳο����� ��ġ ǥ��.
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
				cout << "��! " << team_first[i] << "�� ���ʳ׿�~???^^";
				gotoxy(x, ++y); Sleep(1000);
				cout << "���ε��� �������� �� �� �������~^_^ ";
				gotoxy(x, ++y); Sleep(1000);
				mooindo[i] = false;
				cout << "�ƹ�Ű�� �����ּ���!";
				key_value = _getch();
			}
			else if (soolternull[i]) 
			{
				cout << (i+1)<<"�� ���� ����NULL�� ��ġ "<< ternull_space[i]<<"�̱���!";
				int jump = dice(x, y++, gen);//�̵��ϴ� ĭ ��
				ternull_space[i] += jump; gotoxy(x, ++y);
				if (ternull_space[i] >= 6)
				{
					cout << "����NULL�� ���Խ��ϴ�.";
					soolternull[i] = false;
					if(place[i]>24)
						place[i] = 38 + ternull_space[i] - 6;
					else
						place[i] = 14 + ternull_space[i] - 6;
					gotoxy(x, ++y); cout << "���� ��ġ "<< place[i]<< "�Դϴ�.";
					ternull_space[i] = 0;
				}
				else 
				{
					cout << "���� ����NULL ��ġ "<<ternull_space[i] << "�Դϴ�."; Sleep(1000);
					cout << "����NULL Ż����� ������ "<< 6 - ternull_space[i]<<"ĭ ���ҽ��ϴ�!"<< endl; Sleep(1000);
					cout << "�ƹ�Ű�� �����ּ���!";
					key_value = _getch();
				}
			}
			else {
				cout << team_first[i] << "�� ����" << "��ġ " << place[i] << "�Դϴ�."; gotoxy(x, ++y);
				cout << "���ֱ��� " << 48 - place[i] << "ĭ ���ҽ��ϴ�.";
				int jump = dice(x, y++, gen);//�̵��ϴ� ĭ ��
				place[i] += jump; Sleep(1000);

				if (place[i] >= 48)
				{
					gotoxy(x, y++); cout << "�����մϴ�!" << team_first[i] << "�� ���� �����Դϴ�!";
					fin_team++;
				}
				else 
				{
					gotoxy(x, ++y); cout << "��ġ " << place[i] << "(��)�� �̵��߽��ϴ�.";
					gotoxy(x, ++y);
					if (place[i] >= 25)
					{
						cout << "�� ���� ����Ƽ���� " << adventage[place[i] - 25][0] << "�Դϴ�~";
						gotoxy(x, ++y);
						cout << adventage[place[i] - 25][1] << endl;
					}
					else
					{
						cout << "�� ���� ����Ƽ���� " << adventage[place[i] - 1][0] << "�Դϴ�~";
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
					gotoxy(x, y+2); cout << "��� ����Ƽ���� �����ߴٸ� �ƹ� Ű�� �����ּ���!";
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
cout << "�ַ縶���� ����Ǿ����ϴ�. ���� �����̽��ϴ�~"<<endl;
	system("pause");
}