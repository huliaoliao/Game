#ifndef					__HOLDER_PLAYER_H__
#define					__HOLDER_PLAYER_H__

/* 手动玩家	---	2017.6.9
*/

#include "Player.h"

class HolderPlayer : public Player
{
public:
	//手动玩家显示手中的牌
	void displayPokers();

	virtual void callLandlord();
};

#endif