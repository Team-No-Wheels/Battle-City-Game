#include "Compare.h"
#include <cstring>

namespace AnonymousEngine
{
	bool DefaultCompare<const char*>::operator()(const char* lhs, const char* rhs) const
	{
		return (strcmp(lhs, rhs) == 0);
	}
}
