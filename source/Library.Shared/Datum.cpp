#include "Datum.h"

namespace AnonymousEngine
{
	const std::uint32_t Datum::mTypeSize[7] = {
		0,
		sizeof(std::int32_t),
		sizeof(float),
		sizeof(glm::mat4x4),
		sizeof(glm::vec4),
		sizeof(std::string),
		sizeof(RTTI*)
	};

	Datum::Datum(DatumType type) :
		mType(type), mSize(0), mCapacity(0), mIsExternal(false)
	{
		mData.voidPtr = nullptr;
		Reserve(3);
	}

	Datum::Datum(const Datum& datum)
	{
		Copy(datum);
	}

	void Datum::SetType(DatumType type)
	{
		IsTypeAssignable(type);
		mType = type;
	}

	Datum::DatumType Datum::Type() const
	{
		return mType;
	}

	Datum& Datum::operator=(const Datum& datum)
	{
		Copy(datum);
		return (*this);
	}

	Datum& Datum::operator=(const std::int32_t data)
	{
		IsTypeAssignable(DatumType::Integer);
		*mData.intValue = data;
		return (*this);
	}

	Datum& Datum::operator=(const float data)
	{
		IsTypeAssignable(DatumType::Float);
		*mData.floatValue = data;
		return (*this);
	}

	Datum& Datum::operator=(const std::string& data)
	{
		IsTypeAssignable(DatumType::String);
		*mData.strValue = data;
		return (*this);
	}

	Datum& Datum::operator=(const glm::mat4x4& data)
	{
		IsTypeAssignable(DatumType::Matrix);
		*mData.matValue = data;
		return (*this);
	}

	Datum& Datum::operator=(const glm::vec4& data)
	{
		IsTypeAssignable(DatumType::Vector);
		*mData.vecValue = data;
		return (*this);
	}

	Datum& Datum::operator=(RTTI* data)
	{
		IsTypeAssignable(DatumType::RTTI);
		*mData.rttiPtrValue = data;
		return (*this);
	}

	template <>
	std::int32_t Datum::Get(const std::uint32_t index)
	{
		if (index < 0 && index >= mSize)
		{
			throw std::out_of_range("index out of range");
		}
		return mData.intValue[index];
	}

	template <>
	float Datum::Get(const std::uint32_t index)
	{
		if (index < 0 && index >= mSize)
		{
			throw std::out_of_range("index out of range");
		}
		return mData.floatValue[index];
	}

	template <>
	std::string& Datum::Get(const std::uint32_t index)
	{
		if (index < 0 && index >= mSize)
		{
			throw std::out_of_range("index out of range");
		}
		return mData.strValue[index];
	}

	template <>
	glm::mat4x4& Datum::Get(const std::uint32_t index)
	{
		if (index < 0 && index >= mSize)
		{
			throw std::out_of_range("index out of range");
		}
		return mData.matValue[index];
	}

	template <>
	glm::vec4& Datum::Get(const std::uint32_t index)
	{
		if (index < 0 && index >= mSize)
		{
			throw std::out_of_range("index out of range");
		}
		return mData.vecValue[index];
	}

	template <>
	RTTI*& Datum::Get(const std::uint32_t index)
	{
		if (index < 0 && index >= mSize)
		{
			throw std::out_of_range("index out of range");
		}
		return mData.rttiPtrValue[index];
	}

	void Datum::Set(const std::int32_t data, const std::uint32_t index)
	{
		IsTypeAssignable(DatumType::Integer);
		IndexBoundsCheck(index);
		mData.intValue[index] = data;
	}

	void Datum::Set(const float data, const std::uint32_t index)
	{
		IsTypeAssignable(DatumType::Float);
		IndexBoundsCheck(index);
		mData.floatValue[index] = data;
	}

	void Datum::Set(const std::string& data, const std::uint32_t index)
	{
		IsTypeAssignable(DatumType::String);
		IndexBoundsCheck(index);
		mData.strValue[index] = data;
	}

	void Datum::Set(const glm::mat4x4& data, const std::uint32_t index)
	{
		IsTypeAssignable(DatumType::Matrix);
		IndexBoundsCheck(index);
		mData.matValue[index] = data;
	}

	void Datum::Set(const glm::vec4& data, const std::uint32_t index)
	{
		IsTypeAssignable(DatumType::Vector);
		IndexBoundsCheck(index);
		mData.vecValue[index] = data;
	}

	void Datum::Set(RTTI* data, const std::uint32_t index)
	{
		IsTypeAssignable(DatumType::RTTI);
		IndexBoundsCheck(index);
		mData.rttiPtrValue[index] = data;
	}

	void Datum::PushBack(const std::int32_t data)
	{
		IsTypeAssignable(DatumType::Integer);
		ExpandIfFull();
		mData.intValue[mSize++] = data;
	}

	void Datum::PushBack(const float data)
	{
		IsTypeAssignable(DatumType::Float);
		ExpandIfFull();
		mData.floatValue[mSize++] = data;
	}

	void Datum::PushBack(const std::string& data)
	{
		IsTypeAssignable(DatumType::String);
		ExpandIfFull();
		mData.strValue[mSize++] = data;
	}

	void Datum::PushBack(const glm::mat4x4& data)
	{
		IsTypeAssignable(DatumType::Matrix);
		ExpandIfFull();
		mData.matValue[mSize++] = data;
	}

	void Datum::PushBack(const glm::vec4& data)
	{
		IsTypeAssignable(DatumType::Vector);
		ExpandIfFull();
		mData.vecValue[mSize++] = data;
	}

	void Datum::PushBack(RTTI* data)
	{
		IsTypeAssignable(DatumType::RTTI);
		ExpandIfFull();
		mData.rttiPtrValue[mSize++] = data;
	}

	bool Datum::PopBack()
	{
		if (mSize > 0)
		{
			// TODO: Avoid Switch
			// TODO: call destructor for the data
			--mSize;
			return true;
		}
		return false;
	}

	bool Datum::operator==(const std::int32_t data) const
	{
		if (mType != DatumType::Integer || mSize == 0)
		{
			return false;
		}
		return (*mData.intValue == data);
	}

	bool Datum::operator==(const float data) const
	{
		if (mType != DatumType::Float)
		{
			return false;
		}
		return (*mData.floatValue == data);
	}

	bool Datum::operator==(const std::string& data) const
	{
		if (mType != DatumType::String)
		{
			return false;
		}
		return (*mData.strValue == data);
	}

	bool Datum::operator==(const glm::mat4x4& data) const
	{
		if (mType != DatumType::Matrix)
		{
			return false;
		}
		return (*mData.matValue == data);
	}

	bool Datum::operator==(const glm::vec4& data) const
	{
		if (mType != DatumType::Vector)
		{
			return false;
		}
		return (*mData.vecValue == data);
	}

	bool Datum::operator==(const RTTI* data) const
	{
		if (mType != DatumType::RTTI)
		{
			return false;
		}
		return (*mData.rttiPtrValue == data);
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

	bool Datum::operator!=(const glm::mat4x4& data) const
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

	void Datum::SetStorage(glm::mat4x4* data, std::uint32_t size)
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
		// TODO: Avoid Switch
		// TODO: implement SetFromString
		stringData;
		index;
	}

	std::string Datum::ToString() const
	{
		// TODO: Avoid Switch
		// TODO: implement ToString
		return "";
	}

	void Datum::Resize(std::uint32_t newSize)
	{
		// TODO: Avoid Switch
		// TODO: implement resize
		newSize;
	}

	std::uint32_t Datum::Size() const
	{
		return mSize;
	}

	void Datum::Reserve(std::uint32_t capacity)
	{
		if (capacity > mCapacity)
		{
			mData.voidPtr = (realloc(mData.voidPtr, mTypeSize[static_cast<std::uint32_t>(mType)] * capacity));
			mCapacity = capacity;
		}
	}

	void Datum::Clear()
	{
		if (!mIsExternal)
		{
			// TODO: Avoid Switch
			// TODO: call destructors based on type
			free(mData.voidPtr);
		}
		mSize = 0;
		mCapacity = 0;
		mType = DatumType::Unknown;
		mIsExternal = false;
	}

	Datum::~Datum()
	{
		Clear();
	}

	void Datum::IsTypeAssignable(DatumType type) const
	{
		if (mType != DatumType::Unknown || mType != type)
		{
			throw std::invalid_argument("Cannot modify the type of a Datum with an already set type");
		}
	}

	void Datum::IndexBoundsCheck(std::uint32_t index) const
	{
		if (index > mSize)
		{
			throw std::out_of_range("The given index is out of bounds");
		}
	}

	void Datum::ExpandIfFull()
	{
		if (mSize == mCapacity)
		{
			// TODO: cleanup the increment strategy
			Reserve(mCapacity + 3);
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
			for (std::uint32_t i = 0; i < datum.mSize; i++)
			{
				// TODO: Avoid Switch
				// TODO: deep copy each element based on type
			}
		}
		mSize = datum.mSize;
		mCapacity = datum.mCapacity;
		mIsExternal = datum.mIsExternal;
	}

	void Datum::SetExternalStorage(void* externalData, std::uint32_t size, DatumType type)
	{
		Clear();
		mData.voidPtr = externalData;
		mSize = mCapacity = size;
		mIsExternal = true;
		mType = type;
	}
}
