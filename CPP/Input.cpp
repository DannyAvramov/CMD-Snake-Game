#include "Input.h"
#include "Logic.h"

void Input::InputKeyboard(Draw draw, Logic *logic) {
	if (_kbhit()) {
		if (logic->GetPlayerProtectionBox()) {
			logic->SetPlayerProtectionBox(false);
		};
		switch (_getch()) {
		case W:
		case W_CAPS:
		case UP_ARROW:
			logic->SetInput(Logic::Movement::Up);
			break;
		case A:
		case A_CAPS:
		case LEFT_ARROW:
			logic->SetInput(Logic::Movement::Left);
			break;
		case S:
		case S_CAPS:
		case DOWN_ARROW:
			logic->SetInput(Logic::Movement::Down);
			break;
		case D:
		case D_CAPS:
		case RIGHT_ARROW:
			logic->SetInput(Logic::Movement::Right);
			break;
		case SPACE:
			logic->Pause(draw, this);
			break;
		default:
			break;
		};
	}
	return;
}
