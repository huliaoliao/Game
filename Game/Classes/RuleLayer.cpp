#include "RuleLayer.h"

#include <string>

#include "Common.h"
#include "ScalableMenuItemSprite.h"
#include "ui/UIListView.h"
#include "ui/UIScale9Sprite.h"
#include "Util.h"

static const std::string layerName = "ruleLayer";

void RuleLayer::createLayer()
{
	auto layer = RuleLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

bool RuleLayer::init()
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

bool RuleLayer::initView()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	//͸��������
	auto transparentBg = cocos2d::LayerColor::create(
		cocos2d::ccc4(0x00, 0x00, 0x00, 0xff * 0.5f),
		winSize.width, winSize.height);
	this->addChild(transparentBg);

	//�Ի��򱳾�
	auto dialogBg = cocos2d::ui::Scale9Sprite::create(dialogBgImage);
	auto len = dialogBg->getContentSize().width;
	dialogBg->setCapInsets(cocos2d::Rect(len / 3, len / 2, len / 3, len / 4));
	dialogBg->setContentSize(cocos2d::Size(DIALOG_WIDTH, DIALOG_HEIGHT));
	dialogBg->setPosition(cocos2d::Point(winSize.width / 2, winSize.height / 2));
	dialogBg->setScale(0.0f);	//����ʱ����ʾ�������д���ʵ�ֶ���Ч��
	dialogBg->runAction(cocos2d::EaseBackOut::create(
		cocos2d::ScaleTo::create(0.3, 1.0f))); 
	this->addChild(dialogBg);

	//�Ի��򶥲�����
	auto dialogTopBg = cocos2d::Sprite::create(dialogTopBgImage);
	dialogTopBg->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
	dialogTopBg->setPosition(cocos2d::Point(dialogBg->getContentSize().width / 2, 
		dialogBg->getContentSize().height - 10));
	dialogBg->addChild(dialogTopBg);

	//�Ի��򶥲�����
	auto dialogTitleTTF = cocos2d::LabelTTF::create(util::GBToUTF8("�淨˵��"), "΢���ź�", 34);
	dialogTitleTTF->setColor(cocos2d::Color3B(0xff, 0xff, 0xff));
	dialogTitleTTF->setPosition(cocos2d::Point(dialogTopBg->getContentSize() / 2));
	dialogTopBg->addChild(dialogTitleTTF);

	//���ڹرհ�ť
	auto closeBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(dialogCloseBtn),
		nullptr,
		CC_CALLBACK_1(RuleLayer::backCallback, this));
	auto closeBtnPos = cocos2d::Point(dialogBg->getContentSize().width - closeBtn->getContentSize().width / 3,
		dialogBg->getContentSize().height - closeBtn->getContentSize().height / 3);
	closeBtn->setPosition(closeBtnPos);
	auto closeBtnMenu = cocos2d::Menu::create(closeBtn, nullptr);
	closeBtnMenu->setPosition(cocos2d::Point::ZERO);
	dialogBg->addChild(closeBtnMenu);

	//�ײ�OK��ť
	auto btnOK = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(dialogBtnImage),
		nullptr,
		CC_CALLBACK_1(RuleLayer::backCallback, this));
	btnOK->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	btnOK->setPosition(cocos2d::Point(dialogBg->getContentSize().width / 2, 30));
	auto btnOkMenu = cocos2d::Menu::create(btnOK, nullptr);
	btnOkMenu->setPosition(cocos2d::Point::ZERO);
	dialogBg->addChild(btnOkMenu);

	//OK��ť��������
	auto btnTTF = cocos2d::LabelTTF::create(util::GBToUTF8("ȷ ��"), "΢���ź�", 34);
	btnTTF->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));
	btnTTF->setPosition(btnOK->getContentSize() / 2);
	btnOK->addChild(btnTTF);

	//�Ի����м�ı���
	_dialogMiddleBg = cocos2d::ui::Scale9Sprite::create(dialogMiddleBgImage);
	_dialogMiddleBg->setContentSize(cocos2d::Size(664, 300));
	_dialogMiddleBg->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	_dialogMiddleBg->setPosition(cocos2d::Point(dialogBg->getContentSize().width / 2,
		btnOK->getPosition().y + btnOK->getContentSize().height + 10));
	dialogBg->addChild(_dialogMiddleBg);

	return true;
}

bool RuleLayer::initContent()
{
	if (initListView() == false)
	{
		return false;
	}

	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->onTouchBegan = CC_CALLBACK_2(RuleLayer::onTouchBegan, this);
	listener->setSwallowTouches(true);	////���ɴ����¼����²㴫��
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	////android�����ؼ�
	auto backListener = cocos2d::EventListenerKeyboard::create();
	backListener->onKeyReleased = CC_CALLBACK_2(RuleLayer::onKeyReleased, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(backListener, this);

	return true;
}

bool RuleLayer::initListView()
{
	auto ruleListView = cocos2d::ui::ListView::create();
	ruleListView->setDirection(cocos2d::ui::ScrollView::Direction::VERTICAL);	//����ListView����Ϊ��ֱ
	ruleListView->setContentSize(cocos2d::Size(_dialogMiddleBg->getContentSize().width - 5,
		_dialogMiddleBg->getContentSize().height - 10));	//����ListView��С
	ruleListView->setBounceEnabled(true);	//����ListView�����������ߵײ�ʱ�Ļص�Ч��
	ruleListView->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	ruleListView->setPosition(cocos2d::Point(5, _dialogMiddleBg->getContentSize().height - 5));
	//����ListView������
	ruleListView->addEventListener((cocos2d::ui::ListView::ccListViewCallback)CC_CALLBACK_2(
		RuleLayer::selectedItemEvent, this));
	ruleListView->addEventListener((cocos2d::ui::ListView::ccScrollViewCallback)CC_CALLBACK_2(
		RuleLayer::selectedItemEventScrollView, this));
	ruleListView->setGravity(cocos2d::ui::ListView::Gravity::CENTER_HORIZONTAL);
	_dialogMiddleBg->addChild(ruleListView, 2);

	const std::string rule = "��Ϸ����˵��";
	auto ruleTTF = cocos2d::LabelTTF::create(util::GBToUTF8(rule.c_str()), "΢���ź�", 30);
	ruleTTF->setDimensions(cocos2d::Size(ruleListView->getContentSize().width, 
		ruleTTF->getContentSize().height));	//����������ʾ����
	ruleTTF->setHorizontalAlignment(cocos2d::TextHAlignment::LEFT);//�����
	ruleTTF->setColor(cocos2d::Color3B(0x45, 0x1d, 0x15));

	//ruleTTF���������layout�У�layout������ListView��
	auto layout = cocos2d::ui::Layout::create();
	layout->setContentSize(ruleTTF->getContentSize());
	ruleTTF->setAnchorPoint(cocos2d::Vec2::ANCHOR_BOTTOM_LEFT);
	layout->setPosition(cocos2d::Point::ZERO);
	layout->addChild(ruleTTF);
	ruleListView->addChild(layout);

	return true;
}

bool RuleLayer::onTouchBegan(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_)
{
	return true;
}

void RuleLayer::onKeyReleased(cocos2d::EventKeyboard::KeyCode keyCode_, cocos2d::Event* event_)
{
	//����
	if (keyCode_ == cocos2d::EventKeyboard::KeyCode::KEY_BACK)
	{
		backCallback(nullptr);
	}
}

void RuleLayer::backCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//���ô�����ʧ����
	this->runAction(cocos2d::Sequence::create(
		cocos2d::ScaleTo::create(0.15, 0),
		cocos2d::CallFunc::create(CC_CALLBACK_0(RuleLayer::funcBackCallback, this)),
		nullptr));
}

void RuleLayer::funcBackCallback()
{
	//�ӵ�ǰ�����Ƴ����öԻ���
	this->removeFromParent();
}

void RuleLayer::selectedItemEvent(cocos2d::Ref* sender_, cocos2d::ui::ListView::EventType type_)
{
	switch (type_){
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_START:
	{
		break;
	}
	case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
	{
		break;
	}
	default:
		break;
	}
}

void RuleLayer::selectedItemEventScrollView(cocos2d::Ref* sender_, cocos2d::ui::ScrollView::EventType type_)
{
	switch (type_) {
	case cocos2d::ui::ScrollView::EventType::BOUNCE_BOTTOM:
	{
		break;
	}
	case cocos2d::ui::ScrollView::EventType::BOUNCE_TOP:
	{
		break;
	}
	default:
		break;
	}
}