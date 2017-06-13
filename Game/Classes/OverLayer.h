#ifndef					__OVER_LAYER_H__
#define					__OVER_LAYER_H__

/*	��Ϸ������	---	2017.6.13
*/

#include "cocos2d.h"

class ScalableMenuItemSprite;

class OverLayer : public cocos2d::Layer
{
public:
	static void createLayer();

	static void destroyLayer();

private:
	CREATE_FUNC(OverLayer);

private:
	virtual bool init() override;

	bool initView();

	void initWinAnimation();

	void initLostAnimation();

	bool initContent();

private:
	//����ʤ�������ص�
	void runWinActionCallback(cocos2d::Ref*);

	//����ʧ�ܶ����ص�
	void runLostActionCallback(cocos2d::Ref*);

	//���ش����ص�
	void returnToLobbyBtnCallback(cocos2d::Ref*);

	//��ʾ���ش�����ť
	void showReturnToBtn();

private:
	cocos2d::Animate*	_winAnimation;	//ʤ���Ķ���
	cocos2d::Animate*	_lostAnimation;	//ʧ�ܵĶ���

	cocos2d::Sprite*					_winSprite;
	cocos2d::Sprite*					_lostSprite;
	ScalableMenuItemSprite*		_returnToLobbyBtn;	//���ش�����ť
};

#endif