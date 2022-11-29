#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>
#include <conio.h>
#include "Win10.h"
using namespace std;

//���������
string TitleAuthor[]{
	"  {-----------------------}",
	"{-----------------------} |",
	"|   ABOUT THE AUTHOR    | ]",
	"[-----------------------]  "
};
int TitleAuthorHeight = sizeof(TitleAuthor) / sizeof(TitleAuthor[0]);
int TitleAuthorWidth = TitleAuthor[0].size();
//���������� ��������� � ������
int TitleAuthorRow = 7;
int TitleAuthorCol = 58;
int TextAuthorRow = 13;
int TextAuthorCol = 20;

//��������
int AmountStrFile(string fileName);
string* ShipPrint = new string[AmountStrFile("ShipPrint.txt")];
int ShipPrintHeight;
int ShipPrintWidth;
void LoadPole(string* pole, string fileName, int& height);
void DrowShipPrint();
void PrintTitle(string* Title, int height, int width, int row, int col);


void AboutAuthor() {
	PrintFrame();//�����
	LoadPole(ShipPrint, "ShipPrint.txt", ShipPrintHeight);
	ShipPrintWidth = ShipPrint[0].size();
	DrowShipPrint();

	//����� ���������
	PrintTitle(TitleAuthor, TitleAuthorHeight, TitleAuthorWidth, TitleAuthorRow, TitleAuthorCol);

	//����� �� ����������
	SetPos(TextAuthorRow, TextAuthorCol);
	SetColor(COLOR::black, COLOR::light_aqua);
	cout << "Hi, dear player!";
	SetPos(TextAuthorRow + 2, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "I'm very excited to show you my first game";
	SetPos(TextAuthorRow + 3, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "In fact, this is my first large (for a beginner) project.";
	SetPos(TextAuthorRow + 4, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "I have been studying with you for exactly 5 months.";
	SetPos(TextAuthorRow + 5, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "This is an incredible experience...";
	SetPos(TextAuthorRow + 6, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "Many thanks to the teachers for their input and patience!";
	SetPos(TextAuthorRow + 7, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "I hope we reach the end : )";
	SetPos(TextAuthorRow + 8, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "This is such a humble beginning...";
	//�����������
	SetPos(TextAuthorRow + 10, TextAuthorCol);
	SetColor(COLOR::black, COLOR::blue);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	//����� �� �������
	SETLOCAL_RU;
	SetPos(TextAuthorRow + 12, TextAuthorCol);
	SetColor(COLOR::black, COLOR::light_aqua);
	cout << "������, ������� �����!";
	SetPos(TextAuthorRow + 14, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "� ����� ����, �������� ��� ���� ������ ����.";
	SetPos(TextAuthorRow + 15, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "�� ����� ���� ��� ��� ������ ��������(��� �������) ������.";
	SetPos(TextAuthorRow + 16, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "� ���� � ����� ��� ����� 5 �������.";
	SetPos(TextAuthorRow + 17, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "��� ����������� ����... ";
	SetPos(TextAuthorRow + 18, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "�������� ������� �������������� �� ����� � ��������!";
	SetPos(TextAuthorRow + 19, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "�������, �� ������ �� ����� : )";
	SetPos(TextAuthorRow + 20, TextAuthorCol);
	SetColor(COLOR::black, COLOR::yellow);
	cout << "��� ����� �������� ������";
	SETLOCAL_EN;

	SetPos(TextAuthorRow + 22, TextAuthorCol);
	SetColor(COLOR::black, COLOR::blue);
	cout << "~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~";
	SetPos(TextAuthorRow + 24, TextAuthorCol);
	SetColor(COLOR::black, COLOR::light_aqua);
	cout << "Kaliaskarova Malika, SDP-221.1  ";
	SetColor(COLOR::black, COLOR::light_purple);
	cout << char(3);
}

void DrowShipPrint() {
	for (int i = 0; i < ShipPrintHeight; i++) {
		SetPos(TextAuthorRow + 5 + i, TextAuthorCol + 65);
		for (int j = 0; j < ShipPrintWidth; j++) {
			if (ShipPrint[i][j] == 'm') { SetColor(COLOR::black, COLOR::gray); cout << char(178); }
			if (ShipPrint[i][j] == 'g') { SetColor(COLOR::black, COLOR::green);	cout << char(178); }
			if (ShipPrint[i][j] == 'b') { SetColor(COLOR::black, COLOR::blue);	cout << char(178); }
			if (ShipPrint[i][j] == 'l') { SetColor(COLOR::black, COLOR::light_green);	cout << char(178); }
			if (ShipPrint[i][j] == '.') { SetColor(COLOR::black, COLOR::light_blue);	cout << char(178); }
			if (ShipPrint[i][j] == '*') { SetColor(COLOR::black, COLOR::aqua);	cout << char(178); }
		}
	}
	SetColor(COLOR::black, COLOR::gray);
}
