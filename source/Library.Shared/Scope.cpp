#include "Scope.h"

namespace AnonymousEngine
{
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

	Datum* Scope::Search(const std::string& name, Scope** foundScope)
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

	Datum* Scope::operator[](const std::uint32_t index)
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
