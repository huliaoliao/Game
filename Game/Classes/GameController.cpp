#include "GameController.h"

#include "Common.h"
#include "DealState.h"
#include "GameScene.h"
#include "ReadyState.h"
#include "StartState.h"

GameController::GameController()
{
	this->_startState = new StartState(this);
	this->_readyState = new ReadyState(this);
	this->_dealState = new DealState(this);

	this->_state = _startState;	//初始化状态为开始状态
}

bool GameController::initContent()
{

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

State* GameController::getReadyState() const
{
	return _readyState;
}

State* GameController::getDealState() const
{
	return _dealState;
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
	//该行执行后，runningScene并不会立即切换，需要等到下一帧
	cocos2d::Director::getInstance()->replaceScene(GameScene::createScene());

	//这完全是解决上述问题的无法做法
	auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
	scheduleVar->schedule(schedule_selector(GameController::update), this, 0.0, false);
}

void GameController::run()
{
	_state->handle();
}

void GameController::updateCallback(cocos2d::Ref*)
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

	this->run();
}
