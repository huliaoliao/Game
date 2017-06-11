#include "PokerUtil.h"

bool util::PokerUtil::pokerCmp(const Poker& lhs_, const Poker& rhs_, bool withType_)
{
	//����Ǵ�С������ôֱ���жϲ����رȽϽ��
	if (lhs_.type == Poker::REDJOKER)
	{
		return true;
	}
	else if (rhs_.type == Poker::REDJOKER)
	{
		return false;
	}
	else if (lhs_.type == Poker::BLACKJOKER)
	{
		return true;
	}
	else if (rhs_.type == Poker::BLACKJOKER)
	{
		return false;
	}

	//�Ǵ�С��
	int lhsValue = lhs_.value;
	int rhsValue = rhs_.value;
	//����˿˵�����ֵ��ͬ����ôֱ�Ӹ��ݻ�ɫ����
	if (lhsValue == rhsValue)
	{
		if (withType_ == true)
		{
			return lhs_.type > rhs_.type;
		}
		else if (withType_ == false)
		{
			return false;	//��ȾͲ��� >,��˷���false
		}
	}
	else
	{
		//����˿˵�����ֵ���ȣ���ô���Ƚ�A��2���������Ȼ���������ֵ��С���򼴿�
		if (lhsValue == 2)
		{
			return true;
		}
		else if (rhsValue == 2)
		{
			return false;
		}
		else if (lhsValue == 1)
		{
			return true;
		}
		else if (rhsValue == 1)
		{
			return false;
		}
		
		return lhsValue > rhsValue;
	}
}

bool util::PokerUtil::pokerCmpWithType(const Poker& lhs_, const Poker& rhs_)
{
	return pokerCmp(lhs_, rhs_, true);
}

bool util::PokerUtil::pokerCmpWithoutType(const Poker& lhs_, const Poker& rhs_)
{
	return pokerCmp(lhs_, rhs_, false);
}

void util::PokerUtil::sort(std::vector<Poker>& pokers_)
{
	std::sort(pokers_.begin(), pokers_.end(), pokerCmpWithType);
}

Poker util::PokerUtil::getGreaterPoker(Poker poker_, int increaseValue /*= 1*/)
{
	//��������ҵ��Ʊȵ�ǰС
	CC_ASSERT(increaseValue >= 0, "increaseValue < 0");

	int curValue = poker_.value;
	int needValue = curValue + increaseValue;
	if (needValue >= 3 && needValue <= 13)
	{
		poker_.value = needValue;
		return poker_;
	}
	switch (needValue)
	{
	case 14:
		poker_.value = 1;
		break;
	case 15:
		poker_.value = 2;
		break;
	case 16:
		poker_.type = Poker::BLACKJOKER;
		poker_.value = 0;
		break;
	case 17:
		poker_.type = Poker::REDJOKER;
		poker_.value = 0;
		break;
	default:
		poker_.type = Poker::NONE;
		break;
	}

	return poker_;
}



