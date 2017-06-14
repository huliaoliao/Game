#include "OverLayer.h"

#include "Common.h"
#include "GameController.h"
#include "LobbyScene.h"
#include "ScalableMenuItemSprite.h"
#include "Util.h"

const std::string layerName = "overLayer";

void OverLayer::createLayer()
{
	auto layer = OverLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

void OverLayer::destroyLayer()
{
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
}

bool OverLayer::init()
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

bool OverLayer::initView()
{
	initWinAnimation();
	
	initLostAnimation();

	//auto winSize = cocos2d::Director::getInstance()->getWinSize();

	_winSprite = cocos2d::Sprite::create();
	_winSprite->setScale(MAX_SCALE);
	_winSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_winSprite->setPosition(cocos2d::Point(BASE_WIDTH / 2 * SCALE_X,
		BASE_HEIGHT / 2 * SCALE_Y));
	_winSprite->setVisible(false);
	this->addChild(_winSprite);

	_lostSprite = cocos2d::Sprite::create();
	_lostSprite->setScale(MAX_SCALE);
	_lostSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_lostSprite->setPosition(cocos2d::Point(BASE_WIDTH / 2 * SCALE_X,
		BASE_HEIGHT / 2 * SCALE_Y));
	_lostSprite->setVisible(false);
	this->addChild(_lostSprite);

	//������Ϸ��ť
	_returnToLobbyBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(DIALOG_BTN),
		nullptr,
		CC_CALLBACK_1(OverLayer::returnToLobbyBtnCallback, this));
	_returnToLobbyBtn->setScale(MAX_SCALE);
	_returnToLobbyBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_returnToLobbyBtn->setPosition(cocos2d::Point(BASE_WIDTH / 2 * SCALE_X,
		BASE_HEIGHT / 2 * SCALE_Y));
	_returnToLobbyBtn->setVisible(false);

	//���ذ�ť����
	auto btnTTF = cocos2d::LabelTTF::create(util::strongGBToUTF8("������Ϸ����"),
		"Arial", 32);
	btnTTF->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));
	btnTTF->setPosition(cocos2d::Point(_returnToLobbyBtn->getContentSize() / 2));
	_returnToLobbyBtn->addChild(btnTTF);

	auto menu = cocos2d::Menu::create(_returnToLobbyBtn, nullptr);
	menu->setPosition(cocos2d::Point::ZERO);
	this->addChild(menu);

	return true;
}

void OverLayer::initWinAnimation()
{
	//����ͼƬ�������
	auto frameCache = cocos2d::SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(WIN_ANIMATION_IMAGE_LIST, WIN_ANIMATION_IMAGES);

	int frameNum = 6;
	cocos2d::SpriteFrame* frame = nullptr;
	cocos2d::Vector<cocos2d::SpriteFrame*> frames;

	//��һ���б�������SpriteFrame����
	for (int i = 0; i <= frameNum; ++i)
	{
		frame = frameCache->getSpriteFrameByName(
			cocos2d::StringUtils::format("win_%d.png", i));
		frames.pushBack(frame);
	}

	//ʹ��SpriteFrame�б�����������
	auto animation = cocos2d::Animation::createWithSpriteFrames(frames);
	animation->setDelayPerUnit(0.8f);

	//�����������һ������
	_winAnimation = cocos2d::Animate::create(animation);
}

void OverLayer::initLostAnimation()
{
	//����ͼƬ�������
	auto frameCache = cocos2d::SpriteFrameCache::getInstance();
	frameCache->addSpriteFramesWithFile(LOST_ANIMATION_IMAGE_LIST, LOST_ANIMATION_IMAGES);

	int frameNum = 7;
	cocos2d::SpriteFrame* frame = nullptr;
	cocos2d::Vector<cocos2d::SpriteFrame*> frames;

	//��һ���б�������SpriteFrame����
	for (int i = 0; i <= frameNum; ++i)
	{
		frame = frameCache->getSpriteFrameByName(
			cocos2d::StringUtils::format("lost_%d.png", i));
		frames.pushBack(frame);
	}

	//ʹ��SpriteFrame�б�����������
	auto animation = cocos2d::Animation::createWithSpriteFrames(frames);
	animation->setDelayPerUnit(0.8f);

	//�����������һ������
	_lostAnimation = cocos2d::Animate::create(animation);
}

bool OverLayer::initContent()
{
	//ע��������Ϸʤ����������Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(OverLayer::runWinActionCallback),
		RUN_WIN_ANIMATION,
		nullptr);;

	//ע��������Ϸʧ�ܶ�������Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(OverLayer::runLostActionCallback),
		RUN_LOST_ANIMATION,
		nullptr);

	//ע�᷵����Ϸ��������Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(OverLayer::returnToLobbyBtnCallback),
		RETURN_TO_LOBBY, 
		nullptr);

	return true;
}

void OverLayer::runWinActionCallback(cocos2d::Ref*)
{
	auto fadeOut = cocos2d::FadeOut::create(2.0f);
	_winSprite->setVisible(true);
	_winSprite->runAction(cocos2d::Sequence::create(
		_winAnimation, fadeOut, 
		cocos2d::CallFunc::create(CC_CALLBACK_0(OverLayer::showReturnToBtn, this)), nullptr));

	//_returnToLobbyBtn->setVisible(true);
}

void OverLayer::runLostActionCallback(cocos2d::Ref*)
{
	auto fadeOut = cocos2d::FadeOut::create(2.0f);
	_lostSprite->setVisible(true);
	_lostSprite->runAction(cocos2d::Sequence::create(
		_lostAnimation, fadeOut, 
		cocos2d::CallFunc::create(CC_CALLBACK_0(OverLayer::showReturnToBtn, this)),nullptr));

	//_returnToLobbyBtn->setVisible(true);
}

void OverLayer::returnToLobbyBtnCallback(cocos2d::Ref*)
{
	GameController::getInstance()->updateState();

	//�л�������
	cocos2d::Director::getInstance()->replaceScene(LobbyScene::createScene());
}

void OverLayer::showReturnToBtn()
{
	_returnToLobbyBtn->setVisible(true);
}
