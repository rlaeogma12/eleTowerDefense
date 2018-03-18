#ifndef MSGBOX_H__
#define MSGBOX_H__

#pragma once
#include "menu.h"

/////////////////////
//msgBox.h
/////////////////////

//GameView와 EditView에서 사용되는 MsgBox입니다. 알림창을 띄우기 불편하므로, MsgBox를 통해 데이터 결과값을 출력합니다.

//MsgBox Class Definition

//메뉴셋을 상속받아서 작성.
class msgBox : public menuSet{
private:
	int msgListNum;	//현재 메시지가 나타날 위치

public:
	msgBox(int _colNum, int _rowNum, int x_pos, int y_pos, int _menuWidth, int _menuHeight, BOOL haveTitle = TRUE, BOOL haveBack = TRUE);
	~msgBox();

	void addMsg(CString msg);	//메시지를 맨 아래에 추가한다.
};

#endif