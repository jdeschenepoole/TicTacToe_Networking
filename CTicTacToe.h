#ifndef _HG_TicTacToe_
#define _HG_TicTacToe_

#include <sstream>
#include <string>
#include "CPlayer.h"

class CTicTacToe
{
public:
	CTicTacToe();
	CTicTacToe(char* NP1, char* NP2);
	~CTicTacToe();
	void CreateBoard();
	char* DisplayBoard();
	bool Place(int player, int space, char XorO);
	void EndTurn();
	void ParseData(char* str);
private:
	bool XorOCheck(char XorO);
	bool FindAndPlace(int space, char XorO);
	bool CheckWinConditions(char XorO);
	char board[15];
	int whoseTurn;
	CPlayer* P1;
	CPlayer* P2;
};


#endif