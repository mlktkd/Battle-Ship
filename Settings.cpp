#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>
#include <conio.h>
#include "Win10.h"
using namespace std;

//заголовок
string TitleSettings[]{
	"  {-----------------------}",
	"{-----------------------} |",
	"|        SETTINGS       | ]",
	"[-----------------------]  "
};
int TitleSettingsHeight = sizeof(TitleSettings) / sizeof(TitleSettings[0]);
int TitleSettingsWidth = TitleSettings[0].size();
//координаты заголовка и текста
int TitleSettingsRow = 7;
int TitleSettingsCol = 58;
int TextSettingsRow = 13;
int TextSettingsCol = 20;
int answerItem = 0;

void PrintTitle(string* Title, int height, int width, int row, int col);

void Settings(int& cntRound) {
	PrintFrame();//рамка
	//вывод заголовка
	PrintTitle(TitleSettings, TitleSettingsHeight, TitleSettingsWidth, TitleSettingsRow, TitleSettingsCol);

	SetPos(18, 48);
	SetColor(COLOR::black, COLOR::gray);
	cout << " S E L E C T   A M O U N T   O F   R O U N D S ";
	SetPos(19, 49);
	SetColor(COLOR::black, COLOR::gray);
	for (int i = 1; i <= 45; i++) {
		cout << char(205);
	}
	int roundsSelect[3]{ 1, 3, 5};
	bool notSelect = false;
	bool selected = false;
	while (true) {
		for (int i = 0; i < 3; i++) {
			if (i == answerItem) {
				SetPos(22 + (i * 2), 60);
				SetColor(COLOR::black, COLOR::gray);
				cout << char(16);
				SetPos(22 + (i * 2), 79);
				cout << char(17);
				SetPos(22 + (i * 2), 65);
				SetColor(COLOR::gray, COLOR::blue);
			} else {
				SetPos(22 + (i * 2), 60);
				SetColor(COLOR::black, COLOR::gray);
				cout << " ";
				SetPos(22 + (i * 2), 79);
				cout << " ";
				SetPos(22 + (i * 2), 65);
				SetColor(COLOR::black, COLOR::yellow);
			}
			cout << "     " << roundsSelect[i] << "     ";
		}
		SetColor(COLOR::black, COLOR::bright_white);
		int answer = _getch();
		switch (answer) {
		case _KEY::UP:
			if (answerItem > 0) {
				answerItem--;
			} else {
				answerItem = 2;
			}
			break;
		case _KEY::DOWN:
			if (answerItem < 2) {
				answerItem++;
			} else {
				answerItem = 0;
			}
			break;
		case _KEY::ESC:
			notSelect = true;
		case _KEY::ENTER:
			cntRound = roundsSelect[answerItem];
			selected = true;
			break;
		}
		if (notSelect) {
			CLS;
			break;
		}
		if (selected) {
			CLS;
			break;
		}
	}
}