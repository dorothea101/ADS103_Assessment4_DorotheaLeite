#include <iostream>
#include <string>
#include <SDL.h>
#include "GameBoard.h"
#include "cleanup.h"
#include "drawing_functions.h"
#include "SDL_TTF.h"

using namespace std;

int main(int argc, char** argv)
{
	//Setup SDL
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		cout << "Error: " << SDL_GetError() << endl;
		system("pause");
		return 1;
	}

	//Setup Window
	SDL_Window* window = SDL_CreateWindow("TIC TAC TOE", SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 1024, 768, SDL_WINDOW_SHOWN);
	
	if (window == NULL) {

		cout << "Error: " << SDL_GetError() << endl;
		SDL_Quit();
		system("pause");
		return 1;
	}

	//Setup renderer-lets us draw stuff to the screen
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
	//This is the size to draw things at before we scale it 
	//SDL_RenderSetLogicalSize(renderer, 2048, 1536);





	//Initialize sdl_image
	
	if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG)
	{
		SDL_Quit();
		cout << "sdl image did not initialise" << endl;
		return 1;
	}





	//initialize text to font
	if (TTF_Init() != 0)
	{
		SDL_Quit();
		cout << "sdl tff did not initialise" << endl;
		return 1;
	}

	///this I PUT IN EXTRA!!
	//LOAD a texture to draw
	string resPath = getResourcePath();
	SDL_Texture* texture = loadTexture("assets/yes.png", renderer);
	SDL_Texture* texture2 = loadTexture("assets/PlayerVersesPlayer.png", renderer);
	SDL_Texture* texture3 = loadTexture("assets/AiVersesPlayer.png", renderer);
	SDL_Texture* texture4 = loadTexture("assets/Reset.png", renderer);
	//putting this line in


	//run game for 5000 ticks(5 secs)
	while (SDL_GetTicks() < 4000)
	{
		//clear the screen
		SDL_RenderClear(renderer);    //up to here
		//draw what you want to the screen
		renderTexture(texture, renderer, 0, 0);
		//show image we've been rendering'
		SDL_RenderPresent(renderer);
	}
	
	




//Building Gameboard here(1)
	GameBoard gameBoard(renderer);
	

	bool quit = false;
	bool aiMode = true;
	int playerTurn = 1;
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
				if (e.key.keysym.scancode == SDL_SCANCODE_P)    //player
				{
					aiMode = false;
				}
				if (e.key.keysym.scancode == SDL_SCANCODE_A)    //AI
				{
					aiMode = true;
				}
			}
			//now here(3) this is the AI logic here
			if (aiMode == true)
			{
				if (gameBoard.checkForClick(e, GameBoard::CROSS)) //IF I PRESS CLICK, THE RE SHOULD BE A CROSS ON BOARD
				{
					Move aiMove = gameBoard.findBestMove(gameBoard.opponent);   //you can switch this up and put in player here, instead of opponent
					if (aiMove.row != -1 && aiMove.col != -1)        //will be = to -1 if we cant place a move
					{
						gameBoard.setTile(gameBoard.opponent, aiMove.row, aiMove.col);
					}
				}
			}
			else
			{
				if (playerTurn == 1 && gameBoard.checkForClick(e, GameBoard::CROSS))
				{
					playerTurn = 2;
				}
				else if (playerTurn == 2 && gameBoard.checkForClick(e, GameBoard::NAUGHT))
				{
					playerTurn = 1;
				}
			}


		}
		


		
		SDL_SetRenderDrawColor(renderer,205, 50, 167, 255);//rgba (0-255)
		SDL_RenderClear(renderer);

		//go here after you build gameboard above(2)
		gameBoard.draw();
		//SDL_RenderClear(renderer);
		renderTexture(texture2, renderer,200, 300);
		renderTexture(texture3, renderer,200, 400);
		renderTexture(texture4, renderer,200, 500);
		SDL_RenderPresent(renderer);
		
		//A--------------------------------------------------------
		//added this**
		
		//renderCopy;
		//SDL_Rect drawRect;
		//drawRect.h;
		//drawRect.w;
		//SDL_RenderCopy(renderer, yes, NULL, &drawRect);
		//up to here***/
		//B---------------------------------------------------------
		//get window surface
		//screenSurface = SDL_GetWindowSurface(window);

		//fill the surface
		//SDL_FillRect( "assets/yes.png");

		//**Trying again
		
		//C----------------------------------------------
		//window we are rendering to
		//SDL_Window* gWindow = NULL;

		//THE Surface contained by the window
		//SDL_Surface* gScreenSurface = NULL;

		//The image will load and show on the screen
		//SDL_Surface* gYes = NULL;
		//D--------------------------------------------------

		/*bool loadTexture()
		{
			//Loading success flag
			bool success = true;

			//Load splash/png? image
			gYes = SDL_loadTexture("assets/yes.png");
			if (gYes = NULL)
			{
				printf("Unable to load texture %s! SDL Error: %\n", "assets/yes.png", SDL_GetError());
				success = false;
			}
			return success;

		}*/
		//----------------------------------------------------




		//Swaps the buffers
		SDL_RenderPresent(renderer);


	}

	return 0;
}

