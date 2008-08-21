#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "Renderable.h"
#include "Texture.h"

class Background : public Renderable
{
private:
	Texture* mTexture;
	Real mAlpha;
public:
	Background();
	virtual void render(uint64_t frame);
	virtual Rect boundingRect() const;
	inline void setAlpha(Real alpha) { mAlpha = alpha; }
	inline Real alpha() const { return mAlpha; }
	virtual void setTexture(Texture* texture) { mTexture = texture; }
	virtual Texture* texture() const { return mTexture; }
};

#endif /* _BACKGROUND_H_ */
