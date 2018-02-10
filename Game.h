#ifndef GAME_H
#define GAME_H

#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include <stdio.h>
#include <vector>
#include <memory>
#include <fstream>
#include <stdlib.h>
#include <time.h>

#include "Word.h"
#include "Vec2d.h"


class Game {
public:
	Game();
	~Game();

	void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);

	void handleEvent();
	void update();
	void clean();
	void gameOver();
	void render();
	void parseFile(const char* file);

	void addCurrentWordList(int index);
	void removeCurrentWordList(int index);
	bool running;


private:
	int count;
	int SCREEN_WIDTH;
	int SCREEN_HEIGHT;
	bool isRunning;
	bool game_over;

	int velocity;
	int words_cleared;
	SDL_Window *window;
	SDL_Renderer *renderer;
	
	std::string input;
	std::shared_ptr<Word> player_input;

	std::vector<std::shared_ptr<Word>> total_word_list;
	std::vector<std::shared_ptr<Word>> current_word_list;
};

#endif