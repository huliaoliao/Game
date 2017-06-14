#include "CustomServiceLayer.h"

#include <string>

#include "Common.h"
#include "ScalableMenuItemSprite.h"
#include "ui/UIScale9Sprite.h"
#include "Util.h"

static const std::string layerName = "feedbackLayer";

void CustomServiceLayer::createLayer()
{
	auto layer = CustomServiceLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()
		->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()
			->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()
		->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

bool CustomServiceLayer::init()
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

	if (initContent() == false)
	{
		return false;
	}

	//������Ļ�������²㴫��
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(CustomServiceLayer::onTouchBegan, this);
	listener->setSwallowTouches(true);	//���ɴ����¼����²㴫��
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//android�����ؼ�
	auto backListener = cocos2d::EventListenerKeyboard::create();
	backListener->onKeyReleased = CC_CALLBACK_2(CustomServiceLayer::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backListener, this);

	return true;
}

bool CustomServiceLayer::initView()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	//���͸��������
	auto transparentBg = cocos2d::LayerColor::create(
		cocos2d::ccc4(0x00, 0x00, 0x00, 0xff * 0.5f),
		winSize.width, winSize.height);
	this->addChild(transparentBg);

	//�Ի��򱳾�
	auto dialogBg = cocos2d::ui::Scale9Sprite::create(dialogBgImage);
	auto len = dialogBg->getContentSize().width;
	//������չ����
	dialogBg->setCapInsets(cocos2d::Rect(len / 3, len / 2, len / 3, len / 4));
	dialogBg->setContentSize(cocos2d::Size(720, 480));
	dialogBg->setPosition(cocos2d::Point(winSize.width / 2, winSize.height / 2));
	dialogBg->setScale(0);	//����ʱ����ʾ������ͨ�������Զ�����ʽչʾ
	dialogBg->runAction(cocos2d::EaseBackOut::create(
		cocos2d::ScaleTo::create(0.3, 1.0f)));
	this->addChild(dialogBg, 1);

	auto dialogBgSize = dialogBg->getContentSize();

	//��������
	auto dialogBgTop = cocos2d::Sprite::create(dialogTopBgImage);
	dialogBgTop->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
	dialogBgTop->setPosition(cocos2d::Point(dialogBgSize.width / 2, dialogBgSize.height - 10));
	dialogBg->addChild(dialogBgTop);

	//��������
	auto titleTTF = cocos2d::LabelTTF::create(util::GBToUTF8("�ͷ�"), "Arial", 34);
	titleTTF->setColor(cocos2d::Color3B(0xff, 0xff, 0xff));
	titleTTF->setPosition(cocos2d::Point(dialogBgTop->getContentSize() / 2));
	dialogBgTop->addChild(titleTTF);

	//���ڹرհ�ť
	auto closeBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(dialogCloseBtn),
		nullptr,
		CC_CALLBACK_1(CustomServiceLayer::backCallback, this));
	auto closeBtnPos = cocos2d::Size(dialogBgSize.width - closeBtn->getContentSize().width / 3,
		dialogBgSize.height - closeBtn->getContentSize().height / 3);
	closeBtn->setPosition(cocos2d::Point(closeBtnPos));
	auto closeBtnMenu = cocos2d::Menu::create(closeBtn, nullptr);
	closeBtnMenu->setPosition(cocos2d::Point::ZERO);
	dialogBg->addChild(closeBtnMenu);

	//�Ի����м䱳��
	_middleBgSprite = cocos2d::ui::Scale9Sprite::create(dialogMiddleBgImage);
	len = _middleBgSprite->getContentSize().width;
	_middleBgSprite->setCapInsets(cocos2d::Rect(len / 3, len / 3, len / 3, len / 3));
	_middleBgSprite->setContentSize(cocos2d::Size(664, 303));
	_middleBgSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_middleBgSprite->setPosition(
		cocos2d::Point(dialogBgSize.width / 2, 111));
	dialogBg->addChild(_middleBgSprite);

	//����ͷ��绰��ť
	auto callCustomServiceBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(DIALOG_BTN),
		nullptr,
		CC_CALLBACK_1(CustomServiceLayer::callServiceCallback, this));
	callCustomServiceBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	callCustomServiceBtn->setPosition(cocos2d::Point(dialogBgSize.width / 4, 30));
	auto callCustomServiceMenu = cocos2d::Menu::create(callCustomServiceBtn, nullptr);
	callCustomServiceMenu->setPosition(cocos2d::Point::ZERO);
	dialogBg->addChild(callCustomServiceMenu);

	//����ͷ��绰��ť�ı�����
	auto callCustomServiceTTF = cocos2d::LabelTTF::create(util::GBToUTF8("����绰"), "Arial", 32);
	callCustomServiceTTF->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));
	callCustomServiceTTF->setPosition(cocos2d::Point(callCustomServiceBtn->getContentSize() / 2));
	callCustomServiceBtn->addChild(callCustomServiceTTF);

	//���������ť
	auto feedbackBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(DIALOG_BTN),
		nullptr,
		CC_CALLBACK_1(CustomServiceLayer::feedbackCallback, this));
	feedbackBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	feedbackBtn->setPosition(cocos2d::Point(dialogBgSize.width * 0.75, 30));
	auto feedbackMenu = cocos2d::Menu::create(feedbackBtn, nullptr);
	feedbackMenu->setPosition(cocos2d::Vec2::ZERO);
	dialogBg->addChild(feedbackMenu);

	//���������ť�ı�����
	auto feedbackTTF = cocos2d::LabelTTF::create(util::GBToUTF8("�������"), "Arial", 32);
	feedbackTTF->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));
	feedbackTTF->setPosition(cocos2d::Point(feedbackBtn->getContentSize() / 2));
	feedbackBtn->addChild(feedbackTTF);

	return true;
}

bool CustomServiceLayer::initContent()
{
	//�ͷ�QQ
	std::string textAccount = "�ͷ�QQ��123456789";
	auto QQInfoTtf = cocos2d::LabelTTF::create(util::GBToUTF8(textAccount.c_str()), "", 30);
	QQInfoTtf->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));

	//�ͷ��绰
	std::string textPwd = "�ͷ��绰��123456789";
	auto showTextPwdTtf = cocos2d::LabelTTF::create(util::GBToUTF8(textPwd.c_str()), "", 30);
	showTextPwdTtf->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));

	auto width = std::max(QQInfoTtf->getContentSize().width, showTextPwdTtf->getContentSize().width);
	auto height = QQInfoTtf->getContentSize().height + showTextPwdTtf->getContentSize().height + 20;

	auto contentBg = cocos2d::Sprite::create();
	contentBg->setContentSize(cocos2d::Size(width, height));
	QQInfoTtf->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
	QQInfoTtf->setPosition(cocos2d::Point(width / 2, height));
	showTextPwdTtf->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	showTextPwdTtf->setPosition(cocos2d::Point(width / 2, 0));
	contentBg->addChild(QQInfoTtf);
	contentBg->addChild(showTextPwdTtf);

	contentBg->setPosition(_middleBgSprite->getContentSize() / 2);
	_middleBgSprite->addChild(contentBg);

	return true;
}

bool CustomServiceLayer::onTouchBegan(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_)
{
	return true;
}

void CustomServiceLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode_, cocos2d::Event* event_)
{
	//���ؼ��������ͷŲ���
	if (keyCode_ == cocos2d::EventKeyboard::KeyCode::KEY_BACK)
	{
		backCallback(nullptr);
	}
}

void CustomServiceLayer::backCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//���ô�����ʧ����
	this->runAction(cocos2d::Sequence::create(
		cocos2d::ScaleTo::create(0.15, 0),
		cocos2d::CallFunc::create(CC_CALLBACK_0(CustomServiceLayer::funcBackCallback, this)),
		nullptr));
}

void CustomServiceLayer::funcBackCallback()
{
	//�ӵ�ǰ�����Ƴ����öԻ���
	this->removeFromParent();
}

void CustomServiceLayer::callServiceCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//����ͷ��绰��ť�ص�
}

void CustomServiceLayer::feedbackCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//���������ť�ص�
}
