#pragma once

namespace AnonymousEngine
{
	template <typename T>
	bool DefaultCompare<T>::operator()(const T& lhs, const T& rhs) const
	{
		return (lhs == rhs);
	}
}
