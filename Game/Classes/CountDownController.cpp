#include "CountDownController.h"

#include "Common.h"
#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "HolderPlayerInstance.h"
#include "Player.h"

void CountDownController::startCountDown(Player* player_)
{
	//������Ҷ����ԭ���ǣ��ȼ�ʱ����ʱ���������ͨ����Ҷ���
	//��������ƻص�����
	if (player_ == HolderPlayerInstance::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(HOLDER_START_COUNTDOWN,
			player_);
	}
	else if (player_ == ComputerPlayerInstanceOne::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(COMPUTER_ONE_START_COUNTDOWN,
			player_);
	}
	else if (player_ == ComputerPlayerInstanceTwo::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(COMPUTER_TWO_START_COUNTDOWN,
			player_);
	}
}

void CountDownController::stopCountDown(Player* player_)
{
	//����������ʱ���ֶ���ҵ�����ƻ��߲�����ť��
	//Ӧ��ֹͣ��ʱ����
	if (player_ == HolderPlayerInstance::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(HOLDER_STOP_COUNTDOWN,
			nullptr);
	}
}
