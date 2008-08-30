#include "Renderable.h"
#include <algorithm>
#include <iostream>

using namespace std;

static Renderables renderables;
static bool somethingAddedSinceLastSort = false;

bool compareRenderables(const Renderable* left, const Renderable* right)
{
	return left->layer() <= right->layer() && left->zIndex() <= right->zIndex();
}

Renderables Renderable::all()
{
	if (somethingAddedSinceLastSort)
	{
		sort(renderables.begin(), renderables.end(), compareRenderables);
		somethingAddedSinceLastSort = false;
	}
	
	return renderables;
}

Renderable::Renderable() : mLayer(0), mZIndex(0.0), mHidden(false)
{
	renderables.push_back(this);
	somethingAddedSinceLastSort = true;
}

Renderable::~Renderable()
{
	for (Renderables::iterator iter = renderables.begin(); iter != renderables.end(); ++iter)
	{
		if (*iter == this)
		{
			renderables.erase(iter);
			break;
		}
	}
}
