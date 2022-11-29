#include <iostream>
#include <iomanip>
#include "Win10.h"
using namespace std;

void SetPos(int Row, int Col) {
  COORD cd;
  cd.X = Col;
  cd.Y = Row;
  SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), cd);
}

void SetColor(int colBkgr, int colSym) {
  int wAttributes = colBkgr * 16 + colSym;
  HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
  SetConsoleTextAttribute(hOUTPUT, wAttributes);
}

void CursorHide(BOOL bVisible, DWORD dwSize) {
  HANDLE hOUTPUT = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_CURSOR_INFO cursorInfo;
  cursorInfo.dwSize = dwSize;
  cursorInfo.bVisible = bVisible;
  SetConsoleCursorInfo(hOUTPUT, &cursorInfo);
}

void SetConsoleSize(int Width, int Height) {
  HANDLE hCon = GetStdHandle(STD_OUTPUT_HANDLE);
  CONSOLE_SCREEN_BUFFER_INFOEX sb{ sizeof(CONSOLE_SCREEN_BUFFER_INFOEX) };
  GetConsoleScreenBufferInfoEx(hCon, &sb);
  sb.dwSize.X = Width;
  sb.dwSize.Y = Height;
  sb.srWindow.Left = sb.srWindow.Top = 0;
  sb.srWindow.Right = ((Width > sb.dwMaximumWindowSize.X) ? sb.dwMaximumWindowSize.X : Width);
  sb.srWindow.Bottom = ((Height > sb.dwMaximumWindowSize.Y) ? sb.dwMaximumWindowSize.Y : Height);
  SetConsoleScreenBufferInfoEx(hCon, &sb);
}

void SetConsoleSize(SIZE szConsWin) {
  SetConsoleSize(szConsWin.cx, szConsWin.cy);
}