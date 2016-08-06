#pragma once
//Standard libraries
#include <iostream>
#include <string>
//External Libraries
#include <SDL.h>
#include <GL/glew.h>

using namespace std;

enum class GameState {PLAY, EXIT};

class Engine
{
public:
	Engine();
	~Engine();

	void run();

	

	void setTitle(char*title);

private:
	SDL_Window* _window;
	GameState _gameState;
	const char* _title;
	int _screenWidth, _screenHeight;
	SDL_Event _event;

	void _init();
	void _input();
	void _loop();
	void _tick();
	void _render();
	void _fatalError(string error);
};

