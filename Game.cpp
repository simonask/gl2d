#include "Game.h"
#include "RotatingTriangle.h"
#include "Widget.h"
#include "Button.h"
#include "Block.h"
#include "Streamy.h"

#include <iostream>

using namespace std;

#include <OpenGL/glu.h>

#define FRAMERATE 50
#define MILLISECONDS_PER_FRAME (1000.0 / FRAMERATE)

static SDL_Surface* screen = NULL;
static long long frames_since_last_update = 0;
static long long frames = 0;

bool Game::done = false;
float Game::fps = 0.0;
vector<EventListener*> Game::mListeners;
vector<Layer*> Game::mLayers;
static Point mMousePosition(0, 0);
Point Game::mCameraPosition(0, 0);

static Layer layer(800, 600, false);
static Layer world(800, 600, false);
static RotatingTriangle* triangle;
static Widget* widget;
static bool drawBoundingBoxes = false;

void Game::registerEventListener(EventListener* object)
{
	mListeners.push_back(object);
}

void Game::unregisterEventListener(EventListener* object)
{
	for (vector<EventListener*>::iterator iter = mListeners.begin(); iter != mListeners.end(); ++iter)
	{
		if (*iter == object)
			mListeners.erase(iter);
	}
}

static volatile bool isDrawing = false;
static Block* drawingBlock = NULL;

void beginDrawing()
{
	if (!isDrawing)
	{
		isDrawing = true;
		
		drawingBlock = new Block(Rect(Game::screenToWorldCoord(mMousePosition), Vector(0, 0)), Degrees(0.0));
		drawingBlock->setColor(Color(0.0, 1.0, 0.0, 0.7));
		layer.add(*drawingBlock);
	}
}

void resizeDrawingBlock()
{
	if (isDrawing && drawingBlock)
	{
		Vector newSize = Game::screenToWorldCoord(mMousePosition) - drawingBlock->rect().origin;
		drawingBlock->setRect(Rect(drawingBlock->rect().origin, newSize));
	}
}

void endDrawing()
{
	if (isDrawing)
	{
		isDrawing = false;
		drawingBlock = NULL;
	}
}

void Game::handleEvents()
{
	SDL_Event event;
	
	while (!done && SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		// Some basic event handling that needs to be done regardless
		case SDL_MOUSEMOTION:
			mMousePosition = Point(event.motion.x, event.motion.y);
			break;
		case SDL_QUIT:
			done = true;
			break;
			
		// Debugging stuff...
		case SDL_KEYDOWN:
			switch (event.key.keysym.sym)
			{
			case SDLK_ESCAPE:
				done = true;
				break;
			case SDLK_d:
				drawBoundingBoxes = !drawBoundingBoxes;
				break;
			}
			break;
		}
		
		bool eventWasHandled = false;
		vector<EventListener*>::iterator iter = mListeners.begin();
		while (!eventWasHandled && iter != mListeners.end())
		{
			if (SDL_EVENTMASK(event.type) & (*iter)->eventMask())
				eventWasHandled = (*iter)->handleEvent(event);
			++iter;
		}
		
		if (!eventWasHandled)
		{
			switch (event.type)
			{
				case SDL_MOUSEBUTTONDOWN:
					beginDrawing();
					break;
				case SDL_MOUSEBUTTONUP:
					endDrawing();
					break;
				case SDL_MOUSEMOTION:
					resizeDrawingBlock();
					break;
			}
		}
	}
}


void Game::draw()
{
	glPushMatrix();
	
	// Camera.
	glTranslatef(-mCameraPosition.x, -mCameraPosition.y, -1.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	const Rect cameraRect(mCameraPosition, Vector(screen->w, screen->h));
	for (vector<Layer*>::const_iterator ilayer = mLayers.begin(); ilayer != mLayers.end(); ++ilayer)
	{
		const vector<Renderable*>& renderables((*ilayer)->renderables());
		
		// TODO: Parallaxing
		for (vector<Renderable*>::const_iterator iter = renderables.begin(); iter != renderables.end(); ++iter)
		{
			Renderable& object(**iter);

			Rect boundingRect = object.boundingRect();

			if (cameraRect.overlaps(boundingRect))
			{
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();

				object.update();
				object.draw();

				glMatrixMode(GL_MODELVIEW);
				glPopMatrix();

				if (drawBoundingBoxes)
				{
					glMatrixMode(GL_MODELVIEW);
					glPushMatrix();

					glTranslatef(boundingRect.origin.x, boundingRect.origin.y, 0.0);

					glHint(GL_LINE_SMOOTH_HINT, GL_FASTEST);
					glBegin(GL_LINE_LOOP);
					{
						glLineWidth(1.0);
						Color(1.0, 1.0, 1.0, 0.5).set();
						glVertex2f(0.0, 0.0);
						glVertex2f(boundingRect.size.width, 0.0);
						glVertex2f(boundingRect.size.width, boundingRect.size.height);
						glVertex2f(0.0, boundingRect.size.height);
					}
					glEnd();

					glPopMatrix();
				}
			}
		}
	}
	
	glPopMatrix();
	
	// TODO: Draw widgets here instead of compensating for the translation in the widget drawing code.
	// ^ would also ensure that widgets are always on top of content.
	
	SDL_GL_SwapBuffers();
}


void Game::calculateFps()
{
	static int ticks = 0;
	static int frames_since_last_update = 0;
	
	int now = SDL_GetTicks();
	if (now - ticks > 1000)
	{
		fps = frames_since_last_update;
		ticks = now;
		frames += frames_since_last_update;
		frames_since_last_update = 0;
	}
	
	++frames_since_last_update;
}

void Game::setCameraPosition(const Point& pos, bool smooth)
{
	Point oldPos = mCameraPosition;
	
	// TODO: Smooth movement.
	mCameraPosition = pos;
	
	Point diff = mCameraPosition - oldPos;
	
	// Send out MouseMotion event, because the world has moved under the mouse.
	SDL_Event event;
	event.type = SDL_MOUSEMOTION;
	event.motion.x = (Uint16)mMousePosition.x;
	event.motion.y = (Uint16)mMousePosition.y;
	event.motion.xrel = 0;
	event.motion.yrel = 0;
	event.motion.which = 0;
	event.motion.state = 1;
	SDL_PushEvent(&event);
}

int Game::run(int argc, char* argv[])
{
	/* INITIALIZATION */
	SDL_Init(SDL_INIT_EVERYTHING);
	atexit(SDL_Quit);
	
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 4);
	
	screen = SDL_SetVideoMode(800, 600, 0, SDL_OPENGL);
	SDL_WM_SetCaption("gl2d", "gl2d");
	SDL_EnableUNICODE(1);
	
	glViewport(0, 0, screen->w, screen->h);
	glFrustum(0.0, screen->w, screen->h, 0.0, 1.0, 100.0);
	
	glClearColor(0.0, 0.0, 0.0, 0.0);	
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	/* ALL CLEAR -- START HAVING FUN */
	triangle = new RotatingTriangle;
	layer.add(*triangle);
	widget = new Button;
	layer.add(*widget);
	mLayers.push_back(&layer);
	
	Texture* tex = Texture::fromFile("salmon.png");
	Block* b1 = new Block(Rect(300, 300, 50, 80), -60);
	b1->setTexture(tex);
	world.add(*b1);
	Block* b2 = new Block(Rect(200, 200, 100, 20), 15);
	world.add(*b2);
	mLayers.push_back(&world);
	
	/* GAME LOOP */
	while (!done)
	{
		int now = SDL_GetTicks();
		
		handleEvents();

		draw();
		
		// Maintain a stable FPS.
		now -= SDL_GetTicks();
		if (now < MILLISECONDS_PER_FRAME && !done)
		{
			SDL_Delay(MILLISECONDS_PER_FRAME - now);
		}
		
		calculateFps();
	}
	
	/* CLEANUP */
	delete tex;
	delete b1;
	delete b2;
	
	SDL_Quit();
	
	return 0;
}

int main(int argc, char *argv[])
{
	return Game::run(argc, argv);
}
