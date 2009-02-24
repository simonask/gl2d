#include "Collidable.h"

static Collidables collidables;

const Collidables& Collidable::all()
{
	return collidables;
}

Collidable::Collidable()
{
	collidables.push_back(this);
}

Collidable::~Collidable()
{
	for (Collidables::iterator iter = collidables.begin(); iter != collidables.end(); ++iter)
	{
		if (*iter == this)
		{
			collidables.erase(iter);
			break;
		}
	}
}
