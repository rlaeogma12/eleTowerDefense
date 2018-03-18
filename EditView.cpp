// EditView.cpp : 구현 파일입니다.
//

#include "stdafx.h"
#include "TileEx.h"
#include "EditView.h"


// EditView

IMPLEMENT_DYNCREATE(EditView, CFormView)

EditView::EditView()
	: CFormView(IDD_EDITVIEW)
{

}

EditView::~EditView()
{
}

void EditView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(EditView, CFormView)
	ON_WM_MOUSEMOVE()
	ON_WM_LBUTTONDOWN()
	ON_WM_ERASEBKGND()
	ON_WM_DESTROY()
END_MESSAGE_MAP()


// EditView 진단입니다.

#ifdef _DEBUG
void EditView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void EditView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// EditView 메시지 처리기입니다.

UINT EditView::TestThread(LPVOID _mothod)
{
	EditView *pEdit = (EditView*)_mothod;
	static int TimerCall = 50;
	static int SLEEP_TIME = 1000 / FRAME_PER_SECOND;
	TRACE("TestThread가 시작되었습니다.\n");

	while (pEdit->isNowOnTest) {
		//Thread 동작 시 함수 구현
		TimerCall++;
		pEdit->testEnemySet.MoveAllEnemy();
		pEdit->Invalidate();

		if (TimerCall > 50) {
			pEdit->testEnemySet.spawnEnemy(10, 0, 3, 1);
			TimerCall = 0;
		}

		Sleep(SLEEP_TIME);
	}
	TRACE("TestThread가 종료되었습니다.\n");
	return 0;
}

void EditView::OnDraw(CDC* /*pDC*/)
{
	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.
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
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
	mem.FillRectangle(&brush, 0, 0, rlClientRect.Width(), rlClientRect.Height());

	//오른쪽부분
	brush.SetColor(Gdiplus::Color(255, 105, 105, 105));
	mem.FillRectangle(&brush, 1100, 10, 170, rlClientRect.Height() - 20);

	//게임이 보여질 부분
	brush.SetColor(Gdiplus::Color(255, 105, 105, 105));
	mem.FillRectangle(&brush, 10, 10, 1080, 530);

	//아래쪽부분
	brush.SetColor(Gdiplus::Color(255, 105, 105, 105));
	mem.FillRectangle(&brush, 10, 550, 1080, 97);

	/////////실질적인 MemDC를 통한 Write 과정
	//Draw Codes go Here.
	InfoDraw(&MemDC);
	///////////////////

	dc.BitBlt(0, 0, rlClientRect.right, rlClientRect.bottom, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBitmap);
	mem.ReleaseHDC(dc.m_hDC);

}

//그리기 구현
void EditView::InfoDraw(CDC* pDC) {
	GameViewMenuUI.DrawAllViewUI(pDC);	//Menu UI를 모두 그린다.	
	Map->drawTileSet(pDC);	//그려질 맵을 그린다.
	EditMap->drawTileSet(pDC);	//선택될 타일 목록을 그린다.
	if (testEnemySet.getEnemyNum()) { testEnemySet.drawAllEnemy(pDC); }	//테스트용 적을 그린다.
	if(!isNowOnTest)sTile.drawTile(&TileSetIMG, pDC);	//마우스 포인터를 따라다니는 것을 그린다.
	msgUI->drawAllMenu(pDC);
}



void EditView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: 여기에 특수화된 코드를 추가 및/또는 기본 클래스를 호출합니다.

	//멤버변수 초기화--
	isTestCleared = FALSE;
	isNowOnTest = FALSE;
	DrawUI.SetImage(&TileSetIMG, IDB_TILESET, L"PNG");	//Resource TileSet을 TileSetIMG로 초기화


	//UI Menu 구현-----------------------------------------------------------

	//맵 이름 UI
	MapnameUI = new menuSet(1, 1, 20, 560, 200, 80, TRUE, TRUE);
	MapnameUI->setMenuTitle(15, L"Map Name", 15, L"Corbel", 200, 230, 255);
	MapnameUI->setEach(0, 0, L"Standard Map", 15, L"Corbel", 255, 240, 240, TRUE);

	//Save UI
	SaveUI = new menuSet(1, 1, 230, 560, 120, 80, TRUE, TRUE);
	SaveUI->setMenuTitle(15, L"Save Map", 15, L"Corbel", 0, 220, 200);
	SaveUI->setMenuSetting(TRUE, FALSE, TRUE);
	SaveUI->setEach(0, 0, IDB_SAVE, 32, 32, TRUE);

	//Load UI
	LoadUI = new menuSet(1, 1, 360, 560, 120, 80, TRUE, TRUE);
	LoadUI->setMenuTitle(15, L"Load Map", 15, L"Corbel", 0, 220, 200);
	LoadUI->setMenuSetting(TRUE, FALSE, TRUE);
	LoadUI->setEach(0, 0, IDB_LOAD, 32, 32, TRUE);

	//Help UI
	HelpUI = new menuSet(1, 1, 490, 560, 120, 80, TRUE, TRUE);
	HelpUI->setMenuTitle(15, L"Help", 15, L"Corbel", 0, 220, 200);
	HelpUI->setMenuSetting(TRUE, FALSE, TRUE);
	HelpUI->setEach(0, 0, IDB_QUESTION, 32, 32, TRUE);

	//Option UI
	OptionUI = new menuSet(1, 1, 620, 560, 120, 80, TRUE, TRUE);
	OptionUI->setMenuTitle(15, L"Option", 15, L"Corbel", 0, 220, 200);
	OptionUI->setMenuSetting(TRUE, FALSE, TRUE);
	OptionUI->setEach(0, 0, IDB_OPTION, 32, 32, TRUE);

	//SettingUI
	SettingMapUI = new menuSet(2, 1, 750, 560, 120, 80, TRUE, TRUE);
	SettingMapUI->setMenuTitle(15, L"Setting", 15, L"Corbel", 150, 220, 150);
	SettingMapUI->setMenuSetting(TRUE, FALSE, TRUE);
	SettingMapUI->setEach(0, 0, IDB_TESTSTART, 32, 32, TRUE);
	SettingMapUI->setEach(1, 0, IDB_RESET, 32, 32, TRUE);

	//MsgBox UI
	msgUI = new msgBox(0, 4, 880, 560, 200, 80, TRUE, TRUE);
	msgUI->addMsg(L"이곳에서 맵 제작을 할 수 있습니다.");

	//맵을 제작하기 위한 타일 종류 나열
	TileSetUI = new menuSet(2, 6, 1110, 20, 150, 400, TRUE, TRUE);
	TileSetUI->setMenuSetting(TRUE, FALSE, TRUE);
	TileSetUI->setMenuTitle(15, L"Tile List", 15, L"Corbel", 200, 230, 255);

	int tilecolNum = 2;
	int tilerowNum = 4;
	EditMap = new tileSet(tilecolNum, tilerowNum, 1140, 40, 46, 46, IDB_TILESET);
	vector<vector<int> > MapUIArray;

	for (int i = 0; i < tilecolNum; i++) {
		vector<int> elem;
		elem.resize(tilerowNum);
		MapUIArray.push_back(elem);
	}
	for (int i = 0; i < tilecolNum; i++) {
		for (int j = 0; j < tilerowNum; j++) {
			MapUIArray[i][j] = i + j * 2;
		}
	}
	EditMap->setEachTileID(MapUIArray);

	//타일 정보를 표시하는 UI 생성
	TileInfoUI = new menuSet(1, 3, 1110, 435, 150, 200, TRUE, TRUE);
	TileInfoUI->setMenuTitle(14, L"Tile Information", 15, L"Corbel", 180, 220, 255);
	TileInfoUI->setEach(0, 0, L"건설 여부 : ", 12, L"함초롬돋움", 255, 240, 240);
	TileInfoUI->setEach(0, 1, L"적 이동 여부 : ", 12, L"함초롬돋움", 255, 240, 240);
	TileInfoUI->setEach(0, 2, L"설명 : ", 12, L"함초롬돋움", 255, 240, 240);
	//

	//유저가 선택한 타일을 표시하기 위한 유일한 tile 생성.
	sTile.setSize(46, 46);
	sTile.setTileID(1);
	//

	//기존에 이미 생성한 menuSet을 리스트에 집어넣는다.
	GameViewMenuUI.addMenu(MapnameUI);
	GameViewMenuUI.addMenu(SaveUI);
	GameViewMenuUI.addMenu(LoadUI);
	GameViewMenuUI.addMenu(HelpUI);
	GameViewMenuUI.addMenu(OptionUI);
	GameViewMenuUI.addMenu(SettingMapUI);
	GameViewMenuUI.addMenu(TileSetUI);
	GameViewMenuUI.addMenu(TileInfoUI);
	//List 생성완료.-------------------------------------------------------------

	//Cursor 상태를 정의. 기본 Normal
	CursorState = CURSORNORMAL;
}


//마우스 이동 시 이벤트
void EditView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if (GameViewMenuUI.isInUI(point)) {
if (CursorState == CURSORNORMAL) {
	DrawUI.SetCursorClick();
	CursorState = CURSORCLICK;
}
	}
	else {
		if (CursorState == CURSORCLICK) {
			DrawUI.SetCursorNormal();
			CursorState = CURSORNORMAL;
		}
	}

	//선택된 Tile을 움직인다. (그것이 만약 Map 내부라면)
	if (!isNowOnTest)
	{	
		if (Map->getTileSetRect().PtInRect(point)) {
			sTile.setPos(point.x - 23, point.y - 23);
			CRect rect(point.x - 23, point.y - 23, point.x + 23, point.y + 23);
			InvalidateRect(rect);
		}
	}

	CFormView::OnMouseMove(nFlags, point);
}


//마우스 클릭 시 이벤트
void EditView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.

	if(!isNowOnTest)
	{
		//현재 선택된 타일 변경
		if (EditMap->isInTile(point)) {
			sTile.setTileID(EditMap->ftile->getTileID());
			msgUI->addMsg(L"선택된 타일을 변경했습니다.");
			
			//건설 여부를 UI에 표시
			if (sTile.isBuildable()) {			
				TileInfoUI->setEach(0, 0, L"건설 여부 : 타워 건설 가능");
			}
			else {
				TileInfoUI->setEach(0, 0, L"건설 여부 : 타워 건설 불가능");
			}

			//적 이동 여부를 UI에 표시
			if (sTile.isWalkable(NULL)) {
				TileInfoUI->setEach(0, 1, L"적 이동 여부 : 적 이동 가능");
			}
			else {
				TileInfoUI->setEach(0, 1, L"적 이동 여부 : 적 이동 불가능");
			}

			//설명을 표시
			switch (sTile.getTileID()) {
			case 0:
				TileInfoUI->setEach(0, 2, L"설명 : 이미 땅이라고 부르기도 힘든..");
				break;
			case 1:
				TileInfoUI->setEach(0, 2, L"설명 : 테두리에 풀이 자라 있는 밝은 진흙땅.");
				break;
			case 2:
				TileInfoUI->setEach(0, 2, L"설명 : 테두리에 풀이 자란 검은 진흙땅");
				break;
			case 3:
				TileInfoUI->setEach(0, 2, L"설명 : 초록색 풀들이 꽉 차있는 땅.");
				break;
			case 4:
				TileInfoUI->setEach(0, 2, L"설명 : 밝은 땅.");
				break;
			case 5:
				TileInfoUI->setEach(0, 2, L"설명 : 좀 더 밝은 풀들이 자란 땅.");
				break;
			case 6:
				TileInfoUI->setEach(0, 2, L"설명 : 시작점. 반드시 한개는 배치하자.");
				break;
			case 7:
				TileInfoUI->setEach(0, 2, L"설명 : 도착점. 반드시 한개는 배치하자.");
				break;
			}

			Invalidate();
		}

		//맵 변경
		if (Map->isInTile(point)) {
			if (Map->ftile->getTileID() != 8) {
				Map->ftile->setTileID(sTile.getTileID());
				CRect rect(point.x - 23, point.y - 23, point.x + 23, point.y + 23);
				InvalidateRect(rect);
			}
		}
	}


	if (SaveUI->isInMenu(point)) {
		//Save 버튼 누를 시
		if (SaveUI->FocusedMenu->isIndex(0, 0)) {
			msgUI->addMsg(L"Save를 시작합니다.");
			
			CString str = _T("Map files(*.tmap)|*.tmap|");
			CFileDialog dlg(FALSE, L"tmap", L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

			if (dlg.DoModal() == IDOK) {
				CFile wfile;
				CFileException e;
				if (!wfile.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite, &e)) {
					AfxMessageBox(L"Save에 실패하였습니다 : " + e.m_cause);
					return;
				}
				//ps에 데이터를 담는다.
				char* ps = new char[(Map->getAllTileNum()) * 2 + 1];
				char* ps2 = ps;

				//임시로 tileID 저장용 vector int 생성
				vector<int> tempSaveData = Map->getTileSetArray();

				if (isTestCleared) {
					*ps2++ = 1;
					*ps2++ = ' ';
					msgUI->addMsg(L"테스트에 통과한 맵을 저장했습니다.");
				}
				else {
					*ps2++ = 0;
					*ps2++ = ' ';
					msgUI->addMsg(L"테스트에 통과하지 못한 맵을 저장했습니다.");
				}
				

				for (int i = 0; i < Map->getAllTileNum(); i++) {
					*ps2++ = tempSaveData[i] + '!';
					*ps2++ = ' ';
				}
				*ps2 = NULL;
				wfile.Write(ps, Map->getAllTileNum() * 2 + 1);
				wfile.Close();
				delete[] ps;

				msgUI->addMsg(L"세이브에 성공했습니다.");
			}
			else {
				msgUI->addMsg(L"세이브를 취소했습니다.");
				return;
			}
		}
	}

	if (LoadUI->isInMenu(point)) {
		//Load 버튼 누를 시
		if (LoadUI->FocusedMenu->isIndex(0, 0)) {

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

				if (*ps2 == 1) {
					msgUI->addMsg(L"테스트를 이미 통과한 맵을 불러옵니다.");
					isTestCleared = TRUE;
					*ps2++;
					*ps2++;
				}
				else {
					msgUI->addMsg(L"테스트를 통과하지 못한 맵을 불러옵니다.");
					isTestCleared = FALSE;
					*ps2++;
					*ps2++;
				}
				
				for (int i = 0; i < Map->getAllTileNum(); i++) {
					if (*ps2 == ' ') {
						*ps2++;
					}
					tempArray[i] = *ps2++ - '!';
				}
				Map->setEachTileID(tempArray);
				//

				delete[] ps;
				msgUI->addMsg(L"로드에 성공했습니다.");
				MapnameUI->setEach(0, 0, fileName);
			}
			else {
				msgUI->addMsg(L"로드를 취소했습니다.");
				return;
			}
		}
	}

	if (HelpUI->isInMenu(point)) {
		//Help 버튼 누를 시
		if (HelpUI->FocusedMenu->isIndex(0, 0)) {
			if (!isNowOnTest) {
				EditHelpDlg dlg;
				dlg.DoModal();
			}
			else {
				msgUI->addMsg(L"현재 테스트중이라 열 수 없습니다.");
			}

		}
	}

	if (OptionUI->isInMenu(point)) {
		//Option 버튼 누를 시
		if (OptionUI->FocusedMenu->isIndex(0, 0)) {
			if (!isNowOnTest) {
				EditOptionDlg dlg;
				if (dlg.DoModal() == IDOK) {
					::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_STARTMENUVIEW, 0);
				}
			}
			else {
				msgUI->addMsg(L"현재 테스트중이라 열 수 없습니다.");
			}
		}
	}

	//MapTest Start 버튼 누를 시
	if (SettingMapUI->isInMenu(point)) {		
		//현재 테스트 중이 아닐 경우만
		
		if (SettingMapUI->FocusedMenu->isIndex(0, 0)) {
			if (!isNowOnTest) {
				msgUI->addMsg(L"맵이 실제로 사용가능한지 테스트 시작.");
				if (!Map) {
					msgUI->addMsg(L"Error! 맵을 불러올 수 없습니다.");
				}
				else {
					if (Map->isCanAvailableSave()) {
						testEnemySet.setStartPos(Map);
						testEnemySet.setEndPos(Map);
						testEnemySet.setViewPointer(this);
						isNowOnTest = TRUE;

						//쓰레드의 실행
						pWinThread = NULL;
						pWinThread = AfxBeginThread(TestThread, this);

						if (pWinThread == NULL) {
							AfxMessageBox(L"Thread 생성에 실패했습니다.");
						}

					}
					else {
						MessageBox(L"맵을 테스트 할 수 없습니다! 시작점과 출발점은 반드시 한개만 배치되어야 하고, 길이 교차로를 가지지 않을 때 테스트가 가능합니다.");
						return;
					}
				}
			}
			else {
				msgUI->addMsg(L"테스트를 중지합니다.");
				testEnemySet.RemoveAllEnemy();
				isNowOnTest = FALSE;
			}
		}

		//Reset 버튼 누를 시
		if (SettingMapUI->FocusedMenu->isIndex(0, 1)) {
			MessageBox(L"타일셋을 초기상태로 되돌립니다.");

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

			//Map에 Standard Map 데이터 삽입.
			Map->setEachTileID(MapArray);
			//-----------------------------------------------------
		}
	}



	CFormView::OnLButtonDown(nFlags, point);
}


BOOL EditView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: 여기에 메시지 처리기 코드를 추가 및/또는 기본값을 호출합니다.
	return FALSE;
	// return CFormView::OnEraseBkgnd(pDC);
}


void EditView::OnDestroy()
{
	CFormView::OnDestroy();
	// TODO: 여기에 메시지 처리기 코드를 추가합니다.

	GameViewMenuUI.deleteAllpMenu();
	delete(EditMap);
	delete(msgUI);
}