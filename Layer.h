#ifndef _LAYER_H_
#define _LAYER_H_

#include <vector>
#include "Rect.h"

class Renderable;

class Layer
{
private:
	float mWidth, mHeight;
	bool mTiled;
	std::vector<Renderable*> mRenderables;
	
	Layer(const Layer& other) {}
public:
	explicit Layer(float width, float height, bool tiled = false);
	
	void add(Renderable& renderable) { mRenderables.push_back(&renderable); }
	const std::vector<Renderable*>& renderables() const { return mRenderables; }
	
	float width() const { return mWidth; }
	float height() const { return mHeight; }
	bool tiled() const { return mTiled; }
};

#endif /* _LAYER_H_ */
