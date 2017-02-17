#include "Scope.h"

namespace AnonymousEngine
{
	RTTI_DEFINITIONS(Scope)

	Scope::Scope() : mParent(nullptr)
	{
	}

	Scope::Scope(const Scope& rhs) : Scope()
	{
		Copy(rhs);
	}

	Scope& Scope::operator=(const Scope& rhs)
	{
		if (*this != rhs)
		{
			Clear();
			Copy(rhs);
		}
		return (*this);
	}

	Datum* Scope::Find(const std::string& name)
	{
		auto it = mDatumMap.Find(name);
		if (it != mDatumMap.end())
		{
			return &it->second;
		}
		return nullptr;
	}

	const Datum* Scope::Find(const std::string& name) const
	{
		return const_cast<Scope*>(this)->Find(name);
	}

	Datum* Scope::Search(const std::string& name, Scope** foundScope)
	{
		Scope* scopeToSearch = this;
		while (scopeToSearch != nullptr)
		{
			Datum* datum = scopeToSearch->Find(name);
			if (datum != nullptr)
			{
				if (foundScope != nullptr)
				{
					*foundScope = scopeToSearch;
				}
				return datum;
			}
			scopeToSearch = scopeToSearch->mParent;
		}
		return nullptr;
	}

	const Datum* Scope::Search(const std::string& name, Scope** foundScope) const
	{
		return const_cast<Scope*>(this)->Search(name, foundScope);
	}

	Datum& Scope::Append(const std::string& name)
	{
		bool hasInserted;
		auto it = mDatumMap.Insert(std::make_pair(name, Datum()), hasInserted);
		if (hasInserted)
		{
			mOrderVector.PushBack(&(*it));
		}
		return it->second;
	}

	Scope& Scope::AppendScope(const std::string& name)
	{
		Datum& datum = Append(name);
		if (datum.Type() != Datum::DatumType::Scope)
		{
			throw std::runtime_error("A non scope datum exist in the current scope at the given key");
		}
		Scope* scope = new Scope();
		scope->mParent = this;
		datum.PushBack(scope);
		return *(datum.Get<Scope*>(datum.Size() - 1));
	}

	void Scope::Adopt(Scope& scope, const std::string& name)
	{
		Orphan(scope);
		Append(name) = &scope;
	}

	const Scope* Scope::GetParent() const
	{
		return mParent;
	}

	Datum& Scope::operator[](const std::string& name)
	{
		return Append(name);
	}

	const Datum& Scope::operator[](const std::string& name) const
	{
		return mDatumMap[name];
	}

	Datum& Scope::operator[](const std::uint32_t index)
	{
		return mOrderVector[index]->second;
	}

	const Datum& Scope::operator[](const std::uint32_t index) const
	{
		return mOrderVector[index]->second;
	}

	bool Scope::operator==(const Scope& rhs) const
	{
		if (mOrderVector.Size() != rhs.mOrderVector.Size())
		{
			return false;
		}
		for (std::uint32_t index = 0; index < mOrderVector.Size(); ++index)
		{
			if (mOrderVector[index]->first != rhs.mOrderVector[index]->first || mOrderVector[index]->second != rhs.mOrderVector[index]->second)
			{
				return false;
			}
		}
		return true;
	}

	bool Scope::operator!=(const Scope& rhs) const
	{
		return !(operator==(rhs));
	}

	Scope::~Scope()
	{
		Clear();
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

	void Scope::FromString(const std::string&)
	{
		throw std::runtime_error("Unsupported operation");
	}

	void Scope::Copy(const Scope& rhs)
	{
		for (const auto pairPtr : rhs.mOrderVector)
		{
			const std::string& key = pairPtr->first;
			const Datum& rhsDatum = pairPtr->second;
			if (rhsDatum.Type() == Datum::DatumType::Scope)
			{
				Datum& datumToAppend = Append(key);
				for (std::uint32_t index = 0; index < rhsDatum.Size(); ++index)
				{
					Scope* scope = new Scope(*rhsDatum.Get<Scope*>());
					scope->mParent = this;
					datumToAppend.PushBack(scope);
				}
			}
			else
			{
				Append(key) = rhsDatum;
			}
		}
		mParent = nullptr;
	}

	void Scope::Clear()
	{
		for (const auto& pairPtr : mOrderVector)
		{
			Datum& datum = pairPtr->second;
			if (datum.Type() == Datum::DatumType::Scope)
			{
				for (std::uint32_t index = 0; index < datum.Size(); ++index)
				{
					Scope* childScope = datum.Get<Scope*>(index);
					childScope->Clear();
					delete childScope;
				}
			}
		}
		mOrderVector.Clear();
		mDatumMap.Clear();
	}

	void Scope::Orphan(Scope& scope)
	{
		if (scope.mParent != nullptr)
		{
			for (const auto& pairPtr : scope.mParent->mOrderVector)
			{
				Datum& datum = pairPtr->second;
				if (datum.Type() == Datum::DatumType::Scope)
				{
					// removes the scope it was found in the datum
					datum.Remove(&scope);
				}
			}
			scope.mParent = nullptr;
		}
	}
}
