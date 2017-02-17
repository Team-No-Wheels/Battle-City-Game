#include "Scope.h"

namespace AnonymousEngine
{
	RTTI_DEFINITIONS(Scope)

	Scope::Scope() : mParent(nullptr)
	{
	}

	Scope::Scope(const Scope& rhs)
	{
		rhs;
	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		rhs;
		return (*this);
	}

	Datum* Scope::Find(const std::string& name)
	{
		name;
		return nullptr;
	}

	Datum* const Scope::Find(const std::string& name) const
	{
		name;
		return nullptr;
	}

	Datum* Scope::Search(const std::string& name, Scope** foundScope)
	{
		name;
		foundScope;
		return nullptr;
	}

	Datum* const Scope::Search(const std::string& name, Scope** foundScope) const
	{
		name;
		foundScope;
		return nullptr;
	}

	Datum& Scope::Append(const std::string& name)
	{
		name;
		return mDatum;
	}

	Scope& Scope::AppendScope(const std::string& name)
	{
		name;
		return (*this);
	}

	void Scope::Adopt(Scope& scope, const std::string& name)
	{
		scope;
		name;
	}

	const Scope* Scope::GetParent() const
	{
		return nullptr;
	}

	Datum* Scope::operator[](const std::string& name)
	{
		name;
		return nullptr;
	}

	Datum* const Scope::operator[](const std::string& name) const
	{
		name;
		return nullptr;
	}

	Datum* Scope::operator[](const std::uint32_t index)
	{
		index;
		return nullptr;
	}

	Datum* const Scope::operator[](const std::uint32_t index) const
	{
		index;
		return nullptr;
	}

	bool Scope::operator==(const Scope& rhs) const
	{
		rhs;
		return false;
	}

	bool Scope::operator!=(const Scope& rhs) const
	{
		rhs;
		return true;
	}

	Scope::~Scope()
	{
	}

	bool Scope::Equals(const RTTI* rhs) const
	{
		if (this == rhs)
		{
			return true;
		}

		if (rhs == nullptr)
		{
			return false;
		}

		const Scope* scope = rhs->As<Scope>();
		if (scope != nullptr)
		{
			return operator==(*scope);
		}
		return false;
	}

	std::string Scope::ToString() const
	{
		return "Scope";
	}

	void Scope::FromString(const std::string& str)
	{
		str;
	}

	void Scope::Copy(const Scope& rhs)
	{
		rhs;
	}

	void Scope::Clear()
	{
	}

	void Scope::Orphan(Scope& scope)
	{
		scope;
	}
}
