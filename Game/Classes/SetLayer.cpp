#include "SetLayer.h"

#include <string>

#include "Common.h"
#include "ScalableMenuItemSprite.h"
#include "util.h"

static const std::string layerName = "setLayer";

using namespace cocos2d;

void SetLayer::createSetLayer()
{
	auto layer = SetLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()
		->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()
			->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()
		->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

bool SetLayer::init()
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

bool SetLayer::initContent()
{
	//������ʼ��
	_musicSlider->setValue(util::MusicUtil::getBgMusicVolume());
	_effectSlider->setValue(util::MusicUtil::getVolume());

	//������������
	_musicSlider->addTargetWithActionForControlEvents(this,
		cccontrol_selector(SetLayer::musicChangedCallback),
		cocos2d::extension::Control::EventType::VALUE_CHANGED);
	_effectSlider->addTargetWithActionForControlEvents(this,
		cccontrol_selector(SetLayer::effectChangedCallback),
		cocos2d::extension::Control::EventType::VALUE_CHANGED);

	//������Ļ�������²㴫��
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(SetLayer::onTouchBegan, this);
	listener->setSwallowTouches(true);	//���ɴ����¼����²㴫��
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	//android�����ؼ��ص�
	auto backListener = cocos2d::EventListenerKeyboard::create();
	backListener->onKeyReleased = CC_CALLBACK_2(SetLayer::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backListener, this);

	return true;
}

void SetLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode_, cocos2d::Event* event_)
{
	//���ؼ��������ͷŲ���
	if (keyCode_ == cocos2d::EventKeyboard::KeyCode::KEY_BACK)
	{
		backCallback(nullptr);
	}
}

bool SetLayer::initView()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	//���͸��������
	auto transparentBg = cocos2d::LayerColor::create(
		cocos2d::ccc4(0x00, 0x00, 0x00, 0xff * 0.5f),
		winSize.width, winSize.height);
	this->addChild(transparentBg);

	//�Ի��򱳾�
	auto dialogBg = cocos2d::ui::Scale9Sprite::create(setDialogBg);
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
	auto dialogBgTop = cocos2d::Sprite::create(setDialogTopBg);
	dialogBgTop->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
	dialogBgTop->setPosition(cocos2d::Point(dialogBgSize.width / 2, dialogBgSize.height - 10));
	dialogBg->addChild(dialogBgTop);

	//��������
	auto titleTTF = cocos2d::LabelTTF::create(util::GBToUTF8("��	��"), "΢���ź�", 34);
	titleTTF->setColor(cocos2d::Color3B(0xff, 0xff, 0xff));
	titleTTF->setPosition(cocos2d::Point(dialogBgTop->getContentSize() / 2));
	dialogBgTop->addChild(titleTTF);

	//���ڹرհ�ť
	auto closeBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(dialogCloseBtn),
		nullptr,
		CC_CALLBACK_1(SetLayer::backCallback, this));
	auto closeBtnPos = cocos2d::Size(dialogBgSize.width - closeBtn->getContentSize().width / 3,
		dialogBgSize.height - closeBtn->getContentSize().height / 3);
	closeBtn->setPosition(cocos2d::Point(closeBtnPos));
	auto closeBtnMenu = cocos2d::Menu::create(closeBtn, nullptr);
	closeBtnMenu->setPosition(cocos2d::Point::ZERO);
	dialogBg->addChild(closeBtnMenu);

	//�Ի����м䱳��
	auto middleBgSprite = cocos2d::ui::Scale9Sprite::create(dialogMiddleBg);
	len = middleBgSprite->getContentSize().width;
	middleBgSprite->setCapInsets(cocos2d::Rect(len / 3, len / 3, len / 3, len / 3));
	middleBgSprite->setContentSize(cocos2d::Size(664, 303));
	middleBgSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	middleBgSprite->setPosition(
		cocos2d::Point(dialogBgSize.width / 2, 111));
	dialogBg->addChild(middleBgSprite);

	//�˳���Ϸ��ť
	auto quitGameBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(setDialogBtn),
		nullptr,
		CC_CALLBACK_1(SetLayer::quitGameCallback, this));
	quitGameBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	quitGameBtn->setPosition(cocos2d::Point(dialogBgSize.width / 4, 30));
	auto quiteGameMenu = cocos2d::Menu::create(quitGameBtn, nullptr);
	quiteGameMenu->setPosition(cocos2d::Point::ZERO);
	dialogBg->addChild(quiteGameMenu);

	//�˳���Ϸ��ť�ı�����
	auto quitGameTTF = cocos2d::LabelTTF::create(util::GBToUTF8("�˳���Ϸ"), "΢���ź�", 32);
	quitGameTTF->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));
	quitGameTTF->setPosition(cocos2d::Point(quitGameBtn->getContentSize() / 2));
	quitGameBtn->addChild(quitGameTTF);

	//�л��˺Ű�ť
	auto switchAccountBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(setDialogBtn),
		nullptr,
		CC_CALLBACK_1(SetLayer::switchAccountCallback, this));
	switchAccountBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	switchAccountBtn->setPosition(cocos2d::Point(dialogBgSize.width * 0.75, 30));
	auto switchAccountMenu = cocos2d::Menu::create(switchAccountBtn, nullptr);
	switchAccountMenu->setPosition(cocos2d::Vec2::ZERO);
	dialogBg->addChild(switchAccountMenu);

	//�л��˺Ű�ť�ص�����
	auto switchAccountTTF = cocos2d::LabelTTF::create(util::GBToUTF8("�л��˺�"), "΢���ź�", 32);
	switchAccountTTF->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));
	switchAccountTTF->setPosition(cocos2d::Point(switchAccountBtn->getContentSize() / 2));
	switchAccountBtn->addChild(switchAccountTTF);

	//����
	auto bgMusic = cocos2d::Sprite::create();
	bgMusic->setPosition(cocos2d::Point(middleBgSprite->getContentSize().width / 2,
		middleBgSprite->getContentSize().height * (2.0f / 3)));
	middleBgSprite->addChild(bgMusic);

	//����ͼ��ͻ�����
	auto musicIcon = cocos2d::Sprite::create(setDialogMusic);
	_musicSlider = cocos2d::extension::ControlSlider::create(
		setDialogTrack, setDialogProgress, setDialogSlider);
	_musicSlider->setMinimumValue(0.0f);
	_musicSlider->setMaximumValue(1.0f);

	auto sliderTotalWidth = musicIcon->getContentSize().width + 30
		+ _musicSlider->getContentSize().width;
	musicIcon->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	musicIcon->setPosition(cocos2d::Point(-sliderTotalWidth / 2.0f, 0));
	bgMusic->addChild(musicIcon);

	_musicSlider->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	_musicSlider->setPosition(cocos2d::Point(
		musicIcon->getPosition().x + musicIcon->getContentSize().width + 30, 0));
	bgMusic->addChild(_musicSlider);

	//��Ч
	auto bgEffect = cocos2d::Sprite::create();
	bgEffect->setPosition(cocos2d::Point(
		middleBgSprite->getContentSize().width / 2.0f,
		middleBgSprite->getContentSize().height * (1.0f / 3)));
	middleBgSprite->addChild(bgEffect);

	//��Чͼ��ͻ�����
	auto effectIcon = cocos2d::Sprite::create(setDialogEffect);
	_effectSlider = cocos2d::extension::ControlSlider::create(
		setDialogTrack, setDialogProgress, setDialogSlider);
	_effectSlider->setMinimumValue(0.0f);
	_effectSlider->setMaximumValue(1.0f);

	effectIcon->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	effectIcon->setPosition(cocos2d::Point(-sliderTotalWidth / 2.0f, 0));
	bgEffect->addChild(effectIcon);

	_effectSlider->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	_effectSlider->setPosition(cocos2d::Point(
		effectIcon->getPosition().x + effectIcon->getContentSize().width + 30, 0));
	bgEffect->addChild(_effectSlider);

	return true;
}

bool SetLayer::onTouchBegan(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_)
{
	return true;
}


void SetLayer::backCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//���ô�����ʧ����
	this->runAction(cocos2d::Sequence::create(
		cocos2d::ScaleTo::create(0.15, 0),
		cocos2d::CallFunc::create(CC_CALLBACK_0(SetLayer::funcBackCallback, this)),
		nullptr));
}

void SetLayer::funcBackCallback()
{
	//�ӵ�ǰ�����Ƴ����öԻ���
	this->removeFromParent();
}

void SetLayer::quitGameCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	cocos2d::Director::getInstance()->end();	//������Ϸ
}

void SetLayer::switchAccountCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//�л���Ϸ�˺Ų���
}

void SetLayer::musicChangedCallback(cocos2d::Ref* sender_, cocos2d::extension::Control::EventType type_)
{
	//������İٷֱȷ����仯ʱ
	if (type_ == cocos2d::extension::ControlSlider::EventType::VALUE_CHANGED)
	{
		auto volumn = _musicSlider->getValue();
		//�������õ�����ֵ
		util::MusicUtil::setBgMusicVolume(volumn);
	}
}

void SetLayer::effectChangedCallback(cocos2d::Ref* sender_, cocos2d::extension::Control::EventType type_)
{
	//������İٷֱȷ����仯ʱ
	if (type_ == cocos2d::extension::ControlSlider::EventType::VALUE_CHANGED)
	{
		auto volumn = _effectSlider->getValue();
		//�������õ���Чֵ
		util::MusicUtil::setVolume(volumn);
	}
}