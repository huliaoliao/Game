#ifndef					__OUT_POKER_STATE_H__
#define					__OUT_POKER_STATE_H__

/* ����״̬	---	2017.6.10
*/

#include "State.h"

class CountDownController;
class GameController;
class OutPokers;
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

	void initContent();

	void over(float delta_);

private:
	//���³���˳��
	void updateOutOrderCallback(cocos2d::Ref*);

	//������һ���ƻص��������ⲿ�޸���һ����
	void updateLastOutPokersCallback(cocos2d::Ref* sender_);

private:
	GameController*			_gameController;
	std::vector<Player*>		_players;
	int								_startIndex;			//��ʼ���Ƶ�����±�
	int								_curOutPlayerIndex;	//��ǰ���Ƶ�����±�
	OutPokers*					_lastOutPokers;		//��ҵ�ǰ���ƣ����ڸ���һ����Ҿ������ƣ���ʼ������Ϊnullptr
	const int HOLDER_PLAYER_INDEX = 0;		//�ֶ�����������������±�
};

#endif