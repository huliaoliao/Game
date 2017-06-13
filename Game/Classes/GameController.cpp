#include "GameController.h"

#include "Common.h"
#include "CallLandlordState.h"
#include "DealState.h"
#include "GameScene.h"
#include "OutPokerState.h"
#include "OverState.h"
#include "ReadyState.h"
#include "StartState.h"

GameController::GameController()
{
	this->_startState = new StartState(this);
	this->_readyState = new ReadyState(this);
	this->_dealState = new DealState(this);
	this->_callLandlordState = new CallLandlordState(this);
	this->_outPokerState = new OutPokerState(this);
	this->_overState = new OverState(this);

	this->_state = _startState;	//��ʼ��״̬Ϊ��ʼ״̬

	initContent();
}

bool GameController::initContent()
{
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(GameController::updateStateCallback, this),
		UPDATE_GAME_STATE,
		nullptr);

	return true;
}

GameController& GameController::getIns()
{
	static GameController ins;
	return ins;
}

GameController* GameController::getInstance()
{
	return &getIns();
}

State* GameController::getStartState() const
{
	return _startState;
}

State* GameController::getReadyState() const
{
	return _readyState;
}

State* GameController::getDealState() const
{
	return _dealState;
}

State* GameController::getCalllLandlordState() const
{
	return _callLandlordState;
}

State* GameController::getOutPokerState() const
{
	return _outPokerState;
}

State* GameController::getOverState() const
{
	return _overState;
}

void GameController::setState(State* state_)
{
	this->_state = state_;
}

void GameController::updateState()
{
	this->_state->update();
}

void GameController::start()
{
	//����ִ�к�runningScene�����������л�����Ҫ�ȵ���һ֡
	cocos2d::Director::getInstance()->replaceScene(GameScene::createScene());

	//����ȫ�ǽ������������޷�����
	auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
	scheduleVar->schedule(schedule_selector(GameController::update), this, 1.0, false);
}

void GameController::runState()
{
	_state->handle();
}

void GameController::updateStateCallback(cocos2d::Ref*)
{
	_state->update();
}

void GameController::update(float delta_)
{
	if (_state == _startState)
	{
		auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
		scheduleVar->unschedule(schedule_selector(GameController::update), this);
	}

	this->runState();
}