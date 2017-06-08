#include "ReadyState.h"

#include "Common.h"
#include "DealState.h"
#include "GameController.h"
#include "ReadyStateLayer.h"

ReadyState::ReadyState(GameController* gameController_)
	: _gameController(gameController_)
{
}

void ReadyState::handle()
{
	//��ʾͷ���
	cocos2d::NotificationCenter::getInstance()
		->postNotification(CREATE_READY_LAYER);
}

void ReadyState::update()
{
	//��������һ��״̬������״̬
	this->_gameController->setState(_gameController->getDealState());
}
