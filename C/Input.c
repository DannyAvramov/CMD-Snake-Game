#include "Input.h"

void InputKeyboard(struct Draw draw, struct Logic logic, Input *input) {
	if (_kbhit()) {
		if (logic.bPlayerProtectionBox) {
			logic.bPlayerProtectionBox = false;
		};
		switch (_getch()) {
		case W:
		case W_CAPS:
		case UP_ARROW:
			*input = Up;
			break;
		case A:
		case A_CAPS:
		case LEFT_ARROW:
			*input = Left;
			break;
		case S:
		case S_CAPS:
		case DOWN_ARROW:
			*input = Down;
			break;
		case D:
		case D_CAPS:
		case RIGHT_ARROW:
			*input = Right;
			break;
		case SPACE:
			Pause(draw);
			break;
		default:
			break;
		};
	}
	return;
}
