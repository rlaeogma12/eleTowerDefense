// EditOptionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TileEx.h"
#include "EditOptionDlg.h"
#include "afxdialogex.h"
#include "Setting.h"
#include "MainFrm.h"
#include "EditView.h"
#include "StartMenuView.h"

// EditOptionDlg 대화 상자입니다.

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


// EditOptionDlg 메시지 처리기입니다.


void EditOptionDlg::OnBnClickedGotoTitle()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	//::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_STARTMENUVIEW, 0);
	
	::PostMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
}



int EditOptionDlg::OnCreate(LPCREATESTRUCT lpCreateStruct)
{
	if (CDialog::OnCreate(lpCreateStruct) == -1)
		return -1;

	// TODO:  여기에 특수화된 작성 코드를 추가합니다.



	return 0;
}


void EditOptionDlg::OnDestroy()
{
	CDialog::OnDestroy();

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
}
