#include "Pch.h"
#include "ServiceLocator.h"

namespace AnonymousEngine
{
	namespace Core
	{
		HashMap<ServiceLocator::ServiceType, Service*> ServiceLocator::sServicesCache;

		Service* ServiceLocator::GetService(ServiceType pServiceType)
		{
			HashMap<ServiceType, Service*>::Iterator itr = sServicesCache.Find(pServiceType);
			if (itr != sServicesCache.end())
			{
				return itr->second;
			}
			// if service is not found
			return nullptr;
		}

		Graphics::TextureLoaderService* ServiceLocator::GetTextureLoader()
		{
			return static_cast<Graphics::TextureLoaderService*>(GetService(ServiceType::TextureLoader));
		}

		Graphics::RendererService* ServiceLocator::GetRenderer()
		{
			return static_cast<Graphics::RendererService*>(GetService(ServiceType::Renderer));
		}

		CollisionManager* ServiceLocator::GetCollisionManager()
		{
			return static_cast<CollisionManager*>(GetService(ServiceType::CollisionManager));
		}

		void ServiceLocator::AddService(ServiceType pServiceType, Service& pService)
		{
			sServicesCache[pServiceType] = &pService;
		}
	}
}