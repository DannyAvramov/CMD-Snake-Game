/*
/////////////////////////////////////////////////////
// Created By: Danny Avramov                       //
// Description: A simple classic Snake             //
//              Game made for the Windows          //
//              command prompt.                    //
/////////////////////////////////////////////////////
*/
#include "CallMain.h"
#include <Avramov\console.hpp> // #include "console.hpp"
#include "Draw.h"
#include "Input.h"
#include "Logic.h"

using con::Color;

int main(int argc, char *argv[]) {
	con::setWindow("Snake Game", 43, 32, true, false, false, false, false, false);
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), ENABLE_MOUSE_INPUT | ENABLE_EXTENDED_FLAGS); // Disables input from mouse
	srand((unsigned short)(time(0)));
	/// Draw
	Draw draw;
	draw.SetBorderSize(42, 26);
	draw.SetBorder('#');
	draw.SetBorderColor(Color::Red);

	draw.SetPlayer(/*Snake Head*/'O', /*Snake Tail*/'o');
	draw.SetPlayerColor(Color::Turquise);

	draw.SetTarget('*');
	draw.SetTargetColor(Color::Yellow);

	draw.SetScoreTextColor(/*Score Text*/Color::Purple, /*Score Number*/Color::White);
	// Input
	Input input;
	/// Logic
	Logic logic;
	logic.SetInput(Logic::Movement::Stop); // Stops the player from moving when spawned
	logic.SetGameOverRetryTriggered(false);
	logic.SetGameOverRetry(false);
	logic.SetGameOver(false);

	logic.SetMaxScore(false);
	logic.SetScore(0);

	logic.SetPlayerProtectionBox(true);

	logic.SetPlayerX((draw.GetBorderX() / 2));
	logic.SetPlayerY((draw.GetBorderY() / 2));

	logic.SetTargetX(logic.RAND(draw.GetBorderX()));
	logic.SetTargetY(logic.RAND(draw.GetBorderY()));
	/// Main game loop
	while (!logic.GetGameOver()) {
		/// Draw
		draw.DrawBorder();
		draw.DrawScore(&logic);
		draw.DrawPlayer(logic);
		draw.DrawTarget(&logic);
		/// Input
		input.InputKeyboard(draw, &logic);
		/// Logic
		logic.LogicPlayerMovement(&draw);
		logic.LogicBorder(draw);
		logic.LogicScore(draw);
	}

	return logic.GameOver(draw, input);
}
