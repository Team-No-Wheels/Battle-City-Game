#include "Attributed.h"
#include "Datum.h"

namespace AnonymousEngine
{
	RTTI_DEFINITIONS(Attributed)

	const std::uint32_t Attributed::sPrescribedAttributeCount = InitializePrescribedAttributeNames();

	Attributed::Attributed() :
		mPrescribedAttributesAdded(0U)
	{
		AddInternalAttribute("this", static_cast<RTTI*>(this), 1U);
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

	Attributed& Attributed::operator=(Attributed&& rhs) noexcept
	{
		if (this != &rhs)
		{
			Scope::operator=(std::move(rhs));
			Move(rhs);
		}
		return *this;
	}

	bool Attributed::operator==(const Attributed& rhs) const
	{
		if (rhs.mOrderVector.Size() != mOrderVector.Size())
		{
			return false;
		}
		std::uint32_t index = 0;
		for(const auto& pair : mOrderVector)
		{
			if (pair->first == "this")
			{
				++index;
				continue;
			}
			if (pair->second != rhs.mOrderVector[index]->second)
			{
				return false;
			}
			++index;
		}
		return true;
	}

	bool Attributed::operator!=(const Attributed& rhs) const
	{
		return !(*this == rhs);
	}

	Datum& Attributed::AddAuxiliaryAttribute(const std::string& name)
	{
		return Append(name);
	}

	bool Attributed::IsPrescribedAttribute(const std::string& name) const
	{
		auto prescribedAttributes = PrescribedAttributesNamesCache(TypeIdInstance());
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

	const Vector<std::string>& Attributed::PrescribedAttributes() const
	{
		return PrescribedAttributesNamesCache(TypeIdInstance());
	}

	void Attributed::AuxiliaryAttributes(Vector<std::string>& auxiliaryAttributes) const
	{
		auxiliaryAttributes.Clear();
		const auto& prescribedAttributes = PrescribedAttributesNamesCache(TypeIdInstance());
		for (const auto& pair : mOrderVector)
		{
			if (prescribedAttributes.Find(pair->first) == prescribedAttributes.end())
			{
				auxiliaryAttributes.PushBack(pair->first);
			}
		}
	}

	void Attributed::Attributes(Vector<std::string>& attributes) const
	{
		attributes.Clear();
		attributes.Reserve(mOrderVector.Size());
		for (const auto& pair : mOrderVector)
		{
			attributes.PushBack(pair->first);
		}
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

	void Attributed::AddDatumAttribute(const std::string& name, Datum*& datum)
	{
		ValidateAttribute(name);
		datum = &Append(name);
	}

	void Attributed::ValidateAllPrescribedAttributesAreAdded() const
	{
		if (mPrescribedAttributesAdded < PrescribedAttributesNamesCache(TypeIdInstance()).Size())
		{
			throw std::runtime_error("All the prescribed attributes are not added.");
		}
	}

	Vector<std::string>& Attributed::PrescribedAttributesNamesCache(std::uint64_t typeId)
	{
		static HashMap<std::uint64_t, Vector<std::string>> sPrescribedAttributes;
		return sPrescribedAttributes[typeId];
	}

	void Attributed::AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames)
	{
		prescribedAttributeNames.PushBack("this");
	}

	void Attributed::Copy(const Attributed& rhs)
	{
		mPrescribedAttributesAdded = rhs.mPrescribedAttributesAdded;
		(*this)["this"] = this;
	}

	void Attributed::Move(Attributed& rhs)
	{
		mPrescribedAttributesAdded = rhs.mPrescribedAttributesAdded;
		(*this)["this"] = this;
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
		auto& prescribedAttributes = PrescribedAttributesNamesCache(TypeIdInstance());
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
		Vector<std::string>& prescribedAttributeNames = PrescribedAttributesNamesCache(TypeIdClass());
		prescribedAttributeNames.Reserve(1U);
		AppendPrescribedAttributeNames(prescribedAttributeNames);
		return prescribedAttributeNames.Size();
	}
}
