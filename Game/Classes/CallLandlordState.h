#ifndef					__CALL_LANDLORD_STATE_H__
#define					__CALL_LANDLORD_STATE_H__

/*	叫地主状态	---	2017.6.9
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

	void callLandlord();

	//更新头像
	void updateHeadImage(int landlordIndex_);

	//设置地主
	void setLandlord(int _index);

	//对所有人的分数进行判断，决定地主
	void dicideLandlord();

private:
	void updateCallIndexCallback(cocos2d::Ref*);

private:
	GameController* _gameController;

	cocos2d::Vector<Player*> _players;

	int	_curCallIndex;
	int	_calledNum;
	const int _maxScore;
};

#endif