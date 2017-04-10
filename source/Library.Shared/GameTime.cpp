#include "GameTime.h"

namespace AnonymousEngine
{
	using namespace std::chrono;

	GameTime::GameTime()
		: mCurrentTime(), mTotalGameTime(0), mElapsedGameTime(0)
	{
	}

	const high_resolution_clock::time_point& GameTime::CurrentTime() const
	{
		return mCurrentTime;
	}

	void GameTime::SetCurrentTime(const high_resolution_clock::time_point& currentTime)
	{
		mCurrentTime = currentTime;
	}

	const milliseconds& GameTime::TotalGameTime() const
	{
		return mTotalGameTime;
	}

	void GameTime::SetTotalGameTime(const std::chrono::milliseconds& totalGameTime)
	{
		mTotalGameTime = totalGameTime;
	}

	const milliseconds& GameTime::ElapsedGameTime() const
	{
		return mElapsedGameTime;
	}

	void GameTime::SetElapsedGameTime(const std::chrono::milliseconds& elapsedGameTime)
	{
		mElapsedGameTime = elapsedGameTime;
	}

	bool GameTime::operator==(const GameTime& rhs) const
	{
		return (mCurrentTime == rhs.mCurrentTime) && (mElapsedGameTime == rhs.mElapsedGameTime) && (mTotalGameTime == rhs.mTotalGameTime);
	}

	bool GameTime::operator!=(const GameTime& rhs) const
	{
		return !((*this) == rhs);
	}
}
