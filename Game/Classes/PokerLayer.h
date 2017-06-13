#ifndef					__POKER_LAYER_H__
#define					__POKER_LAYER_H__

/* �˿˲�	---	2017.6.9
*/

#include "cocos2d.h"
#include "PokerSprite.h"

class CountDown;
class ScalableMenuItemSprite;

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

	std::vector<PokerSprite*> createPokerSprites(const std::vector<Poker>& pokers);

private:
	//��ʾԤ������������
	void displayLandlordPokersCallback(cocos2d::Ref* sender_);

	//��ʾ������е��ƻص�
	void displayHolderPokersCallback(cocos2d::Ref* sender_);

	//ɾ���ֶ������һ�ִ������
	void destroyHolderLastOutPokersCallback(cocos2d::Ref* sender_);

	//��ʾ�ֶ������һ�ִ������
	void displayHolderOutPokersCallback(cocos2d::Ref* sender_);

	//ɾ���������1��һ�ִ������
	void destroyComputerOneLastOutPokersCallback(cocos2d::Ref* sender_);

	//��ʾ�������1��һ�ִ������
	void displayComputerOneOutPokersCallback(cocos2d::Ref* sender_);

	//ɾ���������2��һ�ִ������
	void destroyComputerTwoLastOutPokersCallback(cocos2d::Ref* sender_);

	//��ʾ�������2��һ�ִ������
	void displayComputerTwoOutPokersCallback(cocos2d::Ref* sender_);

	//������ذ�ť�ص�
	//��ʾ������ذ�ť�����ز���Ҫд��
	void displayHolderOutPokersBtnsCallback(cocos2d::Ref*);

	//����ư�ť�ɰ��ص�
	void outPokersBtnEnabledCallback(cocos2d::Ref*);

	//����ư�ť���ɰ��ص�
	void outPokersBtnDisabledCallback(cocos2d::Ref*);

	//����ʾ��ť�ɰ��ص�
	void hintBtnEnabledCallback(cocos2d::Ref*);

	//������ť�ص�
	void passBtnCallback(cocos2d::Ref* sender_);

	//���ư�ť�ص�
	void outPokersBtnCallback(cocos2d::Ref* sender_);

	//��ʾ��ť�ص�
	void hintBtnCallback(cocos2d::Ref* sender_);

	//ѡ����ʾ��hint���˿ˣ�����ֶ���ң��Ļص�
	void makeHintPokersSelectedCallback(cocos2d::Ref* sender_);

	//��ʾû�д�ù��ϼҵ��ƵĻص�
	void showPassHintCallback(cocos2d::Ref* sender_);

private:
	//�ֶ���Ҽ�ʱ����ʼ��ʱ�ص�
	void holderStartCountDownCallback(cocos2d::Ref* sender_);

	//�ֶ���Ҽ�ʱ��ֹͣ��ʱ�ص�
	void holderStopCountDownCallback(cocos2d::Ref* sender_);

	//�������1��ʱ����ʼ��ʱ�ص�
	void computerOneStartCountDownCallback(cocos2d::Ref* sender_);

	//�������2��ʱ����ʼ��ʱ�ص�
	void computerTwoStartCountDownCallback(cocos2d::Ref* sender_);

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
	ScalableMenuItemSprite* _outPokersBtn;	//���ư�ť
	ScalableMenuItemSprite* _hintBtn;	//��ʾ��ť

	//��ʱ��
	CountDown*						_holderCountDown;	//�ֶ���ҵ���ʱ��
	CountDown*						_computerOneCountDown;	//�������1����ʱ��
	CountDown*						_computerTwoCountDown;	//�������2����ʱ��

	cocos2d::Sprite*				_passHintSprite;	//û�д�ù��ϼҵ�����ʾ����
};

#endif