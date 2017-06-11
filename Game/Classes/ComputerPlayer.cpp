#include "ComputerPlayer.h"

#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"

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
	//���ȣ�����һ�ѳ����ƴӳ���ɾ��
	//���жϵ��������1����2
	//����ǵ������1
	if (this == ComputerPlayerInstanceOne::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_LAST_COMPUTER_ONE_OUTPOKERS,
			nullptr);

	}
}

