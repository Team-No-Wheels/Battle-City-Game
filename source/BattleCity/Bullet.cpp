#include "Pch.h"
#include "Bullet.h"
#include "TankPlayer.h"
#include "ScoreMessageStructs.h"
#include "World.h"

namespace AnonymousEngine
{
	ATTRIBUTED_DEFINITIONS(Bullet);

	Bullet::Bullet() :
		mMoveComponent(CreateAction("MovementComponent", "ActionMove").As<ActionMove>()),
		mShootParent(nullptr), isStrong(false)
	{
		Event<MessageCollision>::Subscribe(*this);
	}

	Bullet::Bullet(ActionShoot& parent) :
		mMoveComponent(CreateAction("MovementComponent", "ActionMove").As<ActionMove>()),
		mShootParent(&parent)
	{
		Event<MessageCollision>::Subscribe(*this);
	}

	Bullet::~Bullet()
	{
		Event<MessageCollision>::Unsubscribe(*this);
		mShootParent = nullptr;
	}

	void Bullet::SetShootParent(ActionShoot& parent)
	{
		mShootParent = &parent;
	}

	ActionMove& Bullet::MoveComponent()
	{
		return *mMoveComponent;
	}

	void Bullet::Update(WorldState& worldState)
	{
		Entity::Update(worldState);

		worldState.mEntity = this;

		worldState.mEntity = nullptr;
	}

	void Bullet::Notify(class EventPublisher& publisher)
	{
		Event<MessageCollision>* curEvent = publisher.As<Event<MessageCollision>>();

		if (curEvent != nullptr)
		{
			MessageCollision* message = const_cast<MessageCollision*>(&curEvent->Message());
			Vector<CollisionPair>* entities = &message->GetEntities();

			for (CollisionPair e : *entities)
			{
				// Check If Player
				TankPlayer* player = e.first->As<TankPlayer>();
				if (player == nullptr)
				{
					player = e.second->As<TankPlayer>();
				}

				// Check If Bullet
				Bullet* bullet = e.first->As<Bullet>();
				if (bullet == nullptr)
				{
					bullet = e.second->As<Bullet>();
				}

				// Try Executing Actions If This Bullet Exists In List
				if (bullet != nullptr && bullet == this)
				{
					// Do Stuff If Player
					if (player != nullptr && !player->IsInvincible())
					{
						PlayerSideDamageMessage damageMessage(false, message->WorldState());
						const std::shared_ptr<Core::Event<PlayerSideDamageMessage>> eventptr = std::make_shared<Core::Event<PlayerSideDamageMessage>>(damageMessage);
						message->WorldState().mWorld->EventQueue().Enqueue(eventptr, message->WorldState().mGameTime, 0u);
					}

					// Do Stuff If Enemy
					/*
						std::string tankType = //GET TANK TYPE NAME STRING
						ScoreEventMessage scoreMessage(tankType, message->WorldState());
						const std::shared_ptr<Core::Event<PlayerscoreMessageSideDamageMessage>> eventptr = std::make_shared<Core::Event<scoreMessage>>(scoreMessage);
						message->WorldState().mWorld->EventQueue().Enqueue(eventptr, message->WorldState().mGameTime, 0u);
					*/

					// Do Stuff If Wall

					// Do Stuff if Flag
					/*
						PlayerSideDamageMessage damageMessage(true, message->WorldState());
						const std::shared_ptr<Core::Event<PlayerSideDamageMessage>> eventptr = std::make_shared<Core::Event<PlayerSideDamageMessage>>(damageMessage);
						message->WorldState().mWorld->EventQueue().Enqueue(eventptr, message->WorldState().mGameTime, 0u);
					*/

					mShootParent->PendKillBullet(*this);
				}
			}
		}
	}

	void Bullet::AppendPrescribedAttributeNames(AnonymousEngine::Vector<std::string>& prescribedAttributeNames)
	{
		Parent::AppendPrescribedAttributeNames(prescribedAttributeNames);
	}

	ENTITY_FACTORY_DEFINITIONS(Bullet);
}
