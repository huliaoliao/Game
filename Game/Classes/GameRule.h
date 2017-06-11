#ifndef					__GAME_RULE_H__
#define					__GAME_RULE_H__

/*	��Ϸ���򣨳�����أ�	---	2017.6.11
*/

#include <vector>

#include "Poker.h"
#include "PokerSetType.h"
#include "Singleton.h"

class OutPokers;

//������
class GameRule : public Singleton < GameRule >
{
public:
	//���ݵ�ǰ�����ƺ���һ���ƣ��жϵ�ǰ���Ƿ�ɳ�
	bool canOutPokers(std::vector<Poker> waitOutPokers, const OutPokers& lastOutPokers);

	//�������Լ������������ʱ���ҵ�һ�ź��ʵ���
	//������Ϊ�˸�ʱ�䣬ֻ�Ǽ򵥵��ɵ��ţ����ӣ����ţ�˳�ӣ�ը����
	//��ҪAI���ø��ã����������Ҫ����
	std::vector<Poker> searchProperPokers(const std::vector<Poker>& pokers_);

	//���˵�XX��Y���Y
	std::vector<Poker> filterAccessoryPokers(const std::vector<Poker>& pokers_);

public:
	//���������˿˵�����
	PokersType analysePokersType(std::vector<Poker> pokers_);

	//�Ƿ����˿�����
	bool isPokerValueType(const std::vector<Poker>& pokers_);

	//�������˿��Ƿ���ĳ������
	bool isSpecifiedPokerType(const std::vector<Poker>& pokers_, PokersType pokerType_);

	//��ȡ�˿���ֵ��С���˿�
	Poker getLowestPoker(const std::vector<Poker>& pokers_, PokersType pokerType_);

	/* ��ȡָ�������͵��˿ˣ�����VectorΪ��ʱ��ʾ����ʧ��
	��һ�����������ӵ�е��˿ˣ������������Ƿ��ص����͵��˿�����С���ƣ������nullptr���������Գ�����ֵ�ĸ������˿�
	���ĸ����������˳��ʱ�ĳ��� */
	//���ɲ���
	std::vector<Poker> calcPokersWithType(std::vector<Poker> pokers_, PokersType pokersType_, 
		const Poker* poker_ = nullptr, int length = 0);

	//�ɲ���
	std::vector<Poker> calcPokersWithTypeInSplit(std::vector<Poker> pokers_, PokersType pokersType_, 
		const Poker* poker_ = nullptr, int length = 0);

private:
	/* ��һ����������ҵ����棬�ڶ������ϼҶ�Ӧ���Ƶ���С�˿˵�ָ�룬Ĭ��Ϊnullptr��
	��ʾ���������Ӧ�����ͼ��ɣ�������Ҫ ���� poker_�Ķ�Ӧ���Ͳſ��� */
	//���ҵ���
	std::vector<Poker> searchSingle(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);

	//���Ҷ���
	std::vector<Poker> searchPair(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);

	//��������
	std::vector<Poker> searchTriple(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);

	//����ը��
	std::vector<Poker> searchBomb(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);

	//������ը
	std::vector<Poker> searchKingBomb(const std::vector<Poker>& pokers_);

	//���ҹ̶�ֵ�ĵ��ţ����ӣ�����
	std::vector<Poker> searchSpecifiedSingle(const std::vector<Poker>& pokers_, const Poker* poker_);

	std::vector<Poker> searchSpecifiedPair(const std::vector<Poker>& pokers_, const Poker* poker_);

	std::vector<Poker> searchSpecifiedTriple(const std::vector<Poker>& pokers_, const Poker* poker_);

	/* searchStraight�ǲ�������˳�ӵĻ����������������ֶ�Ҫ�����������,
	length��������˳�ӵĳ����Ƕ��٣�����56789 ���Ⱦ���5
	��˳����������5��˫˳����˳�ĳ���������3*/
	//����˳��
	std::vector<Poker> searchSingleStraight(const std::vector<Poker>& pokers_, int length_, const Poker* poker_);

	//����˫˳
	std::vector<Poker> searchPairStraight(const std::vector<Poker>& pokers_, int length_, const Poker* poker_);

	//������˳
	std::vector<Poker> searchTripleStraight(const std::vector<Poker>& pokers_, int length_, const Poker* poker_);

private:
	//���Ʋ���
	//���ҵ���
	std::vector<Poker> searchSingleInSplit(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);

	//���Ҷ���
	std::vector<Poker> searchPairInSplit(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);

	//��������
	std::vector<Poker> searchTripleInSplit(const std::vector<Poker>& pokers_, const Poker* poker_ = nullptr);
	
private:
	//�Ƿ��ǵ���
	bool isSingle(const std::vector<Poker>& pokers_);

	//�Ƿ��Ƕ���
	bool isPair(const std::vector<Poker>& pokers_);

	//�Ƿ�������
	bool isTriple(const std::vector<Poker>& pokers_);

	//�Ƿ���3��1
	bool isTripleWithSingle(std::vector<Poker> pokers_);

	//�Ƿ���3��2
	bool isTripleWithPair(std::vector<Poker> pokers_);

	//�Ƿ��ǵ�˳��
	bool isSingleStraight(std::vector<Poker> pokers_);

	//�Ƿ���˫˳
	bool isPairStraight(std::vector<Poker> pokers_);

	//�Ƿ����޵��Ż�˫�ŵ���˳
	bool isTripleStraight(std::vector<Poker> pokers_);

	//�Ƿ��Ǵ�ͬ�������ŵ���˳
	bool isTripleStraightWithSingle(std::vector<Poker> pokers_);

	//�Ƿ��Ǵ�ͨ����˫�ŵ���˳
	bool isTripleStraightWithPair(std::vector<Poker> pokers_);

	//�Ƿ���ը��
	bool isBomb(const std::vector<Poker>& pokers_);

	//�Ƿ�����ը
	bool isKingBomb(const std::vector<Poker>& pokers_);

	//�Ƿ��Ǵ�С��
	bool isKing(const Poker& poker_);

private:
	//�Ƿ����ը�������ڷ�������ʱ�������ը����ɵ�����
	bool isExistBomb(const std::vector<Poker>& pokers_);

	//�Ƿ���ֵ�����
	bool isValueEqual(const std::vector<Poker>& pokers_);

	//�Ƿ�Ϊ����
	bool isAllPair(const std::vector<Poker>& pokers_);

	//��pokers_�е��˿˻�ȡ���е����ţ����ص���һ��pair
	//��һ���Ƿ��������
	//�ڶ�����ʣ�µ���
	std::pair<std::vector<Poker>, std::vector<Poker>>
		splitTriplesInPokers(const std::vector<Poker>& pokers_);

	/* ���絥�ţ�����SINGLE������1������2�����Ŷ�����TRIPLE��
		��˳��1����˳��2����˳������TRIPLESTRAIGHT����������Ŀ����Ϊ�˼������ͷ���ȫһ�£�����
		��������ȴ��һ�µ��������Ȼ�Ļ������ź�����1���޷��ȼۣ��������������һֱ�ӷ���TRIPLE��
		�ֻᵼ���������⣬�������ְ취�����еİ취*/
	PokersType getBasePokersType(PokersType pokersType_);

	//��ȡ��˳��1����˳��С����
	Poker getTripleStraightWithSingleLowestPoker(const std::vector<Poker>& pokers_);

	//��ȡ��˳��2����˳��С����
	Poker getTripleStraightWithPairLowestPoker(const std::vector<Poker>& pokers_);
};

#endif