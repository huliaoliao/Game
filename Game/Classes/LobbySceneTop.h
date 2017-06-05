#ifndef					__LOBBY_SCENE_TOP_H__
#define					__LOBBY_SCENE_TOP_H__

/* ������������---2017.6.5
*/

#include "cocos2d.h"

class LobbySceneTop : public cocos2d::Layer
{
public:
	CREATE_FUNC(LobbySceneTop);

	virtual bool init() override;

private:
	bool initView();

private:
	//���ð�ť�ص�����
	void lobbySetCallback(cocos2d::Ref* sender_);

	//����ť�ص�����
	void lobbyRuleCallback(cocos2d::Ref* sender_);

	//������ť�ص�����
	void lobbyFeedbackCallback(cocos2d::Ref* sender_);
};

#endif