#include "Attributed.h"
#include "Datum.h"

namespace AnonymousEngine
{
	RTTI_DEFINITIONS(Attributed)

	const std::uint32_t Attributed::sAuxiliaryBegin = InitializePrescribedAttributeNames();
	HashMap<std::uint64_t, Vector<std::string>> Attributed::sPrescribedAttributes = HashMap<std::uint64_t, Vector<std::string>>();

	Attributed::Attributed() : mPrescribedAttributesAdded(0U)
	{
		AddInternalAttribute("This", static_cast<RTTI*>(this), 1U);
	}

	Attributed::~Attributed()
	{
	}

	Attributed::Attributed(const Attributed&& rhs) noexcept
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
		AppendInternalAttribute(name, value, Datum::DatumType::Integer, size);
	}

	void Attributed::AddInternalAttribute(const std::string& name, const float value, const std::uint32_t size)
	{
		AppendInternalAttribute(name, value, Datum::DatumType::Float, size);
	}

	void Attributed::AddInternalAttribute(const std::string& name, const std::string& value, const std::uint32_t size)
	{
		AppendInternalAttribute(name, value, Datum::DatumType::String, size);
	}

	void Attributed::AddInternalAttribute(const std::string& name, const glm::vec4& value, const std::uint32_t size)
	{
		AppendInternalAttribute(name, value, Datum::DatumType::Vector, size);
	}

	void Attributed::AddInternalAttribute(const std::string& name, const glm::mat4& value, const std::uint32_t size)
	{
		AppendInternalAttribute(name, value, Datum::DatumType::Matrix, size);
	}

	void Attributed::AddInternalAttribute(const std::string& name, RTTI* const value, const std::uint32_t size)
	{
		AppendInternalAttribute(name, value, Datum::DatumType::RTTI, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, std::int32_t& address, const std::uint32_t size)
	{
		ValidateAttribute(name);
		Append(name).SetStorage(&address, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, float& address, const std::uint32_t size)
	{
		ValidateAttribute(name);
		Append(name).SetStorage(&address, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, std::string& address, const std::uint32_t size)
	{
		ValidateAttribute(name);
		Append(name).SetStorage(&address, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, glm::vec4& address, const std::uint32_t size)
	{
		ValidateAttribute(name);
		Append(name).SetStorage(&address, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, glm::mat4& address, const std::uint32_t size)
	{
		ValidateAttribute(name);
		Append(name).SetStorage(&address, size);
	}

	void Attributed::AddExternalAttribute(const std::string& name, RTTI*& address, const std::uint32_t size)
	{
		ValidateAttribute(name);
		Append(name).SetStorage(&address, size);
	}

	template <typename T>
	void Attributed::AppendInternalAttribute(const std::string&name, T& value, const Datum::DatumType type, const std::uint32_t size)
	{
		ValidateAttribute(name);
		Datum& datum = Append(name);
		datum.SetType(type);
		datum.Resize(size);
		for (std::uint32_t index = 0; index < size; ++index)
		{
			datum.Set(value, index);
		}
	}

	void Attributed::ValidateAttribute(const std::string& name)
	{
		// Check if all prescribed attributes are added. 
		auto& prescribedAttributes = sPrescribedAttributes[TypeIdInstance()];
		if (mPrescribedAttributesAdded < prescribedAttributes.Size())
		{
			// Since all prescribed attributes are not added, verify that the new attribute being added
			// is in the prescribed attribute names list.
			if (prescribedAttributes.Find(name) == prescribedAttributes.end())
			{
				throw std::invalid_argument("The attribute being added is not a valid prescribed attribute");
			}
			// new attribute being added is a valid prescribed attribute increment the mPrescribedAttributesAdded count
			++mPrescribedAttributesAdded;
		}
	}

	void Attributed::ValidateAllPrescribedAttributesAreAdded() const
	{
		if (mPrescribedAttributesAdded < sPrescribedAttributes[TypeIdInstance()].Size())
		{
			throw std::runtime_error("All the prescribed attributes are not added.");
		}
	}

	void Attributed::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
	{
		prescribedAttributeNames.PushBack("This");
	}

	std::uint32_t Attributed::InitializePrescribedAttributeNames()
	{
		Vector<std::string>& prescribedAttributeNames = sPrescribedAttributes[TypeIdClass()];
		prescribedAttributeNames.Reserve(1U);
		AppendPrescribedAttributeNames(prescribedAttributeNames);
		return prescribedAttributeNames.Size();
	}
}
