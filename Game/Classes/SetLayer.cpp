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

	return true;
}

bool SetLayer::initView()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	//添加透明背景层
	auto transparentBg = cocos2d::LayerColor::create(
		cocos2d::ccc4(0x00, 0x00, 0x00, 0xff * 0.5f),
		winSize.width, winSize.height);
	this->addChild(transparentBg);

	//对话框背景
	auto dialogBg = cocos2d::ui::Scale9Sprite::create(setDialogBg);
	auto len = dialogBg->getContentSize().width;
	//设置伸展区域
	dialogBg->setCapInsets(cocos2d::Rect(len / 3, len / 2, len / 3, len / 4));
	dialogBg->setContentSize(cocos2d::Size(720, 480));
	dialogBg->setPosition(cocos2d::Point(winSize.width / 2, winSize.height / 2));
	dialogBg->setScale(0);	//创建时不显示，后面通过代码以动画形式展示
	dialogBg->runAction(cocos2d::EaseBackOut::create(
		cocos2d::ScaleTo::create(0.3, 1.0f)));
	this->addChild(dialogBg, 1);

	auto dialogBgSize = dialogBg->getContentSize();

	//顶部背景
	auto dialogBgTop = cocos2d::Sprite::create(setDialogTopBg);
	dialogBgTop->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_TOP);
	dialogBgTop->setPosition(cocos2d::Point(dialogBgSize.width / 2, dialogBgSize.height - 10));
	dialogBg->addChild(dialogBgTop);

	//顶部标题
	auto titleTTF = cocos2d::LabelTTF::create(util::GBToUTF8("设	置"), "微软雅黑", 34);
	titleTTF->setColor(cocos2d::Color3B(0xff, 0xff, 0xff));
	titleTTF->setPosition(cocos2d::Point(dialogBgTop->getContentSize() / 2));
	dialogBgTop->addChild(titleTTF);

	//窗口关闭按钮
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

	//对话框中间背景
	auto middleBgSprite = cocos2d::ui::Scale9Sprite::create(dialogMiddleBg);
	len = middleBgSprite->getContentSize().width;
	middleBgSprite->setCapInsets(cocos2d::Rect(len / 3, len / 3, len / 3, len / 3));
	middleBgSprite->setContentSize(cocos2d::Size(664, 303));
	middleBgSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	middleBgSprite->setPosition(
		cocos2d::Point(dialogBgSize.width / 2, 111));
	dialogBg->addChild(middleBgSprite);

	//退出游戏按钮
	auto quitGameBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(setDialogBtn),
		nullptr,
		CC_CALLBACK_1(SetLayer::quitGameCallback, this));
	quitGameBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	quitGameBtn->setPosition(cocos2d::Point(dialogBgSize.width / 4, 30));
	auto quiteGameMenu = cocos2d::Menu::create(quitGameBtn, nullptr);
	quiteGameMenu->setPosition(cocos2d::Point::ZERO);
	dialogBg->addChild(quiteGameMenu);

	//退出游戏按钮文本内容
	auto quitGameTTF = cocos2d::LabelTTF::create(util::GBToUTF8("退出游戏"), "微软雅黑", 32);
	quitGameTTF->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));
	quitGameTTF->setPosition(cocos2d::Point(quitGameBtn->getContentSize() / 2));
	quitGameBtn->addChild(quitGameTTF);

	//切换账号按钮
	auto switchAccountBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(setDialogBtn),
		nullptr,
		CC_CALLBACK_1(SetLayer::switchAccountCallback, this));
	switchAccountBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_BOTTOM);
	switchAccountBtn->setPosition(cocos2d::Point(dialogBgSize.width * 0.75, 30));
	auto switchAccountMenu = cocos2d::Menu::create(switchAccountBtn, nullptr);
	switchAccountMenu->setPosition(cocos2d::Vec2::ZERO);
	dialogBg->addChild(switchAccountMenu);

	//切换账号按钮回调函数
	auto switchAccountTTF = cocos2d::LabelTTF::create(util::GBToUTF8("切换账号"), "微软雅黑", 32);
	switchAccountTTF->setColor(cocos2d::Color3B(0x68, 0x2f, 0x2b));
	switchAccountTTF->setPosition(cocos2d::Point(switchAccountBtn->getContentSize() / 2));
	switchAccountBtn->addChild(switchAccountTTF);

	//音乐
	auto bgMusic = cocos2d::Sprite::create();
	bgMusic->setPosition(cocos2d::Point(middleBgSprite->getContentSize().width / 2,
		middleBgSprite->getContentSize().height * (2.0f / 3)));
	middleBgSprite->addChild(bgMusic);

	//音乐图标和滑动条
	auto musicIcon = cocos2d::Sprite::create(setDialogMusic);
	auto musicSlider = cocos2d::extension::ControlSlider::create(
		setDialogTrack, setDialogProgress, setDialogSlider);
	musicSlider->setMinimumValue(0.0f);
	musicSlider->setMaximumValue(1.0f);

	auto sliderTotalWidth = musicIcon->getContentSize().width + 30
		+ musicSlider->getContentSize().width;
	musicIcon->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	musicIcon->setPosition(cocos2d::Point(-sliderTotalWidth / 2.0f, 0));
	bgMusic->addChild(musicIcon);

	musicSlider->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	musicSlider->setPosition(cocos2d::Point(
		musicIcon->getPosition().x + musicIcon->getContentSize().width + 30, 0));
	bgMusic->addChild(musicSlider);

	//音效
	auto bgEffect = cocos2d::Sprite::create();
	bgEffect->setPosition(cocos2d::Point(
		middleBgSprite->getContentSize().width / 2.0f,
		middleBgSprite->getContentSize().height * (1.0f / 3)));
	middleBgSprite->addChild(bgEffect);

	//音效图标和滑动条
	auto effectIcon = cocos2d::Sprite::create(setDialogEffect);
	auto effectSlider = cocos2d::extension::ControlSlider::create(
		setDialogTrack, setDialogProgress, setDialogSlider);
	effectSlider->setMinimumValue(0.0f);
	effectSlider->setMaximumValue(1.0f);

	effectIcon->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	effectIcon->setPosition(cocos2d::Point(-sliderTotalWidth / 2.0f, 0));
	bgEffect->addChild(effectIcon);

	effectSlider->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE_LEFT);
	effectSlider->setPosition(cocos2d::Point(
		effectIcon->getPosition().x + effectIcon->getContentSize().width + 30, 0));
	bgEffect->addChild(effectSlider);

	return true;
}

void SetLayer::backCallback(cocos2d::Ref* sender_)
{

}

void SetLayer::quitGameCallback(cocos2d::Ref* sender_)
{

}

void SetLayer::switchAccountCallback(cocos2d::Ref* sender_)
{

}

