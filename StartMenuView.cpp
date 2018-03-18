// StartMenuView.cpp : 구현 파일입니다.
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


// StartMenuView 진단입니다.

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


// StartMenuView 메시지 처리기입니다.

//스타트 메뉴를 그리는 메시지 처리
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

	// 그리기 전 bitmap 바탕을 하얗게 그려준다. (이 부분이 없으면 잔상이 남게 된다)
	Gdiplus::SolidBrush whiteBrush(Gdiplus::Color(255, 45, 45, 45));
	mem.FillRectangle(&whiteBrush, 0, 0, rlClientRect.Width(), rlClientRect.Height());

	/////////실질적인 MemDC를 통한 Write 과정

	//Color Set
	GameTitle->PrintMenuList(&MemDC);
	FocusMenu->PrintMenuList(&MemDC);	
	///////////////////

	dc.BitBlt(0, 0, rlClientRect.right, rlClientRect.bottom, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBitmap);
	mem.ReleaseHDC(dc.m_hDC);
}



///변수 초기화를 이곳에서.
void StartMenuView::OnInitialUpdate()
{
	//CFormView::OnInitialUpdate();
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//Title에 표시되는 Text Set을 만든다.
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

	GameTitle->AddMenu_toLast(_T("2013310621 김대흠"));
	(GameTitle->getMenu())[2].setTextSize(20);
	(GameTitle->getMenu())[2].setFontColor(189, 183, 107);
	(GameTitle->getMenu())[2].setMenuRect(840, 170, 1300, 170);

	GameTitle->ShowMenuList();
	////



	//Title Menu를 만든다.
	TitleMenu = new MenuSet(550, 200, 800, 650, 5, 10, 25);

	TitleMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Start Game"));
	TitleMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Load Game"));
	TitleMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Map Edit"));
	TitleMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Option"));
	TitleMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Exit Game"));

	TitleMenu->setFocusImg(IDB_RIGHTARROW, _T("PNG"));

	TitleMenu->ShowMenuList();
	//////

	//Difficulty Menu를 만든다.
	DifficultyMenu = new MenuSet(550, 200, 800, 650, 5, 10, 25);

	DifficultyMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Easy(HP : 50%)"));
	DifficultyMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Normal(100%)"));
	DifficultyMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Hard(150%)"));
	DifficultyMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Impossible(200%)"));
	DifficultyMenu->AddMenu_toLast(IDB_SQUARE, _T("PNG"), _T("Back to Title"));

	DifficultyMenu->setFocusImg(IDB_RIGHTARROW, _T("PNG"));

	DifficultyMenu->HideMenuList();
	//////

	//Load Data Menu를 만든다.
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

	///////Focus Menu를 설정한다. 한 View에서 활성화 되는 갯수를 하나로 한정한다.
	FocusMenu = TitleMenu;
	//////	


	//유일한 맵 개체를 만듭니다.-----------------
	Map = new tileSet(STANDARD_COL, STANDARD_ROW, 20, 20, 46, 46, IDB_TILESET);

	//Standard Map을 구현(23x11 Size)
	vector<vector<int> > MapArray;
	for (int i = 0; i < STANDARD_COL; i++) {
		vector<int> elem;
		elem.resize(STANDARD_ROW);
		MapArray.push_back(elem);
	}

	for (int i = 0; i < STANDARD_COL; i++) {
		for (int j = 0; j < STANDARD_ROW; j++) {
			MapArray[i][j] = 3;

			//가장자리 나무심기
			MapArray[0][j] = 8;
			MapArray[STANDARD_COL - 1][j] = 8;

		}

		//나무심기 2
		MapArray[i][0] = 8;
		MapArray[i][STANDARD_ROW - 1] = 8;
	}

	//가로 3줄
	for (int i = 2; i < STANDARD_COL - 2; i++) {
		MapArray[i][2] = 4;
		MapArray[i][5] = 4;
		MapArray[i][8] = 4;
	}

	//세로 4개
	MapArray[STANDARD_COL - 3][3] = 4;
	MapArray[STANDARD_COL - 3][4] = 4;
	MapArray[2][6] = 4;
	MapArray[2][7] = 4;
	//

	//시작점&도착점
	MapArray[2][2] = ENEMY_START_TILEID;
	MapArray[STANDARD_COL-3][STANDARD_ROW-3] = ENEMY_END_TILEID;

	//Map에 Standard Map 데이터 삽입.
	Map->setEachTileID(MapArray);
	//-----------------------------------------------------
}



BOOL StartMenuView::PreTranslateMessage(MSG* pMsg)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	return CFormView::PreTranslateMessage(pMsg);
}


BOOL StartMenuView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return TRUE;

	//return CFormView::OnEraseBkgnd(pDC);
}



void StartMenuView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
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
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	//누른 지점이 Menu에 포함되는 경우.
	if (FocusMenu->PointOverMenu(point) != -1) {
		//타이틀 메뉴를 선택한 경우
		if (FocusMenu == TitleMenu) {
			switch (FocusMenu->PointOverMenu(point)) {
				//Game Start를 누른경우
			case 0:
				FocusMenu->HideMenuList();
				DifficultyMenu->ShowMenuList();
				FocusMenu = DifficultyMenu;
				break;

				//Game Load를 누른 경우
			case 1:
				FocusMenu->HideMenuList();
				LoadDataMenu->ShowMenuList();
				FocusMenu = LoadDataMenu;
				break;

				//Map Edit를 누른 경우
			case 2:
				FocusMenu->HideMenuList();
				EditDataMenu->ShowMenuList();
				FocusMenu = EditDataMenu;
				break;

				//Option을 누른 경우
			case 3:
				FocusMenu->HideMenuList();
				OptionMenu->ShowMenuList();
				FocusMenu = OptionMenu;
				break;

				//Exit를 누른 경우
			case 4:
				if (MessageBox(L"정말 게임을 종료하시겠습니까?", L"확인", MB_YESNO) == IDYES) {
					AfxGetMainWnd()->PostMessageW(WM_COMMAND, ID_APP_EXIT, 0);
				}
				break;
			}
		}
		//클릭한 메뉴가 DifficultyMenu인 경우.
		else if (FocusMenu == DifficultyMenu) {
			switch (FocusMenu->PointOverMenu(point)) {
				//Easy 선택
			case 0: 
			{
				LoadMap();
				FocusMenu->HideMenuList();
				::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_GAMEVIEW, 0);
				break;
			}
				//Normal 선택
			case 1:
				LoadMap();
				FocusMenu->HideMenuList();
				::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_GAMEVIEW, 1);
				break;


				//Hard 선택
			case 2:
				LoadMap();
				FocusMenu->HideMenuList();
				::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_GAMEVIEW, 2);
				break;


				//Impossible 선택
			case 3:
				LoadMap();
				FocusMenu->HideMenuList();
				::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_GAMEVIEW, 3);
				break;

			//Title로 돌아오기
			case 4:
				FocusMenu->HideMenuList();
				TitleMenu->ShowMenuList();
				FocusMenu = TitleMenu;
				break;
			}
			FocusMenu->Setting.SetCursorNormal();
		}
		//메뉴가 LoadDataMenu 인 경우.
		else if (FocusMenu == LoadDataMenu) {
			switch (FocusMenu->PointOverMenu(point)) {
				//로드할 SaveData 1 선택
			case 0:
				break;
				//2 선택
			case 1:
				break;
				//3 선택
			case 2:
				break;
				//Title로 돌아오기
			case 3:
				FocusMenu->HideMenuList();
				TitleMenu->ShowMenuList();
				FocusMenu = TitleMenu;
				break;
			}
		}
		//메뉴가 EditDataMenu 인 경우.
		else if (FocusMenu == EditDataMenu) {
			switch (FocusMenu->PointOverMenu(point)) {
				//Edit New Map 선택
			case 0:
				::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_EDITVIEW, 0);
				FocusMenu->Setting.SetCursorNormal();
				break;

				//에디트 할 맵 로드 선택
			case 1:
				LoadMap();
				::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_EDITVIEW, 0);
				FocusMenu->Setting.SetCursorNormal();
				break;

				//Title로 돌아오기
			case 2:
				FocusMenu->HideMenuList();
				TitleMenu->ShowMenuList();
				FocusMenu = TitleMenu;
				break;
			}
		}
		//메뉴가 OptionMenu 인 경우.
		else if (FocusMenu == OptionMenu) {
			switch (FocusMenu->PointOverMenu(point)) {
				//해상도 선택
			case 0:
				break;
				//풀스크린 설정 선태
			case 1:
				break;
				//Title로 돌아오기
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

	// TODO: 여기에 메시지 처리기 코드를 추가합니다.
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
			MessageBox(L"tmap파일이 아닌 것 같습니다.. 열수가 없네요!", L"Warning", MB_OK | MB_ICONHAND);
			return;
		}

		UINT FileLength = (UINT)Rfile.GetLength();

		char* ps = new char[FileLength];
		char* ps2 = ps;
		Rfile.Read(ps, FileLength);
		Rfile.Close();

		//ps에는 불러온 정보를 담고 있다. 
		//ps를 이용해 tempArray에  tileID를 설정한다.
		vector<int> tempArray(Map->getAllTileNum());

		//테스트가 통과된 맵인 경우
		if (*ps2 == 1) {
			*ps2++;
			*ps2++;
		}
		//아닌 경우
		else {
			//선택된게 게임시작 메뉴일 경우
			if (FocusMenu == DifficultyMenu) {
				MessageBox(L"테스트에 통과되지 못한 맵을 불러왔습니다. 기본 맵으로 시작합니다.");
				return;
			}
			else if (FocusMenu == EditDataMenu) {
				*ps2++;
				*ps2++;
				MessageBox(L"테스트에 통과되지 못한 맵을 불러왔습니다. 이 맵은 테스트를 통과해야 실제 게임에서 사용할 수 있습니다.");
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
		MessageBox(L"맵 로드를 취소하였습니다. 기본 맵으로 시작합니다.");
	}
}
