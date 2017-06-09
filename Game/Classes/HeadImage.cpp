#include "HeadImage.h"

#include "Common.h"

cocos2d::SpriteFrameCache* HeadImage::s_spriteFrameCache = nullptr;

const float HEADIMAGE_SCALE = 0.7f;

bool HeadImage::init()
{
	//ͷ���
	_headBox = cocos2d::Sprite::create(headBox);
	_headBox->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_headBox->setPosition(cocos2d::Point(_headBox->getContentSize() / 2));
	_headBox->setScale(HEADIMAGE_SCALE);
	this->addChild(_headBox);
	//��ͷ��
	_curHeadImage = cocos2d::Sprite::create(noHead);
	_curHeadImage->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_curHeadImage->setPosition(cocos2d::Point(_headBox->getContentSize() / 2));
	//_curHeadImage->setScale(HEADIMAGE_SCALE);
	_headBox->addChild(_curHeadImage);

	//����Node��С
	this->setContentSize(_headBox->getContentSize() * HEADIMAGE_SCALE);

	//��ʼ������֡����
	if (s_spriteFrameCache == nullptr)
	{
		s_spriteFrameCache = cocos2d::SpriteFrameCache::getInstance();
		s_spriteFrameCache->addSpriteFramesWithFile(headImageList, headImages);
	}

	return true;
}

void HeadImage::setHeadImageType(Type type_)
{
	//����ͷ�����ͺͳ��򣬽���һ������֡
	auto spriteFrame = HeadImage::createSpriteFrameWithType(type_, this->_orientation);
	_curHeadImage->setDisplayFrame(spriteFrame);
}

void HeadImage::setOrientation(Orientation orientation_)
{
	this->_orientation = orientation_;
}

cocos2d::SpriteFrame* HeadImage::createSpriteFrameWithType(Type type_, Orientation orientation_)
{
	cocos2d::SpriteFrame* spriteFrame = nullptr;
	if (type_ == LEANDLORD)
	{
		if (orientation_ == LEFT)
		{
			spriteFrame = s_spriteFrameCache->getSpriteFrameByName(headLandlordRight);
		}
		else if (orientation_ == RIGHT)
		{
			spriteFrame = s_spriteFrameCache->getSpriteFrameByName(headLandlordLeft);
		}
	}
	else if (type_ == FARMER)
	{
		if (orientation_ == LEFT)
		{
			spriteFrame = s_spriteFrameCache->getSpriteFrameByName(headFarmerRight);
		}
		else if (orientation_ == RIGHT)
		{
			spriteFrame = s_spriteFrameCache->getSpriteFrameByName(headFarmerLeft);
		}
	}
	return spriteFrame;
}