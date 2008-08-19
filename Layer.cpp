#include "Layer.h"
#include "Renderable.h"
#include "Color.h"
#include <OpenGL/gl.h>

using namespace std;

Layer::Layer(float width, float height, bool tiled) : mWidth(width), mHeight(height), mTiled(tiled)
{
}
