#ifndef					__COMPUTER_PLAYER_H__
#define					__COMPUTER_PLAYER_H__

/*	µçÄÔÍæ¼Ò	--- 2017.6.9
*/

#include "Player.h"

class ComputerPlayer : public Player
{
public:
	virtual void callLandlord();

	virtual void outPokers(const OutPokers* outPokers_);
};

#endif