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

	bool initListener();

private:
	bool onTouchBegan(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_);

	void onTouchMoved(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_);

	void onTouchEnded(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_);

private:
	void displayPokers(const std::vector<PokerSprite*>& pokers_, float displayMaxWidth_,
		float displayStartX_, float displayMiddleX_, float displayY_, bool isOnScene_, const float SCALE = 1.0f);

	std::vector<PokerSprite*> createPokerSprites(cocos2d::Ref* sender_);

private:
	//显示玩家手中的牌回调
	void displayHolderPokersCallback(cocos2d::Ref* sender_);

	//显示预留给地主的牌
	void displayLandlordPokersCallback(cocos2d::Ref* sender_);

	//删除手动玩家上一手打出的牌
	void destroyHolderLastOutPokersCallback(cocos2d::Ref* sender_);

	//显示手动玩家这一手打出的牌
	void displayHolderOutPokersCallbacl(cocos2d::Ref* sender_);

	//删除电脑玩家1上一手打出的牌
	void destroyComputerOneLastOutPokersCallback(cocos2d::Ref* sender_);

	//显示电脑玩家1这一手打出的牌
	void displayComputerOneOutPokersCallback(cocos2d::Ref* sender_);

	//删除电脑玩家2上一手打出的牌
	void destroyComputerTwoLastOutPokersCallback(cocos2d::Ref* sender_);

	//显示电脑玩家2这一手打出的牌
	void displayComputerTwoOutPokersCallback(cocos2d::Ref* sender_);

	//出牌相关按钮回调
	//不出按钮回调
	void passBtnCallback(cocos2d::Ref* sender_);

	//出牌按钮回调
	void outPokersBtnCallback(cocos2d::Ref* sender_);

	//提示按钮回调
	void hintBtnCallback(cocos2d::Ref* sender_);

private:
	std::vector<PokerSprite*> _holderClickedPokerSprites;
	std::vector<PokerSprite*> _lastHolderPokerSprites;	//手动玩家上一手持有的牌
	//存放打出的牌，用于该次删除上次打出的牌
	std::vector<PokerSprite*> _lastHolderOutPokersSprites;	//手动玩家上一手打出的牌
	std::vector<PokerSprite*>	_lastComputerOneOutPokersSprites;	//电脑玩家1上一手打出的牌
	std::vector<PokerSprite*>	_lastComputerTwoOutPokersSprites;	//电脑玩家2上一手打出的牌

	cocos2d::Sprite*				_holderPassSprite;		//手动玩家不出按钮
	cocos2d::Sprite*				_computerOnePassSprite;	//电脑玩家1不出按钮
	cocos2d::Sprite*				_computerTwoPassSprite;	//电脑玩家2不出按钮

	cocos2d::Menu*				_btnMenu;		//出牌按钮菜单
};

#endif