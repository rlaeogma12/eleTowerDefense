/////////


////�޴��� ���� ///

/*
�� �޴��� StartGameView������ ���� �뵵.�Ф� GameView & EditView �� menu.h �� ���ǵȰ� ��.
*/
#include "stdafx.h"
#include "menutitle.h"
#include "Setting.h"

//�޴� ������
Menu::Menu() {
	//�⺻ ������ �� �޴� �׸��� ������ ����.
	isMenuShow = FALSE;

	textcolor_R = 255;
	textcolor_G = 255;
	textcolor_B = 255;
	fontName = _T("Corbel");


	MenuSize.SetRect(0, 0, 0, 0);
	textSize = 0;
	text = _T("�׽�Ʈ �ؽ�Ʈ, Test Text");
}

//�޴� �Ҹ���
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


////Menu ������ ���� ////

//�޴��� ������ ó���� ���ڷ� �޾Ƽ� �����Ҵ��Ѵ�. ó�� ���ڷ� ���� MaxNumber �̻����� �ø��� ����.
//xpos = �޴����� ��ġ�� x��ǥ, ypos = �޴����� ��ġ�� y��ǥ, MaxNumber = �޴��� �ִ� ����, 
//menu_Interval = �޴� ���� ����, font_size = ��Ʈ������, x~y �޴��� ��ü ũ�⸦ ����. �� �޴� ������� �ִ� ũ�⿡ �˸°� ��е� ���̴�.
MenuSet::MenuSet(int x_startpos, int y_startpos, int x_endpos, int y_endpos, int MaxNumber, int menu_Interval, int font_size) {
	menuNum_Max = MaxNumber;
	menuNum = 0;
	CRect MenuRect(x_startpos, y_startpos, x_endpos, y_endpos);
	menuRect = MenuRect;
	menuInterval = menu_Interval;
	fontSize = font_size;
	isShow = FALSE;
	focusedMenu = -1;

	//�� �޴� �׸� �ش��ϴ� �޸𸮸� �̸� �Ҵ��Ѵ�.

	pMenu = new Menu[MaxNumber];
	for (int i = 0; i < MaxNumber; i++) {
		pMenu[i].setMenuRect(x_startpos, y_startpos, x_endpos, y_endpos);
	}

	//�� �޴��� ũ�⸦ ������ ����Ѵ�.
	width = menuRect.right - menuRect.left;
	height = ((menuRect.bottom - menuRect.top) / menuNum_Max) - menuInterval;

	//�⺻ ������ ��ư Ȱ��ȭ TRUE
	isButton = TRUE;
}

MenuSet::~MenuSet() {
	delete[] pMenu;
}

BOOL MenuSet::AddMenu_toLast(int ResourceID, LPCTSTR lpType, CString text) {

	if (menuNum < menuNum_Max) {
		//���ҽ� ID �� �̹��� Ÿ���� �Ű������� ����, �ش� �޴��� ���ʿ� ��ġ�� �̹��� �� Menu�� ����.
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

//ResourceID ���� �ʰ� OveRRiding..
BOOL MenuSet::AddMenu_toLast(CString text) {
	if (menuNum < menuNum_Max) {
		//�ش� �޴��� ���� �� Menu�� ����.
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

//��ư Ȱ��ȭ�� �ݵ��, �޴��� ��������, �װ��� ��ưȭ �Ǿ��־�߸� �����ϴ�.
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

//��Ŀ�� �Ǿ��� ���� �̹����� ����
void MenuSet::setFocusImg(int ResourceID, LPCTSTR lpType) {
	Setting.SetImage(&focusImg, ResourceID, lpType);
}

void MenuSet::setFocus(int menuID) {
	focusedMenu = menuID;
}