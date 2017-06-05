#ifndef					__LOBBY_SCENE_H__
#define					__LOBBY_SCENE_H__

#include "cocos2d.h"

class LobbyScene : public cocos2d::Layer
{
public:
	static cocos2d::Scene* createScene();

	CREATE_FUNC(LobbyScene);

public:
	virtual bool init() override;

private:
	bool initContent();
	//��ʼ����������ģ�飬��Ϊ�������в��͵ײ�
	bool initSceneModule();
};

#endif