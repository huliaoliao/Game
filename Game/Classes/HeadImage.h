#ifndef					__HEADIMAHE_H__
#define					__HEADIMAHE_H__

/* ���ͷ��	---	2017.6.7
*/

#include "cocos2d.h"

class HeadImage : public cocos2d::Node
{
public:
	enum Type
	{
		LEANDLORD,
		FARMER
	};

	enum Orientation
	{
		LEFT,
		RIGHT
	};

public:
	CREATE_FUNC(HeadImage);

public:
	virtual bool init() override;

public:
	void setHeadImageType(Type type_, Orientation orientation_);

private:
	cocos2d::SpriteFrame* createSpriteFrameWithType(Type type_, Orientation orientation_);

private:
	cocos2d::Sprite*	_headBox;		//ͷ���
	cocos2d::Sprite*	_curHeadImage;	//��ǰͷ��

	static cocos2d::SpriteFrameCache* s_spriteFrameCache;
};

#endif