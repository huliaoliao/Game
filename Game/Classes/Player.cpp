#include "Player.h"

#include "Util.h"

void Player::setPokers(const std::vector<Poker>& pokers_)
{
	//¶ÔÅÆÅÅÐò
	auto pokers = pokers_;
	util::PokerUtil::sort(pokers);

	this->_holdPokers = pokers;
}

void Player::pushPoker(const Poker& poker_)
{
	_holdPokers.push_back(poker_);
	util::PokerUtil::sort(_holdPokers);
}

int Player::getCallScore() const
{
	return _callScore;
}

void Player::setCallScore(int score_)
{
	this->_callScore = score_;
}