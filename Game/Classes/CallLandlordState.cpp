#include "CallLandlordState.h"

#include "Common.h"
#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "GameController.h"
#include "HolderPlayerInstance.h"
#include "Player.h"

CallLandlordState::CallLandlordState(GameController* gameController_)
	: _gameController(gameController_),
	_calledNum(0), _maxScore(3)	//这里可以叫的最高分是3
{
	srand((unsigned)time(nullptr));

	_players.pushBack(HolderPlayerInstance::getInstance());
	_players.pushBack(ComputerPlayerInstanceOne::getInstance());
	_players.pushBack(ComputerPlayerInstanceTwo::getInstance());

	//随机随着开始叫地主的玩家
	_curCallIndex = rand() % _players.size();

	initContent();
}

void CallLandlordState::handle()
{
	//发送消息，创建叫地主层
	cocos2d::NotificationCenter::getInstance()->postNotification(
		CREATE_CALL_LANDLORD_LAYER, nullptr);

	//开始叫地主循环
	callLandlord();
}

void CallLandlordState::update()
{

}

bool CallLandlordState::initContent()
{
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordState::updateCallIndexCallback, this),
		UPDATE_CALL_LANDLORD_INDEX, nullptr);

	return true;
}

void CallLandlordState::callLandlord()
{
	_players.at(_curCallIndex)->callLandlord();
}

void CallLandlordState::dicideLandlord()
{
	//找出叫分最高的人
	int maxScore = 0;
	int landlordIndex = 0;
	for (int i = 0; i < _players.size(); ++i)
	{
		int score = _players.at(i)->getCallScore();
		if (score > maxScore)
		{
			maxScore = score;
			landlordIndex = i;
		}
	}
	//cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_CALL_LANDLORD_LAYER, nullptr);
	//获取地主获得者后的操作（预留的地主牌发给该获得者）
	setLandlord(landlordIndex);
}

void CallLandlordState::setLandlord(int _index)
{
	//更新头像
	updateHeadImage(_index);

	//将预留的地主牌发给地主获得者
	auto pokers = PokerController::getInstance()->getRandomPokers();
	//std::vector<Poker> landlordPokers;
	for (int i = pokers.size() - 3; i < pokers.size(); ++i)
	{
		//landlordPokers.push_back(pokers[i]);
		_players.at(_index)->pushPoker(pokers[i]);
	}

	//手动玩家刷新一次需要显示的牌
	HolderPlayerInstance::getInstance()->displayPokers();

	//销毁叫地主层，进入出牌状态
	cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_CALL_LANDLORD_LAYER);
}

void CallLandlordState::updateHeadImage(int landlordIndex_)
{
	if (landlordIndex_ == 0)
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_HOLDER_HEADIMAGE, nullptr);
	}
	else if (landlordIndex_ == 1)
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_COMPUTERONE_HEADIMAHE, nullptr);
	}
	else if (landlordIndex_ == 2)
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_COMPUTERTWO_HEADIMAGE, nullptr);
	}
}

void CallLandlordState::updateCallIndexCallback(cocos2d::Ref*)
{
	_calledNum++;
	if (_calledNum == _players.size())
	{
		//叫分结束，决定谁是地主
		dicideLandlord();
		return;		//上下两个return导致一个错误调试很久...
	}
	int lastCallIndex = _curCallIndex;
	if (_players.at(lastCallIndex)->getCallScore() == _maxScore)
	{
		//已经有人叫到最高分，因此直接叫分结束，设置该人为地主
		setLandlord(lastCallIndex);
		return;
	}
	_curCallIndex = (_curCallIndex + 1) % _players.size();
	callLandlord();
}
