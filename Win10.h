#pragma once
#include <Windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <conio.h>
#include <io.h>

#define SETLOCAL_RU system( "chcp 1251 > nul" )
#define SETLOCAL_EN system( "chcp 866 > nul" )
#define CLS         system( "cls" )
#define PAUSE       system( "pause > nul" )

#define RAND(min,max)  (rand()%((max)-(min)+1)+(min))

void SetPos(int Row, int Col);
void SetColor(int colBkgr, int colSym);
void CursorHide(BOOL bVisible = FALSE, DWORD dwSize = 10);
void StartGame(int Rounds);
void Settings(int& cntRound);
void Rules();
void PrintFrame();
void AboutAuthor();

enum COLOR {
	black,
	blue,
	green,
	aqua,
	red,
	purple,
	yellow,
	white,
	gray,
	light_blue,
	light_green,
	light_aqua,
	light_red,
	light_purple,
	light_yellow,
	bright_white
};

enum _KEY {
	ESC = 27,
	ENTER = 13,
	SPACE = 32,
	UP = 72, DOWN = 80, LEFT = 75, RIGHT = 77
};

void SetConsoleSize(int Width, int Height);
void SetConsoleSize(SIZE szConsWin);