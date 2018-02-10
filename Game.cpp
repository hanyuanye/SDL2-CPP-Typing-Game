#include "Game.h"

const double TIME_TICK = 1.0 / 60.0;
const double TIME_TO_ADD_WORD = 1;
double TICKS_SINCE_LAST_ADDITION = 0;
const int WORD_LENGTH_LIMIT = 4;

Game::Game() {}	

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
	int flags = 0;
	if (fullscreen) {
		flags = SDL_WINDOW_FULLSCREEN;
	}

	TTF_Init();

	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

		renderer = SDL_CreateRenderer(window, -1, 0);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
		}

		running = true;
	}
	else {
		running = false;
	}
	SCREEN_WIDTH = width;
	SCREEN_HEIGHT = height;
	srand(time(0));
	parseFile("text.txt");
	SDL_StartTextInput();
	game_over = false;
	words_cleared = 0;
}

void Game::handleEvent() {
	SDL_Event event;

	while (SDL_PollEvent(&event)) {
		switch (event.type) {
		case SDL_QUIT:
			running = false;
			break;
		case SDL_TEXTINPUT:
			input += event.text.text;
			std::cout << input << std::endl;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_BACKSPACE && input.size() != 0) {
				input.pop_back();
			}
			std::cout << input << std::endl;
			break;
		default:
			break;
		}
	}
}

void Game::update() 
{
	if (!game_over) {
		for (unsigned i = 0; i < current_word_list.size(); i++) {
			if (current_word_list[i]->compare(input)) {
				words_cleared++;
				removeCurrentWordList(i);
				input.clear();
			}
			else if (current_word_list[i]->past_edge()) {
				gameOver();
			}
			else {
				current_word_list[i]->update(TIME_TICK);
			}
		}
		TICKS_SINCE_LAST_ADDITION++;
		if (TICKS_SINCE_LAST_ADDITION * TIME_TICK > 1) {
			if (total_word_list.size() != 0) {
				int index = rand() % total_word_list.size();
				addCurrentWordList(index);
				TICKS_SINCE_LAST_ADDITION = 1;
			}
		}
	}
}

void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	TTF_Quit();
	SDL_Quit();
}

void Game::gameOver()
{
	SDL_RenderClear(renderer);
	std::string game_over_string = "Game Over! Words Cleared: " + std::to_string(words_cleared);
	TTF_Font* Sans = TTF_OpenFont("arial.ttf", 24);
	SDL_Color White = { 255, 255, 255 };
	SDL_Surface* surface_message = TTF_RenderText_Solid(Sans, game_over_string.c_str(), White);
	SDL_Texture* word_texture = SDL_CreateTextureFromSurface(renderer, surface_message);
	SDL_Rect rect = { SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 25, 400, 50 };
	SDL_RenderCopy(renderer, word_texture, NULL, &rect);

	SDL_FreeSurface(surface_message);
	SDL_DestroyTexture(word_texture);
	SDL_RenderPresent(renderer);
	game_over = true;
}

void Game::render() {
	if (!game_over) {
		SDL_RenderClear(renderer);
		for (unsigned i = 0; i < current_word_list.size(); i++) {
			current_word_list[i]->render();
		}
		SDL_RenderPresent(renderer);
	}
}

void Game::parseFile(const char * file)
{
	std::ifstream readFile(file);
	std::string line;
	while (std::getline(readFile, line)) {
		if (line.length() <= WORD_LENGTH_LIMIT) {
			continue;
		}
		auto sp1 = std::make_shared<Word> (line, renderer, SCREEN_WIDTH);
		total_word_list.push_back(sp1);
	}
}

void Game::addCurrentWordList(int index)
{

	int ypos = rand() % (SCREEN_HEIGHT - WORD_HEIGHT);
	Vec2d _pos(0, ypos);
	int xvelocity = rand() % 50 + SCREEN_WIDTH / 7;
	Vec2d _velocity(xvelocity, 0);

	total_word_list[index]->create(_pos, _velocity);
	current_word_list.push_back(total_word_list[index]);
}

void Game::removeCurrentWordList(int index)
{
	current_word_list.erase(current_word_list.begin() + index);
}
