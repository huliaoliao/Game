#ifndef					__POKER_LAYER_H__
#define					__POKER_LAYER_H__

/* �˿˲�	---	2017.6.9
*/

#include "cocos2d.h"
#include "PokerSprite.h"

class PokerLayer : public cocos2d::Layer
{
public:
	//������
	static void createLayer();

	//���ٲ�
	static void destroyLayer();

private:
	CREATE_FUNC(PokerLayer);

private:
	virtual bool init() override;

	bool initView();

	bool initContent();

private:
	void displayPokers(const std::vector<PokerSprite*>& pokers_, float displayMaxWidth_,
		float displayStartX_, float displayMiddleX_, float displayY_, bool isOnScene_, const float SCALE = 1.0f);

private:
	//��ʾ������е��ƻص�
	void displayHolderPokersCallback(cocos2d::Ref* sender_);

	//��ʾԤ������������
	void displayLandlordPokersCallback(cocos2d::Ref* sender_);

private:
	std::vector<PokerSprite*> _lastHolderPokerSprites;	//�ֶ������һ�ֳ��е���
};

#endif