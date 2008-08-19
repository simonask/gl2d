#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Renderable.h"
#include "Texture.h"
#include "Point.h"
#include "Color.h"
#include "Rect.h"

class Block : public Renderable
{
private:
	Color mColor;
	Texture* mTexture;
	Rect mRect;
	Degrees mRotation;
public:
	Block(const Rect& rect, Degrees rotation = 0.0);
	
	virtual void draw() const;
	
	Color color() const { return mColor; }
	void setColor(const Color& col) { mColor = col; }
	Texture* texture() const { return mTexture; }
	void setTexture(Texture* texture) { mTexture = texture; }
	
	inline Degrees rotation() const { return mRotation; }
	inline void setRotation(const Degrees rot) { mRotation = rot; }
	Rect rect() const { return mRect; }
	void setRect(const Rect& r) { mRect = r; }
	Rect boundingRect() const;
	
	bool contains(const Point& p) const;
};

#endif /* _BLOCK_H_ */
