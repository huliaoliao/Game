#include "Poker.h"

#include "Common.h"

Poker::Poker(Type type_, int value_ /* = 0 */)
	: type(type_), value(value_)
{
}

bool Poker::operator==(const Poker& poker_)
{
	return (this->type == poker_.type)
		&& (this->value = poker_.value);
}

namespace std
{
	bool operator==(const Poker& lhs_, const Poker& rhs_)
	{
		return (lhs_.type == rhs_.type)
			&& (lhs_.value == rhs_.value);
	}
};
