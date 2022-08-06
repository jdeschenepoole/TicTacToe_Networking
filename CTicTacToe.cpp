#include "CTicTacToe.h"

CTicTacToe::CTicTacToe()
{
	this->P1 = new CPlayer();
	this->P2 = new CPlayer();

	P1->setName("Player 1");
	P2->setName("Player 2");

	whoseTurn = 1;
}

CTicTacToe::CTicTacToe(char* NP1, char* NP2)
{
	this->P1 = new CPlayer();
	this->P2 = new CPlayer();

	P1->setName(NP1);
	P2->setName(NP2);

	whoseTurn = 1;
}

CTicTacToe::~CTicTacToe()
{

}

//Creates the board
void CTicTacToe::CreateBoard()
{
	this->board[0] = *"1";
	this->board[1] = *"|";
	this->board[2] = *"2";
	this->board[3] = *"|";
	this->board[4] = *"3";
	this->board[5] = *"4";
	this->board[6] = *"|";
	this->board[7] = *"5";
	this->board[8] = *"|";
	this->board[9] = *"6";
	this->board[10] = *"7";
	this->board[11] = *"|";
	this->board[12] = *"8";
	this->board[13] = *"|";
	this->board[14] = *"9";
}


// Should pass the char array back fpr screen printing
char* CTicTacToe::DisplayBoard()
{
	char b;
	b = board[0] + board[1] + board[2] + board[3] + board[4] + "\n" 
		+ board[5] + board[6] + board[7] + board[8] + board[9] + "\n" 
		+ board[10] + board[11] + board[12] + board[12] + board[14] + "\n" ;
	return &b;
}

bool CTicTacToe::XorOCheck(char XorO)
{
	if (XorO = 'X')
	{
		return true;
	}
	else if (XorO = 'O')
	{
		return true;
	}
	return false;
}

// Finds and paces the char
bool CTicTacToe::FindAndPlace(int space, char XorO)
{
	if ((space == 1) && ((board[0] != 'X') || (board[0] != 'O')))
	{
		board[0] = XorO; 
		return true;
	}
	else if ((space == 2) && ((board[2] != 'X') || (board[2] != 'O')))
	{
		board[2] = XorO;
		return true;
	}
	else if ((space == 3) && ((board[4] != 'X') || (board[4] != 'O')))
	{
		board[4] = XorO;
		return true;
	}
	else if ((space == 4) && ((board[5] != 'X') || (board[5] != 'O')))
	{
		board[5] = XorO;
		return true;
	}
	else if ((space == 5) && ((board[7] != 'X') || (board[7] != 'O')))
	{
		board[7] = XorO;
		return true;
	}
	else if ((space == 6)  && ((board[9] != 'X') || (board[9] != 'O')))
	{
		board[9] = XorO;
		return true;
	}
	else if ((space == 7)  && ((board[10] != 'X') || (board[10] != 'O')))
	{
		board[10] = XorO;
		return true;
	}
	else if ((space == 8)  && ((board[12] != 'X') || (board[12] != 'O')))
	{
		board[12] = XorO;
		return true;
	}
	else if ((space == 9)  && ((board[14] != 'X') || (board[14] != 'O')))
	{
		board[14] = XorO;
		return true;
	}
	return false;
}

// Places the char if all is good
bool CTicTacToe::Place(int player, int space, char XorO)
{
	bool b = false;
	if ((player == 1) && (whoseTurn == 1))
	{
		if (this->XorOCheck(XorO))
		{
			b = this->FindAndPlace(space, XorO);
		}
	}
	else if ((player = 2) && (whoseTurn == 2))
	{
		if (this->XorOCheck(XorO))
		{
			b = this->FindAndPlace(space, XorO);
		}
	}
	return b;
}

// ends the tunr
void CTicTacToe::EndTurn()
{
	if (whoseTurn == 1)
		whoseTurn = 2;
	else
		whoseTurn = 1;
}

bool CTicTacToe::CheckWinConditions(char XorO)
{
	if((board[0] == XorO) && (board[2] == XorO) && (board[4] ==XorO))
	{
		return true;
	}
	else if((board[5] == XorO) && (board[7] == XorO) && (board[9] ==XorO))
	{
		return true;
	}
	else if((board[10] == XorO) && (board[12] == XorO) && (board[14] ==XorO))
	{
		return true;
	}
	else if((board[0] == XorO) && (board[5] == XorO) && (board[10] ==XorO))
	{
		return true;
	}
	else if((board[2] == XorO) && (board[7] == XorO) && (board[12] ==XorO))
	{
		return true;
	}
	else if((board[4] == XorO) && (board[9] == XorO) && (board[14] ==XorO))
	{
		return true;
	}
	else if((board[0] == XorO) && (board[7] == XorO) && (board[14] ==XorO))
	{
		return true;
	}
	else if((board[4] == XorO) && (board[7] == XorO) && (board[10] ==XorO))
	{
		return true;
	}

	return false;
}

void CTicTacToe::ParseData(char* str)
{
	std::stringstream ss;
	std::string s;
	ss << str;
	ss >> s;

	std::string fWord;
	int break1 = int(s.find(' '));
	fWord = s.substr(0, break1);

	bool good = false;

	if (s.length() > 0)
	{
		if(fWord == "Place")
		{
			char space = *s.substr(break1,break1+1).c_str();

			
			if (whoseTurn == 1)
				good = Place(whoseTurn, (int)space, 'X');

			else
				good = Place(whoseTurn, (int)space, 'O');
		}
	}

	if (good == false)
	{

	}
}