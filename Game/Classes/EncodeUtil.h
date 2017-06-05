#ifndef					__ENCODE_UTIL_H__
#define					__ENCODE_UTIL_H__

#include "cocos2d.h"

namespace util
{
	//GB2312תUTF-8
	bool IsUTF8(const void* pBuffer, long lstr_size);

	const char* GBToUTF8(const char* str);

	const char *StrongGBToUTF8(const char *str);
}

#endif