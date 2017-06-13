#ifndef					__COUNT_DOWN_CONTROLLER_H__
#define					__COUNT_DOWN_CONTROLLER_H__

/*	��ʱ������	---	2017.6.13
*/

#include "cocos2d.h"
#include "Singleton.h"

class Player;

class CountDownController : public Singleton<CountDownController>
{
public:
	CountDownController() = default;

public:
	//��ʼ��ʱ
	void startCountDown(Player* player_);

	//ֹͣ��ʱ
	void stopCountDown(Player* player_);
};

#endif