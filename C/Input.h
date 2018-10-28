#ifndef INPUT_H
#define INPUT_H
#include "Draw.h"
#include "Logic.h"
#define Input enum Movement

const enum Keys {
	W = 119,
	A = 97,
	S = 115,
	D = 100,
	W_CAPS = 87,
	A_CAPS = 65,
	S_CAPS = 83,
	D_CAPS = 68,
	UP_ARROW = 72,
	DOWN_ARROW = 80,
	LEFT_ARROW = 75,
	RIGHT_ARROW = 77,
	SPACE = 32
};

void InputKeyboard(struct Draw, struct Logic, Input *);

#endif
