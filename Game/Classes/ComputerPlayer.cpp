#include "ComputerPlayer.h"

void ComputerPlayer::callLandlord()
{
	//��������з�
	int score = rand() % 3;

	setCallScore(score);

	//�зֺ�����Ϣ���½з�˳��
	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_CALL_LANDLORD_INDEX, nullptr);
}

