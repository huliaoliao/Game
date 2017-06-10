#ifndef					__POKER_SPRITE_H__
#define					__POKER_SPRITE_H__

/*	�˿˾��飨�������˿˲�����ʾ��	---	2017.6.9
*/

#include "cocos2d.h"
#include "Poker.h"

class PokerSprite : public cocos2d::Node
{
public:
	static PokerSprite* create(cocos2d::Sprite* pokerSprite_, const Poker& poker_);

public:
	PokerSprite* clone();

private:
	PokerSprite(cocos2d::Sprite* pokerSprite_, const Poker& poker_);

	~PokerSprite();

private:
	virtual bool init() override;

	bool initView();

	bool initContent();

public:
	//���������ƣ���ʾ�����
	void selectedPokersOut();

	//��������ٴε�����ص�δ���λ��
	void selectedPokerBack();

public:
	//�Ƿ��ܱ����
	CC_SYNTHESIZE(bool, canClick, CanClick);	
	
	//�Ƿ���ѡ
	CC_SYNTHESIZE(bool, isSelected, IsSelected);

private:
	cocos2d::Sprite* _pokerSprite;
	Poker				 _poker;
};

#endif