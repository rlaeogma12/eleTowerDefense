// EditOptionDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TileEx.h"
#include "EditOptionDlg.h"
#include "afxdialogex.h"
#include "Setting.h"
#include "MainFrm.h"
#include "EditView.h"
#include "StartMenuView.h"

// EditOptionDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(EditOptionDlg, CDialog)

EditOptionDlg::EditOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_EDITOPTIONDLG, pParent)
{

}

EditOptionDlg::~EditOptionDlg()
{
}

void EditOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EditOptionDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &EditOptionDlg::OnBnClickedGotoTitle)
	ON_WM_CREATE()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// EditOptionDlg �޽��� ó�����Դϴ�.


void EditOptionDlg::OnBnClickedGotoTitle()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	//::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_STARTMENUVIEW, 0);
	
	::PostMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
}



int EditOptionDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  ���⿡ Ư��ȭ�� �ۼ� �ڵ带 �߰��մϴ�.



	return 0;
}


void EditOptionDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
}
