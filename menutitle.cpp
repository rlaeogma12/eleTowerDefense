/////////


////메뉴를 정의 ///

/*
이 메뉴는 StartGameView에서만 쓰는 용도.ㅠㅠ GameView & EditView 는 menu.h 에 정의된걸 씀.
*/
#include "stdafx.h"
#include "menutitle.h"
#include "Setting.h"

//메뉴 생성자
Menu::Menu() {
	//기본 생성시 각 메뉴 항목은 보이지 않음.
	isMenuShow = FALSE;

	textcolor_R = 255;
	textcolor_G = 255;
	textcolor_B = 255;
	fontName = _T("Corbel");


	MenuSize.SetRect(0, 0, 0, 0);
	textSize = 0;
	text = _T("테스트 텍스트, Test Text");
}

//메뉴 소멸자
Menu::~Menu() {

}

void Menu::setMenuRect(int start_x, int start_y, int end_x, int end_y) {
	MenuSize.SetRect(start_x, start_y, end_x, end_y);
}

void Menu::setMenuRect(CRect rect) {
	MenuSize = rect;
}

void Menu::setImage(int ResourceID, LPCTSTR lpType) {
	Setting.SetImage(&img, ResourceID, lpType);
}

void Menu::setString(CString txt) {
	text = txt;
}

void Menu::setTextSize(int fontSize) {
	textSize = fontSize;
}

void Menu::ShowMenu(BOOL ID) {
	isMenuShow = TRUE;
}

void Menu::HideMenu(BOOL ID) {
	isMenuShow = FALSE;
}

void Menu::PrintMenu(CDC* pDC) {
	if (isMenuShow) {
		if (img) { img.Draw(pDC->m_hDC, MenuSize.left, MenuSize.top, 64, 64); }
		Setting.WriteText(pDC, text, MenuSize.left + 80, MenuSize.top, MenuSize.right - MenuSize.left, MenuSize.bottom - MenuSize.top, textSize, fontName, textcolor_R, textcolor_G, textcolor_B);
	}
}

void Menu::setFontName(CString fontName) {
	this->fontName = fontName;
}
void Menu::setFontColor(int r, int g, int b) {
	textcolor_R = r;
	textcolor_G = g;
	textcolor_B = b;
}

CRect Menu::getRect() {
	return MenuSize;
}


////Menu 집합을 정의 ////

//메뉴의 개수를 처음에 인자로 받아서 동적할당한다. 처음 인자로 받은 MaxNumber 이상으로 늘릴수 없다.
//xpos = 메뉴셋이 위치할 x좌표, ypos = 메뉴셋이 위치할 y좌표, MaxNumber = 메뉴의 최대 개수, 
//menu_Interval = 메뉴 사이 간격, font_size = 폰트사이즈, x~y 메뉴판 전체 크기를 정의. 각 메뉴 사이즈는 최대 크기에 알맞게 배분될 것이다.
MenuSet::MenuSet(int x_startpos, int y_startpos, int x_endpos, int y_endpos, int MaxNumber, int menu_Interval, int font_size) {
	menuNum_Max = MaxNumber;
	menuNum = 0;
	CRect MenuRect(x_startpos, y_startpos, x_endpos, y_endpos);
	menuRect = MenuRect;
	menuInterval = menu_Interval;
	fontSize = font_size;
	isShow = FALSE;
	focusedMenu = -1;

	//각 메뉴 항목에 해당하는 메모리를 미리 할당한다.

	pMenu = new Menu[MaxNumber];
	for (int i = 0; i < MaxNumber; i++) {
		pMenu[i].setMenuRect(x_startpos, y_startpos, x_endpos, y_endpos);
	}

	//각 메뉴의 크기를 적당히 배분한다.
	width = menuRect.right - menuRect.left;
	height = ((menuRect.bottom - menuRect.top) / menuNum_Max) - menuInterval;

	//기본 생성시 버튼 활성화 TRUE
	isButton = TRUE;
}

MenuSet::~MenuSet() {
	delete[] pMenu;
}

BOOL MenuSet::AddMenu_toLast(int ResourceID, LPCTSTR lpType, CString text) {

	if (menuNum < menuNum_Max) {
		//리소스 ID 및 이미지 타입을 매개변수로 전달, 해당 메뉴의 왼쪽에 위치할 이미지 등 Menu의 셋팅.
		pMenu[menuNum].setImage(ResourceID, lpType);
		pMenu[menuNum].setMenuRect(menuRect.left, menuRect.top + menuNum*height + menuInterval, menuRect.left + width, menuRect.top + (menuNum + 1)*height);
		pMenu[menuNum].setString(text);
		pMenu[menuNum].setTextSize(fontSize);
		pMenu[menuNum].ShowMenu(TRUE);

		menuNum++;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

//ResourceID 받지 않고 OveRRiding..
BOOL MenuSet::AddMenu_toLast(CString text) {
	if (menuNum < menuNum_Max) {
		//해당 메뉴의 글자 등 Menu의 셋팅.
		pMenu[menuNum].setMenuRect(menuRect.left, menuRect.top + menuNum*height + menuInterval, menuRect.left + width, menuRect.top + (menuNum + 1)*height);
		pMenu[menuNum].setString(text);
		pMenu[menuNum].setTextSize(fontSize);
		pMenu[menuNum].ShowMenu(TRUE);

		menuNum++;
		return TRUE;
	}
	else {
		return FALSE;
	}

}

BOOL MenuSet::DeleteMenu_toLast() {
	if (menuNum > 0) {
		pMenu[menuNum].ShowMenu(FALSE);
		menuNum--;
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void MenuSet::ShowMenuList() {
	isShow = TRUE;
	focusedMenu = 0;
}

void MenuSet::HideMenuList() { isShow = FALSE; }

void MenuSet::PrintMenuList(CDC* pDC) {
	if (isShow) {
		for (int i = 0; i < menuNum; i++) {
			pMenu[i].PrintMenu(pDC);
		}
		if (focusImg) { focusImg.Draw(pDC->m_hDC, menuRect.left - 70, menuRect.top + 8 + focusedMenu*height, 64, 64); }
	}
}

BOOL MenuSet::isShowVaild() {
	if (isShow) {
		if (menuNum > 0) { focusedMenu = 0; }
		return TRUE;
	}
	else {
		return FALSE;
	}
}

void MenuSet::SetMenuBtn(BOOL ID) { isButton = ID; }

Menu* MenuSet::getMenu() {
	return pMenu;
}

//버튼 활성화는 반드시, 메뉴가 보여지고, 그것이 버튼화 되어있어야만 가능하다.
int MenuSet::PointOverMenu(POINT point) {
	if (isShow && isButton) {
		for (int i = 0; i < menuNum; i++) {
			if ((pMenu[i].getRect()).PtInRect(point)) {
				return i;
			}
		}
	}
	return -1;
}

//포커스 되었을 때의 이미지를 설정
void MenuSet::setFocusImg(int ResourceID, LPCTSTR lpType) {
	Setting.SetImage(&focusImg, ResourceID, lpType);
}

void MenuSet::setFocus(int menuID) {
	focusedMenu = menuID;
}