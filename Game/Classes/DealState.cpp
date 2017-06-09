#include "DealState.h"

#include <vector>

#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "GameController.h"
#include "HolderPlayerInstance.h"
#include "PokerController.h"

const int TOTAL_POKER_NUM = 54;	//�˿�����

DealState::DealState(GameController* gameController_)
	: _gameController(gameController_)
{
}

void DealState::handle()
{
	//����˿˲�
	cocos2d::NotificationCenter::getInstance()->postNotification(
		CREATE_POKER_LAYER, nullptr);

	//��ȡϴ�õ���
	auto randomPokers = PokerController::getInstance()->getRandomPokers();
	//����
	dealPokers(randomPokers);
	//��ʾԤ������������
	displayLandlordPokers(randomPokers);

	//�ڳ������ֶ���ҵ��ƣ�������Ϣ���ƴ������ݣ�
	HolderPlayerInstance::getInstance()->displayPokers();

	//���͸�����Ϸ״̬��Ϣ
	cocos2d::NotificationCenter::getInstance()->postNotification(
		UPDATE_GAME_STATE, nullptr);
}

void DealState::update()
{
	//��������һ��״̬���е���״̬
	this->_gameController->setState(_gameController->getCalllLandlordState());

	//������һ��״̬
	_gameController->run();
}

void DealState::updateStateCallback(cocos2d::Ref*)
{
}

void DealState::dealPokers(const std::vector<Poker>& randomPokers_)
{
	std::vector<Poker> pokers;
	//���ֶ���ҷ���
	for (int i = 0; i < TOTAL_POKER_NUM - 3; i += 3)
	{
		pokers.push_back(randomPokers_.at(i));
	}
	HolderPlayerInstance::getInstance()->setPokers(pokers);

	//�Ե������1����
	pokers.clear();
	for (int i = 1; i < TOTAL_POKER_NUM - 3; i += 3)
	{
		pokers.push_back(randomPokers_.at(i));
	}
	ComputerPlayerInstanceOne::getInstance()->setPokers(pokers);

	//�Ե������2����
	pokers.clear();
	for (int i = 2; i < TOTAL_POKER_NUM - 3; i += 3)
	{
		pokers.push_back(randomPokers_.at(i));
	}
	ComputerPlayerInstanceTwo::getInstance()->setPokers(pokers);
}

void DealState::displayLandlordPokers(std::vector<Poker>& pokers_)
{
	//��ȡ������������
	cocos2d::Vector<Poker*> landlordPokers;
	for (int i = pokers_.size() - 3; i < pokers_.size(); ++i)
	{
		landlordPokers.pushBack(&pokers_.at(i));
	}

	cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_LANDLORD_POKERS,
		(cocos2d::Ref*)(&landlordPokers));
}

