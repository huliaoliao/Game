#include "StartState.h"

#include "Common.h"
#include "GameController.h"

StartState::StartState(GameController* gameController_)
	: _gameController(gameController_)
{
}

void StartState::handle()
{
	//��ʾͷ���
	cocos2d::NotificationCenter::getInstance()
		->postNotification(CREATE_HEADIMAGE_LAYER);

	//��ʾͷ����������ʾ׼��״̬
	this->update();
}

void StartState::update()
{
	//��������һ��״̬��׼��״̬
	_gameController->setState(_gameController->getReadyState());

	//������һ��״̬
	_gameController->runState();
}

