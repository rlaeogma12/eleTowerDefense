// GameOptionDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TileEx.h"
#include "GameOptionDlg.h"
#include "afxdialogex.h"

class GameView;
class CMainFrame;
class StartMenuView;

// GameOptionDlg ��ȭ �����Դϴ�.

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


// GameOptionDlg �޽��� ó�����Դϴ�.


void GameOptionDlg::OnButtonClose()
{
	// TODO: ���⿡ ��Ʈ�� �˸� ó���� �ڵ带 �߰��մϴ�.
	::PostMessage(GetSafeHwnd(), WM_CLOSE, NULL, NULL);
}
