#include "ComputerPlayer.h"

#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"

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
	//首先，将上一把出的牌从场景删除
	//先判断电脑玩家是1还是2
	//如果是电脑玩家1
	if (this == ComputerPlayerInstanceOne::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_LAST_COMPUTER_ONE_OUTPOKERS,
			nullptr);

	}
}

