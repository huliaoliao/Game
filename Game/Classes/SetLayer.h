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
	//���ذ�ť�ص�
	void backCallback(cocos2d::Ref* sender_);

	//�˳���Ϸ��ť�ص�
	void quitGameCallback(cocos2d::Ref* sender_);

	//�л��˺Ű�ť�ص�
	void switchAccountCallback(cocos2d::Ref* sender_);
};

#endif