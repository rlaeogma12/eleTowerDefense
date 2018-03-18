/////////////////
//menu.h
////////////////

#ifndef MENU_H__
#define MENU_H__

#pragma once

#include "Setting.h"
#include "Utility.h"



class menuSet;

//menu class 선언
class menu
{
private:
	BOOL isUsingResource;		//그림 사용 여부
	BOOL isUsingText;	//글씨 사용 여부
	BOOL isButton;	//버튼화 설정 여부
	BOOL isAlignCenter;	//메뉴 내용을 가운데 정렬할래?
	////-----------------------------------
		
	CPoint menuPos;	//특정 메뉴의 좌상단 좌표

	//각 메뉴의 크기
	int width, height;

	//메뉴에 필요한 CImage(각 메뉴당 최대 1개)
	CImage menuImg;
	int imgWidth, imgHeight;

	//각 메뉴가 가진 text 설정
	Text menuText;

	//이 메뉴의 부모 메뉴 포인터 설정
	menuSet *pParent;



protected:
	Utility DrawUI;


public:
	//각 메뉴의 Index
	int index;

	//메뉴 기본 생성자
	menu();

	//메뉴 소멸자
	~menu();

	//메뉴의 위치 및 크기 결정
	void setMenuPos(int x_pos, int y_pos, int width, int height, menuSet* parentMenu);

	//메뉴 그림 사용, 글씨 사용 버튼화 설정 여부 결정
	void setEachMenuSetting(BOOL haveImg, BOOL haveText, BOOL isBtn);

	//메뉴의 이미지를 결정한다. 결정하지 않을 경우, 디폴트값으로 지정한다. (항상 투명 가능한 PNG만 받을것)
	void setBtnImage(int ResourceID, int _imgWidth, int _imgHeight, BOOL _isAlignCenter);

	//메뉴 항목의 글씨를 설정한다.
	void setMenuText(CString name, int fontSize, CString fontName, int R, int G, int B, BOOL _isAlignCenter = FALSE);
	void setMenuText(CString name);

	//이 메뉴를 그린다.
	void drawMenu(CDC *pDC);

	//메뉴의 위치를 더하거나 빼서 조정한다.
	void calPos(int add_xpos, int add_ypos);

	//메뉴 크기 네모 리턴
	CRect returnMenuRect();	
	CString getMenuText();

	//Index번호 설정
	void setIndex(int _val);

	//해당하는 인덱스 번호가 맞으면 TRUE 반환. 아니면 FALSE
	BOOL isIndex(int x_index, int y_index);

	//이것은 버튼이냐?
	BOOL isBtn();
};

class menuSet
{
private:
	//설정여부---------------
	//토글이 가능한 메뉴입니까
	BOOL isToggleMenu;

	//보여지게 할 것인가?
	BOOL isShown;

	//타이틀 이름을 설정할 것인가?
	BOOL isHaveTitleName;

	//배경 그림을 설정할 것인가?
	BOOL isHaveBackground;

	//마우스로 Focus 된 메뉴의 왼쪽 위치에 > 표시를 할 것인가?
	BOOL isFocusMenu;

	//----------------------------
	Text titleText;	//타이틀 제목 관련 변수


	//메뉴에 들어갈 내용
	CPoint menuSetPos;	//메뉴 집합의 좌상단 좌표

	//메뉴 총 사이즈
	int menuWidth, menuHeight;


	////계산 값------
	//각 메뉴의 사이즈(자동으로 결과값 산출됨, 오버헤드 줄이기 위함)
	int menuEachWidth, menuEachHeight;

	//메뉴[0][0] 기준 좌표값
	int default_xpos, default_ypos;

	////-----------------

	//메뉴 상하, 좌우 여백
	int udInterval, lrInterval;

	//상하, 좌우 메뉴간 간격
	int udmenuInterval, lrmenuInterval;

	//메뉴 제목과 하위 메뉴들 사이의 간격
	int titleInterval;
	int titleHeight;

	//메뉴 배경색
	int bR, bG, bB;

	//메뉴 테두리색
	int bBR, bBG, bBB;

	//각 메뉴의 사이즈를 계산한다.
	void setEachMenuSize();

	//각 메뉴들의 포지션과 사이즈를 결정한다.
	void setMenuPos();

	int edgeLocate;

protected:
	Utility DrawUI;

	vector<vector<menu> > vMenu;	//메뉴 클래스를 담을 공간 할당
	int colNum, rowNum;	//가로 x 세로 개수(기본 1x1)

public:
	//현재 선택된 메뉴를 고른다.
	menu* FocusedMenu;

	menuSet(int _colNum, int _rowNum, int x_pos, int y_pos, int _menuWidth, int _menuHeight, BOOL haveTitle = FALSE, BOOL haveBack = TRUE);
	~menuSet();

	//메뉴 타이틀 이름을 정한다. titleHeight : 타이틀 바의 높이, name : 이름, fontSize : 폰트크기, 폰트명, R,G,B(색상)
	void setMenuTitle(int _titleHeight, CString name, int fontSize = 15, CString fontName = L"Corbel", int R = 0, int G = 220, int B = 200);

	//메뉴 위치를 갱신한다.
	void renewPosition();

	//타이틀 메뉴 및 배경의 설정
	void setTitleBackground(BOOL haveTitle, BOOL haveBack);

	void setMenuSetPos(int x_pos, int y_pos);

	//메뉴판 배경색 설정
	void setBackGround(int _R, int _G, int _B, int _bR = 58, int _bG = 158, int _bB = 57);

	//각 메뉴들의 그림, 글씨, 버튼화 설정 여부를 한번에 결정한다. (개별적으로 변경 가능)
	//haveimg : 메뉴들이 이미지를 가지게 하는가, havetext : 메뉴들이 글씨를 가지는가, isButton : 메뉴들이 클릭이 가능한가.
	void setMenuSetting(BOOL haveImg, BOOL haveText, BOOL isButton);

	//각 메뉴들의 글씨 크기와 폰트, 색상 등을 한번에 결정한다.
	//_text : 입력 메시지. fontSize : 글꼴 크기, fontName : 폰트 이름, R G B : 색상
	void setAllMenuText(CString _text, int fontSize, CString fontName, int R, int G, int B, BOOL isAlignCenter = FALSE);

	//각 메뉴 간 간격을 설정한다. _titleInterval : 제목과 메뉴목록 사이 간격, _udInterval : 상하 간격, _lrInterval : 좌우 여백
	//_udmenuInterval : 상하 메뉴 사이 간격_lrmenuInterval : 좌우 메뉴 사이 간격
	void setMenuInterval(int _titleInterval, int _udInterval, int _lrInterval, int _udmenuInterval, int _lrmenuInterval);

	//메뉴 개별적 설정 시 작성
	//col : 가로 번호, row : 세로 번호
	void setEach(int col, int row, CString _text);
	void setEach(int col, int row, CString _text, int fontSize, CString fontName, int R, int G, int B, BOOL isAlignCenter = FALSE);
	void setEach(int col, int row, int ResourceID, int imgWidth, int imgHeight, BOOL isAlignCenter);
	void setEach(int col, int row, int add_xpos, int add_ypos);

	//토글 메뉴 설정
	void setEdgeLocate(int locateID);
	void setToggle(BOOL ID);
	void setShown(BOOL ID);
	BOOL isStateShown();

	int getColNum();
	int getHeight();

	//마우스의 위치가 메뉴 안에 있는지 확인한다. 있을 경우 TRUE를 반환하고, Focus된 메뉴를 해당 메뉴로 설정한다. 아닐 경우 FALSE 반환.
	BOOL isInMenu(CPoint& MousePos);
	void setFocusMenu(menu &obj);

	//메뉴 전체를 출력한다
	void drawAllMenu(CDC *pDC);
};

//View에서 사용하는 모든 UI를 통합해서 관리하기 위한 클래스.
class ViewUI {
private:
	//MenuSet을 저장할 공간..
	vector<menuSet*> UIArray;

	//포커스된 메뉴셋
	menuSet* focusedMenuSet;

public:
	//생성자
	ViewUI();
	//소멸자
	~ViewUI();

	//UI 리스트 마지막에 추가
	void addMenu(int _colNum, int _rowNum, int x_pos, int y_pos, int _menuWidth, int _menuHeight, BOOL haveTitle = FALSE, BOOL haveBack = TRUE);
	void addMenu(menuSet *objMenuSet);

	//가장 마지막 List 제거
	void deleteMenu();

	//UI 메뉴들의 데이터를 제거한다.
	void deleteAllpMenu();

	//해당하는 View UI 목록을 전부 Traverse해서, 하나라도
	//매개변수로 받은 point를 통해 InRect TRUE 반환 시, TRUE를 반환. else FALSE.
	BOOL isInUI(CPoint point);

	//View에서 모든 Menu UI를 그려낸다.
	void DrawAllViewUI(CDC *pDC);

};

#endif