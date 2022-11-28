#include "Screen.h"

Screen::Screen(SDL_Window* wind, SDL_Renderer* rend) {
	m_window = wind;
	m_render = rend;
	int flags = IMG_INIT_PNG;
	IMG_Init(flags);
}

void Screen::DrawStaticElements() {
	SDL_SetRenderDrawColor(m_render, 0xFF, 0xFF, 0xFF, 0xFF);

	// Draw the field
	for(int y = 0; y < Constants::WINDOW_HEIGHT; ++y) {
		if(y % 10) {
			SDL_RenderDrawPoint(m_render, Constants::WINDOW_WIDTH / 2, y);
		}
	}
}


void Screen::MenuLoad() {
	//Load elem for menu + init his rectangle
	SDL_Surface* tempa_surfs = new SDL_Surface {NULL};
	tempa_surfs = IMG_Load("Menu.png");
	m_menu = SDL_CreateTextureFromSurface(m_render, tempa_surfs);
	tempa_surfs = NULL;
	delete tempa_surfs;

	rectMenu.x = 140;
	rectMenu.y = 150;
	rectMenu.w = 1000;
	rectMenu.h = 420;

}

void Screen::menu(bool& start, bool& botRun) {
	//menu mehanics and Drawing
	SDL_RenderCopy(m_render, m_menu, NULL, &rectMenu);
	SDL_Event event;
	while(SDL_PollEvent(&event)) {
		if(event.type == SDL_KEYDOWN) {
			if(event.key.keysym.sym == SDLK_1) {
				botRun = true;
				start = false;

			} else if(event.key.keysym.sym == SDLK_2) {
				botRun = false;
				start = false;

			}
		}
	}
}

//ball drowing
void Screen::BallDraw(Ball& ball) {
	ball.rect.x = static_cast<int>(ball.m_position.x);
	ball.rect.y = static_cast<int>(ball.m_position.y);

	SDL_RenderCopy(m_render, ball.m_ball, NULL, &ball.rect);
}

//bricks drawning
void Screen::BrickDraw(Brick& brick) {
	SDL_SetRenderDrawColor(m_render, 0xFF, 0xFF, 111, 0xFF);
	brick.rect.y = static_cast<int>(brick.m_position.y);

	SDL_RenderFillRect(m_render, &brick.rect);
}


//load pmg for Score + init his rectangle
void Screen::ScoreLoad() {
	SDL_Surface* tempa_surf = new SDL_Surface {NULL};
	tempa_surf = IMG_Load("One.png");
	m_One = SDL_CreateTextureFromSurface(m_render, tempa_surf);
	tempa_surf = NULL;
	delete tempa_surf;



	SDL_Surface* temp_surf = new SDL_Surface {NULL};
	temp_surf = IMG_Load("Wins.png");
	m_Wins = SDL_CreateTextureFromSurface(m_render, temp_surf);
	temp_surf = NULL;
	delete temp_surf;


	m_rectFirst.x = (Constants::WINDOW_WIDTH/4) - 100;
	m_rectFirst.y = 40;
	m_rectFirst.w = 20;
	m_rectFirst.h = 25;

	m_rectSecond.x = (3*Constants::WINDOW_WIDTH/4) - 100;
	m_rectSecond.y = 40;
	m_rectSecond.w = 20;
	m_rectSecond.h = 25;

	//cell rectangle
	rect1ScoreTable = {(Constants::WINDOW_WIDTH/4) - 93, 36, 150, 38};
	rect2ScoreTable = {(3*Constants::WINDOW_WIDTH/4) - 93, 36, 150, 38};
}

//Drawning Score according to data
void Screen::DrawScore(SDL_Rect rectFirst, SDL_Rect rectSecond) {
	SDL_RenderDrawRect(m_render, &rect2ScoreTable);
	SDL_RenderDrawRect(m_render, &rect1ScoreTable);
	if(m_pOneScore < 10) {
		for(int i = 0; i < m_pOneScore; i++) {
			rectFirst.x = rectFirst.x + 15;
			SDL_RenderCopy(m_render, m_One, NULL, &rectFirst);
		}
	} else if(m_pOneScore == 10) {

		rectSecond.w = 300;
		rectSecond.h = 120;
		rectSecond.x = (Constants::WINDOW_WIDTH/4) - 150;
		rectSecond.y = 100;
		SDL_RenderCopy(m_render, m_Wins, NULL, &rectSecond);
		m_pOneScore = -1;
		m_pTwoScore = -1;
	}

	if(m_pTwoScore < 10) {
		for(int i = 0; i < m_pTwoScore; i++) {
			rectSecond.x = rectSecond.x + 15;
			SDL_RenderCopy(m_render, m_One, NULL, &rectSecond);
		}
	} else if(m_pTwoScore == 10) {
		rectFirst.w = 300;
		rectFirst.h = 120;
		rectFirst.x = (3*Constants::WINDOW_WIDTH/4) - 150;
		rectFirst.y = 100;
		SDL_RenderCopy(m_render, m_Wins, NULL, &rectFirst);
		m_pOneScore = -1;
		m_pTwoScore = -1;

	}

}

