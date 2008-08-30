#include "EventListener.h"
#include "Game.h"
#include <vector>

using namespace std;

static EventListeners gListeners;

const EventListeners& EventListener::all() { return gListeners; }

void EventListener::registerEventListener(EventListener* self)
{
	gListeners.push_back(self);
}

void EventListener::unregisterEventListener(EventListener* self)
{
	for (EventListeners::iterator iter = gListeners.begin(); iter != gListeners.end(); ++iter)
	{
		if (self == *iter)
		{
			iter = gListeners.erase(iter);
			return;
		}
	}
}

EventListener::EventListener(int mask) : mMask(mask)
{
	registerEventListener(this);
}

EventListener::EventListener(const EventListener& other) : mMask(other.mMask)
{
	registerEventListener(this);
}

EventListener::~EventListener()
{
	unregisterEventListener(this);
}
