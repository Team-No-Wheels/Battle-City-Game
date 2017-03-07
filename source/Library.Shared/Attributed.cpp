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

	Attributed::Attributed(const Attributed& rhs) :
		Scope(rhs)
	{
		Copy(rhs);
	}

	Attributed& Attributed::operator=(const Attributed& rhs)
	{
		if (this != &rhs)
		{
			Scope::operator=(rhs);
			Copy(rhs);
		}
		return *this;
	}

	Attributed::Attributed(Attributed&& rhs) noexcept :
		Scope(std::move(rhs))
	{
		Move(rhs);
	}

	Attributed& Attributed::operator=(Attributed&& rhs)
	{
		if (this != &rhs)
		{
			Scope::operator=(std::move(rhs));
			Move(rhs);
		}
		return *this;
	}

	Datum& Attributed::AddAuxiliaryAttribute(const std::string& name)
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

	Datum& Attributed::AddInternalAttribute(const std::string& name, const std::int32_t value, const std::uint32_t size)
	{
		return AppendInternalAttribute<std::int32_t>(name, value, Datum::DatumType::Integer, size);
	}

	Datum& Attributed::AddInternalAttribute(const std::string& name, const float value, const std::uint32_t size)
	{
		return AppendInternalAttribute<float>(name, value, Datum::DatumType::Float, size);
	}

	Datum& Attributed::AddInternalAttribute(const std::string& name, const std::string& value, const std::uint32_t size)
	{
		return AppendInternalAttribute<std::string>(name, value, Datum::DatumType::String, size);
	}

	Datum& Attributed::AddInternalAttribute(const std::string& name, const glm::vec4& value, const std::uint32_t size)
	{
		return AppendInternalAttribute<glm::vec4>(name, value, Datum::DatumType::Vector, size);
	}

	Datum& Attributed::AddInternalAttribute(const std::string& name, const glm::mat4& value, const std::uint32_t size)
	{
		return AppendInternalAttribute<glm::mat4>(name, value, Datum::DatumType::Matrix, size);
	}

	Datum& Attributed::AddInternalAttribute(const std::string& name, RTTI* const value, const std::uint32_t size)
	{
		return AppendInternalAttribute<RTTI*>(name, value, Datum::DatumType::RTTI, size);
	}

	Datum& Attributed::AddExternalAttribute(const std::string& name, std::int32_t* address, const std::uint32_t size)
	{
		return AppendExternalAttribute<std::int32_t>(name, address, size);
	}

	Datum& Attributed::AddExternalAttribute(const std::string& name, float* address, const std::uint32_t size)
	{
		return AppendExternalAttribute<float>(name, address, size);
	}

	Datum& Attributed::AddExternalAttribute(const std::string& name, std::string* address, const std::uint32_t size)
	{
		return AppendExternalAttribute<std::string>(name, address, size);
	}

	Datum& Attributed::AddExternalAttribute(const std::string& name, glm::vec4* address, const std::uint32_t size)
	{
		return AppendExternalAttribute<glm::vec4>(name, address, size);
	}

	Datum& Attributed::AddExternalAttribute(const std::string& name, glm::mat4* address, const std::uint32_t size)
	{
		return AppendExternalAttribute<glm::mat4>(name, address, size);
	}

	Datum& Attributed::AddExternalAttribute(const std::string& name, RTTI** address, const std::uint32_t size)
	{
		return AppendExternalAttribute<RTTI*>(name, address, size);
	}

	void Attributed::AddNestedScope(const std::string& name, Scope& scope)
	{
		ValidateAttribute(name);
		Adopt(scope, name);
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

	void Attributed::Copy(const Attributed& rhs)
	{
		mPrescribedAttributesAdded = rhs.mPrescribedAttributesAdded;
		operator[]("This") = this;
	}

	void Attributed::Move(Attributed& rhs)
	{
		mPrescribedAttributesAdded = rhs.mPrescribedAttributesAdded;
		operator[]("This") = this;
	}

	template <typename T>
	Datum& Attributed::AppendInternalAttribute(const std::string&name, const T& value, const Datum::DatumType type, const std::uint32_t size)
	{
		ValidateAttribute(name);
		Datum& datum = Append(name);
		datum.SetType(type);
		datum.Resize(size);
		for (std::uint32_t index = 0; index < size; ++index)
		{
			datum.Set(value, index);
		}
		return datum;
	}

	template <typename T>
	Datum& Attributed::AppendExternalAttribute(const std::string&name, T* address, const std::uint32_t size)
	{
		ValidateAttribute(name);
		Datum& datum = Append(name);
		datum.SetStorage(address, size);
		return datum;
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

	std::uint32_t Attributed::InitializePrescribedAttributeNames()
	{
		Vector<std::string>& prescribedAttributeNames = sPrescribedAttributes[TypeIdClass()];
		prescribedAttributeNames.Reserve(1U);
		AppendPrescribedAttributeNames(prescribedAttributeNames);
		return prescribedAttributeNames.Size();
	}
}
