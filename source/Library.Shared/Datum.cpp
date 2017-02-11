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
		mType(type), mSize(0), mCapacity(0)
	{
		mData.voidPtr = nullptr;
		Reserve(3);
	}

	Datum::Datum(const Datum& datum)
	{
		datum;
	}

	void Datum::SetType(DatumType type)
	{
		if (mType != DatumType::Unknown || mType != type)
		{
			throw std::invalid_argument("Cannot modify the type of a Datum with an already set type");
		}
		mType = type;
	}

	Datum::DatumType Datum::Type() const
	{
		return mType;
	}

	Datum& Datum::operator=(const Datum& datum)
	{
		datum;
		return (*this);
	}

	Datum& Datum::operator=(const std::int32_t data)
	{
		data;
		return (*this);
	}

	Datum& Datum::operator=(const float data)
	{
		data;
		return (*this);
	}

	Datum& Datum::operator=(const std::string& data)
	{
		data;
		return (*this);
	}

	Datum& Datum::operator=(const glm::mat4x4& data)
	{
		data;
		return (*this);
	}

	Datum& Datum::operator=(const glm::vec4& data)
	{
		data;
		return (*this);
	}

	Datum& Datum::operator=(const RTTI* data)
	{
		data;
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
		data;
		index;
	}

	void Datum::Set(const float data, const std::uint32_t index)
	{
		data;
		index;
	}

	void Datum::Set(const std::string& data, const std::uint32_t index)
	{
		data;
		index;
	}

	void Datum::Set(const glm::mat4x4& data, const std::uint32_t index)
	{
		data;
		index;
	}

	void Datum::Set(const glm::vec4& data, const std::uint32_t index)
	{
		data;
		index;
	}

	void Datum::Set(const RTTI* data, const std::uint32_t index)
	{
		data;
		index;
	}

	void Datum::PushBack(const std::int32_t data)
	{
		data;
	}

	void Datum::PushBack(const float data)
	{
		data;
	}

	void Datum::PushBack(const std::string& data)
	{
		data;
	}

	void Datum::PushBack(const glm::mat4x4& data)
	{
		data;
	}

	void Datum::PushBack(const glm::vec4& data)
	{
		data;
	}

	void Datum::PushBack(const RTTI* data)
	{
		data;
	}

	bool Datum::PopBack()
	{
		return true;
	}

	bool Datum::operator==(const std::int32_t data) const
	{
		data;
		return true;
	}

	bool Datum::operator==(const float data) const
	{
		data;
		return true;
	}

	bool Datum::operator==(const std::string& data) const
	{
		data;
		return true;
	}

	bool Datum::operator==(const glm::mat4x4& data) const
	{
		data;
		return true;
	}

	bool Datum::operator==(const glm::vec4& data) const
	{
		data;
		return true;
	}

	bool Datum::operator==(const RTTI* data) const
	{
		data;
		return true;
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
		data;
		size;
	}

	void Datum::SetStorage(float* data, std::uint32_t size)
	{
		data;
		size;
	}

	void Datum::SetStorage(std::string* data, std::uint32_t size)
	{
		data;
		size;
	}

	void Datum::SetStorage(RTTI** data, std::uint32_t size)
	{
		data;
		size;
	}

	void Datum::SetStorage(glm::mat4x4* data, std::uint32_t size)
	{
		data;
		size;
	}

	void Datum::SetStorage(glm::vec4* data, std::uint32_t size)
	{
		data;
		size;
	}

	void Datum::SetFromString(const std::string& stringData, std::uint32_t index)
	{
		stringData;
		index;
	}

	std::string Datum::ToString() const
	{
		return "";
	}

	void Datum::Resize(std::uint32_t newSize)
	{
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
	{}

	Datum::~Datum()
	{
		Clear();
	}

	void Datum::Copy(const Datum& rhs)
	{
		rhs;
	}
}
