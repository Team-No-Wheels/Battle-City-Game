#include "Attributed.h"
#include "Datum.h"

namespace AnonymousEngine
{
	RTTI_DEFINITIONS(Attributed)

	const std::uint32_t Attributed::sAuxiliaryBegin = InitializeAttributes();

	Attributed::~Attributed()
	{
	}

	Attributed::Attributed(const Attributed&& rhs)
	{
		rhs;
	}

	Attributed& Attributed::operator=(const Attributed&& rhs)
	{
		rhs;
		return *this;
	}

	Datum& Attributed::AppendAuxiliaryAttribute(const std::string& name)
	{
		return Append(name);
	}

	std::uint32_t Attributed::AuxiliaryBegin()
	{
		return sAuxiliaryBegin;
	}

	bool Attributed::IsPrescribedAttribute(const std::string& name) const
	{
		auto prescribedAttributes = sPrescribedAttributes[TypeIdInstance()];
		return prescribedAttributes.Find(name) != prescribedAttributes.end();
	}

	bool Attributed::IsAuxiliaryAttribute(const std::string& name) const
	{
		return (!IsPrescribedAttribute(name) && IsAttribute(name));
	}

	bool Attributed::IsAttribute(const std::string& name) const
	{
		return (Find(name) != nullptr);
	}

	void Attributed::AddInternalAttribute(const std::string& name, const std::int32_t value, const std::uint32_t size)
	{
		Datum& datum = Append(name);
		datum.Resize(size);
		datum.SetType(Datum::DatumType::Integer);
		for (std::uint32_t index = 0; index < size; ++index)
		{
			datum.Set(value, index);
		}
	}

	void Attributed::AddInternalAttribute(const std::string& name, const float value, const std::uint32_t size)
	{
		Datum& datum = Append(name);
		datum.Resize(size);
		datum.SetType(Datum::DatumType::Float);
		for (std::uint32_t index = 0; index < size; ++index)
		{
			datum.Set(value, index);
		}
	}

	void Attributed::AddInternalAttribute(const std::string& name, const std::string& value, const std::uint32_t size)
	{
		Datum& datum = Append(name);
		datum.Resize(size);
		datum.SetType(Datum::DatumType::String);
		for (std::uint32_t index = 0; index < size; ++index)
		{
			datum.Set(value, index);
		}
	}

	void Attributed::AddInternalAttribute(const std::string& name, const glm::vec4& value, const std::uint32_t size)
	{
		Datum& datum = Append(name);
		datum.Resize(size);
		datum.SetType(Datum::DatumType::Vector);
		for (std::uint32_t index = 0; index < size; ++index)
		{
			datum.Set(value, index);
		}
	}

	void Attributed::AddInternalAttribute(const std::string& name, const glm::mat4& value, const std::uint32_t size)
	{
		Datum& datum = Append(name);
		datum.Resize(size);
		datum.SetType(Datum::DatumType::Matrix);
		for (std::uint32_t index = 0; index < size; ++index)
		{
			datum.Set(value, index);
		}
	}

	void Attributed::AddInternalAttribute(const std::string& name, RTTI* const value, const std::uint32_t size)
	{
		Datum& datum = Append(name);
		datum.Resize(size);
		datum.SetType(Datum::DatumType::RTTI);
		for (std::uint32_t index = 0; index < size; ++index)
		{
			datum.Set(value, index);
		}
	}

	void Attributed::AddExternalAttribute(const std::string& name, std::int32_t& address, const std::uint32_t size)
	{
		Append(name).SetStorage(&address, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, float& address, const std::uint32_t size)
	{
		Append(name).SetStorage(&address, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, std::string& address, const std::uint32_t size)
	{
		Append(name).SetStorage(&address, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, glm::vec4& address, const std::uint32_t size)
	{
		Append(name).SetStorage(&address, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, glm::mat4& address, const std::uint32_t size)
	{
		Append(name).SetStorage(&address, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, RTTI*& address, const std::uint32_t size)
	{
		Append(name).SetStorage(&address, size);
	}

	std::uint32_t Attributed::InitializeAttributes()
	{
		return sPrescribedAttributes[TypeIdClass()].Size();
	}
}
