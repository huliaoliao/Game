#ifndef					__SET_LAYER_H__
#define					__SET_LAYER_H__

//#pragma comment(lib, "libExtensions.lib")

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"
#include "cocos-ext.h"

class SetLayer : public cocos2d::Layer
{
public:
	CREATE_FUNC(SetLayer);

	static void createSetLayer();

public:
	virtual bool init() override;

private:
	bool initView();

private:
	//返回按钮回调
	void backCallback(cocos2d::Ref* sender_);

	//退出游戏按钮回调
	void quitGameCallback(cocos2d::Ref* sender_);

	//切换账号按钮回调
	void switchAccountCallback(cocos2d::Ref* sender_);
};

#endif