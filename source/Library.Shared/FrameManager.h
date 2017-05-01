#pragma once
#include "Frame.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		typedef AnonymousEngine::Containers::Entity Entity;

		/** Manager class for Frame objects.
		*/
		class FrameManager :public Entity
		{
			ATTRIBUTED_DECLARATIONS(FrameManager, Entity)
		public:
			/** Zero-parameterized constructor. Initializes the private members of the class.
			*/
			FrameManager();

			/** Takes in the name of the Frame and returns a pointer to it.
			*	@returns Returns the pointer to the found frame. Returns nullptr if the name wasn't found.
			*/
			Frame* GetFrameEntity(const std::string& name);

			/** Takes in the name of the Frame and returns a pointer to it.
			*	@returns Returns the pointer to the found frame. Returns nullptr if the name wasn't found.
			*/
			const Frame* GetFrameEntity(const std::string& name) const;

			/** Takes in the ID of the Frame and returns a pointer to it.
			*	@returns Returns the pointer to the found frame. Returns nullptr if the ID wasn't found.
			*/
			Frame* GetFrameEntity(const std::int32_t frameID);

			/** Takes in the ID of the Frame and returns a pointer to it.
			*	@returns Returns the pointer to the found frame. Returns nullptr if the ID wasn't found.
			*/
			const Frame* GetFrameEntity(const std::int32_t frameID) const;

			/** Iterates through all the child frames and stores a pointer to them in the Hashmap.
			*	Note: This must be called once.
			*/
			void StoreAllFrames();			

			/** Defaulted destructor.
			*/
			~FrameManager() = default;
		private:
			/** Prescribed attribute for the name/file of the sprite sheet.
			*/
			std::string mSpriteSheetName;

			/** Attribute name for the Frame 
			*/
			static const std::string sFrameIDAttribute;

			/** Attribute name for the name/file of the sprite sheet.
			*/
			static const std::string sSpriteSheetAttributeName;

			/** Hashmap containing the Frame IDs mapped to the Frame.
			*/
			HashMap<int32_t, Frame*> mHashmapSpriteID;
		};

		ENTITY_FACTORY_DECLARATIONS(FrameManager)
	}
}