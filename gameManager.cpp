#include "pch.h"
#include "gameManager.h"

void gameManager::SetInGame(bool _inGame) { inGame = _inGame; }
bool gameManager::InGame() { return inGame; }

void gameManager::SetGameMode(int m) { gameMode = m; }
int gameManager::GetGameMode() { return gameMode; }

void gameManager::SetSizeUp() { n++; }
void gameManager::SetSizeDown() { n--; }
int gameManager::GetSize() { return n; }

void gameManager::SetDiff(int d) { difficulty = d; }
int gameManager::GetDiff() { return difficulty; }

void gameManager::initBrds()
{
	int nBrd = 0;
	if (gameMode == _1P)	//1P
		nBrd = 1;
	else if (gameMode == _2P || gameMode == VSCOMPUTER)	//2P 또는 vs.computer 모드
		nBrd = 2;
	else if(gameMode == SIMULATION)//simulation
		nBrd = 100;	

	brds = new board[nBrd];
	for (int i = 0; i < nBrd; i++)
		brds[i].init(n);
}