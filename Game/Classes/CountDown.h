#ifndef					__COUNT_DOWN_H__
#define					__COUNT_DOWN_H__

/*	��ʱ����������ʾ��	---	2017.6.13
*/

#include "cocos2d.h"

class CountDown : public cocos2d::Node
{
public:
	CREATE_FUNC(CountDown);

private:
	virtual bool init() override;

	bool initView();

private:
	void countDown(float delta_);

public:
	//��ʼ��ʱ
	void startCountDown();

	//������ʱ
	void stopCountDown();

	//���ü�ʱʱ��
	void setCountDownUpper(float upper_); 

	//���ûص�����
	void setCallbackFunc(const std::function<void(void)>& func_);

private:
	int				_totalSpriteNum;	//���м�ʱͼƬ����Ŀ
	int				_curSpriteIndex;	//��ǰ��ʱͼƬ���±�
	float				_countDownUp;	//��ʱ����
	float				_counting;				//���ڼ�ʱ

private:
	cocos2d::Sprite*	_sprite;	//��ʱͼƬ����
	cocos2d::LabelAtlas*	_labelAltas;	//��ʱ�ز��������

private:
	std::function<void(void)>		_callbackFunc;
};

#endif