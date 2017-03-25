#pragma once

#include <string>
#include "HashMap.h"
#include "RTTI.h"

namespace AnonymousEngine
{
	template <typename AbstractProductT>
	class Factory : public RTTI
	{
		typedef HashMap<std::string, Factory<AbstractProductT>*> FactoryMap;
	public:
		typedef typename FactoryMap::Iterator FactoryIterator;

		virtual AbstractProductT* Create() const = 0;
		virtual std::string ClassName() const = 0;

		static Factory<AbstractProductT>* Find(const std::string& name);
		static AbstractProductT* Create(const std::string& name);
		
		static FactoryIterator begin();
		static FactoryIterator end();
		
		static void Add(Factory<AbstractProductT>& factory);
		static bool Remove(Factory<AbstractProductT>& factory);
	private:
		static FactoryMap Factories;

		RTTI_DECLARATIONS(Factory, RTTI)
	};

#define CONCRETE_FACTORY(AbstractProductT, ConcreteProductT)		\
	class ConcreteProductT##Factory : Factory<AbstractProductT>     \
	{                                                               \
	public:                                                         \
		ConcreteProductT##Factory()                                 \
		{                                                           \
			Add(*this);                                             \
		}                                                           \
		~ConcreteProductT##Factory()                                \
		{                                                           \
			Remove(*this);                                          \
		}                                                           \
		std::string ClassName() const override                      \
		{                                                           \
			return #ConcreteProductT;                               \
		}                                                           \
		AbstractProductT* Create() const override                   \
		{                                                           \
			AbstractProductT* product = new ConcreteProductT();     \
			throw std::runtime_error("Created product was null");   \
			return product;                                         \
		}                                                           \
	};
}

#include "Factory.inl"
