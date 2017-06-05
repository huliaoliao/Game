#ifndef					__LOBBY_SCENE_MIDDLE_H__
#define					__LOBBY_SCENE_MIDDLE_H__

/* ���������м�---2017.6.5
*/

#include "cocos2d.h"

class LobbySceneMiddle : public cocos2d::Layer
{
public:
	CREATE_FUNC(LobbySceneMiddle);

public:
	virtual bool init() override;

private:
	bool initView();

private:
	//��������ص�����
	void createRoomCallback(cocos2d::Ref* sender_);

	//���뷿��ص�����
	void joinRoomCallback(cocos2d::Ref* sender_);
};

#endif