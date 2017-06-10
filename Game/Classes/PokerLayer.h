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

	bool initListener();

private:
	bool onTouchBegan(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_);

	void onTouchMoved(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_);

	void onTouchEnded(cocos2d::Touch *touch_, cocos2d::Event *unusedEvent_);

private:
	void displayPokers(const std::vector<PokerSprite*>& pokers_, float displayMaxWidth_,
		float displayStartX_, float displayMiddleX_, float displayY_, bool isOnScene_, const float SCALE = 1.0f);

	std::vector<PokerSprite*> createPokerSprites(cocos2d::Ref* sender_);

private:
	//��ʾ������е��ƻص�
	void displayHolderPokersCallback(cocos2d::Ref* sender_);

	//��ʾԤ������������
	void displayLandlordPokersCallback(cocos2d::Ref* sender_);

	//ɾ���ֶ������һ�ִ������
	void destroyHolderLastOutPokersCallback(cocos2d::Ref* sender_);

	//��ʾ�ֶ������һ�ִ������
	void displayHolderOutPokersCallbacl(cocos2d::Ref* sender_);

	//ɾ���������1��һ�ִ������
	void destroyComputerOneLastOutPokersCallback(cocos2d::Ref* sender_);

	//��ʾ�������1��һ�ִ������
	void displayComputerOneOutPokersCallback(cocos2d::Ref* sender_);

	//ɾ���������2��һ�ִ������
	void destroyComputerTwoLastOutPokersCallback(cocos2d::Ref* sender_);

	//��ʾ�������2��һ�ִ������
	void displayComputerTwoOutPokersCallback(cocos2d::Ref* sender_);

	//������ذ�ť�ص�
	//������ť�ص�
	void passBtnCallback(cocos2d::Ref* sender_);

	//���ư�ť�ص�
	void outPokersBtnCallback(cocos2d::Ref* sender_);

	//��ʾ��ť�ص�
	void hintBtnCallback(cocos2d::Ref* sender_);

private:
	std::vector<PokerSprite*> _holderClickedPokerSprites;
	std::vector<PokerSprite*> _lastHolderPokerSprites;	//�ֶ������һ�ֳ��е���
	//��Ŵ�����ƣ����ڸô�ɾ���ϴδ������
	std::vector<PokerSprite*> _lastHolderOutPokersSprites;	//�ֶ������һ�ִ������
	std::vector<PokerSprite*>	_lastComputerOneOutPokersSprites;	//�������1��һ�ִ������
	std::vector<PokerSprite*>	_lastComputerTwoOutPokersSprites;	//�������2��һ�ִ������

	cocos2d::Sprite*				_holderPassSprite;		//�ֶ���Ҳ�����ť
	cocos2d::Sprite*				_computerOnePassSprite;	//�������1������ť
	cocos2d::Sprite*				_computerTwoPassSprite;	//�������2������ť

	cocos2d::Menu*				_btnMenu;		//���ư�ť�˵�
};

#endif