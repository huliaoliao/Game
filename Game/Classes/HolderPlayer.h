#ifndef					__HOLDER_PLAYER_H__
#define					__HOLDER_PLAYER_H__

/* �ֶ����	---	2017.6.9
*/

#include "Player.h"

class Poker;

class HolderPlayer : public Player
{
public:
	HolderPlayer();

private:
	bool init();

	bool initContent();

public:
	//�ֶ������ʾ���е���
	void displayPokers();

	virtual void callLandlord();

	virtual void outPokers(const OutPokers* outPokers_);

private:
	//�Ӵ�����������ɾ��ĳ���ƻص�
	void deletePokerWaitForOutCallback(cocos2d::Ref* sender_);

	//�����������������ĳ���ƻص�
	void addPokerWaitForOutCallback(cocos2d::Ref* sender_);

private:
	std::vector<Poker>			_pokersWaitForOut;		//�ѵ��׼��������
};

#endif