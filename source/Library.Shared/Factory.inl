
namespace AnonymousEngine
{
	template<typename AbstractProductT>
	RTTI_DEFINITIONS(Factory<AbstractProductT>)

	template <typename AbstractProductT>
	typename Factory<AbstractProductT>::FactoryMap Factory<AbstractProductT>::Factories = Factory<AbstractProductT>::FactoryMap();

	template <typename AbstractProductT>
	Factory<AbstractProductT>* Factory<AbstractProductT>::Find(const std::string& name)
	{
		if (Factories.ContainsKey(name))
		{
			return Factories[name];
		}
		return nullptr;
	}

	template <typename AbstractProductT>
	AbstractProductT* Factory<AbstractProductT>::Create(const std::string& name)
	{
		if (Factories.ContainsKey(name))
		{
			return Factories[name]->Create();
		}
		throw std::runtime_error("Not configured to create product : " + name);
	}

	template <typename AbstractProductT>
	typename Factory<AbstractProductT>::FactoryIterator Factory<AbstractProductT>::begin()
	{
		return Factories.begin();
	}

	template <typename AbstractProductT>
	typename Factory<AbstractProductT>::FactoryIterator Factory<AbstractProductT>::end()
	{
		return Factories.end();
	}

	template <typename AbstractProductT>
	void Factory<AbstractProductT>::Add(Factory<AbstractProductT>& factory)
	{
		std::string className = factory.ClassName();
		if (Factories.ContainsKey(className) && !factory.Is(Factories[className]->TypeIdInstance()))
		{
			throw std::runtime_error("A factory of different type is already registered for class name = " + className);
		}
		Factories[className] = &factory;
	}

	template <typename AbstractProductT>
	bool Factory<AbstractProductT>::Remove(Factory<AbstractProductT>& factory)
	{
		return Factories.Remove(factory.ClassName());
	}
}