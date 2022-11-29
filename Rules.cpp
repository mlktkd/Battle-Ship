#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>
#include <conio.h>
#include "Win10.h"
using namespace std;

//заголовок
string TitleRules[]{
	"  {-----------------------}",
	"{-----------------------} |",
	"|   RULES OF THE GAME   | ]",
	"[-----------------------]  "
};
int TitleRulesHeight = sizeof(TitleRules) / sizeof(TitleRules[0]);
int TitleRulesWidth = TitleRules[0].size();

//текст о кораблях
string ShipsRules[]{
	"There are 10 ships in total :",
	"4-deck - 1 piece             ",
  "3-deck - 2 pieces            ",
  "2-deck - 3 pieces            ",
  "1-deck - 4 pieces            "
};
int ShipsRulesHeight = sizeof(ShipsRules) / sizeof(ShipsRules[0]);
int ShipsRulesWidth = ShipsRules[0].size();
//визуал-картинка о кораблях
string ShipsInfo[]{
	"##  ##  ##  ##   x1",
	"                   ",
	"##  ##  ##       x2",
	"                   ",
	"##  ##           x3",
	"                   ",
	"##               x4",
};
int ShipsHeight = sizeof(ShipsInfo) / sizeof(ShipsInfo[0]);
int ShipsWidth = ShipsInfo[0].size();

int FrameRow = 2;
int FrameCol = 6;
int TitleRulesRow = 7;
int TitleRulesCol = 58;
int RulesRow = 13;
int RulesCol = 20;

//прототипы
void PrintFrame();
void PrintTitle(string* Title, int height, int width, int row, int col);

void Rules() {
	PrintFrame();
	PrintTitle(TitleRules, TitleRulesHeight, TitleRulesWidth, TitleRulesRow, TitleRulesCol);
	//текст правил
	SetPos(RulesRow, RulesCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "1.  The game \"Battleship\" is played by the player and the computer.";
	SetPos(RulesRow + 1, RulesCol);
	cout << "    The player's playing field will be drawn on the screen, where you must place your ships.";
	SetColor(COLOR::black, COLOR::light_aqua);
	SetPos(RulesRow + 4, RulesCol);
	cout << "2.  SHIPS";
	SetColor(COLOR::black, COLOR::light_aqua);
	SetPos(RulesRow + 5, RulesCol + 4);
	cout << char(205) << char(205) << char(205) << char(205) << char(205);
	SetColor(COLOR::black, COLOR::light_aqua);
	for (int i = 0; i < ShipsRulesHeight; i++) {
		SetPos(RulesRow + 6 + i, RulesCol + 4);
		for (int j = 0; j < ShipsRulesWidth; j++) {
			cout << ShipsRules[i][j];
		}
	}
	for (int i = 0; i < ShipsHeight; i++) {
		SetPos(RulesRow + 4 + i, RulesCol + 65);
		for (int j = 0; j < ShipsWidth; j++) {
		if (ShipsInfo[i][j] == '#') { SetColor(COLOR::black, COLOR::blue);	cout << char(178); }
		else { SetColor(COLOR::black, COLOR::blue);	cout << ShipsInfo[i][j]; }
	  }
	}
	SetColor(COLOR::black, COLOR::yellow);
	SetPos(RulesRow + 13, RulesCol);
	cout << "3.  The rules for the location of ships are simple - it is impossible for ships to touch either sides or corners.";
	SetColor(COLOR::black, COLOR::yellow);
	SetPos(RulesRow + 14, RulesCol);
	cout << "    There must be at least one cell between them. You can press ships to the edges of the playing field.";
	SetColor(COLOR::black, COLOR::light_aqua);
	SetPos(RulesRow + 17, RulesCol);
	cout << "4.  The goal of this game is to destroy all enemy ships. The one who does it first wins.";
	SetColor(COLOR::black, COLOR::yellow);
	SetPos(RulesRow + 20, RulesCol);
	cout << "5.  The player and the computer take turns, the player takes the first shot.";
	SetColor(COLOR::black, COLOR::yellow);
	SetPos(RulesRow + 21, RulesCol);
	cout << "    - If after the shot the color of the coordinate turned blue, then the player missed";
	SetColor(COLOR::black, COLOR::yellow);
	SetPos(RulesRow + 22, RulesCol);
	cout << "    - If after the shot the color of the coordinate turned red, then the player hit the enemy ship";
	SetColor(COLOR::black, COLOR::light_aqua);
	SetPos(RulesRow + 24, RulesCol);
	cout << "6.  If the player hits the ship, he makes his turn again until he misses!";
}

//печать рамки
void PrintFrame() {
	//рамка (верхние левые углы)
	SetPos(FrameRow, FrameCol);
	SetColor(COLOR::black, COLOR::light_blue);
	cout << char(201);
	SetPos(FrameRow + 1, FrameCol + 2);
	SetColor(COLOR::black, COLOR::light_blue);
	cout << char(201);
	//рамка (верхние правые углы)
	SetPos(FrameRow, FrameCol + 134);
	SetColor(COLOR::black, COLOR::light_blue);
	cout << char(187);
	SetPos(FrameRow + 1, FrameCol + 132);
	SetColor(COLOR::black, COLOR::light_blue);
	cout << char(187);
	//рамка (нижние левые углы)
	SetPos(FrameRow + 39, FrameCol);
	SetColor(COLOR::black, COLOR::light_blue);
	cout << char(200);
	SetPos(FrameRow + 38, FrameCol + 2);
	SetColor(COLOR::black, COLOR::light_blue);
	cout << char(200);
	//рамка (нижние правые углы)
	SetPos(FrameRow + 39, FrameCol + 134);
	SetColor(COLOR::black, COLOR::light_blue);
	cout << char(188);
	SetPos(FrameRow + 38, FrameCol + 132);
	SetColor(COLOR::black, COLOR::light_blue);
	cout << char(188);
	//рамка (внешние линии)
	for (int i = 1; i < 134; i++) {
		SetPos(FrameRow, FrameCol + i);
		SetColor(COLOR::black, COLOR::light_blue);
		cout << char(205);
	}
	for (int i = 1; i < 134; i++) {
		SetPos(FrameRow + 39, FrameCol + i);
		SetColor(COLOR::black, COLOR::light_blue);
		cout << char(205);
	}
	for (int i = 1; i < 39; i++) {
		SetPos(FrameRow + i, FrameCol);
		SetColor(COLOR::black, COLOR::light_blue);
		cout << char(186);
	}
	for (int i = 1; i < 39; i++) {
		SetPos(FrameRow + i, FrameCol + 134);
		SetColor(COLOR::black, COLOR::light_blue);
		cout << char(186);
	}
	//рамка (внутренние линии)
	for (int i = 3; i < 132; i++) {
		SetPos(FrameRow + 1, FrameCol + i);
		SetColor(COLOR::black, COLOR::light_blue);
		cout << char(205);
	}
	for (int i = 3; i < 132; i++) {
		SetPos(FrameRow + 38, FrameCol + i);
		SetColor(COLOR::black, COLOR::light_blue);
		cout << char(205);
	}
	for (int i = 2; i < 38; i++) {
		SetPos(FrameRow + i, FrameCol + 2);
		SetColor(COLOR::black, COLOR::light_blue);
		cout << char(186);
	}
	for (int i = 2; i < 38; i++) {
		SetPos(FrameRow + i, FrameCol + 132);
		SetColor(COLOR::black, COLOR::light_blue);
		cout << char(186);
	}
}

//печать заголовка
void PrintTitle(string* Title, int height, int width, int row, int col) {
	for (int i = 0; i < height; i++) {
		SetPos(row + i, col);
		for (int j = 0; j < width; j++) {
			if (Title[i][j] == '{') { SetColor(COLOR::black, COLOR::blue);	cout << char(201); }
			else if (Title[i][j] == '}') { SetColor(COLOR::black, COLOR::blue);	cout << char(187); }
			else if (Title[i][j] == '[') { SetColor(COLOR::black, COLOR::blue);	cout << char(200); }
			else if (Title[i][j] == ']') { SetColor(COLOR::black, COLOR::blue);	cout << char(188); }
			else if (Title[i][j] == '-') { SetColor(COLOR::black, COLOR::blue);	cout << char(205); }
			else if (Title[i][j] == '|') { SetColor(COLOR::black, COLOR::blue);	cout << char(186); }
			else { SetColor(COLOR::black, COLOR::yellow);	cout << Title[i][j]; }
		}
	}
}