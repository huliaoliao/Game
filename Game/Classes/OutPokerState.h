#ifndef					__OUT_POKER_STATE_H__
#define					__OUT_POKER_STATE_H__

/* 出牌状态	---	2017.6.10
*/

#include "State.h"

class GameController;
class Player;

class OutPokerState : public State
{
public:
	OutPokerState(GameController* gameController_);

public:
	virtual void handle();

	virtual void update();

private:
	void init();

private:
	GameController*			_gameController;
	std::vector<Player*>		_players;
	int								_startIndex;			//开始出牌的玩家下标

};

#endif