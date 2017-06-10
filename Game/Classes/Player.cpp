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

Player::Type Player::getPlayerType() const
{
	return _type;
}

void Player::setPlayerType(Type type_)
{
	this->_type = type_;
}

void Player::setPokersCanClick(bool canClick_)
{
	for (int i = 0; i < _holdPokers.size(); ++i)
	{
		auto pokerSprite = PokerController::getInstance()->genPokerSprite(_holdPokers.at(i));
		pokerSprite->setCanClick(canClick_);
	}
}
