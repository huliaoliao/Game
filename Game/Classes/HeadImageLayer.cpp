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

	return true;
}

bool HeadImageLayer::initView()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();

	//����1��λ�ã����Ϸ���
	_computerOneHeadImage = HeadImage::create();
	_computerOneHeadImage->setOrientation(HeadImage::RIGHT);
	_computerOneHeadImage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_computerOneHeadImage->setPosition(
		cocos2d::Point(winSize.width * 0.9, winSize.height * 0.65));
	this->addChild(_computerOneHeadImage, 1);

	//����2��λ�ã����Ϸ���
	_computerTwoHeadImage = HeadImage::create();
	_computerTwoHeadImage->setOrientation(HeadImage::LEFT);
	_computerTwoHeadImage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_computerTwoHeadImage->setPosition(
		cocos2d::Point(winSize.width * 0.1, winSize.height * 0.65));
	this->addChild(_computerTwoHeadImage);

	//�ֶ���ҵ�λ��
	_holdPlayerHeadImage = HeadImage::create();
	_holdPlayerHeadImage->setOrientation(HeadImage::LEFT);
	_holdPlayerHeadImage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_holdPlayerHeadImage->setPosition(
		cocos2d::Point(winSize.width * 0.1, winSize.height * 0.4));
	this->addChild(_holdPlayerHeadImage);

	return true;
}