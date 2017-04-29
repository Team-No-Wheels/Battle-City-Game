#pragma once

namespace AnonymousEngine
{
	namespace Core
	{
		enum class PlatformType
		{
			OpenGL,
			DirectX
		};

		/**
			Contains the engine settings.
		*/
		class EngineSettings
		{
		public:
			/**
				@brief Return the platform type.
			*/
			static PlatformType GetPlatform();

			/**
				@brief Set the platform type.
				@details Never use this function in code. This is set from DirectX or OpenGl project.
				@param[in] pPlatformType Type of platform. This is set from the engine main.
			*/
			static void SetPlatform(PlatformType pPlatformType);

			/**
				@brief Return screen width.
				@return unsigned int that holds the screen width.
			*/
			static std::uint32_t GetScreenWidth();

			/**
				@brief Return screen height.
				@return unsigned int that holds the screen height.
			*/
			static std::uint32_t GetScreenHeight();

			/**
				@brief Set the screen width.
				@details Never use this function in code. This is set from DirectX or OpenGl project.
				@param[in] unsigned int that holds the screen width.
			*/
			static void SetScreenWidth(std::uint32_t pScreenWidth);

			/**
				@brief Set the screen height.
				@details Never use this function in code. This is set from DirectX or OpenGl project.
				@param[in] unsigned int that holds the screen height.
			*/
			static void SetScreenHeight(std::uint32_t pScreenHeight);
		private:
			/**
				Holds the platform type.
			*/
			static PlatformType sPlatformType;

			/**
				Holds the screen width.
			*/
			static std::uint32_t sScreenWidth;

			/**
				Holds the screen height.
			*/
			static std::uint32_t sScreenHeight;
		};
	}
}