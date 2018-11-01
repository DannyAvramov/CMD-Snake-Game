#include "Logic.h"
#include <Avramov\console.hpp> // #include "console.hpp"
#include "CallMain.h"

using con::Color;
using con::clear;
using con::setColor;
using con::placeCursor;

void Logic::SetGameOverRetry(const bool GAME_OVER_RETRY) {
	m_bGameOverRetry = GAME_OVER_RETRY;
	return;
}
bool Logic::GetGameOverRetry(void) {
	return m_bGameOverRetry;
}

void Logic::SetGameOverRetryTriggered(const bool GAME_OVER_RETRY_TRIGGERED) {
	m_bGameOverRetryTriggered = GAME_OVER_RETRY_TRIGGERED;
	return;
}

bool Logic::GetGameOverRetryTriggered(void) {
	return m_bGameOverRetryTriggered;
}

void Logic::SetGameOver(const bool GAME_OVER) {
	m_bGameOver = GAME_OVER;
	return;
}

bool Logic::GetGameOver(void) const {
	return m_bGameOver;
}

void Logic::SetMaxScore(const bool MAX_SCORE) {
	m_bMaxScore = MAX_SCORE;
	return;
}

bool Logic::GetMaxScore(void) const {
	return m_bMaxScore;
}

void Logic::SetScore(const short SCORE) {
	m_iScore = SCORE;
	return;
}

short Logic::GetScore(void) const {
	return m_iScore;
}

short &Logic::GetScorePtr(void) const {
	return (short &)m_iScore;
}

void Logic::SetPlayerProtectionBox(const bool PROTECTION) {
	m_bPlayerProtectionBox = PROTECTION;
	return;
}

bool Logic::GetPlayerProtectionBox(void) const {
	return m_bPlayerProtectionBox;
}

void Logic::SetPlayerX(const unsigned short PLAYER_X) {
	m_iPlayerX = PLAYER_X;
	return;
}

unsigned short Logic::GetPlayerX(void) const {
	return m_iPlayerX;
}

void Logic::SetPlayerY(const unsigned short PLAYER_Y) {
	m_iPlayerY = PLAYER_Y;
	return;
}

unsigned short Logic::GetPlayerY(void) const {
	return m_iPlayerY;
}
///
unsigned short Logic::GetPlayerTailX(unsigned int ELEMENT) const {
	return m_iPlayerTailX[ELEMENT];
}

unsigned short Logic::GetPlayerTailY(unsigned int ELEMENT) const {
	return m_iPlayerTailY[ELEMENT];
}

void Logic::SetTargetX(const unsigned short TARGET_X) {
	m_iTargetX = TARGET_X;
	return;
}

unsigned short Logic::GetTargetX(void) const {
	return m_iTargetX;
}

void Logic::SetTargetY(const unsigned short TARGET_Y) {
	m_iTargetY = TARGET_Y;
	return;
}

unsigned short Logic::GetTargetY(void) const {
	return m_iTargetY;
}
///
void Logic::LogicPlayerMovement(Draw *draw) {
	switch (input) {
	case Movement::Up:
		m_iPlayerY--;
		break;
	case Movement::Down:
		m_iPlayerY++;
		break;
	case Movement::Left:
		m_iPlayerX--;
		break;
	case Movement::Right:
		m_iPlayerX++;
		break;
	default:
		break;
	}
	// Player's tail movement
	unsigned short previousPlayerTailX[2], previousPlayerTailY[2];
	// [0] = prev1; [1] = prev2;
	previousPlayerTailX[0] = m_iPlayerTailX[0];
	previousPlayerTailY[0] = m_iPlayerTailY[0];

	m_iPlayerTailX[0] = m_iPlayerX;
	m_iPlayerTailY[0] = m_iPlayerY;
	// Moves the tail away from the head's coordinates so the head appears when moving
	switch (input) {
	case Up:
		m_iPlayerTailY[0] = m_iPlayerY + 1;
		break;
	case Down:
		m_iPlayerTailY[0] = m_iPlayerY - 1;
		break;
	case Left:
		m_iPlayerTailX[0] = m_iPlayerX + 1;
		break;
	case Right:
		m_iPlayerTailX[0] = m_iPlayerX - 1;
		break;
	default:
		break;
	};
	// Makes the tail follow the head in snakey format
	for (unsigned short x = 1; x < (PLAYER_TAIL_LENGTH_PTR(this) + 1); x++) {
		previousPlayerTailX[1] = m_iPlayerTailX[x];
		previousPlayerTailY[1] = m_iPlayerTailY[x];

		m_iPlayerTailX[x] = previousPlayerTailX[0];
		m_iPlayerTailY[x] = previousPlayerTailY[0];

		previousPlayerTailX[0] = previousPlayerTailX[1];
		previousPlayerTailY[0] = previousPlayerTailY[1];
	}
	// Logic for when the head hits the tail
	for (unsigned short x = 0; x < PLAYER_TAIL_LENGTH_PTR(this); x++) {
		if (m_iPlayerX == m_iPlayerTailX[x] && m_iPlayerY == m_iPlayerTailY[x]) {
			Beep(3048, 0010);
			if (m_iScore <= 300) {
				m_iScore = m_iScore - 10;
			}else if (m_iScore > 300 && m_iScore < 600) {
				m_iScore = m_iScore - 50;
			}else if (m_iScore >= 600) {
				m_iScore = m_iScore - 100;
			};
			// Make snake turn red for color changing
			draw->SetPlayerColor(Color::Dark_Red);
		};
	}
	return;
}

void Logic::LogicBorder(Draw draw) {
	if (/*Top Border & Left Border*/ m_iPlayerY == 0 || m_iPlayerX == 0 || /*Bottom Border & Right Border*/ m_iPlayerY == (draw.GetBorderY() + 1) || m_iPlayerX == (draw.GetBorderX() - 1)) {
		if (m_iScore <= 300) {
			m_iScore = (m_iScore - 50);
		}else if (m_iScore > 300 && m_iScore < 600) {
			m_iScore = (m_iScore - 100);
		}else if (m_iScore >= 600) {
			m_iScore = (m_iScore - 150);
		};
		// Sets Player to middle of screen after hitting border
		m_iPlayerX = (draw.GetBorderX() / 2);
		m_iPlayerY = (draw.GetBorderY() / 2);
		// Makes the Player's tail not delayed when teleported
		for (unsigned short x = 0; x < PLAYER_TAIL_LENGTH_PTR(this); x++) {
			m_iPlayerTailX[x] = m_iPlayerX;
			m_iPlayerTailY[x] = m_iPlayerY;
		};
	}
	return;
}

void Logic::LogicScore(Draw draw) {
	if (m_iScore < 0) {
		Beep(60, 0600);
		m_bGameOver = true;
	}else if (m_iPlayerX == m_iTargetX && m_iPlayerY == m_iTargetY) {
		if (!m_bMaxScore) {
			Beep(1096, 0010);
			if (m_iScore < 300) {
				m_iScore = (m_iScore + 50);
			}else if (m_iScore > 300 && m_iScore < 600) {
				m_iScore = (m_iScore + 100);
			}else if (m_iScore > 600) {
				m_iScore = (m_iScore + 150);
			};
		};
		m_iTargetX = RAND(draw.GetBorderX());
		m_iTargetY = RAND(draw.GetBorderY());
	}
	return;
}
///
void Logic::Pause(Draw draw, const Input *input) {
	clear();
	const char PAUSE[] = "  PAUSED";
	placeCursor((draw.GetBorderX() / 2) - sizeof(PAUSE) / 2, draw.GetBorderY() - 11);
	setColor(Color::White);
	printf("%s\n", PAUSE);
	switch (_getch()) {
	case Input::Keys::SPACE:
		break;
	case 27: // ESC key
		exit(EXIT_SUCCESS);
		break;
	default:
		Pause(draw, input);
		break;
	}
	return;
}

short Logic::GameOver(Draw draw,  Input input) {
	clear();
	setColor(Color::White);
	placeCursor((draw.GetBorderX() / 2) - 4, (draw.GetBorderY() / 2) - 2);
	puts("GAME OVER");
	placeCursor((draw.GetBorderX() / 2) - 2, (draw.GetBorderY() / 2) + 2);
	puts("RETRY");
	placeCursor((draw.GetBorderX() / 2) - 9, (draw.GetBorderY() / 2) + 6);
	if (!GetGameOverRetry() && GetGameOverRetryTriggered()) { // No
		printf("[YES]         ");
		setColor(Color::Red);
		printf("[NO]");
	}else if (GetGameOverRetry() && GetGameOverRetryTriggered()) { // Yes
		setColor(Color::Red);
		printf("[YES]");
		setColor(Color::White);
		printf("         [NO]");
	}else if (!GetGameOverRetryTriggered()) {
		printf("[YES]         [NO]");
	}
	switch (_getch()) {
	case 110: // N
	case input.Keys::D:
	case input.Keys::D_CAPS:
	case input.Keys::RIGHT_ARROW:
		SetGameOverRetryTriggered(true);
		SetGameOverRetry(false);
		break;
	case 121: // Y
	case input.Keys::A:
	case input.Keys::A_CAPS:
	case input.Keys::LEFT_ARROW:
		SetGameOverRetryTriggered(true);
		SetGameOverRetry(true);
		break;
	case input.Keys::SPACE:
	case 13: // Enter
		if (GetGameOverRetry()) {
			return main(NULL, NULL);
		}else if (!GetGameOverRetry() && GetGameOverRetryTriggered()) {
			return 0;
		};
		break;
	default:
		break;
	}
	return GameOver(draw, input);
}

unsigned short Logic::Random(const unsigned short LOW, const unsigned short BUFFER, const unsigned short HIGH) {
	return (LOW + (rand() % (BUFFER - HIGH)));
}

unsigned short Logic::RandomColors(void) {
	switch ((1 + (rand() % 12))) {
	case 1:
		return Color::Blue;
		break;
	case 2:
		return Color::Green;
		break;
	case 3:
		return Color::Turquise;
		break;
	case 4:
		return Color::Red;
		break;
	case 5:
		return Color::Purple;
		break;
	case 6:
		return Color::Yellow;
		break;
	case 7:
		return Color::Dark_Blue;
		break;
	case 8:
		return Color::Dark_Green;
		break;
	case 9:
		return Color::Dark_Turquise;
		break;
	case 10:
		return Color::Dark_Red;
		break;
	case 11:
		return Color::Dark_Purple;
		break;
	case 12:
		return Color::Dark_Yellow;
		break;
	default:
		break;
	}
	return 0;
}

void Logic::SetInput(const Movement INPUT) {
	input = INPUT;
	return;
}
