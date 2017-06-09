#ifndef					__HEADIMAGE_LAYER_H__
#define					__HEADIMAGE_LAYER_H__

/*	��Ҳ㣺������ͷ����Ϣ	---	2017.6.7 
*/

#include "cocos2d.h"

class HeadImage;

class HeadImageLayer : public cocos2d::Layer
{
public:
	static void createLayer();

	static void destroyLayer();

private:
	CREATE_FUNC(HeadImageLayer);

	virtual bool init() override;

private:
	bool initView();

	bool initContent();

	//������ͷ������Ϊũ��
	void updateHeadImage();

private:
	//��Բ�ͬ��callback����Ŀ��ͷ������Ϊ����

	void updateHolderHeadImageCallback(cocos2d::Ref*);

	void updateComputerOneHeadImageCallback(cocos2d::Ref*);

	void updateComputerTwoHeadImageCallback(cocos2d::Ref*);

private:
	HeadImage* _computerOneHeadImage;
	HeadImage* _computerTwoHeadImage;
	HeadImage* _holdPlayerHeadImage;
};

#endif