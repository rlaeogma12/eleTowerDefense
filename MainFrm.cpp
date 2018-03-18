
// MainFrm.cpp : CMainFrame 클래스의 구현
//

#include "stdafx.h"
#include "TileEx.h"

#include "MainFrm.h"
#include "GameView.h"
#include "StartMenuView.h"
#include "EditView.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// CMainFrame

IMPLEMENT_DYNCREATE(CMainFrame, CFrameWnd)

BEGIN_MESSAGE_MAP(CMainFrame, CFrameWnd)
	ON_WM_SETCURSOR()
	ON_WM_MOUSEMOVE()
	ON_MESSAGE(WM_ON_FORM_CHANGE, &CMainFrame::OnFormChange)
	ON_MESSAGE(WM_CHANGECURSOR, &CMainFrame::OnChangecursor)
END_MESSAGE_MAP()

// CMainFrame 생성/소멸

CMainFrame::CMainFrame()
{
	// TODO: 여기에 멤버 초기화 코드를 추가합니다.
}

CMainFrame::~CMainFrame()
{
}

BOOL CMainFrame::PreCreateWindow(CREATESTRUCT& cs)
{
	if (!CFrameWnd::PreCreateWindow(cs))
		return FALSE;
	// TODO: CREATESTRUCT cs를 수정하여 여기에서
	//  Window 클래스 또는 스타일을 수정합니다.

	//해상도 1300x700
	cs.cx = 1300;
	cs.cy = 700;

	cs.style = WS_MINIMIZEBOX | WS_SYSMENU;
	if (cs.hMenu != NULL) {
		::DestroyMenu(cs.hMenu);
		cs.hMenu = NULL;
	}



	return TRUE;
}

// CMainFrame 진단

#ifdef _DEBUG
void CMainFrame::AssertValid() const
{
	CFrameWnd::AssertValid();
}

void CMainFrame::Dump(CDumpContext& dc) const
{
	CFrameWnd::Dump(dc);
}
#endif //_DEBUG


// CMainFrame 메시지 처리기



BOOL CMainFrame::OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext)
{
	m_hNormalCursor = AfxGetApp()->LoadCursorW(IDC_CURSOR1);
	m_hClickCursor = AfxGetApp()->LoadCursorW(IDC_CURSOR2);
	m_bOnButton = FALSE;

	return CFrameWnd::OnCreateClient(lpcs, pContext);
}



BOOL CMainFrame::OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (nHitTest == HTCLIENT) {
		::GetCursorPos(&point);
		ScreenToClient(&point);
		GetClientRect(&rect);
		if (rect.PtInRect(point)) {
			SetCursor(m_bOnButton ? m_hClickCursor : m_hNormalCursor);
		}
		else {
			SetCursor(AfxGetApp()->LoadStandardCursor(IDC_CROSS));
		}
		return TRUE;
	}

	return CFrameWnd::OnSetCursor(pWnd, nHitTest, message);
}



void CMainFrame::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	CFrameWnd::OnMouseMove(nFlags, point);
}



afx_msg LRESULT CMainFrame::OnFormChange(WPARAM wParam, LPARAM lParam)
{
	int p_index = (int)wParam;

	CView *pOldActiveView = GetActiveView();
	CView *pNewActiveView = (CView*)GetDlgItem(wParam);


	if (pNewActiveView == NULL) {
		switch (p_index) {
			//GameView로의 전환 시
		case IDD_GAMEVIEW:
			pNewActiveView = (CView*)new GameView;
			TRACE0("Active View를 GameView로 설정합니다.");
			nDifficulty = (int)lParam;
			break;
		case IDD_EDITVIEW:
			pNewActiveView = (CView*)new EditView;
			TRACE0("Active View를 EditView로 설정합니다.");
			break;
		case IDD_STARTMENUVIEW:
			pNewActiveView = (CView*)new StartMenuView;
			TRACE0("Active View를 StartMenuView로 설정합니다.");
			break;
		}
		CCreateContext context;
		context.m_pCurrentDoc = pOldActiveView->GetDocument();
		pNewActiveView->Create(NULL, NULL, 0L, CFrameWnd::rectDefault, this, wParam, &context);
		pNewActiveView->OnInitialUpdate();
	}
	SetActiveView(pNewActiveView);
	pNewActiveView->ShowWindow(SW_SHOW);

	if (pOldActiveView->GetRuntimeClass() == RUNTIME_CLASS(GameView)) {
		pOldActiveView->SetDlgCtrlID(IDD_GAMEVIEW);
	}
	else if (pOldActiveView->GetRuntimeClass() == RUNTIME_CLASS(EditView)) {
		pOldActiveView->SetDlgCtrlID(IDD_EDITVIEW);
	}
	else if (pOldActiveView->GetRuntimeClass() == RUNTIME_CLASS(StartMenuView)) {
		pOldActiveView->SetDlgCtrlID(IDD_STARTMENUVIEW);
	}

	pNewActiveView->SetDlgCtrlID(AFX_IDW_PANE_FIRST);
	RecalcLayout();
	delete pOldActiveView;
	return 0;
}



afx_msg LRESULT CMainFrame::OnChangecursor(WPARAM wParam, LPARAM lParam)
{
	//wParam 으로 TRUE 받을 시
	if (wParam) {
		m_bOnButton = TRUE;
	}
	//wParam 으로 FALSE 받을 시
	else {
		m_bOnButton = FALSE;
	}

	return 0;
}
