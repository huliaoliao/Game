#include "LobbySceneBottom.h"

#include "ScalableMenuItemSprite.h"

bool LobbySceneBottom::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	if (initView() == false)
	{
		return false;
	}

	return true;
}

bool LobbySceneBottom::initView()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();

	//背景
	auto bottomBg = cocos2d::Sprite::create("lobby/lobby_bottom_bg.png");
	bottomBg->setScale(0.9f);
	bottomBg->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	bottomBg->setPosition(cocos2d::Point(winSize.width / 2, 0));
	this->addChild(bottomBg);

	const auto bottomBgSize = bottomBg->getContentSize();

	//分享按钮
	auto shareBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create("lobby/share.png"),
		nullptr,
		CC_CALLBACK_1(LobbySceneBottom::lobbyShareCallback, this));
	shareBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	shareBtn->setPosition(cocos2d::Point(bottomBgSize.width / 2, 70));

	//活动按钮
	auto activityBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create("lobby/activity.png"),
		nullptr,
		CC_CALLBACK_1(LobbySceneBottom::lobbyActivityCallback, this));
	activityBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_RIGHT);
	activityBtn->setPosition(cocos2d::Point(shareBtn->getPosition()) - 
		cocos2d::Size(bottomBgSize.width / 4, 0));

	//战绩按钮
	auto recordBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create("lobby/record.png"),
		nullptr,
		CC_CALLBACK_1(LobbySceneBottom::lobbyRecordCallback, this));
	recordBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	recordBtn->setPosition(cocos2d::Point(shareBtn->getPosition()) +
		cocos2d::Size(bottomBgSize.width / 4, 0));

	auto menu = cocos2d::Menu::create(activityBtn, shareBtn, recordBtn, nullptr);
	menu->setPosition(cocos2d::Point::ZERO);
	bottomBg->addChild(menu);

	return true;
}

void LobbySceneBottom::lobbyShareCallback(cocos2d::Ref* sender_)
{

}

void LobbySceneBottom::lobbyActivityCallback(cocos2d::Ref* sender_)
{

}

void LobbySceneBottom::lobbyRecordCallback(cocos2d::Ref* sender_)
{

}

