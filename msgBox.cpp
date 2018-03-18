/////////////////////
//msgBox.cpp
/////////////////////

//GameView와 EditView에서 사용되는 MsgBox입니다. 알림창을 띄우기 불편하므로, MsgBox를 통해 데이터 결과값을 출력합니다.

#include "stdafx.h"
#include "msgBox.h"

//msgBox 정의-------------

msgBox::msgBox(int _colNum, int _rowNum, int x_pos, int y_pos, int _menuWidth, int _menuHeight, BOOL haveTitle, BOOL haveBack) : menuSet(1, _rowNum, x_pos, y_pos, _menuWidth, _menuHeight, haveTitle, haveBack)
{	
	setAllMenuText(L"이곳에 새 메시지가 나타납니다.", 10, L"함초롬돋움", 220, 255, 255);
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
			temp2 = vMenu[0][i].getMenuText();	//먼저 자신의 값을 저장해둠
			vMenu[0][i].setMenuText(temp);	//이전 상황에서 가지고 있던 temp를 자신의 값에 대입.
			temp = temp2;	//저장해 둔 값을 최신으로 바꿈
		}

		vMenu[0][msgListNum].setMenuText(msg, 10, L"함초롬돋움", 255, 215, 0);


	}
}
