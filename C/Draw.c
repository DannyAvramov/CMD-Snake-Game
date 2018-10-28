#include "Draw.h"
// I'm lazy
#define X (draw.iBorderX / 2)
#define Y (draw.iBorderY / 2)

void DrawBorder(struct Draw draw) {
	Sleep(48);
	clear();
	setColor(draw.iBorderColor);
	for (unsigned short x = 0; x < draw.iBorderX; x++) {
		printf("%c", draw.cBorder);
	}
	printf("\n");
	for (unsigned short x = 0; x < draw.iBorderY; x++) {
		printf("%c", draw.cBorder);
		for (unsigned short y = 0; y < draw.iBorderX - 2; y++) {
			printf(" ");
		};
		printf("%c\n", draw.cBorder);
	}
	for (unsigned short x = 0; x < draw.iBorderX; x++) {
		printf("%c", draw.cBorder);
	}
	return;
}

void DrawScore(struct Draw draw, struct Logic *logic) {
	const char SCORE[] = "SCORE: ";
	unsigned short textWidth = (draw.iBorderX / 2) - (sizeof(SCORE) / 2);
	if (logic->iScore > 9 && logic->iScore < 100) {
		textWidth--;
	}else if (logic->iScore > 99 && logic->iScore < 1000) {
		textWidth = textWidth - 2;
	}else if (logic->iScore >= 1000) {
		if (!logic->bMaxScore) {
			logic->bMaxScore = true;
			logic->iScore = 999;
		};
	}
	placeCursor(textWidth, draw.iBorderY + 4);
	setColor(draw.iScoreTextColor);
	printf("%s", SCORE);
	setColor(draw.iScoreNumberColor);
	printf("%d\n", logic->iScore);
	return;
}

void DrawPlayer(struct Draw *draw, struct Logic logic) {
	if (draw->iPlayerColor == Dark_Red) {
		draw->iPlayerColor = RandomColors();
	}
	placeCursor(logic.iPlayerX, logic.iPlayerY);
	setColor(draw->iPlayerColor);
	printf("%c", draw->cPlayer);
	// Player's tail
	for (unsigned short x = 0; x < PLAYER_TAIL_LENGTH; x++) {
		placeCursor(logic.iPlayerTailX[x], logic.iPlayerTailY[x]);
		printf("%c", draw->cPlayerTail);
	}
	return;
}

void DrawTarget(struct Draw draw, struct Logic *logic) {
	// PlayerProtectionBox is to make sure the target doesn't spawn near the player
	const unsigned short PLAYER_PROTECTION_BOX[81][2] = { // left & right
		{ X - 4, Y - 4 },{ X - 3, Y - 4 },{ X - 2, Y - 4 },{ X - 1, Y - 4 },{ X, Y - 4 },{ X + 1, Y - 4 },{ X + 2, Y - 4 },{ X + 3, Y - 4 },{ X + 4, Y - 4 },

		{ X - 4, Y - 3 },{ X - 3, Y - 3 },{ X - 2, Y - 3 },{ X - 1, Y - 3 },{ X, Y - 3 },{ X + 1, Y - 3 },{ X + 2, Y - 3 },{ X + 3, Y - 3 },{ X + 4, Y - 3 },

		{ X - 4, Y - 2 },{ X - 3, Y - 2 },{ X - 2, Y - 2 },{ X - 1, Y - 2 },{ X, Y - 2 },{ X + 1, Y - 2 },{ X + 2, Y - 2 },{ X + 3, Y - 2 },{ X + 4, Y - 2 },

		{ X - 4, Y - 1 },{ X - 3, Y - 1 },{ X - 2, Y - 1 },{ X - 1, Y - 1 },{ X, Y - 1 },{ X + 1, Y - 1 },{ X + 2, Y - 1 },{ X + 3, Y - 1 },{ X + 4, Y - 1 },

		{ X - 4, Y },{ X - 3, Y },{ X - 2, Y },{ X - 1, Y },{ X, Y },{ X + 1, Y },{ X + 2, Y },{ X + 3, Y },{ X + 4, Y },

		{ X - 4, Y + 1 },{ X - 3, Y + 1 },{ X - 2, Y + 1 },{ X - 1, Y + 1 },{ X, Y + 1 },{ X + 1, Y + 1 },{ X + 2, Y + 1 },{ X + 3, Y + 1 },{ X + 4, Y + 1 },

		{ X - 4, Y + 2 },{ X - 3, Y + 2 },{ X - 2, Y + 2 },{ X - 1, Y + 2 },{ X, Y + 2 },{ X + 1, Y + 2 },{ X + 2, Y + 2 },{ X + 3, Y + 2 },{ X + 4, Y + 2 },

		{ X - 4, Y + 3 },{ X - 3, Y + 3 },{ X - 2, Y + 3 },{ X - 1, Y + 3 },{ X, Y + 3 },{ X + 1, Y + 3 },{ X + 2, Y + 3 },{ X + 3, Y + 3 },{ X + 4, Y + 3 },

		{ X - 4, Y + 4 },{ X - 3, Y + 4 },{ X - 2, Y + 4 },{ X - 1, Y + 4 },{ X, Y + 4 },{ X + 1, Y + 4 },{ X + 2, Y + 4 },{ X + 3, Y + 4 },{ X + 4, Y + 4 }
	};
	if (logic->bPlayerProtectionBox) {
		for (unsigned short x = 0; x < 81; x++) {
			if (PLAYER_PROTECTION_BOX[x][0] == logic->iTargetX && PLAYER_PROTECTION_BOX[x][1] == logic->iTargetY) {
				logic->iTargetX = RAND(draw.iBorderX);
				logic->iTargetY = RAND(draw.iBorderY);
			};
		};
	}
	// Stop the target from spawning on the Player's tail
	for (unsigned short x = 0; x < PLAYER_TAIL_LENGTH_PTR; x++) {
		if (logic->iTargetX == logic->iPlayerTailX[x] && logic->iTargetY == logic->iPlayerTailY[x]) {
			logic->iTargetX = RAND(draw.iBorderX);
			logic->iTargetY = RAND(draw.iBorderY);
		};
	}
	// Draw & places target
	placeCursor(logic->iTargetX, logic->iTargetY);
	setColor(draw.iTargetColor);
	printf("%c", draw.cTarget);
	return;
}
