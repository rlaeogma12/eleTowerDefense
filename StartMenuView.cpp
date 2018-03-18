// StartMenuView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TileEx.h"
#include "StartMenuView.h"

#include "Utility.h"
// StartMenuView

IMPLEMENT_DYNCREATE(StartMenuView, CFormView)

StartMenuView::StartMenuView()
	: CFormView(IDD_STARTMENUVIEW)
{
}

StartMenuView::~StartMenuView()
{
}

void StartMenuView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(StartMenuView, CFormView)
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_MOUSEMOVE()
	ON_WM_DESTROY()
//	ON_WM_NCDESTROY()
END_MESSAGE_MAP()


// StartMenuView �����Դϴ�.

#ifdef _DEBUG

void StartMenuView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void StartMenuView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// StartMenuView �޽��� ó�����Դϴ�.

//��ŸƮ �޴��� �׸��� �޽��� ó��
void StartMenuView::OnDraw(CDC* /*pDC*/)
{
	CClientDC dc(this);
	CRect rlClientRect;
	GetClientRect(&rlClientRect);

	Rect rclClient(rlClientRect.left, rlClientRect.top, rlClientRect.Width(), rlClientRect.Height());

	CDC MemDC;
	MemDC.CreateCompatibleDC(&dc);
	CBitmap memBitmap;
	memBitmap.CreateCompatibleBitmap(&dc, rlClientRect.Width(), rlClientRect.Height());
	CBitmap *pOldBitmap = MemDC.SelectObject(&memBitmap);
	Graphics mem(MemDC.m_hDC);
	mem.SetSmoothingMode(SmoothingModeHighQuality);

	// �׸��� �� bitmap ������ �Ͼ�� �׷��ش�. (�� �κ��� ������ �ܻ��� ���� �ȴ�)
	Gdiplus::SolidBrush whiteBrush(Gdiplus::Color(255, 45, 45, 45));
	mem.FillRectangle(&whiteBrush, 0, 0, rlClientRect.Width(), rlClientRect.Height());

	/////////�������� MemDC�� ���� Write ����

	//Color Set
	GameTitle->PrintMenuList(&MemDC);
	FocusMenu->PrintMenuList(&MemDC);	
	///////////////////

	dc.BitBlt(0, 0, rlClientRect.right, rlClientRect.bottom, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBitmap);
	mem.ReleaseHDC(dc.m_hDC);
}



///���� �ʱ�ȭ�� �̰�����.
void StartMenuView::OnInitialUpdate()
{
	//CFormView::OnInitialUpdate();
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	//Title�� ǥ�õǴ� Text Set�� �����.
	GameTitle = new MenuSet(600, 30, 1200, 350, 3, 20, 20);
	GameTitle->SetMenuBtn(FALSE);

	GameTitle->AddMenu_toLast(_T("TOWER DEFENSE"));
	(GameTitle->getMenu())[0].setTextSize(70);
	(GameTitle->getMenu())[0].setFontColor(82, 170, 170);
	(GameTitle->getMenu())[0].setMenuRect(270, 70, 1300, 70);

	GameTitle->AddMenu_toLast(_T("Visual Programming Project - Using MFC, C++"));
	(GameTitle->getMenu())[1].setTextSize(20);
	(GameTitle->getMenu())[1].setFontColor(255, 228, 196);
	(GameTitle->getMenu())[1].setMenuRect(700, 140, 1300, 140);

	GameTitle->AddMenu_toLast(_T("2013310621 �����"));
	(GameTitle->getMenu())[2].setTextSize(20);
	(GameTitle->getMenu())[2].setFontColor(189, 183, 107);
	(GameTitle->getMenu())[2].setMenuRect(840, 170, 1300, 170);

	GameTitle->ShowMenuList();
	////



	//Title Menu�� �����.
	TitleMenu = new MenuSet(550, 200, 800, 650, 5, 10, 25);

	TitleMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Start Game"));
	TitleMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Load Game"));
	TitleMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Map Edit"));
	TitleMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Option"));
	TitleMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Exit Game"));

	TitleMenu->setFocusImg(IDB_RIGHTARROW, _T("PNG"));

	TitleMenu->ShowMenuList();
	//////

	//Difficulty Menu�� �����.
	DifficultyMenu = new MenuSet(550, 200, 800, 650, 5, 10, 25);

	DifficultyMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Easy(HP : 50%)"));
	DifficultyMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Normal(100%)"));
	DifficultyMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Hard(150%)"));
	DifficultyMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Impossible(200%)"));
	DifficultyMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Back to Title"));

	DifficultyMenu->setFocusImg(IDB_RIGHTARROW, _T("PNG"));

	DifficultyMenu->HideMenuList();
	//////

	//Load Data Menu�� �����.
	LoadDataMenu = new MenuSet(550, 200, 800, 580, 4, 10, 25);

	LoadDataMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Save Data 1 - "));
	LoadDataMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Save Data 2 - "));
	LoadDataMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Save Data 3 - "));
	LoadDataMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Back to Title "));

	LoadDataMenu->setFocusImg(IDB_RIGHTARROW, _T("PNG"));

	LoadDataMenu->HideMenuList();
	////

	//EditDataMenu
	EditDataMenu = new MenuSet(550, 200, 800, 520, 3, 10, 25);

	EditDataMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Create New Map"));
	EditDataMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Load Map"));
	EditDataMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Back to Title"));

	EditDataMenu->setFocusImg(IDB_RIGHTARROW, _T("PNG"));

	EditDataMenu->HideMenuList();
	////

	//OptionMenu;
	OptionMenu = new MenuSet(550, 200, 800, 520, 3, 10, 25);

	OptionMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Resolution Setting"));
	OptionMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("FullScreen Mode"));
	OptionMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Back to Title"));

	OptionMenu->setFocusImg(IDB_RIGHTARROW, _T("PNG"));

	OptionMenu->HideMenuList();

	///////Focus Menu�� �����Ѵ�. �� View���� Ȱ��ȭ �Ǵ� ������ �ϳ��� �����Ѵ�.
	FocusMenu = TitleMenu;
	//////	


	//������ �� ��ü�� ����ϴ�.-----------------
	Map = new tileSet(STANDARD_COL, STANDARD_ROW, 20, 20, 46, 46, IDB_TILESET);

	//Standard Map�� ����(23x11 Size)
	vector<vector<int> > MapArray;
	for (int i = 0; i < STANDARD_COL; i++) {
		vector<int> elem;
		elem.resize(STANDARD_ROW);
		MapArray.push_back(elem);
	}

	for (int i = 0; i < STANDARD_COL; i++) {
		for (int j = 0; j < STANDARD_ROW; j++) {
			MapArray[i][j] = 3;

			//�����ڸ� �����ɱ�
			MapArray[0][j] = 8;
			MapArray[STANDARD_COL - 1][j] = 8;

		}

		//�����ɱ� 2
		MapArray[i][0] = 8;
		MapArray[i][STANDARD_ROW - 1] = 8;
	}

	//���� 3��
	for (int i = 2; i < STANDARD_COL - 2; i++) {
		MapArray[i][2] = 4;
		MapArray[i][5] = 4;
		MapArray[i][8] = 4;
	}

	//���� 4��
	MapArray[STANDARD_COL - 3][3] = 4;
	MapArray[STANDARD_COL - 3][4] = 4;
	MapArray[2][6] = 4;
	MapArray[2][7] = 4;
	//

	//������&������
	MapArray[2][2] = ENEMY_START_TILEID;
	MapArray[STANDARD_COL-3][STANDARD_ROW-3] = ENEMY_END_TILEID;

	//Map�� Standard Map ������ ����.
	Map->setEachTileID(MapArray);
	//-----------------------------------------------------
}



BOOL StartMenuView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	return CFormView::PreTranslateMessage(pMsg);
}


BOOL StartMenuView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return TRUE;

	//return CFormView::OnEraseBkgnd(pDC);
}



void StartMenuView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	if(FocusMenu->PointOverMenu(point)!=-1) {
		FocusMenu->Setting.SetCursorClick();
		FocusMenu->setFocus(FocusMenu->PointOverMenu(point));
		Invalidate();
	}
	else {
		FocusMenu->Setting.SetCursorNormal();
	}

	CFormView::OnMouseMove(nFlags, point);
}


void StartMenuView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	//���� ������ Menu�� ���ԵǴ� ���.
	if (FocusMenu->PointOverMenu(point) != -1) {
		//Ÿ��Ʋ �޴��� ������ ���
		if (FocusMenu == TitleMenu) {
			switch (FocusMenu->PointOverMenu(point)) {
				//Game Start�� �������
			case 0:
				FocusMenu->HideMenuList();
				DifficultyMenu->ShowMenuList();
				FocusMenu = DifficultyMenu;
				break;

				//Game Load�� ���� ���
			case 1:
				FocusMenu->HideMenuList();
				LoadDataMenu->ShowMenuList();
				FocusMenu = LoadDataMenu;
				break;

				//Map Edit�� ���� ���
			case 2:
				FocusMenu->HideMenuList();
				EditDataMenu->ShowMenuList();
				FocusMenu = EditDataMenu;
				break;

				//Option�� ���� ���
			case 3:
				FocusMenu->HideMenuList();
				OptionMenu->ShowMenuList();
				FocusMenu = OptionMenu;
				break;

				//Exit�� ���� ���
			case 4:
				if (MessageBox(L"���� ������ �����Ͻðڽ��ϱ�?", L"Ȯ��", MB_YESNO) == IDYES) {
					AfxGetMainWnd()->PostMessageW(WM_COMMAND, ID_APP_EXIT, 0);
				}
				break;
			}
		}
		//Ŭ���� �޴��� DifficultyMenu�� ���.
		else if (FocusMenu == DifficultyMenu) {
			switch (FocusMenu->PointOverMenu(point)) {
				//Easy ����
			case 0: 
			{
				LoadMap();
				FocusMenu->HideMenuList();
				::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_GAMEVIEW, 0);
				break;
			}
				//Normal ����
			case 1:
				LoadMap();
				FocusMenu->HideMenuList();
				::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_GAMEVIEW, 1);
				break;


				//Hard ����
			case 2:
				LoadMap();
				FocusMenu->HideMenuList();
				::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_GAMEVIEW, 2);
				break;


				//Impossible ����
			case 3:
				LoadMap();
				FocusMenu->HideMenuList();
				::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_GAMEVIEW, 3);
				break;

			//Title�� ���ƿ���
			case 4:
				FocusMenu->HideMenuList();
				TitleMenu->ShowMenuList();
				FocusMenu = TitleMenu;
				break;
			}
			FocusMenu->Setting.SetCursorNormal();
		}
		//�޴��� LoadDataMenu �� ���.
		else if (FocusMenu == LoadDataMenu) {
			switch (FocusMenu->PointOverMenu(point)) {
				//�ε��� SaveData 1 ����
			case 0:
				break;
				//2 ����
			case 1:
				break;
				//3 ����
			case 2:
				break;
				//Title�� ���ƿ���
			case 3:
				FocusMenu->HideMenuList();
				TitleMenu->ShowMenuList();
				FocusMenu = TitleMenu;
				break;
			}
		}
		//�޴��� EditDataMenu �� ���.
		else if (FocusMenu == EditDataMenu) {
			switch (FocusMenu->PointOverMenu(point)) {
				//Edit New Map ����
			case 0:
				::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_EDITVIEW, 0);
				FocusMenu->Setting.SetCursorNormal();
				break;

				//����Ʈ �� �� �ε� ����
			case 1:
				LoadMap();
				::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_EDITVIEW, 0);
				FocusMenu->Setting.SetCursorNormal();
				break;

				//Title�� ���ƿ���
			case 2:
				FocusMenu->HideMenuList();
				TitleMenu->ShowMenuList();
				FocusMenu = TitleMenu;
				break;
			}
		}
		//�޴��� OptionMenu �� ���.
		else if (FocusMenu == OptionMenu) {
			switch (FocusMenu->PointOverMenu(point)) {
				//�ػ� ����
			case 0:
				break;
				//Ǯ��ũ�� ���� ����
			case 1:
				break;
				//Title�� ���ƿ���
			case 2:
				FocusMenu->HideMenuList();
				TitleMenu->ShowMenuList();
				FocusMenu = TitleMenu;
				break;
			}
		}
	}
	Invalidate();
	//CFormView::OnLButtonDown(nFlags, point);
}



void StartMenuView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	delete(GameTitle);
	delete(TitleMenu);
	delete(DifficultyMenu);
	delete(LoadDataMenu);
	delete(EditDataMenu);
	delete(OptionMenu);
}

void StartMenuView::LoadMap()
{
	CString str = _T("Map files(*.tmap)|*.tmap|");
	CFileDialog dlg(TRUE, NULL, NULL, OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);
	if (dlg.DoModal() == IDOK)
	{
		CString fileName = dlg.GetFileTitle();

		CFile Rfile;
		CFileException e;

		if (!Rfile.Open(dlg.GetPathName(), CFile::modeRead)) {
			MessageBox(L"tmap������ �ƴ� �� �����ϴ�.. ������ ���׿�!", L"Warning", MB_OK | MB_ICONHAND);
			return;
		}

		UINT FileLength = (UINT)Rfile.GetLength();

		char* ps = new char[FileLength];
		char* ps2 = ps;
		Rfile.Read(ps, FileLength);
		Rfile.Close();

		//ps���� �ҷ��� ������ ��� �ִ�. 
		//ps�� �̿��� tempArray��  tileID�� �����Ѵ�.
		vector<int> tempArray(Map->getAllTileNum());

		//�׽�Ʈ�� ����� ���� ���
		if (*ps2 == 1) {
			*ps2++;
			*ps2++;
		}
		//�ƴ� ���
		else {
			//���õȰ� ���ӽ��� �޴��� ���
			if (FocusMenu == DifficultyMenu) {
				MessageBox(L"�׽�Ʈ�� ������� ���� ���� �ҷ��Խ��ϴ�. �⺻ ������ �����մϴ�.");
				return;
			}
			else if (FocusMenu == EditDataMenu) {
				*ps2++;
				*ps2++;
				MessageBox(L"�׽�Ʈ�� ������� ���� ���� �ҷ��Խ��ϴ�. �� ���� �׽�Ʈ�� ����ؾ� ���� ���ӿ��� ����� �� �ֽ��ϴ�.");
			}
		}

		for (int i = 0; i < Map->getAllTileNum(); i++) {
			if (*ps2 == ' ') {
				*ps2++;
			}
			tempArray[i] = *ps2++ - '!';
		}
		Map->setEachTileID(tempArray);
		Map->MapName = fileName;
		//

		delete[] ps;
	}
	else {
		MessageBox(L"�� �ε带 ����Ͽ����ϴ�. �⺻ ������ �����մϴ�.");
	}
}
