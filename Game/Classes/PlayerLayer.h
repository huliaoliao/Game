#ifndef					__PLAYER_LAYER_H__
#define					__PLAYER_LAYER_H__

/*	��Ҳ㣺������ͷ����Ϣ	---	2017.6.7 
*/

#include "cocos2d.h"

class HeadImage;

class PlayerLayer : public cocos2d::Layer
{
public:
	static void createLayer();

private:
	CREATE_FUNC(PlayerLayer);

	virtual bool init() override;

private:
	bool initView();

private:
	HeadImage* _computerOneHeadImage;
	HeadImage* _computerTwoHeadImage;
	HeadImage* _holdPlayerHeadImage;
};

#endif