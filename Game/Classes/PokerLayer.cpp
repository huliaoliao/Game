#include "PokerLayer.h"

#include "Common.h"
#include "Poker.h"
#include "PokerController.h"

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

	return true;
}

bool PokerLayer::initView()
{
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

	return true;
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
	const auto pokers = *reinterpret_cast<cocos2d::Vector<Poker*>*>(sender_);

	const float SCALE = 0.7f;

	//����һ��Sprite���ܱ�addChild���Σ����ｫ��ʾ�ĵ���Ԥ���ƾ������ó�һ��clone��õ�ֵ
	const auto tmp = PokerController::getInstance()->genPokerSprites(pokers);
	std::vector<PokerSprite*> pokerSprites;
	for (int i = 0; i < tmp.size(); ++i)
	{
		pokerSprites.push_back(tmp.at(i)->clone());
	}

	const auto winSize = cocos2d::Director::getInstance()->getWinSize();
	float displayPokerMaxWidth = 192;
	float displayPokerMiddleX = winSize.width / 2;
	float displayPokerStartX = displayPokerMiddleX - displayPokerMaxWidth / 2.0f;
	float displayPokerY = winSize.height - SCALE * (pokerSprites.front()->getContentSize().height / 2 + 10);
	displayPokers(pokerSprites, displayPokerMaxWidth, displayPokerStartX, displayPokerMiddleX,
		displayPokerY, false, SCALE);
}