#pragma once

// EditOptionDlg ��ȭ �����Դϴ�.
class EditView;
class CMainFrame;
class StartMenuView;


class EditOptionDlg : public CDialog
{
	DECLARE_DYNAMIC(EditOptionDlg)

public:
	EditOptionDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~EditOptionDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITOPTIONDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGotoTitle();


	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};
