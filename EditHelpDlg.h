#pragma once


// EditHelpDlg ��ȭ �����Դϴ�.

class EditHelpDlg : public CDialog
{
	DECLARE_DYNAMIC(EditHelpDlg)

public:
	EditHelpDlg(CWnd* pParent = NULL);   // ǥ�� �������Դϴ�.
	virtual ~EditHelpDlg();

// ��ȭ ���� �������Դϴ�.
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EDITHELPDLG };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
};
