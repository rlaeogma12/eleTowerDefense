// EditHelpDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TileEx.h"
#include "EditHelpDlg.h"
#include "afxdialogex.h"


// EditHelpDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(EditHelpDlg, CDialog)

EditHelpDlg::EditHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_EDITHELPDLG, pParent)
{

}

EditHelpDlg::~EditHelpDlg()
{
}

void EditHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(EditHelpDlg, CDialog)
END_MESSAGE_MAP()


// EditHelpDlg 메시지 처리기입니다.
