#pragma once


// EditHelpDlg 대화 상자입니다.

class EditHelpDlg : public CDialog
{
	DECLARE_DYNAMIC(EditHelpDlg)

public:
	EditHelpDlg(CWnd* pParent = NULL);   // 표준 생성자입니다.
	virtual ~EditHelpDlg();

// 대화 상자 데이터입니다.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITHELPDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
};
