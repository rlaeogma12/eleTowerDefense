#include "stdafx.h"
#include "menu.h"


////--------------------------------
//메뉴 구현부
menu::menu()
{
	isAlignCenter = FALSE;
	setMenuPos(0, 0, 0, 0, NULL);
	setEachMenuSetting(FALSE, TRUE, FALSE);
	//메뉴 버튼 디폴트 사이즈 32x32 , png 딴거 쓸거면 별도로 선언.
	setBtnImage(0, 32, 32, FALSE);
	setIndex(0);
}


menu::~menu()
{
}

void menu::setMenuPos(int x_pos, int y_pos, int width, int height, menuSet* parentMenu)
{
	pParent = parentMenu;
	menuPos.SetPoint(x_pos, y_pos);
	this->width = width;
	this->height = height;
}

void menu::setEachMenuSetting(BOOL haveImg, BOOL haveText, BOOL isBtn)
{
	isUsingResource = haveImg;
	isUsingText = haveText;
	isButton = isBtn;
}

void menu::setBtnImage(int ResourceID, int _imgWidth, int _imgHeight, BOOL _isAlignCenter)
{
	if (ResourceID) {
		DrawUI.SetImage(&menuImg, ResourceID, _T("PNG"));
		isUsingResource = TRUE;
	};
	isAlignCenter = _isAlignCenter;
	imgWidth = _imgWidth;
	imgHeight = _imgHeight;
}

void menu::setMenuText(CString name, int fontSize, CString fontName, int R, int G, int B, BOOL _isAlignCenter)
{
	isAlignCenter = _isAlignCenter;
	isUsingText = TRUE;
	menuText.setText(name, fontSize, fontName, R, G, B);
}

void menu::setMenuText(CString name)
{
	menuText.setText(name);
}

void menu::drawMenu(CDC * pDC)
{
	//그림 사용하면
	if (isUsingResource) {
		if (isAlignCenter) {
			if (menuImg)menuImg.Draw(pDC->m_hDC, menuPos.x + (width - imgWidth) / 2, menuPos.y + (height - imgHeight) / 2, imgWidth, imgHeight);
		}
		else {
			if (menuImg)menuImg.Draw(pDC->m_hDC, menuPos.x, menuPos.y + (height - imgHeight) / 2, imgWidth, imgHeight);
		}
	}

	//텍스트 사용하면
	if (isUsingText) {
		if (isUsingResource) {
			DrawUI.WriteText(pDC, menuText.text, menuPos.x + imgWidth + 5, menuPos.y, width - imgWidth - 5, height, menuText.textSize,
				menuText.fontName, menuText.R, menuText.G, menuText.B, isAlignCenter);
		}
		else {
			DrawUI.WriteText(pDC, menuText.text, menuPos.x, menuPos.y, width, height, menuText.textSize,
				menuText.fontName, menuText.R, menuText.G, menuText.B, isAlignCenter);
		}
	}
}
void menu::calPos(int add_xpos, int add_ypos)
{
	menuPos.SetPoint(menuPos.x + add_xpos, menuPos.y + add_ypos);
}
CRect menu::returnMenuRect()
{
	return CRect(menuPos.x, menuPos.y, menuPos.x + width, menuPos.y + height);
}
CString menu::getMenuText()
{
	return menuText.getText();
}
void menu::setIndex(int _val)
{
	index = _val;
}
BOOL menu::isIndex(int x_index, int y_index)
{
	if (index == x_index*(pParent->getColNum()) + y_index) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}
BOOL menu::isBtn()
{
	return isButton;
}
//------------------------------
//메뉴 집합 구현부

void menuSet::setEachMenuSize()
{
	menuEachWidth = (menuWidth - 2 * lrInterval - (colNum - 1)*lrmenuInterval) / colNum;
	menuEachHeight = (menuHeight - titleHeight - 2 * udInterval - (rowNum - 1)*udmenuInterval) / rowNum;

	default_xpos = menuSetPos.x + lrInterval;
	default_ypos = menuSetPos.y + udInterval + titleHeight + titleInterval;
}

void menuSet::setMenuPos()
{
	for (int i = 0; i < colNum; i++) {
		for (int j = 0; j < rowNum; j++) {
			vMenu[i][j].setMenuPos(default_xpos + (menuEachWidth + lrmenuInterval)*i, default_ypos + (menuEachHeight + udmenuInterval)*j, menuEachWidth, menuEachHeight, this);
			vMenu[i][j].setIndex(i + j*colNum);
		}
	}
}

menuSet::menuSet(int _colNum, int _rowNum, int x_pos, int y_pos, int _menuWidth, int _menuHeight, BOOL haveTitle, BOOL haveBack)
{
	isShown = TRUE;
	isToggleMenu = FALSE;
	edgeLocate = 0;
	colNum = _colNum;
	rowNum = _rowNum;


	//col x row 2차원배열 생성
	for (int i = 0; i < colNum; i++) {
		vector<menu> elem;
		elem.resize(rowNum);
		vMenu.push_back(elem);
	}

	//메뉴 생성시 Focus Mouse는 일반적으로 OFF 상태이다.
	isFocusMenu = FALSE;

	//기본적으로 Focus 된 Menu는 vMenu(0,0) 을 기본으로 한다.
	FocusedMenu = &vMenu[0][0];

	//받은 변수로 설정
	menuSetPos.SetPoint(x_pos, y_pos);
	menuWidth = _menuWidth;
	menuHeight = _menuHeight;
	//메뉴 생성 시 디폴트 간격
	setMenuInterval(0, 5, 7, 5, 5);
	setTitleBackground(haveTitle, haveBack);

	//메뉴 생성 시 디폴트 제목
	if (isHaveTitleName) {
		setMenuTitle(15, L"Menu Title", 15, L"Corbel", 0, 220, 200);
	}
	else {
		setMenuTitle(0, L"Menu Title", 20, L"Corbel", 255, 220, 200);
	}
	//메뉴 생성 시 디폴트 메뉴 설정
	setMenuSetting(FALSE, TRUE, FALSE);
	//디폴트 배경색
	setBackGround(36, 112, 41);
	renewPosition();
}

menuSet::~menuSet()
{
	//메뉴 모음 vector 동적할당 해제 한다.
	for (int i = 0; i < (int)vMenu.size(); i++) {
		vMenu[i].clear();
	}
	vMenu.clear();
}

void menuSet::setMenuTitle(int _titleHeight, CString name, int fontSize, CString fontName, int R, int G, int B)
{
	titleHeight = _titleHeight;
	titleText.setText(name, fontSize, fontName, R, G, B);
}

void menuSet::renewPosition()
{
	setEachMenuSize();
	setMenuPos();
}

void menuSet::setTitleBackground(BOOL haveTitle, BOOL haveBack)
{
	isHaveTitleName = haveTitle;
	if (isHaveTitleName) {
		//Do Nothing.
	}
	else {
		titleHeight = 0;
		titleInterval = 0;
	}
	isHaveBackground = haveBack;
	renewPosition();
}

void menuSet::setMenuSetPos(int x_pos, int y_pos)
{
	isToggleMenu = TRUE;
	menuSetPos.SetPoint(x_pos, y_pos);
	renewPosition();
}

void menuSet::setBackGround(int _R, int _G, int _B, int _bR, int _bG, int _bB)
{
	bR = _R;
	bG = _G;
	bB = _B;

	bBR = _bR;
	bBG = _bG;
	bBB = _bB;
}

void menuSet::setMenuSetting(BOOL haveImg, BOOL haveText, BOOL isButton)
{
	for (int i = 0; i < colNum; i++) {
		for (int j = 0; j < rowNum; j++) {
			vMenu[i][j].setEachMenuSetting(haveImg, haveText, isButton);
		}
	}
}

void menuSet::setAllMenuText(CString _text, int fontSize, CString fontName, int R, int G, int B, BOOL isAlignCenter)
{
	for (int i = 0; i < colNum; i++) {
		for (int j = 0; j < rowNum; j++) {
			vMenu[i][j].setMenuText(_text, fontSize, fontName, R, G, B, isAlignCenter);
		}
	}
}

void menuSet::setMenuInterval(int _titleInterval, int _udInterval, int _lrInterval, int _udmenuInterval, int _lrmenuInterval)
{
	titleInterval = _titleInterval;
	udInterval = _udInterval;
	lrInterval = _lrInterval;
	udmenuInterval = _udmenuInterval;
	lrmenuInterval = _lrmenuInterval;
}

void menuSet::setEach(int col, int row, CString _text)
{
	if (col < colNum && row < rowNum) {
		vMenu[col][row].setMenuText(_text);
	}
	else {
		TRACE("col, row 이상은 불가능");
	}
}

void menuSet::setEach(int col, int row, CString _text, int fontSize, CString fontName, int R, int G, int B, BOOL isAlignCenter)
{
	if (col < colNum && row < rowNum) {
		vMenu[col][row].setMenuText(_text, fontSize, fontName, R, G, B, isAlignCenter);
	}
	else {
		TRACE("col, row 이상은 불가능");
	}
}



void menuSet::setEach(int col, int row, int ResourceID, int imgWidth, int imgHeight, BOOL isAlignCenter)
{
	if (col < colNum && row < rowNum) {
		vMenu[col][row].setBtnImage(ResourceID, imgWidth, imgHeight, isAlignCenter);
	}
	else {
		TRACE("col, row 이상은 불가능");
	}
}

void menuSet::setEach(int col, int row, int add_xpos, int add_ypos)
{
	vMenu[col][row].calPos(add_xpos, add_ypos);
}

void menuSet::setEdgeLocate(int locateID)
{
	edgeLocate = locateID;
}

void menuSet::setToggle(BOOL ID)
{
	isToggleMenu = ID;
}

void menuSet::setShown(BOOL ID)
{
	isShown = ID;
}

BOOL menuSet::isStateShown()
{
	return isShown;
}

int menuSet::getColNum()
{
	return colNum;
}

int menuSet::getHeight()
{
	return menuHeight;
}

BOOL menuSet::isInMenu(CPoint& MousePos)
{
	if (isShown) {
		for (int i = 0; i < colNum; i++) {
			for (int j = 0; j < rowNum; j++) {
				if (vMenu[i][j].isBtn()) {
					if (vMenu[i][j].returnMenuRect().PtInRect(MousePos)) {
						setFocusMenu(vMenu[i][j]);
						return TRUE;
					}
				}
			}
		}
	}
	return FALSE;
}

void menuSet::setFocusMenu(menu & obj)
{
	FocusedMenu = &obj;
}

void menuSet::drawAllMenu(CDC * pDC)
{
	if (isShown) {
		if (isHaveBackground) {
			if (isToggleMenu) {
				DrawUI.DrawWordBack(pDC, menuSetPos.x, menuSetPos.y, menuWidth, menuHeight, bR, bG, bB, bBR, bBG, bBB, 10, 5, edgeLocate);
			}
			else {
				DrawUI.DrawBack(pDC, menuSetPos.x, menuSetPos.y, menuWidth, menuHeight, bR, bG, bB, bBR, bBG, bBB);
			}			
		}

		if (isHaveTitleName) {
			DrawUI.WriteText(pDC, titleText.text, menuSetPos.x + lrInterval, menuSetPos.y + udInterval,
				menuWidth - 2 * lrInterval, titleHeight, titleText.textSize, titleText.fontName, titleText.R, titleText.G, titleText.B, TRUE);
		}

		for (int i = 0; i < colNum; i++) {
			for (int j = 0; j < rowNum; j++) {
				vMenu[i][j].drawMenu(pDC);
			}
		}
	}
}

ViewUI::ViewUI()
{
	focusedMenuSet = NULL;
}

ViewUI::~ViewUI()
{
	//UIArray Vector 메모리해제 필요..
}

void ViewUI::addMenu(int _colNum, int _rowNum, int x_pos, int y_pos, int _menuWidth, int _menuHeight, BOOL haveTitle, BOOL haveBack)
{
	menuSet *tempMenuSet = new menuSet(_colNum, _rowNum, x_pos, y_pos, _menuWidth, _menuHeight, haveTitle, haveBack);
	UIArray.push_back(tempMenuSet);
}

void ViewUI::addMenu(menuSet * objMenuSet)
{
	UIArray.push_back(objMenuSet);
}

void ViewUI::deleteMenu()
{
	UIArray.pop_back();
}

void ViewUI::deleteAllpMenu()
{
	for (vector<menuSet*>::size_type i = 0; i < UIArray.size(); i++) {
		delete UIArray[i];
	}

}

BOOL ViewUI::isInUI(CPoint point)
{
	if (!UIArray.empty()) {
		for (vector<menuSet>::size_type i = 0; i < UIArray.size(); i++) {
			if (UIArray[i]->isInMenu(point)) {
				focusedMenuSet = UIArray[i];
				return TRUE;
			}
		}
	}
	return FALSE;
}

void ViewUI::DrawAllViewUI(CDC * pDC)
{
	for (vector<menuSet>::size_type i = 0; i < UIArray.size(); i++) {
		UIArray[i]->drawAllMenu(pDC);
	}
}

