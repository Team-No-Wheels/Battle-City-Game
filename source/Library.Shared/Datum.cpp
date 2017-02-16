#include "Datum.h"
#include <glm/gtc/type_ptr.hpp>

namespace AnonymousEngine
{
	const std::uint32_t Datum::mTypeSizes[] = {
		0,
		sizeof(std::int32_t),
		sizeof(float),
		sizeof(std::string),
		sizeof(glm::vec4),
		sizeof(glm::mat4),
		sizeof(RTTI*)
	};

	const std::function<void(Datum::DatumValue&, std::uint32_t)> Datum::mDefaultConstructors[] =  {
		[] (DatumValue&, std::uint32_t) { },		// Unknown
		[] (DatumValue& datum, std::uint32_t index) { datum.intValue[index] = 0; },						// Integer
		[] (DatumValue& datum, std::uint32_t index) { datum.floatValue[index] = 0.0f; },				// Float
		[] (DatumValue& datum, std::uint32_t index) { new (&datum.strValue[index]) std::string(""); },	// String
		[] (DatumValue& datum, std::uint32_t index) { new (&datum.vecValue[index]) glm::vec4(); },		// Vec4
		[] (DatumValue& datum, std::uint32_t index) { new (&datum.matValue[index]) glm::mat4(); },		// Mat4
		[] (DatumValue& datum, std::uint32_t index) { datum.rttiPtrValue[index] = nullptr; }			// RTTI*
	};

	const std::function<void(Datum::DatumValue&, std::uint32_t)> Datum::mDestructors[] = {
		[] (DatumValue&, std::uint32_t) { },	// Unknown
		[] (DatumValue&, std::uint32_t) { },	// Integer
		[] (DatumValue&, std::uint32_t) { },	// Float
		[] (DatumValue& datum, std::uint32_t index) { index;  datum;  datum.strValue[index].~basic_string(); },		// String
		[] (DatumValue& datum, std::uint32_t index) { index;  datum;  datum.vecValue[index].~tvec4(); },			// Vec4
		[] (DatumValue& datum, std::uint32_t index) { index;  datum;  datum.matValue[index].~tmat4x4(); },			// Mat4
		[] (DatumValue&, std::uint32_t) { }		// RTTI*
	};

	const std::function<bool(const Datum::DatumValue&, const Datum::DatumValue&, std::uint32_t)> Datum::mComparators[] = {
		[] (const DatumValue&, const DatumValue&, std::uint32_t) { return true; },		// Unknown
		[] (const DatumValue& lhs, const DatumValue& rhs, std::uint32_t index) { return lhs.intValue[index] == rhs.intValue[index]; },			// Integer
		[] (const DatumValue& lhs, const DatumValue& rhs, std::uint32_t index) { return lhs.floatValue[index] == rhs.floatValue[index]; },		// Float
		[] (const DatumValue& lhs, const DatumValue& rhs, std::uint32_t index) { return lhs.strValue[index] == rhs.strValue[index]; },			// String
		[] (const DatumValue& lhs, const DatumValue& rhs, std::uint32_t index) { return lhs.vecValue[index] == rhs.vecValue[index]; },			// Vec4
		[] (const DatumValue& lhs, const DatumValue& rhs, std::uint32_t index) { return lhs.matValue[index] == rhs.matValue[index]; },			// Mat4
		[] (const DatumValue& lhs, const DatumValue& rhs, std::uint32_t index) { return lhs.rttiPtrValue[index] == rhs.rttiPtrValue[index]; }	// RTTI*
	};

	const std::function<void(Datum::DatumValue&, const Datum::DatumValue&, std::uint32_t)> Datum::mCloners[] = {
		[] (DatumValue&, const DatumValue&, std::uint32_t) { },		// Unknown
		[] (DatumValue& lhs, const DatumValue& rhs, std::uint32_t index) { lhs.intValue[index] = rhs.intValue[index]; },			// Integer
		[] (DatumValue& lhs, const DatumValue& rhs, std::uint32_t index) { lhs.floatValue[index] = rhs.floatValue[index]; },		// Float
		[] (DatumValue& lhs, const DatumValue& rhs, std::uint32_t index) { lhs.strValue[index] = rhs.strValue[index]; },			// String
		[] (DatumValue& lhs, const DatumValue& rhs, std::uint32_t index) { lhs.vecValue[index] = rhs.vecValue[index]; },			// Vec4
		[] (DatumValue& lhs, const DatumValue& rhs, std::uint32_t index) { lhs.matValue[index] = rhs.matValue[index]; },			// Mat4
		[] (DatumValue& lhs, const DatumValue& rhs, std::uint32_t index) { lhs.rttiPtrValue[index] = rhs.rttiPtrValue[index]; }		// RTTI*
	};

	const std::function<void(const std::string&, Datum::DatumValue&, std::uint32_t)> Datum::mDeserializers[] = {

		[] (const std::string&, DatumValue&, std::uint32_t) {},		// Unknown
		[] (const std::string& str, DatumValue& datum, std::uint32_t index) { datum.intValue[index] = std::stoi(str); },	// Integer
		[] (const std::string& str, DatumValue& datum, std::uint32_t index) { datum.floatValue[index] = std::stof(str); },	// Float
		[] (const std::string& str, DatumValue& datum, std::uint32_t index) { datum.strValue[index] = str; },				// String
		[] (const std::string& str, DatumValue& datum, std::uint32_t index)													// Vec4
			{
				glm::vec4& vector = datum.vecValue[index];
				std::size_t tempPos;
				std::size_t pos = 0;
				vector.x = std::stof(str, &tempPos);
				pos += (tempPos + 1);
				vector.y = std::stof(str.substr(pos), &tempPos);
				pos += (tempPos + 1);
				vector.z = std::stof(str.substr(pos), &tempPos);
				pos += (tempPos + 1);
				vector.w = std::stof(str.substr(pos), &tempPos);
			},
		[] (const std::string& str, DatumValue& datum, std::uint32_t index)													// Mat4
			{
				glm::mat4& mat = datum.matValue[index];
				float values[16];
				std::size_t tempPos;
				std::size_t pos = 0;
				for(std::uint32_t i = 0; i < 16; ++i)
				{
					values[i] = std::stof(str.substr(pos), &tempPos);
					pos += (tempPos + 1);
				}
				mat = glm::make_mat4(values);
			},
		[] (const std::string& str, DatumValue& datum, std::uint32_t index) { datum.rttiPtrValue[index]->FromString(str); }	// RTTI*
	};

	const std::function<std::string(const Datum::DatumValue&, std::uint32_t)> Datum::mSerializers[] = {
		[] (const DatumValue&, std::uint32_t) { return ""; },		// Unknown
		[] (const DatumValue& datum, std::uint32_t index) { return std::to_string(datum.intValue[index]); },		// Integer
		[] (const DatumValue& datum, std::uint32_t index) { return std::to_string(datum.floatValue[index]); },		// Float
		[] (const DatumValue& datum, std::uint32_t index) { return datum.strValue[index]; },						// String
		[] (const DatumValue& datum, std::uint32_t index)															// Vec4
			{
				const glm::vec4& vector = datum.vecValue[index];
				return std::to_string(vector.x) + "," + std::to_string(vector.y) + "," + std::to_string(vector.z) + "," + std::to_string(vector.w);
			},
		[] (const DatumValue& datum, std::uint32_t index)															// Mat4
			{
				const glm::mat4& mat = datum.matValue[index];
				const float *values = static_cast<const float*>(glm::value_ptr(mat));
				std::string output = std::to_string(values[0]);
				for (std::uint32_t i = 1; i < 16; ++i)
				{
					output += "," + std::to_string(values[i]);
				}
				return output;
			},
		[] (const DatumValue& datum, std::uint32_t index) { return datum.rttiPtrValue[index]->ToString(); }			// RTTI*
	};

	Datum::Datum(DatumType type) :
		mType(type), mSize(0), mIsExternal(false)
	{
		mData.voidPtr = nullptr;
	}

	Datum::Datum(const Datum& datum)
	{
		Copy(datum);
	}

	void Datum::SetType(DatumType type)
	{
		ValidateType(type);
		mType = type;
	}

	Datum::DatumType Datum::Type() const
	{
		return mType;
	}

	Datum& Datum::operator=(const Datum& datum)
	{
		if (&datum != this)
		{
			Copy(datum);
		}
		return (*this);
	}

	Datum& Datum::operator=(const std::int32_t& data)
	{
		InitializeScalar(DatumType::Integer);
		mData.intValue[0] = data;
		return (*this);
	}

	Datum& Datum::operator=(const float& data)
	{
		InitializeScalar(DatumType::Float);
		mData.floatValue[0] = data;
		return (*this);
	}

	Datum& Datum::operator=(const std::string& data)
	{
		InitializeScalar(DatumType::String);
		mData.strValue[0] = data;
		return (*this);
	}

	Datum& Datum::operator=(const glm::mat4& data)
	{
		InitializeScalar(DatumType::Matrix);
		mData.matValue[0] = data;
		return (*this);
	}

	Datum& Datum::operator=(const glm::vec4& data)
	{
		InitializeScalar(DatumType::Vector);
		mData.vecValue[0] = data;
		return (*this);
	}

	Datum& Datum::operator=(RTTI* data)
	{
		InitializeScalar(DatumType::RTTI);
		mData.rttiPtrValue[0] = data;
		return (*this);
	}

	void Datum::Set(const std::int32_t data, const std::uint32_t index)
	{
		ValidateType(DatumType::Integer);
		ValidateIndex(index);
		mData.intValue[index] = data;
	}

	void Datum::Set(const float data, const std::uint32_t index)
	{
		ValidateType(DatumType::Float);
		ValidateIndex(index);
		mData.floatValue[index] = data;
	}

	void Datum::Set(const std::string& data, const std::uint32_t index)
	{
		ValidateType(DatumType::String);
		ValidateIndex(index);
		mData.strValue[index] = data;
	}

	void Datum::Set(const glm::mat4& data, const std::uint32_t index)
	{
		ValidateType(DatumType::Matrix);
		ValidateIndex(index);
		mData.matValue[index] = data;
	}

	void Datum::Set(const glm::vec4& data, const std::uint32_t index)
	{
		ValidateType(DatumType::Vector);
		ValidateIndex(index);
		mData.vecValue[index] = data;
	}

	void Datum::Set(RTTI* data, const std::uint32_t index)
	{
		ValidateType(DatumType::RTTI);
		ValidateIndex(index);
		mData.rttiPtrValue[index] = data;
	}

	void Datum::PushBack(const std::int32_t data)
	{
		RaiseExceptionOnExternal();
		SetType(DatumType::Integer);
		Resize(mSize + 1);
		mData.intValue[mSize-1] = data;
	}

	void Datum::PushBack(const float data)
	{
		RaiseExceptionOnExternal();
		SetType(DatumType::Float);
		Resize(mSize + 1);
		mData.floatValue[mSize - 1] = data;
	}

	void Datum::PushBack(const std::string& data)
	{
		RaiseExceptionOnExternal();
		SetType(DatumType::String);
		Resize(mSize + 1);
		mData.strValue[mSize - 1] = data;
	}

	void Datum::PushBack(const glm::mat4& data)
	{
		RaiseExceptionOnExternal();
		SetType(DatumType::Matrix);
		Resize(mSize + 1);
		mData.matValue[mSize - 1] = data;
	}

	void Datum::PushBack(const glm::vec4& data)
	{
		RaiseExceptionOnExternal();
		SetType(DatumType::Vector);
		Resize(mSize + 1);
		mData.vecValue[mSize - 1] = data;
	}

	void Datum::PushBack(RTTI* data)
	{
		RaiseExceptionOnExternal();
		SetType(DatumType::RTTI);
		Resize(mSize + 1);
		mData.rttiPtrValue[mSize - 1] = data;
	}

	bool Datum::PopBack()
	{
		RaiseExceptionOnExternal();
		if (mSize > 0)
		{
			mDestructors[static_cast<std::uint32_t>(mType)](mData, mSize-1);
			--mSize;
			return true;
		}
		return false;
	}

	bool Datum::operator==(const Datum& data) const
	{
		if (mType != data.mType || mSize != data.mSize)
		{
			return false;
		}
		for(std::uint32_t index = 0; index < mSize; ++index)
		{
			if (!mComparators[static_cast<std::uint32_t>(mType)](mData, data.mData, index))
			{
				return false;
			}
		}
		return true;
	}

	bool Datum::operator==(const std::int32_t data) const
	{
		if (mType != DatumType::Integer || mSize != 1)
		{
			return false;
		}
		return (*mData.intValue == data);
	}

	bool Datum::operator==(const float data) const
	{
		if (mType != DatumType::Float || mSize != 1)
		{
			return false;
		}
		return (*mData.floatValue == data);
	}

	bool Datum::operator==(const std::string& data) const
	{
		if (mType != DatumType::String || mSize != 1)
		{
			return false;
		}
		return (*mData.strValue == data);
	}

	bool Datum::operator==(const glm::mat4& data) const
	{
		if (mType != DatumType::Matrix || mSize != 1)
		{
			return false;
		}
		return (*mData.matValue == data);
	}

	bool Datum::operator==(const glm::vec4& data) const
	{
		if (mType != DatumType::Vector || mSize != 1)
		{
			return false;
		}
		return (*mData.vecValue == data);
	}

	bool Datum::operator==(const RTTI* data) const
	{
		if (mType != DatumType::RTTI || mSize != 1)
		{
			return false;
		}
		return (*mData.rttiPtrValue == data);
	}

	bool Datum::operator!=(const Datum& data) const
	{
		return !(*this == data);
	}

	bool Datum::operator!=(const std::int32_t data) const
	{
		return !(*this == data);
	}

	bool Datum::operator!=(const float data) const
	{
		return !(*this == data);
	}

	bool Datum::operator!=(const std::string& data) const
	{
		return !(*this == data);
	}

	bool Datum::operator!=(const glm::mat4& data) const
	{
		return !(*this == data);
	}

	bool Datum::operator!=(const glm::vec4& data) const
	{
		return !(*this == data);
	}

	bool Datum::operator!=(const RTTI* data) const
	{
		return !(*this == data);
	}

	void Datum::SetStorage(std::int32_t* data, std::uint32_t size)
	{
		SetExternalStorage(data, size, DatumType::Integer);
	}

	void Datum::SetStorage(float* data, std::uint32_t size)
	{
		SetExternalStorage(data, size, DatumType::Float);
	}

	void Datum::SetStorage(std::string* data, std::uint32_t size)
	{
		SetExternalStorage(data, size, DatumType::String);
	}

	void Datum::SetStorage(glm::mat4* data, std::uint32_t size)
	{
		SetExternalStorage(data, size, DatumType::Matrix);
	}

	void Datum::SetStorage(glm::vec4* data, std::uint32_t size)
	{
		SetExternalStorage(data, size, DatumType::Vector);
	}

	void Datum::SetStorage(RTTI** data, std::uint32_t size)
	{
		SetExternalStorage(data, size, DatumType::RTTI);
	}

	void Datum::SetFromString(const std::string& stringData, std::uint32_t index)
	{
		ValidateIndex(index);
		mDeserializers[static_cast<std::uint32_t>(mType)](stringData, mData, index);
	}

	std::string Datum::ToString(std::uint32_t index) const
	{
		ValidateIndex(index);
		return mSerializers[static_cast<std::uint32_t>(mType)](mData, index);
	}

	void Datum::Resize(std::uint32_t newSize)
	{
		RaiseExceptionOnExternal();
		if (newSize == 0)
		{
			Clear();
		}
		else if (mSize != newSize)
		{
			for (std::uint32_t index = newSize; index < mSize; index++)
			{
				mDestructors[static_cast<std::uint32_t>(mType)](mData, index);
			}
			mData.voidPtr = realloc(mData.voidPtr, mTypeSizes[static_cast<std::uint32_t>(mType)] * newSize);
			for (std::uint32_t index = mSize; index < newSize; index++)
			{
				mDefaultConstructors[static_cast<std::uint32_t>(mType)](mData, index);
			}
		}
		mSize = newSize;
	}

	std::uint32_t Datum::Size() const
	{
		return mSize;
	}

	void Datum::Clear()
	{
		if (!mIsExternal)
		{
			for (std::uint32_t index = 0; index < mSize; ++index)
			{
				mDestructors[static_cast<std::uint32_t>(mType)](mData, index);
			}
			free(mData.voidPtr);
		}
		mSize = 0;
		mIsExternal = false;
		mData.voidPtr = nullptr;
	}

	Datum::~Datum()
	{
		Clear();
	}

	void Datum::ValidateType(DatumType type) const
	{
		if (!(mType == DatumType::Unknown || mType == type))
		{
			throw std::invalid_argument("Cannot modify the type of a Datum with an already set type");
		}
	}

	void Datum::ValidateIndex(std::uint32_t index) const
	{
		if (index >= mSize)
		{
			throw std::out_of_range("The given index is out of bounds");
		}
	}

	void Datum::RaiseExceptionOnExternal() const
	{
		if (mIsExternal)
		{
			throw std::runtime_error("Operation not permitted for external types");
		}
	}

	void Datum::InitializeScalar(DatumType type)
	{
		SetType(type);
		if (!mIsExternal)
		{
			Resize(1);
		}
	}

	void Datum::Copy(const Datum& datum)
	{
		Clear();
		mType = datum.mType;
		if (datum.mIsExternal)
		{
			mData = datum.mData;
		}
		else
		{
			Resize(datum.mSize);
			for (std::uint32_t index = 0; index < datum.mSize; ++index)
			{
				mCloners[static_cast<std::uint32_t>(mType)](mData, datum.mData, index);
			}
		}
		mSize = datum.mSize;
		mIsExternal = datum.mIsExternal;
	}

	void Datum::SetExternalStorage(void* externalData, std::uint32_t size, DatumType type)
	{
		if (mType != type)
		{
			throw std::invalid_argument("Cannot modify the type of a Datum with an already set type");
		}
		Clear();
		mData.voidPtr = externalData;
		mSize = size;
		mIsExternal = true;
		mType = type;
	}
}
