#pragma once
#include "GameView.h"
#include "StartMenuView.h"
#include "MainFrm.h"

// GameOptionDlg ��ȭ �����Դϴ�.

class GameOptionDlg : public CDialog
{
	DECLARE_DYNAMIC(GameOptionDlg)

public:
	GameOptionDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GameOptionDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEOPTIONDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnButtonClose();
};
