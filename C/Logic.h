#ifndef LOGIC_H
#define LOGIC_H
#include "Draw.h"
#include "Input.h"
#include "console.h"
#include <time.h>
// I'm lazy
#define RAND(x) Random(2, x, 4)
// const int
#define PLAYER_TAIL_LENGTH (logic.iScore / 10)
#define PLAYER_TAIL_LENGTH_PTR (logic->iScore / 10)

struct Logic {
	bool bGameOver;
	bool bMaxScore;
	short iScore;
	bool bPlayerProtectionBox;
	unsigned short iPlayerX;
	unsigned short iPlayerY;
	///
	unsigned short iPlayerTailX[100];
	unsigned short iPlayerTailY[100];
	unsigned short iTargetX;
	unsigned short iTargetY;
};

struct LogicGameOver {
	bool bGameOverRetry;
	bool bGameOverRetryTriggered;
}logicGO;

enum Movement {
	Stop = 0,
	Up = 1,
	Down = 2,
	Left = 3,
	Right = 4
};

void LogicPlayerMovement(struct Draw *, struct Logic *, enum Movement);

void LogicBorder(struct Draw, struct Logic *);

void LogicScore(struct Draw, struct Logic *);
///
void Pause(struct Draw);

short GameOver(struct Draw);

unsigned short Random(const unsigned short, const unsigned short, const unsigned short);

unsigned short RandomColors(void);

#endif
