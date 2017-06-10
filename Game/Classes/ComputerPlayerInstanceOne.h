#ifndef					__COMPUTER_PLAYER_INSTANCE_ONE_H__
#define					__COMPUTER_PLAYER_INSTANCE_ONE_H__

/*	�������ʵ��1	---	2017.6.9
*/

#include "ComputerPlayer.h"
#include "Singleton.h"

class ComputerPlayerInstanceOne : private Singleton<ComputerPlayerInstanceOne>
{
public:
	static ComputerPlayer* getInstance();

private:
	static ComputerPlayer _computerPlayer;
};

#endif