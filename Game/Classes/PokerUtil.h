#ifndef					__POKER_UTIL_H__
#define					__POKER_UTIL_H__

/* �˿���صĺ���		---	2017.6.9
*/

#include "Poker.h"

namespace util
{
	namespace PokerUtil
	{
		//lhs_ > rhs_ �ŷ���true
		//����static�������ļ��ڲ��ɵ��øú���
		static bool pokerCmp(const Poker& lhs_, const Poker& rhs_, bool withType_);

		static bool pokerCmpWithType(const Poker& lhs_, const Poker& rhs_);

		bool pokerCmpWithoutType(const Poker& lhs_, const Poker& rhs_);

		void sort(std::vector<Poker>& pokers_);

		//��ȡ��poker_ֵ��increaseValue����
		Poker getGreaterPoker(Poker poker_, int increaseValue = 1);
	};
};

#endif