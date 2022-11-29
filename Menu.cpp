#include <iostream>
#include <iomanip>
#include <string>
#include "Win10.h"
using namespace std;

//цвета
int clrActiveFon = COLOR::gray;
int clrActiveTxt = COLOR::blue;
int clrInactiveFon = COLOR::black;
int clrInactiveTxt = COLOR::yellow;
int clrDefFon = COLOR::black;
int clrDefTxt = COLOR::gray;

int menu(string* Item, int cntItem, int Row, int Col, int Select) {
	CursorHide(); //скрытие каретки

	while (true) {
		for (int i = 0; i < cntItem; i++) {
			if (i == Select) {
				SetPos(Row + (i * 2), Col - 5);
				SetColor(clrDefFon, clrDefTxt);
				cout << char(16);
				SetPos(Row + (i * 2), Col + 41);
				cout << char(17);
				SetColor(clrActiveFon, clrActiveTxt);
				SetPos(Row + (i * 2), Col);
			} else {
				SetPos(Row + (i * 2), Col - 5);
				SetColor(clrDefFon, clrDefTxt);
				cout << " ";
				SetPos(Row + (i * 2), Col + 41);
				cout << " ";
				SetPos(Row + (i * 2), Col);
				SetColor(clrInactiveFon, clrInactiveTxt);
			}
			cout << Item[i];
		}
		SetColor(clrDefFon, clrDefTxt);
		{
			int key = _getch();
			switch (key) {
			case _KEY::UP:        case _KEY::LEFT:
				if (Select > 0) {
					Select--;
				} else {
					Select = cntItem - 1;
				}
				break;

			case _KEY::DOWN:      case _KEY::RIGHT:
				if (Select < cntItem - 1) {
					Select++;
				} else {
					Select = 0;
				}
				break;

			case _KEY::ENTER:
				return Select;

			case _KEY::ESC:
				return -1;
			}
		}
	}
}