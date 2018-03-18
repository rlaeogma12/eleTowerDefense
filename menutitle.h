#ifndef MENUTITLE_H__
#define MENUTITLE_H__

#pragma once
/////////////////
//menutitle.h
/////////////////


#include "Utility.h"

class MenuSet;

//title Menu������ ����մϴ�.

class Menu
{
private:
	//�� �޴� �׸��� ���̰� �� ������?
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

	//�޴�ũ��, �̹���, �ؽ�Ʈ ������, ���ڿ� set
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

	//�޴��� ������ DC�� �� ����Ѵ�.
	void PrintMenu(CDC* pDC);

	//�޴��� Rect�� ��ȯ�Ѵ�.(���콺 Ȱ���� ����)
	CRect getRect();
};


//�޴��� Class ����.
class MenuSet
{
private:
	//�޴��� ������ Ȱ��ȭ �� ������.
	BOOL isShow;

	//�޴� ��� ��� ������.
	Menu* pMenu;

	//�޴� ���̻����� ����
	int menuInterval;

	//�޴��� ��ü�� ũ��
	CRect menuRect;

	//�� �޴��� �۾� ũ�⸦ ����
	int fontSize;

	//�ִ� �޴� ����
	int menuNum_Max;

	//���� Ȱ��ȭ�� �޴��� ���� ó�� ���� �� 0���� �ʱ�ȭ.
	int menuNum;

	//�� �޴��� ����� ��� ����
	int width, height;

	//Ŭ���� �����ϴٸ�, ���� focused �� menu�� �������.
	int focusedMenu;

	//focus Menu�� ǥ�����ֱ� ���� Resouce CImage
	CImage focusImg;

protected:
	//�� �޴��� Ŭ���� �� �ְ� �� ������?
	BOOL isButton;

public:
	//�޴��� ������ ó���� ���ڷ� �޾Ƽ� �����Ҵ��Ѵ�. ó�� ���ڷ� ���� MaxNumber �̻����� �ø��� ����.
	MenuSet(int x_startpos, int y_startpos, int x_endpos, int y_endpos, int MaxNumber, int menu_Interval, int font_size);
	~MenuSet();

	Utility Setting;
	//�޴��� �������� �߰�
	BOOL AddMenu_toLast(int ResourceID, LPCTSTR lpType, CString text);
	BOOL AddMenu_toLast(CString text);

	//������ �޴��� ����.
	BOOL DeleteMenu_toLast();

	//�޴� ���̱�
	void ShowMenuList();
	void HideMenuList();

	//�޴��� ���� �������� BOOL �� ��ȯ. ���δ�(TRUE) : �Ⱥ��δ�(FALSE).
	BOOL isShowVaild();

	//�޴� ����Ʈ�� ������ DC�� �� ����Ѵ�.
	void PrintMenuList(CDC* pDC);

	//�޴� ��ưȭ ����
	void SetMenuBtn(BOOL ID);

	//focus�� �޴� ��
	void setFocus(int menuID);

	//�ش��ϴ� �޴��� �ҷ��´�.
	Menu* getMenu();

	//�Է¹��� Point�� � Menu�� Rect�� ��ġ�ϴ� �� ��ȯ. -1�� ������ �ǹ�.
	int PointOverMenu(POINT point);

	//focused Icon Set
	void setFocusImg(int ResourceID, LPCTSTR lpType);
};

#endif