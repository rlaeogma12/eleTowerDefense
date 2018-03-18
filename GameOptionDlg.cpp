// GameOptionDlg.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TileEx.h"
#include "GameOptionDlg.h"
#include "afxdialogex.h"

class GameView;
class CMainFrame;
class StartMenuView;

// GameOptionDlg 대화 상자입니다.

IMPLEMENT_DYNAMIC(GameOptionDlg, CDialog)

GameOptionDlg::GameOptionDlg(CWnd* pParent /*=NULL*/)
	: CDialog(IDD_GAMEOPTIONDLG, pParent)
{

}

GameOptionDlg::~GameOptionDlg()
{
}

void GameOptionDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(GameOptionDlg, CDialog)
	ON_BN_CLICKED(IDC_BUTTON1, &GameOptionDlg::OnButtonClose)
END_MESSAGE_MAP()


// GameOptionDlg 메시지 처리기입니다.


void GameOptionDlg::OnButtonClose()
{
	// TODO: 여기에 컨트롤 알림 처리기 코드를 추가합니다.
	::PostMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
}
