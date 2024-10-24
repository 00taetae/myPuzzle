#pragma once
#include "board.h"
#include "myPreProc.h"

//#define _1P 0
//#define _2P 1
//#define VSCOMPUTER 2
//#define SIMULATION 3
//
//#define EASY 10
//#define NORM 11
//#define HARD 12

class gameManager
{
private:
	bool inGame = false;
	int gameMode = _1P;	//1p, 2p, vs.computer, simualtion
	int n = 3;	//3*3, 4*4, 5*5;
	int difficulty = EASY;//vs. computer mode difficulty

public:
	void SetInGame(bool _inGame);
	void SetGameMode(int m);
	void SetSizeUp();
	void SetSizeDown();
	void SetDiff(int d);
	bool InGame();
	int GetGameMode();
	int GetSize();
	int GetDiff();

	board* brds;
	void initBrds();
	
};

