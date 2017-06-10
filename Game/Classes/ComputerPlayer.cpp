#include "ComputerPlayer.h"

void ComputerPlayer::callLandlord()
{
	//电脑随机叫分
	int score = rand() % 4;	//不叫，一分，两分，三分

	setCallScore(score);

	//叫分后发送消息更新叫分顺序
	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_CALL_LANDLORD_INDEX, nullptr);
}

void ComputerPlayer::outPokers(const OutPokers* outPokers_)
{

}

