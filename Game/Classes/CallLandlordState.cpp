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

	_players.pushBack(HolderPlayerInstance::getInstance());
	_players.pushBack(ComputerPlayerInstanceOne::getInstance());
	_players.pushBack(ComputerPlayerInstanceTwo::getInstance());

	//������ſ�ʼ�е��������
	_curCallIndex = rand() % _players.size();

	initContent();
}

void CallLandlordState::handle()
{
	//������Ϣ�������е�����
	cocos2d::NotificationCenter::getInstance()->postNotification(
		CREATE_CALL_LANDLORD_LAYER, nullptr);

	//��ʼ�е���ѭ��
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
	//�ҳ��з���ߵ���
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
	//��ȡ��������ߺ�Ĳ�����Ԥ���ĵ����Ʒ����û���ߣ�
	setLandlord(landlordIndex);
}

void CallLandlordState::setLandlord(int _index)
{
	//����ͷ��
	updateHeadImage(_index);

	//��Ԥ���ĵ����Ʒ������������
	auto pokers = PokerController::getInstance()->getRandomPokers();
	//std::vector<Poker> landlordPokers;
	for (int i = pokers.size() - 3; i < pokers.size(); ++i)
	{
		//landlordPokers.push_back(pokers[i]);
		_players.at(_index)->pushPoker(pokers[i]);
	}

	//�ֶ����ˢ��һ����Ҫ��ʾ����
	HolderPlayerInstance::getInstance()->displayPokers();

	//���ٽе����㣬�������״̬
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
		//�зֽ���������˭�ǵ���
		dicideLandlord();
		return;		//��������return����һ��������Ժܾ�...
	}
	int lastCallIndex = _curCallIndex;
	if (_players.at(lastCallIndex)->getCallScore() == _maxScore)
	{
		//�Ѿ����˽е���߷֣����ֱ�ӽзֽ��������ø���Ϊ����
		setLandlord(lastCallIndex);
		return;
	}
	_curCallIndex = (_curCallIndex + 1) % _players.size();
	callLandlord();
}
