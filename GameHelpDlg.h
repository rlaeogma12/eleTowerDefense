#pragma once


// GameHelpDlg ��ȭ �����Դϴ�.

class GameHelpDlg : public CDialog
{
	DECLARE_DYNAMIC(GameHelpDlg)

public:
	GameHelpDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~GameHelpDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEHELPDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
