#include "ComputerPlayer.h"

void ComputerPlayer::callLandlord()
{
	//��������з�
	int score = rand() % 4;	//���У�һ�֣����֣�����

	setCallScore(score);

	//�зֺ�����Ϣ���½з�˳��
	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_CALL_LANDLORD_INDEX, nullptr);
}

void ComputerPlayer::outPokers(const OutPokers* outPokers_)
{

}

