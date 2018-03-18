#pragma once
#include "MainFrm.h"
#include "Setting.h"

//--------------------------------
//---------Utility.h-------------
//--------------------------------

#ifndef UTILITY_H__
#define UTILITY_H__

class Text;

class Utility
{
private:


public:
	Utility();
	~Utility();

	//Draw 기능 지원(Text, 그림, ...)
	void WriteText(CDC* pDC, CString aa, int x, int y, int width, int height, long size, CString fontname = _T("나눔고딕"), int R = 255, int G = 255, int B = 255, BOOL align = FALSE);
	void WriteText(CDC* pDC, int x_pos, int y_pos, int width, int height, Text text, BOOL align = FALSE);

	void SetImage(CImage *rImage, int ResourceID, LPCTSTR lpType);
	void DrawBack(CDC* pDC, int x_pos, int y_pos, int width, int height, int R, int G, int B, int bR = 54, int bG = 158, int bB = 57, int borderEdge = 10, int borderSize = 5);
	void DrawWordBack(CDC* pDC, int x_pos, int y_pos, int width, int height, int R, int G, int B, int bR = 54, int bG = 158, int bB = 57, int borderEdge = 10, int borderSize = 5, int edgeLocate = 0);

	void DrawEnemy(CDC *pDC, int x_pos, int y_pos, int Enemy_Width, int Enemy_Height, int Bar_Interval, int Bar_xpos, int Bar_ypos, int HP_Width, int HP_Height, int monState = 1, int hR = 255, int hG = 0, int hB = 0);
	void DrawHPBar(CDC *pDC, int& bar_xpos, int& bar_ypos,  int& HP_Width, int& HP_Height, int& hR, int& hG, int& hB);

	void DrawTower(CDC *pDC, CPoint towerPos, int tWidth, int tHeight, CImage *img, int towerAttribute, int towerLv, CRect towerRange, int borderEdge = 3, int borderSize = 4, BOOL isShownRange = FALSE);

	//커서 상태 정의
	CMainFrame* pFrame;
	void SetCursor(int CursorState);
	void SetCursorNormal();
	void SetCursorClick();
	//Cursor State---




	//기능지원 추가함수
protected:
	IStream* CreateStreamOnResource(LPCTSTR lpName, LPCTSTR lpType);
	void Convert_png_transparent(CImage *m_image, LPCTSTR lpType);
};

class Text {

public:
	//텍스트 크기
	int textSize;

	//텍스트 폰트 이름
	CString fontName;

	//텍스트 폰트 색상
	int R, G, B;

	//텍스트에 들어갈 문자열
	CString text;

public:
	//텍스트 설정
	Text();
	Text(CString _text, int _textSize, CString _fontName, int R, int G, int B);

	~Text();

	//텍스트 설정. 오버로딩 오지게 함
	void setText(CString _text, int _textSize, CString _fontName, int _R, int _G, int _B);
	void setText(CString _text);
	void setText(int _textSize);
	void setText(int _R, int _G, int _B);

	//텍스트 불러오기
	CString getText();

	//Debug용 
	void showTextMessage();
};

#endif