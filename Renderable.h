#ifndef _RENDERABLE_H_
#define _RENDERABLE_H_

#include <OpenGL/gl.h>
#include <vector>

#include "Rect.h"

class Renderable;
typedef std::vector<Renderable*> Renderables;

class Renderable
{
private:
	int mLayer;
	Real mZIndex;
	bool mHidden;
public:
	static const Renderables& all();
	
	Renderable();
	virtual ~Renderable();
	
	/*
		Renders the object to screen.
		
		frame is given to enable the Renderable to handle accumulation effects
		such as motion blur by either calculating the state from the frame
		number or save previous states for re-rendering.
		
		It can be determined if render() is being called in an accumulation
		pass by comparing frame to Game::currentFrame().
		
		This function is only called if the object is determined to be on
		screen. This is determined by the result of boundingRect().
	*/
	virtual void render(uint64_t frame) = 0;
	
	/*
		Optional. This is called exactly once for all objects on screen. Use this
		to implement animation and whatever you may like.
		
		boundingRect() is used to determine whether this object is on screen, and
		thus, whether it should be updated.
	*/
	virtual void update() {}
	
	/*
		Return a rectangle that is guaranteed to contain this object. This
		is used to determine whether or not the object should be allowed to
		perform rendering, so it is important that draw() does not perform
		rendering outside this rectangle.
	*/
	virtual Rect boundingRect() const = 0;
	
	inline int layer() const { return mLayer; }
	inline void setLayer(int l) { mLayer = l; }
	inline Real zIndex() const { return mZIndex; }
	inline void setZIndex(Real z) { mZIndex = z; }
	inline bool hidden() const { return mHidden; }
	inline void setHidden(bool h) { mHidden = h; }
	inline void show() { mHidden = false; }
	inline void hide() { mHidden = true; }
};

#endif /* _RENDERABLE_H_ */
