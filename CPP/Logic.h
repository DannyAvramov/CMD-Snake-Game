#ifndef LOGIC_H
#define LOGIC_H
#include "Input.h"
// used in main.cpp too
#include <Avramov\console.hpp> // #include "console.hpp"
#include <time.h> 

// I'm lazy
#define RAND(x) Random(2, x, 4)

// const int
#define PLAYER_TAIL_LENGTH(x) (x.GetScore() / 10)
#define PLAYER_TAIL_LENGTH_PTR(x) (x->GetScorePtr() / 10)

class Logic {
public:
	enum Movement {
		Stop = 0,
		Up = 1,
		Down = 2,
		Left = 3,
		Right = 4
	};
private:
	bool m_bGameOverRetry;
	bool m_bGameOverRetryTriggered;
	///
	bool m_bGameOver;
	bool m_bMaxScore;
	short m_iScore;
	bool m_bPlayerProtectionBox;
	unsigned short m_iPlayerX;
	unsigned short m_iPlayerY;
	///
	unsigned short m_iPlayerTailX[100];
	unsigned short m_iPlayerTailY[100];
	unsigned short m_iTargetX;
	unsigned short m_iTargetY;
	///
	Movement input;
public:
	void SetGameOverRetry(const bool);
	bool GetGameOverRetry(void);
	void SetGameOverRetryTriggered(const bool);
	bool GetGameOverRetryTriggered(void);
	///
	void SetGameOver(const bool);
	bool GetGameOver(void) const;
	void SetMaxScore(const bool);
	bool GetMaxScore(void) const;
	void SetScore(const short);
	short GetScore(void) const;
	short &GetScorePtr(void) const;
	void SetPlayerProtectionBox(const bool);
	bool GetPlayerProtectionBox(void) const;
	void SetPlayerX(const unsigned short);
	unsigned short GetPlayerX(void) const;
	void SetPlayerY(const unsigned short);
	unsigned short GetPlayerY(void) const;
	///
	unsigned short GetPlayerTailX(unsigned int) const;
	unsigned short GetPlayerTailY(unsigned int) const;
	void SetTargetX(const unsigned short);
	unsigned short GetTargetX(void) const;
	void SetTargetY(const unsigned short);
	unsigned short GetTargetY(void) const;
	///
	void LogicPlayerMovement(Draw *);
	void LogicBorder(Draw);
	void LogicScore(Draw);
	///
	void Pause(Draw, const Input *);
	short GameOver(Draw, Input);
	unsigned short Random(const unsigned short, const unsigned short, const unsigned short);
	unsigned short RandomColors(void);
	void SetInput(const Movement);
};

#endif
