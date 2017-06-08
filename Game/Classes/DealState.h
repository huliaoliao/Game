#ifndef					__DEAL_STATE_H__
#define					__DEAL_STATE_H__

/*	·¢ÅÆ×´Ì¬	---	2017.6.8
*/

#include "State.h"

class GameController;

class DealState : public State
{
public:
	DealState(GameController* gameController_);

public:
	virtual void handle();

	virtual void update();

protected:
	void updateStateCallback(cocos2d::Ref*);

private:
	GameController* _gameController;
};

#endif