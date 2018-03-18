// GameHelpDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TileEx.h"
#include "GameHelpDlg.h"
#include "afxdialogex.h"


// GameHelpDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(GameHelpDlg, CDialog)

GameHelpDlg::GameHelpDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_GAMEHELPDLG, pParent)
{

}

GameHelpDlg::~GameHelpDlg()
{
}

void GameHelpDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GameHelpDlg, CDialog)
END_MESSAGE_MAP()


// GameHelpDlg 메시지 처리기입니다.
