#pragma once
#include "menu.h"
#include "tile.h"
#include "enemy.h"
#include "afxwin.h"
#include "Utility.h"
#include "Setting.h"
#include "msgBox.h"

//Dialog 모음
#include "EditHelpDlg.h"
#include "EditOptionDlg.h"

// EditView 폼 뷰입니다.

class EditView : public CFormView
{
	DECLARE_DYNCREATE(EditView)
protected:
	Utility DrawUI;


public:
	EditView();           // 동적 만들기에 사용되는 public 생성자입니다.
	virtual ~EditView();

	//Draw 기능
	void InfoDraw(CDC* pDC);

	//이 뷰에서 가진 메뉴 UI의 모든 정보를 담음.
	ViewUI GameViewMenuUI;

	//현재 이 뷰의 커서 상태를 나타낸다. 
	//0 : default , 1 : click
	int CursorState;

	//UI 메뉴 변수.
	menuSet *MapnameUI;
	menuSet *SaveUI;
	menuSet *LoadUI;
	menuSet *HelpUI;
	menuSet *OptionUI;
	menuSet *SettingMapUI;

	menuSet *TileSetUI;
	menuSet *TileInfoUI;

	////Map 관련 변수들
	//TileImg 변수
	CImage TileSetIMG;



	//tileInfo를 표시하기 위한 변수입니다.
	tileSet *EditMap;

	//테스트 클리어 여부. 이를 통과하지 못할 경우, 게임 시작이 불가능합니다.
	BOOL isTestCleared;	

	//Map ID를 담고있는 2차원 배열입니다.
	vector<vector<int> > MapArray;

	//User에게 클릭된 Tile 표시용
	tile sTile;

	//맵 경로 시험주행 도중일경우 TRUE 아닌경우 FALSE
	BOOL isNowOnTest;

	//테스트용 적 Set
	enemySet testEnemySet;

	//MsgBox 사용
	msgBox *msgUI;

	//Test용 Enemy 이동 구현을 위한 Thread 생성
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
	virtual void OnDraw(CDC* /*pDC*/);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnDestroy();
};


