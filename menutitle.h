#ifndef MENUTITLE_H__
#define MENUTITLE_H__

#pragma once
/////////////////
//menutitle.h
/////////////////


#include "Utility.h"

class MenuSet;

//title Menu에서만 사용합니다.

class Menu
{
private:
	//각 메뉴 항목을 보이게 할 것인지?
	BOOL isMenuShow;

	CRect MenuSize;
	CImage img;
	CString text;
	int textSize;

	int textcolor_R, textcolor_G, textcolor_B;
	CString fontName;

public:
	Menu();
	~Menu();

	//메뉴크기, 이미지, 텍스트 사이즈, 문자열 set
	void setMenuRect(int start_x, int start_y, int end_x, int end_y);
	void setMenuRect(CRect rect);
	void setImage(int ResourceID, LPCTSTR lpType);
	void setString(CString txt);
	void setTextSize(int fontSize);
	void setFontName(CString fontName);
	void setFontColor(int r, int g, int b);

	void ShowMenu(BOOL ID);
	void HideMenu(BOOL ID);

	Utility Setting;

public:

	//메뉴를 실제로 DC를 얻어서 출력한다.
	void PrintMenu(CDC* pDC);

	//메뉴의 Rect를 반환한다.(마우스 활용을 위함)
	CRect getRect();
};


//메뉴셋 Class 정의.
class MenuSet
{
private:
	//메뉴가 실제로 활성화 될 것인지.
	BOOL isShow;

	//메뉴 목록 헤드 포인터.
	Menu* pMenu;

	//메뉴 사이사이의 간격
	int menuInterval;

	//메뉴판 전체의 크기
	CRect menuRect;

	//각 메뉴의 글씨 크기를 결정
	int fontSize;

	//최대 메뉴 개수
	int menuNum_Max;

	//현재 활성화된 메뉴의 개수 처음 생성 시 0개로 초기화.
	int menuNum;

	//각 메뉴의 사이즈를 담는 변수
	int width, height;

	//클릭이 가능하다면, 현재 focused 된 menu는 어떤것인지.
	int focusedMenu;

	//focus Menu를 표시해주기 위한 Resouce CImage
	CImage focusImg;

protected:
	//각 메뉴를 클릭할 수 있게 할 것인지?
	BOOL isButton;

public:
	//메뉴의 개수를 처음에 인자로 받아서 동적할당한다. 처음 인자로 받은 MaxNumber 이상으로 늘릴수 없다.
	MenuSet(int x_startpos, int y_startpos, int x_endpos, int y_endpos, int MaxNumber, int menu_Interval, int font_size);
	~MenuSet();

	Utility Setting;
	//메뉴를 마지막에 추가
	BOOL AddMenu_toLast(int ResourceID, LPCTSTR lpType, CString text);
	BOOL AddMenu_toLast(CString text);

	//마지막 메뉴를 삭제.
	BOOL DeleteMenu_toLast();

	//메뉴 보이기
	void ShowMenuList();
	void HideMenuList();

	//메뉴가 보임 상태인지 BOOL 로 반환. 보인다(TRUE) : 안보인다(FALSE).
	BOOL isShowVaild();

	//메뉴 리스트를 실제로 DC를 얻어서 출력한다.
	void PrintMenuList(CDC* pDC);

	//메뉴 버튼화 셋팅
	void SetMenuBtn(BOOL ID);

	//focus된 메뉴 셋
	void setFocus(int menuID);

	//해당하는 메뉴를 불러온다.
	Menu* getMenu();

	//입력받은 Point가 어떤 Menu의 Rect에 위치하는 지 반환. -1은 없음을 의미.
	int PointOverMenu(POINT point);

	//focused Icon Set
	void setFocusImg(int ResourceID, LPCTSTR lpType);
};

#endif