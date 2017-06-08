#ifndef					__GAME_SCENE_H__
#define					__GAME_SCENE_H__

/* ��Ϸ����	---	2017.6.7 
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
	void createHeadImageLayerCallback(cocos2d::Ref*);	//����ͷ���ص�	

	void destroyHeadImageLayerCallback(cocos2d::Ref*);	//����ͷ���ص�

	void createReadyLayerCallback(cocos2d::Ref*);			//����׼����

	void destroyReadyLayerCallback(cocos2d::Ref*);			//����׼����
};

#endif