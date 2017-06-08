#ifndef					__START_STATE_H__
#define					__START_STATE_H__

/*	������Ϸ����״̬����ʼ��
*/

#include "State.h"

class GameController;

class StartState : public State
{
public:
	StartState(GameController* gameController_);

public:
	virtual void handle() override;

	virtual void update() override;

private:
	GameController* _gameController;
};

#endif