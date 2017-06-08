#ifndef					__GAME_SCENE_H__
#define					__GAME_SCENE_H__

/* 游戏场景	---	2017.6.7 
*/

#include "cocos2d.h"

class GameScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(GameScene);

public:
	virtual bool init();

private:
	bool initView();

	bool initContent();

private:
	void createHeadImageLayerCallback(cocos2d::Ref*);	//创建头像层回调	

	void destroyHeadImageLayerCallback(cocos2d::Ref*);	//销毁头像层回调

	void createReadyLayerCallback(cocos2d::Ref*);			//创建准备层

	void destroyReadyLayerCallback(cocos2d::Ref*);			//销毁准备层
};

#endif