#include "HeadImageLayer.h"

#include "Common.h"
#include "HeadImage.h"

static const std::string layerName = "headImageLayer";

void HeadImageLayer::createLayer()
{
	auto layer = HeadImageLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

void HeadImageLayer::destroyLayer()
{
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
}

bool HeadImageLayer::init()
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
		return false;
	}

	return true;
}

bool HeadImageLayer::initView()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();

	//电脑1的位置（右上方）
	_computerOneHeadImage = HeadImage::create();
	_computerOneHeadImage->setOrientation(HeadImage::RIGHT);
	_computerOneHeadImage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_computerOneHeadImage->setPosition(
		cocos2d::Point(winSize.width * 0.9, winSize.height * 0.65));
	this->addChild(_computerOneHeadImage, 1);

	//电脑2的位置（左上方）
	_computerTwoHeadImage = HeadImage::create();
	_computerTwoHeadImage->setOrientation(HeadImage::LEFT);
	_computerTwoHeadImage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_computerTwoHeadImage->setPosition(
		cocos2d::Point(winSize.width * 0.1, winSize.height * 0.65));
	this->addChild(_computerTwoHeadImage);

	//手动玩家的位置
	_holdPlayerHeadImage = HeadImage::create();
	_holdPlayerHeadImage->setOrientation(HeadImage::LEFT);
	_holdPlayerHeadImage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_holdPlayerHeadImage->setPosition(
		cocos2d::Point(winSize.width * 0.1, winSize.height * 0.3));
	this->addChild(_holdPlayerHeadImage);

	return true;
}

bool HeadImageLayer::initContent()
{
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HeadImageLayer::updateHolderHeadImageCallback, this),
		UPDATE_HOLDER_HEADIMAGE,
		nullptr);

	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HeadImageLayer::updateComputerOneHeadImageCallback, this),
		UPDATE_COMPUTERONE_HEADIMAHE,
		nullptr);

	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(HeadImageLayer::updateComputerTwoHeadImageCallback, this),
		UPDATE_COMPUTERTWO_HEADIMAGE,
		nullptr);

	return true;
}

void HeadImageLayer::updateHeadImage()
{
	_holdPlayerHeadImage->setHeadImageType(HeadImage::FARMER);
	_computerOneHeadImage->setHeadImageType(HeadImage::FARMER);
	_computerTwoHeadImage->setHeadImageType(HeadImage::FARMER);
}


void HeadImageLayer::updateHolderHeadImageCallback(cocos2d::Ref*)
{
	updateHeadImage();
	_holdPlayerHeadImage->setHeadImageType(HeadImage::LEANDLORD);
}

void HeadImageLayer::updateComputerOneHeadImageCallback(cocos2d::Ref*)
{
	updateHeadImage();
	_computerOneHeadImage->setHeadImageType(HeadImage::LEANDLORD);
}

void HeadImageLayer::updateComputerTwoHeadImageCallback(cocos2d::Ref*)
{
	updateHeadImage();
	_computerTwoHeadImage->setHeadImageType(HeadImage::LEANDLORD);
}