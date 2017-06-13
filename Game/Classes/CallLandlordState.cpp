#include "CallLandlordState.h"

#include "Common.h"
#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "GameController.h"
#include "HolderPlayerInstance.h"
#include "Player.h"

CallLandlordState::CallLandlordState(GameController* gameController_)
	: _gameController(gameController_),
	_calledNum(0), _maxScore(3)	//������Խе���߷���3
{
	srand((unsigned)time(nullptr));

	_players.push_back(HolderPlayerInstance::getInstance());
	_players.push_back(ComputerPlayerInstanceOne::getInstance());
	_players.push_back(ComputerPlayerInstanceTwo::getInstance());

	//������ſ�ʼ�е��������
	_startIndex = rand() % _players.size();
	_curCallIndex = _startIndex;

	initContent();
}

void CallLandlordState::handle()
{
	//������Ϣ�������е�����
	cocos2d::NotificationCenter::getInstance()->postNotification(
		CREATE_CALL_LANDLORD_LAYER, nullptr);

	//��ʼ�е���ѭ��
	callLandlordDelayed();
}

void CallLandlordState::update()
{
	//������Ϸ״̬Ϊ��һ��״̬������״̬
	this->_gameController->setState(_gameController->getOutPokerState());

	//������һ��״̬
	_gameController->runState();
}

bool CallLandlordState::initContent()
{
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordState::updateCallIndexCallback, this),
		UPDATE_CALL_LANDLORD_INDEX, nullptr);

	return true;
}

void CallLandlordState::callLandlordDelayed()
{
	auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
	scheduleVar->schedule(schedule_selector(CallLandlordState::callLandlordDelayed), this, 1.0, false);
}

void CallLandlordState::callLandlordDelayed(float delta_)
{
	//ÿ����ҽ�ִ��һ�Σ���unschdule
	auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
	scheduleVar->unschedule(schedule_selector(CallLandlordState::callLandlordDelayed), this);

	_players.at(_curCallIndex)->callLandlord();
}

void CallLandlordState::decideLandlord()
{
	//�ҳ��з���ߵ���
	int maxScore = 0;
	int landlordIndex = _startIndex;
	//�������ʼ��˳�����
	for (int i = 0, playerIndex = _startIndex; i < _players.size();
		++i, playerIndex = (playerIndex + 1) % _players.size())
	{
		int score = _players.at(playerIndex)->getCallScore();
		if (score > maxScore)
		{
			maxScore = score;
			landlordIndex = playerIndex;
		}
	}

	//����������ͣ�����Orũ��
	for (int i = 0; i < _players.size(); ++i)
	{
		if (i == landlordIndex)
		{
			_players.at(i)->setPlayerType(Player::LANDLORD);
		}
		else
		{
			_players.at(i)->setPlayerType(Player::FARMER);
		}
	}

	this->_landlordIndex = landlordIndex;

	//cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_CALL_LANDLORD_LAYER, nullptr);
	//��ȡ��������ߺ�Ĳ�����Ԥ���ĵ����Ʒ����û���ߣ�
	setLandlord();
}

void CallLandlordState::setLandlord()
{
	auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
	//�ӳ�2�룬�������һ���зֵ���ҵĽз�״̬�޷�����
	scheduleVar->schedule(schedule_selector(CallLandlordState::setLandlordDelayed), this, 2.0, false);
}

void CallLandlordState::setLandlordDelayed(float delta_)
{
	//��ִ��һ�Σ���unschdule
	auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
	scheduleVar->unschedule(schedule_selector(CallLandlordState::setLandlordDelayed), this);

	//����ͷ��
	updateHeadImage(_landlordIndex);

	//��Ԥ���ĵ����Ʒ������������
	auto pokers = PokerController::getInstance()->getRandomPokers();
	//std::vector<Poker> landlordPokers;
	for (int i = pokers.size() - 3; i < pokers.size(); ++i)
	{
		//landlordPokers.push_back(pokers[i]);
		_players.at(_landlordIndex)->pushPoker(pokers[i]);
	}

	//�ֶ����ˢ��һ����Ҫ��ʾ����
	HolderPlayerInstance::getInstance()->displayPokers();

	//���ٽе����㣬�������״̬
	cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_CALL_LANDLORD_LAYER);

	//������һ����Ϸ״̬
	this->update();
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
	//��ʾ��ҽз���Ϣ
	if (_curCallIndex == 1)
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			DISPLAY_COMPUTE_ONE_CALLLANDLORD_STATE, nullptr);
	}
	else if (_curCallIndex == 2)
	{
		cocos2d::NotificationCenter::getInstance()->postNotification(
			DISPLAY_COMPUTE_TWO_CALLLANDLORD_STATE, nullptr);
	}

	_calledNum++;
	if (_calledNum == _players.size())
	{
		//�зֽ���������˭�ǵ���
		decideLandlord();
		return;		//��������return����һ��������Ժܾ�...
	}
	int lastCallIndex = _curCallIndex;
	if (_players.at(lastCallIndex)->getCallScore() == _maxScore)
	{
		//�Ѿ����˽е���߷֣����ֱ�ӽзֽ��������ø���Ϊ����
		decideLandlord();
		return;
	}
	_curCallIndex = (_curCallIndex + 1) % _players.size();

	callLandlordDelayed();
}
