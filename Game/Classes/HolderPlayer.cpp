#include "HolderPlayer.h"

#include "HolderPlayerInstance.h"

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

