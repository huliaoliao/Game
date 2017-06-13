#include "ComputerPlayer.h"

#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "CountDownController.h"

void ComputerPlayer::callLandlord()
{
	//��������з�
	int score = rand() % 4;	//���У�һ�֣����֣�����

	setCallScore(score);

	//�зֺ�����Ϣ���½з�˳��
	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_CALL_LANDLORD_INDEX, nullptr);
}

void ComputerPlayer::outPokers(OutPokers* lastOutPokers_)
{
	//���ȣ�����һ�ѳ����ƴӳ���ɾ��
	//���жϵ��������1����2
	//����ǵ������1
	if (this == ComputerPlayerInstanceOne::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_LAST_COMPUTER_ONE_OUTPOKERS,
			nullptr);
	}
	else if (this == ComputerPlayerInstanceTwo::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_LAST_COMPUTER_TWO_OUTPOKERS,
			nullptr);
	}

	//������Ϸ��һ���Ʋ��ҷ���Ҫ�����
	_outedPokers = this->searchOutPokers(lastOutPokers_);

	//���������ҵ����Գ����ƣ���ô������һ����
	if (_outedPokers.size() != 0)
	{
		auto lastOutPokers = createLastOutPokers(_outedPokers);
		//��һ��������ô������ң���ɶ�����ȷ������
		//lastOutPokers_ = lastOutPokers;		//����򵥵ĸ�����Ϸѭ������һ����
		cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_LAST_OUTPOKERS,
			(cocos2d::Ref*)(lastOutPokers));
	}

	//����������Ϣ���ݵĴ�����ƣ���һ����ҵ���һ���ƣ�
// 	_outedPokersForPost.clear();
// 	for (int i = 0; i < _outedPokers.size(); ++i)
// 	{
// 		_outedPokersForPost.pushBack(&_outedPokers.at(i));
// 	}

	//�ڳ��е�����ɾ��Ҫ������
	for (int i = 0; i < _outedPokers.size(); ++i)
	{
		for (auto iter = _holdPokers.begin(); iter != _holdPokers.end();)
		{
			if (*iter == _outedPokers[i])
			{
				iter = _holdPokers.erase(iter);
				break;
			}
			else
			{
				iter++;
			}
		}
	}

	//�����Ƴ�����
	if (_holdPokers.size() == 0)
	{
		//TODO
		return;
	}

	CountDownController::getInstance()->startCountDown(this);

// 	//��ʾҪ�������
// 	if (this == ComputerPlayerInstanceOne::getInstance())
// 	{
// 		cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_COMPUTER_ONE_OUTPOKERS,
// 			reinterpret_cast<cocos2d::Ref*>(&_outedPokers));
// 	}
// 	else if (this == ComputerPlayerInstanceTwo::getInstance())
// 	{
// 		cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_COMPUTER_TWO_OUTPOKERS,
// 			reinterpret_cast<cocos2d::Ref*>(&_outedPokers));
// 	}
// 
// 	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_OUT_ORDER, nullptr);
}

void ComputerPlayer::outPokersCallback()
{
	//��ʾҪ�������
	if (this == ComputerPlayerInstanceOne::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_COMPUTER_ONE_OUTPOKERS,
			reinterpret_cast<cocos2d::Ref*>(&_outedPokers));
	}
	else if (this == ComputerPlayerInstanceTwo::getInstance())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_COMPUTER_TWO_OUTPOKERS,
			reinterpret_cast<cocos2d::Ref*>(&_outedPokers));
	}

	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_OUT_ORDER, nullptr);
}
