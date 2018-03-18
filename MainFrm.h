
// MainFrm.h : CMainFrame 클래스의 인터페이스
//

#pragma once
#include "Setting.h"


///임의로 만든 Message 목록



class CMainFrame : public CFrameWnd
{
	
protected: // serialization에서만 만들어집니다.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// 특성입니다.
public:
	HCURSOR m_hNormalCursor, m_hClickCursor;

	BOOL m_bOnButton;
// 작업입니다.
public:
	CPoint point;
	CRect rect;
	
	int nDifficulty;


// 재정의입니다.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// 구현입니다.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// 생성된 메시지 맵 함수
protected:
	DECLARE_MESSAGE_MAP()

	virtual BOOL OnCreateClient(LPCREATESTRUCT lpcs, CCreateContext* pContext);
public:
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
protected:
	afx_msg LRESULT OnFormChange(WPARAM wParam, LPARAM lParam);
	afx_msg LRESULT OnChangecursor(WPARAM wParam, LPARAM lParam);
};


