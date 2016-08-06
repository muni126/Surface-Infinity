#include "Engine.h"
//Constructor
Engine::Engine()
{
	_window = nullptr;
	_title = "Surface Infinity";
	_screenWidth = 1600;
	_screenHeight = 900;
	_gameState = GameState::PLAY;
}

//De-constructor
Engine::~Engine()
{
}

void Engine::run()
{
	_init();
	_loop();
}

//Private engine functions

//Initialize SDL
void Engine::_init()
{
	SDL_Init(SDL_INIT_EVERYTHING);
	_window = SDL_CreateWindow(_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_OPENGL);

	if (_window == nullptr) {
		_fatalError("SDL Window could not initialize!");
	}

	SDL_GLContext glContext = SDL_GL_CreateContext(_window);
	if (glContext == nullptr) {
		_fatalError("SDL_GL context could not initialize!");
	}

	GLenum status = glewInit();
	if (status != GLEW_OK) {
		_fatalError("GLEW could not initialize!");
	}

	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
}

//Loop for input
void Engine::_loop()
{
	while (_gameState != GameState::EXIT) {
		_tick();
		_render();
	}
	cout << "Exiting!" << endl;
}

void Engine::_tick()
{
	_input();
}

void Engine::_render()
{
	glClearDepth(1);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glEnableClientState(GL_COLOR_ARRAY);
	glBegin(GL_TRIANGLES);
	glColor3f(1.0f, 1.0f, 1.0f);
	glVertex2f(0, 0);
	glVertex2f(_event.motion.x - 440, _event.motion.y - 440);
	glVertex2f(_event.motion.x - 460, _event.motion.y - 460);
	glEnd();

	SDL_GL_SwapWindow(_window);
}

//Listen for input
void Engine::_input()
{
	while (SDL_PollEvent(&_event)) {
		switch (_event.type) {
			case SDL_QUIT:
				_gameState = GameState::EXIT;
				break;
			case SDL_MOUSEMOTION:
				cout << _event.motion.x << " " << _event.motion.y << endl;
		}
	}
}

//Crash
void Engine::_fatalError(string error)
{
	cout << "Fatal error occured!" << endl << error << endl;
	_gameState = GameState::EXIT;
}

//Setters and Getters

//Set title of window
void Engine::setTitle(char * title)
{
	_title = title;
	SDL_SetWindowTitle(_window, _title);
}
