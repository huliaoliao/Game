#include "ReadyStateLayer.h"

#include "Common.h"
#include "GameController.h"
#include "ScalableMenuItemSprite.h"

const std::string layerName = "readyStateLayer";

void ReadyStateLayer::createLayer()
{
	auto layer = ReadyStateLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

void ReadyStateLayer::destroyLayer()
{
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
}

bool ReadyStateLayer::init()
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

bool ReadyStateLayer::initView()
{
	const auto winSize = cocos2d::Director::getInstance()->getWinSize();
	const auto computerOnePos = cocos2d::Point(winSize.width * 0.8, winSize.height * 0.72);
	const auto computerTwoPos = cocos2d::Point(winSize.width * 0.2, winSize.height * 0.72);
	const auto holderPos = cocos2d::Point(winSize.width * 0.5, winSize.height * 0.4);

	//�������1׼��״̬����ʼֱ�����ó�׼����ʾ��
	_computerOneReady = cocos2d::Sprite::create(gameStateReady);
	_computerOneReady->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_computerOneReady->setPosition(computerOnePos);
	this->addChild(_computerOneReady);

	//�������2׼��״̬����ʼֱ�����ó�׼����ʾ��
	_computerTwoReady = cocos2d::Sprite::create(gameStateReady);
	_computerTwoReady->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_computerTwoReady->setPosition(computerTwoPos);
	this->addChild(_computerTwoReady);

	//�ֶ����׼��״̬����ʼ���ò���ʾ��
	_holderReady = cocos2d::Sprite::create(gameStateReady);
	_holderReady->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_holderReady->setPosition(holderPos);

	_holderReady->setVisible(false);

	this->addChild(_holderReady);

	//�ֶ����׼����ť����ʼ������ʾ��
	_holderReadyBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(gameStateReadyBtn),
		nullptr,
		CC_CALLBACK_1(ReadyStateLayer::readyBtnCallback, this));
	_holderReadyBtn->setAnchorPoint(cocos2d::Point(cocos2d::Vec2::ANCHOR_MIDDLE));
	_holderReadyBtn->setPosition(holderPos);
	
	auto menu = cocos2d::Menu::create(_holderReadyBtn, nullptr);
	menu->setPosition(cocos2d::Point::ZERO);
	this->addChild(menu);

	return true;
}

void ReadyStateLayer::updateState(float delta_)
{
	//������׼����ʶ���أ����л�����һ��״̬
	_holderReady->setVisible(false);

	_computerOneReady->setVisible(false);
	_computerTwoReady->setVisible(false);
	_holderReadyBtn->setVisible(false);

	GameController::getInstance()->updateState();

	//���ٸò�
	this->removeFromParent();
}

void ReadyStateLayer::readyBtnCallback(cocos2d::Ref*)
{
	//׼����ť����
	_holderReadyBtn->setVisible(false);
	//��ʾ�ֶ����׼��״̬
	_holderReady->setVisible(true);

	//1.0����л�״̬
	this->scheduleOnce(schedule_selector(ReadyStateLayer::updateState), 1.0f);
}
