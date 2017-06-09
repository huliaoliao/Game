#include "PokerController.h"

#include "Common.h"

cocos2d::SpriteFrameCache*		PokerController::s_pokerSpriteCache;
std::vector<Poker>					PokerController::s_pokers;
std::unordered_map<Poker, PokerSprite*>		PokerController::s_pokersMap;

PokerController::PokerController()
{
	srand((unsigned)time(nullptr));	//�����������

	//������õ�ͼƬ����SpriteFrameCache����Ȼ�����ֱ�ӻ�ȡ
	s_pokerSpriteCache = cocos2d::SpriteFrameCache::getInstance();
	s_pokerSpriteCache->addSpriteFramesWithFile(POKER_IMAGE_LIST, POKER_IMAGES);

	initPokers();
	randomPokers();	//ϴ��
	initPokerSprites();
}

PokerController& PokerController::getIns()
{
	static PokerController pokerController;
	return pokerController;
}

PokerController* PokerController::getInstance()
{
	return &getIns();
}

void PokerController::initPokers()
{
	s_pokers.clear();
	//����DIAMOND
	for (int i = 1; i <= SINGLE_TYPE_CARD_NUM; ++i)
	{
		auto poker = Poker(Poker::DIAMOND, i);
		s_pokers.push_back(poker);
	}

	//÷��HEART
	for (int i = 1; i <= SINGLE_TYPE_CARD_NUM; ++i)
	{
		auto poker = Poker(Poker::HEART, i);
		s_pokers.push_back(poker);
	}

	//����CLUB
	for (int i = 1; i <= SINGLE_TYPE_CARD_NUM; ++i)
	{
		auto poker = Poker(Poker::CLUB, i);
		s_pokers.push_back(poker);
	}

	//����SPADE
	for (int i = 1; i <= SINGLE_TYPE_CARD_NUM; ++i)
	{
		auto poker = Poker(Poker::SPADE, i);
		s_pokers.push_back(poker);
	}

	//��С��
	s_pokers.push_back(Poker(Poker::BLACKJOKER));
	s_pokers.push_back(Poker(Poker::REDJOKER));
}

void PokerController::initPokerSprites()
{
	s_pokersMap.clear();

	//����Poker�Ͷ�Ӧ��Sprite��Map���൱����Cache����������Ч��
	for (int i = 0; i < s_pokers.size(); ++i)
	{
		auto poker = s_pokers.at(i);
		int index = calcImageIndex(s_pokers.at(i));
		std::string str = cocos2d::StringUtils::format("%d.png", index);
		auto sprite = cocos2d::Sprite::createWithSpriteFrameName(str);
		auto pokerSprite = PokerSprite::create(sprite, poker);

		//----------------------------------------
		pokerSprite->retain();

		s_pokersMap.insert(std::pair<decltype(poker), decltype(pokerSprite)>(poker, pokerSprite));
	}
}

std::vector<Poker> PokerController::getRandomPokers()
{
	return s_pokers;
}

void PokerController::randomPokers()
{
	//srand((unsigned)time(nullptr));	//�����������
	for (int i = s_pokers.size(); i > 0; --i)
	{
		auto randomIndex = rand() % i;
		std::swap(s_pokers[i - 1], s_pokers[randomIndex]);
	}
}

std::vector<PokerSprite*> PokerController::genPokerSprites(const cocos2d::Vector<Poker*>& pokers_)
{
	std::vector<PokerSprite*> result;
	for (int i = 0; i < pokers_.size(); ++i)
	{
		auto sprite = s_pokersMap.at(*pokers_.at(i));
		result.push_back(sprite);
	}

	return result;
}

int PokerController::calcImageIndex(const Poker& poker_)
{
	int result = 0;

	switch (poker_.type)
	{
	case Poker::BLACKJOKER:
	case Poker::REDJOKER:
	case Poker::BACK:	result = poker_.type; break;
	default:
		result = poker_.type * SINGLE_TYPE_CARD_NUM + poker_.value - 1;
		break;
	}

	return result;
}