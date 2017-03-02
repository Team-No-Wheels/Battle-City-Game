#pragma once

#include "Vector.h"
#include "HashMap.h"
#include "RTTI.h"
#include "Scope.h"

namespace AnonymousEngine
{
	class Attributed : public Scope
	{
	public:
		Attributed();
		virtual ~Attributed();

		Attributed(const Attributed& rhs) = default;
		Attributed(const Attributed&& rhs) noexcept;

		Attributed& operator=(const Attributed& rhs) = default;
		Attributed& operator=(const Attributed&& rhs);

		Datum& AppendAuxiliaryAttribute(const std::string& name);
		static std::uint32_t AuxiliaryBegin();

		bool IsPrescribedAttribute(const std::string& name) const;
		bool IsAuxiliaryAttribute(const std::string& name) const;
		bool IsAttribute(const std::string& name) const;
	protected:
		// In the constructor of a derived class add all the prescribed attributes first. "This" is added automatically
		void AddInternalAttribute(const std::string& name, const std::int32_t value, const std::uint32_t size);
		void AddInternalAttribute(const std::string& name, const float value, const std::uint32_t size);
		void AddInternalAttribute(const std::string& name, const std::string& value, const std::uint32_t size);
		void AddInternalAttribute(const std::string& name, const glm::vec4& value, const std::uint32_t size);
		void AddInternalAttribute(const std::string& name, const glm::mat4& value, const std::uint32_t size);
		void AddInternalAttribute(const std::string& name, RTTI* const value, const std::uint32_t size);

		void AddExternalAttribute(const std::string& name, std::int32_t& address, const std::uint32_t size);
		void AddExternalAttribute(const std::string& name, float& address, const std::uint32_t size);
		void AddExternalAttribute(const std::string& name, std::string& address, const std::uint32_t size);
		void AddExternalAttribute(const std::string& name, glm::vec4& address, const std::uint32_t size);
		void AddExternalAttribute(const std::string& name, glm::mat4& address, const std::uint32_t size);
		void AddExternalAttribute(const std::string& name, RTTI*& address, const std::uint32_t size);

		// For child classes call Parent::AppendPrescribedAttributes and pass reference to prescribed attributes
		// list of child class before adding the child class attribute names to the list
		static void AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames);
		// Checks if attribute being added is a valid prescribed attribute.
		// This should be called at the end of all child class constructors
		void ValidateAllPrescribedAttributesAreAdded() const;

		static const std::uint32_t sAuxiliaryBegin;
		static HashMap<std::uint64_t, Vector<std::string>> sPrescribedAttributes;
	private:
		std::uint32_t mPrescribedAttributesAdded;

		// Checks if attribute being added is a valid prescribed attribute
		void ValidateAttribute(const std::string& name);
		// Helper method to add internal attributes of all types
		template <typename T>
		void AppendInternalAttribute(const std::string&name, T& value, const Datum::DatumType type, const std::uint32_t size);
		// Initializes the sAuxiliaryBegin count by appending all prescribed names to the list
		static std::uint32_t InitializePrescribedAttributeNames();

		RTTI_DECLARATIONS(Attributed, Scope)
	};

#define ATTRIBUTED_DECLARATIONS()																							\
		protected:                                                                                                          \
			/* For child classes call Parent::AppendPrescribedAttributes and pass reference to prescribed attributes */     \
			/* list of child class before adding the child class attribute names to the list                         */     \
			static void AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames);     \
			static const std::uint32_t sAuxiliaryBegin;                                                                     \
		private:                                                                                                            \
			static std::uint32_t InitializePrescribedAttributeNames();

#define ATTRIBUTED_DEFINITIONS(Type, MemberAttributeCount)																	\
	const std::uint32_t AttributedFoo::sAuxiliaryBegin = InitializePrescribedAttributeNames();                              \
	std::uint32_t AttributedFoo::InitializePrescribedAttributeNames()                                                       \
	{                                                                                                                       \
		AnonymousEngine::Vector<std::string>& prescribedAttributeNames = sPrescribedAttributes[TypeIdClass()];              \
		prescribedAttributeNames.Reserve(Parent::sAuxiliaryBegin + MemberAttributeCount);                                   \
		AppendPrescribedAttributeNames(prescribedAttributeNames);                                                           \
		return prescribedAttributeNames.Size();                                                                             \
	}
}
