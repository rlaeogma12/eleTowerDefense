
// TileEx.h : TileEx ���� ���α׷��� ���� �� ��� ����
//
#pragma once

#ifndef __AFXWIN_H__
	#error "PCH�� ���� �� ������ �����ϱ� ���� 'stdafx.h'�� �����մϴ�."
#endif

#include "resource.h"       // �� ��ȣ�Դϴ�.
#include "tile.h"					//��� View���� ����� �� Map ���� ����Դϴ�.

// CTileExApp:
// �� Ŭ������ ������ ���ؼ��� TileEx.cpp�� �����Ͻʽÿ�.
//

class CTileExApp : public CWinApp
{
public:
	CTileExApp();
	ULONG_PTR m_gpToken;



// �������Դϴ�.
public:
	virtual BOOL InitInstance();
	virtual int ExitInstance();

// �����Դϴ�.
	afx_msg void OnAppAbout();
	DECLARE_MESSAGE_MAP()
};

extern CTileExApp theApp;
extern tileSet *Map;