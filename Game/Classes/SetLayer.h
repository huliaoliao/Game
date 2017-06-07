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
	//�����ʼ��
	bool initView();

	//�������ͳ�Ա������ʼ��
	bool initContent();

private:
	bool onTouchBegan(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_);

	//androidƽ̨�µķ��ؼ�����
	void onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode_, cocos2d::Event* event_);

private:
	//���ذ�ť�ص�
	void backCallback(cocos2d::Ref* sender_);

	void funcBackCallback();

	//�˳���Ϸ��ť�ص�
	void quitGameCallback(cocos2d::Ref* sender_);

	//�л��˺Ű�ť�ص�
	void switchAccountCallback(cocos2d::Ref* sender_);

	//���ֻ������仯�ص�
	void musicChangedCallback(cocos2d::Ref* sender_, cocos2d::extension::Control::EventType type_);

	//��Ч�������仯�ص�
	void effectChangedCallback(cocos2d::Ref* sender_, cocos2d::extension::Control::EventType type_);

private:
	cocos2d::extension::ControlSlider* _musicSlider;	//���ֻ�����
	cocos2d::extension::ControlSlider* _effectSlider;	//��Ч������
};

#endif