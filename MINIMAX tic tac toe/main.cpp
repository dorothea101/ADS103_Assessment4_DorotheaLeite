#include <iostream>
#include <string>
#include <SDL.h>
#include "GameBoard.h"

using namespace std;

int main(int argc, char** argv)
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Error: " << SDL_GetError() << endl;
		system("pause");
		return 1;
	}
	SDL_Window* window = SDL_CreateWindow("TIC TAC TOE", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	
	if (window == NULL) {

		cout << "Error: " << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 
		SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		cout << "Error: " << SDL_GetError() << endl;
		SDL_DestroyWindow(window);
		SDL_Quit();
		system("pause");
		return 1;




	}
//Building Gameboard here(1)
	GameBoard gameBoard(renderer);
	

	bool quit = false;
	//GAME LOOP
	while (!quit)
	{
		//get user inputs first
		SDL_Event e;
		while (SDL_PollEvent(&e) != 0)
		{
			//User clicks close button
			if (e.type == SDL_QUIT)
				quit = true;
			if (e.type == SDL_KEYDOWN)
			{
				//press escape key
				if (e.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
					quit = true;
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_RETURN) {
					gameBoard.clearBoard();
				}
			}
			//now here(3) this is the AI logic here
			if (gameBoard.checkForClick(e, GameBoard::CROSS)) //IF I PRESS CLICK, THE RE SHOULD BE A CROSS ON BOARD
			{
				Move aiMove = gameBoard.findBestMove(gameBoard.opponent);   //you can switch this up and put in player here, instead of opponent
				if(aiMove.row != -1 && aiMove.col != -1)        //will be = to -1 if we cant place a move
				{
					gameBoard.setTile(gameBoard.opponent, aiMove.row, aiMove.col);
				}
			}


		}
		



		SDL_SetRenderDrawColor(renderer, 170, 170, 170, 255);//rgba (0-255)
		SDL_RenderClear(renderer);

		//go here after you build gameboard above(2)
		gameBoard.draw();


		//Swaps the buffers
		SDL_RenderPresent(renderer);


	}

	return 0;
}

