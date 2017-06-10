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
	_holderPassSprite->setVisible(false);	//��ʼ����ʾ
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

	//������ذ�ť�����������ƣ���ʾ��û���ƴ�ù��ϼң�
	const auto btnInterval = 10.0f;
	const auto btnWidth = cocos2d::Sprite::create(PASS_BTN)->getContentSize().width;
	const auto btnPos = cocos2d::Point(winSize.width * 0.5f, winSize.height * 0.35);
	//������ť
	auto passBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(PASS_BTN),
		nullptr,
		CC_CALLBACK_1(PokerLayer::passBtnCallback, this));
	passBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	passBtn->setPosition(cocos2d::Point(btnPos.x - btnWidth - btnInterval, btnPos.y));

	//��ʾ��ť
	auto hintBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(HINT_BTN),
		nullptr,
		CC_CALLBACK_1(PokerLayer::hintBtnCallback, this));
	hintBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	hintBtn->setPosition(cocos2d::Point(btnPos.x, btnPos.y));
	hintBtn->setDisabledImage(cocos2d::Sprite::create(HINT_DISABLE_BTN));	//��ʾ��ť���ɰ�״̬
	hintBtn->setEnabled(false);	//��ʾ��ť��ʼ���ɵ��

	//���ư�ť
	auto outPokersBtn = ScalableMenuItemSprite::create(
		cocos2d::Sprite::create(OUTPOKER_BTN),
		nullptr,
		CC_CALLBACK_1(PokerLayer::outPokersBtnCallback, this));
	outPokersBtn->setAnchorPoint(cocos2d::Vec2::ANCHOR_MIDDLE);
	outPokersBtn->setPosition(cocos2d::Point(btnPos.x + btnWidth + btnInterval, btnPos.y));
	outPokersBtn->setDisabledImage(cocos2d::Sprite::create(OUTPOKER_DISABLE_BTN));	//���ư�ť���ɰ�״̬
	outPokersBtn->setEnabled(false);

	_btnMenu = cocos2d::Menu::create(passBtn, hintBtn, outPokersBtn, nullptr);
	_btnMenu->setPosition(cocos2d::Point::ZERO);
	this->addChild(_btnMenu);

	return true;
}

bool PokerLayer::initContent()
{
	//ע����ʾ�ֶ�������е�����Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayHolderPokersCallback, this),
		DISPLAY_HOLDER_POKERS,
		nullptr);

	//ע����ʾԤ��������������Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayLandlordPokersCallback, this),
		DISPLAY_LANDLORD_POKERS,
		nullptr);

	//ע�������ֶ������һ�ִ��������Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::destroyHolderLastOutPokersCallback, this),
		DESTROY_LAST_HOLDER_OUTPOKERS,
		nullptr);

	//ע����ʾ��Ҹþִ��������Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayHolderOutPokersCallbacl, this),
		DISPLAY_HOLDER_OUTPOKERS,
		nullptr);

	//ע�����ٵ������1��һ�ִ��������Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::destroyComputerOneLastOutPokersCallback, this),
		DESTROY_LAST_COMPUTER_ONE_OUTPOKERS,
		nullptr);

	//ע����ʾ�������1�þִ��������Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayComputerOneOutPokersCallback, this),
		DISPLAY_COMPUTER_ONE_OUTPOKERS,
		nullptr);

	//ע�����ٵ������2��һ�ִ�����Ƶ���Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::destroyComputerTwoLastOutPokersCallback, this),
		DESTROY_LAST_COMPUTER_TWO_OUTPOKERS,
		nullptr);

	//ע����ʾ�������2�þִ�����Ƶ���Ϣ
	cocos2d::NotificationCenter::getInstance()->addObserver(this,
		callfuncO_selector(PokerLayer::displayComputerTwoOutPokersCallback, this),
		DISPLAY_COMPUTER_TWO_OUTPOKERS,
		nullptr);

	return true;
}

bool PokerLayer::initListener()
{
	auto listener = cocos2d::EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);	//���ɣ������ϲ㴥������������ٴ��ݸ��²�

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
			//����ѡ�Ƶ���Ч

			_holderClickedPokerSprites.push_back(holderPokerSprites.at(i));
			if (!holderPokerSprites.at(i)->getIsSelected())
			{
				//�����δѡ�������ƣ��Ǿͽ�������¶����
				holderPokerSprites.at(i)->selectedPokersOut();
			}
			else
			{
				//�����������Ѿ���ѡ�񣬽���Ż�
				holderPokerSprites.at(i)->selectedPokerBack();
			}

			//��⵱ǰѡ������Ƿ��������ư�ť�ɰ�

			return true;
		}
	}

	//�������µ�λ�ò����˿˷�Χ�ڣ���ô��ʹ�����ƶ���Ҳ�������κβ���
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
			//��ǰ��������Ƿ������Ѿ�ѡ����Ƽ����ڣ�����ڣ���ôֱ�ӽ���ѭ��
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

			//���ŵ���Ƶ���Ч
			//TODO

			_holderClickedPokerSprites.push_back(pokerSprites.at(i));
			if (!pokerSprites.at(i)->getIsSelected())
			{
				//�����δѡ�������ƣ��Ǿͽ�������¶����
				pokerSprites.at(i)->selectedPokersOut();
			}
			else
			{
				//�����������Ѿ���ѡ�񣬽���Ż�
				pokerSprites.at(i)->selectedPokerBack();
			}

			//��⵱ǰ���Ƿ��������ư�ť�ɰ�
			//TODO

			break;
		}
	}
}

void PokerLayer::onTouchEnded(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_)
{
	//�������������clickedPokers
	_holderClickedPokerSprites.clear();
}

std::vector<PokerSprite*> PokerLayer::createPokerSprites(cocos2d::Ref* sender_)
{
	const auto pokers = *reinterpret_cast<cocos2d::Vector<Poker*>*>(sender_);

	//����һ��Sprite���ܱ�addChild���Σ����ｫ��ʾ�ĵ���Ԥ���ƾ�����ߴ���������ó�һ��clone��õ�ֵ
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
	//������֮�������϶
	float	maxIntervalBetweenPokers = pokerWidth - MIMIUM_CARDS_OVERLAPWIDTH * SCALE;
	float intervalBetweenPokers = (displayMaxWidth_ - pokerWidth) < maxIntervalBetweenPokers * (pokersNum - 1) ?
		(displayMaxWidth_ - pokerWidth) / (pokersNum - 1) : maxIntervalBetweenPokers;

	//����֮��ļ�϶�ﵽ���ʱ����Ҫ����ʾ���е�չ����ʾ����Ȼ�������ʾ����ƫ������Ӿ�����
	if (intervalBetweenPokers == maxIntervalBetweenPokers)
	{
		// 		displayStartX_ = pokersNum % 2 == 0 ?
		// 			displayMiddleX_ - (pokersNum / 2) * intervalBetweenPokers :
		// 			displayMiddleX_ - (pokersNum / 2 + 0.5) * intervalBetweenPokers;
		auto totalPokersWidth = (pokersNum - 1) * intervalBetweenPokers + pokerWidth;
		displayStartX_ = displayMiddleX_ - totalPokersWidth / 2.0f;
	}

	//��ʾ����
	for (int i = 0; i < pokersNum; ++i)
	{
		if (isOnScene_ == false)	//�ֶ���ҳ��е���
		{
			this->addChild(pokers_.at(i));
		}
		else
		{
			displayY_ = pokers_.at(i)->getPosition().y;	//��Դ�������
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

	//�����ޱ仯��ֱ�ӷ���
	if (_lastHolderPokerSprites.size() == pokers.size())
	{
		return;
	}

	for (int i = 0; i < pokers.size(); ++i)
	{
		cocos2d::log("%d : %d\n", pokers.at(i)->type, pokers.at(i)->value);
	}
	const auto pokerSprites = PokerController::getInstance()->genPokerSprites(pokers);

	//��Ҫ���ϴ���ʾ���Ƹ�����
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
	//���ز�����ť
	_holderPassSprite->setVisible(false);

	for (int i = 0; i < _lastHolderOutPokersSprites.size(); ++i)
	{
		_lastHolderOutPokersSprites.at(i)->removeFromParent();
	}
	_lastHolderOutPokersSprites.clear();
}

void PokerLayer::displayHolderOutPokersCallbacl(cocos2d::Ref* sender_)
{
	//���û�г��ƣ���ô��ʾ����
	if (sender_ == nullptr)
	{
		//��ʾ����
		_holderPassSprite->setVisible(true);
		return;
	}

	CCASSERT(sender_ != nullptr, "sender_ is nullptr!");

	auto pokerSprites = createPokerSprites(sender_);

	//�ѵ�ǰ�����Ƽ�¼����
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
	//���ز�����ť
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
		//��ʾ������ť
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
	//���ز�����ť
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
		//��ʾ������ť
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
