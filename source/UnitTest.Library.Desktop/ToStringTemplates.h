#pragma once
#include <string>
#include "Foo.h"
#include "SList.h"

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			std::wstring ToString<UnitTestLibraryDesktop::Foo>(const UnitTestLibraryDesktop::Foo& foo)
			{
				return std::to_wstring(foo.Data());
			}
		}
	}
}
