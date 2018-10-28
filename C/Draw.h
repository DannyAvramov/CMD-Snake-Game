#ifndef DRAW_H
#define DRAW_H
#include "Logic.h"

struct Draw {
	unsigned short iBorderX;
	unsigned short iBorderY;
	char cBorder;
	unsigned short iBorderColor;
	char cPlayer;
	char cPlayerTail;
	unsigned short iPlayerColor;
	char cTarget;
	unsigned short iTargetColor;
	unsigned short iScoreTextColor;
	unsigned short iScoreNumberColor;
};

void DrawBorder(struct Draw);

void DrawScore(struct Draw, struct Logic *);

void DrawPlayer(struct Draw *, struct Logic);

void DrawTarget(struct Draw, struct Logic *);

#endif
