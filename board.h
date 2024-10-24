#pragma once
#include "myPreProc.h"
//#define LEFT 0x25
//#define UP 0x26
//#define RIGHT 0x27
//#define DOWN 0x28
//
//#define nEMPTY 0
//#define nSHUFFLE 300
class board
{
private:
	int size = 3;	//board size, 3, 4, 5
	int brdArraySize = 9;
	int* brd = nullptr;
	int iEmpty = 0;
	int moveCnt = 0;
	//int* solution = new int[nSHUFFLE];	//셔플 함수에서 타일의 움직임을 역순으로 저장.

public:
	void init(int n);
	void ShuffleBrd();
	void MoveTile(int _dir);
	void MoveTile2p(int _dir);
	void SwapTile(int idx1, int idx2);
	void DrawBrd(CDC* DC, int height, CPoint leftTop);
	int* GetBrd() { return brd; }
	int GetBrd(int _idx) { return brd[_idx]; }
	bool isSolve();
	//int GetSize();
};

