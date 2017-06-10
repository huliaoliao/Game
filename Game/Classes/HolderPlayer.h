#ifndef					__HOLDER_PLAYER_H__
#define					__HOLDER_PLAYER_H__

/* 手动玩家	---	2017.6.9
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
	//手动玩家显示手中的牌
	void displayPokers();

	virtual void callLandlord();

	virtual void outPokers(const OutPokers* outPokers_);

private:
	//从待出牌序列中删除某张牌回调
	void deletePokerWaitForOutCallback(cocos2d::Ref* sender_);

	//向待出牌序列中增加某张牌回调
	void addPokerWaitForOutCallback(cocos2d::Ref* sender_);

private:
	std::vector<Poker>			_pokersWaitForOut;		//已点击准备出的牌
};

#endif