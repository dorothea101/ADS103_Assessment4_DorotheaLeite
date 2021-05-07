#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>
#include "res_path.h"

using namespace std;


//Struct old school- can do class, but we are going to use struct
struct Move {

	int row, col;
};



class GameBoard
{
public:
	static char BLANK;
	static char CROSS;
	static char NAUGHT;


	

	//Need a reference to the renderer
	SDL_Renderer* renderer;
	SDL_Texture* blank, * cross, * naught, * yes;

	//put this in 1
	SDL_Texture* scoreTexture = NULL; //FOR DRAWING strings to the screen

	char board[3][3];
	int boardX = 500, boardY = 100;
	int tileSize = 50;

	char player = CROSS, opponent = NAUGHT;

	int minimaxCount = 0;


	GameBoard(SDL_Renderer* renderer);  //constructor
	~GameBoard(); ///Deconstructor, to help with the cleanup
	void clearBoard();
	bool setTile(char type, int x, int y);
	void getTileBasedOnPixlXY(int pixelX, int pixelY, int& tileX, int& tileY);   ///int&= pass by reference
	bool checkForClick(SDL_Event& event, char type);
	bool checkForWin(char type);
	bool checkIfAnyPlacesFree();



	void draw();


	//MINIMAX STUFF
	int evaluate();
	int minimax(int depth, bool isMax, int alpha, int beta);
	int minimax(int depth, bool isMax);   //recursive function
	//minimax using alpha beta pruning



	Move findBestMove(char type);//unbeatable AI












};

