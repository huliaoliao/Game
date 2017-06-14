#ifndef					__WINDOW_UTIL_H__
#define					__WINDOW_UTIL_H__

/*	������صĺ����ͱ�����������Ļ����	---	2017.6.14
*/

#include "cocos2d.h"

namespace util
{
	struct WindowUtil
	{
		//��ʼ����������صı���ֵ
		static float baseWidth;	//��ƿ��
		static float baseHeight;	//��Ƹ߶�
		static float screenWidth;	//��Ļ���
		static float screenHeight;	//��Ļ�߶�
		static float	 scaleX;		//ˮƽ����ֵ
		static float scaleY;		//��ֱ����ֵ

		//��ʼ����Ƴߴ�
		static void doInit(const cocos2d::Size& designSize_);
	};
};

//�궨�壬������д�ͷ���
#define	 SCALE_X	util::WindowUtil::scaleX	
#define SCALE_Y	util::WindowUtil::scaleY
#define BASE_WIDTH util::WindowUtil::baseWidth
#define BASE_HEIGHT util::WindowUtil::baseHeight
#define SCREEN_WIDTH util::WindowUtil::screenWidth
#define SCREEN_HEIGHT util::WindowUtil::screenHeight
#define MIN_SCALE std::min(SCALE_X, SCALE_Y)
#define SCALE MIN_SCALE
#define MAX_SCALE std::max(SCALE_X, SCALE_Y)
#define MIDDLE_SCALE (SCALE_X + SCALE_Y ) / 2.0f

#endif