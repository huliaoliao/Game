#ifndef					__LOBBY_SCENE_BOTTOM_H__
#define					__LOBBY_SCENE_BOTTOM_H__

/* ���������ײ�---2017.6.5
*/

#include "cocos2d.h"

class LobbySceneBottom : public cocos2d::Layer
{
public:
	CREATE_FUNC(LobbySceneBottom);

public:
	virtual bool init() override;

private:
	bool initView();

private:
	//����ť�ص�����
	void lobbyShareCallback(cocos2d::Ref* sender_);

	//���ť�ص�����
	void lobbyActivityCallback(cocos2d::Ref* sender_);

	//ս����ť�ص�����
	void lobbyRecordCallback(cocos2d::Ref* sender_);
};

#endif