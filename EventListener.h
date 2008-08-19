#ifndef _EVENTLISTENER_H_
#define _EVENTLISTENER_H_

#include <SDL/SDL.h>

class EventListener
{
private:
	int mMask;
protected:
	explicit EventListener(int mask);
	EventListener(const EventListener&);
	virtual ~EventListener();
public:
	/*
		handleEvent is called anytime an event is fired that matches
		this EventListener's eventMask.
		
		An EventListener can either choose to handle the event or ignore
		it. If it handled the event, no other EventListener will be notified
		of the event.
		
		An example of this is a Widget, which does not want to handle mouse
		events occurring when the mouse is not over the widget.
		
		handleEvent should return true if it handled the event, and false if
		it was ignored.
	*/
	virtual bool handleEvent(const SDL_Event& event) = 0;
	inline int eventMask() const { return mMask; }
};

#endif /* _EVENTLISTENER_H_ */
