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
		/** Default initialize an attributed instance
		 */
		Attributed();
		/** Destroy the attributed instance
		 */
		virtual ~Attributed();

		/** Initialize an attributed instance by copying values from another instance
		 *  @param rhs The other instance to copy the values from
		 */
		Attributed(const Attributed& rhs);
		/** Initialize an attributed instance by moving values from another instance
		 *  @param rhs The other instance to move the values from
		 */
		Attributed(Attributed&& rhs) noexcept;

		/** Copy values from another instance to this
		 *  @param rhs The other instance to copy the values from
		 *  @return A reference to this instance
		 */
		Attributed& operator=(const Attributed& rhs);
		/** Move values from another instance to this
		 *  @param rhs The other instance to move the values from
		 *  @return A reference to this instance
		 */
		Attributed& operator=(Attributed&& rhs);

		/** Adds an auxiliary attribute to the current instance
		 *  @param name The name of the auxiliary attribute to add
		 *  @return A reference to the newly added attribute Datum
		 */
		Datum& AddAuxiliaryAttribute(const std::string& name);
		/** Get the first index at which the auxiliary attributes begin
		 *  @return The index at which the auxiliary attributes start
		 */
		static std::uint32_t AuxiliaryBegin();

		/** Check if the given name is a prescribed attribute or not
		 *  @param name The name of the attribute to check
		 *  @return A boolean indicating whether the attribute is a prescribed attribute or not
		 */
		bool IsPrescribedAttribute(const std::string& name) const;
		/** Check if the given name is an auxiliary attribute or not
		 *  @param name The name of the attribute to check
		 *  @return A boolean indicating whether the attribute is an auxiliary attribute or not
		 */
		bool IsAuxiliaryAttribute(const std::string& name) const;
		/** Check if the given name is an attribute or not
		 *  @param name The name of the attribute to check
		 *  @return A boolean indicating whether the given name corresponds to an attribute or not
		 */
		bool IsAttribute(const std::string& name) const;
	protected:
		// In the constructor of a derived class add all the prescribed attributes first. "This" is added automatically

		/** Adds an internal attribute of type integer with the given name, value and size
		 *  @param name The name of the attribute to add
		 *  @value The value of the attribute
		 *  @size The number of items in the attribute
		 */
		Datum& AddInternalAttribute(const std::string& name, const std::int32_t value, const std::uint32_t size);
		/** Adds an internal attribute of type float with the given name, value and size
		 *  @param name The name of the attribute to add
		 *  @value The value of the attribute
		 *  @size The number of items in the attribute
		 */
		Datum& AddInternalAttribute(const std::string& name, const float value, const std::uint32_t size);
		/** Adds an internal attribute of type string with the given name, value and size
		 *  @param name The name of the attribute to add
		 *  @value The value of the attribute
		 *  @size The number of items in the attribute
		 */
		Datum& AddInternalAttribute(const std::string& name, const std::string& value, const std::uint32_t size);
		/** Adds an internal attribute of type vector with the given name, value and size
		 *  @param name The name of the attribute to add
		 *  @value The value of the attribute
		 *  @size The number of items in the attribute
		 */
		Datum& AddInternalAttribute(const std::string& name, const glm::vec4& value, const std::uint32_t size);
		/** Adds an internal attribute of type matrix with the given name, value and size
		 *  @param name The name of the attribute to add
		 *  @value The value of the attribute
		 *  @size The number of items in the attribute
		 */
		Datum& AddInternalAttribute(const std::string& name, const glm::mat4& value, const std::uint32_t size);
		/** Adds an internal attribute of type RTTI* with the given name, value and size
		 *  @param name The name of the attribute to add
		 *  @value The value of the attribute
		 *  @size The number of items in the attribute
		 */
		Datum& AddInternalAttribute(const std::string& name, RTTI* const value, const std::uint32_t size);

		/** Adds an external attribute of type integer with the given name, address and size
		 *  @param name The name of the attribute to add
		 *  @address The address of the attribute
		 *  @size The number of items in the attribute
		 */
		Datum& AddExternalAttribute(const std::string& name, std::int32_t* address, const std::uint32_t size);
		/** Adds an external attribute of type float with the given name, address and size
		 *  @param name The name of the attribute to add
		 *  @address The address of the attribute
		 *  @size The number of items in the attribute
		 */
		Datum& AddExternalAttribute(const std::string& name, float* address, const std::uint32_t size);
		/** Adds an external attribute of type string with the given name, address and size
		 *  @param name The name of the attribute to add
		 *  @address The address of the attribute
		 *  @size The number of items in the attribute
		 */
		Datum& AddExternalAttribute(const std::string& name, std::string* address, const std::uint32_t size);
		/** Adds an external attribute of type vector with the given name, address and size
		 *  @param name The name of the attribute to add
		 *  @address The address of the attribute
		 *  @size The number of items in the attribute
		 */
		Datum& AddExternalAttribute(const std::string& name, glm::vec4* address, const std::uint32_t size);
		/** Adds an external attribute of type matrix with the given name, address and size
		 *  @param name The name of the attribute to add
		 *  @address The address of the attribute
		 *  @size The number of items in the attribute
		 */
		Datum& AddExternalAttribute(const std::string& name, glm::mat4* address, const std::uint32_t size);
		/** Adds an external attribute of type RTTI* with the given name, address and size
		 *  @param name The name of the attribute to add
		 *  @address The address of the attribute
		 *  @size The number of items in the attribute
		 */
		Datum& AddExternalAttribute(const std::string& name, RTTI** address, const std::uint32_t size);

		/** Adds an external attribute of type integer with the given name, address and size
		 *  @param name The name of the attribute to add
		 *  @address The address of the attribute
		 *  @size The number of items in the attribute
		 */
		void AddNestedScope(const std::string& name, Scope& scope);

		/** Validate if all prescribed attributes are added to the current instance or not
		 *  Checks if attribute being added is a valid prescribed attribute.
		 *  This should be called at the end of all child class constructors
		 */
		void ValidateAllPrescribedAttributesAreAdded() const;

		/** Appends the names of the prescribed attributes of this class to the attribute names list static hashmap.
		 *  This method should be redefined in all the descendants of Attributed class
		 *  For child classes call Parent::AppendPrescribedAttributes and pass reference to prescribed attributes
		 *  list of child class before adding the child class attribute names to the list
		 *  @param prescribedAttributeNames A reference to the vector in the hashmap to which this names are to be added
		 */
		static void AppendPrescribedAttributeNames(Vector<std::string>& prescribedAttributeNames);

		/** Stores the starting index of the auxiliary attributes
		 *  This is equivalent to the total number of prescribed attributes
		 *  Each of the descendants of attributed redefines this variable (part of the attributed macros)
		 */
		static const std::uint32_t sAuxiliaryBegin;
		/** This hashmap stores a list of prescribed attribute names for attributed class and all its descendants
		 */
		static HashMap<std::uint64_t, Vector<std::string>> sPrescribedAttributes;
	private:
		// This instance variable is used to keep track of whether all prescribed attributes are added to the current instance
		std::uint32_t mPrescribedAttributesAdded;

		// Helper for copying data from another attributed class. Used by copy constructor and assignment
		void Copy(const Attributed& rhs);

		// Helper for moving data from another attributed class. Used by move constructor and assignment
		void Move(Attributed& rhs);

		// Helper method to add internal attributes of all types
		template <typename T>
		Datum& AppendInternalAttribute(const std::string&name, const T& value, const Datum::DatumType type, const std::uint32_t size);

		// Helper method to add external attributes of all types
		template <typename T>
		Datum& AppendExternalAttribute(const std::string&name, T* address, const std::uint32_t size);

		// Checks if attribute being added is a valid prescribed attribute
		void ValidateAttribute(const std::string& name);

		// Initializes the sAuxiliaryBegin count by appending all prescribed names to the list
		// Each of the descendants of attributed redefines this method(part of the attributed macros)
		static std::uint32_t InitializePrescribedAttributeNames();

		RTTI_DECLARATIONS(Attributed, Scope)
	};

// This macro needs to be added to any class declaration that falls under the Attribute hierrarchy
#define ATTRIBUTED_DECLARATIONS()																							\
		protected:                                                                                                          \
			/* For child classes call Parent::AppendPrescribedAttributes and pass reference to prescribed attributes */     \
			/* list of child class before adding the child class attribute names to the list                         */     \
			static void AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames);     \
			static const std::uint32_t sAuxiliaryBegin;                                                                     \
		private:                                                                                                            \
			static std::uint32_t InitializePrescribedAttributeNames();

// This macro needs to be added to any class definition that falls under the Attribute hierrarchy
#define ATTRIBUTED_DEFINITIONS(Type, MemberAttributeCount)																	\
	const std::uint32_t Type::sAuxiliaryBegin = InitializePrescribedAttributeNames();                                       \
	std::uint32_t Type::InitializePrescribedAttributeNames()                                                                \
	{                                                                                                                       \
		AnonymousEngine::Vector<std::string>& prescribedAttributeNames = sPrescribedAttributes[TypeIdClass()];              \
		prescribedAttributeNames.Reserve(Parent::sAuxiliaryBegin + MemberAttributeCount);                                   \
		AppendPrescribedAttributeNames(prescribedAttributeNames);                                                           \
		return prescribedAttributeNames.Size();                                                                             \
	}
}
