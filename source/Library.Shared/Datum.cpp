#include "Datum.h"

AnonymousEngine::Datum::Datum(DatumType type)
{
	type;
}

AnonymousEngine::Datum::Datum(const Datum& datum)
{
	datum;
}

void AnonymousEngine::Datum::SetType(DatumType type)
{
	type;
}

AnonymousEngine::Datum::DatumType AnonymousEngine::Datum::Type()
{
	return mType;
}

AnonymousEngine::Datum& AnonymousEngine::Datum::operator=(const Datum& datum)
{
	datum;
	return (*this);
}

AnonymousEngine::Datum& AnonymousEngine::Datum::operator=(const std::int32_t data)
{
	data;
	return (*this);
}

AnonymousEngine::Datum& AnonymousEngine::Datum::operator=(const float data)
{
	data;
	return (*this);
}

AnonymousEngine::Datum& AnonymousEngine::Datum::operator=(const std::string& data)
{
	data;
	return (*this);
}

AnonymousEngine::Datum& AnonymousEngine::Datum::operator=(const RTTI* data)
{
	data;
	return (*this);
}

void AnonymousEngine::Datum::Set(const std::int32_t data, const std::uint32_t index)
{
	data;
	index;
}

void AnonymousEngine::Datum::Set(const float data, const std::uint32_t index)
{
	data;
	index;
}

void AnonymousEngine::Datum::Set(const std::string& data, const std::uint32_t index)
{
	data;
	index;
}

void AnonymousEngine::Datum::Set(const RTTI* data, const std::uint32_t index)
{
	data;
	index;
}

void AnonymousEngine::Datum::PushBack(const std::int32_t data)
{
	data;
}

void AnonymousEngine::Datum::PushBack(const float data)
{
	data;
}

void AnonymousEngine::Datum::PushBack(const std::string& data)
{
	data;
}

void AnonymousEngine::Datum::PushBack(const RTTI* data)
{
	data;
}

bool AnonymousEngine::Datum::PopBack()
{
	return true;
}

bool AnonymousEngine::Datum::operator==(const std::int32_t data)
{
	data;
	return true;
}

bool AnonymousEngine::Datum::operator==(const float data)
{
	data;
	return true;
}

bool AnonymousEngine::Datum::operator==(const std::string& data)
{
	data;
	return true;
}

bool AnonymousEngine::Datum::operator==(const RTTI* data)
{
	data;
	return true;
}

bool AnonymousEngine::Datum::operator!=(const std::int32_t data)
{
	data;
	return true;
}

bool AnonymousEngine::Datum::operator!=(const float data)
{
	data;
	return true;
}

bool AnonymousEngine::Datum::operator!=(const std::string& data)
{
	data;
	return true;
}

bool AnonymousEngine::Datum::operator!=(const RTTI* data)
{
	data;
	return true;
}

void AnonymousEngine::Datum::SetStorage(std::int32_t* data, std::uint32_t size)
{
	data;
	size;
}

void AnonymousEngine::Datum::SetStorage(float* data, std::uint32_t size)
{
	data;
	size;
}

void AnonymousEngine::Datum::SetStorage(std::string* data, std::uint32_t size)
{
	data;
	size;
}

void AnonymousEngine::Datum::SetStorage(RTTI** data, std::uint32_t size)
{
	data;
	size;
}

void AnonymousEngine::Datum::SetFromString(const std::string& stringData, std::uint32_t index)
{
	stringData;
	index;
}

std::string AnonymousEngine::Datum::ToString()
{
	return "";
}

void AnonymousEngine::Datum::Resize(std::uint32_t newSize)
{
	newSize;
}

std::uint32_t AnonymousEngine::Datum::Size() const
{
	return mSize;
}

void AnonymousEngine::Datum::Reserve(std::uint32_t capacity)
{
	capacity;
}

void AnonymousEngine::Datum::Clear()
{
}

AnonymousEngine::Datum::~Datum()
{
}

void AnonymousEngine::Datum::Copy(const Datum& rhs)
{
	rhs;
}

