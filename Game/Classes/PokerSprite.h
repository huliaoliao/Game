#ifndef					__POKER_SPRITE_H__
#define					__POKER_SPRITE_H__

/*	扑克精灵（用于在扑克层上显示）	---	2017.6.9
*/

#include "cocos2d.h"
#include "Poker.h"

class PokerSprite : public cocos2d::Node
{
public:
	static PokerSprite* create(cocos2d::Sprite* pokerSprite_, const Poker& poker_);

public:
	PokerSprite* clone();

private:
	PokerSprite(cocos2d::Sprite* pokerSprite_, const Poker& poker_);

	~PokerSprite();

private:
	virtual bool init() override;

	bool initView();

private:
	cocos2d::Sprite* _pokerSprite;
	Poker				 _poker;
};

#endif