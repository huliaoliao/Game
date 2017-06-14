#include "CallLandlordLayer.h"

#include "Common.h"
#include "ComputerPlayerInstanceOne.h"
#include "ComputerPlayerInstanceTwo.h"
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

	//��ʾ�ֶ�����ҵĽе�����ť
	auto callOneBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(CALLONEBTN),
		nullptr,
		CC_CALLBACK_1(CallLandlordLayer::callOneCallback, this));
	callOneBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	callOneBtn->setPosition(cocos2d::Point(holderPos.x - btnInterval / 2 - btnWidth / 2,
		holderPos.y));
	
	auto noCallBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(NOCALLBTN),
		nullptr,
		CC_CALLBACK_1(CallLandlordLayer::noCallCallBack, this));
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
	_btnMenu->setVisible(false);	//��ʼ������ʾ
	this->addChild(_btnMenu);

	//�з�״̬��Ϣ����ʼ����sprite����Ϊ���е�״̬�����ݾ���зֵ�״̬����ʾ�з���Ϣ
	//�ֶ���ҵĽе���״̬����ͷ����
	auto holderCallLandlordStatePos = cocos2d::Point(winSize.width * 0.2, winSize.height * 0.4);

	_holderCallLandlordState = cocos2d::Sprite::createWithSpriteFrameName(NOCALLSTATE);
	_holderCallLandlordState->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_holderCallLandlordState->setPosition(cocos2d::Point(holderCallLandlordStatePos));
	_holderCallLandlordState->setVisible(false);	//��ʼ����ʾ
	this->addChild(_holderCallLandlordState);

	_computerOneCallLandlordState = cocos2d::Sprite::createWithSpriteFrameName(NOCALLSTATE);
	_computerOneCallLandlordState->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_computerOneCallLandlordState->setPosition(cocos2d::Point(computerOnePos));
	_computerOneCallLandlordState->setVisible(false);
	this->addChild(_computerOneCallLandlordState);

	_computerTwoCallLandlordState = cocos2d::Sprite::createWithSpriteFrameName(NOCALLSTATE);
	_computerTwoCallLandlordState->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_computerTwoCallLandlordState->setPosition(cocos2d::Point(computerTwoPos));
	_computerTwoCallLandlordState->setVisible(false);
	this->addChild(_computerTwoCallLandlordState);

	return true;
}

bool CallLandlordLayer::initContent()
{
	//ע����ʾ�ֶ���ҽе�����ť
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordLayer::displayCallLandlordBtnCallback),
		DISPLAY_CALL_LANDLORD_BTN,
		nullptr);

	//�������1�зֻص����������ֽз�״̬��
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordLayer::computerOneNoCallCallback),
		COMPUTER_ONE_NOCALL,
		nullptr);

	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordLayer::computerOneCallOneCallback),
		COMPUTER_ONE_CALLONE,
		nullptr);

	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordLayer::computerOneCallTwoCallback),
		COMPUTER_ONE_CALLTWO,
		nullptr);

	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordLayer::computerOneCallThreeCallback),
		COMPUTER_ONE_CALLTHREE,
		nullptr);

	//�������2�зֻص����������ֽз�״̬��
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordLayer::computerTwoNoCallCallback),
		COMPUTER_TWO_NOCALL,
		nullptr);

	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordLayer::computerTwoCallOneCallback),
		COMPUTER_TWO_CALLONE,
		nullptr);

	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordLayer::computerTwoCallTwoCallback),
		COMPUTER_TWO_CALLTWO,
		nullptr);

	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordLayer::computerTwoCallThreeCallback),
		COMPUTER_TWO_CALLTHREE,
		nullptr);

	//ע����ʾ�������1�Ľз�״̬��Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordLayer::displayComputerOneCallStateCallback),
		DISPLAY_COMPUTE_ONE_CALLLANDLORD_STATE,
		nullptr);

	//ע����ʾ�������2�Ľз�״̬��Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(CallLandlordLayer::displayComputerTwoCallStateCallback),
		DISPLAY_COMPUTE_TWO_CALLLANDLORD_STATE,
		nullptr);

	return true;
}

void CallLandlordLayer::displayCallLandlordBtnCallback(cocos2d::Ref*)
{
	_btnMenu->setVisible(true);
}

void CallLandlordLayer::displayComputerOneCallStateCallback(cocos2d::Ref*)
{
	auto callScore = ComputerPlayerInstanceOne::getInstance()->getCallScore();
	switch (callScore)
	{
	case 0:
		computerOneCallLandlordState(NOCALLSTATE); 
		break;
	case 1:
		computerOneCallLandlordState(CALLONESTATE);
		break;
	case 2:
		computerOneCallLandlordState(CALLTWOSTATE);
		break;
	case 3:
		computerOneCallLandlordState(CALLTHREESTATE);
		break;
	}
}

void CallLandlordLayer::displayComputerTwoCallStateCallback(cocos2d::Ref*)
{
	auto callScore = ComputerPlayerInstanceTwo::getInstance()->getCallScore();
	switch (callScore)
	{
	case 0:
		computerTwoCallLandlordState(NOCALLSTATE);
		break;
	case 1:
		computerTwoCallLandlordState(CALLONESTATE);
		break;
	case 2:
		computerTwoCallLandlordState(CALLTWOSTATE);
		break;
	case 3:
		computerTwoCallLandlordState(CALLTHREESTATE);
		break;
	}
}

void CallLandlordLayer::holderCallLandlordState(const std::string& name_)
{
	auto spriteFrame = _stateSpriteCache->getSpriteFrameByName(name_);
	CC_ASSERT(spriteFrame != nullptr);
	_holderCallLandlordState->setDisplayFrame(spriteFrame);
	_holderCallLandlordState->setVisible(true);

	_btnMenu->setVisible(false);
}

void CallLandlordLayer::computerOneCallLandlordState(const std::string& name_)
{
	auto spriteFrame = _stateSpriteCache->getSpriteFrameByName(name_);
	//auto spriteFrame = cocos2d::Sprite::createWithSpriteFrameName(NOCALLSTATE)->getSpriteFrame();
	CC_ASSERT(spriteFrame != nullptr);
	_computerOneCallLandlordState->setDisplayFrame(spriteFrame);
	_computerOneCallLandlordState->setVisible(true);
}

void CallLandlordLayer::computerTwoCallLandlordState(const std::string& name_)
{
	auto spriteFrame = _stateSpriteCache->getSpriteFrameByName(name_);
	CC_ASSERT(spriteFrame != nullptr);
	_computerTwoCallLandlordState->setDisplayFrame(spriteFrame);
	_computerTwoCallLandlordState->setVisible(true);
}

void CallLandlordLayer::noCallCallBack(cocos2d::Ref*)
{
	HolderPlayerInstance::getInstance()->setCallScore(0);

	holderCallLandlordState(NOCALLSTATE);

	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_CALL_LANDLORD_INDEX, nullptr);
}

void CallLandlordLayer::callOneCallback(cocos2d::Ref*)
{
	HolderPlayerInstance::getInstance()->setCallScore(1);

	holderCallLandlordState(CALLONESTATE);

	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_CALL_LANDLORD_INDEX, nullptr);
}

void CallLandlordLayer::callTwoCallback(cocos2d::Ref*)
{
	HolderPlayerInstance::getInstance()->setCallScore(2);

	holderCallLandlordState(CALLTWOSTATE);

	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_CALL_LANDLORD_INDEX, nullptr);
}

void CallLandlordLayer::callThreeCallback(cocos2d::Ref*)
{
	HolderPlayerInstance::getInstance()->setCallScore(3);

	holderCallLandlordState(CALLTHREESTATE);

	cocos2d::NotificationCenter::getInstance()->postNotification(UPDATE_CALL_LANDLORD_INDEX, nullptr);
}

void CallLandlordLayer::computerOneNoCallCallback(cocos2d::Ref*)
{
	computerOneCallLandlordState(NOCALLSTATE);
}

void CallLandlordLayer::computerOneCallOneCallback(cocos2d::Ref*)
{
	computerOneCallLandlordState(CALLONESTATE);
}

void CallLandlordLayer::computerOneCallTwoCallback(cocos2d::Ref*)
{
	computerOneCallLandlordState(CALLTWOSTATE);
}

void CallLandlordLayer::computerOneCallThreeCallback(cocos2d::Ref*)
{
	computerOneCallLandlordState(CALLTHREESTATE);
}

void CallLandlordLayer::computerTwoNoCallCallback(cocos2d::Ref*)
{
	computerTwoCallLandlordState(NOCALLSTATE);
}

void CallLandlordLayer::computerTwoCallOneCallback(cocos2d::Ref*)
{
	computerTwoCallLandlordState(CALLONESTATE);
}

void CallLandlordLayer::computerTwoCallTwoCallback(cocos2d::Ref*)
{
	computerTwoCallLandlordState(CALLTWOSTATE);
}

void CallLandlordLayer::computerTwoCallThreeCallback(cocos2d::Ref*)
{
	computerTwoCallLandlordState(CALLTHREESTATE);
}
