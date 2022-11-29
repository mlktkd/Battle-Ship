#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <time.h>
#include <conio.h>
#include "Win10.h"
using namespace std;

//���� � �������
int AmountStrFile(string fileName);
string* PolePl = new string[AmountStrFile("Pole.txt")];        //���� ������
string* PolePC = new string[AmountStrFile("Pole.txt")];        //���� ����������
string* PolePlAttack = new string[AmountStrFile("Pole.txt")];  //���� ��� ����� �������
int PolePlHeight;
int PolePlWidth;
int PolePlAttackHeight;
int PolePlAttackWidth;

//�������� ����� ��������� ���� � �������
string* GameOver = new string[AmountStrFile("GameOver.txt")];   //�������� ����� ����
string* YouWon = new string[AmountStrFile("Win.txt")];          //�������� �������
int GameOverHeight;
int GameOverWidth;
int YouWonHeight;
int YouWonWidth;

//���������� ��� ������� �����
int PolePlRow = 7;
int PolePlCol = 18;
int PolePlAttackRow = 7;
int PolePlAttackCol = 80;
int GameOverRow = 17;
int GameOverCol = 22;
int YouWonRow = 17;
int YouWonCol = 25;

//����������� ������������ ������ ������� ������������ �������� ������ ������
enum DIR {
	left,
	right,
	up,
	down
};

//��������� ��� ���������
bool FreePlaceForConfirm(string* pole, int row, int col, bool& isEmpty);
void PrintTable(string* pole, int i, int j);

//��������a �������
struct Ship {
	int row;         //�������� ���������� �� ���������
	char col;        //�������� ���������� �� �����������
	int cntDeck;     //���������� ����� �������
	DIR dir;         //����������� ���������� ����� ������� ������������ ��� �������� ����������

	//���������� ������� ��� ������ �������
	void PrintShipSelect() {
		//������� �������� ��������� � ������� �������� ���� 
		int rows = row * 2 + 2;
		int cols = (col - 64) * 4 + 4;
		//
		SetPos(PolePlRow + 1, PolePlCol + 3);
		SetColor(COLOR::black, COLOR::yellow);
		cout << " Your map: ";
		SetPos(PolePlRow + 3, PolePlCol);
		for (int i = 0; i < PolePlHeight; i++) {
			SetPos(PolePlRow + 3 + i, PolePlCol);
			for (int j = 0; j < PolePlWidth; j++) {
				bool isFound = false;  //��� �������� �� ���������� ���������� ����� ��� �������
				if (dir == DIR::right && i == rows) {  //������ ��������������� ���������� �����
					for (int decks = 0; decks < cntDeck; decks++) {  //decks - ��� �������� �� ���������� ������ ������
						if (j == cols + (decks * 4)) {
							FreePlaceForConfirm(PolePl, i, j, isFound);  //����� ������� �� ������� ���������� �����
							if (isFound) {  //���� ��������
								SetColor(COLOR::light_blue, COLOR::green);
								cout << char(178) << char(178) << char(178);
								j += 2;
							}
							if (!isFound) {  //���� ������
								SetColor(COLOR::light_blue, COLOR::red);
								cout << char(178) << char(178) << char(178);
								j += 2;
								isFound = true;             
							}
						}
					}
					if (!isFound) {	PrintTable(PolePl, i, j);	} //���� ���������� i � j �������� ������������� � �������
				}
				else if (dir == DIR::left && i == rows) {  //������ �������������� ���������� �����
					for (int decks = 0; decks < cntDeck; decks++) {
						if (j == cols - (decks * 4)) {
							FreePlaceForConfirm(PolePl, i, j, isFound);
							if (isFound) {
								SetColor(COLOR::light_blue, COLOR::green);
								cout << char(178) << char(178) << char(178);
								j += 2;
							}
							if (!isFound) {
								SetColor(COLOR::light_blue, COLOR::red);
								cout << char(178) << char(178) << char(178);
								j += 2;
								isFound = true;
							}
						}
					}
					if (!isFound) {	PrintTable(PolePl, i, j);	}
				}
				else if (dir == DIR::up && (j == cols)) {  //������ �������� ���������� �����
					for (int decks = 0; decks < cntDeck; decks++) {
						if (i == rows - (decks * 2)) {
							FreePlaceForConfirm(PolePl, i, j, isFound);
							if (isFound) {
								SetColor(COLOR::light_blue, COLOR::green);
								cout << char(178) << char(178) << char(178);
								j += 2;
							}
							if (!isFound) {
								SetColor(COLOR::light_blue, COLOR::red);
								cout << char(178) << char(178) << char(178);
								j += 2;
								isFound = true;
							}
						}
					}
					if (!isFound) {	PrintTable(PolePl, i, j);	}
				}
				else if (dir == DIR::down && (j == cols)) {  ////������ ������� ���������� �����
					for (int decks = 0; decks < cntDeck; decks++) {
						if (i == rows + (decks * 2)) {
							FreePlaceForConfirm(PolePl, i, j, isFound);
							if (isFound) {
								SetColor(COLOR::light_blue, COLOR::green);
								cout << char(178) << char(178) << char(178);
								j += 2;
							}
							if (!isFound) {
								SetColor(COLOR::light_blue, COLOR::red);
								cout << char(178) << char(178) << char(178);
								j += 2;
								isFound = true;
							}
						}
					}
					if (!isFound) {	PrintTable(PolePl, i, j);	}
				}
				else { PrintTable(PolePl, i, j); }   //���� ���������� i � j �� �������� ������������ �������
			}
		}
	}
};

//��������� ��������� ��� ����� 
struct AttackCoord {
	int row;
	char col;
};

//��������� �������
void PrintFrame();
void LoadPole(string* pole, string fileName, int& height);
void DetermPlayerCoord(bool& isExit);
void DetermPCCoord();
void DrawPole();
void SelectAttackCoord(AttackCoord& PlAttack, bool& isExit);
bool HitOrMissPl(int row, int col1, int col2, int col3, bool& isHit);
bool HitOrMissPC(int row, int col1, int col2, int col3, bool& isHitOrMiss, bool& isHit);
void CoordToRowColConversion1(AttackCoord coord, int& row, int& col1, int& col2, int& col3, int& col1_1, int& col2_2, int& col3_3);
void CoordToRowColConversion2(int CoordRow, char CoordCol, int& row, int& col1, int& col2, int& col3);
bool FreePlaceForNewAttack(int row, int col, AttackCoord& PCAttack, bool& isEmpty);
void CoordConfirm(string* pole, int row, int col1, int col2, int col3, char sym);
void DrawWin();
void DrawGameOver();
//

//������ ����
void StartGame(int Rounds) {
	int cntWinsPl = 0;
	int cntWinsPC = 0;
	bool isExit = false;  //���������� ��� �������� �� ����� �� ����
	LoadPole(PolePl, "Pole.txt", PolePlHeight);
	LoadPole(PolePC, "Pole.txt", PolePlAttackHeight);
	LoadPole(PolePlAttack, "Pole.txt", PolePlAttackHeight);
	LoadPole(GameOver, "GameOver.txt", GameOverHeight);
	LoadPole(YouWon, "Win.txt", YouWonHeight);
	for (int roundNum = 1; roundNum <= Rounds; roundNum++) {
		CLS;
		PrintFrame(); //�����
		SetPos(PolePlAttackRow + 27, PolePlAttackCol + 30);
		SetColor(COLOR::black, COLOR::yellow);
		cout << "  R O U N D  " << roundNum << " of " << Rounds;  //����� �������� ������ �� ������ �����
		SetPos(PolePlAttackRow + 28, PolePlAttackCol + 35);
		SetColor(COLOR::black, COLOR::green);
		cout << "Player wins: " << cntWinsPl;  //���������� ����� ������
		SetPos(PolePlAttackRow + 29, PolePlAttackCol + 35);
		SetColor(COLOR::black, COLOR::light_red);
		cout << " Enemy wins: " << cntWinsPC;  //���������� ����� ����������

	//�������� ����� � �������� �� �����
		LoadPole(PolePl, "Pole.txt", PolePlHeight);
		LoadPole(PolePC, "Pole.txt", PolePlAttackHeight);
		LoadPole(PolePlAttack, "Pole.txt", PolePlAttackHeight);
		//��������� �������� �����
		PolePlWidth = PolePl[0].size();
		PolePlAttackWidth = PolePlAttack[0].size();
		GameOverWidth = GameOver[0].size();
		YouWonWidth = YouWon[0].size();
		//
		DetermPlayerCoord(isExit); //��������� ��������� ����� ������
		if (isExit) {
			break;
		}
		DetermPCCoord();  //��������� ��������� ����� ����������
		CLS;
		PrintFrame(); //�����
		SetPos(PolePlAttackRow + 27, PolePlAttackCol + 30);
		SetColor(COLOR::black, COLOR::yellow);
		cout << "  R O U N D  " << roundNum << " of " << Rounds;  //����� �������� ������ �� ������ �����
		SetPos(PolePlAttackRow + 28, PolePlAttackCol + 35);
		SetColor(COLOR::black, COLOR::green);
		cout << "Player wins: " << cntWinsPl;  //���������� ���������� �������� ������� ������
		SetPos(PolePlAttackRow + 29, PolePlAttackCol + 35);
		SetColor(COLOR::black, COLOR::light_red);
		cout << " Enemy wins: " << cntWinsPC;  //���������� ���������� �������� ������� ��
		SetPos(PolePlRow + 31, PolePlCol);
		SetColor(COLOR::black, COLOR::gray);
		cout << "If you want to exit, in the coordinate input field, write \"exit\"";  //��� ������ � ���� ����� ��������� �������� "exit"
		bool isGameOver = false;  //���������� ��� �������� �� ��������
		bool isWin = false;  //���������� ��� �������� �� �������
		AttackCoord PlAttack;  //���������� ����� �������
		AttackCoord PCAttack; //���������� ����� �����������

		DrawPole();  //������ ��������� ����
		while (!isGameOver && !isWin && !isExit) {  //�������� ���� ����
			int cntPlShip = 0;  //���������� ��� �������� ����������� ����� ������
			int cntPCShip = 0;  //���������� ��� �������� ����������� ����� ����������
			//���� ���� ���������, �� ����� ����� �����
			while (true) {
				//������ ��������� �� ��� ������
				SetPos(PolePlAttackRow + 27, PolePlAttackCol);
				SetColor(COLOR::black, COLOR::yellow);
				cout << char(16);
				SetPos(PolePlAttackRow + 29, PolePlAttackCol);
				SetColor(COLOR::black, COLOR::yellow);
				cout << " ";
				SetPos(PolePlAttackRow + 27, PolePlAttackCol + 4);
				SetColor(COLOR::black, COLOR::yellow);
				cout << "YOUR TURN";
				SetPos(PolePlAttackRow + 29, PolePlAttackCol + 4);
				SetColor(COLOR::black, COLOR::gray);
				cout << "ENEMY'S TURN";
				//
				SelectAttackCoord(PlAttack, isExit);   //��������� ��������� ��� ����� ����������
				if (isExit) {
					break;
				}
				//�������� ��������� ��� ����� � ������� �������� ����  (� ����� �������� �� ���� ��� ������)
				int rowAttackPl;
				int colAttack1Pl, colAttack2Pl, colAttack3Pl, colAttack1_1Pl, colAttack2_2Pl, colAttack3_3Pl;
				CoordToRowColConversion1(PlAttack, rowAttackPl, colAttack1Pl, colAttack2Pl, colAttack3Pl, colAttack1_1Pl, colAttack2_2Pl, colAttack3_3Pl);
				//
				//�������� �� ������ � ���������
				bool isHit = false;
				if (PlAttack.col >= 'A' && PlAttack.col <= 'J') {
					HitOrMissPl(rowAttackPl, colAttack1Pl, colAttack2Pl, colAttack3Pl, isHit);
				}
				if (PlAttack.col >= 'a' && PlAttack.col <= 'j') {
					HitOrMissPl(rowAttackPl, colAttack1_1Pl, colAttack2_2Pl, colAttack3_3Pl, isHit);
				}
				if (isHit) {  //���� ���� ��������� -> ��������� ���� � ����� �����
					DrawPole();
					//������� ��������� ���������� �������� ���������� � �������� �� �������
					for (int i = 0; i < PolePlAttackHeight; i++) {
						for (int j = 0; j < PolePlAttackWidth; j++) {
							if (PolePC[i][j] == 'o') {
								cntPCShip++;
							}
						}
					}
					if (cntPCShip == 0) {
						isWin = true;
						break;
					}
				}
				if (!isHit || isWin) {
					break;
				}
			}
			if (isWin) {
				break;
			}
			if (isExit) {
				break;
			}
			DrawPole(); //��������� ���� ��� ��������� ���������� ���������
			Sleep(1500);  //��������� �����
			//������ ��������� �� ��� ����������
			SetPos(PolePlAttackRow + 27, PolePlAttackCol);
			SetColor(COLOR::black, COLOR::yellow);
			cout << " ";
			SetPos(PolePlAttackRow + 29, PolePlAttackCol);
			SetColor(COLOR::black, COLOR::light_red);
			cout << char(16);
			SetPos(PolePlAttackRow + 27, PolePlAttackCol + 4);
			SetColor(COLOR::black, COLOR::gray);
			cout << "YOUR TURN";
			SetPos(PolePlAttackRow + 29, PolePlAttackCol + 4);
			SetColor(COLOR::black, COLOR::light_red);
			cout << "ENEMY'S TURN";
			Sleep(1500);  //��������� �����

			//��������� ��������� ��� ����� ����������
			while (true) {
				bool empty = false; //���������� ��� �������� �� ������� ��������� ������ ������ ��������� �������
				for (int i = 0; i < PolePlHeight; i++) {
					for (int j = 0; j < PolePlWidth; j += 4) {
						if (PolePl[i][j] == 'x') {
							FreePlaceForNewAttack(i, j, PCAttack, empty);
						}
						if (empty) {
							break;
						}
					}
				}
				if (!empty) {
					PCAttack.row = RAND(1, 10);
					PCAttack.col = RAND('A', 'J');
				}
				int rowAttackPC;
				int colAttack1PC;
				int colAttack2PC;
				int colAttack3PC;
				CoordToRowColConversion2(PCAttack.row, PCAttack.col, rowAttackPC, colAttack1PC, colAttack2PC, colAttack3PC);
				bool isHitOrMiss = false; //�������� �� ������������ ���������� (��������� ����������)
				bool isHit = false; //�������� �� ������ � ���������
				HitOrMissPC(rowAttackPC, colAttack1PC, colAttack2PC, colAttack3PC, isHitOrMiss, isHit);
				if (isHitOrMiss && isHit) {  //���� ���� ��������� -> ��������� ���� � ����� �����
					DrawPole();
					Sleep(1500);
					//�������� �� ��������
					for (int i = 0; i < PolePlHeight; i++) {
						for (int j = 0; j < PolePlWidth; j++) {
							if (PolePl[i][j] == 'o') {
								cntPlShip++;
							}
						}
					}
					if (cntPlShip == 0) {
						isGameOver = true;
						break;
					}
				}
				if (isHitOrMiss && !isHit) {
					break;
				}
			}
			DrawPole(); //��������� ���� ��� ��������� ���������� ���������
		} //while (!GameOver && !Win && !isExit)

		SetColor(COLOR::black, COLOR::white); //������� ���������� �����
		if (isWin) { //��������� �������� ��������
			cntWinsPl++;
		}
		if (isGameOver) {  //��������� �������� ���������
			cntWinsPC++;
		}
		if (isExit) {
			break;
		}
	}
	if (isExit) {
		CLS;
	}
	else if (cntWinsPl > cntWinsPC) {
		CLS;
		DrawWin();
		PAUSE;
	} else {
		CLS;
		DrawGameOver();
		PAUSE;
	}

}//StartGame()

//������ ����� �� �����
//������� ���������� ����� ��� �������� �������
int AmountStrFile(string fileName) {
	int cntStr = 0; //������ �����
	string str;
	ifstream file(fileName);
	if (!file.is_open()) {
		cout << " File not found!\n";
	} else {
		while (!file.eof()) {
			getline(file, str);
			cntStr++;
		}
	}
	return cntStr;
}
//�������� ���� ��� �������� �� �����
void LoadPole(string* pole, string fileName, int& height) {
	ifstream file(fileName);   //������ ���� �� �����
	if (!file.is_open()) {
		cout << " File not found!\n";
	} else {
		int i = 0;
		while (!file.eof()) {
			string str;
			getline(file, str);
			pole[i] = str;
			i++;
		}
		height = i;  //�������� ������ ����
	}
}
//

//������� ������ ��������� �������� �������
void DetermPlayerCoord(bool& isExit) {
	for (int i = 4; i >= 1; i--) {        //������ � 4-� ��������� ����� �� 1-���������
		for (int j = 1; j + i <= 5; j++) {  //������� ���������� ����������� �������  
			bool is�onfirmed = false;  //��� ��������: ������������� �� �������������� �������?
			
			//�������� ��������� ���������� �������
			Ship shipPl;
			shipPl.row = 2;
			shipPl.col = 'A';
			shipPl.cntDeck = i;
			shipPl.dir = DIR::right;

			SetPos(PolePlAttackRow + 3, PolePlAttackCol - 1);
			SetColor(COLOR::yellow, COLOR::black);
			cout << " Select ship location! ";
			SetPos(PolePlAttackRow + 5, PolePlAttackCol - 1);
			SetColor(COLOR::black, COLOR::gray);
			cout << " - to flip the ship, press \"SPACE\"";
			SetPos(PolePlAttackRow + 6, PolePlAttackCol - 1);
			cout << " - to confirm the location of the ship, press \"ENTER\"\n";
			SetPos(PolePlAttackRow + 7, PolePlAttackCol - 1);
			cout << " - to exit, press \"ESC\"\n";

			shipPl.PrintShipSelect(); //������ ����������
			while (true) {
				if (_kbhit()) {
					int key = _getch();
					switch (key) {
					case _KEY::UP:  //����� �����
						if ((shipPl.dir == DIR::right || shipPl.dir == DIR::left || shipPl.dir == DIR::down) && shipPl.row - 1 >= 1) { shipPl.row--; } 
						else if (shipPl.dir == DIR::up && shipPl.row - shipPl.cntDeck >= 1) { shipPl.row--; }
						break;
					case _KEY::DOWN:  //����� ����
						if ((shipPl.dir == DIR::right || shipPl.dir == DIR::left || shipPl.dir == DIR::up) && shipPl.row + 1 <= 10) { shipPl.row++; } 
						else if (shipPl.dir == DIR::down && shipPl.row + shipPl.cntDeck <= 10) { shipPl.row++; }
						break;
					case _KEY::LEFT:  //����� �����
						if ((shipPl.dir == DIR::up || shipPl.dir == DIR::down || shipPl.dir == DIR::right) && shipPl.col - 1 >= 'A') { shipPl.col--; } 
						else if (shipPl.dir == DIR::left && shipPl.col - shipPl.cntDeck >= 'A') { shipPl.col--; }
						break;
					case _KEY::RIGHT:  //����� ������
						if ((shipPl.dir == DIR::up || shipPl.dir == DIR::down || shipPl.dir == DIR::left) && shipPl.col + 1 <= 'J') { shipPl.col++; } 
						else if (shipPl.dir == DIR::right && shipPl.col + shipPl.cntDeck <= 'J') { shipPl.col++; }
						break;
					case _KEY::SPACE:  //�������� �������
						if (shipPl.dir == DIR::right) {
							if (shipPl.row + (shipPl.cntDeck - 1) <= 10) { shipPl.dir = DIR::down; } 
							else if (shipPl.col - (shipPl.cntDeck - 1) >= 'A') { shipPl.dir = DIR::left; } 
							else if (shipPl.row - (shipPl.cntDeck - 1) >= 1) { shipPl.dir = DIR::up; }
						} else if (shipPl.dir == DIR::left) {
							if (shipPl.row - (shipPl.cntDeck - 1) >= 1) { shipPl.dir = DIR::up; } 
							else if (shipPl.col + (shipPl.cntDeck - 1) <= 'J') { shipPl.dir = DIR::right; } 
							else if (shipPl.row + (shipPl.cntDeck - 1) <= 10) { shipPl.dir = DIR::down; }
						} else if (shipPl.dir == DIR::up) {
							if (shipPl.col + (shipPl.cntDeck - 1) <= 'J') { shipPl.dir = DIR::right; } 
							else if (shipPl.row + (shipPl.cntDeck - 1) <= 10) { shipPl.dir = DIR::down; } 
							else if (shipPl.col - (shipPl.cntDeck - 1) >= 'A') { shipPl.dir = DIR::left; }
						} else {
							if (shipPl.col - (shipPl.cntDeck - 1) >= 'A') { shipPl.dir = DIR::left; } 
							else if (shipPl.row - (shipPl.cntDeck - 1) >= 1) { shipPl.dir = DIR::up; } 
							else if (shipPl.col + (shipPl.cntDeck - 1) <= 'J') { shipPl.dir = DIR::right; }
						}
						break;
					case _KEY::ESC:
						isExit = true;
						break;
					case _KEY::ENTER:  //������������� ������
						int cntEmpty = 0;  //������� ���������� ��������� ������ ��� �������� �� ����������� ��������� ������, 
						                   //�������� ������ ��������� ������� �� �������
						//�������� ��������� ��� ��������� � ������� �������� ����
						int row;
						int col1, col2, col3;
						CoordToRowColConversion2(shipPl.row, shipPl.col, row, col1, col2, col3);
						//
						// �������� �� ����������� ��������� ������� � ���������
						FreePlaceForConfirm(PolePl, row, col2, is�onfirmed);
						if (is�onfirmed) {
							if (shipPl.cntDeck > 1) {
								if (shipPl.dir == DIR::right) {  //������ ��������������� ���������� �������
									for (int k = 0; k < shipPl.cntDeck; k++) {
										CoordConfirm(PolePl, row, col1 + (k * 4), col2 + (k * 4), col3 + (k * 4), 'o');
									}
								}
								if (shipPl.dir == DIR::left) {  //������ �������������� ���������� �������
									for (int k = 0; k < shipPl.cntDeck; k++) {
										CoordConfirm(PolePl, row, col1 - (k * 4), col2 - (k * 4), col3 - (k * 4), 'o');
									}
								}
								if (shipPl.dir == DIR::up) {    //������ �������� ���������� �������
									for (int k = 0; k < shipPl.cntDeck; k++) {
										CoordConfirm(PolePl, row - (k * 2), col1, col2, col3, 'o');
									}
								}
								if (shipPl.dir == DIR::down) {  //������ ������� ���������� �������
									for (int k = 0; k < shipPl.cntDeck; k++) {
										CoordConfirm(PolePl, row + (k * 2), col1, col2, col3, 'o');
									}
								}
							}
							if (shipPl.cntDeck == 1) {  //������ ������������� �������
								CoordConfirm(PolePl, row, col1, col2, col3, 'o');
							}
						}
					}
				}
				if (isExit) {
					break;
				}
				shipPl.PrintShipSelect();
				if (is�onfirmed) {  //�������� �� ������������� ��������������
					break;
				}
			} //while (true)
			if (isExit) {
				break;
			}
		}
		if (isExit) {
			break;
		}
	}
	SetColor(COLOR::black, COLOR::white); //������� ���������� �����
}
//������� ������ ��������� �������� �����������
void DetermPCCoord() {
	for (int i = 4; i >= 1; i--) {           //������ � 4-� ��������� ����� �� 1-���������
		for (int j = 1; j + i <= 5; j++) {		 //������� ���������� ����������� �������  
			bool is�onfirmed = false;   //���������� ��� ������������� ��������� �������
			while (true) {
				Ship shipPC;
				//����������� ��������� �������� ��� ��������� �������
				shipPC.row = RAND(1, 10);
				shipPC.col = RAND('A', 'J');
				shipPC.cntDeck = i;
				int numDirEnum = RAND(1, 4);
				switch (numDirEnum) {
				case 1:
					shipPC.dir = DIR::down;
					break;
				case 2:
					shipPC.dir = DIR::left;
					break;
				case 3:
					shipPC.dir = DIR::right;
					break;
				case 4:
					shipPC.dir = DIR::up;
					break;
				}
				int row;
				int col1, col2, col3;
				CoordToRowColConversion2(shipPC.row, shipPC.col, row, col1, col2, col3);
				//��������: �� ������� �� ���������� ����� �� ������� ����
				if (shipPC.dir == DIR::right && col2 + ((shipPC.cntDeck - 1) * 4) < PolePlAttackWidth - 5
					|| shipPC.dir == DIR::left && col2 - ((shipPC.cntDeck - 1) * 4) > 8
					|| shipPC.dir == DIR::up && row - ((shipPC.cntDeck - 1) * 2) > 3
					|| shipPC.dir == DIR::down && row + ((shipPC.cntDeck - 1) * 2) < PolePlAttackHeight - 3) {
					int cntEmpty = 0;
					if (shipPC.cntDeck > 1) {
						if (shipPC.dir == DIR::right) {
							for (int k = 0; k < shipPC.cntDeck; k++) {
								FreePlaceForConfirm(PolePC, row, col2 + (k * 4), is�onfirmed);  //�������� �� ��������� ������
								if (is�onfirmed) {
									cntEmpty++;
								}
							}
							if (cntEmpty == shipPC.cntDeck) {
								for (int k = 0; k < shipPC.cntDeck; k++) {
									CoordConfirm(PolePC, row, col1 + (k * 4), col2 + (k * 4), col3 + (k * 4), 'o');
								}
							}
						}
						if (shipPC.dir == DIR::left) {
							for (int k = 0; k < shipPC.cntDeck; k++) {
								FreePlaceForConfirm(PolePC, row, col2 - (k * 4), is�onfirmed);  //�������� �� ��������� ������
								if (is�onfirmed) {
									cntEmpty++;
								}
							}
							if (cntEmpty == shipPC.cntDeck) {
								for (int k = 0; k < shipPC.cntDeck; k++) {
									CoordConfirm(PolePC, row, col1 - (k * 4), col2 - (k * 4), col3 - (k * 4), 'o');
								}
							}
						}
						if (shipPC.dir == DIR::up) {
							for (int k = 0; k < shipPC.cntDeck; k++) {
								FreePlaceForConfirm(PolePC, row - (k * 2), col2, is�onfirmed);  //�������� �� ��������� ������
								if (is�onfirmed) {
									cntEmpty++;
								}
							}
							if (cntEmpty == shipPC.cntDeck) {
								for (int k = 0; k < shipPC.cntDeck; k++) {
									CoordConfirm(PolePC, row - (k * 2), col1, col2, col3, 'o');
								}
							}
						}
						if (shipPC.dir == DIR::down) {
							for (int k = 0; k < shipPC.cntDeck; k++) {
								FreePlaceForConfirm(PolePC, row + (k * 2), col2, is�onfirmed);  //�������� �� ��������� ������
								if (is�onfirmed) {
									cntEmpty++;
								}
							}
							if (cntEmpty == shipPC.cntDeck) {
								for (int k = 0; k < shipPC.cntDeck; k++) {
									CoordConfirm(PolePC, row + (k * 2), col1, col2, col3, 'o');
								}
							}
						}
					}
					if (shipPC.cntDeck == 1) {
						FreePlaceForConfirm(PolePC, row, col2, is�onfirmed);
						if (is�onfirmed) {
							CoordConfirm(PolePC, row, col1, col2, col3, 'o');
						}
					}
				}
				if (is�onfirmed) {
					break;
				}
			}
		}
	}
}

//������� ������ ����
void DrawPole() {
	SetPos(PolePlRow - 2, PolePlCol + 3);
	SetColor(COLOR::black, COLOR::yellow);
	cout << " Your map: ";
	SetPos(PolePlAttackRow - 2, PolePlAttackCol + 3);
	SetColor(COLOR::black, COLOR::light_red);
	cout << " Enemy's map: ";
	for (int i = 0; i < PolePlHeight; i++) {  //���������� ���� ������
		SetPos(PolePlRow + i, PolePlCol);
		for (int j = 0; j < PolePlWidth; j++) {
			PrintTable(PolePl, i, j);
		}
	}
	for (int i = 0; i < PolePlAttackHeight; i++) {   //���������� ���� ����������
		SetPos(PolePlAttackRow + i, PolePlAttackCol);
		for (int j = 0; j < PolePlAttackWidth; j++) {
			PrintTable(PolePlAttack, i, j);
		}
	}
}
//������� ������ "You Won"
void DrawWin() {
	PrintFrame(); //�����
	for (int i = 0; i < YouWonHeight; i++) {
		SetPos(YouWonRow + i, YouWonCol);
		for (int j = 0; j < YouWonWidth; j++) {
			if (YouWon[i][j] == 'u') { SetColor(COLOR::black, COLOR::yellow); cout << char(178); } 
			else if (YouWon[i][j] == 'n') { SetColor(COLOR::black, COLOR::gray); cout << char(177); } 
			else { cout << YouWon[i][j]; }
		}
	}
}
//������� ������ "Game Over"
void DrawGameOver() {
	PrintFrame(); //�����
	for (int i = 0; i < GameOverHeight; i++) {
		SetPos(GameOverRow + i, GameOverCol);
		for (int j = 0; j < GameOverWidth; j++) {
			if (GameOver[i][j] == 'm') { SetColor(COLOR::black, COLOR::blue); cout << char(178); } 
			else if (GameOver[i][j] == 'n') { SetColor(COLOR::black, COLOR::gray); cout << char(177); } 
			else { cout << GameOver[i][j]; }
		}
	}
}

//������� ������ ���������� ��� ����� ����������
void SelectAttackCoord(AttackCoord& PlAttack, bool& isExit) {
	while (true) {
		char AttackCoord[5]{};  //�������� ������� ��� ��� ������ ������
		SetPos(PolePlRow + 27, PolePlCol);
		SetColor(COLOR::black, COLOR::light_aqua);
		cout << "Select attack coordinates (row, col). For example: 1A ";
		SetPos(PolePlRow + 28, PolePlCol);
		SetColor(COLOR::black, COLOR::white);
		cout << "    ";
		SetPos(PolePlRow + 28, PolePlCol);
		SetColor(COLOR::black, COLOR::gray);
		cin >> AttackCoord;
		//���� ������ ���������� ������ 10
		if (AttackCoord[0] >= '1' && AttackCoord[0] <= '9' && ((AttackCoord[1] >= 'A' && AttackCoord[1] <= 'J') || (AttackCoord[1] >= 'a' && AttackCoord[1] <= 'j'))) {
			PlAttack.row = AttackCoord[0] - 48;
			PlAttack.col = AttackCoord[1];
			break;
		}
		//���� ������ ���������� ����� 10
		else if (AttackCoord[0] == '1' && AttackCoord[1] == '0' && ((AttackCoord[2] >= 'A' && AttackCoord[2] <= 'J') || (AttackCoord[2] >= 'a' && AttackCoord[2] <= 'j'))) {
	    PlAttack.row = 10;
 			PlAttack.col = AttackCoord[2];
			break;
		}
		else if (AttackCoord[0] == 'e' && AttackCoord[1] == 'x'&& AttackCoord[2] == 'i'&& AttackCoord[3] == 't') {
			isExit = true;
			break;
		}
		else {
			SetPos(PolePlRow + 29, PolePlCol);
			SetColor(COLOR::black, COLOR::red);
			cout << "Wrong coordinate! Try again... ";
		}
	}
}
//������� �������� �� ��������� �������
bool HitOrMissPl(int row, int col1, int col2, int col3, bool& isHit) {
	if (PolePC[row][col2] == 'o') {
		CoordConfirm(PolePC, row, col1, col2, col3, 'x');
		CoordConfirm(PolePlAttack, row, col1, col2, col3, 'x');
		SetPos(PolePlRow + 29, PolePlCol);
		SetColor(COLOR::black, COLOR::gray);
		cout << "                               ";
		SetPos(PolePlRow + 29, PolePlCol);
		SetColor(COLOR::black, COLOR::green);
		cout << "You hit!";
		isHit = true;
	} else if (PolePC[row][col2] == ' ') {
		CoordConfirm(PolePlAttack, row, col1, col2, col3, '#');
		SetPos(PolePlRow + 29, PolePlCol);
		SetColor(COLOR::black, COLOR::gray);
		cout << "                               ";
		SetPos(PolePlRow + 29, PolePlCol);
		SetColor(COLOR::black, COLOR::gray);
		cout << "You missed...";
		isHit = false;
	}
	return isHit;
}
//������� �������� �� ��������� �����������
bool HitOrMissPC(int row, int col1, int col2, int col3, bool &isHitOrMiss, bool &isHit) {
	if (PolePl[row][col2] == 'o') {
		PolePl[row][col1]= 'x';
		PolePl[row][col2] = 'x';
		PolePl[row][col3] = 'x';
		isHitOrMiss = true;
		isHit = true;
	}
	else if (PolePl[row][col2] == ' ') {
		PolePl[row][col1] = '#';
		PolePl[row][col2] = '#';
		PolePl[row][col3] = '#';
		isHitOrMiss = true;
		isHit = false;
	}
	else {
		isHitOrMiss = false;
	}
	return isHitOrMiss;
}
//������� �������� ���������� ����� ��� ��������� �������
bool FreePlaceForConfirm(string* pole, int row, int col, bool& isEmpty) {
		if (pole[row][col] == ' '
		&& pole[row][col - 4] != 'o'
		&& pole[row][col + 4] != 'o'
		&& pole[row - 2][col] != 'o'
		&& pole[row + 2][col] != 'o'
		&& pole[row - 2][col - 4] != 'o'
		&& pole[row + 2][col - 4] != 'o'
		&& pole[row + 2][col + 4] != 'o'
		&& pole[row - 2][col + 4] != 'o') {
		isEmpty = true;
	} else {
		isEmpty = false;
	}
	return isEmpty;
}
//������� �������� ���������� ��������� ��� ����� ����� ���������
bool FreePlaceForNewAttack(int row, int col, AttackCoord& PCAttack, bool& isEmpty) {
	if ((PolePl[row][col - 4] == ' ' || PolePl[row][col - 4] == 'o') && col - 4 > 7) { 
		PCAttack.row = (row - 2) / 2;
		PCAttack.col = ((col - 8) / 4) + 64; 
		isEmpty = true; 
	}	else if ((PolePl[row][col + 4] == ' ' || PolePl[row][col + 4] == 'o') && col + 4 < PolePlWidth - 4) { 
		PCAttack.row = (row - 2) / 2;
		PCAttack.col = (col / 4) + 64; 
		isEmpty = true;  
	}	else if ((PolePl[row - 2][col] == ' ' || PolePl[row - 2][col] == 'o') && row - 2 > 3) { 
		PCAttack.row = (row - 4) / 2;
		PCAttack.col = ((col - 4) / 4) + 64; 
		isEmpty = true; 
	}	else if ((PolePl[row + 2][col] == ' ' || PolePl[row + 2][col] == 'o') && row + 2 < PolePlHeight - 3) { 
		PCAttack.row = row / 2;
		PCAttack.col = ((col - 4) / 4) + 64; 
		isEmpty = true; 
	}	else { isEmpty = false; }
	return isEmpty;
}
//������� ������ ��������� ����
void PrintTable(string* pole, int i, int j) {
	if (pole == PolePl) {
	  if (pole[i][j] == 'o') { SetColor(COLOR::light_blue, COLOR::black); cout << char(178); }
	  else if (pole[i][j] == '/') { SetColor(COLOR::yellow, COLOR::blue);	cout << char(186); }
	  else if (pole[i][j] == '=') { SetColor(COLOR::yellow, COLOR::blue);	cout << char(205); }
	  else if (pole[i][j] == '-') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(205); }
	  else if (pole[i][j] == '|') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(186); }
	  else if (pole[i][j] == '+') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(206); }
	  else if (pole[i][j] == 'T') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(203); }
	  else if (pole[i][j] == 'b') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(202); }
	  else if (pole[i][j] == 'r') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(185); }
	  else if (pole[i][j] == 'l') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(204); }
	  else if (pole[i][j] == 'q') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(201); }
	  else if (pole[i][j] == 'w') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(187); }
	  else if (pole[i][j] == 'e') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(188); }
	  else if (pole[i][j] == 'd') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(200); }
	  else if (pole[i][j] == '{') {	SetColor(COLOR::yellow, COLOR::blue);	cout << char(201); }
	  else if (pole[i][j] == '}') { SetColor(COLOR::yellow, COLOR::blue);	cout << char(187); }
	  else if (pole[i][j] == '[') {	SetColor(COLOR::yellow, COLOR::blue);	cout << char(200); }
	  else if (pole[i][j] == ']') {	SetColor(COLOR::yellow, COLOR::blue);	cout << char(188); }
	  else if (pole[i][j] == '!') {	SetColor(COLOR::yellow, COLOR::blue);	cout << " "; }
	  else if (pole[i][j] == '?') {	SetColor(COLOR::black, COLOR::white);	cout << " "; }
	  else if (pole[i][j] == '#') {	SetColor(COLOR::light_blue, COLOR::blue);	cout << char(219); }
	  else if (pole[i][j] == 'x') {	SetColor(COLOR::light_blue, COLOR::light_red);	cout << char(219); }
	  else { SetColor(COLOR::light_blue, COLOR::black);	cout << pole[i][j]; }
	}
	if (pole == PolePlAttack) {
	  if (pole[i][j] == '/') { SetColor(COLOR::light_red, COLOR::blue);	cout << char(186); }
	  else if (pole[i][j] == '=') { SetColor(COLOR::light_red, COLOR::blue);	cout << char(205); }
		else if (pole[i][j] == '-') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(205); }
		else if (pole[i][j] == '|') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(186); }
		else if (pole[i][j] == '+') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(206); }
		else if (pole[i][j] == 'T') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(203); }
		else if (pole[i][j] == 'b') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(202); }
		else if (pole[i][j] == 'r') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(185); }
	  else if (pole[i][j] == 'q') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(201); }
	  else if (pole[i][j] == 'w') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(187); }
	  else if (pole[i][j] == 'e') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(188); }
	  else if (pole[i][j] == 'd') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(200); }
		else if (pole[i][j] == 'l') { SetColor(COLOR::light_blue, COLOR::blue);	cout << char(204); }
	  else if (pole[i][j] == '{') {	SetColor(COLOR::light_red, COLOR::blue);	cout << char(201); }
	  else if (pole[i][j] == '}') { SetColor(COLOR::light_red, COLOR::blue);	cout << char(187); }
	  else if (pole[i][j] == '[') {	SetColor(COLOR::light_red, COLOR::blue);	cout << char(200); }
	  else if (pole[i][j] == ']') {	SetColor(COLOR::light_red, COLOR::blue);	cout << char(188); }
	  else if (pole[i][j] == '!') {	SetColor(COLOR::light_red, COLOR::blue);	cout << " "; }
		else if (pole[i][j] == '?') { SetColor(COLOR::black, COLOR::white);	cout << " "; }
	  else if (pole[i][j] == '#') {	SetColor(COLOR::light_blue, COLOR::blue);	cout << char(219); }
	  else if (pole[i][j] == 'x') {	SetColor(COLOR::light_blue, COLOR::light_red);	cout << char(219); }
	  else { SetColor(COLOR::light_blue, COLOR::black);	cout << pole[i][j]; }
	}
}
//������� ��������� ��������� � ������� �������� ����
void CoordToRowColConversion1(AttackCoord coord, int& row, int& col1, int& col2, int& col3, int& col1_1, int& col2_2, int& col3_3) {
	row = coord.row * 2 + 2;
	col1 = (coord.col - 64) * 4 + 4;
	col2 = (coord.col - 64) * 4 + 5;
	col3 = (coord.col - 64) * 4 + 6;
	col1_1 = (coord.col - 96) * 4 + 4;
	col2_2 = (coord.col - 96) * 4 + 5;
	col3_3 = (coord.col - 96) * 4 + 6;
}
void CoordToRowColConversion2(int CoordRow, char CoordCol, int& row, int& col1, int& col2, int& col3) {
	row = CoordRow * 2 + 2;
	col1 = (CoordCol - 64) * 4 + 4;
	col2 = (CoordCol - 64) * 4 + 5;
	col3 = (CoordCol - 64) * 4 + 6;
}
//������� ������������ ������ ������
void CoordConfirm(string* pole, int row, int col1, int col2, int col3, char sym) {
	pole[row][col1] = sym;
	pole[row][col2] = sym;
	pole[row][col3] = sym;
}