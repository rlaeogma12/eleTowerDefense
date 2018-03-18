#pragma once

// EditOptionDlg 대화 상자입니다.
class EditView;
class CMainFrame;
class StartMenuView;


class EditOptionDlg : public CDialog
{
	DECLARE_DYNAMIC(EditOptionDlg)

public:
	EditOptionDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~EditOptionDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITOPTIONDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedGotoTitle();


	afx_msg int OnCreate(LPCREATESTRUCT lpCreateStruct);
	afx_msg void OnDestroy();
};
