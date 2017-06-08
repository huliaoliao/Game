#include "LobbySceneMiddle.h"

#include "Common.h"
#include "GameController.h"
#include "ScalableMenuItemSprite.h"
#include "ui/UIScale9Sprite.h"
#include "Util.h"

bool LobbySceneMiddle::init()
{
	if (!Layer::init())
	{
		return false;
	}

	if (initView() == false)
	{
		return false;
	}

	return true;
}

bool LobbySceneMiddle::initView()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	//公告显示
	auto marqueeBg = cocos2d::ui::Scale9Sprite::create(
		"lobby/lobby_marquee_right.png");
	const auto marqueeBgWidth = 700.0f;
	marqueeBg->setContentSize(cocos2d::Size(marqueeBgWidth, marqueeBg->getContentSize().height));
	marqueeBg->setPosition(cocos2d::Point(winSize.width / 2,
		0.78 * winSize.height));
	this->addChild(marqueeBg);
	
	//喇叭
	auto marqueeLeft = cocos2d::Sprite::create("lobby/lobby_marquee_left.png");
	marqueeLeft->setPosition(cocos2d::Point(0, marqueeBg->getContentSize().height / 2));
	marqueeBg->addChild(marqueeLeft);

	//绘制矩形当做模板stencil，左上角，右上角，右下角，左下角，相对于clipper的正中心
	auto shape = cocos2d::DrawNode::create();
	cocos2d::Point points[] = {cocos2d::Point(-marqueeBgWidth / 2 + 25, 20), cocos2d::Point(marqueeBgWidth / 2, 20),
		cocos2d::Point(marqueeBgWidth / 2, -20), cocos2d::Point(-marqueeBgWidth / 2 + 25, -20)};
	shape->drawPolygon(points, 4, cocos2d::Color4F(1, 0, 0, 1), 2, cocos2d::Color4F(0, 0, 1, 1));

	//遮罩
	auto clipper = cocos2d::ClippingNode::create(shape);
	clipper->setPosition(cocos2d::Point(marqueeBg->getContentSize() / 2));
	marqueeBg->addChild(clipper);

	//显示内容
	std::string showContent = "欢迎来到单机斗地主!";
	auto showContentTTF = cocos2d::LabelTTF::create(util::strongGBToUTF8(showContent.c_str()),
		"微软雅黑", 27);
	showContentTTF->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	showContentTTF->setPosition(cocos2d::Point(marqueeBg->getContentSize().width / 2, 0));
	clipper->addChild(showContentTTF);
	float moveLen = marqueeBg->getContentSize().width / 2 + showContentTTF->getContentSize().width;
	showContentTTF->runAction(cocos2d::RepeatForever::create(
		cocos2d::Sequence::create(
		cocos2d::MoveTo::create(5.0f * moveLen / (marqueeBg->getContentSize().width / 2), cocos2d::Point(-moveLen, 0)),
		cocos2d::Place::create(showContentTTF->getPosition() + cocos2d::Size(00, 0)), nullptr)));

	//创建房间按钮
// 	auto createRoomBtn = ScalableMenuItemSprite::create(
// 		cocos2d::Sprite::create("lobby/create_room.png"),
// 		nullptr,
// 		CC_CALLBACK_1(LobbySceneMiddle::createRoomCallback, this));
// 	createRoomBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
// 	createRoomBtn->setPosition(cocos2d::Point(winSize.width / 4, winSize.height / 2 - 20));
// 	createRoomBtn->setScale(0.8f);

	//加入房间按钮
// 	auto joinRoomBtn = ScalableMenuItemSprite::create(
// 		cocos2d::Sprite::create("lobby/join_room.png"),
// 		nullptr,
// 		CC_CALLBACK_1(LobbySceneMiddle::joinRoomCallback, this));
// 	joinRoomBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
// 	joinRoomBtn->setPosition(cocos2d::Point(winSize.width * 3 / 4, winSize.height / 2 - 20));
// 	joinRoomBtn->setScale(0.8f);

	auto startGameBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(startGameImage),
		nullptr,
		CC_CALLBACK_1(LobbySceneMiddle::startGameCallback, this));
	startGameBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	startGameBtn->setPosition(cocos2d::Point(winSize.width / 2, winSize.height / 2 - 20));
	startGameBtn->setScale(0.8f);

	auto startGameMenu = cocos2d::Menu::create(
		startGameBtn, nullptr);
	startGameMenu->setPosition(cocos2d::Point::ZERO);
	this->addChild(startGameMenu);

// 	auto roomMenu = cocos2d::Menu::create(
// 		createRoomBtn, joinRoomBtn, nullptr);
// 	roomMenu->setPosition(cocos2d::Point::ZERO);
// 	this->addChild(roomMenu);

	return true;
}

void LobbySceneMiddle::createRoomCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//创建房间
}

void LobbySceneMiddle::joinRoomCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//加入房间
}

void LobbySceneMiddle::startGameCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//开始游戏
	//cocos2d::Director::getInstance()->replaceScene(GameScene::createScene());
	GameController::getInstance()->start();
}

