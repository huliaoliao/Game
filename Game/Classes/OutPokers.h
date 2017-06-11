#ifndef					__OUT_POKERS_H__
#define					__OUT_POKERS_H__

/* ���Ƽ��ϣ���������������ƣ�		---	2017.6.10
*/

#include "cocos2d.h"

#include "Poker.h"
#include "PokerSetType.h"

class Player;

class OutPokers : public cocos2d::Ref
{
public:
	OutPokers(Player* pokerOwner_, Poker poker_, size_t totalLen_, PokersType pokersType_);

public:
	PokersType getPokersType() const;

	void setPokersType(PokersType pokersType_);

	size_t getTotalLen() const;

	void setTotalLen(size_t totalLen_);

	Poker getLowestPoker() const;

	void setLowestPoker(Poker poker_);

	Player* getPokerOwner() const;

private:
	PokersType	_pokersType;	//��ǰ������
	size_t				_totalLen;		//��������ĳ��ȣ�����334455�ĳ�����6
	Poker				_lowestPoker;	//����������ֵ��С����
	Player*				_outPokersOwner;	//��ǰ�˿˳�����
};

#endif