#include "CPlayer.h"

CPlayer::CPlayer()
{

}

CPlayer::~CPlayer()
{

}

void CPlayer::setName(char* name)
{
	this->m_name = name;
}

char* CPlayer::getName()
{
	return this->m_name;
}

int CPlayer::getLoses()
{
	return this->m_loses;
}

int CPlayer::getTied()
{
	return this->m_totalNumberOfGames - (this->m_loses + this->m_wins);
}

int CPlayer::getTotalNumberPlayed()
{
	return this->m_totalNumberOfGames;
}

int CPlayer::getWins()
{
	return this->m_wins;
}

void CPlayer::LostGame()
{
	this->m_loses++;
}

void CPlayer::PlayedGame()
{
	this->m_totalNumberOfGames++;
}

void CPlayer::WonGame()
{
	this->m_wins++;
}