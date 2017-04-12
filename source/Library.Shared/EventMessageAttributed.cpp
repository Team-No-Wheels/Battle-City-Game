#include "EventMessageAttributed.h"
#include "World.h"

namespace AnonymousEngine
{
	namespace Containers
	{
		ATTRIBUTED_DEFINITIONS(EventMessageAttributed)

		EventMessageAttributed::EventMessageAttributed() :
			mWorld(nullptr)
		{
			AddExternalAttribute("Subtype", &mSubtype, 1);
		}

		EventMessageAttributed::EventMessageAttributed(const EventMessageAttributed& rhs) :
			Attributed(rhs), mSubtype(rhs.mSubtype), mWorld(rhs.mWorld)
		{
		}

		EventMessageAttributed::EventMessageAttributed(EventMessageAttributed&& rhs) noexcept :
			Attributed(rhs), mSubtype(rhs.mSubtype), mWorld(rhs.mWorld)
		{
			rhs.mSubtype.clear();
			rhs.mWorld = nullptr;
		}

		EventMessageAttributed& EventMessageAttributed::operator=(const EventMessageAttributed& rhs)
		{
			if (this != &rhs)
			{
				Attributed::operator=(rhs);
				mSubtype = rhs.mSubtype;
				mWorld = rhs.mWorld;
			}
			return (*this);
		}

		EventMessageAttributed& EventMessageAttributed::operator=(EventMessageAttributed&& rhs) noexcept
		{
			if (this != &rhs)
			{
				Attributed::operator=(rhs);
				mSubtype = rhs.mSubtype;
				mWorld = rhs.mWorld;
				rhs.mSubtype.clear();
				rhs.mWorld = nullptr;
			}
			return (*this);
		}

		const std::string& EventMessageAttributed::GetSubtype() const
		{
			return mSubtype;
		}

		void EventMessageAttributed::SetSubtype(const std::string& subtype)
		{
			mSubtype = subtype;
		}

		World* EventMessageAttributed::GetWorld() const
		{
			return static_cast<World*>(mWorld);
		}

		void EventMessageAttributed::SetWorld(World& world)
		{
			assert(world.Is(World::TypeIdClass()));
			mWorld = &world;
		}

		void EventMessageAttributed::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
		{
			Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
			prescribedAttributeNames.PushBack("Subtype");
		}
	}
}
