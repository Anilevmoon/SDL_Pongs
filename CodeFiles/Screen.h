#pragma once
#include <iostream>
#include <Windows.h>
#include <SDL.h>
#include <SDL_image.h>
#include "CONSTANTS.h"
#include "Brick.h"
#include "Ball.h"
class Screen {
	public:
	int m_pOneScore = 0;
	int m_pTwoScore = 0;

	SDL_Rect m_rectFirst;
	SDL_Rect m_rectSecond;

	

	Screen(SDL_Window* wind, SDL_Renderer* rend);
	void MenuLoad();
	void menu(bool &start, bool &botRun);
	void DrawStaticElements();
	void BallDraw(Ball &ball);
	void BrickDraw(Brick &brick);
	void ScoreLoad();
	void DrawScore(SDL_Rect rectFirst, SDL_Rect rectSecond);

	private:
	SDL_Window* m_window;
	SDL_Renderer* m_render;

	SDL_Texture* m_menu;
	SDL_Texture *m_Null = NULL;
	SDL_Texture *m_One = NULL;
	SDL_Texture *m_Wins = NULL;

	SDL_Rect rectMenu;
	SDL_Rect rect1ScoreTable;
	SDL_Rect rect2ScoreTable;
	
};

