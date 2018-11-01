#include "Draw.h"
#include "Logic.h"

// I'm lazy
#define X (m_iBorderX / 2)
#define Y (m_iBorderY / 2)

using namespace con;
using std::cout;
using std::endl;

void Draw::SetBorderSize(const unsigned short BORDER_X, const unsigned short BORDER_Y) {
	m_iBorderX = BORDER_X;
	m_iBorderY = BORDER_Y;
	return;
}

unsigned short Draw::GetBorderX(void) const {
	return m_iBorderX;
}

unsigned short Draw::GetBorderY(void) const {
	return m_iBorderY;
}

void Draw::SetBorder(const char BORDER_CHAR) {
	m_cBorder = BORDER_CHAR;
	return;
}

void Draw::SetBorderColor(const unsigned short BORDER_COLOR) {
	m_iBorderColor = BORDER_COLOR;
	return;
}

void Draw::SetPlayer(const char PLAYER_CHAR, const char TAIL_CHAR) {
	m_cPlayer = PLAYER_CHAR;
	m_cPlayerTail = TAIL_CHAR;
	return;
}

void Draw::SetPlayerColor(const unsigned short PLAYER_COLOR) {
	m_iPlayerColor = PLAYER_COLOR;
	return;
}

void Draw::SetTarget(const char TARGET_CHAR) {
	m_cTarget = TARGET_CHAR;
	return;
}

void Draw::SetTargetColor(const unsigned short TARGET_COLOR) {
	m_iTargetColor = TARGET_COLOR;
	return;
}

void Draw::SetScoreTextColor(const unsigned short TEXT_COLOR, const unsigned short NUMBER_COLOR) {
	m_iScoreTextColor = TEXT_COLOR;
	m_iScoreNumberColor = NUMBER_COLOR;
	return;
}
///
void Draw::DrawBorder(void) {
	Sleep(48);
	clear();
	setColor(m_iBorderColor);
	for (unsigned short x = 0; x < m_iBorderX; x++) {
		cout << m_cBorder;
	}
	cout << endl;
	for (unsigned short x = 0; x < m_iBorderY; x++) {
		cout << m_cBorder;
		for (unsigned short y = 0; y < m_iBorderX - 2; y++) {
			cout << " ";
		};
		cout << m_cBorder << endl;
	}
	for (unsigned short x = 0; x < m_iBorderX; x++) {
		cout << m_cBorder;
	}
	return;
}

void Draw::DrawScore(Logic *logic) {
	const std::string SCORE = "SCORE: ";
	unsigned short textWidth = (m_iBorderX / 2) - ((USHORT)SCORE.size() / 2);
	if (logic->GetScore() > 9 && logic->GetScore() < 100) {
		textWidth--;
	}else if (logic->GetScore() > 99 && logic->GetScore() < 1000) {
		textWidth = textWidth - 2;
	}else if (logic->GetScore() >= 1000) {
		if (!logic->GetMaxScore()) {
			logic->SetMaxScore(true);
			logic->SetScore(999);
		};
	}
	placeCursor(textWidth, m_iBorderY + 4);
	setColor(m_iScoreTextColor);
	cout << SCORE.c_str();
	setColor(m_iScoreNumberColor);
	cout << logic->GetScore() << endl;
	return;
}

void Draw::DrawPlayer(Logic logic) {
	if (m_iPlayerColor == Dark_Red) {
		m_iPlayerColor = logic.RandomColors();
	}
	placeCursor(logic.GetPlayerX(), logic.GetPlayerY());
	setColor(m_iPlayerColor);
	cout << m_cPlayer;
	// Player's tail
	for (unsigned short x = 0; x < PLAYER_TAIL_LENGTH(logic); x++) {
		placeCursor(logic.GetPlayerTailX(x), logic.GetPlayerTailY(x));
		cout << m_cPlayerTail;
	}
	return;
}

void Draw::DrawTarget(Logic *logic) {
	// PlayerProtectionBox is to make sure the target doesn't spawn near the player
	const int PLAYER_PROTECTION_BOX[81][2] = { // left & right
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
	if (logic->GetPlayerProtectionBox()) {
		for (unsigned short x = 0; x < 81; x++) {
			if (PLAYER_PROTECTION_BOX[x][0] == logic->GetTargetX() && PLAYER_PROTECTION_BOX[x][1] == logic->GetTargetY()) {
				logic->SetTargetX(logic->RAND(m_iBorderX));
				logic->SetTargetY(logic->RAND(m_iBorderY));
			};
		};
	}
	// Stop the target from spawning on the Player's tail
	for (unsigned short x = 0; x < PLAYER_TAIL_LENGTH_PTR(logic); x++) {
		if (logic->GetTargetX() == logic->GetPlayerTailX(x) && logic->GetTargetY() == logic->GetPlayerTailY(x)) {
			logic->SetTargetX(logic->RAND(m_iBorderX));
			logic->SetTargetY(logic->RAND(m_iBorderY));
		};
	}
	// Draw & places target
	placeCursor(logic->GetTargetX(), logic->GetTargetY());
	setColor(m_iTargetColor);
	cout << m_cTarget;
	return;
}
