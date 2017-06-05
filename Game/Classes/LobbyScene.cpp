#include "LobbyScene.h"

#include "LobbySceneBottom.h"
#include "LobbySceneMiddle.h"
#include "LobbySceneTop.h"

cocos2d::Scene* LobbyScene::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = LobbyScene::create();
	scene->addChild(layer);
	return scene;
}

bool LobbyScene::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	if (initContent() == false)
	{
		return false;
	}

	return true;
}

bool LobbyScene::initContent()
{
	//��ʼ�����汳��
	auto bgSprite = cocos2d::Sprite::create("lobby/lobby_bg.png");
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	bgSprite->setPosition(cocos2d::Point(winSize.width / 2, winSize.height / 2));
	auto bgSize = bgSprite->getContentSize();
	bgSprite->setScaleX(winSize.width / bgSize.width);
	bgSprite->setScaleY(winSize.height / bgSize.height);
	this->addChild(bgSprite, 0);

	if (initSceneModule() == false)
	{
		return false;
	}

	return true;
}

bool LobbyScene::initSceneModule()
{
	auto lobbySceneTop = LobbySceneTop::create();
	this->addChild(lobbySceneTop, 0);
	auto lobbySceneMiddle = LobbySceneMiddle::create();
	this->addChild(lobbySceneMiddle, 0);
	auto lobbySceneBottom = LobbySceneBottom::create();
	this->addChild(lobbySceneBottom, 0);

	return true;
}
