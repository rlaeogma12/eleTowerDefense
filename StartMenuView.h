#pragma once
#include "afxwin.h"
#include "menutitle.h"
#include "Setting.h"
// StartMenuView �� ���Դϴ�.

class StartMenuView : public CFormView
{
	DECLARE_DYNCREATE(StartMenuView)

public:
	StartMenuView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~StartMenuView();
	
public:
	
	//�޴��� ����
	MenuSet* GameTitle;
	MenuSet* TitleMenu;
	MenuSet* DifficultyMenu;
	MenuSet* LoadDataMenu;
	MenuSet* EditDataMenu;
	MenuSet* OptionMenu;
	MenuSet* FocusMenu;
	
	void LoadMap();

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STARTMENUVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

	DECLARE_MESSAGE_MAP()
	virtual void OnDraw(CDC* /*pDC*/);
public:
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	virtual BOOL PreTranslateMessage(MSG* pMsg);
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};


