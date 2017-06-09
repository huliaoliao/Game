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
		static bool pokerCmp(const Poker& lhs_, const Poker& rhs_, bool withType_);

		static bool pokerCmpWithType(const Poker& lhs_, const Poker& rhs_);

		static bool pokerCmpWithoutType(const Poker& lhs_, const Poker& rhs_);

		void sort(std::vector<Poker>& pokers_);
	};
};

#endif