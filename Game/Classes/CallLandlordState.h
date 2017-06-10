#ifndef					__CALL_LANDLORD_STATE_H__
#define					__CALL_LANDLORD_STATE_H__

/*	�е���״̬	---	2017.6.9
*/

#include "State.h"

class GameController;
class Player;

class CallLandlordState : public State
{
public:
	CallLandlordState(GameController* gameController_);

public:
	virtual void handle() override;

	virtual void update() override;

private:
	bool initContent();

	void callLandlordDelayed();

	void callLandlordDelayed(float delta_);

	//����ͷ��
	void updateHeadImage(int landlordIndex_);

	//���õ���
	void setLandlord();

	void setLandlordDelayed(float delta_);

	//�������˵ķ��������жϣ���������
	void decideLandlord();

private:
	void updateCallIndexCallback(cocos2d::Ref*);

private:
	GameController* _gameController;

	cocos2d::Vector<Player*> _players;

	int	_startIndex;
	int	_curCallIndex;
	int	_calledNum;
	int	_landlordIndex;
	const int _maxScore;
};

#endif