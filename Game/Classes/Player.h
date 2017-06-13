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

	bool isWinner() const;	//�����Ƿ�������ж��Ƿ���Ӯ��

public:
	//�е���
	virtual void callLandlord() = 0;

	//����
	virtual void outPokers(OutPokers* lastOutPokers_) = 0;

	//���ƻص����ṩ����ʱ����ʱ�������ã�
	virtual void outPokersCallback() = 0;

	//������һ����ҳ����Ʋ��Һ��ʵ���
	virtual std::vector<Poker> searchOutPokers(OutPokers* lastOutPokers_);

	//���ݳ����ƣ�����һ��OutPokers�������ڼ�¼��һ������Ϣ
	OutPokers* createLastOutPokers(const std::vector<Poker>& pokers_);

protected:
	std::vector<Poker>	_holdPokers;		//���е���
	std::vector<Poker>	 _outedPokers;	//��ǰ�������
	//cocos2d::Vector<Poker*>	_outedPokersForPost;	//��ǰ������ƣ�������Ϣ���ݣ�����ʹ�þֲ�����������Ϣ������
	int							 _callScore;
	Type							 _type;				//�������
	//OutPokers*				_lastOutPokers;	//��һ���˿ˣ���ʼ��Ϊnullptr���ֵ������ʱ��ȡ�������ƺ������nullptr
};

#endif