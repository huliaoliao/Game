#ifndef					__CUSTOMSERVICE_LAYER_H__
#define					__CUSTOMSERVICE_LAYER_H__

/* �ͷ��Ի��� --- 2017.6.7
*/

#include "cocos2d.h"
#include "ui/UIScale9Sprite.h"

class CustomServiceLayer : public cocos2d::Layer
{
public:
	static void createLayer();

private:
	CREATE_FUNC(CustomServiceLayer);

public:
	virtual bool init() override;

private:
	//��ʼ���Ի������
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

	//����绰��ť�ص�
	void callServiceCallback(cocos2d::Ref* sender_);

	//�л��˺Ű�ť�ص�
	void feedbackCallback(cocos2d::Ref* sender_);

private:
	cocos2d::ui::Scale9Sprite* _middleBgSprite;
};

#endif