#ifndef					__HOLDER_PLAYER_H__
#define					__HOLDER_PLAYER_H__

/* �ֶ����	---	2017.6.9
*/

#include "Player.h"

class Poker;

class HolderPlayer : public Player
{
public:
	HolderPlayer();

private:
	bool init();

	bool initContent();

public:
	//�ֶ������ʾ���е���
	void displayPokers();

	virtual void callLandlord() override;

	virtual void outPokers(OutPokers* lastOutPokers_) override;

	virtual void outPokersCallback() override;

	//�ͻ��ຯ���������ǣ�������Բ���
	virtual std::vector<Poker> searchOutPokers(OutPokers* lastOutPokers_) override;

private:
	//���������Ƿ���Գ�
	bool isPokerWaitForOutCanOut();

	//���ó��ư�ť�Ƿ�ɰ�
	void checkOutPokerBtnEnabled();

private:
	//�Ӵ�����������ɾ��ĳ���ƻص�
	void deletePokerWaitForOutCallback(cocos2d::Ref* sender_);

	//�����������������ĳ���ƻص�
	void addPokerWaitForOutCallback(cocos2d::Ref* sender_);

	//������ư�ť��ĳ��ƻص�
	void holderOutPokersCallback(cocos2d::Ref*);

	void clickHintBtnCallback(cocos2d::Ref*);

private:
	std::vector<Poker>			_pokersWaitForOut;		//�ѵ��׼��������
	std::vector<Poker>			_hintPokers;	//��ʾ����
	//cocos2d::Vector<Poker*>	_holderPokerForPost;		//��ҳ��е��ƣ�������Ϣ���ݣ�
	OutPokers*						_lastOutPokers;		//����ֶ����ǰһ����ҳ����ƣ�
};

#endif