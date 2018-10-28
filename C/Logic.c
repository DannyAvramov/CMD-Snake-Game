#include "Logic.h"

void LogicPlayerMovement(struct Draw *draw, struct Logic *logic, enum Movement input) {
	switch (input) {
	case Up:
		logic->iPlayerY--;
		break;
	case Down:
		logic->iPlayerY++;
		break;
	case Left:
		logic->iPlayerX--;
		break;
	case Right:
		logic->iPlayerX++;
		break;
	default:
		break;
	}
	// Player's tail movement
	unsigned short previousPlayerTailX[2], previousPlayerTailY[2];
	// [0] = prev1; [1] = prev2;
	previousPlayerTailX[0] = logic->iPlayerTailX[0];
	previousPlayerTailY[0] = logic->iPlayerTailY[0];

	logic->iPlayerTailX[0] = logic->iPlayerX;
	logic->iPlayerTailY[0] = logic->iPlayerY;
	// Moves the tail away from the head's coordinates so the head appears when moving
	switch (input) {
	case Up:
		logic->iPlayerTailY[0] = logic->iPlayerY + 1;
		break;
	case Down:
		logic->iPlayerTailY[0] = logic->iPlayerY - 1;
		break;
	case Left:
		logic->iPlayerTailX[0] = logic->iPlayerX + 1;
		break;
	case Right:
		logic->iPlayerTailX[0] = logic->iPlayerX - 1;
		break;
	default:
		break;
	};
	// Makes the tail follow the head in snakey format
	for (unsigned short x = 1; x < (PLAYER_TAIL_LENGTH_PTR + 1); x++) {
		previousPlayerTailX[1] = logic->iPlayerTailX[x];
		previousPlayerTailY[1] = logic->iPlayerTailY[x];

		logic->iPlayerTailX[x] = previousPlayerTailX[0];
		logic->iPlayerTailY[x] = previousPlayerTailY[0];

		previousPlayerTailX[0] = previousPlayerTailX[1];
		previousPlayerTailY[0] = previousPlayerTailY[1];
	}
	// Logic for when the head hits the tail
	for (unsigned short x = 0; x < PLAYER_TAIL_LENGTH_PTR; x++) {
		if (logic->iPlayerX == logic->iPlayerTailX[x] && logic->iPlayerY == logic->iPlayerTailY[x]) {
			Beep(3048, 0010);
			if (logic->iScore <= 300) {
				logic->iScore = logic->iScore - 10;
			}else if (logic->iScore > 300 && logic->iScore < 600) {
				logic->iScore = logic->iScore - 50;
			}else if (logic->iScore >= 600) {
				logic->iScore = logic->iScore - 100;
			};
			// Make snake turn red for color changing
			draw->iPlayerColor = Dark_Red;
		};
	}
	return;
}

void LogicBorder(struct Draw draw, struct Logic *logic) {
	if (/*Top Border & Left Border*/ logic->iPlayerY == 0 || logic->iPlayerX == 0 || /*Bottom Border & Right Border*/ logic->iPlayerY == (draw.iBorderY + 1) || logic->iPlayerX == (draw.iBorderX - 1)) {
		if (logic->iScore <= 300) {
			logic->iScore = (logic->iScore - 50);
		}else if (logic->iScore > 300 && logic->iScore < 600) {
			logic->iScore = (logic->iScore - 100);
		}else if (logic->iScore >= 600) {
			logic->iScore = (logic->iScore - 150);
		};
		// Sets Player to middle of screen after hitting border
		logic->iPlayerX = (draw.iBorderX / 2);
		logic->iPlayerY = (draw.iBorderY / 2);
		// Makes the Player's tail not delayed when teleported
		for (unsigned short x = 0; x < PLAYER_TAIL_LENGTH_PTR; x++) {
			logic->iPlayerTailX[x] = logic->iPlayerX;
			logic->iPlayerTailY[x] = logic->iPlayerY;
		};
	}
	return;
}

void LogicScore(struct Draw draw, struct Logic *logic) {
	if (logic->iScore < 0) {
		Beep(60, 0600);
		logic->bGameOver = true;
	}else if (logic->iPlayerX == logic->iTargetX && logic->iPlayerY == logic->iTargetY) {
		if (!logic->bMaxScore) {
			Beep(1096, 0010);
			if (logic->iScore < 300) {
				logic->iScore = (logic->iScore + 50);
			}else if (logic->iScore > 300 && logic->iScore < 600) {
				logic->iScore = (logic->iScore + 100);
			}else if (logic->iScore > 600) {
				logic->iScore = (logic->iScore + 150);
			}else {
			
			};
		};
		logic->iTargetX = RAND(draw.iBorderX);
		logic->iTargetY = RAND(draw.iBorderY);
	}
	return;
}
///
void Pause(struct Draw draw) {
	clear();
	const char PAUSE[] = "  PAUSED";
	placeCursor((draw.iBorderX / 2) - sizeof(PAUSE) / 2, draw.iBorderY - 11);
	setColor(White);
	printf("%s\n", PAUSE);
	switch (_getch()) {
	case SPACE:
		break;
	case 27: // ESC key
		exit(EXIT_SUCCESS);
		break;
	default:
		Pause(draw);
		break;
	}
	return;
}

short GameOver(struct Draw draw) {
	clear();
	setColor(White);
	placeCursor((draw.iBorderX / 2) - 4, (draw.iBorderY / 2) - 2);
	puts("GAME OVER");
	placeCursor((draw.iBorderX / 2) - 2, (draw.iBorderY / 2) + 2);
	puts("RETRY");
	placeCursor((draw.iBorderX / 2) - 9, (draw.iBorderY / 2) + 6);
	if (!logicGO.bGameOverRetry && logicGO.bGameOverRetryTriggered) { // No
		printf("[YES]         ");
		setColor(Red);
		printf("[NO]");
	}else if (logicGO.bGameOverRetry && logicGO.bGameOverRetryTriggered) { // Yes
		setColor(Red);
		printf("[YES]");
		setColor(White);
		printf("         [NO]");
	}else if (!logicGO.bGameOverRetryTriggered) {
		printf("[YES]         [NO]");
	}
	switch (_getch()) {
	case 110: // N
	case D:
	case D_CAPS:
	case RIGHT_ARROW:
		logicGO.bGameOverRetryTriggered = true;
		logicGO.bGameOverRetry = false;
		break;
	case 121: // Y
	case A:
	case A_CAPS:
	case LEFT_ARROW:
		logicGO.bGameOverRetryTriggered = true;
		logicGO.bGameOverRetry = true;
		break;
	case SPACE:
	case 13: // Enter
		if (logicGO.bGameOverRetry) {
			extern main();
			return main();
		}else if (!logicGO.bGameOverRetry && logicGO.bGameOverRetryTriggered) {
			return 0;
		};
		break;
	default:
		break;
	}
	return GameOver(draw);
}

unsigned short Random(const unsigned short LOW, const unsigned short BUFFER, const unsigned short HIGH) {
	return (LOW + (rand() % (BUFFER - HIGH)));
}

unsigned short RandomColors(void) {
	switch ((1 + (rand() % 12))) {
	case 1:
		return Blue;
		break;
	case 2:
		return Green;
		break;
	case 3:
		return Turquise;
		break;
	case 4:
		return Red;
		break;
	case 5:
		return Purple;
		break;
	case 6:
		return Yellow;
		break;
	case 7:
		return Dark_Blue;
		break;
	case 8:
		return Dark_Green;
		break;
	case 9:
		return Dark_Turquise;
		break;
	case 10:
		return Dark_Red;
		break;
	case 11:
		return Dark_Purple;
		break;
	case 12:
		return Dark_Yellow;
		break;
	default:
		break;
	}
	return 0;
}
