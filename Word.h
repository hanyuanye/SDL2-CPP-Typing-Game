#ifndef WORD_H
#define WORD_H

#pragma once
#include <string>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <iostream>
#include "Vec2d.h"

const int WORD_WIDTH = 150;
const int WORD_HEIGHT = 50;

class Word
{
private:
	SDL_Texture * word_texture;
	SDL_Renderer* renderer;
	SDL_Rect rect;
	std::string word;
	const char* char_word;
	Vec2d pos;
	Vec2d velocity;
	int SCREEN_WIDTH;

public:
	Word(std::string _word, SDL_Renderer* ren, int _SCREEN_WIDTH);
	~Word();
	void change_string(std::string _input);
	void create(Vec2d _pos, Vec2d _velocity);
	void update(double _time_tick);
	void render();
	bool compare(std::string _word);
	bool past_edge();
};

#endif