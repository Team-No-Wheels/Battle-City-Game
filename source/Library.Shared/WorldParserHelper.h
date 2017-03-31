#pragma once

#include "IXmlParseHelper.h"
#include <functional>
#include "HashMap.h"
#include "WorldSharedData.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class WorldParserHelper final : public IXmlParserHelper
		{
		public:
			typedef AnonymousEngine::HashMap<std::string, std::string> AttributeMap;
			typedef std::function<void(WorldParserHelper& helper, WorldSharedData& sharedData, const AttributeMap& attributes)> StartHandlerFunction;
			typedef std::function<void(WorldParserHelper& helper, WorldSharedData& sharedData)> EndHandlerFunction;

			/** Initialize an instance of this helper
			*/
			WorldParserHelper() = default;
			/** Free up allocated resources
			*/
			~WorldParserHelper() = default;

			/** Delete copy constructor
			*/
			WorldParserHelper(const WorldParserHelper&) = delete;
			/** Delete copy assignment operator
			*/
			WorldParserHelper& operator=(const WorldParserHelper&) = delete;

			/** Create another instance with same state as this one
			*/
			IXmlParserHelper* Clone() override;

			/** Handles start element tags for all int, float, string, vec4, mat4 and scope
			*  @param sharedData The common shared data object which is modified by the helpers
			*  @param name The tag name
			*  @param attributes All the xml element attributes
			*/
			bool StartElementHandler(SharedData& sharedData, const std::string& name, const AttributeMap& attributes) override;
			/** Handles emd element tags for all int, float, string, vec4, mat4 and scope
			*  @param sharedData The common shared data object which is modified by the helpers
			*  @param name The tag name
			*/
			bool EndElementHandler(SharedData& sharedData, const std::string& name) override;

		private:
			static void HandleIntegerStart(WorldParserHelper& helper, WorldSharedData& sharedData, const AttributeMap& attributes);
			static void HandleFloatStart(WorldParserHelper& helper, WorldSharedData& sharedData, const AttributeMap& attributes);
			static void HandleStringStart(WorldParserHelper& helper, WorldSharedData& sharedData, const AttributeMap& attributes);
			static void HandleVectorStart(WorldParserHelper& helper, WorldSharedData& sharedData, const AttributeMap& attributes);
			static void HandleMatrixStart(WorldParserHelper& helper, WorldSharedData& sharedData, const AttributeMap& attributes);
			static void HandleScopeStart(WorldParserHelper& helper, WorldSharedData& sharedData, const AttributeMap& attributes);

			static void HandleCommonEnd(WorldParserHelper& helper, WorldSharedData& sharedData);
			static void HandleMatrixEnd(WorldParserHelper& helper, WorldSharedData& sharedData);
			static void HandleScopeEnd(WorldParserHelper& helper, WorldSharedData& sharedData);

			static void ValidateRequiredAttributes(const AttributeMap& attributes);

			Vector<Datum> mMatrixVectors;
			std::string mMatrixName;

			static const HashMap<std::string, StartHandlerFunction> StartElementHandlers;
			static const HashMap<std::string, EndHandlerFunction> EndElementHandlers;

			static const std::string ROOT_TAG;
			static const std::string NAME;
			static const std::string VALUE;
			static const std::string VECTOR_X;
			static const std::string VECTOR_Y;
			static const std::string VECTOR_Z;
			static const std::string VECTOR_W;

			RTTI_DECLARATIONS(WorldParserHelper, IXmlParserHelper)
		};
	}
}
