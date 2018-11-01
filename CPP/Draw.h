#ifndef DRAW_H
#define DRAW_H

class Logic;

class Draw {
private:
	unsigned short m_iBorderX;
	unsigned short m_iBorderY;
	char m_cBorder;
	unsigned short m_iBorderColor;
	char m_cPlayer;
	char m_cPlayerTail;
	unsigned short m_iPlayerColor;
	char m_cTarget;
	unsigned short m_iTargetColor;
	unsigned short m_iScoreTextColor;
	unsigned short m_iScoreNumberColor;
public:
	void SetBorderSize(const unsigned short, const unsigned short);
	unsigned short GetBorderX(void) const;
	unsigned short GetBorderY(void) const;
	void SetBorder(const char);
	void SetBorderColor(const unsigned short);
	void SetPlayer(const char, const char);
	void SetPlayerColor(const unsigned short);
	void SetTarget(const char);
	void SetTargetColor(const unsigned short);
	void SetScoreTextColor(const unsigned short, const unsigned short);
	///
	void DrawBorder(void);
	void DrawScore(Logic *);
	void DrawPlayer(Logic);
	void DrawTarget(Logic *);
};

#endif
