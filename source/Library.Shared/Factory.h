#pragma once

#include <string>
#include "HashMap.h"
#include "RTTI.h"

namespace AnonymousEngine
{
	/** This class is a templated abstract factory class.
	 *  There are macros defined which lets the user create custom factories
	 */
	template <typename AbstractProductT>
	class Factory : public RTTI
	{
		typedef HashMap<std::string, Factory<AbstractProductT>*> FactoryMap;
	public:
		typedef typename FactoryMap::Iterator FactoryIterator;

		/** Create an instance of the concrete product instance which this factory supports
		 *  @return An instance of the concrete product
		 */
		virtual AbstractProductT* Create() const = 0;
		/** Create an abstract product which this factory hierrarchy supports
		 *  @return The name of the concrete product class which this factory creates
		 */
		virtual std::string ClassName() const = 0;

		/** Finds the factory registered for a given name
		 *  @param name The name against which the registered factory is to be searched
		 *  @return If found return the address of the factory instance else return null
		 */
		static Factory<AbstractProductT>* Find(const std::string& name);
		/** Creates an instance of a concrete product based on the given product name
		 *  @param name The name of the concrete product type
		 *  @return An instance of the concerete product specified by name
		 */
		static AbstractProductT* Create(const std::string& name);
		
		/** Gets the begining of the factories list
		 *  @return The begin iterator of the factories list
		 */
		static FactoryIterator begin();
		/** Gets the end of the factories list
		 *  @return The end iterator of the factories list
		 */
		static FactoryIterator end();
		
		/** Register a factory against a product name
		 *  @param factory The factory which is to be registered
		 */
		static void Add(Factory<AbstractProductT>& factory);
		/** Remove a factory against a product name
		 *  @param name The name of the product for which the factory is to be removed
		 *  @return True if factory was removed, false otherwise
		 */
		static bool Remove(const std::string& name);
	private:
		static FactoryMap Factories;

		RTTI_DECLARATIONS(Factory, RTTI)
	};

#define CONCRETE_FACTORY_DECLARATIONS(AbstractProductT, ConcreteProductT)		\
	class ConcreteProductT##Factory : public AnonymousEngine::Factory<AbstractProductT>          \
	{                                                                           \
	public:                                                                     \
		ConcreteProductT##Factory();                                            \
		~ConcreteProductT##Factory();                                           \
		std::string ClassName() const override;                                 \
		AbstractProductT* Create() const override;                              \
		RTTI_DECLARATIONS(ConcreteProductT##Factory, AnonymousEngine::Factory<AbstractProductT>) \
	};

#define CONCRETE_FACTORY_DEFINITIONS(AbstractProductT, ConcreteProductT)		\
		RTTI_DEFINITIONS(ConcreteProductT##Factory)                             \
		ConcreteProductT##Factory::ConcreteProductT##Factory()                  \
		{                                                                       \
			Add(*this);                                                         \
		}                                                                       \
		ConcreteProductT##Factory::~ConcreteProductT##Factory()                 \
		{                                                                       \
			Remove(ClassName());                                                \
		}                                                                       \
		std::string ConcreteProductT##Factory::ClassName() const                \
		{                                                                       \
			return #ConcreteProductT;                                           \
		}                                                                       \
		AbstractProductT* ConcreteProductT##Factory::Create() const             \
		{                                                                       \
			AbstractProductT* product = new ConcreteProductT();                 \
			if (product == nullptr)                                             \
			{                                                                   \
				throw std::runtime_error("Created product was null");           \
			}                                                                   \
			return product;                                                     \
		}
}

#include "Factory.inl"
