/////////////////
//menu.h
////////////////

#ifndef MENU_H__
#define MENU_H__

#pragma once

#include "Setting.h"
#include "Utility.h"



class menuSet;

//menu class ����
class menu
{
private:
	BOOL isUsingResource;		//�׸� ��� ����
	BOOL isUsingText;	//�۾� ��� ����
	BOOL isButton;	//��ưȭ ���� ����
	BOOL isAlignCenter;	//�޴� ������ ��� �����ҷ�?
	////-----------------------------------
		
	CPoint menuPos;	//Ư�� �޴��� �»�� ��ǥ

	//�� �޴��� ũ��
	int width, height;

	//�޴��� �ʿ��� CImage(�� �޴��� �ִ� 1��)
	CImage menuImg;
	int imgWidth, imgHeight;

	//�� �޴��� ���� text ����
	Text menuText;

	//�� �޴��� �θ� �޴� ������ ����
	menuSet *pParent;



protected:
	Utility DrawUI;


public:
	//�� �޴��� Index
	int index;

	//�޴� �⺻ ������
	menu();

	//�޴� �Ҹ���
	~menu();

	//�޴��� ��ġ �� ũ�� ����
	void setMenuPos(int x_pos, int y_pos, int width, int height, menuSet* parentMenu);

	//�޴� �׸� ���, �۾� ��� ��ưȭ ���� ���� ����
	void setEachMenuSetting(BOOL haveImg, BOOL haveText, BOOL isBtn);

	//�޴��� �̹����� �����Ѵ�. �������� ���� ���, ����Ʈ������ �����Ѵ�. (�׻� ���� ������ PNG�� ������)
	void setBtnImage(int ResourceID, int _imgWidth, int _imgHeight, BOOL _isAlignCenter);

	//�޴� �׸��� �۾��� �����Ѵ�.
	void setMenuText(CString name, int fontSize, CString fontName, int R, int G, int B, BOOL _isAlignCenter = FALSE);
	void setMenuText(CString name);

	//�� �޴��� �׸���.
	void drawMenu(CDC *pDC);

	//�޴��� ��ġ�� ���ϰų� ���� �����Ѵ�.
	void calPos(int add_xpos, int add_ypos);

	//�޴� ũ�� �׸� ����
	CRect returnMenuRect();	
	CString getMenuText();

	//Index��ȣ ����
	void setIndex(int _val);

	//�ش��ϴ� �ε��� ��ȣ�� ������ TRUE ��ȯ. �ƴϸ� FALSE
	BOOL isIndex(int x_index, int y_index);

	//�̰��� ��ư�̳�?
	BOOL isBtn();
};

class menuSet
{
private:
	//��������---------------
	//����� ������ �޴��Դϱ�
	BOOL isToggleMenu;

	//�������� �� ���ΰ�?
	BOOL isShown;

	//Ÿ��Ʋ �̸��� ������ ���ΰ�?
	BOOL isHaveTitleName;

	//��� �׸��� ������ ���ΰ�?
	BOOL isHaveBackground;

	//���콺�� Focus �� �޴��� ���� ��ġ�� > ǥ�ø� �� ���ΰ�?
	BOOL isFocusMenu;

	//----------------------------
	Text titleText;	//Ÿ��Ʋ ���� ���� ����


	//�޴��� �� ����
	CPoint menuSetPos;	//�޴� ������ �»�� ��ǥ

	//�޴� �� ������
	int menuWidth, menuHeight;


	////��� ��------
	//�� �޴��� ������(�ڵ����� ����� �����, ������� ���̱� ����)
	int menuEachWidth, menuEachHeight;

	//�޴�[0][0] ���� ��ǥ��
	int default_xpos, default_ypos;

	////-----------------

	//�޴� ����, �¿� ����
	int udInterval, lrInterval;

	//����, �¿� �޴��� ����
	int udmenuInterval, lrmenuInterval;

	//�޴� ����� ���� �޴��� ������ ����
	int titleInterval;
	int titleHeight;

	//�޴� ����
	int bR, bG, bB;

	//�޴� �׵θ���
	int bBR, bBG, bBB;

	//�� �޴��� ����� ����Ѵ�.
	void setEachMenuSize();

	//�� �޴����� �����ǰ� ����� �����Ѵ�.
	void setMenuPos();

	int edgeLocate;

protected:
	Utility DrawUI;

	vector<vector<menu> > vMenu;	//�޴� Ŭ������ ���� ���� �Ҵ�
	int colNum, rowNum;	//���� x ���� ����(�⺻ 1x1)

public:
	//���� ���õ� �޴��� ����.
	menu* FocusedMenu;

	menuSet(int _colNum, int _rowNum, int x_pos, int y_pos, int _menuWidth, int _menuHeight, BOOL haveTitle = FALSE, BOOL haveBack = TRUE);
	~menuSet();

	//�޴� Ÿ��Ʋ �̸��� ���Ѵ�. titleHeight : Ÿ��Ʋ ���� ����, name : �̸�, fontSize : ��Ʈũ��, ��Ʈ��, R,G,B(����)
	void setMenuTitle(int _titleHeight, CString name, int fontSize = 15, CString fontName = L"Corbel", int R = 0, int G = 220, int B = 200);

	//�޴� ��ġ�� �����Ѵ�.
	void renewPosition();

	//Ÿ��Ʋ �޴� �� ����� ����
	void setTitleBackground(BOOL haveTitle, BOOL haveBack);

	void setMenuSetPos(int x_pos, int y_pos);

	//�޴��� ���� ����
	void setBackGround(int _R, int _G, int _B, int _bR = 58, int _bG = 158, int _bB = 57);

	//�� �޴����� �׸�, �۾�, ��ưȭ ���� ���θ� �ѹ��� �����Ѵ�. (���������� ���� ����)
	//haveimg : �޴����� �̹����� ������ �ϴ°�, havetext : �޴����� �۾��� �����°�, isButton : �޴����� Ŭ���� �����Ѱ�.
	void setMenuSetting(BOOL haveImg, BOOL haveText, BOOL isButton);

	//�� �޴����� �۾� ũ��� ��Ʈ, ���� ���� �ѹ��� �����Ѵ�.
	//_text : �Է� �޽���. fontSize : �۲� ũ��, fontName : ��Ʈ �̸�, R G B : ����
	void setAllMenuText(CString _text, int fontSize, CString fontName, int R, int G, int B, BOOL isAlignCenter = FALSE);

	//�� �޴� �� ������ �����Ѵ�. _titleInterval : ����� �޴���� ���� ����, _udInterval : ���� ����, _lrInterval : �¿� ����
	//_udmenuInterval : ���� �޴� ���� ����_lrmenuInterval : �¿� �޴� ���� ����
	void setMenuInterval(int _titleInterval, int _udInterval, int _lrInterval, int _udmenuInterval, int _lrmenuInterval);

	//�޴� ������ ���� �� �ۼ�
	//col : ���� ��ȣ, row : ���� ��ȣ
	void setEach(int col, int row, CString _text);
	void setEach(int col, int row, CString _text, int fontSize, CString fontName, int R, int G, int B, BOOL isAlignCenter = FALSE);
	void setEach(int col, int row, int ResourceID, int imgWidth, int imgHeight, BOOL isAlignCenter);
	void setEach(int col, int row, int add_xpos, int add_ypos);

	//��� �޴� ����
	void setEdgeLocate(int locateID);
	void setToggle(BOOL ID);
	void setShown(BOOL ID);
	BOOL isStateShown();

	int getColNum();
	int getHeight();

	//���콺�� ��ġ�� �޴� �ȿ� �ִ��� Ȯ���Ѵ�. ���� ��� TRUE�� ��ȯ�ϰ�, Focus�� �޴��� �ش� �޴��� �����Ѵ�. �ƴ� ��� FALSE ��ȯ.
	BOOL isInMenu(CPoint& MousePos);
	void setFocusMenu(menu &obj);

	//�޴� ��ü�� ����Ѵ�
	void drawAllMenu(CDC *pDC);
};

//View���� ����ϴ� ��� UI�� �����ؼ� �����ϱ� ���� Ŭ����.
class ViewUI {
private:
	//MenuSet�� ������ ����..
	vector<menuSet*> UIArray;

	//��Ŀ���� �޴���
	menuSet* focusedMenuSet;

public:
	//������
	ViewUI();
	//�Ҹ���
	~ViewUI();

	//UI ����Ʈ �������� �߰�
	void addMenu(int _colNum, int _rowNum, int x_pos, int y_pos, int _menuWidth, int _menuHeight, BOOL haveTitle = FALSE, BOOL haveBack = TRUE);
	void addMenu(menuSet *objMenuSet);

	//���� ������ List ����
	void deleteMenu();

	//UI �޴����� �����͸� �����Ѵ�.
	void deleteAllpMenu();

	//�ش��ϴ� View UI ����� ���� Traverse�ؼ�, �ϳ���
	//�Ű������� ���� point�� ���� InRect TRUE ��ȯ ��, TRUE�� ��ȯ. else FALSE.
	BOOL isInUI(CPoint point);

	//View���� ��� Menu UI�� �׷�����.
	void DrawAllViewUI(CDC *pDC);

};

#endif