// EditView.cpp : ���� �����Դϴ�.
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


// EditView �����Դϴ�.

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


// EditView �޽��� ó�����Դϴ�.

UINT EditView::TestThread(LPVOID _mothod)
{
	EditView *pEdit = (EditView*)_mothod;
	static int TimerCall = 50;
	static int SLEEP_TIME = 1000 / FRAME_PER_SECOND;
	TRACE("TestThread�� ���۵Ǿ����ϴ�.\n");

	while (pEdit->isNowOnTest) {
		//Thread ���� �� �Լ� ����
		TimerCall++;
		pEdit->testEnemySet.MoveAllEnemy();
		pEdit->Invalidate();

		if (TimerCall > 50) {
			pEdit->testEnemySet.spawnEnemy(10, 0, 3, 1);
			TimerCall = 0;
		}

		Sleep(SLEEP_TIME);
	}
	TRACE("TestThread�� ����Ǿ����ϴ�.\n");
	return 0;
}

void EditView::OnDraw(CDC* /*pDC*/)
{
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
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
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
	mem.FillRectangle(&brush, 0, 0, rlClientRect.Width(), rlClientRect.Height());

	//�����ʺκ�
	brush.SetColor(Gdiplus::Color(255, 105, 105, 105));
	mem.FillRectangle(&brush, 1100, 10, 170, rlClientRect.Height() - 20);

	//������ ������ �κ�
	brush.SetColor(Gdiplus::Color(255, 105, 105, 105));
	mem.FillRectangle(&brush, 10, 10, 1080, 530);

	//�Ʒ��ʺκ�
	brush.SetColor(Gdiplus::Color(255, 105, 105, 105));
	mem.FillRectangle(&brush, 10, 550, 1080, 97);

	/////////�������� MemDC�� ���� Write ����
	//Draw Codes go Here.
	InfoDraw(&MemDC);
	///////////////////

	dc.BitBlt(0, 0, rlClientRect.right, rlClientRect.bottom, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBitmap);
	mem.ReleaseHDC(dc.m_hDC);

}

//�׸��� ����
void EditView::InfoDraw(CDC* pDC) {
	GameViewMenuUI.DrawAllViewUI(pDC);	//Menu UI�� ��� �׸���.	
	Map->drawTileSet(pDC);	//�׷��� ���� �׸���.
	EditMap->drawTileSet(pDC);	//���õ� Ÿ�� ����� �׸���.
	if (testEnemySet.getEnemyNum()) { testEnemySet.drawAllEnemy(pDC); }	//�׽�Ʈ�� ���� �׸���.
	if(!isNowOnTest)sTile.drawTile(&TileSetIMG, pDC);	//���콺 �����͸� ����ٴϴ� ���� �׸���.
	msgUI->drawAllMenu(pDC);
}



void EditView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();

	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.

	//������� �ʱ�ȭ--
	isTestCleared = FALSE;
	isNowOnTest = FALSE;
	DrawUI.SetImage(&TileSetIMG, IDB_TILESET, L"PNG");	//Resource TileSet�� TileSetIMG�� �ʱ�ȭ


	//UI Menu ����-----------------------------------------------------------

	//�� �̸� UI
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
	msgUI->addMsg(L"�̰����� �� ������ �� �� �ֽ��ϴ�.");

	//���� �����ϱ� ���� Ÿ�� ���� ����
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

	//Ÿ�� ������ ǥ���ϴ� UI ����
	TileInfoUI = new menuSet(1, 3, 1110, 435, 150, 200, TRUE, TRUE);
	TileInfoUI->setMenuTitle(14, L"Tile Information", 15, L"Corbel", 180, 220, 255);
	TileInfoUI->setEach(0, 0, L"�Ǽ� ���� : ", 12, L"���ʷҵ���", 255, 240, 240);
	TileInfoUI->setEach(0, 1, L"�� �̵� ���� : ", 12, L"���ʷҵ���", 255, 240, 240);
	TileInfoUI->setEach(0, 2, L"���� : ", 12, L"���ʷҵ���", 255, 240, 240);
	//

	//������ ������ Ÿ���� ǥ���ϱ� ���� ������ tile ����.
	sTile.setSize(46, 46);
	sTile.setTileID(1);
	//

	//������ �̹� ������ menuSet�� ����Ʈ�� ����ִ´�.
	GameViewMenuUI.addMenu(MapnameUI);
	GameViewMenuUI.addMenu(SaveUI);
	GameViewMenuUI.addMenu(LoadUI);
	GameViewMenuUI.addMenu(HelpUI);
	GameViewMenuUI.addMenu(OptionUI);
	GameViewMenuUI.addMenu(SettingMapUI);
	GameViewMenuUI.addMenu(TileSetUI);
	GameViewMenuUI.addMenu(TileInfoUI);
	//List �����Ϸ�.-------------------------------------------------------------

	//Cursor ���¸� ����. �⺻ Normal
	CursorState = CURSORNORMAL;
}


//���콺 �̵� �� �̺�Ʈ
void EditView::OnMouseMove(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

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

	//���õ� Tile�� �����δ�. (�װ��� ���� Map ���ζ��)
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


//���콺 Ŭ�� �� �̺�Ʈ
void EditView::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.

	if(!isNowOnTest)
	{
		//���� ���õ� Ÿ�� ����
		if (EditMap->isInTile(point)) {
			sTile.setTileID(EditMap->ftile->getTileID());
			msgUI->addMsg(L"���õ� Ÿ���� �����߽��ϴ�.");
			
			//�Ǽ� ���θ� UI�� ǥ��
			if (sTile.isBuildable()) {			
				TileInfoUI->setEach(0, 0, L"�Ǽ� ���� : Ÿ�� �Ǽ� ����");
			}
			else {
				TileInfoUI->setEach(0, 0, L"�Ǽ� ���� : Ÿ�� �Ǽ� �Ұ���");
			}

			//�� �̵� ���θ� UI�� ǥ��
			if (sTile.isWalkable(NULL)) {
				TileInfoUI->setEach(0, 1, L"�� �̵� ���� : �� �̵� ����");
			}
			else {
				TileInfoUI->setEach(0, 1, L"�� �̵� ���� : �� �̵� �Ұ���");
			}

			//������ ǥ��
			switch (sTile.getTileID()) {
			case 0:
				TileInfoUI->setEach(0, 2, L"���� : �̹� ���̶�� �θ��⵵ ����..");
				break;
			case 1:
				TileInfoUI->setEach(0, 2, L"���� : �׵θ��� Ǯ�� �ڶ� �ִ� ���� ���붥.");
				break;
			case 2:
				TileInfoUI->setEach(0, 2, L"���� : �׵θ��� Ǯ�� �ڶ� ���� ���붥");
				break;
			case 3:
				TileInfoUI->setEach(0, 2, L"���� : �ʷϻ� Ǯ���� �� ���ִ� ��.");
				break;
			case 4:
				TileInfoUI->setEach(0, 2, L"���� : ���� ��.");
				break;
			case 5:
				TileInfoUI->setEach(0, 2, L"���� : �� �� ���� Ǯ���� �ڶ� ��.");
				break;
			case 6:
				TileInfoUI->setEach(0, 2, L"���� : ������. �ݵ�� �Ѱ��� ��ġ����.");
				break;
			case 7:
				TileInfoUI->setEach(0, 2, L"���� : ������. �ݵ�� �Ѱ��� ��ġ����.");
				break;
			}

			Invalidate();
		}

		//�� ����
		if (Map->isInTile(point)) {
			if (Map->ftile->getTileID() != 8) {
				Map->ftile->setTileID(sTile.getTileID());
				CRect rect(point.x - 23, point.y - 23, point.x + 23, point.y + 23);
				InvalidateRect(rect);
			}
		}
	}


	if (SaveUI->isInMenu(point)) {
		//Save ��ư ���� ��
		if (SaveUI->FocusedMenu->isIndex(0, 0)) {
			msgUI->addMsg(L"Save�� �����մϴ�.");
			
			CString str = _T("Map files(*.tmap)|*.tmap|");
			CFileDialog dlg(FALSE, L"tmap", L"", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, str, this);

			if (dlg.DoModal() == IDOK) {
				CFile wfile;
				CFileException e;
				if (!wfile.Open(dlg.GetPathName(), CFile::modeCreate | CFile::modeWrite, &e)) {
					AfxMessageBox(L"Save�� �����Ͽ����ϴ� : " + e.m_cause);
					return;
				}
				//ps�� �����͸� ��´�.
				char* ps = new char[(Map->getAllTileNum()) * 2 + 1];
				char* ps2 = ps;

				//�ӽ÷� tileID ����� vector int ����
				vector<int> tempSaveData = Map->getTileSetArray();

				if (isTestCleared) {
					*ps2++ = 1;
					*ps2++ = ' ';
					msgUI->addMsg(L"�׽�Ʈ�� ����� ���� �����߽��ϴ�.");
				}
				else {
					*ps2++ = 0;
					*ps2++ = ' ';
					msgUI->addMsg(L"�׽�Ʈ�� ������� ���� ���� �����߽��ϴ�.");
				}
				

				for (int i = 0; i < Map->getAllTileNum(); i++) {
					*ps2++ = tempSaveData[i] + '!';
					*ps2++ = ' ';
				}
				*ps2 = NULL;
				wfile.Write(ps, Map->getAllTileNum() * 2 + 1);
				wfile.Close();
				delete[] ps;

				msgUI->addMsg(L"���̺꿡 �����߽��ϴ�.");
			}
			else {
				msgUI->addMsg(L"���̺긦 ����߽��ϴ�.");
				return;
			}
		}
	}

	if (LoadUI->isInMenu(point)) {
		//Load ��ư ���� ��
		if (LoadUI->FocusedMenu->isIndex(0, 0)) {

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

				if (*ps2 == 1) {
					msgUI->addMsg(L"�׽�Ʈ�� �̹� ����� ���� �ҷ��ɴϴ�.");
					isTestCleared = TRUE;
					*ps2++;
					*ps2++;
				}
				else {
					msgUI->addMsg(L"�׽�Ʈ�� ������� ���� ���� �ҷ��ɴϴ�.");
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
				msgUI->addMsg(L"�ε忡 �����߽��ϴ�.");
				MapnameUI->setEach(0, 0, fileName);
			}
			else {
				msgUI->addMsg(L"�ε带 ����߽��ϴ�.");
				return;
			}
		}
	}

	if (HelpUI->isInMenu(point)) {
		//Help ��ư ���� ��
		if (HelpUI->FocusedMenu->isIndex(0, 0)) {
			if (!isNowOnTest) {
				EditHelpDlg dlg;
				dlg.DoModal();
			}
			else {
				msgUI->addMsg(L"���� �׽�Ʈ���̶� �� �� �����ϴ�.");
			}

		}
	}

	if (OptionUI->isInMenu(point)) {
		//Option ��ư ���� ��
		if (OptionUI->FocusedMenu->isIndex(0, 0)) {
			if (!isNowOnTest) {
				EditOptionDlg dlg;
				if (dlg.DoModal() == IDOK) {
					::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_STARTMENUVIEW, 0);
				}
			}
			else {
				msgUI->addMsg(L"���� �׽�Ʈ���̶� �� �� �����ϴ�.");
			}
		}
	}

	//MapTest Start ��ư ���� ��
	if (SettingMapUI->isInMenu(point)) {		
		//���� �׽�Ʈ ���� �ƴ� ��츸
		
		if (SettingMapUI->FocusedMenu->isIndex(0, 0)) {
			if (!isNowOnTest) {
				msgUI->addMsg(L"���� ������ ��밡������ �׽�Ʈ ����.");
				if (!Map) {
					msgUI->addMsg(L"Error! ���� �ҷ��� �� �����ϴ�.");
				}
				else {
					if (Map->isCanAvailableSave()) {
						testEnemySet.setStartPos(Map);
						testEnemySet.setEndPos(Map);
						testEnemySet.setViewPointer(this);
						isNowOnTest = TRUE;

						//�������� ����
						pWinThread = NULL;
						pWinThread = AfxBeginThread(TestThread, this);

						if (pWinThread == NULL) {
							AfxMessageBox(L"Thread ������ �����߽��ϴ�.");
						}

					}
					else {
						MessageBox(L"���� �׽�Ʈ �� �� �����ϴ�! �������� ������� �ݵ�� �Ѱ��� ��ġ�Ǿ�� �ϰ�, ���� �����θ� ������ ���� �� �׽�Ʈ�� �����մϴ�.");
						return;
					}
				}
			}
			else {
				msgUI->addMsg(L"�׽�Ʈ�� �����մϴ�.");
				testEnemySet.RemoveAllEnemy();
				isNowOnTest = FALSE;
			}
		}

		//Reset ��ư ���� ��
		if (SettingMapUI->FocusedMenu->isIndex(0, 1)) {
			MessageBox(L"Ÿ�ϼ��� �ʱ���·� �ǵ����ϴ�.");

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

			//Map�� Standard Map ������ ����.
			Map->setEachTileID(MapArray);
			//-----------------------------------------------------
		}
	}



	CFormView::OnLButtonDown(nFlags, point);
}


BOOL EditView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return FALSE;
	// return CFormView::OnEraseBkgnd(pDC);
}


void EditView::OnDestroy()
{
	CFormView::OnDestroy();
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.

	GameViewMenuUI.deleteAllpMenu();
	delete(EditMap);
	delete(msgUI);
}