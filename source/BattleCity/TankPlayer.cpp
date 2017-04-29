#include "Pch.h"
#include "TankPlayer.h"

using namespace AnonymousEngine;
RTTI_DEFINITIONS(TankPlayer);

TankPlayer::TankPlayer() :
	mLives(2), mMaxLives(9), mIsInvincible(false), mStars(0), mTimeInvincible(0)
{

}

TankPlayer::~TankPlayer()
{

}

void TankPlayer::IncrementLives()
{
	if (mLives < mMaxLives)
	{
		++mLives;
	}
}

void TankPlayer::DecrementLives()
{
	if (mLives == 0)
	{
		// Game Over
	}

	else
	{
		--mLives;
	}
}

void TankPlayer::IncrementStars()
{
	if (mStars < 3)
		++mStars;
}

void TankPlayer::SetInvincibility(bool state)
{
	mIsInvincible = state;
}

bool TankPlayer::IsInvincible()
{
	return mIsInvincible;
}

void TankPlayer::Update(WorldState& worldState)
{
	Entity::Update(worldState);

	if (mIsInvincible)
	{
		SetInvincibility( (mTimeInvincible += worldState.mGameTime.ElapsedGameTime()) < mInvincbleLimit);
	}
}