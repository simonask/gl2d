#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "Renderable.h"
#include "Texture.h"

class Background : public Renderable
{
private:
	Texture* mTexture;
	Real mAlpha;
	Vector mClipSize;
public:
	Background();
	virtual void render(uint64_t frame);
	virtual Rect boundingRect() const;
	inline void setAlpha(Real alpha) { mAlpha = alpha; }
	inline Real alpha() const { return mAlpha; }
	inline void setClipSize(const Vector& clipsize) { mClipSize = clipsize; }
	inline Vector clipSize() const { return mClipSize; }
	virtual void setTexture(Texture* texture) { mTexture = texture; }
	virtual Texture* texture() const { return mTexture; }
};

#endif /* _BACKGROUND_H_ */
