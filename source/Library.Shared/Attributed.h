#pragma once

#include "Vector.h"
#include "HashMap.h"
#include "RTTI.h"
#include "Scope.h"

namespace AnonymousEngine
{
	class Attributed : Scope
	{
	public:
		Attributed() = default;
		virtual ~Attributed();

		Attributed(const Attributed& rhs) = default;
		Attributed(const Attributed&& rhs);

		Attributed& operator=(const Attributed& rhs) = default;
		Attributed& operator=(const Attributed&& rhs);

		Datum& AppendAuxiliaryAttribute(const std::string& name);
		static std::uint32_t AuxiliaryBegin();

		bool IsPrescribedAttribute(const std::string& name) const;
		bool IsAuxiliaryAttribute(const std::string& name) const;
		bool IsAttribute(const std::string& name) const;
	protected:
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
	private:
		static HashMap<std::uint64_t, Vector<std::string>> sPrescribedAttributes;
		static const std::uint32_t sAuxiliaryBegin;

		static std::uint32_t InitializeAttributes();

		RTTI_DECLARATIONS(Attributed, Scope)
	};
}
