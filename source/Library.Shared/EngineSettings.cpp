#include "Pch.h"
#include "EngineSettings.h"

namespace AnonymousEngine
{
	namespace Core
	{
		std::uint32_t EngineSettings::sScreenWidth;
		std::uint32_t EngineSettings::sScreenHeight;
		PlatformType EngineSettings::sPlatformType;

		PlatformType EngineSettings::GetPlatform()
		{
			return sPlatformType;
		}

		void EngineSettings::SetPlatform(PlatformType pPlatformType)
		{
			sPlatformType = pPlatformType;
		}

		std::uint32_t EngineSettings::GetScreenWidth()
		{
			return sScreenWidth;
		}

		std::uint32_t EngineSettings::GetScreenHeight()
		{
			return sScreenHeight;
		}

		void EngineSettings::SetScreenWidth(std::uint32_t pScreenWidth)
		{
			sScreenWidth = pScreenWidth;
		}

		void EngineSettings::SetScreenHeight(std::uint32_t pScreenHeight)
		{
			sScreenHeight = pScreenHeight;
		}
	}
}

