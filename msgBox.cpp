/////////////////////
//msgBox.cpp
/////////////////////

//GameView�� EditView���� ���Ǵ� MsgBox�Դϴ�. �˸�â�� ���� �����ϹǷ�, MsgBox�� ���� ������ ������� ����մϴ�.

#include "stdafx.h"
#include "msgBox.h"

//msgBox ����-------------

msgBox::msgBox(int _colNum, int _rowNum, int x_pos, int y_pos, int _menuWidth, int _menuHeight, BOOL haveTitle, BOOL haveBack) : menuSet(1, _rowNum, x_pos, y_pos, _menuWidth, _menuHeight, haveTitle, haveBack)
{	
	setAllMenuText(L"�̰��� �� �޽����� ��Ÿ���ϴ�.", 10, L"���ʷҵ���", 220, 255, 255);
	setMenuTitle(10, L"Message Box", 10, L"Corbel", 150, 200, 255);
	setBackGround(0, 150, 150, 0, 120, 120);
	setMenuInterval(3, 5, 5, 0, 0);
	setMenuSetting(FALSE, FALSE, FALSE);
	msgListNum = 0;
}

msgBox::~msgBox()
{

}

void msgBox::addMsg(CString msg)
{
	if (msgListNum < rowNum-1) {
		vMenu[0][msgListNum].setEachMenuSetting(FALSE, TRUE, FALSE);
		vMenu[0][msgListNum].setMenuText(msg);
		msgListNum++;
	}
	else {
		vMenu[0][msgListNum].setEachMenuSetting(FALSE, TRUE, FALSE);

		CString temp, temp2;		
		temp = msg;

		for (int i = msgListNum; i >= 0; i--) {
			temp2 = vMenu[0][i].getMenuText();	//���� �ڽ��� ���� �����ص�
			vMenu[0][i].setMenuText(temp);	//���� ��Ȳ���� ������ �ִ� temp�� �ڽ��� ���� ����.
			temp = temp2;	//������ �� ���� �ֽ����� �ٲ�
		}

		vMenu[0][msgListNum].setMenuText(msg, 10, L"���ʷҵ���", 255, 215, 0);


	}
}
