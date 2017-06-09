#ifndef					__POKER_H__
#define					__POKER_H__

/* �˿�	--- 2017.6.9
*/

#include "cocos2d.h"

#include "Common.h"

struct Poker : public cocos2d::Ref
{
	enum Type
	{
		DIAMOND = 0,			//����
		CLUB,						//÷��
		HEART,						//����
		SPADE = 3,				//����
		BLACKJOKER = 52,	//С��
		REDJOKER = 53,		//����
		BACK = 54,				//�˿˱���
	};

	Poker(Type type_, int value_ = 0);

	bool operator==(const Poker& poker_);

	Type type;		//����
	int    value;	//��ֵ
};

namespace std
{
	template<>
	struct hash < Poker >
	{
		std::size_t operator()(const Poker& poker_) const
		{
			return poker_.type * SINGLE_TYPE_CARD_NUM + poker_.value;
		}
	};

	bool operator==(const Poker& lhs_, const Poker& rhs_);
};

#endif