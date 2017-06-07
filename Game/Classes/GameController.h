#ifndef					__GAME_CONTROLLER_H__
#define					__GAME_CONTROLLER_H__

/* ÓÎÏ·¿ØÖÆÆ÷ --- 2017.6.7 
*/

#include "cocos2d.h"

class GameController : public cocos2d::Ref
{
public:
	static GameController& getIns();

	static GameController* getInstance();
};

#endif