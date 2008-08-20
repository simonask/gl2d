#include "Color.h"
#include <queue>
using namespace std;

const Color Color::id(1.0, 1.0, 1.0, 1.0);
Color Color::matrix(Color::id);

static queue<Color> colorStack;

void Color::push()
{
	colorStack.push(matrix);
}

void Color::pop()
{
	if (colorStack.size() > 0)
	{
		matrix = colorStack.front();
		colorStack.pop();
	}
	else
	{
		loadIdentity();
	}
}
