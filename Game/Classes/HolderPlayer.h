#ifndef					__HOLDER_PLAYER_H__
#define					__HOLDER_PLAYER_H__

/* �ֶ����	---	2017.6.9
*/

#include "Player.h"

class HolderPlayer : public Player
{
public:
	//�ֶ������ʾ���е���
	void displayPokers();

	virtual void callLandlord();
};

#endif