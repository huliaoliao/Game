#ifndef					__CALL_LANDLORD_LAYER_H__
#define					__CALL_LANDLORD_LAYER_H__

/*	叫地主层	---	2017.6.9
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
	void noCallCallBack(cocos2d::Ref*);

	void callOneCallback(cocos2d::Ref*);

	void callTwoCallback(cocos2d::Ref*);

	void callThreeCallback(cocos2d::Ref*);

	void displayCallLandlordBtnCallback(cocos2d::Ref*);

private:
	cocos2d::SpriteFrameCache* _stateSpriteCache;

	cocos2d::Menu*					_btnMenu;	//手动玩家叫地主按钮
};

#endif