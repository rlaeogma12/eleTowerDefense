#ifndef MSGBOX_H__
#define MSGBOX_H__

#pragma once
#include "menu.h"

/////////////////////
//msgBox.h
/////////////////////

//GameView�� EditView���� ���Ǵ� MsgBox�Դϴ�. �˸�â�� ���� �����ϹǷ�, MsgBox�� ���� ������ ������� ����մϴ�.

//MsgBox Class Definition

//�޴����� ��ӹ޾Ƽ� �ۼ�.
class msgBox : public menuSet{
private:
	int msgListNum;	//���� �޽����� ��Ÿ�� ��ġ

public:
	msgBox(int _colNum, int _rowNum, int x_pos, int y_pos, int _menuWidth, int _menuHeight, BOOL haveTitle = TRUE, BOOL haveBack = TRUE);
	~msgBox();

	void addMsg(CString msg);	//�޽����� �� �Ʒ��� �߰��Ѵ�.
};

#endif