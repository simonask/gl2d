#ifndef _BUTTON_H_
#define _BUTTON_H_

#include "Widget.h"
#include "Color.h"

class Button : public Widget
{
private:
	Color color;
public:
	explicit Button();
	
	virtual void drawWidget() const;
	
	virtual void mouseOver(const SDL_MouseMotionEvent&);
	virtual void mouseOut(const SDL_MouseMotionEvent&);
	virtual void mouseDown(const SDL_MouseButtonEvent&);
	virtual void mouseUp(const SDL_MouseButtonEvent&);
};

#endif /* _BUTTON_H_ */
