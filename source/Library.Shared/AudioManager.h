#pragma once

#include "fmod.hpp"
#include "HashMap.h"
#include "EventMessageAttributed.h"

namespace AnonymousEngine
{

	namespace Audio
	{
		class AudioManager
		{
		public:
			/**
			* The default constructor of class.
			*/
			AudioManager() = default;

			/**
			* The default destructor of class.
			*/
			~AudioManager() = default;

			AudioManager(const AudioManager&) = delete;
			AudioManager(AudioManager&&) = delete;

			void Update(const Containers::EventMessageAttributed& message);

		private:
			static const HashMap<std::string, std::string> mSoundMap;
		};
	}
}