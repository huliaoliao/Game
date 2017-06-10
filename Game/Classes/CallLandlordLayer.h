#ifndef					__CALL_LANDLORD_LAYER_H__
#define					__CALL_LANDLORD_LAYER_H__

/*	�е�����	---	2017.6.9
*/

#include "cocos2d.h"

class CallLandlordLayer : public cocos2d::Layer
{
public:
	static void createLayer();

	static void destroyLayer();

private:
	CREATE_FUNC(CallLandlordLayer);

	virtual bool init() override;

	bool initView();

	bool initContent();

private:
	void holderCallLandlordState(const std::string& name_);

	void computerOneCallLandlordState(const std::string& name_);

	void computerTwoCallLandlordState(const std::string& name_);

private:
	void displayCallLandlordBtnCallback(cocos2d::Ref*);

	//��ʾ�������1�з�״̬�ص�
	void displayComputerOneCallStateCallback(cocos2d::Ref*);

	//��ʾ�������2�з�״̬�ص�
	void displayComputerTwoCallStateCallback(cocos2d::Ref*);


	//�ֶ���ҽзֻص�
	void noCallCallBack(cocos2d::Ref*);

	void callOneCallback(cocos2d::Ref*);

	void callTwoCallback(cocos2d::Ref*);

	void callThreeCallback(cocos2d::Ref*);

	//�������1�зֻص�
	void computerOneNoCallCallback(cocos2d::Ref*);

	void computerOneCallOneCallback(cocos2d::Ref*);

	void computerOneCallTwoCallback(cocos2d::Ref*);

	void computerOneCallThreeCallback(cocos2d::Ref*);

	//�������2�зֻص�
	void computerTwoNoCallCallback(cocos2d::Ref*);

	void computerTwoCallOneCallback(cocos2d::Ref*);

	void computerTwoCallTwoCallback(cocos2d::Ref*);

	void computerTwoCallThreeCallback(cocos2d::Ref*);

private:
	cocos2d::SpriteFrameCache* _stateSpriteCache;

	cocos2d::Menu*					_btnMenu;	//�ֶ���ҽе�����ť

	cocos2d::Sprite*					_holderCallLandlordState;
	cocos2d::Sprite*					_computerOneCallLandlordState;
	cocos2d::Sprite*					_computerTwoCallLandlordState;
};

#endif