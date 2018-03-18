#pragma once
#include "GameView.h"
#include "StartMenuView.h"
#include "MainFrm.h"

// GameOptionDlg 대화 상자입니다.

class GameOptionDlg : public CDialog
{
	DECLARE_DYNAMIC(GameOptionDlg)

public:
	GameOptionDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~GameOptionDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEOPTIONDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonClose();
};
