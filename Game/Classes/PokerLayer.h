#ifndef					__POKER_LAYER_H__
#define					__POKER_LAYER_H__

/* 扑克层	---	2017.6.9
*/

#include "cocos2d.h"
#include "PokerSprite.h"

class PokerLayer : public cocos2d::Layer
{
public:
	//创建层
	static void createLayer();

	//销毁层
	static void destroyLayer();

private:
	CREATE_FUNC(PokerLayer);

private:
	virtual bool init() override;

	bool initView();

	bool initContent();

private:
	void displayPokers(const std::vector<PokerSprite*>& pokers_, float displayMaxWidth_,
		float displayStartX_, float displayMiddleX_, float displayY_, bool isOnScene_, const float SCALE = 1.0f);

private:
	//显示玩家手中的牌回调
	void displayHolderPokersCallback(cocos2d::Ref* sender_);

	//显示预留给地主的牌
	void displayLandlordPokersCallback(cocos2d::Ref* sender_);

private:
	std::vector<PokerSprite*> _lastHolderPokerSprites;	//手动玩家上一手持有的牌
};

#endif