#include "GameScene.h"

#include "Common.h"
#include "ui/UIScale9Sprite.h"

#include "PlayerLayer.h"

cocos2d::Scene* GameScene::createScene()
{
	auto scene = cocos2d::Scene::create();
	auto layer = GameScene::create();
	scene->addChild(layer);
		
	return scene;
}

bool GameScene::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	if (initView() == false)
	{
		return false;
	}

	//如果不这样做，因为Scene还没有完全初始化，导致当前RunningScene
	//不是该Scene，导致出错
	this->scheduleOnce(schedule_selector(GameScene::initUpdate), 1.0f);

	return true;
}

bool GameScene::initView()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();

	//游戏场景背景
	auto sceneBg = cocos2d::ui::Scale9Sprite::create(gameSceneBg);
	auto sceneBgSize = sceneBg->getContentSize();
	sceneBg->setCapInsets(cocos2d::Rect(sceneBgSize.width / 4, sceneBgSize.height / 4,
		sceneBgSize.width / 4, sceneBgSize.height / 4));
	sceneBg->setContentSize(cocos2d::Size(winSize));
	sceneBg->setPosition(cocos2d::Point(winSize / 2));
	this->addChild(sceneBg);

	//游戏场景四周边框
	auto sceneBorder = cocos2d::ui::Scale9Sprite::create(gameSceneBorder);
	auto sceneBorderSize = sceneBorder->getContentSize();
	sceneBorder->setCapInsets(cocos2d::Rect(sceneBorderSize.width / 4, sceneBorderSize.height / 4,
		sceneBorderSize.width / 4, sceneBorderSize.height / 4));
	sceneBorder->setContentSize(cocos2d::Size(winSize.width, winSize.height));
	sceneBorder->setPosition(cocos2d::Point(winSize / 2));
	this->addChild(sceneBorder);

	return true;
}

void GameScene::initUpdate(float delta_)
{
	PlayerLayer::createLayer();
}






