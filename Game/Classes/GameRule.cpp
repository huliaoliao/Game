#include "GameRule.h"

#include "OutPokers.h"
#include "PokerSetType.h"
#include "Util.h"

#define COMPARE_POKER_GREATER(a, b) util::PokerUtil::pokerCmpWithoutType(a, b)
#define COMPARE_POKER_EQUAL(a, b) !util::PokerUtil::pokerCmpWithoutType(a, b) && \
	util::PokerUtil::pokerCmpWithoutType(b, a)

bool GameRule::isSingle(const std::vector<Poker>& pokers_)
{
	return pokers_.size() == 1;
}

bool GameRule::isPair(const std::vector<Poker>& pokers_)
{
	//���ţ���������������ֵһ��
	if (pokers_.size() != 2)
	{
		return false;
	}
	else if (isKing(pokers_.at(0)) || isKing(pokers_.at(1)))
	{
		return false;
	}
	else if (pokers_.at(0).value != pokers_.at(1).value)
	{
		return false;
	}

	return true;
}

bool GameRule::isTriple(const std::vector<Poker>& pokers_)
{
	//���ţ�������������ֵһ��
	if (pokers_.size() != 3)
	{
		return false;
	}
	else if (isKing(pokers_.at(0)) || isKing(pokers_.at(1)) || isKing(pokers_.at(2)))
	{
		return false;
	}
	else if (pokers_.at(0).value != pokers_.at(1).value ||
		pokers_.at(1).value != pokers_.at(2).value)
	{
		return false;
	}

	return true;
}

bool GameRule::isTripleWithSingle(std::vector<Poker> pokers_)
{
	//����4�Ż��ߴ���ը��������false
	if (pokers_.size() != 4)
	{
		return false;
	}
	else if (isExistBomb(pokers_))
	{
		return false;
	}

	//����
	util::PokerUtil::sort(pokers_);

	//���������1-3����3-1
	//3-1
	std::vector<Poker> pokers = std::vector<Poker>(pokers_.begin(), pokers_.begin() + 3);
	if (isTriple(pokers))
	{
		return true;
	}

	//1-3
	pokers = std::vector<Poker>(pokers_.begin() + 1, pokers_.begin() + 4);
	if (isTriple(pokers))
	{
		return true;
	}

	//�����ǣ�����false
	return false;
}

bool GameRule::isTripleWithPair(std::vector<Poker> pokers_)
{
	//����5�ţ�����false
	if (pokers_.size() != 5)
	{
		return false;
	}

	//����
	util::PokerUtil::sort(pokers_);

	//���������2-3����3-2
	//2-3
	std::vector<Poker> pairPokers = std::vector<Poker>(pokers_.begin(), pokers_.begin() + 2);
	std::vector<Poker> triplePokers = std::vector<Poker>(pokers_.begin() + 2, pokers_.begin() + 5);
	if (isPair(pairPokers) && isTriple(triplePokers))
	{
		return true;
	}

	//3-2
	triplePokers = std::vector<Poker>(pokers_.begin(), pokers_.begin() + 3);
	pairPokers = std::vector<Poker>(pokers_.begin() + 3, pokers_.begin() + 5);
	if (isTriple(triplePokers) && isPair(pairPokers))
	{
		return true;
	}

	return false;
}

bool GameRule::isSingleStraight(std::vector<Poker> pokers_)
{
	//����
	util::PokerUtil::sort(pokers_);

	auto firstPoker = pokers_.front();
	//�����һ������������2����ô�϶�����˳��
	if (firstPoker.value == 2 || isKing(firstPoker))
	{
		return false;
	}

	//�����һ����A
	if (firstPoker.value == 1)
	{
		//�����2�Ų���K������false
		if (pokers_.at(1).value != 13)
		{
			return false;
		}
		else
		{
			for (int i = 1; i < pokers_.size() - 1; ++i)
			{
				if (pokers_.at(i).value != pokers_.at(i + 1).value + 1)
				{
					return false;
				}
			}
			return true;
		}
	}
	//�����һ�Ų���A
	else
	{
		for (int i = 0; i < pokers_.size() - 1; ++i)
		{
			if (pokers_.at(i).value != pokers_.at(i + 1).value + 1)
			{
				return false;
			}
		}
		return true;
	}
}

bool GameRule::isPairStraight(std::vector<Poker> pokers_)
{
	//����˿�������ż������ô�϶�����˫˳
	if (pokers_.size() % 2 != 0)
	{
		return false;
	}

	//����
	util::PokerUtil::sort(pokers_);

	const auto firstPoker = pokers_.front();
	//�����һ������������2����ô�϶�����˫˳
	if (firstPoker.value == 2 || isKing(firstPoker))
	{
		return false;
	}

	//�ж��Ƿ��Ƕ���
	for (int i = 0; i <= pokers_.size() - 2; i += 2)
	{
		auto pairPokers = std::vector<Poker>(pokers_.begin() + i, pokers_.begin() + i + 2);
		if (isPair(pairPokers) == false)
		{
			return false;
		}
	}

	//�͵�˳һ�����ж��Ƿ���������
	if (firstPoker.value == 1)
	{
		if (pokers_.at(2).value != 13)
		{
			return false;
		}
		else
		{
			for (int i = 2; i < pokers_.size() - 2; i += 2)
			{
				if (pokers_.at(i).value != pokers_.at(i + 2).value + 1)
				{
					return false;
				}
			}
			return true;
		}
	}
	else
	{
		for (int i = 0; i < pokers_.size() - 2; i += 2)
		{
			if (pokers_.at(i).value != pokers_.at(i + 2).value + 1)
			{
				return false;
			}
			return true;
		}
	}
}

bool GameRule::isTripleStraight(std::vector<Poker> pokers_)
{
	//����˿�������3�ı������ұ�������Ϊ2����ô�϶�������˳
	if (pokers_.size() % 3 != 0 || pokers_.size() < 6)
	{
		return false;
	}

	//����
	util::PokerUtil::sort(pokers_);

	auto firstPoker = pokers_.front();
	//�͵�˳���ж��߼�����
	if (firstPoker.value == 2 || isKing(firstPoker))
	{
		return false;
	}

	//�ж��Ƿ�������
	for (int i = 0; i <= pokers_.size() - 3; i += 3)
	{
		auto triplePokers = std::vector<Poker>(pokers_.begin() + i, pokers_.begin() + i + 3);
		if (isTriple(triplePokers) == false)
		{
			return false;
		}
	}

	if (firstPoker.value == 1)
	{
		if (pokers_.at(3).value != 13)
		{
			return false;
		}
		else
		{
			for (int i = 3; i < pokers_.size() - 3; i += 3)
			{
				if (pokers_.at(i).value != pokers_.at(i + 3).value + 1)
				{
					return false;
				}
			}
			return true;
		}
	}
	else
	{
		for (int i = 0; i < pokers_.size() - 3; i += 3)
		{
			if (pokers_.at(i).value != pokers_.at(i + 3).value + 1)
			{
				return false;
			}
		}
		return true;
	}
}

bool GameRule::isTripleStraightWithSingle(std::vector<Poker> pokers_)
{
	//������ǣ�3+1��*X����ʽ����X����Ϊ2����ô�϶�����3��1
	if (pokers_.size() % 4 != 0 || pokers_.size() < 8)
	{
		return false;
	}

	auto tmp = splitTriplesInPokers(pokers_);
	auto triplePokers = tmp.first;
	auto remainedPokers = tmp.second;

	//���ŵ���Ŀ����͵��ŵ���Ŀ��ȣ����򷵻�false
	if (triplePokers.size() != 3 * remainedPokers.size())
	{
		return false;
	}

	//�����ǲ���˳��
	if (isTripleStraight(triplePokers) == false)
	{
		return false;
	}

	return true;
}

bool GameRule::isTripleStraightWithPair(std::vector<Poker> pokers_)
{
	//������ǣ�3+2��*X����ʽ����X����2����ô�϶�����3��2
	if (pokers_.size() % 5 != 0 || pokers_.size() < 10)
	{
		return false;
	}

	//������ŵļ��ϼ����ŵļ���
	auto tmp = splitTriplesInPokers(pokers_);
	auto triplePokers = tmp.first;
	auto remainedPokers = tmp.second;

	if (triplePokers.size() / 3 != remainedPokers.size() / 2)
	{
		return false;
	}

	//��ֳ���remainedPokers�Ƿ��Ƕ���
	if (isAllPair(remainedPokers) == false)
	{
		return false;
	}

	if (isTripleStraight(triplePokers) == false)
	{
		return false;
	}

	return true;
}

bool GameRule::isBomb(const std::vector<Poker>& pokers_)
{
	if (pokers_.size() != 4)
	{
		return false;
	}

	return isValueEqual(pokers_);
}

bool GameRule::isKingBomb(const std::vector<Poker>& pokers_)
{
	if (pokers_.size() != 2)
	{
		return false;
	}

	if (isKing(pokers_.at(0)) && isKing(pokers_.at(1)))
	{
		return false;
	}

	return true;
}

bool GameRule::isKing(const Poker& poker_)
{
	if (poker_.type == Poker::BLACKJOKER ||
		poker_.type == Poker::REDJOKER)
	{
		return true;
	}
	return false;
}

bool GameRule::isExistBomb(const std::vector<Poker>& pokers_)
{
	int index = 0;
	while (index <= pokers_.size() - 4)
	{
		auto tmp = std::vector<Poker>(pokers_.begin() + index, pokers_.begin() + index + 4);
		if (isBomb(tmp) == true)
		{
			return true;
		}
	}
	return false;
}

bool GameRule::isValueEqual(const std::vector<Poker>& pokers_)
{
	auto firstPoker = pokers_.front();

	if (isKing(firstPoker))
	{
		return false;
	}

	for (int i = 1; i < pokers_.size(); ++i)
	{
		if (pokers_.at(i).value != firstPoker.value)
		{
			return false;
		}
	}

	return true;
}

bool GameRule::isAllPair(const std::vector<Poker>& pokers_)
{
	if (pokers_.size() % 2 != 0)
	{
		return false;
	}
	for (int i = 0; i < pokers_.size() - 1; ++i)
	{
		if (pokers_.at(i).value != pokers_.at(i + 1).value)
		{
			return false;
		}
	}
	return true;
}

std::pair<std::vector<Poker>, std::vector<Poker>> 
	GameRule::splitTriplesInPokers(const std::vector<Poker>& pokers_)
{
	//��ԭ�е����в������
	std::vector<Poker> pokers = pokers_;
	std::vector<Poker> triplePokers;
	int index = 0;
	while (index <= pokers.size() - 3)
	{
		auto tmp = std::vector<Poker>(pokers_.begin() + index, pokers_.begin() + index + 3);
		if (isTriple(tmp) == true)
		{
			for (int i = 0; i < tmp.size(); ++i)
			{
				triplePokers.push_back(tmp[i]);
			}
			pokers.erase(pokers.begin() + index, pokers.begin() + index + 3);
		}
		else
		{
			index += 1;
		}
	}
	//pokersΪʣ�����
	return std::pair<std::vector<Poker>, std::vector<Poker>>(triplePokers, pokers);
}

PokersType GameRule::getBasePokersType(PokersType pokersType_)
{
	switch (pokersType_){
	case SINGLE:
	case PAIR:
	case TRIPLE:
	case BOMB:
	case KINGBOMB:
	case STRAIGHT:
	case PAIRSTRAIGHT:
	case TRIPLESTRAIGHT:
		return pokersType_;  break;
	case TRIPLEWITHSINGLE:
	case TRIPLEWITHPAIR: 
		return TRIPLE; break;
	case TRIPLESTRAIGHTWITHSINGLE:
	case TRIPLESTRAIGHTWITHPAIR: 
		return TRIPLESTRAIGHT; break;
	default: 
		return NONE; break;
	}
}

Poker GameRule::getTripleStraightWithSingleLowestPoker(const std::vector<Poker>& pokers_)
{
	std::vector<Poker> tmp = splitTriplesInPokers(pokers_).first;
	Poker result = tmp.back();
	return result;
}

Poker GameRule::getTripleStraightWithPairLowestPoker(const std::vector<Poker>& pokers_)
{
	return getTripleStraightWithSingleLowestPoker(pokers_);
}

bool GameRule::canOutPokers(std::vector<Poker> waitOutPokers, const OutPokers& lastOutPokers)
{
	//����
	util::PokerUtil::sort(waitOutPokers);

	//����֮һ����ը
	if (isKingBomb(waitOutPokers))
	{
		return true;
	}
	if (lastOutPokers.getPokersType() == PokersType::KINGBOMB)
	{
		return false;
	}

	//����֮һ��ը��
	if (lastOutPokers.getPokersType() == PokersType::BOMB)
	{
		//�������Ƿ���ը��������ǣ���ô�Ƿ������һ���Ƶ�ը������������ֵ����ը����С��
		if (isBomb(waitOutPokers) == BOMB &&
			COMPARE_POKER_GREATER(waitOutPokers.back(), lastOutPokers.getLowestPoker()))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else if (isBomb(waitOutPokers))
	{
		return true;
	}

	//�������ͱ�����ͬ
	//���������︽�����˿�
	auto filterPokers = filterAccessoryPokers(waitOutPokers);
	PokersType waitOutPokersType = getBasePokersType(analysePokersType(waitOutPokers));
	PokersType lastOutPokersType = getBasePokersType(lastOutPokers.getPokersType());

	//���Ͳ�һ�£�����false
	if (waitOutPokersType != lastOutPokersType)
	{
		return false;
	}

	//����һ��ʱ
	//�����˳��
	if (lastOutPokersType == STRAIGHT || lastOutPokersType == PAIRSTRAIGHT ||
		lastOutPokersType == TRIPLESTRAIGHT)
	{
		//�����Ƿ�һ��
		if (lastOutPokers.getTotalLen() != waitOutPokers.size())
		{
			return false;
		}
		//�������Ƿ������һ����ҵ���
		else if (!COMPARE_POKER_GREATER(waitOutPokers.back(), lastOutPokers.getLowestPoker()))
		{
			return false;
		}
		return true;
	}

	//����˳��
	if (lastOutPokers.getTotalLen() == waitOutPokers.size())
	{
		if (COMPARE_POKER_GREATER(waitOutPokers.back(), lastOutPokers.getLowestPoker()))
		{
			return true;
		}
	}

	return false;
}

std::vector<Poker> GameRule::searchProperPokers(const std::vector<Poker>& pokers_)
{
	std::vector<Poker> result;
	//���ҵ���
	result = calcPokersWithType(pokers_, SINGLE);
	if (result.size() == 0)	//û�ҵ�����
	{
		result = calcPokersWithType(pokers_, PAIR);
		if (result.size() == 0)
		{
			result = calcPokersWithType(pokers_, TRIPLE);
			if (result.size() == 0)
			{
				//����û������ը
				result = calcPokersWithType(pokers_, BOMB);
			}
		}
	}

	return result;
}

std::vector<Poker> GameRule::filterAccessoryPokers(const std::vector<Poker>& pokers_)
{
	PokersType pokersType = analysePokersType(pokers_);

	switch (pokersType)
	{
	case SINGLE:
	case PAIR:
	case TRIPLE:
	case BOMB:
	case KINGBOMB:
	case STRAIGHT:
	case PAIRSTRAIGHT:
	case TRIPLESTRAIGHT:
		return pokers_;
		break;
	case TRIPLEWITHSINGLE:
	case TRIPLEWITHPAIR:
	case TRIPLESTRAIGHTWITHSINGLE:
	case TRIPLESTRAIGHTWITHPAIR:
		return splitTriplesInPokers(pokers_).first;
		break;
	default:
		CC_ASSERT(0 != 0); 
		break;
	}
}

std::vector<Poker> GameRule::calcPokersWithType(std::vector<Poker> pokers_, PokersType pokersType_, 
	const Poker* poker_ /*= nullptr*/, int length /*= 0*/)
{
	//����
	util::PokerUtil::sort(pokers_);

	switch (pokersType_)
	{
	case SINGLE:
		return searchSingle(pokers_, poker_);
		break;
	case PAIR:
		return searchPair(pokers_, poker_);
		break;
	case TRIPLE:
	case TRIPLEWITHSINGLE:
	case TRIPLEWITHPAIR:
		//�����3��1����3��2��ȫ������3�ż���
		return searchTriple(pokers_, poker_);
		break;
	case BOMB:
		return searchBomb(pokers_, poker_);
		break;
	case KINGBOMB:
		return searchKingBomb(pokers_);
		break;
	case STRAIGHT:
		return searchSingleStraight(pokers_, length, poker_);
		break;
	case PAIRSTRAIGHT:
		return searchPairStraight(pokers_, length, poker_);
		break;
	case TRIPLESTRAIGHT:
	case TRIPLESTRAIGHTWITHSINGLE:
	case TRIPLESTRAIGHTWITHPAIR:
		//�������˳��1������˳��2��ȫ��������˳����
		return searchTripleStraight(pokers_, length, poker_);
		break;
	default:
		break;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::calcPokersWithTypeInSplit(std::vector<Poker> pokers_, PokersType pokersType_, const Poker* poker_ /*= nullptr*/, int length /*= 0*/)
{
	//����
	util::PokerUtil::sort(pokers_);

	switch (pokersType_)
	{
	case SINGLE:
		return searchSingleInSplit(pokers_, poker_);
		break;
	case PAIR:
		return searchPairInSplit(pokers_, poker_);
		break;
	case TRIPLE:
	case TRIPLEWITHSINGLE:
	case TRIPLEWITHPAIR:
		//�����3��1����3��2��ȫ������3�ż���
		return searchTripleInSplit(pokers_, poker_);
		break;
	case BOMB:
		return searchBomb(pokers_, poker_);
		break;
	case KINGBOMB:
		return searchKingBomb(pokers_);
		break;
	case STRAIGHT:
		return searchSingleStraight(pokers_, length, poker_);
		break;
	case PAIRSTRAIGHT:
		return searchPairStraight(pokers_, length, poker_);
		break;
	case TRIPLESTRAIGHT:
	case TRIPLESTRAIGHTWITHSINGLE:
	case TRIPLESTRAIGHTWITHPAIR:
		//�������˳��1������˳��2��ȫ��������˳����
		return searchTripleStraight(pokers_, length, poker_);
		break;
	default:
		break;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchSingle(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.empty())
	{
		return std::vector<Poker>();
	}

	//��Ϊ����Ӵ�С����ģ������Ҫ�Ӹ�λ������
	int index = pokers_.size() - 1;
	while (index >= 0)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		/* �����ж��Ƿ�����ֵ����Ҫ�ҵ��ƣ�����ǣ��ǾͿ��Խ�һ���ж��Ƕ��ӣ����ţ�ը���ȣ��������Լ��������
		�ж϶��ӵȵ������Ƿ�ֹ���ƣ��ڷ�˳�ӵ�ǰ���£������Բ���*/
		if (poker_ == nullptr || COMPARE_POKER_GREATER(tmp.front(), *poker_))
		{
			if (index - 1 >= 0)
			{
				tmp.push_back(pokers_.at(index - 1));
				if (isPair(tmp))
				{
					if (index - 2 >= 0)
					{
						tmp.push_back(pokers_.at(index - 2));
						if (isTriple(tmp))
						{
							if (index - 3 >= 0)
							{
								tmp.push_back(pokers_.at(index - 3));
								if (isBomb(tmp))
								{
									index = index - 4;
									continue;
								}
								tmp.pop_back();//�������ը������ôҪ��ǰ���һ��popBack
							}
							index = index - 3;
							continue;
						}
						tmp.pop_back();//����������ţ���ôҪ��ǰ���һ��popBack
					}
					index = index - 2;
					continue;
				}
				tmp.pop_back();
			}
			return tmp;
		}
		index = index - 1;
		tmp.clear();
	}

	//���ڵ�һ�����⣬Ϊ�˲����ƣ����ܳ���333444555�������ʱ�����������
	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchPair(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.size() < 2)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	//>= 1��Ŀ���ǣ���֤ÿ��ѭ��������������
	while (index >= 1)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		if (isPair(tmp) == true &&
			(poker_ == nullptr || COMPARE_POKER_GREATER(tmp.front(), *poker_)))
		{
			if (index - 2 >= 0)
			{
				tmp.push_back(pokers_.at(index - 2));
				if (isTriple(tmp) == true)
				{
					if (index - 3 >= 0)
					{
						tmp.push_back(pokers_.at(index - 3));
						if (isBomb(tmp) == true)
						{
							index = index - 4;
							continue;
						}
						tmp.pop_back();
					}
					index = index - 3;
					continue;
				}
				tmp.pop_back();//����������ţ���ôҪ��ǰ���һ��popBack
			}
			return tmp;
		}
		index = index - 1;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchTriple(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.size() < 3)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 2)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		tmp.push_back(pokers_.at(index - 2));

		if (isTriple(tmp) == true &&
			(poker_ == nullptr || COMPARE_POKER_GREATER(tmp.front(), *poker_)))
		{
			if (index - 3 >= 0)
			{
				tmp.push_back(pokers_.at(index - 3));
				if (isBomb(tmp) == true)
				{
					index = index - 4;
					continue;
				}
				tmp.pop_back();	//�������ը������ôҪ��ǰ���һ��popBack
			}
			return tmp;
		}
		index = index - 1;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchBomb(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.size() < 4)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index - 3 >= 0)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		tmp.push_back(pokers_.at(index - 2));
		tmp.push_back(pokers_.at(index - 3));
		if (isBomb(tmp) == true &&
			(poker_ == nullptr || COMPARE_POKER_GREATER(tmp.front(), *poker_)))
		{
			return tmp;
		}
		index = index - 1;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchKingBomb(const std::vector<Poker>& pokers_)
{
	//����˿˵�����С��2����ô�϶�������ը
	if (pokers_.size() < 2)
	{
		return std::vector<Poker>();
	}

	//�������϶�����������ĵ�һ�ڶ��ţ�
	//���ֱ�ӽ�ǰ�����Ʒ���һ��Vector������isKingBomb�������ж�
	std::vector<Poker> tmp{ pokers_.at(0), pokers_.at(1) };

	if (isKingBomb(tmp))
	{
		return tmp;
	}
	
	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchSpecifiedSingle(const std::vector<Poker>& pokers_, const Poker* poker_)
{
	if (pokers_.empty() || poker_ == nullptr)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 0)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		if (COMPARE_POKER_EQUAL(tmp.front(), *poker_))
		{
			return tmp;
		}
		//�����ǰ�˿��Ѿ�����Ҫ�ҵ��˿ˣ���ôֱ��break
		if (COMPARE_POKER_GREATER(tmp.front(), *poker_))
		{
			break;
		}
		index = index - 1;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchSpecifiedPair(const std::vector<Poker>& pokers_, const Poker* poker_)
{
	if (pokers_.size() < 2 || poker_ == nullptr)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 1)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		if (isPair(tmp) == true)
		{
			if (COMPARE_POKER_EQUAL(tmp.front(), *poker_))
			{
				return tmp;
			}
			if (COMPARE_POKER_GREATER(tmp.front(), *poker_))
			{
				break;
			}
			index = index - 2;
		}
		else
		{
			index = index - 1;
		}
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchSpecifiedTriple(const std::vector<Poker>& pokers_, const Poker* poker_)
{
	if (pokers_.size() < 3 || poker_ == nullptr)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 2)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		tmp.push_back(pokers_.at(index - 2));
		if (isTriple(tmp) == true)
		{
			if (COMPARE_POKER_EQUAL(tmp.front(), *poker_))
			{
				return tmp;
			}
			if (COMPARE_POKER_GREATER(tmp.front(), *poker_))
			{
				break;
			}
			index = index - 3;
		}
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchSingleStraight(const std::vector<Poker>& pokers_, int length_, const Poker* poker_)
{
	//���length��������С��5�ţ������12�ţ���
	//�����˿˵��������������length����ôֱ�ӷ��ؿ�
	if (length_ < 5 || length_ > 12 || pokers_.size() < length_ || poker_ == nullptr)
	{
		return std::vector<Poker>();
	}

	//������ҵ�˳�ӵ���С������ֵ��1����2��
	//�Լ�����˳���������ֵ+˳�ӳ��ȣ���ʱ����˳����������ֵ��> A��14��,��ôֱ�ӷ��ؿ�
	int pokerValue = poker_->value;
	//������ҵ���ֵ��0�������Ǵ�������С��
	if (pokerValue == 0 || pokerValue == 1 || pokerValue == 2 ||
		(pokerValue + length_ > 14))
	{
		return std::vector<Poker>();
	}

	int index = pokerValue + 1;
	std::vector<Poker> result;
	while (index <= (14 - length_ + 1))
	{
		for (int i = 0; i < length_; ++i, ++index)
		{
			auto tmpPoker = util::PokerUtil::getGreaterPoker(*poker_, index - pokerValue);
			//û�з���Ҫ�����
			if (tmpPoker.type == Poker::NONE)
			{
				result.clear();
				break;
			}
			auto tmpPokers = searchSpecifiedSingle(pokers_, &tmpPoker);
			if (tmpPokers.empty())
			{
				result.clear();
				break;
			}
			else
			{
				result.push_back(tmpPokers.front());
			}
		}
		//��ѯ���õĽ�����ǵ����ģ��͹涨�ĵݼ��෴�������������һ��
		if (result.size() == length_)
		{
			util::PokerUtil::sort(result);
			return result;
		}
		//��ǰ�Ѿ�����ʧ�ܣ���index+1������һ����ʼ����
		index++;
	}

	return std::vector<Poker>();
}

//length������˳�ӵĲ�ͬ�Ƶĸ���
std::vector<Poker> GameRule::searchPairStraight(const std::vector<Poker>& pokers_, int length_, const Poker* poker_)
{
	if (length_ < 2 || length_ >= 12 || pokers_.size() < length_ * 2 || poker_ == nullptr)
	{
		return std::vector<Poker>();
	}

	int pokerValue = poker_->value;
	if (pokerValue == 0 || pokerValue == 1 || pokerValue == 2 ||
		(pokerValue + length_ > 14))
	{
		return std::vector<Poker>();
	}

	int index = pokerValue + 1;
	std::vector<Poker> result;
	while (index <= (14 - length_ + 1))
	{
		for (int i = 0; i < length_; ++i, ++index)
		{
			auto tmpPoker = util::PokerUtil::getGreaterPoker(*poker_, index - pokerValue);
			if (tmpPoker.type = Poker::NONE)
			{
				result.clear();
				break;
			}
			auto tmpPokers = searchSpecifiedPair(pokers_, &tmpPoker);
			if (tmpPokers.empty())
			{
				result.clear();
				break;
			}
			else
			{
				result.push_back(tmpPokers.at(0));
				result.push_back(tmpPokers.at(1));
			}
		}
		if (result.size() == length_ * 2)
		{
			util::PokerUtil::sort(result);
			return result;
		}
		//��ǰ�Ѿ�����ʧ�ܣ���index + 1������һ����ʼ����
		index++;
	}

	return std::vector<Poker>();
}

//length������˳�ӵĲ�ͬ�Ƶĸ���
std::vector<Poker> GameRule::searchTripleStraight(const std::vector<Poker>& pokers_, int length_, const Poker* poker_)
{
	if (length_ < 3 || length_ > 12 || pokers_.size() < length_ * 3)
	{
		return std::vector<Poker>();
	}

	int pokerValue = poker_->value;
	if (pokerValue == 0 || pokerValue == 1 || pokerValue == 2 ||
		(pokerValue + length_ > 14))
	{
		std::vector<Poker>();
	}

	int index = pokerValue + 1;
	std::vector<Poker> result;
	while (index <= (14 - length_ + 1))
	{
		for (int i = 0; i < length_; ++i, ++index)
		{
			auto tmpPoker = util::PokerUtil::getGreaterPoker(*poker_, index - pokerValue);
			if (tmpPoker.type == Poker::NONE)
			{
				result.clear();
				break;
			}
			auto tmpPokers = searchSpecifiedTriple(pokers_, &tmpPoker);
			if (tmpPokers.empty())
			{
				result.clear();
				break;
			}
			else
			{
				result.push_back(tmpPokers.at(0));
				result.push_back(tmpPokers.at(1));
				result.push_back(tmpPokers.at(2));
			}
		}
		if (result.size() == length_ * 3)
		{
			util::PokerUtil::sort(result);
			return result;
		}
		index++;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchSingleInSplit(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.size() == 0)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 0)
	{
		if (poker_ == nullptr || COMPARE_POKER_GREATER(pokers_.at(index), *poker_))
		{
			std::vector<Poker> tmp;
			tmp.push_back(pokers_.at(index));
			return tmp;
		}
		index--;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchPairInSplit(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.size() < 2)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 1)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		if (isPair(tmp) == true && (poker_ == nullptr || COMPARE_POKER_GREATER(tmp.front(), *poker_)))
		{
			return tmp;
		}
		index--;
	}

	return std::vector<Poker>();
}

std::vector<Poker> GameRule::searchTripleInSplit(const std::vector<Poker>& pokers_, const Poker* poker_ /*= nullptr*/)
{
	if (pokers_.size() < 3)
	{
		return std::vector<Poker>();
	}

	int index = pokers_.size() - 1;
	while (index >= 2)
	{
		std::vector<Poker> tmp;
		tmp.push_back(pokers_.at(index));
		tmp.push_back(pokers_.at(index - 1));
		tmp.push_back(pokers_.at(index - 2));
		if (isTriple(tmp) == true && (poker_ == nullptr || COMPARE_POKER_GREATER(tmp.front(), *poker_)))
		{
			return tmp;
		}
		index--;
	}

	return std::vector<Poker>();
}

PokersType GameRule::analysePokersType(std::vector<Poker> pokers_)
{
	if (pokers_.empty())
	{
		return NONE;
	}

	//����
	util::PokerUtil::sort(pokers_);

	if (pokers_.size() < 5)
	{
		if (isSingle(pokers_))
		{
			return SINGLE;
		}

		if (isKingBomb(pokers_))
		{
			return KINGBOMB;
		}

		if (isPair(pokers_))
		{
			return PAIR;
		}

		if (isTriple(pokers_))
		{
			return TRIPLE;
		}

		if (isTripleStraightWithSingle(pokers_))
		{
			return TRIPLESTRAIGHTWITHSINGLE;
		}

		if (isBomb(pokers_))
		{
			return BOMB;
		}
	}
	else
	{
		if (isTripleWithPair(pokers_))
		{
			return TRIPLEWITHPAIR;
		}

		if (isSingleStraight(pokers_))
		{
			return STRAIGHT;
		}

		if (isPairStraight(pokers_))
		{
			return PAIRSTRAIGHT;
		}

		if (isTripleStraight(pokers_))
		{
			return TRIPLESTRAIGHT;
		}

		if (isTripleStraightWithSingle(pokers_))
		{
			return TRIPLESTRAIGHTWITHSINGLE;
		}

		if (isTripleStraightWithPair(pokers_))
		{
			return TRIPLESTRAIGHTWITHPAIR;
		}
	}

	return NONE;
}

bool GameRule::isPokerValueType(const std::vector<Poker>& pokers_)
{
	return !(analysePokersType(pokers_) == NONE);
}

bool GameRule::isSpecifiedPokerType(const std::vector<Poker>& pokers_, PokersType pokerType_)
{
	auto pokerType = analysePokersType(pokers_);
	return pokerType_ != NONE && pokerType_ == pokerType;
}

Poker GameRule::getLowestPoker(const std::vector<Poker>& pokers_, PokersType pokerType_)
{
	CC_ASSERT(pokerType_ != NONE);

	int pokersSize = pokers_.size();
	Poker result;

	switch (pokerType_)
	{
	case SINGLE:
	case PAIR:
	case TRIPLE:
	case STRAIGHT:
	case PAIRSTRAIGHT:
	case TRIPLESTRAIGHT:
	case BOMB:
	case KINGBOMB:
		result = pokers_.back();
		break;
	case TRIPLEWITHSINGLE:
	case TRIPLEWITHPAIR:
		//3��1����3��2�����ſ϶���һ�����˿˵ĵ�3��
		result = pokers_.at(2);
		break;
	case TRIPLESTRAIGHTWITHSINGLE:
		result = getTripleStraightWithSingleLowestPoker(pokers_);
		break;
	case TRIPLESTRAIGHTWITHPAIR:
		result = getTripleStraightWithPairLowestPoker(pokers_);
		break;
	default:
		CC_ASSERT(0 != 0);
		break;
	}

	return result;
}
