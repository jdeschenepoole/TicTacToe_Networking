#ifndef _HG_CPlayer_
#define _HG_CPlayer_

class CPlayer
{
public:
	CPlayer();
	~CPlayer();

	void setName(char* name);
	char* getName();

	int getWins();
	int getLoses();
	int getTied();
	int getTotalNumberPlayed();

	void WonGame();
	void LostGame();
	void PlayedGame();
private:
	char* m_name;
	int m_wins;
	int m_loses;
	int m_totalNumberOfGames;
};

#endif