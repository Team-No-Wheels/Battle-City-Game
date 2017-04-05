
#include "Print.h"

#include <iostream>
#include "../../../../../../../../../../Program Files (x86)/Microsoft Visual Studio 14.0/VC/UnitTest/include/CppUnitTestLogger.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(Print)

		Print::Print(const std::string& name) :
			Action(name)
		{
			AddExternalAttribute("PrintString", &mPrintString, 1);
		}

		void Print::Update(WorldState& worldState)
		{
			worldState.mAction = this;
			Microsoft::VisualStudio::CppUnitTestFramework::Logger::WriteMessage(mPrintString.c_str());
			worldState.mAction = nullptr;
		}

		void Print::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("PrintString");
		}

		ACTION_FACTORY_DEFINITIONS(Print)
	}
}
