#ifndef _BLOCK_H_
#define _BLOCK_H_

#include "Renderable.h"
#include "BoxCollider.h"
#include "Texture.h"
#include "Point.h"
#include "Color.h"
#include "Rect.h"

class Block : public Renderable, public BoxCollider
{
private:
	Color mColor;
	Texture* mTexture;
public:
	Block(const Rect& rect, Degrees rotation = 0.0);
	
	virtual void render(uint64_t frame);
	virtual void debugRender(uint64_t frame);
	virtual Rect boundingRect() const;
	
	Color color() const { return mColor; }
	void setColor(const Color& col) { mColor = col; }
	Texture* texture() const { return mTexture; }
	void setTexture(Texture* texture) { mTexture = texture; }
	
	inline Degrees rotation() const { return mRotation; }
	inline void setRotation(const Degrees rot) { mRotation = rot; }
	Rect rect() const { return mRect; }
	void setRect(const Rect& r) { mRect = r; }
	
	bool contains(const Point& p) const;
};

#endif /* _BLOCK_H_ */
