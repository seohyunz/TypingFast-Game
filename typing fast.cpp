#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include <Windows.h>
#include <conio.h>
#include<string.h>
#pragma comment(lib,"winmm.lib") //사운드 
using namespace std;
#define MAGIC_KEY 224
#define SPACE 32
#define LIFE 3
#define MAX_LEVEL 20
#define SCORE 0

#define WIDTH 30 
#define HEIGHT 22 
typedef struct xy {
	int x;
	int y;
	int con;
}Enemy;

Enemy enemy[WIDTH];

int score = 0;


void Sound() {
	PlaySound(TEXT("sky.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
	
}
void Sound2() { //인게임브금
	PlaySound(TEXT("dusr.wav"), 0, SND_FILENAME | SND_ASYNC | SND_LOOP);
}
enum ConsolColor {
	CC_BLACK,
	CC_DARKBLUE,
	CC_DARKGREEN,
	CC_DARKCYAN,
	CC_DARKRED,
	CC_DARKMAGENTA,
	CC_DARKYELLOW,
	CC_GRAY,
	CC_DARKGRAY,
	CC_BLUE,
	CC_GREEN,
	CC_CYAN,
	CC_RED,
	CC_MAGENTA,
	CC_YELLOW,
	CC_WHITE,
	CC_LIGHTGRAY = 7,
	CC_ORIGINAL = 7,
	CC_ORIGINALFONT = 7,
	CC_ORIGINALBG = 0
};
void init() {
	int i;
	for (i = 0; i < WIDTH; i++)
		enemy[i].con = FALSE;
}
enum NENU {
	GAMESTART = 0, INFO, QUIT, IING
};
enum KEYBOARD { //방향키 아스키코드
	UP = 72, LEFT = 75, RIGHT = 77, DOWN = 80
};
void Gamebeep() {
	Beep(1000, 200);
}
void gotoxy(int x, int y) {
	COORD pos;
	pos.X = 2 * x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}
void setFontColor(int color) {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (info.wAttributes & 0xf0) | (color & 0xf));
}
int getFontColor() {
	CONSOLE_SCREEN_BUFFER_INFO info;
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
	return info.wAttributes & 0xf;
}
__inline void resetFontColor() {
	setFontColor(7);
}


void SetGameView() {
	system("tiTle TYPING FAST!!");
}


void DrawtitleVie() {
	system("cls");
	
	int i;
	printf("%c%c", 0xA6, 0xAE);
	for (i = 0; i < 70; i++) { printf("%c%c", 0xA6, 0xAC); }
	printf("%c%c\n", 0xA6, 0xAF);
	cout << endl << endl;
	for (i = 0; i < 20; i++) { printf("%c%c%71c%c\n", 0xA6, 0xAD, 0xA6, 0xAD); }
	printf("%c%c", 0xA6, 0xb1);
	for (i = 0; i < 70; i++) { printf("%c%c", 0xA6, 0xAC); }
	printf("%c%c\n", 0xA6, 0xb0);
	
	setFontColor(CC_CYAN);
	
	gotoxy(10, 6);
	cout << "        TYPING FAST GAME       " << endl;
	resetFontColor();
	gotoxy(16, 12);
	cout << "게임시작\n";
	gotoxy(16, 13);
	cout << "게임방법\n";
	gotoxy(16, 14);
	cout << "  종료\n";

}



void DrawInfoGame() {
	system("cls");
	int i;
	printf("%c%c", 0xA6, 0xAE);
	for (i = 0; i < 70; i++) { printf("%c%c", 0xA6, 0xAC); }
	printf("%c%c\n", 0xA6, 0xAF);
	cout << endl << endl;
	for (i = 0; i < 20; i++) { printf("%c%c%71c%c\n", 0xA6, 0xAD, 0xA6, 0xAD); }
	printf("%c%c", 0xA6, 0xb1);
	for (i = 0; i < 70; i++) { printf("%c%c", 0xA6, 0xAC); }
	printf("%c%c\n", 0xA6, 0xb0);
	gotoxy(8, 5);
	cout << " 보여지는 문자를 차례대로 빨리 입력하는 게임";
	gotoxy(8, 7);
	cout << " 키보드로 해당된 문자 입력";
	gotoxy(8, 9);
	cout << " 정답  +10 점       오답  -3 점";
	gotoxy(8, 11);
	cout << "*난이도는 총3단계로 점수에 따라 올라갑니다.*";
	gotoxy(8, 13);
	cout << " 0~60     1단계";
	gotoxy(8, 14);
	cout << " 60~110   2단계";
	gotoxy(8, 15);
	cout << " 110~     3단계";
	gotoxy(8, 17);
	cout << " ENTER를 누르면 채점됩니다." << endl;
	gotoxy(8, 18);
	cout << " 목숨은 총 3개 입니다." << endl;
	
	
	setFontColor(CC_YELLOW);
	gotoxy(5, 21);
	cout << "P또는 p를 입력하면 게임이 종료되고,"
		" 메인화면으로 돌아갑니다.";
	gotoxy(15, 22);
	cout << "SPACE를 누르면 메인으로 돌아갑니다...";
	resetFontColor();
	while (1) {
		int n = _getch();
		if (n == 32) {
			break;
		}
	}
}
void DrawCusor(int& y) {
	if (y <= 0) { y = 0; }
	else if (y >= 2) { y = 2; }
	gotoxy(14, 12+y);
	cout << ">>";
	
}
NENU ReadyGame() {
	int y = 0;
	int input = 0;
	while (1) {
		DrawtitleVie();
		DrawCusor(y);
		input = _getch();
		if (input == MAGIC_KEY) {
			switch (_getch()) {
			case UP:
				--y;
				break;
			case DOWN:
				++y;
				break;
			}
		}
		else if (input == SPACE) {
			switch (y) {
			case 0:
				return GAMESTART;
			case 1:
				return INFO;
			
			case 2:
				return QUIT;
			}
		}
	}
}

void DrawGameOver(int score, int time) {
	system("cls");
	resetFontColor();
	int i;
	printf("%c%c", 0xA6, 0xAE);
	for (i = 0; i < 70; i++) { printf("%c%c", 0xA6, 0xAC); }
	printf("%c%c\n", 0xA6, 0xAF);
	cout << endl << endl;
	for (i = 0; i < 20; i++) { printf("%c%c%71c%c\n", 0xA6, 0xAD, 0xA6, 0xAD); }
	printf("%c%c", 0xA6, 0xb1);
	for (i = 0; i < 70; i++) { printf("%c%c", 0xA6, 0xAC); }
	printf("%c%c\n", 0xA6, 0xb0);
	gotoxy(10, 5);
	Gamebeep();
	Gamebeep();
	gotoxy(10, 8);
	setFontColor(CC_RED);
	cout << "Game Over" << endl;
	resetFontColor();
	gotoxy(10, 12);
	cout << "플레이 시간 : " << time << "초";
	gotoxy(10, 14);
	cout << "점 수 : " << score;
	setFontColor(CC_YELLOW);
	gotoxy(15, 22);
	cout << "SPACE를 누르면 메인으로 돌아갑니다...";
	resetFontColor();

	while (1) {
		int n = _getch();
		if (n == 32) {
			Sound();
			return;
		}
	}

}

void playGame(int life, int score) {
	system("cls");
	
	int n = 3;
	int i;
	setFontColor(CC_ORIGINALFONT);
	printf("%c%c", 0xA6, 0xAE);
	for (i = 0; i < 70; i++) { printf("%c%c", 0xA6, 0xAC); }
	printf("%c%c\n", 0xA6, 0xAF);
	cout << "  순서대로 입력"<<endl << endl;
	for (i = 0; i < 20; i++) { printf("%c%c%71c%c\n", 0xA6, 0xAD, 0xA6, 0xAD); }
	printf("%c%c", 0xA6, 0xb1);
	for (i = 0; i < 70; i++) { printf("%c%c", 0xA6, 0xAC); }
	printf("%c%c\n", 0xA6, 0xb0);
	resetFontColor();
	time_t start, finish;
	double ch;
	start = time(NULL);
	
	
	while (true) {
		
		gotoxy(7, 5);
		cout << " 점 수: " <<score;
		switch (life) {
		case 3:
			gotoxy(27, 5);
			cout << "0 0"; break;
		case 2:
			gotoxy(27, 5);
			cout << "0 X "; break;
		case 1:
			gotoxy(27, 5);
			cout << " X X "; break;
		}
		
		char Qword[8] = { 'w','s','a','d','w','s','a','d' };
		char Qword2[8] = { 'w','s','a','d','W','S','A','D' };
		char Qword3[11] = { 'w','s','a','d','W','S','A','D','1','2','3' };
		 
		
		char* pNums;
		char num;
		char ok;

		int i;
		srand((unsigned)time(NULL));
		pNums = (char*)malloc(sizeof(char) * n);

		for (i = 0; i < n; ++i) {
			int ra = rand() % 8;
			int ra2 = rand() % 11;
			pNums[i] = Qword[ra];
			if (score > 60) {
				pNums[i] = Qword2[ra];
			}
			if (score > 110) {
				pNums[i] = Qword3[ra2];
			}
		}
		if (score > 60) {
			setFontColor(CC_BLUE);
			gotoxy(3, 19);
			cout << "게임 난이도↑↑";
			resetFontColor();
		}
		if (score > 110) {
			setFontColor(CC_MAGENTA);
			gotoxy(3, 19);
			cout << "게임 난이도↑↑↑";
			resetFontColor();
		}
		setFontColor(CC_YELLOW);
		gotoxy(7, 7);
		cout<<"───────────────────────────────────────────";
		gotoxy(7, 11);
		cout << "───────────────────────────────────────────";
		resetFontColor();
		gotoxy(13, 9);
		for (i = 0; i < n; ++i) {
			cout << pNums[i]<<" ";
		}
		ok = true;
		gotoxy(14, 15);
		cout << "-->                                        ";
		gotoxy(16, 15);
		for (i = 0; i < n; ++i){
			cin >> num;
			if (num != pNums[i]) {
				ok = false;
				if (num == 'p' || num == 'P') {
					setFontColor(CC_YELLOW);
					gotoxy(15, 18);
					cout << "게임 죵료!! 메인화면으로 돌아갑니다.";
					resetFontColor();
					Sleep(2000);
					DrawtitleVie();
					Sound();
					return;
				}
			}
				
		}
		if (!ok) {
			Gamebeep();
			gotoxy(26, 19);
			setFontColor(CC_RED);
			cout<<"false       ";
			life--;
			score -= 3;
			if (life == 0) {
				free(pNums);
				finish = time(NULL);
				ch = (double)(finish - start);
				DrawGameOver(score, ch);
				//DrawtitleVie();
				return;
			}
			
		}
		else if (ok == true) {
			gotoxy(26, 19);
			setFontColor(CC_GREEN);
			cout<<"true         ";
			n++;
			score += 10;
			if (n >= 20)
				n = 20;	
		}
		resetFontColor();
		free(pNums);
		
	}

}

void moveww() {
	int i;
	printf("%c%c", 0xA6, 0xAE);
	for (i = 0; i < 70; i++) { printf("%c%c", 0xA6, 0xAC); }
	printf("%c%c\n", 0xA6, 0xAF);
	cout << endl << endl;
	for (i = 0; i < 20; i++) { printf("%c%c%71c%c\n", 0xA6, 0xAD, 0xA6, 0xAD); }
	printf("%c%c", 0xA6, 0xb1);
	for (i = 0; i < 70; i++) { printf("%c%c", 0xA6, 0xAC); }
	printf("%c%c\n", 0xA6, 0xb0);
	setFontColor(CC_CYAN);
	char Re[] = { '  T','Y','P','I','N','G',' ', 'F','A','S','T', ' ' ,'G','A','M','E' };
	gotoxy(14, 6);
	for (int i = 0; i < 16; i++) {
		cout << Re[i];
		Sleep(200);
	}
	resetFontColor();
}

int main() {
	//fullscreen();
	SetGameView();
	Sound();
	moveww();
	while (1) {
		
		switch (ReadyGame()) {
		case GAMESTART:
			Sound2();
			playGame(LIFE, score);
			break;
		case INFO:
			DrawInfoGame();
			break;
		case QUIT:
			return 0;

		}
	 
	}
	

	return 0;

}

