#include "OutPokerState.h"

#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "GameController.h"
#include "HolderPlayerInstance.h"
#include "OutPokers.h"

OutPokerState::OutPokerState(GameController* gameController_)
	: _gameController(gameController_)
{
	init();
}

void OutPokerState::init()
{
	_lastOutPokers = nullptr;	//��ʼ��Ϊnullptr����һ�������˿��Գ�������

	initContent();
}

void OutPokerState::initContent()
{
	//ע����³���˳�����Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(OutPokerState::updateOutOrderCallback, this),
		UPDATE_OUT_ORDER,
		nullptr);

	//ע�������һ���Ƶ���Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(OutPokerState::updateLastOutPokersCallback, this),
		UPDATE_LAST_OUTPOKERS,
		nullptr);
}

void OutPokerState::handle()
{
	_players.clear();
	_players.push_back(HolderPlayerInstance::getInstance());
	_players.push_back(ComputerPlayerInstanceOne::getInstance());
	_players.push_back(ComputerPlayerInstanceTwo::getInstance());

	//ȷ��_startIndex
	for (int i = 0; i < _players.size(); ++i)
	{
		if (_players.at(i)->getPlayerType() == Player::LANDLORD)
		{
			_startIndex = i;
			break;
		}
	}

	_curOutPlayerIndex = _startIndex;

	//��ʱ���ֶ���ҳ��е��ƿ��Ե��
	HolderPlayerInstance::getInstance()->setPokersCanClick(true);

	_players.at(_curOutPlayerIndex)->outPokers(_lastOutPokers);

	//cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_HOLDER_OUTPOKERS, nullptr);
}

void OutPokerState::update()
{
	//������Ϸ״̬Ϊ��һ��״̬������״̬
	this->_gameController->setState(_gameController->getOverState());

	//������һ��״̬
	this->_gameController->runState();
}

void OutPokerState::updateOutOrderCallback(cocos2d::Ref*)
{
	//����Ѿ�����ҳ����ƣ�ת�����״̬
	if (_players.at(_curOutPlayerIndex)->isWinner())
	{
		//�ӳ����룬���и�״̬��������ز���
		auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
		scheduleVar->schedule(schedule_selector(OutPokerState::over), this, 2.0, false);
		return;
	}

	_curOutPlayerIndex = (_curOutPlayerIndex + 1) % _players.size();

	_players.at(_curOutPlayerIndex)->outPokers(_lastOutPokers);
}

void OutPokerState::updateLastOutPokersCallback(cocos2d::Ref* sender_)
{
	if (sender_ == nullptr)
	{
		return;
	}
	//������һ����
	auto tmp = reinterpret_cast<OutPokers*>(sender_);
	_lastOutPokers = tmp;
}

void OutPokerState::over(float delta_)
{
	//��ִ��һ��over�������Ҫunschedule
	auto scheduleVar = cocos2d::Director::getInstance()->getScheduler();
	scheduleVar->unschedule(schedule_selector(OutPokerState::over), this);

	//�����˿˲�
	cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_POKER_LAYER, nullptr);
	//����ͷ���
	cocos2d::NotificationCenter::getInstance()->postNotification(DESTROY_HEADIMAGE_LAYER, nullptr);

	//����״̬
	update();
}
