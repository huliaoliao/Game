#include "PokerLayer.h"

#include "Common.h"
#include "Poker.h"
#include "PokerController.h"
#include "ScalableMenuItemSprite.h"

const std::string layerName = "pokerLayer";

const float MIMIUM_CARDS_OVERLAPWIDTH = 20.0f;

void PokerLayer::createLayer()
{
	auto layer = PokerLayer::create();
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
	cocos2d::Director::getInstance()->getRunningScene()->addChild(layer, COMMON_DIALOG_ZORDER, layerName);
}

void PokerLayer::destroyLayer()
{
	if (cocos2d::Director::getInstance()->getRunningScene()->getChildByName(layerName))
	{
		cocos2d::Director::getInstance()->getRunningScene()->removeChildByName(layerName);
	}
}

bool PokerLayer::init()
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

	if (initListener() == false)
	{
		return false;
	}

	return true;
}

bool PokerLayer::initView()
{
	auto winSize = cocos2d::Director::getInstance()->getWinSize();
	const auto computerOnePos = cocos2d::Point(winSize.width * 0.8, winSize.height * 0.72);
	const auto computerTwoPos = cocos2d::Point(winSize.width * 0.2, winSize.height * 0.72);
	const auto holderPos = cocos2d::Point(winSize.width * 0.2, winSize.height * 0.4);

	_holderPassSprite = cocos2d::Sprite::create(PASS_IMAGE);
	_holderPassSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_holderPassSprite->setPosition(holderPos);
	_holderPassSprite->setVisible(false);	//初始不显示
	this->addChild(_holderPassSprite);

	_computerOnePassSprite = cocos2d::Sprite::create(PASS_IMAGE);
	_computerOnePassSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_computerOnePassSprite->setPosition(computerOnePos);
	_computerOnePassSprite->setVisible(false);
	this->addChild(_computerOnePassSprite);

	_computerTwoPassSprite = cocos2d::Sprite::create(PASS_IMAGE);
	_computerTwoPassSprite->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	_computerTwoPassSprite->setPosition(computerTwoPos);
	_computerTwoPassSprite->setVisible(false);
	this->addChild(_computerTwoPassSprite);

	//出牌相关按钮（不出，出牌，提示，没有牌打得过上家）
	const auto btnInterval = 10.0f;
	const auto btnWidth = cocos2d::Sprite::create(PASS_BTN)->getContentSize().width;
	const auto btnPos = cocos2d::Point(winSize.width * 0.5f, winSize.height * 0.35);
	//不出按钮
	auto passBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(PASS_BTN),
		nullptr,
		CC_CALLBACK_1(PokerLayer::passBtnCallback, this));
	passBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	passBtn->setPosition(cocos2d::Point(btnPos.x - btnWidth - btnInterval, btnPos.y));

	//提示按钮
	auto hintBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(HINT_BTN),
		nullptr,
		CC_CALLBACK_1(PokerLayer::hintBtnCallback, this));
	hintBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	hintBtn->setPosition(cocos2d::Point(btnPos.x, btnPos.y));
	hintBtn->setDisabledImage(cocos2d::Sprite::create(HINT_DISABLE_BTN));	//提示按钮不可按状态
	hintBtn->setEnabled(false);	//提示按钮开始不可点击

	//出牌按钮
	auto outPokersBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(OUTPOKER_BTN),
		nullptr,
		CC_CALLBACK_1(PokerLayer::outPokersBtnCallback, this));
	outPokersBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	outPokersBtn->setPosition(cocos2d::Point(btnPos.x + btnWidth + btnInterval, btnPos.y));
	outPokersBtn->setDisabledImage(cocos2d::Sprite::create(OUTPOKER_DISABLE_BTN));	//出牌按钮不可按状态
	outPokersBtn->setEnabled(false);

	_btnMenu = cocos2d::Menu::create(passBtn, hintBtn, outPokersBtn, nullptr);
	_btnMenu->setPosition(cocos2d::Point::ZERO);
	this->addChild(_btnMenu);

	return true;
}

bool PokerLayer::initContent()
{
	//注册显示手动玩家手中的牌消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayHolderPokersCallback, this),
		DISPLAY_HOLDER_POKERS,
		nullptr);

	//注册显示预留给地主的牌消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayLandlordPokersCallback, this),
		DISPLAY_LANDLORD_POKERS,
		nullptr);

	//注册销毁手动玩家上一手打出的牌消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::destroyHolderLastOutPokersCallback, this),
		DESTROY_LAST_HOLDER_OUTPOKERS,
		nullptr);

	//注册显示玩家该局打出的牌消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayHolderOutPokersCallbacl, this),
		DISPLAY_HOLDER_OUTPOKERS,
		nullptr);

	//注册销毁电脑玩家1上一手打出的牌消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::destroyComputerOneLastOutPokersCallback, this),
		DESTROY_LAST_COMPUTER_ONE_OUTPOKERS,
		nullptr);

	//注册显示电脑玩家1该局打出的牌消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayComputerOneOutPokersCallback, this),
		DISPLAY_COMPUTER_ONE_OUTPOKERS,
		nullptr);

	//注册销毁电脑玩家2上一手打出的牌的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::destroyComputerTwoLastOutPokersCallback, this),
		DESTROY_LAST_COMPUTER_TWO_OUTPOKERS,
		nullptr);

	//注册显示电脑玩家2该局打出的牌的消息
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayComputerTwoOutPokersCallback, this),
		DISPLAY_COMPUTER_TWO_OUTPOKERS,
		nullptr);

	return true;
}

bool PokerLayer::initListener()
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);	//吞噬，避免上层触摸操作捕获后再传递给下层

	listener->onTouchBegan = CC_CALLBACK_2(PokerLayer::onTouchBegan, this);
	listener->onTouchMoved = CC_CALLBACK_2(PokerLayer::onTouchMoved, this);
	listener->onTouchEnded = CC_CALLBACK_2(PokerLayer::onTouchEnded, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);

	return true;
}

bool PokerLayer::onTouchBegan(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_)
{
	auto holderPokerSprites = _lastHolderPokerSprites;

	auto touchPos = this->convertToNodeSpace(touch_->getLocation());
	for (int i = holderPokerSprites.size() - 1; i >= 0; --i)
	{
		auto rect = holderPokerSprites.at(i)->getBoundingBox();
		if (holderPokerSprites.at(i)->getCanClick() && rect.containsPoint(touchPos))
		{
			//播放选牌的音效

			_holderClickedPokerSprites.push_back(holderPokerSprites.at(i));
			if (!holderPokerSprites.at(i)->getIsSelected())
			{
				//如果还未选择这张牌，那就将这张牌露出来
				holderPokerSprites.at(i)->selectedPokersOut();
			}
			else
			{
				//否则这张牌已经被选择，将其放回
				holderPokerSprites.at(i)->selectedPokerBack();
			}

			//检测当前选择的牌是否可以令出牌按钮可按

			return true;
		}
	}

	//如果点击下的位置不在扑克范围内，那么即使触摸移动后也不会有任何操作
	return false;
}

void PokerLayer::onTouchMoved(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_)
{
	auto pokerSprites = _lastHolderPokerSprites;

	auto touchPos = this->convertToNodeSpace(touch_->getLocation());
	for (int i = pokerSprites.size() - 1; i >= 0; --i)
	{
		auto rect = pokerSprites.at(i)->getBoundingBox();
		if (pokerSprites.at(i)->getCanClick() && rect.containsPoint(touchPos))
		{
			//当前点击的牌是否是在已经选择的牌集合内，如果在，那么直接结束循环
			bool isInClickedPokerSprites = false;
			for (int k = 0; k < _holderClickedPokerSprites.size(); ++k)
			{
				if (pokerSprites.at(i) == _holderClickedPokerSprites.at(k))
				{
					isInClickedPokerSprites = true;
					break;
				}
			}
			if (isInClickedPokerSprites)
			{
				break;
			}

			//播放点击牌的音效
			//TODO

			_holderClickedPokerSprites.push_back(pokerSprites.at(i));
			if (!pokerSprites.at(i)->getIsSelected())
			{
				//如果还未选择这张牌，那就将这张牌露出来
				pokerSprites.at(i)->selectedPokersOut();
			}
			else
			{
				//否则这张牌已经被选择，将其放回
				pokerSprites.at(i)->selectedPokerBack();
			}

			//检测当前牌是否可以另出牌按钮可按
			//TODO

			break;
		}
	}
}

void PokerLayer::onTouchEnded(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_)
{
	//触摸结束，清空clickedPokers
	_holderClickedPokerSprites.clear();
}

std::vector<PokerSprite*> PokerLayer::createPokerSprites(cocos2d::Ref* sender_)
{
	const auto pokers = *reinterpret_cast<cocos2d::Vector<Poker*>*>(sender_);

	//由于一个Sprite不能被addChild两次，这里将显示的地主预留牌精灵或者打出的牌设置成一个clone获得的值
	const auto tmp = PokerController::getInstance()->genPokerSprites(pokers);
	std::vector<PokerSprite*> pokerSprites;
	for (int i = 0; i < tmp.size(); ++i)
	{
		pokerSprites.push_back(tmp.at(i)->clone());
	}

	return pokerSprites;
}

void PokerLayer::displayPokers(const std::vector<PokerSprite*>& pokers_, float displayMaxWidth_,
	float displayStartX_, float displayMiddleX_, float displayY_, bool isOnScene_, const float SCALE /*= 1.0f*/)
{
	if (pokers_.size() == 0)
	{
		return;
	}

	int pokersNum = pokers_.size();
	float pokerWidth = pokers_.front()->getContentSize().width * SCALE;
	float pokerHeight = pokers_.front()->getContentSize().height * SCALE;
	//两张牌之间的最大间隙
	float	maxIntervalBetweenPokers = pokerWidth - MIMIUM_CARDS_OVERLAPWIDTH * SCALE;
	float intervalBetweenPokers = (displayMaxWidth_ - pokerWidth) < maxIntervalBetweenPokers * (pokersNum - 1) ?
		(displayMaxWidth_ - pokerWidth) / (pokersNum - 1) : maxIntervalBetweenPokers;

	//卡牌之间的间隙达到最大时，需要以显示区中点展开显示，不然整体的显示会左偏，造成视觉问题
	if (intervalBetweenPokers == maxIntervalBetweenPokers)
	{
		// 		displayStartX_ = pokersNum % 2 == 0 ?
		// 			displayMiddleX_ - (pokersNum / 2) * intervalBetweenPokers :
		// 			displayMiddleX_ - (pokersNum / 2 + 0.5) * intervalBetweenPokers;
		auto totalPokersWidth = (pokersNum - 1) * intervalBetweenPokers + pokerWidth;
		displayStartX_ = displayMiddleX_ - totalPokersWidth / 2.0f;
	}

	//显示卡牌
	for (int i = 0; i < pokersNum; ++i)
	{
		if (isOnScene_ == false)	//手动玩家持有的牌
		{
			this->addChild(pokers_.at(i));
		}
		else
		{
			displayY_ = pokers_.at(i)->getPosition().y;	//针对待出的牌
		}
		pokers_.at(i)->setScale(SCALE);
		pokers_.at(i)->setVisible(true);
		pokers_.at(i)->setPosition(cocos2d::Point(displayStartX_ + pokerWidth / 2 + i * intervalBetweenPokers,
			displayY_));
	}
}

void PokerLayer::displayHolderPokersCallback(cocos2d::Ref* sender_)
{
	const auto pokers = *reinterpret_cast<cocos2d::Vector<Poker*>*>(sender_);

	//两次无变化，直接返回
	if (_lastHolderPokerSprites.size() == pokers.size())
	{
		return;
	}

	for (int i = 0; i < pokers.size(); ++i)
	{
		cocos2d::log("%d : %d\n", pokers.at(i)->type, pokers.at(i)->value);
	}
	const auto pokerSprites = PokerController::getInstance()->genPokerSprites(pokers);

	//需要将上次显示的牌给销毁
	for (int i = 0; i < _lastHolderPokerSprites.size(); ++i)
	{
		_lastHolderPokerSprites.at(i)->removeFromParent();
	}
	_lastHolderPokerSprites = pokerSprites;

	const auto winSize = cocos2d::Director::getInstance()->getWinSize();
	float displayPokerMaxWidth =  winSize.width * 5.0 / 6.0;
	float displayPokerMiddleX = winSize.width / 2;
	float displayPokerStartX = displayPokerMiddleX - displayPokerMaxWidth / 2;
	float displayPokerY = pokerSprites.front()->getContentSize().height / 2 + 25;//winSize.height * 0.2;
	displayPokers(pokerSprites, displayPokerMaxWidth, displayPokerStartX, displayPokerMiddleX,
		displayPokerY, false);
}

void PokerLayer::displayLandlordPokersCallback(cocos2d::Ref* sender_)
{
	auto pokerSprites = createPokerSprites(sender_);

	const float SCALE = 0.7f;

	const auto winSize = cocos2d::Director::getInstance()->getWinSize();
	float displayPokerMaxWidth = 192;
	float displayPokerMiddleX = winSize.width / 2;
	float displayPokerStartX = displayPokerMiddleX - displayPokerMaxWidth / 2.0f;
	float displayPokerY = winSize.height - SCALE * (pokerSprites.front()->getContentSize().height / 2 + 10);
	displayPokers(pokerSprites, displayPokerMaxWidth, displayPokerStartX, displayPokerMiddleX,
		displayPokerY, false, SCALE);
}

void PokerLayer::destroyHolderLastOutPokersCallback(cocos2d::Ref* sender_)
{
	//隐藏不出按钮
	_holderPassSprite->setVisible(false);

	for (int i = 0; i < _lastHolderOutPokersSprites.size(); ++i)
	{
		_lastHolderOutPokersSprites.at(i)->removeFromParent();
	}
	_lastHolderOutPokersSprites.clear();
}

void PokerLayer::displayHolderOutPokersCallbacl(cocos2d::Ref* sender_)
{
	//如果没有出牌，那么显示不出
	if (sender_ == nullptr)
	{
		//显示不出
		_holderPassSprite->setVisible(true);
		return;
	}

	CCASSERT(sender_ != nullptr, "sender_ is nullptr!");

	auto pokerSprites = createPokerSprites(sender_);

	//把当前出的牌记录下来
	_lastHolderOutPokersSprites = pokerSprites;

	const float SCALE = 0.7f;

	const auto winSize = cocos2d::Director::getInstance()->getWinSize();
	float displayPokerMaxWidth = 192;
	float displayPokerMiddleX = winSize.width / 2;
	float displayPokerStartX = displayPokerMiddleX - displayPokerMaxWidth / 2.0f;
	float displayPokerY = winSize.height * 0.4f;
	displayPokers(pokerSprites, displayPokerMaxWidth, displayPokerStartX, displayPokerMiddleX,
		displayPokerY, false, SCALE);
}

void PokerLayer::destroyComputerOneLastOutPokersCallback(cocos2d::Ref* sender_)
{
	//隐藏不出按钮
	_computerOnePassSprite->setVisible(false);

	for (int i = 0; i < _lastComputerOneOutPokersSprites.size(); ++i)
	{
		_lastComputerOneOutPokersSprites.at(i)->removeFromParent();
	}
	_lastComputerOneOutPokersSprites.clear();
}

void PokerLayer::displayComputerOneOutPokersCallback(cocos2d::Ref* sender_)
{
	if (sender_ == nullptr)
	{
		//显示不出按钮
		_computerOnePassSprite->setVisible(true);
		return;
	}

	CCASSERT(sender_ != nullptr, "sender_ is nullptr!");

	auto pokerSprites = createPokerSprites(sender_);

	_lastComputerOneOutPokersSprites = pokerSprites;

	const float SCALE = 0.7f;

	const auto winSize = cocos2d::Director::getInstance()->getWinSize();
	float displayPokerMaxWidth = 192;
	float displayPokerMiddleX = winSize.width * 0.7f;
	float displayPokerStartX = displayPokerMiddleX - displayPokerMaxWidth / 2.0f;
	float displayPokerY = winSize.height * 0.72f;
	displayPokers(pokerSprites, displayPokerMaxWidth, displayPokerStartX, displayPokerMiddleX,
		displayPokerY, false, SCALE);
}

void PokerLayer::destroyComputerTwoLastOutPokersCallback(cocos2d::Ref* sender_)
{
	//隐藏不出按钮
	_computerTwoPassSprite->setVisible(false);

	for (int i = 0; i < _lastComputerTwoOutPokersSprites.size(); ++i)
	{
		_lastComputerTwoOutPokersSprites.at(i)->removeFromParent();
	}
	_lastComputerTwoOutPokersSprites.clear();
}

void PokerLayer::displayComputerTwoOutPokersCallback(cocos2d::Ref* sender_)
{
	if (sender_ == nullptr)
	{
		//显示不出按钮
		_computerTwoPassSprite->setVisible(true);
		return;
	}

	CCASSERT(sender_ != nullptr, "sender_ is nullptr!");

	auto pokerSprites = createPokerSprites(sender_);

	_lastComputerTwoOutPokersSprites = pokerSprites;

	const float SCALE = 0.7f;

	const auto winSize = cocos2d::Director::getInstance()->getWinSize();
	float displayPokerMaxWidth = 192;
	float displayPokerMiddleX = winSize.width * 0.3f;
	float displayPokerStartX = displayPokerMiddleX - displayPokerMaxWidth / 2.0f;
	float displayPokerY = winSize.height * 0.72f;
	displayPokers(pokerSprites, displayPokerMaxWidth, displayPokerStartX, displayPokerMiddleX,
		displayPokerY, false, SCALE);
}

void PokerLayer::passBtnCallback(cocos2d::Ref* sender_)
{

}

void PokerLayer::outPokersBtnCallback(cocos2d::Ref* sender_)
{

}

void PokerLayer::hintBtnCallback(cocos2d::Ref* sender_)
{

}
