#include "OutPokerState.h"

#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
#include "GameController.h"
#include "HolderPlayerInstance.h"

OutPokerState::OutPokerState(GameController* gameController_)
	: _gameController(gameController_)
{
}

void OutPokerState::init()
{
}

void OutPokerState::handle()
{
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

	//��ʱ���ֶ���ҳ��е��ƿ��Ե��
	HolderPlayerInstance::getInstance()->setPokersCanClick(true);

	//cocos2d::NotificationCenter::getInstance()->postNotification(DISPLAY_HOLDER_OUTPOKERS, nullptr);
}

void OutPokerState::update()
{

}