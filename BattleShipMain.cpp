#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>
#include <conio.h>
#include "Win10.h"
using namespace std;

#define RAND(min,max) ((min) + (rand()) % ((max) - (min) + 1))

string Menu[]{
	"         S T A R T   G A M E         ",
	"  R U L E S   O F   T H E   G A M E  ",
	"   A B O U T   T H E   A U T H O R   ",
	"           S E T T I N G S           ",
	"               E X I T               "
};
int cntMenu = sizeof(Menu) / sizeof(Menu[0]);
//заставка
int AmountStrFile(string fileName);
string* SplashScreen = new string[AmountStrFile("SplashScreen.txt")];
int SplashScreenHeight;
int SplashScreenWidth;

//название игры картинка
string* PrintGameName = new string[AmountStrFile("GameName.txt")];
int GameNameHeight;
int GameNameWidth;

//картинка мини-кораблика
string* PrintLittleShip = new string[AmountStrFile("LittleShip.txt")];
int LittleShipHeight;
int LittleShipWidth;

//прототипы
int menu(string* Item, int cntItem, int Row, int Col, int Select);
void LoadPole(string* pole, string fileName, int& height);
void SplashScreenPrint();
void DrowGameName();
void DrowLittleShip();
void PrintTitle(string* Title, int height, int width, int row, int col);
extern string* PolePl;
extern string* PolePC;
extern string* PolePlAttack;
extern string* GameOver;
extern string* YouWon;
extern string* ShipPrint;

int main() {
	srand(time(0));
	SetConsoleSize(150, 45);
	CursorHide();
	LoadPole(SplashScreen, "SplashScreen.txt", SplashScreenHeight);
	SplashScreenWidth = SplashScreen[0].size();
	SplashScreenPrint();
	Sleep(5000);
	CLS;
	bool isExit = false;  //для проверки на выход из программы
	int Select = 0;  //пункт выбора меню
	int Rounds = 1;
	int rowMenu = 20, colMenu = 55;  //координаты меню
	do {
		PrintFrame(); //рамка
		//вывод названия игры в меню
		LoadPole(PrintGameName, "GameName.txt", GameNameHeight);
		GameNameWidth = PrintGameName[0].size();
		DrowGameName();
		//вывод картинки мини-кораблика в меню
		LoadPole(PrintLittleShip, "LittleShip.txt", LittleShipHeight);
		LittleShipWidth = PrintLittleShip[0].size();
		DrowLittleShip();
		Select = menu(Menu, cntMenu, rowMenu, colMenu, Select); //вывод менюшки и выбор пункта
		switch (Select) {
		case 0:
			CLS;
			StartGame(Rounds);  //начало игры
			CLS;
			break;
		case 1:
			CLS;
			Rules();  //правила игры
			PAUSE;
			CLS;
			break;
		case 2:
			CLS;
			AboutAuthor();  //об авторе
			PAUSE;
			CLS;
			break;
		case 3:
			CLS;
			Settings(Rounds);  //об авторе
			CLS;
			break;
		case 4:
		case -1:  //выход из игры
			CLS;
			PrintFrame();//рамка
			DrowGameName();
			DrowLittleShip();
			SetPos(20, 60);
			SetColor(COLOR::black, COLOR::yellow);
			cout << "Are you sure you want to EXIT?";
			string exitMenu[]{ "Yes", "No" };
			int answerItem = 0;
			bool notExit = false;
			while (true) {
				for (int i = 0; i < 2; i++) {
					SetPos(22, 70 + (i * 6));
					if (i == answerItem) {
						SetColor(COLOR::gray, COLOR::black);
					} else {
						SetColor(COLOR::black, COLOR::gray);
					}
					cout << exitMenu[i];
				}
				SetColor(COLOR::black, COLOR::bright_white);
				int answer = _getch();
				switch (answer) {
				case _KEY::LEFT:
					if (answerItem == 1) {
						answerItem = 0;
					} else {
						answerItem = 1;
					}
					break;
				case _KEY::RIGHT:
					if (answerItem == 0) {
						answerItem = 1;
					} else {
						answerItem = 0;
					}
					break;
				case _KEY::ENTER:
					if (answerItem == 0) {
						isExit = true;
						break;
					} else {
						notExit = true;
					}
					break;
				}
				if (notExit) {
					CLS;
					break;
				}
				if (isExit) {
					CLS;
					delete[] PolePl;
					delete[] PolePC;
					delete[] PolePlAttack;
					delete[] YouWon;
					delete[] GameOver;
					delete[] ShipPrint;
					delete[] SplashScreen;
					delete[] PrintGameName;
					delete[] PrintLittleShip;
					exit(0);
				}
			}
		}
	} while (!isExit);
	cin.get(); cin.get();
}

//вывод рисунка-заставки
void SplashScreenPrint() {
	PrintFrame();
	int SplashScreenRow = 4;
	int SplashScreenCol = 9;
	for (int i = 0; i < SplashScreenHeight; i++) {
		SetPos(SplashScreenRow + i, SplashScreenCol);
		for (int j = 0; j < SplashScreenWidth; j++) {
			if (SplashScreen[i][j] == 'm') { SetColor(COLOR::black, COLOR::blue); cout << char(178); }
	    if (SplashScreen[i][j] == 'n') { SetColor(COLOR::black, COLOR::gray);	cout << char(178); }
	    if (SplashScreen[i][j] == 'u') { SetColor(COLOR::black, COLOR::blue);	cout << char(178); }
	    if (SplashScreen[i][j] == 'b') { SetColor(COLOR::black, COLOR::black);	cout << char(178); }
	    if (SplashScreen[i][j] == 'r') { SetColor(COLOR::black, COLOR::light_red);	cout << char(178); }
	    if (SplashScreen[i][j] == 'y') { SetColor(COLOR::black, COLOR::red);	cout << char(178); }
	    if (SplashScreen[i][j] == 'i') { SetColor(COLOR::black, COLOR::yellow);	cout << char(178); }
	    if (SplashScreen[i][j] == '.') { SetColor(COLOR::black, COLOR::light_blue);	cout << char(178); }
	    if (SplashScreen[i][j] == '*') { SetColor(COLOR::black, COLOR::aqua);	cout << char(178); }
		}
	}
	SetColor(COLOR::black, COLOR::gray);
}
//вывод названия игры в меню
void DrowGameName() {
	int GameNameRow = 7;
	int GameNameCol = 28;
	for (int i = 0; i < GameNameHeight; i++) {
		SetPos(GameNameRow + i, GameNameCol);
		for (int j = 0; j < GameNameWidth; j++) {
			if (PrintGameName[i][j] == 'm') { SetColor(COLOR::black, COLOR::blue); cout << char(178); }
			if (PrintGameName[i][j] == 'n') { SetColor(COLOR::black, COLOR::gray);	cout << char(178); }
			if (PrintGameName[i][j] == '.') { SetColor(COLOR::black, COLOR::light_blue);	cout << " "; }
		}
	}
	SetColor(COLOR::black, COLOR::gray);
}
//вывод мини-картинки в меню
void DrowLittleShip() {
	int LittleShipRow = 25;
	int LittleShipCol = 20;
	for (int i = 0; i < LittleShipHeight; i++) {
		SetPos(LittleShipRow + i, LittleShipCol);
		for (int j = 0; j < LittleShipWidth; j++) {
			if (PrintLittleShip[i][j] == 'u') { SetColor(COLOR::black, COLOR::blue); cout << char(178); }
			if (PrintLittleShip[i][j] == 'n') { SetColor(COLOR::black, COLOR::gray);	cout << char(178); }
			if (PrintLittleShip[i][j] == '.') { SetColor(COLOR::black, COLOR::light_blue);	cout << " "; }
			if (PrintLittleShip[i][j] == '*') { SetColor(COLOR::black, COLOR::light_aqua);	cout << char(178); }
			if (PrintLittleShip[i][j] == 'i') { SetColor(COLOR::black, COLOR::yellow);	cout << char(178); }
			if (PrintLittleShip[i][j] == 'r') { SetColor(COLOR::black, COLOR::light_red);	cout << char(178); }
			if (PrintLittleShip[i][j] == 'y') { SetColor(COLOR::black, COLOR::red);	cout << char(178); }
		}
	}
	SetColor(COLOR::black, COLOR::gray);
}