#pragma once
#include "menu.h"
#include "tile.h"
#include "enemy.h"
#include "afxwin.h"
#include "Utility.h"
#include "Setting.h"
#include "msgBox.h"

//Dialog ����
#include "EditHelpDlg.h"
#include "EditOptionDlg.h"

// EditView �� ���Դϴ�.

class EditView : public CFormView
{
	DECLARE_DYNCREATE(EditView)
protected:
	Utility DrawUI;


public:
	EditView();           // ���� ����⿡ ���Ǵ� public �������Դϴ�.
	virtual ~EditView();

	//Draw ���
	void InfoDraw(CDC* pDC);

	//�� �信�� ���� �޴� UI�� ��� ������ ����.
	ViewUI GameViewMenuUI;

	//���� �� ���� Ŀ�� ���¸� ��Ÿ����. 
	//0 : default , 1 : click
	int CursorState;

	//UI �޴� ����.
	menuSet *MapnameUI;
	menuSet *SaveUI;
	menuSet *LoadUI;
	menuSet *HelpUI;
	menuSet *OptionUI;
	menuSet *SettingMapUI;

	menuSet *TileSetUI;
	menuSet *TileInfoUI;

	////Map ���� ������
	//TileImg ����
	CImage TileSetIMG;



	//tileInfo�� ǥ���ϱ� ���� �����Դϴ�.
	tileSet *EditMap;

	//�׽�Ʈ Ŭ���� ����. �̸� ������� ���� ���, ���� ������ �Ұ����մϴ�.
	BOOL isTestCleared;	

	//Map ID�� ����ִ� 2���� �迭�Դϴ�.
	vector<vector<int> > MapArray;

	//User���� Ŭ���� Tile ǥ�ÿ�
	tile sTile;

	//�� ��� �������� �����ϰ�� TRUE �ƴѰ�� FALSE
	BOOL isNowOnTest;

	//�׽�Ʈ�� �� Set
	enemySet testEnemySet;

	//MsgBox ���
	msgBox *msgUI;

	//Test�� Enemy �̵� ������ ���� Thread ����
	CWinThread *pWinThread;
	static UINT TestThread(LPVOID _mothod);
//
public:
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnDraw(CDC* /*pDC*/);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
};


