#include "Pch.h"
#include "ServiceLocator.h"

namespace AnonymousEngine
{
	namespace Core
	{
		const std::string ServiceLocator::sTextureLoader = "TextureLoader";
		const std::string ServiceLocator::sRenderer = "Renderer";
		const std::string ServiceLocator::sCollisionManager = "CollisionManager";

		HashMap<std::string, Service*> ServiceLocator::sServicesCache;

		Service* ServiceLocator::GetService(std::string pServiceType)
		{
			HashMap<std::string, Service*>::Iterator itr = sServicesCache.Find(pServiceType);
			if (itr != sServicesCache.end())
			{
				return itr->second;
			}
			// if service is not found
			return nullptr;
		}

		Graphics::TextureLoaderService* ServiceLocator::GetTextureLoader()
		{
			return static_cast<Graphics::TextureLoaderService*>(GetService(sTextureLoader));
		}

		Graphics::RendererService* ServiceLocator::GetRenderer()
		{
			return static_cast<Graphics::RendererService*>(GetService(sRenderer));
		}

		CollisionManager* ServiceLocator::GetCollisionManager()
		{
			return static_cast<CollisionManager*>(GetService(sCollisionManager));
		}

		void ServiceLocator::AddService(std::string pServiceType, Service& pService)
		{
			sServicesCache[pServiceType] = &pService;
		}
	}
}