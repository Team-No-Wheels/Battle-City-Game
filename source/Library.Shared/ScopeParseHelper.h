#pragma once

#include "IXmlParseHelper.h"
#include <functional>
#include "HashMap.h"
#include "ScopeSharedData.h"

namespace AnonymousEngine
{
	namespace Parsers
	{
		class ScopeParseHelper final : public IXmlParserHelper
		{
		public:
			typedef AnonymousEngine::HashMap<std::string, std::string> AttributeMap;
			typedef std::function<void(ScopeParseHelper& helper, ScopeSharedData& sharedData, const AttributeMap& attributes)> StartHandlerFunction;
			typedef std::function<void(ScopeParseHelper& helper, ScopeSharedData& sharedData)> EndHandlerFunction;

			/** Initialize an instance of this helper
			 */
			ScopeParseHelper() = default;
			/** Free up allocated resources
			 */
			~ScopeParseHelper() = default;

			/** Delete copy constructor
			 */
			ScopeParseHelper(const ScopeParseHelper&) = delete;
			/** Delete copy assignment operator
			*/
			ScopeParseHelper& operator=(const ScopeParseHelper&) = delete;
			
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
			static void HandleIntegerStart(ScopeParseHelper& helper, ScopeSharedData& sharedData, const AttributeMap& attributes);
			static void HandleFloatStart(ScopeParseHelper& helper, ScopeSharedData& sharedData, const AttributeMap& attributes);
			static void HandleStringStart(ScopeParseHelper& helper, ScopeSharedData& sharedData, const AttributeMap& attributes);
			static void HandleVectorStart(ScopeParseHelper& helper, ScopeSharedData& sharedData, const AttributeMap& attributes);
			static void HandleMatrixStart(ScopeParseHelper& helper, ScopeSharedData& sharedData, const AttributeMap& attributes);
			static void HandleScopeStart(ScopeParseHelper& helper, ScopeSharedData& sharedData, const AttributeMap& attributes);

			static void HandleCommonEnd(ScopeParseHelper& helper, ScopeSharedData& sharedData);
			static void HandleMatrixEnd(ScopeParseHelper& helper, ScopeSharedData& sharedData);
			static void HandleScopeEnd(ScopeParseHelper& helper, ScopeSharedData& sharedData);

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

			RTTI_DECLARATIONS(ScopeParseHelper, IXmlParserHelper)
		};
	}
}
