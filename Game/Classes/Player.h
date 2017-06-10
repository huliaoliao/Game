#ifndef					__PLAYER_H__
#define					__PLAYER_H__

/* �����	---	2017.6.7
*/

#include "cocos2d.h"
#include "PokerController.h"

class OutPokers;

class Player : public cocos2d::Ref
{
public:
	enum Type
	{
		LANDLORD,
		FARMER
	};
public:
	void setPokers(const std::vector<Poker>& pokers_);

	void pushPoker(const Poker& poker_);

	int getCallScore() const;

	void setCallScore(int score_);

	//����������
	Type getPlayerType() const;

	void setPlayerType(Type type_);

	void setPokersCanClick(bool canClick_);

public:
	//�е���
	virtual void callLandlord() = 0;

	//����
	virtual void outPokers(const OutPokers* outPokers_) = 0;

protected:
	std::vector<Poker>	 _holdPokers;		//���е���
	std::vector<Poker>	 _outedPokers;	//��ǰ�������
	int							 _callScore;
	Type							 _type;				//�������
	OutPokers*				_lastOutPokers;	//��һ���˿ˣ���ʼ��Ϊnullptr���ֵ������ʱ��ȡ�������ƺ������nullptr
};

#endif