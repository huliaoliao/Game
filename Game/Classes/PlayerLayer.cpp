#include "PlayerLayer.h"

#include "Common.h"
#include "HeadImage.h"

static const std::string layerName = "playerLayer";

void PlayerLayer::createLayer()
{
	auto layer = PlayerLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

bool PlayerLayer::init()
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

bool PlayerLayer::initView()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();

	//电脑1的位置
	_computerOneHeadImage = HeadImage::create();
	_computerOneHeadImage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_computerOneHeadImage->setPosition(
		cocos2d::Point(winSize.width * 0.1, winSize.height * 0.65));
	this->addChild(_computerOneHeadImage, 1);

	//电脑2的位置
	_computerTwoHeadImage = HeadImage::create();
	_computerTwoHeadImage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_computerTwoHeadImage->setPosition(
		cocos2d::Point(winSize.width * 0.9, winSize.height * 0.65));
	this->addChild(_computerTwoHeadImage);

	//手动玩家的位置
	_holdPlayerHeadImage = HeadImage::create();
	_holdPlayerHeadImage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_holdPlayerHeadImage->setPosition(
		cocos2d::Point(winSize.width * 0.1, winSize.height * 0.4));
	this->addChild(_holdPlayerHeadImage);

	return true;
}



