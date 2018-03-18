// GameView.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "TileEx.h"
#include "GameView.h"
#include "GameHelpDlg.h"
#include "GameOptionDlg.h"



// GameView

IMPLEMENT_DYNCREATE(GameView, CFormView)

GameView::GameView() : CFormView(IDD_GAMEVIEW)
{
	
}

GameView::~GameView()
{
}

void GameView::DoDataExchange(CDataExchange* pDX)
{
	CFormView::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(GameView, CFormView)
	ON_WM_ERASEBKGND()
	ON_WM_LBUTTONDOWN()
ON_WM_MOUSEMOVE()
ON_WM_DESTROY()
END_MESSAGE_MAP()


// GameView �����Դϴ�.

#ifdef _DEBUG

void GameView::AssertValid() const
{
	CFormView::AssertValid();
}

#ifndef _WIN32_WCE
void GameView::Dump(CDumpContext& dc) const
{
	CFormView::Dump(dc);
}
#endif
#endif //_DEBUG


// GameView �޽��� ó�����Դϴ�.


BOOL GameView::OnEraseBkgnd(CDC* pDC)
{
	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰� ��/�Ǵ� �⺻���� ȣ���մϴ�.
	return TRUE;
	//return CFormView::OnEraseBkgnd(pDC);
}


void GameView::OnDraw(CDC* /*pDC*/)
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
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 255, 255, 255));
	mem.FillRectangle(&brush, 0, 0, rlClientRect.Width(), rlClientRect.Height());



	//�����ʺκ�
	brush.SetColor(Gdiplus::Color(255, 105, 105, 105));
	mem.FillRectangle(&brush, 1100, 10, 170, rlClientRect.Height()-20);
	 
	//������ ������ �κ�
	brush.SetColor(Gdiplus::Color(255, 105, 105, 105));
	mem.FillRectangle(&brush, 10, 10, 1080, 530);

	//�Ʒ��ʺκ�
	brush.SetColor(Gdiplus::Color(255, 105, 105, 105));
	mem.FillRectangle(&brush, 10, 550, 1080, 97);

	/////////�������� MemDC�� ���� Write ����
	//Codes go Here.
	
	InfoDraw(&MemDC);	

	///////////////////

	dc.BitBlt(0, 0, rlClientRect.right, rlClientRect.bottom, &MemDC, 0, 0, SRCCOPY);

	MemDC.SelectObject(pOldBitmap);
	mem.ReleaseHDC(dc.m_hDC);	
}

void GameView::SetDifficulty() {
	CMainFrame* pFrame = (CMainFrame*)AfxGetMainWnd();
	Difficulty = pFrame->nDifficulty;

	switch (Difficulty) {
	case 0:
		DifficultyString = L"Game Level : Easy";
		Money = 500;
		break;
	case 1:
		DifficultyString = L"Game Level : Normal";
		for (int i = 0; i < MAX_STAGE_NUMBER; i++) {
			EnemySetting[i].HP *= 2;
		}
		Money = 1000;
		break;
	case 2:  
		DifficultyString = L"Game Level : Hard";
		for (int i = 0; i < MAX_STAGE_NUMBER; i++) {
			EnemySetting[i].HP *= 3;
		}
		Money = 2000;
		break;
	case 3:
		DifficultyString = L"Game Level : Impossible";
		for (int i = 0; i < MAX_STAGE_NUMBER; i++) {
			EnemySetting[i].HP *= 4;
		}
		Money = 3000;
		break;
	}	
}




void GameView::OnInitialUpdate()
{
	CFormView::OnInitialUpdate();
	// TODO: ���⿡ Ư��ȭ�� �ڵ带 �߰� ��/�Ǵ� �⺻ Ŭ������ ȣ���մϴ�.
	
	////�� �ܿ� ��Ÿ �ʱⰪ..
	Lives = 20;
	Score = 0;
	Interest = DEFAULT_INTEREST_RATE;
	Wave = 1;
	GameState = FALSE;
	////

	//UI �޴� ����.--------------------------------
	//MsgBox UI
	msgUI = new msgBox(0, 4, 885, 560, 200, 80, TRUE, TRUE);
	msgUI->addMsg(L"Ÿ�� ���潺�� �����մϴ�.");

	//Difficulty , Map Name UI
	LevelMap = new menuSet(1, 2, 20, 560, 200, 80);
	LevelMap->setEach(0, 0, L"Difficulty : ", 15, L"Corbel", 50, 164, 240, FALSE);
	LevelMap->setEach(0, 1, L"Map Name : ", 15, L"Corbel", 250, 250, 210, FALSE);

	MoneyInterest = new menuSet(1, 2, 230, 560, 200, 80);
	MoneyInterest->setEach(0, 0, L"Money : ", 15, L"Corbel", 255, 215, 0, FALSE);
	MoneyInterest->setEach(0, 1, L"Interest Rate : ", 15, L"Corbel", 218, 165, 32, FALSE);

	ScoreLives = new menuSet(1, 2, 440, 560, 200, 80);
	ScoreLives->setEach(0, 0, L"Score : ", 15, L"Corbel", 255, 192, 203, FALSE);
	ScoreLives->setEach(0, 1, L"Lives : ", 15, L"Corbel", 0, 255, 127, FALSE);


	WaveUI = new menuSet(1, 1, 650, 560, 120, 35);
	WaveUI->setMenuSetting(FALSE, TRUE, TRUE);
	WaveUI->setEach(0, 0, L"Wave : ", 15, L"Corbel", 137, 206, 250, TRUE);


	GameStartUI = new menuSet(1, 1, 650, 605, 120, 35);
	GameStartUI->setMenuSetting(TRUE, TRUE, TRUE);
	GameStartUI->setEach(0, 0, IDB_TESTSTART, 32, 32, FALSE);
	GameStartUI->setEach(0, 0, L"Stage Start", 12, L"Corbel", 255, 255, 255);


	//Option Menu
	OptionButtons = new menuSet(2, 2, 780, 560, 95, 80);
	OptionButtons->setMenuInterval(0, 5, 20, 0, 0);
	OptionButtons->setMenuSetting(TRUE, FALSE, TRUE);
	OptionButtons->setEach(0, 0, IDB_SAVE, 32, 32, TRUE);
	OptionButtons->setEach(0, 0, 5, 0);
	OptionButtons->setEach(0, 1, IDB_LOAD, 32, 32, TRUE);
	OptionButtons->setEach(0, 1, 5, 0);
	OptionButtons->setEach(1, 0, IDB_QUESTION, 32, 32, TRUE);
	OptionButtons->setEach(1, 1, IDB_OPTION, 32, 32, TRUE);

	//Tower Build �޴�
	TowerBuild = new menuSet(1, 1, 1110, 20, 150, 95, 1, 1);
	TowerBuild->setMenuSetting(TRUE, FALSE, TRUE);
	TowerBuild->setMenuTitle(13, L"Tower Build & Upgrade", 12);
	TowerBuild->setEach(0, 0, IDB_BUILD, 48, 48, TRUE);
	
	AttributeUpgrade = new menuSet(2, 2, 1110, 125, 150, 165, 1, 1);
	AttributeUpgrade->setMenuInterval(10, 5, 5, 5, 5);
	AttributeUpgrade->setMenuSetting(TRUE, FALSE, TRUE);
	AttributeUpgrade->setMenuTitle(13, L"Attribute Upgrade", 12);

	AttributeUpgrade->setEach(0, 0, IDB_FIRE, 48, 48, TRUE);

	AttributeUpgrade->setEach(0, 1, IDB_ELECTRIC, 48, 48, TRUE);
	
	AttributeUpgrade->setEach(1, 0, IDB_WATER, 48, 48, TRUE);	
	AttributeUpgrade->setEach(1, 0, 2, 0);
	AttributeUpgrade->setEach(1, 1, IDB_NATURE, 48, 48, TRUE);
	AttributeUpgrade->setEach(1, 1, 2, 0);

	IncomeUpgrade = new menuSet(1, 1, 1110, 300, 150, 95, 1, 1);
	IncomeUpgrade->setMenuSetting(TRUE, FALSE, TRUE);
	IncomeUpgrade->setMenuTitle(13, L"Income Upgrade", 12);
	IncomeUpgrade->setEach(0, 0, IDB_INCOME, 48, 48, TRUE);

	TowerInfo = new menuSet(1, 5, 1110, 405, 150, 165, 1, 1);
	TowerInfo->setMenuTitle(13, L"Tower Info", 12);
	TowerInfo->setAllMenuText(L"Default", 12, L"Corbel", 255, 255, 255, FALSE);
	UpgradeCost = new menuSet(1, 1, 1110, 580, 150, 60, 1, 1);
	UpgradeCost->setMenuTitle(13, L"Upgrade Cost", 12);
	UpgradeCost->setAllMenuText(L"Default", 15, L"Corbel", 255, 255, 255, TRUE);
	

	BuySell = new menuSet(1, 2, 100, 100, 110, 80, 1, 1);
	BuySell->setToggle(TRUE); 
	BuySell->setShown(FALSE);
	BuySell->setMenuSetting(FALSE, TRUE, TRUE);
	BuySell->setMenuTitle(13, L"Buy & Sell", 12);
	BuySell->setBackGround(219, 112, 147, 255, 105, 180);
	BuySell->setAllMenuText(L"Default", 12, L"Corbel", 255, 255, 255, TRUE);
	BuySell->setEach(0, 0, L"Build & Upgrade", 12, L"Corbel", 255, 255, 255, TRUE);
	BuySell->setEach(0, 1, L"Sell Tower", 12, L"Corbel", 255, 255, 255, TRUE);

	ShowIncome = new menuSet(1, 3, 960, 350, 160, 100, 1, 1);
	ShowIncome->setToggle(TRUE);
	ShowIncome->setShown(FALSE);
	ShowIncome->setMenuSetting(FALSE, TRUE, TRUE);
	ShowIncome->setMenuTitle(13, L"Upgrade Income", 12);
	ShowIncome->setBackGround(218, 165, 32, 184, 134, 11);
	ShowIncome->setAllMenuText(L"Default", 12, L"Corbel", 255, 255, 255, TRUE);
	ShowIncome->setEach(0, 0, L"Now Income : ", 12, L"Corbel", 255, 255, 255, FALSE);
	ShowIncome->setEach(0, 1, L"Upgrade Cost : ", 12, L"Corbel", 255, 255, 255, FALSE);
	ShowIncome->setEach(0, 2, L"Upgrade", 12, L"Corbel", 123, 104, 238, TRUE);
	ShowIncome->setEdgeLocate(1);

	ShowEnemy = new menuSet(1, 6, 680, 400, 150, 140, 1, 1);
	ShowEnemy->setToggle(TRUE);
	ShowEnemy->setShown(FALSE);
	ShowEnemy->setMenuSetting(FALSE, TRUE, FALSE);
	ShowEnemy->setMenuTitle(13, L"Monster Infomation", 12);
	ShowEnemy->setBackGround(219, 112, 147, 255, 105, 180);
	ShowEnemy->setAllMenuText(L"Default", 12, L"Corbel", 255, 255, 255, FALSE);
	ShowEnemy->setEach(0, 0, L"HP : ", 12, L"Corbel", 220, 020, 060, FALSE);
	ShowEnemy->setEach(0, 1, L"MP : ", 12, L"Corbel", 0, 0, 205, FALSE);
	ShowEnemy->setEach(0, 2, L"Speed : ", 12, L"Corbel", 0, 205, 154, FALSE);
	ShowEnemy->setEach(0, 3, L"DEF : ", 12, L"Corbel", 112, 128, 128, FALSE);
	ShowEnemy->setEach(0, 4, L"Kill Money : ", 12, L"Corbel", 240, 230, 140, FALSE);
	ShowEnemy->setEach(0, 5, L"Attribute : ", 12, L"Corbel", 139, 0, 139, FALSE);

	//������ �̹� ������ menuSet�� ����Ʈ�� ����ִ´�.
	GameViewMenuUI.addMenu(LevelMap);
	GameViewMenuUI.addMenu(MoneyInterest);
	GameViewMenuUI.addMenu(ScoreLives);
	GameViewMenuUI.addMenu(WaveUI);
	GameViewMenuUI.addMenu(GameStartUI);
	GameViewMenuUI.addMenu(OptionButtons);
	GameViewMenuUI.addMenu(TowerBuild);
	GameViewMenuUI.addMenu(AttributeUpgrade);
	GameViewMenuUI.addMenu(IncomeUpgrade);
	GameViewMenuUI.addMenu(TowerInfo);
	GameViewMenuUI.addMenu(UpgradeCost);
	GameViewMenuUI.addMenu(BuySell);
	GameViewMenuUI.addMenu(ShowIncome);
	GameViewMenuUI.addMenu(ShowEnemy);
	//List �����Ϸ�.
	

	//Tower �Ѱ� Handler ����.
	TowerHandle = new towerHandle(msgUI, TowerInfo);
	clicked_Attribute = FIRE_TOWER;
	
	//Enemy Handler Position Set
	EnemySet.setViewPointer(this);
	EnemySet.setStartPos(Map);
	EnemySet.setEndPos(Map);
	GameSpeed = 1;
	//Enemy List �ҷ�����
	if (getStageData()) {
		AfxMessageBox(L"Enemy Data�� ���������� �ҷ��Խ��ϴ�.");
	}
	else {
		AfxMessageBox(L"Enemy Data�� �ҷ����� �� �����߽��ϴ�.");
	}
	SetDifficulty();
	//-------------------------------------------------
	CursorState = CURSORNORMAL;
	isShowInfo = FALSE;
	srand((unsigned int)time(NULL));

	//---Enemy Attribute Random ����--
	for (int i = 0; i < 40; i++) {
		EnemySetting[i].attribute = rand() % 5;
	}

	UpdateUI();
}


GameView* GameView::GetView() {
	CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

	CView * pView = pFrame->GetActiveView();

	if (!pView)

		return NULL;

	// Fail if view is of wrong kind

	// (this could occur with splitter windows, or additional

	// views on a single document

	if (!pView->IsKindOf(RUNTIME_CLASS(GameView)))

		return NULL;

	return (GameView *)pView;
}


//�� ��ư Ŭ�� �� ��Ÿ���� �̺�Ʈ ����
void GameView::OnLButtonDown(UINT nFlags, CPoint point)
{
	//Upgrade Income UI ���� ��
	if (ShowIncome->isInMenu(point)) {
		//Build Button Clicked
		if (ShowIncome->FocusedMenu->isIndex(0, 2)) {
			if (Money >= getIncomeUpgradeValue()) {
				Money -= getIncomeUpgradeValue();
				msgUI->addMsg(L"Income Upgrade(+5%) Complete!");
				Interest+= INTEREST_UPGRADE_RATE;
			}
			else {
				msgUI->addMsg(L"���� �����մϴ�.");
			}

			ShowIncome->setShown(FALSE);
			isShowInfo = FALSE;
			Invalidate();
			UpdateUI();
			return;
		}
	}

	//BuySell UI  ���� ��(�ֻ�� ��ġ �ʿ�)
	if (BuySell->isInMenu(point)) {
		//�Ǽ� or ���׷��̵� ��ư Ŭ����
		if (BuySell->FocusedMenu->isIndex(0, 0)) {
			BuySell->setShown(FALSE);
			if(Map->ftile->tileTower)Map->ftile->tileTower->showRange = FALSE;
			if (Map->bftile && Map->bftile->tileTower)Map->bftile->tileTower->showRange = FALSE;

			if (clicked_Attribute == NORMAL_TOWER) {
				msgUI->addMsg(L"���׷��̵� �� �Ӽ��� ������ �ּ���!");
			}
			else {
				TowerHandle->upgradeTower(clicked_Attribute, &Money, &EnemySet);
			}
		}

		//�Ǹ� ��ư Ŭ�� ��
		if (BuySell->FocusedMenu->isIndex(0, 1)) {
			TowerHandle->sellTower(Money);
			BuySell->setShown(FALSE);
			if (Map->ftile->tileTower)Map->ftile->tileTower->showRange = FALSE;
			if (Map->bftile && Map->bftile->tileTower)Map->bftile->tileTower->showRange = FALSE;
		}
		Invalidate();
		UpdateUI();
		return;
	}


	//Ÿ���� Ŭ���� �ش� Ÿ���� �����ͷ� ��ġ��Ŵ.
	if (Map->isInTile(point)) {
		//���ſ� �����ߴ� Ÿ�ϰ� �ٸ� ���
		if (Map->ftile != Map->bftile) {
			BuySell->setShown(TRUE);
			CPoint tilePoint = Map->ftile->rPoint();
			BuySell->setMenuSetPos(tilePoint.x + (DEFAULT_TILE_WIDTH) / 2, tilePoint.y - (DEFAULT_TILE_HEIGHT) / 5 - BuySell->getHeight());

			if (Map->bftile && Map->bftile->tileTower)Map->bftile->tileTower->showRange = FALSE;
			if (Map->ftile->tileTower)Map->ftile->tileTower->showRange = TRUE;
		}
		//���ſ� �����ߴ� Ÿ�ϰ� ���� ���
		else {
			if (!BuySell->isStateShown()) {
				BuySell->setShown(TRUE);
				CPoint tilePoint = Map->ftile->rPoint();
				BuySell->setMenuSetPos(tilePoint.x + (DEFAULT_TILE_WIDTH) / 2, tilePoint.y - (DEFAULT_TILE_HEIGHT) / 5 - BuySell->getHeight());				
				if (Map->ftile->tileTower)Map->ftile->tileTower->showRange = TRUE;
			}
			else {
				BuySell->setShown(FALSE);
				if (Map->ftile->tileTower)Map->ftile->tileTower->showRange = FALSE;
			}
		}
		Map->bftile = Map->ftile;
	}

	

	//TowerBuild UI ���� ��
	if (TowerBuild->isInMenu(point)) {
		//Build Button Clicked
		if (TowerBuild->FocusedMenu->isIndex(0, 0)) {
			if (clicked_Attribute == NORMAL_TOWER) {
				msgUI->addMsg(L"���׷��̵� �� �Ӽ��� ������ �ּ���!");
			}
			else {
				TowerHandle->upgradeTower(clicked_Attribute, &Money, &EnemySet);
			}			
		}
	}

	//AttributeUpgrade UI ���� ��
	if (AttributeUpgrade->isInMenu(point)) {
		//Fire Clicked
		if (AttributeUpgrade->FocusedMenu->isIndex(0, 0)) {
			clicked_Attribute = FIRE_TOWER;
			msgUI->addMsg(L"�� �Ӽ� ���׷��̵带 �����߽��ϴ�.");
		}
		else if (AttributeUpgrade->FocusedMenu->isIndex(0, 1)) {
			clicked_Attribute = WATER_TOWER;
			msgUI->addMsg(L"�� �Ӽ� ���׷��̵带 �����߽��ϴ�.");
		}
		else if (AttributeUpgrade->FocusedMenu->isIndex(1, 0)) {
			clicked_Attribute = ELECTRIC_TOWER;
			msgUI->addMsg(L"���� �Ӽ� ���׷��̵带 �����߽��ϴ�.");
		}
		else if (AttributeUpgrade->FocusedMenu->isIndex(1,1)) {
			clicked_Attribute = NATURE_TOWER;
			msgUI->addMsg(L"�ڿ� �Ӽ� ���׷��̵带 �����߽��ϴ�.");
		}
	}

	//IncomeUpgrade UI ���� ��
	if (IncomeUpgrade->isInMenu(point)) {
		//IncomeUpgrade Clicked
		if (IncomeUpgrade->FocusedMenu->isIndex(0, 0)) {
			if (!isShowInfo) {
				ShowIncome->setShown(TRUE);
				isShowInfo = TRUE;
			}
			else {
				ShowIncome->setShown(FALSE);
				isShowInfo = FALSE;
			}			
		}
	}

	//Wave UI ���ý�
	if (WaveUI->isInMenu(point)) {
		//IncomeUpgrade Clicked
		if (WaveUI->FocusedMenu->isIndex(0, 0)) {
			if (!isShowInfo) {
				ShowEnemy->setShown(TRUE);
				isShowInfo = TRUE;
			}
			else {
				ShowEnemy->setShown(FALSE);
				isShowInfo = FALSE;
			}
		}
	}


	//GameStartUI
	if (GameStartUI->isInMenu(point)) {
		//Start ��ư Ŭ���� ���� ����.
		if (GameStartUI->FocusedMenu->isIndex(0, 0)) {
			//���� �������� �ƴ� ��츸
			if (!GameState) {				
				if (Wave <= 40 && Lives > 0) {
					GameState = TRUE;

					msg.Format(L"%d Stage Start!", Wave);
					msgUI->addMsg(msg);

					//�������� ����
					pWinThread = NULL;
					pWinThread = AfxBeginThread(StageThread, this);

					if (pWinThread == NULL) {
						AfxMessageBox(L"Error! Thread ������ �����߽��ϴ�.");
					}
				}
			}
			else {
				if (GameSpeed == 1) {
					msgUI->addMsg(L"���Ӽӵ��� 2��� �����մϴ�.");
					GameSpeed = 2;
					GameStartUI->setEach(0, 0, IDB_RIGHTDOUBLE, 32, 32, FALSE);
				}
				else {
					msgUI->addMsg(L"���Ӽӵ��� �⺻���� �����մϴ�.");
					GameSpeed = 1;
					GameStartUI->setEach(0, 0, IDB_TESTSTART, 32, 32, FALSE);
				}				
			}
		}
	}

	//OptionButtons UI
	if (OptionButtons->isInMenu(point)) {
		//Save ��ư
		if (OptionButtons->FocusedMenu->isIndex(0, 0)) {
			msgUI->addMsg(L"�������� �ʾҽ��ϴ�.");
		}
		//Help ��ư
		if (OptionButtons->FocusedMenu->isIndex(0, 1)) {
			if (!GameState) {
				GameHelpDlg dlg;
				dlg.DoModal();
			}
			else {
				msgUI->addMsg(L"���� ���� �������̶� �� �� �����ϴ�.");
			}
		}
		//Load ��ư
		if (OptionButtons->FocusedMenu->isIndex(1, 0)) {
			msgUI->addMsg(L"�������� �ʾҽ��ϴ�.");
		}
		//Option ��ư
		if (OptionButtons->FocusedMenu->isIndex(1, 1)) {
			if (!GameState) {
				GameOptionDlg dlg;
				if (dlg.DoModal() == IDOK) {
					::PostMessage(AfxGetMainWnd()->m_hWnd, WM_ON_FORM_CHANGE, IDD_STARTMENUVIEW, 0);
				}
			}
			else {
				msgUI->addMsg(L"���� ���� �������̶� �� �� �����ϴ�.");
			}
		}
	}

	UpdateUI();
}

//�׸��� ����
void GameView::InfoDraw(CDC* pDC) {
	Map->drawTileSet(pDC);
	msgUI->drawAllMenu(pDC);
	TowerHandle->drawAllTower(pDC);
	GameViewMenuUI.DrawAllViewUI(pDC);
	EnemySet.drawAllEnemy(pDC);
}

//���콺 ������ ����
void GameView::OnMouseMove(UINT nFlags, CPoint point)
{

	//Menu�� ���콺 �ø� ��, �ش� ���콺�� CLICK State�� ����.
	if (GameViewMenuUI.isInUI(point)) {
		if (CursorState == CURSORNORMAL) {
			Draw.SetCursorClick();
			CursorState = CURSORCLICK;
		}
	}
	else {
		if (CursorState == CURSORCLICK) {
			Draw.SetCursorNormal();
			CursorState = CURSORNORMAL;
		}
	}

	CFormView::OnMouseMove(nFlags, point);
}



void GameView::OnDestroy()
{
	CFormView::OnDestroy();

	// TODO: ���⿡ �޽��� ó���� �ڵ带 �߰��մϴ�.
	GameState = FALSE;
	GameViewMenuUI.deleteAllpMenu();
	delete(msgUI);
	delete(TowerHandle);
}

int GameView::getIncomeUpgradeValue()
{
	int value = DEFAULT_INTEREST_VALUE;
	for (int i = DEFAULT_INTEREST_RATE; i < Interest; i+=INTEREST_UPGRADE_RATE) {
		value *= 4;
	}
	return value;
}

int GameView::convert_int(TCHAR * obj)
{
	TCHAR *tmp = obj;
	TCHAR data[30] = L"\0";
	TCHAR *tmp2 = data;
	while (*tmp && *tmp != ' ') {
		*tmp2 = *tmp;
		tmp++, tmp2++;
	}

	int value = _ttoi(data);
	return value;
}

BOOL GameView::getStageData()
{
	CStdioFile file;
	CString str;	
	TCHAR tempData[50];
	TCHAR *temp;
	int count = 0;
	int stage = 0;
	if (file.Open(L"enemy.dat", CFile::modeRead | CFile::typeText)) {
		
		while (file.ReadString(str))
		{		
			count = 0;
			int nStrLength = str.GetLength() + 1;
			_tcscpy_s(tempData, nStrLength, str);
			temp = tempData;

			while (*temp) {
				if (*temp == ' ') {
					count++;
					temp++;
				}
				switch (count) {
				//�ùٸ� ���������� �˻�.
				case 0:
					if (stage != convert_int(temp) - 1) {
						return FALSE;
					}
					break;
				case 1:
					EnemySetting[stage].enemyNumber = convert_int(temp);
					break;
				case 2:
					EnemySetting[stage].HP = convert_int(temp);
					break;
				case 3:
					EnemySetting[stage].MP = convert_int(temp);
					break;
				case 4:
					EnemySetting[stage].Speed = convert_int(temp);
					break;
				case 5:
					EnemySetting[stage].DEF = convert_int(temp);
					break;
				case 6:
					EnemySetting[stage].killMoney = convert_int(temp);
					break;
				}

				while (*temp && *temp != ' ') {
					temp++;
				}
			}
			stage++;
		}
	}
	else {
		return FALSE;
	}

	file.Close();
	return TRUE;
}



//60fps
UINT GameView::StageThread(LPVOID _mothod)
{

	//Thread ����
	GameView *pEdit = (GameView*)_mothod;
	static int TimerCall, Spawn_Enemy_Num, SpawnTime;
	static int SLEEP_TIME = 1000 / FRAME_PER_SECOND;

	Spawn_Enemy_Num = pEdit->EnemySetting[pEdit->Wave-1].enemyNumber;	//������ ���� ������ ����
	SpawnTime = ENEMY_ALLSPAWN_TIME / Spawn_Enemy_Num;
	SpawnTime = SpawnTime / SLEEP_TIME;
	TimerCall = SpawnTime;
	TRACE("Game Thread�� ���۵Ǿ����ϴ�.\n");	

	while (pEdit->GameState) {
		//Thread ���� �� �Լ� ����
		TimerCall++;
		pEdit->EnemySet.MoveAllEnemy();	//������ ������
		pEdit->TowerHandle->setAllTowerDelay();	//��� Ÿ���� �����̸� ����
		pEdit->Invalidate();	 //ȭ�� ����

		if (TimerCall > SpawnTime) {	//���� �ð� ���� enemy ����
			if (Spawn_Enemy_Num > 0) {
				Spawn_Enemy_Num--;
				pEdit->EnemySet.spawnEnemy(pEdit->EnemySetting[pEdit->Wave - 1].HP, pEdit->EnemySetting[pEdit->Wave - 1].MP, pEdit->EnemySetting[pEdit->Wave - 1].Speed,
					pEdit->EnemySetting[pEdit->Wave - 1].DEF, pEdit->EnemySetting[pEdit->Wave - 1].killMoney, pEdit->Wave * 50 * (pEdit->Difficulty+1), pEdit->EnemySetting[pEdit->Wave -1].attribute);
				TimerCall = 0;
			}
			//�����ϴ� ���� �Ѹ����� ������
			else {
				if (pEdit->EnemySet.getEnemyNum() == 0) {
					pEdit->TowerHandle->deleteAllBullet();
					pEdit->EnemySet.RemoveAllEnemy();
					pEdit->msg.Format(L"Stage %d Clear!", pEdit->Wave);
					pEdit->msgUI->addMsg(pEdit->msg);
					pEdit->GameState = FALSE;
					pEdit->Wave += 1;	//Wave +1
					if (pEdit->Wave > 40) {
						AfxMessageBox(L"Game Clear! �����մϴ�.");
					}
					//Income ����
					pEdit->Money = pEdit->Money + pEdit->Money*(pEdit->Interest)/100;
					pEdit->msg.Format(L"Income +%d$", pEdit->Money*(pEdit->Interest) / 100);
					pEdit->msgUI->addMsg(pEdit->msg);
					//UI Update
					pEdit->UpdateUI();
				}
			}
		}
		//60fps
		Sleep(SLEEP_TIME/pEdit->GameSpeed);
	}


	TRACE("Game Thread�� ����Ǿ����ϴ�.\n");
	return 0;
}

void GameView::UpdateUI()
{
	//���̵� ����
	LevelMap->setEach(0, 0, DifficultyString);	

	//�� �̸� ����
	msg.Format(L"Map Name : %s", Map->MapName);	
	LevelMap->setEach(0, 1, msg);	

	//�� ����
	msg.Format(L"Money : %d$", Money);
	MoneyInterest->setEach(0, 0, msg);
	//���� ����
	msg.Format(L"Interest Rate : %d%%", Interest);
	MoneyInterest->setEach(0, 1, msg);

	//���� ����
	msg.Format(L"Score : %d", Score);
	ScoreLives->setEach(0, 0, msg);
	//��� ����
	msg.Format(L"Lives : %d",Lives);
	ScoreLives->setEach(0, 1, msg);

	//���� Wave ����
	msg.Format(L"Wave : %d / 40", Wave);
	WaveUI->setEach(0, 0, msg);

	//TowerInfo ����------

	//Ŭ���� Ÿ���� �����ϰ�, �� Ÿ�Ͽ� Ÿ���� �Ǽ��� ��츸.
	if (Map->ftile && Map->ftile->tileTower) {
		//Ÿ�� ������?
		msg.Format(L"Tower Lv : %d ", Map->ftile->tileTower->getTowerLv());
		TowerInfo->setEach(0, 0, msg);

		//Ÿ�� ���ݷ���?
		msg.Format(L"Damage : %.2f", Map->ftile->tileTower->getDamage());
		TowerInfo->setEach(0, 1, msg);

		//Ÿ���� ��Ÿ���?
		msg.Format(L"Range : %.2f", Map->ftile->tileTower->getRange());
		TowerInfo->setEach(0, 2, msg);

		//Ÿ�� ���ݼӵ���?
		msg.Format(L"Attack Speed : %.3f", Map->ftile->tileTower->getAtkSpeed());
		TowerInfo->setEach(0, 3, msg);

		//Ÿ���� �� �Ӽ��� ������?
		msg.Format(L"Fire : %d, Water : %d, \nElectric : %d, Nature : %d", Map->ftile->tileTower->getFireLv(), Map->ftile->tileTower->getWaterLv(), Map->ftile->tileTower->getElectricLv(), Map->ftile->tileTower->getNatureLv());
		TowerInfo->setEach(0, 4, msg);
		//--------------

		//���׷��̵� ��� ����
		msg.Format(L"%d $", Map->ftile->tileTower->getTowerValue());
		UpgradeCost->setEach(0, 0, msg);
		//
	}
	//Ÿ���� ������.
	else {
		//Ÿ�� ������?
		msg.Format(L"Tower Lv : None ");
		TowerInfo->setEach(0, 0, msg);

		//Ÿ�� ���ݷ���?
		msg.Format(L"Damage : %d", 0);
		TowerInfo->setEach(0, 1, msg);

		//Ÿ���� ��Ÿ���?
		msg.Format(L"Range : %d", 0);
		TowerInfo->setEach(0, 2, msg);

		//Ÿ�� ���ݼӵ���?
		msg.Format(L"Attack Speed : %d", 0);
		TowerInfo->setEach(0, 3, msg);

		//Ÿ���� �� �Ӽ��� ������?
		msg.Format(L"Fire : 0, Water : 0, \nElectric : 0, Nature : 0");
		TowerInfo->setEach(0, 4, msg);
		//--------------

		//���׷��̵� ��� ����
		msg.Format(L"%d $", DEFAULT_TOWER_VALUE);
		UpgradeCost->setEach(0, 0, msg);
		//
	}


	//Next Enemy ����------
	msg.Format(L"HP : %d", EnemySetting[Wave - 1].HP);
	ShowEnemy->setEach(0, 0, msg);

	msg.Format(L"MP : %d", EnemySetting[Wave - 1].MP);
	ShowEnemy->setEach(0, 1, msg);

	msg.Format(L"Speed : %d", EnemySetting[Wave - 1].Speed);
	ShowEnemy->setEach(0, 2, msg);

	msg.Format(L"DEF : %d", EnemySetting[Wave - 1].DEF);
	ShowEnemy->setEach(0, 3, msg);

	msg.Format(L"Kill Money : %d", EnemySetting[Wave - 1].killMoney);
	ShowEnemy->setEach(0, 4, msg);

	switch (EnemySetting[Wave - 1].attribute) {
	case 0:
		msg.Format(L"Attribute : Component");
		break;
	case 1:
		msg.Format(L"Attribute : Fire");
		break;
	case 2:
		msg.Format(L"Attribute : Water");
		break;
	case 3:
		msg.Format(L"Attribute : Electric");
		break;
	case 4:
		msg.Format(L"Attribute : Nature");
		break;
	}	
	ShowEnemy->setEach(0, 5, msg);

	//Income Upgrade UI ����
	msg.Format(L"Now Income : %d(%%)", Interest);
	ShowIncome->setEach(0, 0, msg);

	msg.Format(L"Upgrade Cost : %d", getIncomeUpgradeValue());
	ShowIncome->setEach(0, 1, msg);

	//ȭ�� �ٽñ׸���
	Invalidate();
}
