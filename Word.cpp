#include "Word.h"



Word::Word(std::string _word, SDL_Renderer* ren, int _SCREEN_WIDTH)
{
	renderer = ren;
	word = _word;
	SCREEN_WIDTH = _SCREEN_WIDTH;
}


Word::~Word()
{
	SDL_DestroyTexture(word_texture);
	
}

void Word::change_string(std::string _input)
{
	word = _input;
}

void Word::create(Vec2d _pos, Vec2d _velocity)
{
	this->pos = _pos;
	this->velocity = _velocity;
	TTF_Font* Sans = TTF_OpenFont("arial.ttf", 24);
	SDL_Color White = { 255, 255, 255 };
	SDL_Surface* surface_message = TTF_RenderText_Solid(Sans, word.c_str(), White);
	word_texture = SDL_CreateTextureFromSurface(renderer, surface_message);

	SDL_FreeSurface(surface_message);

	TTF_CloseFont(Sans);

	SDL_Rect _rect = { pos.get_x(), pos.get_y(), WORD_WIDTH, WORD_HEIGHT };
	rect = _rect;
}

void Word::update(double _time_tick)
{
	pos += velocity.scalarMultiple(_time_tick);
	rect.x = pos.get_x();
	rect.y = pos.get_y();
}

void Word::render()
{
	SDL_RenderCopy(renderer, word_texture, NULL, &rect);
}

bool Word::compare(std::string _word)
{
	return (this->word == _word);
}

bool Word::past_edge()
{
	return (pos.get_x() + WORD_WIDTH > SCREEN_WIDTH);
}
