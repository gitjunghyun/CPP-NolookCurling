#include <iostream>
#include <windows.h> //System(cls) , Sleep() 噙朝 ④渦だ橾
#include <conio.h> // kbhit(), getch() 噙朝 ④渦だ橾
#include <time.h>
#include <string> 
#include <stdio.h>
#include <tchar.h>
#include <gdiplus.h>
#pragma comment(lib, "gdiplus")
/* GDI 餌辨徹擊 霤褻 */
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
#define red SetConsoleTextAttribute( col,12 ); //說
#define white SetConsoleTextAttribute( col,15); //��


typedef enum { NOCURSOR, SOLIDCURSOR, NORMALCURSOR } CURSOR_TYPE;   //醴憮 婦溼

int bx;
int by; //stone(獐)
int cx = 3, cy = HEIGHT + 1;  //議葛攪 夔樂謝ル
int px = 2 * WIDTH + 1, py = 1;
char cha[3] = "褡";                                       // 頂 議葛攪
char po[3] = "Ｂ";
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

/*議葛攪 婦溼 謝ル*/
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

/*詭檣л熱*/
int main() {
	setcursortype(NOCURSOR); //醴憮 橈擁晦
	system("title No Look Pass");
	system("mode con:cols=65 lines=30");
	gotoxy(28, 15);
	white;
	prn("Game Start!");
	system("cls");
	/* 螃Щ棚 斜楚а �膩� 褒ч */
	open_ball();
	open_main();
	/* 螃Щ棚 斜楚а �膩� 謙猿 */

	show_main();
}

/*醴憮 橈擁朝 л熱*/
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

int gotoxy(int x, int y)                              //頂陛 錳ж朝 嬪纂煎 醴憮 檜翕
{
	COORD pos = { x - 1, y - 1 };                           //醴憮陛 X謝ル縑憮 -1 и高, Y謝ル縑憮 -1и 高戲煎 檜翕(蟾晦��)
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); //夔樂曖 醴憮 ん雖暮 雖薑 //樽朝 斜傖 陛螳螞剪塭 澀 路塭厄;;;
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
	setcursortype(NOCURSOR); //醴憮 橈擁晦
	system("mode con:cols=130 lines=55");
	int menu = 1; // 寞щ酈 檜翕縑 評艇 �飛橉� 薯橫й 詭景廓��
	int in; // 殮溘 嫡擊 嬴蝶酈囀萄高

	show_main_1();
	in = (int)_getch();
	if (in == 13) {
	}
	while (1) {
		in = (int)_getch();
		/* �飛橉� 薯橫й 詭景廓�ㄟ� 彰嬪(1~3)蒂 慇橫 陬擊 陽 廓��薯橫 */
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

		/* 詭景 廓�ˋ� 評塭憮 爾罹還 3偃曖 詭景 �飛� */
		switch (menu)
		{
		case 1:
			show_main_1();
			in = (int)_getch();
			if (in == 13) {

				player[0].score = 0; // 薄熱 蟾晦��
				player[1].score = 0; // 薄熱 蟾晦��
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

/* map擊 蟾晦�� ж朝 л熱 */
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
	/* map 斜葬晦 */
	for (int i = 0; i < HEIGHT; i++) {                              //map縑 評塭憮 //y高(堪檜)
		for (int j = 0; j < WIDTH; j++) {                           //x高

			switch (map[i][j]) {
			case 0:                                       //map檜 0檜賊 綴蘊
				cout << "  ";
				break;
			case 1:                                       //map檜 1檜賊 望虞 儅撩
				cout << "||";
				break;
			case 2:                                       //map檜 2檜賊 錳 儅撩
				cout << "仄";
				break;
			case 3:
				cout << "≡"; // map檜 3檜賊 1p 奢 儅撩
				break;
			case 4:
				cout << "≒"; // map檜 3檜賊 1p 奢 儅撩
				break;
			case 33:
				cout << "≡"; // map檜 3檜賊 1p 奢 儅撩
				break;
			case 44:
				cout << "≒"; // map檜 3檜賊 1p 奢 儅撩
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
	gotoxy(5, 4); printf("﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥");
	white;
	gotoxy(5, 35); printf("﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥");
	red;
	gotoxy(50, 19); prn("<< ROUND 1 >>");
	Sleep(3000);
}
void Round2View() {
	system("mode con:cols=120 lines=40");
	system("cls");
	white;
	gotoxy(5, 4); printf("﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥");
	white;
	gotoxy(5, 35); printf("﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥");
	red;
	gotoxy(50, 19); prn("<< ROUND 2 >>");
	Sleep(3000);
}
void Player1View() {
	system("mode con:cols=120 lines=40");
	system("cls");
	white;
	gotoxy(5, 4); printf("﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥");
	color(10);
	gotoxy(55, 19); printf(player[0].name); //殮溘嫡擎 Ы溯檜橫曖 檜葷擊 轎溘ж朝 睡碟
	gotoxy(55, 22);; printf("1p"); //1p歜擊 憲溥邀
	white;
	gotoxy(5, 35); printf("﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥");
	Sleep(3000);
	system("cls");
}
void Player2View() {
	system("mode con:cols=120 lines=40");
	system("cls");
	white;
	gotoxy(5, 4); printf("﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥");
	color(10);
	gotoxy(55, 19); printf(player[1].name);
	gotoxy(55, 22); printf("2p"); //2p歜擊 憲溥邀
	white;
	gotoxy(5, 35); printf("﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥﹥");
	Sleep(3000);
	system("cls");
}

/*http://m.blog.naver.com/cjsendqnssh/220039060254 霤褻*/
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
					while (1) {//space bar蒂 揚毓擊陽
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
											cout << "≡";
										else if (count % 2 == 0)
											cout << "≒";

										gotoxy(bx, by + 1);
										cout << "  ";
										if (map[by][(bx - 1) / 2] == 2) {
											gotoxy(bx, by + 1);
											cout << "仄";
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
												cout << "≡";
											}
											else
												cout << "≒";

											gotoxy(bx, by_ + 1);
											cout << "  ";

											if (map[by_][(bx - 1) / 2] == 2) {
												gotoxy(bx, by_ + 1);
												cout << "仄";
											}
											by_--;
											Sleep(100);
										}
										ball_set(c, by_, (bx - 1) / 2); // 醱給 �� 給 盪濰
										if (map[by + 1][(bx - 1) / 2] == 3 || map[by + 1][(bx - 1) / 2] == 4)
											map[by - 1][(bx - 1) / 2] = 0;
										else if (map[by + 1][(bx - 1) / 2] == 33 || map[by + 1][(bx - 1) / 2] == 44)
											map[by - 1][(bx - 1) / 2] = 2;
									}
									ball_set(count, by, (bx - 1) / 2); // 醱給 瞪 給 盪濰
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
											cout << "≡";
										else if (count % 2 == 0)
											cout << "≒";

										gotoxy(bx, by + 1);
										cout << "  ";
										if (map[by][(bx - 1) / 2] == 2) {
											gotoxy(bx, by + 1);
											cout << "仄";
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
												cout << "≡";
											}
											else
												cout << "≒";

											gotoxy(bx, by_ + 1);
											cout << "  ";

											if (map[by_][(bx - 1) / 2] == 2) {
												gotoxy(bx, by_ + 1);
												cout << "仄";
											}
											by_--;
											Sleep(100);
										}
										ball_set(c, by_, (bx - 1) / 2); // 醱給 �� 給 盪濰
										if (map[by + 1][(bx - 1) / 2] == 3 || map[by + 1][(bx - 1) / 2] == 4)
											map[by - 1][(bx - 1) / 2] = 0;
										else if (map[by + 1][(bx - 1) / 2] == 33 || map[by + 1][(bx - 1) / 2] == 44)
											map[by - 1][(bx - 1) / 2] = 2;
									}
									ball_set(count, by, (bx - 1) / 2); // 醱給 瞪 給 盪濰
								}
								//////////////////////////////////////////////


								Sleep(1000);
								cx = 3;
								py = 1;
								return;

								//py = 2;
							}
						}
					}//space if僥

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
					while (1) {//space bar蒂 揚毓擊陽
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
											cout << "≡";
										else if (count % 2 == 0)
											cout << "≒";

										gotoxy(bx, by + 1);
										cout << "  ";
										if (map[by][(bx - 1) / 2] == 2) {
											gotoxy(bx, by + 1);
											cout << "仄";
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
												cout << "≡";
											}
											else
												cout << "≒";

											gotoxy(bx, by_ + 1);
											cout << "  ";

											if (map[by_][(bx - 1) / 2] == 2) {
												gotoxy(bx, by_ + 1);
												cout << "仄";
											}
											by_--;
											Sleep(100);
										}
										ball_set(c, by_, (bx - 1) / 2); // 醱給 �� 給 盪濰
										if (map[by + 1][(bx - 1) / 2] == 3 || map[by + 1][(bx - 1) / 2] == 4)
											map[by - 1][(bx - 1) / 2] = 0;
										else if (map[by + 1][(bx - 1) / 2] == 33 || map[by + 1][(bx - 1) / 2] == 44)
											map[by - 1][(bx - 1) / 2] = 2;
									}
									ball_set(count, by, (bx - 1) / 2); // 醱給 瞪 給 盪濰
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
											cout << "≡";
										else if (count % 2 == 0)
											cout << "≒";

										gotoxy(bx, by + 1);
										cout << "  ";
										if (map[by][(bx - 1) / 2] == 2) {
											gotoxy(bx, by + 1);
											cout << "仄";
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
												cout << "≡";
											}
											else
												cout << "≒";

											gotoxy(bx, by_ + 1);
											cout << "  ";

											if (map[by_][(bx - 1) / 2] == 2) {
												gotoxy(bx, by_ + 1);
												cout << "仄";
											}
											by_--;
											Sleep(100);
										}
										ball_set(c, by_, (bx - 1) / 2); // 醱給 �� 給 盪濰
										if (map[by + 1][(bx - 1) / 2] == 3 || map[by + 1][(bx - 1) / 2] == 4)
											map[by - 1][(bx - 1) / 2] = 0;
										else if (map[by + 1][(bx - 1) / 2] == 33 || map[by + 1][(bx - 1) / 2] == 44)
											map[by - 1][(bx - 1) / 2] = 2;
									}
									ball_set(count, by, (bx - 1) / 2); // 醱給 瞪 給 盪濰
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

/* 3偃曖 ball 醞縑憮 薯橾 陛梱遴 ball曖 剪葬蒂 掘ж朝 л熱 */
int min_point(int x, int y, int z) {
	int temp = x;
	if (temp > y)
		temp = y;
	if (temp > z)
		temp = z;
	return temp;
}

/* sqrtл熱蒂 餌辨п憮 ball曖 剪葬蒂 掘ж朝 л熱 */
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

/* 餌辨濠菟曖 ball曖 剪葬蒂 綠掖ж堅 蝓濠曖 薄熱蒂 奩�納炴� л熱 */
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
	gotoxy(5, 5); printf("\t\t\t\t\t     ≡敘罌撲貲≡\t\t\t\t\t\t");
	gotoxy(5, 6); printf("-------------------------------------------------------------------------------------------");
	gotoxy(5, 40); printf("-------------------------------------------------------------------------------------------");
	color(2);
	gotoxy(3, 8); printf("\t\t 1. SPACE夥蒂 援腦賊 蝶驛擊 湍韓 寞щ婁 樓紫蒂 褻瞰й 熱 氈橫");
	gotoxy(3, 10); printf("\t\t 2. 陝 ぜ擎 3偃曖 蝶驛擊 廓陞嬴 陛賊憮 湍雖朝 剪雖");
	gotoxy(3, 12); printf("\t\t 3. 賃偃曖 蝶驛檜 錳寰縑 氈湍除縑 錳醞懈縑 陛濰 陛梱遴 蝶驛檜 氈朝ぜ檜 檜啖  ");
	gotoxy(3, 14); printf("\t\t 4. 試盪ж朝 ぜ檜 碳葬ж棲 2ground薯煎 摹�譬� 夥船啪 腋  ");
	gotoxy(3, 16); printf("\t\t 5. 2っ曖 啪歜檜 部釭賊 蝓, 鼠, ぬ蒂 唸薑ж雖  \n");
	color(9);
	gotoxy(5, 18); printf("檜пц戲賊 縛攪蒂 揚楝輿撮蹂\n");
	GdiplusStartupInput m_sGSI;
	ULONG_PTR m_lpToken = NULL;
	GdiplusStartup(&m_lpToken, &m_sGSI, NULL);

	Graphics *pGraphics = new Graphics(GetDC(GetConsoleWindow()));
	Image* pImage = new Image(L"梯鼠撩.png");
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

void start() {//Ы溯檜橫 殮溘嫡晦
	system("mode con:cols=40 lines=20");
	system("cls");

	gotoxy(5, 5);
	cout << "Ы溯檜橫 檜葷擊 殮溘ж衛螃.";
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
	int score1 = a, score2 = b;//1P 薄熱, 2P 薄熱
	system("cls");
	Sleep(1000);

	if (score1 > score2) {//1P陛 檜啣擊 唳辦縑 釭顫釭朝 斜楚а

		system("cls");
		color(3);
		cout << "\n\n\n";
		printf("             ≒≒≒≒              ≒≒≒≒≒≒≒≒≒≒                      ≒≒≒≒≒          ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("           ≒≒≒≒≒              ≒≒≒≒≒≒≒≒≒≒≒                  ≒≒≒≒≒            ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("         ≒≒≒≒≒≒              ≒≒≒≒≒≒≒≒≒≒≒≒              ≒≒≒≒≒              ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("       ≒≒≒  ≒≒≒              ≒≒≒≒        ≒≒≒≒            ≒≒≒≒≒≒≒                          ≒≒≒    ≒≒   \n");
		printf("     ≒≒≒    ≒≒≒              ≒≒≒≒        ≒≒≒≒          ≒≒≒≒   ≒≒≒≒                       ≒≒≒    ≒≒   \n");
		printf("               ≒≒≒              ≒≒≒≒≒≒≒≒≒≒≒≒        ≒≒≒≒       ≒≒≒≒                     ≒≒≒    ≒≒   \n");
		printf("               ≒≒≒              ≒≒≒≒≒≒≒≒≒≒≒        ≒≒≒≒           ≒≒≒≒                   ≒≒≒    ≒≒   \n");
		printf("               ≒≒≒              ≒≒≒≒≒≒≒≒≒≒                                          ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("               ≒≒≒              ≒≒≒                      ≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒  ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("               ≒≒≒              ≒≒≒                      ≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒  ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("               ≒≒≒              ≒≒≒                                                        ≒≒≒                  ≒≒   \n");
		printf("               ≒≒≒              ≒≒≒                                 ≒≒≒≒≒             ≒≒≒                  ≒≒   \n");
		printf("               ≒≒≒              ≒≒≒                               ≒≒≒≒≒≒≒           ≒≒≒                  ≒≒   \n");
		printf("               ≒≒≒              ≒≒≒                             ≒≒≒≒  ≒≒≒≒         ≒≒≒                  ≒≒   \n");
		printf("               ≒≒≒              ≒≒≒                             ≒≒≒      ≒≒≒         ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("               ≒≒≒              ≒≒≒                             ≒≒≒≒  ≒≒≒≒         ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("     ≒≒≒≒≒≒≒≒≒≒≒≒≒    ≒≒≒                               ≒≒≒≒≒≒≒           ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("     ≒≒≒≒≒≒≒≒≒≒≒≒≒ 1  ≒≒≒                     1           ≒≒≒≒≒           1                         ≒≒   \n");
		Sleep(3000);
		system("cls");
		cout << "\n\n\n";
		printf("        ≒≒           ≒≒       ≒≒≒        ≒≒≒      ≒≒                           ≒≒         ≒≒≒≒≒≒≒          \n");
		printf("         ≒≒          ≒≒       ≒≒≒        ≒≒≒      ≒≒   ≒≒≒≒≒≒≒≒≒      ≒≒       ≒≒≒≒≒≒≒≒≒        \n");
		printf(" ≒≒≒≒≒≒≒≒≒≒  ≒≒       ≒≒≒        ≒≒≒  ≒≒≒≒   ≒≒≒≒≒≒≒≒≒      ≒≒     ≒≒≒         ≒≒≒       \n");
		printf(" ≒≒≒≒≒≒≒≒≒≒  ≒≒       ≒≒≒≒≒≒≒≒≒≒  ≒≒≒≒   ≒≒                ≒≒≒≒    ≒≒≒           ≒≒≒      \n");
		printf("       ≒≒≒≒        ≒≒≒≒   ≒≒≒≒≒≒≒≒≒≒      ≒≒   ≒≒                ≒≒≒≒   ≒≒≒            ≒≒≒      \n");
		printf("     ≒≒≒≒≒≒      ≒≒≒≒   ≒≒≒        ≒≒≒      ≒≒   ≒≒                    ≒≒   ≒≒≒            ≒≒≒      \n");
		printf("    ≒≒≒  ≒≒≒     ≒≒       ≒≒≒        ≒≒≒      ≒≒   ≒≒                    ≒≒    ≒≒≒          ≒≒≒       \n");
		printf("     ≒≒≒≒≒≒      ≒≒       ≒≒≒≒≒≒≒≒≒≒      ≒≒   ≒≒                    ≒≒                  ≒≒≒         \n");
		printf("       ≒≒≒≒        ≒≒       ≒≒≒≒≒≒≒≒≒≒      ≒≒   ≒≒≒≒≒≒≒≒≒      ≒≒                ≒≒≒           \n");
		printf("                       ≒≒                                 ≒≒   ≒≒≒≒≒≒≒≒≒      ≒≒               ≒≒≒            \n");
		printf("                       ≒≒                                 ≒≒                           ≒≒               ≒≒≒            \n");
		printf("                                                                                           ≒≒               ≒≒≒            \n");
		printf("      ≒≒                          ≒≒                                                   ≒≒               ≒≒≒            \n");
		printf("      ≒≒                          ≒≒                                                   ≒≒                                 \n");
		printf("      ≒≒≒≒≒≒≒≒≒≒≒≒      ≒≒≒≒≒≒≒≒≒≒≒≒≒≒                           ≒≒               ≒≒≒            \n");
		printf("      ≒≒≒≒≒≒≒≒≒≒≒≒      ≒≒≒≒≒≒≒≒≒≒≒≒≒≒                           ≒≒               ≒≒≒            \n");
		Sleep(3000);
	}

	else if (score1 == score2) {//鼠蝓睡橾陽 釭顫釭朝 斜楚а

		system("cls");
		color(9);
		cout << "\n\n\n";
		printf("       ≒≒≒≒≒≒≒≒≒≒                   ≒≒≒≒≒                   ≒≒≒        ≒≒≒         ≒≒≒≒≒≒            \n");
		printf("       ≒≒≒≒≒≒≒≒≒≒                 ≒≒≒≒≒≒≒                 ≒≒≒        ≒≒≒         ≒≒≒≒≒≒            \n");
		printf("       ≒≒≒        ≒≒≒               ≒≒≒≒  ≒≒≒≒               ≒≒≒≒≒≒≒≒≒≒         ≒≒≒≒≒≒            \n");
		printf("       ≒≒≒        ≒≒≒              ≒≒≒≒    ≒≒≒≒              ≒≒≒≒≒≒≒≒≒≒         ≒≒≒≒≒≒            \n");
		printf("       ≒≒≒≒≒≒≒≒≒≒             ≒≒≒≒      ≒≒≒≒             ≒≒≒        ≒≒≒         ≒≒≒≒≒≒            \n");
		printf("       ≒≒≒≒≒≒≒≒≒≒                                                ≒≒≒≒≒≒≒≒≒≒         ≒≒≒≒≒≒            \n");
		printf("                                     ≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒        ≒≒≒≒≒≒≒≒≒≒         ≒≒≒≒≒≒            \n");
		printf(" ≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒    ≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒                                     ≒≒≒≒≒≒            \n");
		printf(" ≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒                                    ≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒   ≒≒≒≒≒≒            \n");
		printf("              ≒≒≒                          ≒≒≒≒≒             ≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒    ≒≒≒≒≒             \n");
		printf("              ≒≒≒                        ≒≒≒≒≒≒≒                        ≒≒≒                  ≒≒≒≒              \n");
		printf("              ≒≒≒                       ≒≒≒≒≒≒≒≒                       ≒≒≒                                        \n");
		printf("              ≒≒≒                       ≒≒≒≒≒≒≒≒                       ≒≒≒                  ≒≒≒≒              \n");
		printf("              ≒≒≒                        ≒≒≒≒≒≒≒                        ≒≒≒                  ≒≒≒≒              \n");
		printf("                                              ≒≒≒≒≒                          ≒≒≒                  ≒≒≒≒              \n");
		Sleep(3000);
		system("cls");
		cout << "\n\n\n";
		printf("        ≒≒           ≒≒       ≒≒≒        ≒≒≒      ≒≒                           ≒≒         ≒≒≒≒≒≒≒          \n");
		printf("         ≒≒          ≒≒       ≒≒≒        ≒≒≒      ≒≒   ≒≒≒≒≒≒≒≒≒      ≒≒       ≒≒≒≒≒≒≒≒≒        \n");
		printf(" ≒≒≒≒≒≒≒≒≒≒  ≒≒       ≒≒≒        ≒≒≒  ≒≒≒≒   ≒≒≒≒≒≒≒≒≒      ≒≒     ≒≒≒         ≒≒≒       \n");
		printf(" ≒≒≒≒≒≒≒≒≒≒  ≒≒       ≒≒≒≒≒≒≒≒≒≒  ≒≒≒≒   ≒≒                ≒≒≒≒    ≒≒≒           ≒≒≒      \n");
		printf("       ≒≒≒≒        ≒≒≒≒   ≒≒≒≒≒≒≒≒≒≒      ≒≒   ≒≒                ≒≒≒≒   ≒≒≒            ≒≒≒      \n");
		printf("     ≒≒≒≒≒≒      ≒≒≒≒   ≒≒≒        ≒≒≒      ≒≒   ≒≒                    ≒≒   ≒≒≒            ≒≒≒      \n");
		printf("    ≒≒≒  ≒≒≒     ≒≒       ≒≒≒        ≒≒≒      ≒≒   ≒≒                    ≒≒    ≒≒≒          ≒≒≒       \n");
		printf("     ≒≒≒≒≒≒      ≒≒       ≒≒≒≒≒≒≒≒≒≒      ≒≒   ≒≒                    ≒≒                  ≒≒≒         \n");
		printf("       ≒≒≒≒        ≒≒       ≒≒≒≒≒≒≒≒≒≒      ≒≒   ≒≒≒≒≒≒≒≒≒      ≒≒                ≒≒≒           \n");
		printf("                       ≒≒                                 ≒≒   ≒≒≒≒≒≒≒≒≒      ≒≒               ≒≒≒            \n");
		printf("                       ≒≒                                 ≒≒                           ≒≒               ≒≒≒            \n");
		printf("                                                                                           ≒≒               ≒≒≒            \n");
		printf("      ≒≒                          ≒≒                                                   ≒≒               ≒≒≒            \n");
		printf("      ≒≒                          ≒≒                                                   ≒≒                                 \n");
		printf("      ≒≒≒≒≒≒≒≒≒≒≒≒      ≒≒≒≒≒≒≒≒≒≒≒≒≒≒                           ≒≒               ≒≒≒            \n");
		printf("      ≒≒≒≒≒≒≒≒≒≒≒≒      ≒≒≒≒≒≒≒≒≒≒≒≒≒≒                           ≒≒               ≒≒≒            \n");
		Sleep(3000);
	}
	else {//2P陛 檜啣擊 唳辦縑 釭顫釭朝 斜楚а

		system("cls");
		color(5);
		cout << "\n\n\n";
		printf("           ≒≒≒≒≒≒            ≒≒≒≒≒≒≒≒≒≒                      ≒≒≒≒≒          ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("         ≒≒≒≒≒≒≒≒          ≒≒≒≒≒≒≒≒≒≒≒                  ≒≒≒≒≒            ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("       ≒≒≒≒≒≒≒≒≒≒        ≒≒≒≒≒≒≒≒≒≒≒≒              ≒≒≒≒≒              ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("     ≒≒≒          ≒≒≒        ≒≒≒≒        ≒≒≒≒            ≒≒≒≒≒≒≒                          ≒≒≒    ≒≒   \n");
		printf("    ≒≒≒            ≒≒≒       ≒≒≒≒        ≒≒≒≒          ≒≒≒≒   ≒≒≒≒                       ≒≒≒    ≒≒   \n");
		printf("   ≒≒≒              ≒≒≒      ≒≒≒≒≒≒≒≒≒≒≒≒        ≒≒≒≒       ≒≒≒≒                     ≒≒≒    ≒≒   \n");
		printf("   ≒≒≒              ≒≒≒      ≒≒≒≒≒≒≒≒≒≒≒        ≒≒≒≒           ≒≒≒≒                   ≒≒≒    ≒≒   \n");
		printf("                       ≒≒≒      ≒≒≒≒≒≒≒≒≒≒                                          ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("                     ≒≒≒        ≒≒≒                      ≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒  ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("                   ≒≒≒          ≒≒≒                      ≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒≒  ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("                 ≒≒≒            ≒≒≒                                                        ≒≒≒                  ≒≒   \n");
		printf("               ≒≒≒              ≒≒≒                                 ≒≒≒≒≒             ≒≒≒                  ≒≒   \n");
		printf("             ≒≒≒                ≒≒≒                               ≒≒≒≒≒≒≒           ≒≒≒                  ≒≒   \n");
		printf("           ≒≒≒                  ≒≒≒                             ≒≒≒≒  ≒≒≒≒         ≒≒≒                  ≒≒   \n");
		printf("         ≒≒≒                    ≒≒≒                             ≒≒≒      ≒≒≒         ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("       ≒≒≒                      ≒≒≒                             ≒≒≒≒  ≒≒≒≒         ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("     ≒≒≒≒≒≒≒≒≒≒≒≒≒    ≒≒≒                               ≒≒≒≒≒≒≒           ≒≒≒≒≒≒≒≒≒≒    ≒≒   \n");
		printf("     ≒≒≒≒≒≒≒≒≒≒≒≒≒    ≒≒≒                                 ≒≒≒≒≒                                     ≒≒   \n");
		Sleep(3000);
		system("cls");
		cout << "\n\n\n";
		printf("        ≒≒           ≒≒       ≒≒≒        ≒≒≒      ≒≒                           ≒≒         ≒≒≒≒≒≒≒          \n");
		printf("         ≒≒          ≒≒       ≒≒≒        ≒≒≒      ≒≒   ≒≒≒≒≒≒≒≒≒      ≒≒       ≒≒≒≒≒≒≒≒≒        \n");
		printf(" ≒≒≒≒≒≒≒≒≒≒  ≒≒       ≒≒≒        ≒≒≒  ≒≒≒≒   ≒≒≒≒≒≒≒≒≒      ≒≒     ≒≒≒         ≒≒≒       \n");
		printf(" ≒≒≒≒≒≒≒≒≒≒  ≒≒       ≒≒≒≒≒≒≒≒≒≒  ≒≒≒≒   ≒≒                ≒≒≒≒    ≒≒≒           ≒≒≒      \n");
		printf("       ≒≒≒≒        ≒≒≒≒   ≒≒≒≒≒≒≒≒≒≒      ≒≒   ≒≒                ≒≒≒≒   ≒≒≒            ≒≒≒      \n");
		printf("     ≒≒≒≒≒≒      ≒≒≒≒   ≒≒≒        ≒≒≒      ≒≒   ≒≒                    ≒≒   ≒≒≒            ≒≒≒      \n");
		printf("    ≒≒≒  ≒≒≒     ≒≒       ≒≒≒        ≒≒≒      ≒≒   ≒≒                    ≒≒    ≒≒≒          ≒≒≒       \n");
		printf("     ≒≒≒≒≒≒      ≒≒       ≒≒≒≒≒≒≒≒≒≒      ≒≒   ≒≒                    ≒≒                  ≒≒≒         \n");
		printf("       ≒≒≒≒        ≒≒       ≒≒≒≒≒≒≒≒≒≒      ≒≒   ≒≒≒≒≒≒≒≒≒      ≒≒                ≒≒≒           \n");
		printf("                       ≒≒                                 ≒≒   ≒≒≒≒≒≒≒≒≒      ≒≒               ≒≒≒            \n");
		printf("                       ≒≒                                 ≒≒                           ≒≒               ≒≒≒            \n");
		printf("                                                                                           ≒≒               ≒≒≒            \n");
		printf("      ≒≒                          ≒≒                                                   ≒≒               ≒≒≒            \n");
		printf("      ≒≒                          ≒≒                                                   ≒≒                                 \n");
		printf("      ≒≒≒≒≒≒≒≒≒≒≒≒      ≒≒≒≒≒≒≒≒≒≒≒≒≒≒                           ≒≒               ≒≒≒            \n");
		printf("      ≒≒≒≒≒≒≒≒≒≒≒≒      ≒≒≒≒≒≒≒≒≒≒≒≒≒≒                           ≒≒               ≒≒≒            \n");
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
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                 ≡≡≡≡≡≡≡≡≡                                                     早 \n");
	printf("   早                                                  ≡≡≡≡≡≡≡≡                                                      早 \n");
	printf("   早                                                   ≡≡≡≡≡≡≡                                                       早 \n");
	printf("   早                                                     ≡≡≡≡≡                                                         早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	Sleep(100);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
}

void open_main() {
	Sleep(200);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO                                                                                     早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO                                                                               早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO                                                                                     早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO                                                                                     早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO                                                                                     早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO                                                                                     早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO                                                                                     早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO                                                                                     早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");

	Sleep(200);
	system("cls");
	color(4);
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO                                                                                     早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO                                                                                     早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO                                                                                     早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO                                                                                     早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                               LLLL                  OOOOOOO              OOOOOOO        KKK        KKK 早 \n");
	printf("   早                                               LLLL                OOO     OOO          OOO     OOO      KKK       KKK  早 \n");
	printf("   早                                               LLLL               OOO       OOO        OOO       OOO     KKK      KKK   早 \n");
	printf("   早                                               LLLL              OOO         OOO      OOO         OOO    KKK     KKK    早 \n");
	printf("   早                                               LLLL             OOO           OOO    OOO           OOO   KKK    KKK     早 \n");
	printf("   早                                               LLLL            OOO             OOO  OOO             OOO  KKK   KKK      早 \n");
	printf("   早                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO                                                                                     早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO                                                                                     早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                               LLLL                  OOOOOOO              OOOOOOO        KKK        KKK 早 \n");
	printf("   早                                               LLLL                OOO     OOO          OOO     OOO      KKK       KKK  早 \n");
	printf("   早                                               LLLL               OOO       OOO        OOO       OOO     KKK      KKK   早 \n");
	printf("   早                                               LLLL              OOO         OOO      OOO         OOO    KKK     KKK    早 \n");
	printf("   早                                               LLLL             OOO           OOO    OOO           OOO   KKK    KKK     早 \n");
	printf("   早                                               LLLL            OOO             OOO  OOO             OOO  KKK   KKK      早 \n");
	printf("   早                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早                                               LLLL            OOO             OOO  OOO             OOO  KKK KKK        早 \n");
	printf("   早                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早                                               LLLL             OOO           OOO    OOO           OOO   KKK   KKK      早 \n");
	printf("   早                                               LLLL              OOO         OOO      OOO         OOO    KKK    KKK     早 \n");
	printf("   早                                               LLLL               OOO       OOO        OOO       OOO     KKK     KKK    早 \n");
	printf("   早                                               LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   早 \n");
	printf("   早                                               LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO                                                                                     早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO                                                                                     早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                               LLLL                  OOOOOOO              OOOOOOO        KKK        KKK 早 \n");
	printf("   早                                               LLLL                OOO     OOO          OOO     OOO      KKK       KKK  早 \n");
	printf("   早                                               LLLL               OOO       OOO        OOO       OOO     KKK      KKK   早 \n");
	printf("   早                                               LLLL              OOO         OOO      OOO         OOO    KKK     KKK    早 \n");
	printf("   早                                               LLLL             OOO           OOO    OOO           OOO   KKK    KKK     早 \n");
	printf("   早                                               LLLL            OOO             OOO  OOO             OOO  KKK   KKK      早 \n");
	printf("   早                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早                                               LLLL            OOO             OOO  OOO             OOO  KKK KKK        早 \n");
	printf("   早                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早                                               LLLL             OOO           OOO    OOO           OOO   KKK   KKK      早 \n");
	printf("   早                                               LLLL              OOO         OOO      OOO         OOO    KKK    KKK     早 \n");
	printf("   早                                               LLLL               OOO       OOO        OOO       OOO     KKK     KKK    早 \n");
	printf("   早                                               LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   早 \n");
	printf("   早                                               LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO                                                                                     早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO                                                                                   早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO                                                                                  早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO                                                                                 早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO                                                                                早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO                                                                               早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO      LLLL                  OOOOOOO              OOOOOOO        KKK        KKK 早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO       LLLL                OOO     OOO          OOO     OOO      KKK       KKK  早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO        LLLL               OOO       OOO        OOO       OOO     KKK      KKK   早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO         LLLL              OOO         OOO      OOO         OOO    KKK     KKK    早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO          LLLL             OOO           OOO    OOO           OOO   KKK    KKK     早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO            LLLL            OOO             OOO  OOO             OOO  KKK   KKK      早 \n");
	printf("   早                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早                                               LLLL            OOO             OOO  OOO             OOO  KKK KKK        早 \n");
	printf("   早                                               LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早                                               LLLL             OOO           OOO    OOO           OOO   KKK   KKK      早 \n");
	printf("   早                                               LLLL              OOO         OOO      OOO         OOO    KKK    KKK     早 \n");
	printf("   早                                               LLLL               OOO       OOO        OOO       OOO     KKK     KKK    早 \n");
	printf("   早                                               LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   早 \n");
	printf("   早                                               LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO            LLLL                  OOOOOOO              OOOOOOO        KKK        KKK 早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO          LLLL                OOO     OOO          OOO     OOO      KKK       KKK  早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK      KKK   早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK     KKK    早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK    KKK     早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK   KKK      早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK KKK        早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK   KKK      早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK    KKK     早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK     KKK    早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO          LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO            LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO            LLLL                  OOOOOOO              OOOOOOO        KKK        KKK 早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO          LLLL                OOO     OOO          OOO     OOO      KKK       KKK  早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK      KKK   早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK     KKK    早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK    KKK     早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK   KKK      早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK KKK        早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK   KKK      早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK    KKK     早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK     KKK    早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO          LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO            LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早            PPPPPPPPPPPPPPP                    A                 SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP          PPP                  AAA                SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP           PPP                AAAAA               SSS                     SSS                            早 \n");
	printf("   早            PPP            PPP              AAA AAA              SSS                     SSS                            早 \n");
	printf("   早            PPP             PPP            AAA   AAA             SSS                     SSS                            早 \n");
	printf("   早            PPP             PPP           AAA     AAA            SSS                     SSS                            早 \n");
	printf("   早            PPP            PPP           AAA       AAA           SSS                     SSS                            早 \n");
	printf("   早            PPP           PPP           AAA         AAA          SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");

	Sleep(200);
	system("cls");
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO            LLLL                  OOOOOOO              OOOOOOO        KKK        KKK 早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO          LLLL                OOO     OOO          OOO     OOO      KKK       KKK  早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK      KKK   早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK     KKK    早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK    KKK     早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK   KKK      早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK KKK        早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK   KKK      早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK    KKK     早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK     KKK    早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO          LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO            LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早            PPPPPPPPPPPPPPP                    A                 SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP          PPP                  AAA                SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP           PPP                AAAAA               SSS                     SSS                            早 \n");
	printf("   早            PPP            PPP              AAA AAA              SSS                     SSS                            早 \n");
	printf("   早            PPP             PPP            AAA   AAA             SSS                     SSS                            早 \n");
	printf("   早            PPP             PPP           AAA     AAA            SSS                     SSS                            早 \n");
	printf("   早            PPP            PPP           AAA       AAA           SSS                     SSS                            早 \n");
	printf("   早            PPP           PPP           AAA         AAA          SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPPPPPPPPPPPPPP            AAAAAAAAAAAAAAAAA         SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP                       AAAAAAAAAAAAAAAAAAA                       SSS                    SSS              早 \n");
	printf("   早            PPP                      AAA               AAA                      SSS                    SSS              早 \n");
	printf("   早            PPP                      AAA               AAA                      SSS                    SSS              早 \n");
	printf("   早            PPP                     AAA                 AAA                     SSS                    SSS              早 \n");
	printf("   早            PPP                     AAA                 AAA                     SSS                    SSS              早 \n");
	printf("   早            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	Sleep(200);
	system("cls");
}

void show_main_1() {
	system("cls");
	color(5);
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO            LLLL                  OOOOOOO              OOOOOOO        KKK        KKK 早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO          LLLL                OOO     OOO          OOO     OOO      KKK       KKK  早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK      KKK   早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK     KKK    早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK    KKK     早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK   KKK      早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK KKK        早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK   KKK      早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK    KKK     早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK     KKK    早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO          LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO            LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早            PPPPPPPPPPPPPPP                    A                 SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP          PPP                  AAA                SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP           PPP                AAAAA               SSS                     SSS                            早 \n");
	printf("   早            PPP            PPP              AAA AAA              SSS                     SSS                            早 \n");
	printf("   早            PPP             PPP            AAA   AAA             SSS                     SSS                            早 \n");
	printf("   早            PPP             PPP           AAA     AAA            SSS                     SSS                            早 \n");
	printf("   早            PPP            PPP           AAA       AAA           SSS                     SSS                            早 \n");
	printf("   早            PPP           PPP           AAA         AAA          SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPPPPPPPPPPPPPP            AAAAAAAAAAAAAAAAA         SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP                       AAAAAAAAAAAAAAAAAAA                       SSS                    SSS              早 \n");
	printf("   早            PPP                      AAA               AAA                      SSS                    SSS              早 \n");
	printf("   早            PPP                      AAA               AAA                      SSS                    SSS              早 \n");
	printf("   早            PPP                     AAA                 AAA                     SSS                    SSS              早 \n");
	printf("   早            PPP                     AAA                 AAA                     SSS                    SSS              早 \n");
	printf("   早            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	printf("\n\n\n");
	printf("                                                        Ｃ 啪歜衛濛 Ｂ                                                        \n");
	printf("\n                                                           啪歜撲貲                                                             \n");
	printf("\n                                                           啪歜謙猿                                                           \n");
}

void show_main_2() {
	system("cls");
	color(2);
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO            LLLL                  OOOOOOO              OOOOOOO        KKK        KKK 早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO          LLLL                OOO     OOO          OOO     OOO      KKK       KKK  早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK      KKK   早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK     KKK    早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK    KKK     早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK   KKK      早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK KKK        早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK   KKK      早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK    KKK     早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK     KKK    早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO          LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO            LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早            PPPPPPPPPPPPPPP                    A                 SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP          PPP                  AAA                SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP           PPP                AAAAA               SSS                     SSS                            早 \n");
	printf("   早            PPP            PPP              AAA AAA              SSS                     SSS                            早 \n");
	printf("   早            PPP             PPP            AAA   AAA             SSS                     SSS                            早 \n");
	printf("   早            PPP             PPP           AAA     AAA            SSS                     SSS                            早 \n");
	printf("   早            PPP            PPP           AAA       AAA           SSS                     SSS                            早 \n");
	printf("   早            PPP           PPP           AAA         AAA          SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPPPPPPPPPPPPPP            AAAAAAAAAAAAAAAAA         SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP                       AAAAAAAAAAAAAAAAAAA                       SSS                    SSS              早 \n");
	printf("   早            PPP                      AAA               AAA                      SSS                    SSS              早 \n");
	printf("   早            PPP                      AAA               AAA                      SSS                    SSS              早 \n");
	printf("   早            PPP                     AAA                 AAA                     SSS                    SSS              早 \n");
	printf("   早            PPP                     AAA                 AAA                     SSS                    SSS              早 \n");
	printf("   早            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	printf("\n\n\n");
	printf("                                                           啪歜衛濛                                                           \n");
	printf("\n                                                        Ｃ 啪歜撲貲 Ｂ                                                          \n");
	printf("\n                                                           啪歜謙猿                                                           \n");
}

void show_main_3() {
	system("cls");
	color(3);
	printf("\n");
	printf("   旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早 NNNN            NNN        OOOOOOO            LLLL                  OOOOOOO              OOOOOOO        KKK        KKK 早 \n");
	printf("   早 NNNNN           NNN      OOO     OOO          LLLL                OOO     OOO          OOO     OOO      KKK       KKK  早 \n");
	printf("   早 NNNNNN          NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK      KKK   早 \n");
	printf("   早 NNN NNN         NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK     KKK    早 \n");
	printf("   早 NNN  NNN        NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK    KKK     早 \n");
	printf("   早 NNN   NNN       NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK   KKK      早 \n");
	printf("   早 NNN    NNN      NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早 NNN     NNN     NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK KKK        早 \n");
	printf("   早 NNN      NNN    NNN  OOO             OOO      LLLL            OOO             OOO  OOO             OOO  KKK  KKK       早 \n");
	printf("   早 NNN       NNN   NNN   OOO           OOO       LLLL             OOO           OOO    OOO           OOO   KKK   KKK      早 \n");
	printf("   早 NNN        NNN  NNN    OOO         OOO        LLLL              OOO         OOO      OOO         OOO    KKK    KKK     早 \n");
	printf("   早 NNN         NNN NNN     OOO       OOO         LLLL               OOO       OOO        OOO       OOO     KKK     KKK    早 \n");
	printf("   早 NNN          NNNNNN      OOO     OOO          LLLLLLLLLLLLLLL     OOO     OOO          OOO     OOO      KKK      KKK   早 \n");
	printf("   早 NNN           NNNNN        OOOOOOO            LLLLLLLLLLLLLLL       OOOOOOO              OOOOOOO        KKK       KKK  早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早            PPPPPPPPPPPPPPP                    A                 SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP          PPP                  AAA                SSSSSSSSSSSSSSSSS       SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP           PPP                AAAAA               SSS                     SSS                            早 \n");
	printf("   早            PPP            PPP              AAA AAA              SSS                     SSS                            早 \n");
	printf("   早            PPP             PPP            AAA   AAA             SSS                     SSS                            早 \n");
	printf("   早            PPP             PPP           AAA     AAA            SSS                     SSS                            早 \n");
	printf("   早            PPP            PPP           AAA       AAA           SSS                     SSS                            早 \n");
	printf("   早            PPP           PPP           AAA         AAA          SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPPPPPPPPPPPPPP            AAAAAAAAAAAAAAAAA         SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP                       AAAAAAAAAAAAAAAAAAA                       SSS                    SSS              早 \n");
	printf("   早            PPP                      AAA               AAA                      SSS                    SSS              早 \n");
	printf("   早            PPP                      AAA               AAA                      SSS                    SSS              早 \n");
	printf("   早            PPP                     AAA                 AAA                     SSS                    SSS              早 \n");
	printf("   早            PPP                     AAA                 AAA                     SSS                    SSS              早 \n");
	printf("   早            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早            PPP                    AAA                   AAA     SSSSSSSSSSSSSSSSSS      SSSSSSSSSSSSSSSSS              早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   早                                                                                                                        早 \n");
	printf("   曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭 \n");
	printf("\n\n\n");
	printf("                                                           啪歜衛濛                                                           \n");
	printf("\n                                                           啪歜撲貲                                                             \n");
	printf("\n                                                        Ｃ 啪歜謙猿 Ｂ                                                        \n");
}

//熱薑陳瞼 : 2017-06-22(cmd 璽 觼晦 熱薑)