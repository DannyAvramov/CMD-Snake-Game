/*
/////////////////////////////////////////////////////
// Created By: Danny Avramov                       //
// Description: A simple classic Snake             //
//              Game made for the Windows          //
//              command prompt.                    //
/////////////////////////////////////////////////////
*/
#include "console.h"
#include "Draw.h"
#include "Input.h"
#include "Logic.h"

int main(int argc, char *argv[]) {
	setWindow("Snake Game", 43, 32, true, false, false, false, false, false);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS); // Disables input from mouse
	srand((unsigned short)(time(0)));
	/// Draw
	struct Draw draw;
	draw.iBorderX = 42;
	draw.iBorderY = 26;
	draw.cBorder = '#';
	draw.iBorderColor = Red;

	draw.cPlayer = 'O';
	draw.cPlayerTail = 'o';
	draw.iPlayerColor = Turquise;

	draw.cTarget = '*';
	draw.iTargetColor = Yellow;
	
	draw.iScoreTextColor = Purple;
	draw.iScoreNumberColor = White;
	// Input
	Input input = Stop;
	/// Logic
	struct Logic logic;
	logicGO.bGameOverRetryTriggered = false;
	logicGO.bGameOverRetry = false;
	logic.bGameOver = false;

	logic.bMaxScore = false;
	logic.iScore = 0;

	logic.bPlayerProtectionBox = true;

	logic.iPlayerX = (draw.iBorderX / 2);
	logic.iPlayerY = (draw.iBorderY / 2);

	logic.iTargetX = RAND(draw.iBorderX);
	logic.iTargetY = RAND(draw.iBorderY);
	/// Main game loop
	while (!logic.bGameOver) {
		/// Draw
		DrawBorder(draw);
		DrawScore(draw, &logic);
		DrawPlayer(&draw, logic);
		DrawTarget(draw, &logic);
		/// Input
		InputKeyboard(draw, logic, &input);
		/// Logic
		LogicPlayerMovement(&draw, &logic, input);
		LogicBorder(draw, &logic);
		LogicScore(draw, &logic);
	}

	return GameOver(draw);
}
