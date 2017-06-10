#include "HolderPlayer.h"

#include "HolderPlayerInstance.h"
#include "Util.h"

HolderPlayer::HolderPlayer()
{
	init();
}

bool HolderPlayer::init()
{
	_lastOutPokers = nullptr;

	if (initContent() == false)
	{
		return false;
	}

	return true;
}

bool HolderPlayer::initContent()
{
	//注册在手动玩家待出牌中添加牌的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HolderPlayer::addPokerWaitForOutCallback, this),
		ADD_POKER_IN_HOLDER_POKERSWAITFOROUT,
		nullptr);

	//注册在手动玩家待出牌中删除牌的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HolderPlayer::deletePokerWaitForOutCallback, this),
		DELETE_POKER_IN_HOLDER_POKERSWAITFOROUT,
		nullptr);

	return true;
}


void HolderPlayer::displayPokers()
{
	cocos2d::Vector<Poker*> pokers;
	for (int i = 0; i < _holdPokers.size(); ++i)
	{
		pokers.pushBack(&_holdPokers[i]);
	}

	cocos2d::NotificationCenter::getInstance()->postNotification(
		DISPLAY_HOLDER_POKERS, (cocos2d::Ref*)(&pokers));
}

void HolderPlayer::callLandlord()
{
	//显示叫地主按钮
	cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_CALL_LANDLORD_BTN, nullptr);
}

void HolderPlayer::outPokers(const OutPokers* outPokers_)
{

}

void HolderPlayer::deletePokerWaitForOutCallback(cocos2d::Ref* sender_)
{
	auto poker = dynamic_cast<Poker*>(sender_);
	if (poker == nullptr)
	{
		CCASSERT(poker != nullptr, "sender_ is nullptr");
		return;
	}
	for (auto iter = _pokersWaitForOut.begin(); iter != _pokersWaitForOut.end();)
	{
		bool isEqual = *iter == *poker;
		if (isEqual)
		{
			iter = _pokersWaitForOut.erase(iter);
		}
		else
		{
			++iter;
		}
	}
	//删除牌不需要重新排序
}

void HolderPlayer::addPokerWaitForOutCallback(cocos2d::Ref* sender_)
{
	auto poker = dynamic_cast<Poker*>(sender_);
	if (poker == nullptr)
	{
		CCASSERT(poker != nullptr, "sender_ is nullptr!");
		return;
	}
	_pokersWaitForOut.push_back(*poker);
	util::PokerUtil::sort(_pokersWaitForOut);
}