#ifndef					__PLAYER_H__
#define					__PLAYER_H__

/* 玩家类	---	2017.6.7
*/

#include "cocos2d.h"
#include "PokerController.h"

class OutPokers;

class Player : public cocos2d::Ref
{
public:
	enum Type
	{
		LANDLORD,
		FARMER
	};
public:
	void setPokers(const std::vector<Poker>& pokers_);

	void pushPoker(const Poker& poker_);

	int getCallScore() const;

	void setCallScore(int score_);

	//玩家类型相关
	Type getPlayerType() const;

	void setPlayerType(Type type_);

	void setPokersCanClick(bool canClick_);

public:
	//叫地主
	virtual void callLandlord() = 0;

	//出牌
	virtual void outPokers(const OutPokers* outPokers_) = 0;

protected:
	std::vector<Poker>	 _holdPokers;		//持有的牌
	std::vector<Poker>	 _outedPokers;	//当前打出的牌
	int							 _callScore;
	Type							 _type;				//玩家类型
	OutPokers*				_lastOutPokers;	//上一手扑克，初始化为nullptr，轮到其出牌时获取，出完牌后必须置nullptr
};

#endif