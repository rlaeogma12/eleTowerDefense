
// MainFrm.h : CMainFrame Ŭ������ �������̽�
//

#pragma once
#include "Setting.h"


///���Ƿ� ���� Message ���



class CMainFrame : public CFrameWnd
{
	
protected: // serialization������ ��������ϴ�.
	CMainFrame();
	DECLARE_DYNCREATE(CMainFrame)

// Ư���Դϴ�.
public:
	HCURSOR m_hNormalCursor, m_hClickCursor;

	BOOL m_bOnButton;
// �۾��Դϴ�.
public:
	CPoint point;
	CRect rect;
	
	int nDifficulty;


// �������Դϴ�.
public:
	virtual BOOL PreCreateWindow(CREATESTRUCT& cs);

// �����Դϴ�.
public:
	virtual ~CMainFrame();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


// ������ �޽��� �� �Լ�
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


