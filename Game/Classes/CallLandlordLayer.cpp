#include "CallLandlordLayer.h"

#include "Common.h"
#include "HolderPlayerInstance.h"
#include "ScalableMenuItemSprite.h"

const std::string layerName = "callLandlordLayer";

void CallLandlordLayer::createLayer()
{
	auto layer = CallLandlordLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

void CallLandlordLayer::destroyLayer()
{
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
}

bool CallLandlordLayer::init()
{
	if (!cocos2d::Layer::init())
	{
		return false;
	}

	if (initView() == false)
	{
		return false;
	}

	if (initContent() == false)
	{
		return true;
	}

	return true;
}

bool CallLandlordLayer::initView()
{
	_stateSpriteCache = cocos2d::SpriteFrameCache::getInstance();
	_stateSpriteCache->addSpriteFramesWithFile(CALL_LANDLORD_IMAGE_LIST, CALL_LANDLORD_IMAGES);

	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	const auto computerOnePos = cocos2d::Point(winSize.width * 0.8, winSize.height * 0.72);
	const auto computerTwoPos = cocos2d::Point(winSize.width * 0.2, winSize.height * 0.72);
	const auto holderPos = cocos2d::Point(winSize.width * 0.5, winSize.height * 0.4);

	auto btnWidth = cocos2d::Sprite::create(NOCALLBTN)->getContentSize().width;
	const auto btnInterval = 10;

	//显示手动的玩家的叫地主按钮
	auto callOneBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(CALLONEBTN),
		nullptr,
		CC_CALLBACK_1(CallLandlordLayer::noCallCallBack, this));
	callOneBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	callOneBtn->setPosition(cocos2d::Point(holderPos.x - btnInterval / 2 - btnWidth / 2,
		holderPos.y));
	
	auto noCallBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(NOCALLBTN),
		nullptr,
		CC_CALLBACK_1(CallLandlordLayer::callOneCallback, this));
	noCallBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	noCallBtn->setPosition(cocos2d::Point(callOneBtn->getPosition().x - btnWidth - btnInterval,
		callOneBtn->getPosition().y));

	auto callTwoBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(CALLTWOBTN),
		nullptr,
		CC_CALLBACK_1(CallLandlordLayer::callTwoCallback, this));
	callTwoBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	callTwoBtn->setPosition(cocos2d::Point(callOneBtn->getPosition().x + btnWidth + btnInterval,
		callOneBtn->getPosition().y));

	auto callThreeBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(CALLTHREEBTN),
		nullptr,
		CC_CALLBACK_1(CallLandlordLayer::callThreeCallback, this));
	callThreeBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	callThreeBtn->setPosition(cocos2d::Point(callTwoBtn->getPosition().x + btnWidth + btnInterval,
		callTwoBtn->getPosition().y));

	_btnMenu = cocos2d::Menu::create(noCallBtn, callOneBtn, callTwoBtn, callThreeBtn, nullptr);
	_btnMenu->setPosition(cocos2d::Point::ZERO);
	_btnMenu->setVisible(false);	//开始均不显示
	this->addChild(_btnMenu);

	return true;
}

bool CallLandlordLayer::initContent()
{
	//注册显示手动玩家叫地主按钮
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordLayer::displayCallLandlordBtnCallback, this),
		DISPLAY_CALL_LANDLORD_BTN,
		nullptr);

	return true;
}

void CallLandlordLayer::noCallCallBack(cocos2d::Ref*)
{
	HolderPlayerInstance::getInstance()->setCallScore(0);

	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_CALL_LANDLORD_INDEX, nullptr);
}

void CallLandlordLayer::callOneCallback(cocos2d::Ref*)
{
	HolderPlayerInstance::getInstance()->setCallScore(1);

	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_CALL_LANDLORD_INDEX, nullptr);
}

void CallLandlordLayer::callTwoCallback(cocos2d::Ref*)
{
	HolderPlayerInstance::getInstance()->setCallScore(2);

	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_CALL_LANDLORD_INDEX, nullptr);
}

void CallLandlordLayer::callThreeCallback(cocos2d::Ref*)
{
	HolderPlayerInstance::getInstance()->setCallScore(3);

	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_CALL_LANDLORD_INDEX, nullptr);
}

void CallLandlordLayer::displayCallLandlordBtnCallback(cocos2d::Ref*)
{
	_btnMenu->setVisible(true);
}
