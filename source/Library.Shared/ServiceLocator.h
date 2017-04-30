#pragma once
#include "Service.h"
#include "TextureLoaderService.h"
#include "RendererService.h"
#include "HashMap.h"
#include "CollisionManager.h"

namespace AnonymousEngine
{
	namespace Core
	{
		class ServiceLocator final
		{
		public:
			static const std::string sTextureLoader;
			static const std::string sRenderer;
			static const std::string sCollisionManager;

			/**
				Return the service of given type.
				@param[in] pServiceType Enum that holds the type of service.
				@return Pointer to the service. If service is not found nullptr is returned.
			*/
			static Service* GetService(std::string pServiceType);
			
			/**
				Return the service that handles texture loading
				@return Pointer to TextureLoaderService.
			*/
			static Graphics::TextureLoaderService* GetTextureLoader();
			
			/**
				Return the service that handles texture loading.
				@return Pointer to RendererService.
			*/
			static Graphics::RendererService* GetRenderer();
			
			/**
			* Return the service that handles collision manager.
			* @return Pointer to CollisionManager.
			*/
			static CollisionManager* GetCollisionManager();
			
			/**
				Add service to the list of services that this ServiceLocator can locate.
				@param[in] pServiceType Enum that holds the type of service.
				@param[in] pService Reference to the service that should be stored associated with pServiceType.
			*/
			static void AddService(std::string pServiceType, Service& pService);

		private:
			
			/**
				Hashmap of Service pointers and service type
			*/
			static HashMap<std::string, Service*> sServicesCache;
		};
	}
}