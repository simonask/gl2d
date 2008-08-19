#include "EventListener.h"
#include "Game.h"

EventListener::EventListener(int mask) : mMask(mask)
{
	Game::registerEventListener(this);
}

EventListener::EventListener(const EventListener& other) : mMask(other.mMask)
{
	Game::registerEventListener(this);
}

EventListener::~EventListener()
{
	Game::unregisterEventListener(this);
}
