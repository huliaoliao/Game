#include "Player.h"

#include "GameRule.h"
#include "OutPokers.h"
#include "PokerSetType.h"
#include "Util.h"

void Player::setPokers(const std::vector<Poker>& pokers_)
{
	//��������
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

bool Player::isWinner() const
{
	return _holdPokers.empty();
}

std::vector<Poker> Player::searchOutPokers(OutPokers* lastOutPokers_)
{
	std::vector<Poker> result;

	//�����һ�������Լ���
	if (lastOutPokers_ == nullptr || lastOutPokers_->getPokerOwner() == this ||
		lastOutPokers_->getPokersType() == NONE)
	{
		result = GameRule::getInstance()->searchProperPokers(_holdPokers);
	}
	else if (lastOutPokers_->getPokersType() != KINGBOMB)
	{
		//static Poker poker = lastOutPokers_->getLowestPoker();	//����д�ᵼ�¸�ֵ������ִ��һ�Σ��������BUG
		static Poker poker;
		poker = lastOutPokers_->getLowestPoker();
		result = GameRule::getInstance()->calcPokersWithType(
			_holdPokers, lastOutPokers_->getPokersType(), &poker,//lastOutPokers_->getLowestPoker(),
			lastOutPokers_->getTotalLen());

		if (result.size() == 0) //����Ҳ�����Ӧ���ƣ�����ը��
		{
			result = GameRule::getInstance()->calcPokersWithType(_holdPokers, BOMB, &poker);// lastOutPokers_->getLowestPoker());
			if (result.size() == 0)//����Ҳ�����ͨ��ը��������ը
			{
				result = GameRule::getInstance()->calcPokersWithType(_holdPokers, KINGBOMB);
			}
		}
	}

	return result;
}

OutPokers* Player::createLastOutPokers(const std::vector<Poker>& pokers_)
{
	auto pokersType = GameRule::getInstance()->analysePokersType(pokers_);
	auto lowestPoker = GameRule::getInstance()->getLowestPoker(pokers_, pokersType);
	int pokersLen = GameRule::getInstance()->filterAccessoryPokers(pokers_).size();
	auto lastOutPokers = new OutPokers(this, lowestPoker, pokersLen, pokersType);
	//lastOutPokers->retain();
	return lastOutPokers;
}