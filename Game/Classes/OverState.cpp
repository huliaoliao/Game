#include "OverState.h"

#include "Common.h"
#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "GameController.h"
#include "HolderPlayerInstance.h"
#include "LobbyScene.h"
#include "Player.h"

OverState::OverState(GameController* gameController_)
	: _gameController(gameController_)
{
}

void OverState::handle()
{
	//����������
	cocos2d::NotificationCenter::getInstance()->postNotification(CREATE_OVER_LAYER,
		nullptr);

	//�ж�����Ƿ�ʤ��

	//�ҵ�ʤ����ҵ����ͣ�����ORũ��
	Player::Type winnerPlayerType;
	if (HolderPlayerInstance::getInstance()->isWinner())
	{
		winnerPlayerType = HolderPlayerInstance::getInstance()->getPlayerType();
	}
	else if (ComputerPlayerInstanceOne::getInstance()->isWinner())
	{
		winnerPlayerType = ComputerPlayerInstanceOne::getInstance()->getPlayerType();
	}
	else if (ComputerPlayerInstanceTwo::getInstance()->isWinner())
	{
		winnerPlayerType = ComputerPlayerInstanceTwo::getInstance()->getPlayerType();
	}

	//����ʤ��������ͺ��ֶ���������Ƿ���ͬ���������Ƿ�ʤ��
	if (winnerPlayerType == HolderPlayerInstance::getInstance()->getPlayerType())
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(RUN_WIN_ANIMATION, nullptr);
	}
	else
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(RUN_LOST_ANIMATION, nullptr);
	}
}

void OverState::update()
{
	//�ָ���Ϸ״̬����ʼ״̬
	this->_gameController->setState(_gameController->getStartState());
}

