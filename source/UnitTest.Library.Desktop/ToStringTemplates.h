#pragma once
#include <string>
#include <cstdint>
#include "Foo.h"
#include "SList.h"

namespace Microsoft
{
	namespace VisualStudio
	{
		namespace CppUnitTestFramework
		{
			template<>
			inline std::wstring ToString<UnitTestLibraryDesktop::Foo>(const UnitTestLibraryDesktop::Foo& foo)
			{
				return std::to_wstring(foo.Data());
			}

			template<>
			inline std::wstring ToString<AnonymousEngine::SList<std::uint32_t>::Iterator>(const AnonymousEngine::SList<std::uint32_t>::Iterator& it)
			{
				std::wstring valueString;
				try
				{
					valueString = std::to_wstring(*it);
				}
				catch(std::exception)
				{
				}
				return valueString;
			}

			template<>
			inline std::wstring ToString<AnonymousEngine::SList<std::uint32_t*>::Iterator>(const AnonymousEngine::SList<std::uint32_t*>::Iterator& it)
			{
				std::wstring valueString;
				try
				{
					valueString = std::to_wstring(reinterpret_cast<std::uintptr_t>(*it));
				}
				catch (std::exception)
				{
				}
				return valueString;
			}

			template<>
			inline std::wstring ToString<AnonymousEngine::SList<UnitTestLibraryDesktop::Foo>::Iterator>(const AnonymousEngine::SList<UnitTestLibraryDesktop::Foo>::Iterator& it)
			{
				std::wstring valueString;
				try
				{
					valueString = std::to_wstring((*it).Data());
				}
				catch (std::exception)
				{
				}
				return valueString;
			}
		}
	}
}
