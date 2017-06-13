#ifndef					__GAME_CONTROLLER_H__
#define					__GAME_CONTROLLER_H__

/* ��Ϸ������ --- 2017.6.7 
*/

#include "cocos2d.h"
#include "State.h"

class GameController : private cocos2d::Node
{
public:
	static GameController& getIns();

	static GameController* getInstance();

public:
	State* getStartState() const;

	State* getReadyState() const;

	State* getDealState() const;

	State* getCalllLandlordState() const;

	State* getOutPokerState() const;

	State* getOverState() const;

public:
	void setState(State* state_);

	void start();	//��ʼ��Ϸ״̬����

	void runState();		//���е�ǰ״̬

	void updateState();	//�л�����һ��״̬

private:
	GameController();

private:
	bool initContent();

	void update(float delta_);

private:
	void updateStateCallback(cocos2d::Ref*);	//�л�����һ��״̬�ص�

private:
	State*				_state;

	State*				_startState;			//��ʼ״̬
	State*				_readyState;			//׼��״̬
	State*				_dealState;			//����״̬
	State*				_callLandlordState;//�е���״̬
	State*				_outPokerState;		//����״̬
	State*				_overState;			//����״̬
};

#endif