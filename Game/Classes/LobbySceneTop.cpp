#include "LobbySceneTop.h"

#include "Common.h"
#include "ScalableMenuItemSprite.h"
#include "ui/UIScale9Sprite.h"
#include "Util.h"

bool LobbySceneTop::init()
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

bool LobbySceneTop::initView()
{
	//��������
	auto topBg = cocos2d::ui::Scale9Sprite::create("lobby/lobby_top_bg.png");
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	topBg->setContentSize(cocos2d::Size(winSize.width, 100));
	topBg->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	topBg->setPosition(cocos2d::Point(0, winSize.height));
	this->addChild(topBg, 0);

	//ͷ�񱳾�����
	auto headBgSprite = cocos2d::ui::Scale9Sprite::create("lobby/head_box.png");
	const auto headBgScale = cocos2d::Size(0.54, 0.54);
	headBgSprite->setContentSize(cocos2d::Size(148 * 0.54, 148 * 0.54));
	headBgSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	headBgSprite->setPosition(cocos2d::Vec2(10, topBg->getContentSize().height / 2));
	topBg->addChild(headBgSprite);

	//ͷ��
	auto headSprite = cocos2d::Sprite::create("lobby/head.png");
	headSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	auto headScaleX = headSprite->getContentSize().width * headBgScale.width / headBgSprite->getContentSize().width;
	auto headScaleY = headSprite->getContentSize().height * headBgScale.height / headBgSprite->getContentSize().height;
	headSprite->setScaleX(headScaleX + 0.05);
	headSprite->setScaleY(headScaleY + 0.05);
	headSprite->setPosition(cocos2d::Point(headBgSprite->getContentSize() / 2));
	headBgSprite->addChild(headSprite, -1);	//��ͷ�������ͷ�����

	//�������
	std::string playerName = util::StrongGBToUTF8("��˿����");
	auto playerNameText = cocos2d::LabelTTF::create(playerName, "΢���ź�", 18);
	playerNameText->setColor(cocos2d::Color3B(0xF4, 0xE0, 0xDF));
	playerNameText->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	playerNameText->setPosition(cocos2d::Point(headBgSprite->getPosition()) +
		cocos2d::Size(headBgSprite->getContentSize().width + 5, 30));
	topBg->addChild(playerNameText);

	//���ID
	auto playerID = "ID:123456";
	auto playerIDText = cocos2d::LabelTTF::create(playerID, "΢���ź�", 18);
	playerIDText->setColor(cocos2d::Color3B(0xF4, 0xE0, 0xDF));
	playerIDText->setAnchorPoint(cocos2d::Vec2::ANCHOR_TOP_LEFT);
	playerIDText->setPosition(playerNameText->getPosition() + 
		cocos2d::Size(0, -30));
	topBg->addChild(playerIDText);

	//��������
	auto lobbyLogoBg = cocos2d::Sprite::create("lobby/slogan_bg.png");
	lobbyLogoBg->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	lobbyLogoBg->setPosition(cocos2d::Point(topBg->getContentSize().width / 2, 0));
	topBg->addChild(lobbyLogoBg);
	auto lobbyLogo = cocos2d::Sprite::create("lobby/slogan.png");
	lobbyLogo->setPosition(cocos2d::Point(lobbyLogoBg->getContentSize() / 2));
	lobbyLogoBg->addChild(lobbyLogo);

	//�������ð�ť
	auto setBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create("lobby/setting.png"),
		nullptr,
		CC_CALLBACK_1(LobbySceneTop::lobbySetCallback, this));
	auto topBgSize = topBg->getContentSize();
	setBtn->setPosition(cocos2d::Vec2(topBgSize.width - topBgSize.width / 3 / 6,
		topBgSize.height / 2));

	//��Ϸ����ť
	auto ruleBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create("lobby/rule.png"),
		nullptr,
		CC_CALLBACK_1(LobbySceneTop::lobbyRuleCallback, this));
	ruleBtn->setPosition(cocos2d::Vec2(topBgSize.width  - topBgSize.width / 3 / 2,
		topBgSize.height / 2));

	//������ť
	auto feedbackBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create("lobby/feedback.png"),
		nullptr,
		CC_CALLBACK_1(LobbySceneTop::lobbyFeedbackCallback, this));
	feedbackBtn->setPosition(cocos2d::Point(topBgSize.width - topBgSize.width / 3 * 5 / 6,
		topBgSize.height / 2));
	
	//��ť֮��ķָ���
	auto btnLine1 = cocos2d::Sprite::create("lobby/lobby_btn_line.png");
	auto btnLine2 = cocos2d::Sprite::create("lobby/lobby_btn_line.png");
	auto btnLine1PosX = (setBtn->getPosition().x + ruleBtn->getPosition().x) / 2;
	auto btnLine2PosX = (ruleBtn->getPosition().x + feedbackBtn->getPosition().x) / 2;
	btnLine1->setPosition(cocos2d::Point(btnLine1PosX, ruleBtn->getPositionY()));
	btnLine2->setPosition(cocos2d::Point(btnLine2PosX, ruleBtn->getPositionY()));
	topBg->addChild(btnLine1);
	topBg->addChild(btnLine2);

	//��MenuItemSprite���ӵ�Menu��
	auto menu = cocos2d::Menu::create(setBtn, ruleBtn, feedbackBtn, nullptr);
	menu->setPosition(cocos2d::Point::ZERO);	//û�д��У�λ�û�������
	topBg->addChild(menu);

	return true;
}

void LobbySceneTop::lobbySetCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//ת�����ý���
}

void LobbySceneTop::lobbyRuleCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//ת��������
}

void LobbySceneTop::lobbyFeedbackCallback(cocos2d::Ref* sender_)
{
	util::MusicUtil::playEffectMusic(pressBtnMusic);
	//ת��������
}