#ifndef					__GAME_SCENE_H__
#define					__GAME_SCENE_H__

/* ”Œœ∑≥°æ∞	---	2017.6.7 
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

	void initUpdate(float delta_);
};

#endif