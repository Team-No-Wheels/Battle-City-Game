#include "Pch.h"
#include "Frame.h"

namespace AnonymousEngine
{
	namespace Graphics
	{
		ATTRIBUTED_DEFINITIONS(Frame);

		Frame::Frame()
		{
			AddExternalAttribute("id", &mFrameID, 1);
			AddExternalAttribute("FilePath", &mFilePath, 1);
			AddExternalAttribute("Position", &mPosition, 1);
			AddExternalAttribute("width", &width, 1);
			AddExternalAttribute("height", &height, 1);
		}

		void Frame::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);

			prescribedAttributeNames.PushBack("id");
			prescribedAttributeNames.PushBack("FilePath");
			prescribedAttributeNames.PushBack("Position");
			prescribedAttributeNames.PushBack("width");
			prescribedAttributeNames.PushBack("height");
		}
	}
}