#include "Game.h"
#include "RotatingTriangle.h"
#include "YinYang.h"
#include "Widget.h"
#include "Button.h"
#include "Block.h"
#include "Streamy.h"
#include "Background.h"

#include <iostream>

using namespace std;

#include <OpenGL/glu.h>

static uint64_t target_framerate = 50;
#define MILLISECONDS_PER_FRAME (1000.0 / target_framerate)

static SDL_Surface* screen = NULL;
static uint64_t frames_since_last_update = 0;
static uint64_t frames = 0;     // at an fps of 50, this will overflow to 0 after ~11.7 billion years.

bool Game::done = false;
float Game::fps = 0.0;
vector<EventListener*> Game::mListeners;
static Point mMousePosition(0, 0);
Vector Game::mScreenSize(1024, 768);
Vector Game::mWorldSize(10000, 10000);

Point Game::mCameraPosition(Game::mScreenSize.width / 2, Game::mScreenSize.height / 2);


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

uint64_t Game::currentFrame()
{
	return frames;
}

uint64_t Game::framerate()
{
	return target_framerate;
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
			mMouseMovedInThisFrame = true;
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

void Game::update()
{
	Renderables renderables = Renderable::all();
	for (Renderables::iterator iter = renderables.begin(); iter != renderables.end(); ++iter)
	{
		(*iter)->update();
	}
}

void Game::renderPass(uint64_t frame)
{	
	const Rect cameraRect(mCameraPosition - (mScreenSize / 2), mScreenSize);
	
	Renderables renderables = Renderable::all();
	
	for (Renderables::iterator iter = renderables.begin(); iter != renderables.end(); ++iter)
	{
		Renderable& object = **iter;
		Rect boundingRect = object.boundingRect();
		
		if (!object.hidden() && cameraRect.overlaps(boundingRect))
		{
			// Motion blur
			Color::push();
			int max = 1;
			Color::translate(Color(1.0, 1.0, 1.0, 1.0 / max));
			for (int i = 0; i < max; ++i)
			{
				glMatrixMode(GL_MODELVIEW);
				glPushMatrix();
				object.render(frame - i);
				glMatrixMode(GL_MODELVIEW);
				glPopMatrix();
			}
			Color::pop();
		}
	}
}

void Game::render()
{
	glPushMatrix();
	// Camera.
	
	glTranslatef(-(mCameraPosition.x - (mScreenSize.width / 2)), -(mCameraPosition.y - (mScreenSize.height / 2)), 0.0);
	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	renderPass(frames);
	
	if (drawBoundingBoxes)
	{
		Renderables rs = Renderable::all();
		for (Renderables::const_iterator iter = rs.begin(); iter != rs.end(); ++iter)
		{
			Rect boundingRect = (*iter)->boundingRect();
			
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
	
	glPopMatrix();
	
	// TODO: Draw widgets here instead of compensating for the translation in the widget drawing code.
	// ^ would also ensure that widgets are always on top of content.
	
	SDL_GL_SwapBuffers();
}

void Game::calculateFps()
{
	static int ticks = 0;
	
	int now = SDL_GetTicks();
	if (now - ticks > 1000)
	{
		fps = frames_since_last_update;
		ticks = now;
		frames_since_last_update = 0;
	}
	
	++frames_since_last_update;
}

void Game::setCameraPosition(const Point& newPos, bool smooth)
{
	Point oldPos = mCameraPosition;
	
	// Limit camera to the world
	Point pos(newPos);
	if (pos.x < mScreenSize.width / 2.0)
		pos.x = mScreenSize.width / 2.0;
	else if (pos.x > mWorldSize.width - mScreenSize.width / 2.0)
		pos.x = mWorldSize.width - mScreenSize.width / 2.0;
	if (pos.y < mScreenSize.height / 2.0)
		pos.y = mScreenSize.height / 2.0;
	else if (pos.y > mWorldSize.height - mScreenSize.height / 2.0)
		pos.y = mWorldSize.height - mScreenSize.height / 2.0;
	
	// TODO: Smooth movement.
	mCameraPosition = pos;
	
	if (!mMouseMovedInThisFrame) // avoid piling up MouseMotion events when the camera is moved as a result of mouse movement
	{
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
		mMouseMovedInThisFrame = true;
	}
}

Point Game::mousePosition()
{
	return mMousePosition;
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
	SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS, 8);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	
	screen = SDL_SetVideoMode(mScreenSize.width, mScreenSize.height, 0, SDL_OPENGL);
	SDL_WM_SetCaption("gl2d", "gl2d");
	SDL_EnableUNICODE(1);
	
	glViewport(0, 0, screen->w, screen->h);
	glFrustum(0.0, screen->w, screen->h, 0.0, 300.0, 500.0);
	glTranslatef(0.0, 0.0, -300.0);
	
	glClearColor(0.0, 0.0, 0.0, 0.0);	
	
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);
	
	glEnable(GL_MULTISAMPLE_ARB);
	
	/* ALL CLEAR -- START HAVING FUN */
	Background bg;
	bg.setZIndex(-100.0);
	bg.setTexture(Texture::fromFile("heineken.jpg"));
	
	
	triangle = new RotatingTriangle;
	triangle->setZIndex(-1.0);
	widget = new Button;
	
	Texture* tex = Texture::fromFile("salmon.png");
	Block* b1 = new Block(Rect(300, 300, 50, 80), -60);
	b1->setTexture(tex);
	Block* b2 = new Block(Rect(200, 200, 100, 20), 15);
	
	YinYang* yy = new YinYang(Point(500, 500), 24);
	
	/* GAME LOOP */
	while (!done)
	{
		int now = SDL_GetTicks();
		
		handleEvents();
		update();
		render();
				
		// Maintain a stable FPS.
		now -= SDL_GetTicks();
		if (now < MILLISECONDS_PER_FRAME && !done)
		{
			SDL_Delay(MILLISECONDS_PER_FRAME - now);
		}
		
		calculateFps();
		
		++frames;
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
