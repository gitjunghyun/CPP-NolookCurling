#include <iostream>
#include <windows.h> //System(cls) , Sleep() ���� �������
#include <conio.h> // kbhit(), getch() ���� �������
#include <time.h>
#include <string> 
#include <stdio.h>
#include <tchar.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
/* GDI ������ ���� */
/* http://blog.naver.com/cci123vv/220984604837 */

using namespace std;
using namespace Gdiplus;

#define LEFT 75
#define RIGHT 77
#define SPACE 32
#define DOWN 80
#define UP 72
#define MAX 13
#define WIDTH 19
#define HEIGHT 35
#define col GetStdHandle(STD_OUTPUT_HANDLE)
#define sky SetConsoleTextAttribute(col,11);
#define red SetConsoleTextAttribute( col,12 ); //��
#define white SetConsoleTextAttribute( col,15); //��


typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;   //Ŀ�� ����

int bx;
int by; //stone(��)
int cx = 3, cy = HEIGHT + 1;  //ĳ���� �ܼ���ǥ
int px = 2 * WIDTH + 1, py = 1;
char cha[3] = "��";                                       // �� ĳ����
char po[3] = "��";
int arr[3];
int count = 1;

int map[HEIGHT][WIDTH] = {

	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,            // 1
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,1,
	1,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,1,
	1,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,1,
	1,0,0,0,0,0,2,0,0,0,0,0,2,0,0,0,0,0,1,
	1,0,0,0,0,0,0,2,0,0,0,2,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,2,2,2,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,
	1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1// 15 :y
};

struct user {
	char name[20];
	int point;
	int count = 0;
	int score = 0;
};
user player[2];

/*ĳ���� ���� ��ǥ*/
int gotoxy(int x, int y);
void color(int color_number);
void setcursortype(CURSOR_TYPE c);
int point(int x, int y);
int min_point(int x, int y, int z);
void point_count();
void ball_shoot(int count);
void map_clear();
void ball_set(int count, int x, int y);
void Round1View();
void Round2View();
void Player1View();
void Player2View();
void rule();
void start();
void result(int a, int b);
void open_ball();
void open_main();
void show_main_1();
void show_main_2();
void show_main_3();
void map_draw();
void show_main();
void prn(string str);

/*�����Լ�*/
int main() {
	setcursortype(NOCURSOR); //Ŀ�� ���ֱ�
	system("title No Look Pass");
	system("mode con:cols=65 lines=30");
	gotoxy(28, 15);
	white;
	prn("Game Start!");
	system("cls");
	/* ������ �׷��� ȿ�� ���� */
	open_ball();
	open_main();
	/* ������ �׷��� ȿ�� ���� */

	show_main();
}

/*Ŀ�� ���ִ� �Լ�*/
void setcursortype(CURSOR_TYPE c)
{
	CONSOLE_CURSOR_INFO CurInfo;
	switch (c)
	{
	case NOCURSOR:
		CurInfo.dwSize = 1;
		CurInfo.bVisible = FALSE;
		break;
	case SOLIDCURSOR:
		CurInfo.dwSize = 100;
		CurInfo.bVisible = TRUE;
		break;
	case NORMALCURSOR:
		CurInfo.dwSize = 20;
		CurInfo.bVisible = TRUE;
		break;
	}
	SetConsoleCursorInfo(GetStdHandle(STD_OUTPUT_HANDLE), &CurInfo);
}

void color(int color_number)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color_number);
}

int gotoxy(int x, int y)                              //���� ���ϴ� ��ġ�� Ŀ�� �̵�
{
	COORD pos = { x - 1, y - 1 };                           //Ŀ���� X��ǥ���� -1 �Ѱ�, Y��ǥ���� -1�� ������ �̵�(�ʱ�ȭ)
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //�ܼ��� Ŀ�� ������ ���� //��� �׳� �����°Ŷ� �� �����;;;
	return 0;
}

void prn(string str) {
	int i = 0;
	while (i <= str.length() - 1) {
		char c = str.at(i);
		cout << c;
		i++;
		Sleep(100);
	}
}

void show_main() {
	setcursortype(NOCURSOR); //Ŀ�� ���ֱ�
	system("mode con:cols=130 lines=55");
	int menu = 1; // ����Ű �̵��� ���� ȭ���� ������ �޴���ȣ
	int in; // �Է� ���� �ƽ�Ű�ڵ尪

	show_main_1();
	in = (int)_getch();
	if (in == 13) {
	}
	while (1) {
		in = (int)_getch();
		/* ȭ���� ������ �޴���ȣ�� ����(1~3)�� ���� ���� �� ��ȣ���� */
		if (in == UP) {
			menu = menu - 1;
			if (menu == 0)
				menu = menu + 1;
		}
		else if (in == DOWN) {
			menu = menu + 1;
			if (menu == 4)
				menu = menu - 1;
		}
		else {
		}

		/* �޴� ��ȣ�� ���� ������ 3���� �޴� ȭ�� */
		switch (menu)
		{
		case 1:
			show_main_1();
			in = (int)_getch();
			if (in == 13) {

				player[0].score = 0; // ���� �ʱ�ȭ
				player[1].score = 0; // ���� �ʱ�ȭ
				start();
				Round1View();
				map_clear();
				for (int n = 1; n <= 6; n++) {
					if (n % 2 == 1) {
						Player1View();
						map_draw();
						ball_shoot(n);
					}
					else {
						Player2View();
						map_draw();
						ball_shoot(n);
					}
				}
				point_count();
				map_clear();
				Round2View();
				for (int n = 0; n <= 5; n++) {
					if (n % 2 == 1) {
						Player1View();
						map_draw();
						ball_shoot(n);
					}
					else {
						Player2View();
						map_draw();
						ball_shoot(n);
					}
				}
				point_count();
				map_clear();
				result(player[0].score, player[1].score);
			}
			break;
		case 2:
			show_main_2();
			in = (int)_getch();
			if (in == 13) {
				rule();
			}
			break;
		case 3:
			show_main_3();
			in = (int)_getch();
			if (in == 13) {
				exit(0);
			}
			break;
		default:
			break;
		}
	}
}

/* map�� �ʱ�ȭ �ϴ� �Լ� */
void map_clear() {
	system("cls");
	for (int a = 0; a < HEIGHT; a++) {
		for (int b = 0; b < WIDTH; b++) {
			if (map[a][b] == 3 || map[a][b] == 4)
				map[a][b] = 0;
			else if (map[a][b] == 33 || map[a][b] == 44)
				map[a][b] = 2;
		}
	}
}

void map_draw() {
	system("mode con:cols=40 lines=37");
	/* map �׸��� */
	for (int i = 0; i < HEIGHT; i++) {                              //map�� ���� //y��(����)
		for (int j = 0; j < WIDTH; j++) {                           //x��

			switch (map[i][j]) {
			case 0:                                       //map�� 0�̸� ��ĭ
				cout << "  ";
				break;
			case 1:                                       //map�� 1�̸� �渷 ����
				cout << "||";
				break;
			case 2:                                       //map�� 2�̸� �� ����
				cout << "��";
				break;
			case 3:
				cout << "��"; // map�� 3�̸� 1p �� ����
				break;
			case 4:
				cout << "��"; // map�� 3�̸� 1p �� ����
				break;
			case 33:
				cout << "��"; // map�� 3�̸� 1p �� ����
				break;
			case 44:
				cout << "��"; // map�� 3�̸� 1p �� ����
				break;
			}
		}
		puts(" ");
	}
}

void ball_set(int count, int x, int y)
{
	if (count % 2 == 1) { // 1p
		if (map[x][y] == 2)
			map[x][y] = 33;
		else {
			map[x][y] = 3;
		}
	}
	else if (count % 2 == 0) { // 2p
		if (map[x][y] == 2)
			map[x][y] = 44;
		else {
			map[x][y] = 4;
		}
	}
}

void Round1View() {
	system("mode con:cols=120 lines=40");
	system("cls");
	white;
	gotoxy(5, 4); printf("���������������������������������������������������������");
	white;
	gotoxy(5, 35); printf("���������������������������������������������������������");
	red;
	gotoxy(50, 19); prn("<< ROUND 1 >>");
	Sleep(3000);
}
void Round2View() {
	system("mode con:cols=120 lines=40");
	system("cls");
	white;
	gotoxy(5, 4); printf("���������������������������������������������������������");
	white;
	gotoxy(5, 35); printf("���������������������������������������������������������");
	red;
	gotoxy(50, 19); prn("<< ROUND 2 >>");
	Sleep(3000);
}
void Player1View() {
	system("mode con:cols=120 lines=40");
	system("cls");
	white;
	gotoxy(5, 4); printf("���������������������������������������������������������");
	color(10);
	gotoxy(55, 19); printf(player[0].name); //�Է¹��� �÷��̾��� �̸��� ����ϴ� �κ�
	gotoxy(55, 22);; printf("1p"); //1p���� �˷���
	white;
	gotoxy(5, 35); printf("���������������������������������������������������������");
	Sleep(3000);
	system("cls");
}
void Player2View() {
	system("mode con:cols=120 lines=40");
	system("cls");
	white;
	gotoxy(5, 4); printf("���������������������������������������������������������");
	color(10);
	gotoxy(55, 19); printf(player[1].name);
	gotoxy(55, 22); printf("2p"); //2p���� �˷���
	white;
	gotoxy(5, 35); printf("���������������������������������������������������������");
	Sleep(3000);
	system("cls");
}

/*http://m.blog.naver.com/cjsendqnssh/220039060254 ����*/
void ball_shoot(int count) {
	int t;
	char input;
	while (1) {
		for (int i = 0; i < 16; i++) {
			gotoxy(cx, cy);
			cout << " ";
			cx++;
			cx++;
			gotoxy(cx, cy);
			cout << cha;
			Sleep(30);
			if (_kbhit()) {
				input = _getch();
				if (input == SPACE) {
					while (1) {//space bar�� ��������
						for (int j = 0; j < 15; j++) {
							gotoxy(px, py);
							cout << " ";
							py++;
							gotoxy(px, py);
							cout << po;
							Sleep(30);
							if (_kbhit()) {
								input = _getch();
								if (input == SPACE) {
									bx = cx;
									by = cy - 1;
									gotoxy(px, py);
									cout << " ";
									for (int k = 0; k < cy - py; k++) {
										////////////////////////////////////////////////////////////
										if (map[by][(bx - 1) / 2] == 3 || map[by][(bx - 1) / 2] == 4 || map[by][(bx - 1) / 2] == 33 || map[by][(bx - 1) / 2] == 44) {
											break;
										}
										////////////////////////////////////////////////////////////
										gotoxy(bx, by);
										if (count % 2 == 1)
											cout << "��";
										else if (count % 2 == 0)
											cout << "��";

										gotoxy(bx, by + 1);
										cout << "  ";
										if (map[by][(bx - 1) / 2] == 2) {
											gotoxy(bx, by + 1);
											cout << "��";
										}
										by--;
										Sleep(100);
									}
									//////////////////////////////////////////////
									if (map[by][(bx - 1) / 2] == 3 || map[by][(bx - 1) / 2] == 4 || map[by][(bx - 1) / 2] == 33 || map[by][(bx - 1) / 2] == 44) {
										int by_ = by - 1;
										int c;

										for (int k = 0; k < (by - py) / 2 + 1; k++) {
											gotoxy(bx, by);
											if (map[by_ + 1][(bx - 1) / 2] == 3 || map[by_ + 1][(bx - 1) / 2] == 33) {
												c = 1;
											}
											else if (map[by_ + 1][(bx - 1) / 2] == 4 || map[by_ + 1][(bx - 1) / 2] == 44) {
												c = 2;
											}
											gotoxy(bx, by_);
											if (c % 2 == 1) {
												cout << "��";
											}
											else
												cout << "��";

											gotoxy(bx, by_ + 1);
											cout << "  ";

											if (map[by_][(bx - 1) / 2] == 2) {
												gotoxy(bx, by_ + 1);
												cout << "��";
											}
											by_--;
											Sleep(100);
										}
										ball_set(c, by_, (bx - 1) / 2); // �浹 �� �� ����
										if (map[by + 1][(bx - 1) / 2] == 3 || map[by + 1][(bx - 1) / 2] == 4)
											map[by - 1][(bx - 1) / 2] = 0;
										else if (map[by + 1][(bx - 1) / 2] == 33 || map[by + 1][(bx - 1) / 2] == 44)
											map[by - 1][(bx - 1) / 2] = 2;
									}
									ball_set(count, by, (bx - 1) / 2); // �浹 �� �� ����
								}
								Sleep(1000);
								cx = 3;
								py = 1;
								return;
							}
							//py = 2;
						}
						for (int j = 0; j < 15; j++) {
							gotoxy(px, py);
							cout << " ";
							py--;
							gotoxy(px, py);
							cout << po;
							Sleep(30);
							if (_kbhit()) {
								input = _getch();
								if (input == SPACE) {
									bx = cx;
									by = cy - 1;
									gotoxy(px, py);
									cout << " ";
									for (int k = 0; k < cy - py; k++) {
										////////////////////////////////////////////////////////////
										if (map[by][(bx - 1) / 2] == 3 || map[by][(bx - 1) / 2] == 4 || map[by][(bx - 1) / 2] == 33 || map[by][(bx - 1) / 2] == 44) {
											break;
										}
										////////////////////////////////////////////////////////////
										gotoxy(bx, by);
										if (count % 2 == 1)
											cout << "��";
										else if (count % 2 == 0)
											cout << "��";

										gotoxy(bx, by + 1);
										cout << "  ";
										if (map[by][(bx - 1) / 2] == 2) {
											gotoxy(bx, by + 1);
											cout << "��";
										}
										by--;
										Sleep(100);
									}
									//////////////////////////////////////////////
									if (map[by][(bx - 1) / 2] == 3 || map[by][(bx - 1) / 2] == 4 || map[by][(bx - 1) / 2] == 33 || map[by][(bx - 1) / 2] == 44) {
										int by_ = by - 1;
										int c;

										for (int k = 0; k < (by - py) / 2 + 1; k++) {
											gotoxy(bx, by);
											if (map[by_ + 1][(bx - 1) / 2] == 3 || map[by_ + 1][(bx - 1) / 2] == 33) {
												c = 1;
											}
											else if (map[by_ + 1][(bx - 1) / 2] == 4 || map[by_ + 1][(bx - 1) / 2] == 44) {
												c = 2;
											}
											gotoxy(bx, by_);
											if (c % 2 == 1) {
												cout << "��";
											}
											else
												cout << "��";

											gotoxy(bx, by_ + 1);
											cout << "  ";

											if (map[by_][(bx - 1) / 2] == 2) {
												gotoxy(bx, by_ + 1);
												cout << "��";
											}
											by_--;
											Sleep(100);
										}
										ball_set(c, by_, (bx - 1) / 2); // �浹 �� �� ����
										if (map[by + 1][(bx - 1) / 2] == 3 || map[by + 1][(bx - 1) / 2] == 4)
											map[by - 1][(bx - 1) / 2] = 0;
										else if (map[by + 1][(bx - 1) / 2] == 33 || map[by + 1][(bx - 1) / 2] == 44)
											map[by - 1][(bx - 1) / 2] = 2;
									}
									ball_set(count, by, (bx - 1) / 2); // �浹 �� �� ����
								}
								//////////////////////////////////////////////


								Sleep(1000);
								cx = 3;
								py = 1;
								return;

								//py = 2;
							}
						}
					}//space if��

				}
			}
		}


		for (int j = 0; j < 16; j++) {

			gotoxy(cx, cy);
			cout << " ";
			cx--;
			cx--;
			gotoxy(cx, cy);
			cout << cha;
			Sleep(30);
			if (_kbhit()) {
				input = _getch();
				if (input == SPACE) {
					while (1) {//space bar�� ��������
						for (int j = 0; j < 15; j++) {
							gotoxy(px, py);
							cout << " ";
							py++;
							gotoxy(px, py);
							cout << po;
							Sleep(30);
							if (_kbhit()) {
								input = _getch();
								if (input == SPACE) {
									bx = cx;
									by = cy - 1;
									gotoxy(px, py);
									cout << " ";
									for (int k = 0; k < cy - py; k++) {
										////////////////////////////////////////////////////////////
										if (map[by][(bx - 1) / 2] == 3 || map[by][(bx - 1) / 2] == 4 || map[by][(bx - 1) / 2] == 33 || map[by][(bx - 1) / 2] == 44) {
											break;
										}
										////////////////////////////////////////////////////////////
										gotoxy(bx, by);
										if (count % 2 == 1)
											cout << "��";
										else if (count % 2 == 0)
											cout << "��";

										gotoxy(bx, by + 1);
										cout << "  ";
										if (map[by][(bx - 1) / 2] == 2) {
											gotoxy(bx, by + 1);
											cout << "��";
										}
										by--;
										Sleep(100);
									}
									//////////////////////////////////////////////
									if (map[by][(bx - 1) / 2] == 3 || map[by][(bx - 1) / 2] == 4 || map[by][(bx - 1) / 2] == 33 || map[by][(bx - 1) / 2] == 44) {
										int by_ = by - 1;
										int c;

										for (int k = 0; k < (by - py) / 2 + 1; k++) {
											gotoxy(bx, by);
											if (map[by_ + 1][(bx - 1) / 2] == 3 || map[by_ + 1][(bx - 1) / 2] == 33) {
												c = 1;
											}
											else if (map[by_ + 1][(bx - 1) / 2] == 4 || map[by_ + 1][(bx - 1) / 2] == 44) {
												c = 2;
											}
											gotoxy(bx, by_);
											if (c % 2 == 1) {
												cout << "��";
											}
											else
												cout << "��";

											gotoxy(bx, by_ + 1);
											cout << "  ";

											if (map[by_][(bx - 1) / 2] == 2) {
												gotoxy(bx, by_ + 1);
												cout << "��";
											}
											by_--;
											Sleep(100);
										}
										ball_set(c, by_, (bx - 1) / 2); // �浹 �� �� ����
										if (map[by + 1][(bx - 1) / 2] == 3 || map[by + 1][(bx - 1) / 2] == 4)
											map[by - 1][(bx - 1) / 2] = 0;
										else if (map[by + 1][(bx - 1) / 2] == 33 || map[by + 1][(bx - 1) / 2] == 44)
											map[by - 1][(bx - 1) / 2] = 2;
									}
									ball_set(count, by, (bx - 1) / 2); // �浹 �� �� ����
								}
								//////////////////////////////////////////////

								Sleep(1000);
								cx = 3;
								py = 1;
								return;

								//py = 2;
							}
						}
						for (int j = 0; j < 15; j++) {
							gotoxy(px, py);
							cout << " ";
							py--;
							gotoxy(px, py);
							cout << po;
							Sleep(30);
							if (_kbhit()) {
								input = _getch();
								if (input == SPACE) {
									bx = cx;
									by = cy - 1;
									gotoxy(px, py);
									cout << " ";
									for (int k = 0; k < cy - py; k++) {
										////////////////////////////////////////////////////////////
										if (map[by][(bx - 1) / 2] == 3 || map[by][(bx - 1) / 2] == 4 || map[by][(bx - 1) / 2] == 33 || map[by][(bx - 1) / 2] == 44) {
											break;
										}
										////////////////////////////////////////////////////////////
										gotoxy(bx, by);
										if (count % 2 == 1)
											cout << "��";
										else if (count % 2 == 0)
											cout << "��";

										gotoxy(bx, by + 1);
										cout << "  ";
										if (map[by][(bx - 1) / 2] == 2) {
											gotoxy(bx, by + 1);
											cout << "��";
										}
										by--;
										Sleep(100);
									}
									//////////////////////////////////////////////
									if (map[by][(bx - 1) / 2] == 3 || map[by][(bx - 1) / 2] == 4 || map[by][(bx - 1) / 2] == 33 || map[by][(bx - 1) / 2] == 44) {
										int by_ = by - 1;
										int c;

										for (int k = 0; k < (by - py) / 2 + 1; k++) {
											gotoxy(bx, by);
											if (map[by_ + 1][(bx - 1) / 2] == 3 || map[by_ + 1][(bx - 1) / 2] == 33) {
												c = 1;
											}
											else if (map[by_ + 1][(bx - 1) / 2] == 4 || map[by_ + 1][(bx - 1) / 2] == 44) {
												c = 2;
											}
											gotoxy(bx, by_);
											if (c % 2 == 1) {
												cout << "��";
											}
											else
												cout << "��";

											gotoxy(bx, by_ + 1);
											cout << "  ";

											if (map[by_][(bx - 1) / 2] == 2) {
												gotoxy(bx, by_ + 1);
												cout << "��";
											}
											by_--;
											Sleep(100);
										}
										ball_set(c, by_, (bx - 1) / 2); // �浹 �� �� ����
										if (map[by + 1][(bx - 1) / 2] == 3 || map[by + 1][(bx - 1) / 2] == 4)
											map[by - 1][(bx - 1) / 2] = 0;
										else if (map[by + 1][(bx - 1) / 2] == 33 || map[by + 1][(bx - 1) / 2] == 44)
											map[by - 1][(bx - 1) / 2] = 2;
									}
									ball_set(count, by, (bx - 1) / 2); // �浹 �� �� ����
								}
								//////////////////////////////////////////////

								Sleep(1000);
								cx = 3;
								py = 1;
								return;

								//py = 2;
							};
						}
					}

				}
			}
		}
	}
}

/* 3���� ball �߿��� ���� ����� ball�� �Ÿ��� ���ϴ� �Լ� */
int min_point(int x, int y, int z) {
	int temp = x;
	if (temp > y)
		temp = y;
	if (temp > z)
		temp = z;
	return temp;
}

/* sqrt�Լ��� ����ؼ� ball�� �Ÿ��� ���ϴ� �Լ� */
int point(int x, int y) {
	int result = 0;
	x = x - 9;
	y = y - 6;
	if (x < 0)
		x = -x;
	if (y < 0)
		y = -y;

	result = sqrt((x*x) + (y*y));

	return result;
}

/* ����ڵ��� ball�� �Ÿ��� ���ϰ� ������ ������ ��ȯ�ϴ� �Լ� */
void point_count() {
	int m = 0;
	int p = 0;
	int p1 = 0, p2 = 0;
	arr[3] = { 0, };
	player[0].count = 0;
	player[1].count = 0;
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (map[i][j] == 3 || map[i][j] == 33) {
				p = point(j, i);
				arr[m] = p;
				m++;
				if (p < 5)
					player[0].count++;
			}
		}
	}
	p1 = min_point(arr[0], arr[1], arr[2]);
	m = 0;
	arr[3] = { 0, };
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (map[i][j] == 4 || map[i][j] == 44) {
				p = point(j, i);
				arr[m] = p;
				m++;
				if (p < 5)
					player[1].count++;
			}
		}
	}
	p2 = min_point(arr[0], arr[1], arr[2]);

	if (p1 < p2)
		player[0].score += player[0].count;
	if (p2 < p1) {
		player[1].score += player[1].count;
	}
	if (p1 == p2) {
		player[0].score += player[0].count;
		player[1].score += player[1].count;
	}
}

void rule() {
	system("mode con:cols=100 lines=45");
	system("cls");
	color(7);
	gotoxy(5, 4); printf("-------------------------------------------------------------------------------------------");
	gotoxy(5, 5); printf("\t\t\t\t\t     �ݱ�Ģ�����\t\t\t\t\t\t");
	gotoxy(5, 6); printf("-------------------------------------------------------------------------------------------");
	gotoxy(5, 40); printf("-------------------------------------------------------------------------------------------");
	color(2);
	gotoxy(3, 8); printf("\t\t 1. SPACE�ٸ� ������ ������ ���� ����� �ӵ��� ������ �� �־�");
	gotoxy(3, 10); printf("\t\t 2. �� ���� 3���� ������ ������ ���鼭 ������ ����");
	gotoxy(3, 12); printf("\t\t 3. ��� ������ ���ȿ� �ִ����� ���߾ӿ� ���� ����� ������ �ִ����� �̰�  ");
	gotoxy(3, 14); printf("\t\t 4. �����ϴ� ���� �Ҹ��ϴ� 2ground���� ���Ĵ� �ٲ�� ��  ");
	gotoxy(3, 16); printf("\t\t 5. 2���� ������ ������ ��, ��, �и� ��������  \n");
	color(9);
	gotoxy(5, 18); printf("���������� ���͸� �����ּ���\n");
	GdiplusStartupInput m_sGSI;
	ULONG_PTR m_lpToken = NULL;
	GdiplusStartup(&m_lpToken, &m_sGSI, NULL);

	Graphics *pGraphics = new Graphics(GetDC(GetConsoleWindow()));
	Image* pImage = new Image(L"�蹫��.png");
	pGraphics->DrawImage(pImage, 130, 320);

	int in = (int)_getch();
	if (in == 13) {
		delete pImage;
		delete pGraphics;
		GdiplusShutdown(m_lpToken);
		show_main();
	}
	else {
		rule();
	}
}

void start() {//�÷��̾� �Է¹ޱ�
	system("mode con:cols=40 lines=20");
	system("cls");

	gotoxy(5, 5);
	cout << "�÷��̾� �̸��� �Է��Ͻÿ�.";
	gotoxy(5, 12);
	cout << "1P : ";
	cin >> player[0].name;
	gotoxy(5, 15);
	cout << "2P : ";
	cin >> player[1].name;
	system("mode con:cols=40 lines=40");
}

void result(int a, int b)
{
	system("mode con:cols=135 lines=30");
	int score1 = a, score2 = b;//1P ����, 2P ����
	system("cls");
	Sleep(1000);

	if (score1 > score2) {//1P�� �̰��� ��쿡 ��Ÿ���� �׷���

		system("cls");
		color(3);
		cout << "\n\n\n";
		printf("             �ܡܡܡ�              �ܡܡܡܡܡܡܡܡܡ�                      �ܡܡܡܡ�          �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("           �ܡܡܡܡ�              �ܡܡܡܡܡܡܡܡܡܡ�                  �ܡܡܡܡ�            �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("         �ܡܡܡܡܡ�              �ܡܡܡܡܡܡܡܡܡܡܡ�              �ܡܡܡܡ�              �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("       �ܡܡ�  �ܡܡ�              �ܡܡܡ�        �ܡܡܡ�            �ܡܡܡܡܡܡ�                          �ܡܡ�    �ܡ�   \n");
		printf("     �ܡܡ�    �ܡܡ�              �ܡܡܡ�        �ܡܡܡ�          �ܡܡܡ�   �ܡܡܡ�                       �ܡܡ�    �ܡ�   \n");
		printf("               �ܡܡ�              �ܡܡܡܡܡܡܡܡܡܡܡ�        �ܡܡܡ�       �ܡܡܡ�                     �ܡܡ�    �ܡ�   \n");
		printf("               �ܡܡ�              �ܡܡܡܡܡܡܡܡܡܡ�        �ܡܡܡ�           �ܡܡܡ�                   �ܡܡ�    �ܡ�   \n");
		printf("               �ܡܡ�              �ܡܡܡܡܡܡܡܡܡ�                                          �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("               �ܡܡ�              �ܡܡ�                      �ܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡ�  �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("               �ܡܡ�              �ܡܡ�                      �ܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡ�  �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("               �ܡܡ�              �ܡܡ�                                                        �ܡܡ�                  �ܡ�   \n");
		printf("               �ܡܡ�              �ܡܡ�                                 �ܡܡܡܡ�             �ܡܡ�                  �ܡ�   \n");
		printf("               �ܡܡ�              �ܡܡ�                               �ܡܡܡܡܡܡ�           �ܡܡ�                  �ܡ�   \n");
		printf("               �ܡܡ�              �ܡܡ�                             �ܡܡܡ�  �ܡܡܡ�         �ܡܡ�                  �ܡ�   \n");
		printf("               �ܡܡ�              �ܡܡ�                             �ܡܡ�      �ܡܡ�         �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("               �ܡܡ�              �ܡܡ�                             �ܡܡܡ�  �ܡܡܡ�         �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("     �ܡܡܡܡܡܡܡܡܡܡܡܡ�    �ܡܡ�                               �ܡܡܡܡܡܡ�           �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("     �ܡܡܡܡܡܡܡܡܡܡܡܡ� 1  �ܡܡ�                     1           �ܡܡܡܡ�           1                         �ܡ�   \n");
		Sleep(3000);
		system("cls");
		cout << "\n\n\n";
		printf("        �ܡ�           �ܡ�       �ܡܡ�        �ܡܡ�      �ܡ�                           �ܡ�         �ܡܡܡܡܡܡ�          \n");
		printf("         �ܡ�          �ܡ�       �ܡܡ�        �ܡܡ�      �ܡ�   �ܡܡܡܡܡܡܡܡ�      �ܡ�       �ܡܡܡܡܡܡܡܡ�        \n");
		printf(" �ܡܡܡܡܡܡܡܡܡ�  �ܡ�       �ܡܡ�        �ܡܡ�  �ܡܡܡ�   �ܡܡܡܡܡܡܡܡ�      �ܡ�     �ܡܡ�         �ܡܡ�       \n");
		printf(" �ܡܡܡܡܡܡܡܡܡ�  �ܡ�       �ܡܡܡܡܡܡܡܡܡ�  �ܡܡܡ�   �ܡ�                �ܡܡܡ�    �ܡܡ�           �ܡܡ�      \n");
		printf("       �ܡܡܡ�        �ܡܡܡ�   �ܡܡܡܡܡܡܡܡܡ�      �ܡ�   �ܡ�                �ܡܡܡ�   �ܡܡ�            �ܡܡ�      \n");
		printf("     �ܡܡܡܡܡ�      �ܡܡܡ�   �ܡܡ�        �ܡܡ�      �ܡ�   �ܡ�                    �ܡ�   �ܡܡ�            �ܡܡ�      \n");
		printf("    �ܡܡ�  �ܡܡ�     �ܡ�       �ܡܡ�        �ܡܡ�      �ܡ�   �ܡ�                    �ܡ�    �ܡܡ�          �ܡܡ�       \n");
		printf("     �ܡܡܡܡܡ�      �ܡ�       �ܡܡܡܡܡܡܡܡܡ�      �ܡ�   �ܡ�                    �ܡ�                  �ܡܡ�         \n");
		printf("       �ܡܡܡ�        �ܡ�       �ܡܡܡܡܡܡܡܡܡ�      �ܡ�   �ܡܡܡܡܡܡܡܡ�      �ܡ�                �ܡܡ�           \n");
		printf("                       �ܡ�                                 �ܡ�   �ܡܡܡܡܡܡܡܡ�      �ܡ�               �ܡܡ�            \n");
		printf("                       �ܡ�                                 �ܡ�                           �ܡ�               �ܡܡ�            \n");
		printf("                                                                                           �ܡ�               �ܡܡ�            \n");
		printf("      �ܡ�                          �ܡ�                                                   �ܡ�               �ܡܡ�            \n");
		printf("      �ܡ�                          �ܡ�                                                   �ܡ�                                 \n");
		printf("      �ܡܡܡܡܡܡܡܡܡܡܡ�      �ܡܡܡܡܡܡܡܡܡܡܡܡܡ�                           �ܡ�               �ܡܡ�            \n");
		printf("      �ܡܡܡܡܡܡܡܡܡܡܡ�      �ܡܡܡܡܡܡܡܡܡܡܡܡܡ�                           �ܡ�               �ܡܡ�            \n");
		Sleep(3000);
	}

	else if (score1 == score2) {//���º��϶� ��Ÿ���� �׷���

		system("cls");
		color(9);
		cout << "\n\n\n";
		printf("       �ܡܡܡܡܡܡܡܡܡ�                   �ܡܡܡܡ�                   �ܡܡ�        �ܡܡ�         �ܡܡܡܡܡ�            \n");
		printf("       �ܡܡܡܡܡܡܡܡܡ�                 �ܡܡܡܡܡܡ�                 �ܡܡ�        �ܡܡ�         �ܡܡܡܡܡ�            \n");
		printf("       �ܡܡ�        �ܡܡ�               �ܡܡܡ�  �ܡܡܡ�               �ܡܡܡܡܡܡܡܡܡ�         �ܡܡܡܡܡ�            \n");
		printf("       �ܡܡ�        �ܡܡ�              �ܡܡܡ�    �ܡܡܡ�              �ܡܡܡܡܡܡܡܡܡ�         �ܡܡܡܡܡ�            \n");
		printf("       �ܡܡܡܡܡܡܡܡܡ�             �ܡܡܡ�      �ܡܡܡ�             �ܡܡ�        �ܡܡ�         �ܡܡܡܡܡ�            \n");
		printf("       �ܡܡܡܡܡܡܡܡܡ�                                                �ܡܡܡܡܡܡܡܡܡ�         �ܡܡܡܡܡ�            \n");
		printf("                                     �ܡܡܡܡܡܡܡܡܡܡܡܡܡܡ�        �ܡܡܡܡܡܡܡܡܡ�         �ܡܡܡܡܡ�            \n");
		printf(" �ܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡ�    �ܡܡܡܡܡܡܡܡܡܡܡܡܡܡ�                                     �ܡܡܡܡܡ�            \n");
		printf(" �ܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡ�                                    �ܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡ�   �ܡܡܡܡܡ�            \n");
		printf("              �ܡܡ�                          �ܡܡܡܡ�             �ܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡ�    �ܡܡܡܡ�             \n");
		printf("              �ܡܡ�                        �ܡܡܡܡܡܡ�                        �ܡܡ�                  �ܡܡܡ�              \n");
		printf("              �ܡܡ�                       �ܡܡܡܡܡܡܡ�                       �ܡܡ�                                        \n");
		printf("              �ܡܡ�                       �ܡܡܡܡܡܡܡ�                       �ܡܡ�                  �ܡܡܡ�              \n");
		printf("              �ܡܡ�                        �ܡܡܡܡܡܡ�                        �ܡܡ�                  �ܡܡܡ�              \n");
		printf("                                              �ܡܡܡܡ�                          �ܡܡ�                  �ܡܡܡ�              \n");
		Sleep(3000);
		system("cls");
		cout << "\n\n\n";
		printf("        �ܡ�           �ܡ�       �ܡܡ�        �ܡܡ�      �ܡ�                           �ܡ�         �ܡܡܡܡܡܡ�          \n");
		printf("         �ܡ�          �ܡ�       �ܡܡ�        �ܡܡ�      �ܡ�   �ܡܡܡܡܡܡܡܡ�      �ܡ�       �ܡܡܡܡܡܡܡܡ�        \n");
		printf(" �ܡܡܡܡܡܡܡܡܡ�  �ܡ�       �ܡܡ�        �ܡܡ�  �ܡܡܡ�   �ܡܡܡܡܡܡܡܡ�      �ܡ�     �ܡܡ�         �ܡܡ�       \n");
		printf(" �ܡܡܡܡܡܡܡܡܡ�  �ܡ�       �ܡܡܡܡܡܡܡܡܡ�  �ܡܡܡ�   �ܡ�                �ܡܡܡ�    �ܡܡ�           �ܡܡ�      \n");
		printf("       �ܡܡܡ�        �ܡܡܡ�   �ܡܡܡܡܡܡܡܡܡ�      �ܡ�   �ܡ�                �ܡܡܡ�   �ܡܡ�            �ܡܡ�      \n");
		printf("     �ܡܡܡܡܡ�      �ܡܡܡ�   �ܡܡ�        �ܡܡ�      �ܡ�   �ܡ�                    �ܡ�   �ܡܡ�            �ܡܡ�      \n");
		printf("    �ܡܡ�  �ܡܡ�     �ܡ�       �ܡܡ�        �ܡܡ�      �ܡ�   �ܡ�                    �ܡ�    �ܡܡ�          �ܡܡ�       \n");
		printf("     �ܡܡܡܡܡ�      �ܡ�       �ܡܡܡܡܡܡܡܡܡ�      �ܡ�   �ܡ�                    �ܡ�                  �ܡܡ�         \n");
		printf("       �ܡܡܡ�        �ܡ�       �ܡܡܡܡܡܡܡܡܡ�      �ܡ�   �ܡܡܡܡܡܡܡܡ�      �ܡ�                �ܡܡ�           \n");
		printf("                       �ܡ�                                 �ܡ�   �ܡܡܡܡܡܡܡܡ�      �ܡ�               �ܡܡ�            \n");
		printf("                       �ܡ�                                 �ܡ�                           �ܡ�               �ܡܡ�            \n");
		printf("                                                                                           �ܡ�               �ܡܡ�            \n");
		printf("      �ܡ�                          �ܡ�                                                   �ܡ�               �ܡܡ�            \n");
		printf("      �ܡ�                          �ܡ�                                                   �ܡ�                                 \n");
		printf("      �ܡܡܡܡܡܡܡܡܡܡܡ�      �ܡܡܡܡܡܡܡܡܡܡܡܡܡ�                           �ܡ�               �ܡܡ�            \n");
		printf("      �ܡܡܡܡܡܡܡܡܡܡܡ�      �ܡܡܡܡܡܡܡܡܡܡܡܡܡ�                           �ܡ�               �ܡܡ�            \n");
		Sleep(3000);
	}
	else {//2P�� �̰��� ��쿡 ��Ÿ���� �׷���

		system("cls");
		color(5);
		cout << "\n\n\n";
		printf("           �ܡܡܡܡܡ�            �ܡܡܡܡܡܡܡܡܡ�                      �ܡܡܡܡ�          �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("         �ܡܡܡܡܡܡܡ�          �ܡܡܡܡܡܡܡܡܡܡ�                  �ܡܡܡܡ�            �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("       �ܡܡܡܡܡܡܡܡܡ�        �ܡܡܡܡܡܡܡܡܡܡܡ�              �ܡܡܡܡ�              �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("     �ܡܡ�          �ܡܡ�        �ܡܡܡ�        �ܡܡܡ�            �ܡܡܡܡܡܡ�                          �ܡܡ�    �ܡ�   \n");
		printf("    �ܡܡ�            �ܡܡ�       �ܡܡܡ�        �ܡܡܡ�          �ܡܡܡ�   �ܡܡܡ�                       �ܡܡ�    �ܡ�   \n");
		printf("   �ܡܡ�              �ܡܡ�      �ܡܡܡܡܡܡܡܡܡܡܡ�        �ܡܡܡ�       �ܡܡܡ�                     �ܡܡ�    �ܡ�   \n");
		printf("   �ܡܡ�              �ܡܡ�      �ܡܡܡܡܡܡܡܡܡܡ�        �ܡܡܡ�           �ܡܡܡ�                   �ܡܡ�    �ܡ�   \n");
		printf("                       �ܡܡ�      �ܡܡܡܡܡܡܡܡܡ�                                          �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("                     �ܡܡ�        �ܡܡ�                      �ܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡ�  �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("                   �ܡܡ�          �ܡܡ�                      �ܡܡܡܡܡܡܡܡܡܡܡܡܡܡܡ�  �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("                 �ܡܡ�            �ܡܡ�                                                        �ܡܡ�                  �ܡ�   \n");
		printf("               �ܡܡ�              �ܡܡ�                                 �ܡܡܡܡ�             �ܡܡ�                  �ܡ�   \n");
		printf("             �ܡܡ�                �ܡܡ�                               �ܡܡܡܡܡܡ�           �ܡܡ�                  �ܡ�   \n");
		printf("           �ܡܡ�                  �ܡܡ�                             �ܡܡܡ�  �ܡܡܡ�         �ܡܡ�                  �ܡ�   \n");
		printf("         �ܡܡ�                    �ܡܡ�                             �ܡܡ�      �ܡܡ�         �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("       �ܡܡ�                      �ܡܡ�                             �ܡܡܡ�  �ܡܡܡ�         �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("     �ܡܡܡܡܡܡܡܡܡܡܡܡ�    �ܡܡ�                               �ܡܡܡܡܡܡ�           �ܡܡܡܡܡܡܡܡܡ�    �ܡ�   \n");
		printf("     �ܡܡܡܡܡܡܡܡܡܡܡܡ�    �ܡܡ�                                 �ܡܡܡܡ�                                     �ܡ�   \n");
		Sleep(3000);
		system("cls");
		cout << "\n\n\n";
		printf("        �ܡ�           �ܡ�       �ܡܡ�        �ܡܡ�      �ܡ�                           �ܡ�         �ܡܡܡܡܡܡ�          \n");
		printf("         �ܡ�          �ܡ�       �ܡܡ�        �ܡܡ�      �ܡ�   �ܡܡܡܡܡܡܡܡ�      �ܡ�       �ܡܡܡܡܡܡܡܡ�        \n");
		printf(" �ܡܡܡܡܡܡܡܡܡ�  �ܡ�       �ܡܡ�        �ܡܡ�  �ܡܡܡ�   �ܡܡܡܡܡܡܡܡ�      �ܡ�     �ܡܡ�         �ܡܡ�       \n");
		printf(" �ܡܡܡܡܡܡܡܡܡ�  �ܡ�       �ܡܡܡܡܡܡܡܡܡ�  �ܡܡܡ�   �ܡ�                �ܡܡܡ�    �ܡܡ�           �ܡܡ�      \n");
		printf("       �ܡܡܡ�        �ܡܡܡ�   �ܡܡܡܡܡܡܡܡܡ�      �ܡ�   �ܡ�                �ܡܡܡ�   �ܡܡ�            �ܡܡ�      \n");
		printf("     �ܡܡܡܡܡ�      �ܡܡܡ�   �ܡܡ�        �ܡܡ�      �ܡ�   �ܡ�                    �ܡ�   �ܡܡ�            �ܡܡ�      \n");
		printf("    �ܡܡ�  �ܡܡ�     �ܡ�       �ܡܡ�        �ܡܡ�      �ܡ�   �ܡ�                    �ܡ�    �ܡܡ�          �ܡܡ�       \n");
		printf("     �ܡܡܡܡܡ�      �ܡ�       �ܡܡܡܡܡܡܡܡܡ�      �ܡ�   �ܡ�                    �ܡ�                  �ܡܡ�         \n");
		printf("       �ܡܡܡ�        �ܡ�       �ܡܡܡܡܡܡܡܡܡ�      �ܡ�   �ܡܡܡܡܡܡܡܡ�      �ܡ�                �ܡܡ�           \n");
		printf("                       �ܡ�                                 �ܡ�   �ܡܡܡܡܡܡܡܡ�      �ܡ�               �ܡܡ�            \n");
		printf("                       �ܡ�                                 �ܡ�                           �ܡ�               �ܡܡ�            \n");
		printf("                                                                                           �ܡ�               �ܡܡ�            \n");
		printf("      �ܡ�                          �ܡ�                                                   �ܡ�               �ܡܡ�            \n");
		printf("      �ܡ�                          �ܡ�                                                   �ܡ�                                 \n");
		printf("      �ܡܡܡܡܡܡܡܡܡܡܡ�      �ܡܡܡܡܡܡܡܡܡܡܡܡܡ�                           �ܡ�               �ܡܡ�            \n");
		printf("      �ܡܡܡܡܡܡܡܡܡܡܡ�      �ܡܡܡܡܡܡܡܡܡܡܡܡܡ�                           �ܡ�               �ܡܡ�            \n");
		Sleep(3000);
	}
	int in = (int)_getch();
	if (in == 13) {
		show_main();
	}
}

void open_ball() {
	system("mode con:cols=130 lines=45");
	color(7);
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                 �ݡݡݡݡݡݡݡݡ�                                                     �� \n");
	printf("   ��                                                  �ݡݡݡݡݡݡݡ�                                                      �� \n");
	printf("   ��                                                   �ݡݡݡݡݡݡ�                                                       �� \n");
	printf("   ��                                                     �ݡݡݡݡ�                                                         �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
}

void open_main() {
	Sleep(200);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO                                                                                     �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO                                                                               �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO                                                                                     �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO                                                                                     �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO                                                                                     �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO                                                                                     �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO                                                                                     �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO                                                                                     �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");

	Sleep(200);
	system("cls");
	color(4);
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO                                                                                     �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO                                                                                     �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO                                                                                     �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO                                                                                     �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                               LLLL                  OOOOOOO              OOOOOOO        KKK        KKK �� \n");
	printf("   ��                                               LLLL                OOO     OOO          OOO     OOO      KKK       KKK  �� \n");
	printf("   ��                                               LLLL               OOO       OOO        OOO       OOO     KKK      KKK   �� \n");
	printf("   ��                                               LLLL              OOO         OOO      OOO         OOO    KKK     KKK    �� \n");
	printf("   ��                                               LLLL             OOO           OOO    OOO           OOO   KKK    KKK     �� \n");
	printf("   ��                                               LLLL            OOO             OOO  OOO             OOO  KKK   KKK      �� \n");
	printf("   ��                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO                                                                                     �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO                                                                                     �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                               LLLL                  OOOOOOO              OOOOOOO        KKK        KKK �� \n");
	printf("   ��                                               LLLL                OOO     OOO          OOO     OOO      KKK       KKK  �� \n");
	printf("   ��                                               LLLL               OOO       OOO        OOO       OOO     KKK      KKK   �� \n");
	printf("   ��                                               LLLL              OOO         OOO      OOO         OOO    KKK     KKK    �� \n");
	printf("   ��                                               LLLL             OOO           OOO    OOO           OOO   KKK    KKK     �� \n");
	printf("   ��                                               LLLL            OOO             OOO  OOO             OOO  KKK   KKK      �� \n");
	printf("   ��                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   ��                                               LLLL            OOO             OOO  OOO             OOO  KKK KKK        �� \n");
	printf("   ��                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   ��                                               LLLL             OOO           OOO    OOO           OOO   KKK   KKK      �� \n");
	printf("   ��                                               LLLL              OOO         OOO      OOO         OOO    KKK    KKK     �� \n");
	printf("   ��                                               LLLL               OOO       OOO        OOO       OOO     KKK     KKK    �� \n");
	printf("   ��                                               LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   �� \n");
	printf("   ��                                               LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO                                                                                     �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO                                                                                     �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                               LLLL                  OOOOOOO              OOOOOOO        KKK        KKK �� \n");
	printf("   ��                                               LLLL                OOO     OOO          OOO     OOO      KKK       KKK  �� \n");
	printf("   ��                                               LLLL               OOO       OOO        OOO       OOO     KKK      KKK   �� \n");
	printf("   ��                                               LLLL              OOO         OOO      OOO         OOO    KKK     KKK    �� \n");
	printf("   ��                                               LLLL             OOO           OOO    OOO           OOO   KKK    KKK     �� \n");
	printf("   ��                                               LLLL            OOO             OOO  OOO             OOO  KKK   KKK      �� \n");
	printf("   ��                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   ��                                               LLLL            OOO             OOO  OOO             OOO  KKK KKK        �� \n");
	printf("   ��                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   ��                                               LLLL             OOO           OOO    OOO           OOO   KKK   KKK      �� \n");
	printf("   ��                                               LLLL              OOO         OOO      OOO         OOO    KKK    KKK     �� \n");
	printf("   ��                                               LLLL               OOO       OOO        OOO       OOO     KKK     KKK    �� \n");
	printf("   ��                                               LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   �� \n");
	printf("   ��                                               LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO                                                                                     �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO                                                                                   �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO                                                                                  �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO                                                                                 �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO                                                                                �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO                                                                               �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO      LLLL                  OOOOOOO              OOOOOOO        KKK        KKK �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO       LLLL                OOO     OOO          OOO     OOO      KKK       KKK  �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO        LLLL               OOO       OOO        OOO       OOO     KKK      KKK   �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO         LLLL              OOO         OOO      OOO         OOO    KKK     KKK    �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO          LLLL             OOO           OOO    OOO           OOO   KKK    KKK     �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO            LLLL            OOO             OOO  OOO             OOO  KKK   KKK      �� \n");
	printf("   ��                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   ��                                               LLLL            OOO             OOO  OOO             OOO  KKK KKK        �� \n");
	printf("   ��                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   ��                                               LLLL             OOO           OOO    OOO           OOO   KKK   KKK      �� \n");
	printf("   ��                                               LLLL              OOO         OOO      OOO         OOO    KKK    KKK     �� \n");
	printf("   ��                                               LLLL               OOO       OOO        OOO       OOO     KKK     KKK    �� \n");
	printf("   ��                                               LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   �� \n");
	printf("   ��                                               LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO            LLLL                  OOOOOOO              OOOOOOO        KKK        KKK �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO          LLLL                OOO     OOO          OOO     OOO      KKK       KKK  �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK      KKK   �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK     KKK    �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK    KKK     �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK   KKK      �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK KKK        �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK   KKK      �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK    KKK     �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK     KKK    �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO          LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO            LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO            LLLL                  OOOOOOO              OOOOOOO        KKK        KKK �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO          LLLL                OOO     OOO          OOO     OOO      KKK       KKK  �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK      KKK   �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK     KKK    �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK    KKK     �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK   KKK      �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK KKK        �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK   KKK      �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK    KKK     �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK     KKK    �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO          LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO            LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��            PPPPPPPPPPPPPPP                    A                 SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP          PPP                  AAA                SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP           PPP                AAAAA               SSS                     SSS                            �� \n");
	printf("   ��            PPP            PPP              AAA AAA              SSS                     SSS                            �� \n");
	printf("   ��            PPP             PPP            AAA   AAA             SSS                     SSS                            �� \n");
	printf("   ��            PPP             PPP           AAA     AAA            SSS                     SSS                            �� \n");
	printf("   ��            PPP            PPP           AAA       AAA           SSS                     SSS                            �� \n");
	printf("   ��            PPP           PPP           AAA         AAA          SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO            LLLL                  OOOOOOO              OOOOOOO        KKK        KKK �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO          LLLL                OOO     OOO          OOO     OOO      KKK       KKK  �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK      KKK   �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK     KKK    �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK    KKK     �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK   KKK      �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK KKK        �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK   KKK      �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK    KKK     �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK     KKK    �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO          LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO            LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��            PPPPPPPPPPPPPPP                    A                 SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP          PPP                  AAA                SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP           PPP                AAAAA               SSS                     SSS                            �� \n");
	printf("   ��            PPP            PPP              AAA AAA              SSS                     SSS                            �� \n");
	printf("   ��            PPP             PPP            AAA   AAA             SSS                     SSS                            �� \n");
	printf("   ��            PPP             PPP           AAA     AAA            SSS                     SSS                            �� \n");
	printf("   ��            PPP            PPP           AAA       AAA           SSS                     SSS                            �� \n");
	printf("   ��            PPP           PPP           AAA         AAA          SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPPPPPPPPPPPPPP            AAAAAAAAAAAAAAAAA         SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP                       AAAAAAAAAAAAAAAAAAA                       SSS                    SSS              �� \n");
	printf("   ��            PPP                      AAA               AAA                      SSS                    SSS              �� \n");
	printf("   ��            PPP                      AAA               AAA                      SSS                    SSS              �� \n");
	printf("   ��            PPP                     AAA                 AAA                     SSS                    SSS              �� \n");
	printf("   ��            PPP                     AAA                 AAA                     SSS                    SSS              �� \n");
	printf("   ��            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	Sleep(200);
	system("cls");
}

void show_main_1() {
	system("cls");
	color(5);
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO            LLLL                  OOOOOOO              OOOOOOO        KKK        KKK �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO          LLLL                OOO     OOO          OOO     OOO      KKK       KKK  �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK      KKK   �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK     KKK    �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK    KKK     �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK   KKK      �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK KKK        �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK   KKK      �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK    KKK     �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK     KKK    �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO          LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO            LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��            PPPPPPPPPPPPPPP                    A                 SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP          PPP                  AAA                SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP           PPP                AAAAA               SSS                     SSS                            �� \n");
	printf("   ��            PPP            PPP              AAA AAA              SSS                     SSS                            �� \n");
	printf("   ��            PPP             PPP            AAA   AAA             SSS                     SSS                            �� \n");
	printf("   ��            PPP             PPP           AAA     AAA            SSS                     SSS                            �� \n");
	printf("   ��            PPP            PPP           AAA       AAA           SSS                     SSS                            �� \n");
	printf("   ��            PPP           PPP           AAA         AAA          SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPPPPPPPPPPPPPP            AAAAAAAAAAAAAAAAA         SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP                       AAAAAAAAAAAAAAAAAAA                       SSS                    SSS              �� \n");
	printf("   ��            PPP                      AAA               AAA                      SSS                    SSS              �� \n");
	printf("   ��            PPP                      AAA               AAA                      SSS                    SSS              �� \n");
	printf("   ��            PPP                     AAA                 AAA                     SSS                    SSS              �� \n");
	printf("   ��            PPP                     AAA                 AAA                     SSS                    SSS              �� \n");
	printf("   ��            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("\n\n\n");
	printf("                                                        �� ���ӽ��� ��                                                        \n");
	printf("\n                                                           ���Ӽ���                                                             \n");
	printf("\n                                                           ��������                                                           \n");
}

void show_main_2() {
	system("cls");
	color(2);
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO            LLLL                  OOOOOOO              OOOOOOO        KKK        KKK �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO          LLLL                OOO     OOO          OOO     OOO      KKK       KKK  �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK      KKK   �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK     KKK    �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK    KKK     �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK   KKK      �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK KKK        �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK   KKK      �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK    KKK     �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK     KKK    �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO          LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO            LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��            PPPPPPPPPPPPPPP                    A                 SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP          PPP                  AAA                SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP           PPP                AAAAA               SSS                     SSS                            �� \n");
	printf("   ��            PPP            PPP              AAA AAA              SSS                     SSS                            �� \n");
	printf("   ��            PPP             PPP            AAA   AAA             SSS                     SSS                            �� \n");
	printf("   ��            PPP             PPP           AAA     AAA            SSS                     SSS                            �� \n");
	printf("   ��            PPP            PPP           AAA       AAA           SSS                     SSS                            �� \n");
	printf("   ��            PPP           PPP           AAA         AAA          SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPPPPPPPPPPPPPP            AAAAAAAAAAAAAAAAA         SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP                       AAAAAAAAAAAAAAAAAAA                       SSS                    SSS              �� \n");
	printf("   ��            PPP                      AAA               AAA                      SSS                    SSS              �� \n");
	printf("   ��            PPP                      AAA               AAA                      SSS                    SSS              �� \n");
	printf("   ��            PPP                     AAA                 AAA                     SSS                    SSS              �� \n");
	printf("   ��            PPP                     AAA                 AAA                     SSS                    SSS              �� \n");
	printf("   ��            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("\n\n\n");
	printf("                                                           ���ӽ���                                                           \n");
	printf("\n                                                        �� ���Ӽ��� ��                                                          \n");
	printf("\n                                                           ��������                                                           \n");
}

void show_main_3() {
	system("cls");
	color(3);
	printf("\n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   �� NNNN            NNN        OOOOOOO            LLLL                  OOOOOOO              OOOOOOO        KKK        KKK �� \n");
	printf("   �� NNNNN           NNN      OOO     OOO          LLLL                OOO     OOO          OOO     OOO      KKK       KKK  �� \n");
	printf("   �� NNNNNN          NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK      KKK   �� \n");
	printf("   �� NNN NNN         NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK     KKK    �� \n");
	printf("   �� NNN  NNN        NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK    KKK     �� \n");
	printf("   �� NNN   NNN       NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK   KKK      �� \n");
	printf("   �� NNN    NNN      NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   �� NNN     NNN     NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK KKK        �� \n");
	printf("   �� NNN      NNN    NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       �� \n");
	printf("   �� NNN       NNN   NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK   KKK      �� \n");
	printf("   �� NNN        NNN  NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK    KKK     �� \n");
	printf("   �� NNN         NNN NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK     KKK    �� \n");
	printf("   �� NNN          NNNNNN      OOO     OOO          LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   �� \n");
	printf("   �� NNN           NNNNN        OOOOOOO            LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��            PPPPPPPPPPPPPPP                    A                 SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP          PPP                  AAA                SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP           PPP                AAAAA               SSS                     SSS                            �� \n");
	printf("   ��            PPP            PPP              AAA AAA              SSS                     SSS                            �� \n");
	printf("   ��            PPP             PPP            AAA   AAA             SSS                     SSS                            �� \n");
	printf("   ��            PPP             PPP           AAA     AAA            SSS                     SSS                            �� \n");
	printf("   ��            PPP            PPP           AAA       AAA           SSS                     SSS                            �� \n");
	printf("   ��            PPP           PPP           AAA         AAA          SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPPPPPPPPPPPPPP            AAAAAAAAAAAAAAAAA         SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP                       AAAAAAAAAAAAAAAAAAA                       SSS                    SSS              �� \n");
	printf("   ��            PPP                      AAA               AAA                      SSS                    SSS              �� \n");
	printf("   ��            PPP                      AAA               AAA                      SSS                    SSS              �� \n");
	printf("   ��            PPP                     AAA                 AAA                     SSS                    SSS              �� \n");
	printf("   ��            PPP                     AAA                 AAA                     SSS                    SSS              �� \n");
	printf("   ��            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ��                                                                                                                        �� \n");
	printf("   ���������������������������������������������������������������������������������������������������������������������������� \n");
	printf("\n\n\n");
	printf("                                                           ���ӽ���                                                           \n");
	printf("\n                                                           ���Ӽ���                                                             \n");
	printf("\n                                                        �� �������� ��                                                        \n");
}

//������¥ : 2017-06-22(cmd â ũ�� ����)