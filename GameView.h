#pragma once
#include "afxcmn.h"
#include "afxwin.h"


#include "Utility.h"
#include "menu.h"
#include "msgBox.h"
#include "tower.h"
// GameView 폼 뷰입니다.

class GameView : public CFormView
{
	DECLARE_DYNCREATE(GameView)

public:
	GameView();           // 동적 만들기에 사용되는 protected 생성자입니다.
	virtual ~GameView();

protected:
	Utility Draw;	//그리기 도우미 클래스 선언

public:
	//Menu 창을 만들기 위한 기존 클래스 이용
	void InfoDraw(CDC* pDC);
	void SetDifficulty();
	static GameView* GetView();

	//UI리스트 총괄.
	ViewUI GameViewMenuUI;

	//UI List
	menuSet* LevelMap;
	menuSet* MoneyInterest;
	menuSet* ScoreLives;
	menuSet* WaveUI;
	menuSet* GameStartUI;
	menuSet* OptionButtons;

	menuSet* TowerBuild;
	menuSet* AttributeUpgrade;
	menuSet* IncomeUpgrade;
	menuSet* TowerInfo;
	menuSet* UpgradeCost;

	//Buy Infomation
	menuSet *BuySell;
	menuSet *ShowIncome;
	menuSet *ShowEnemy;
	BOOL isShowInfo;

	//Enemy Set...
	//불러오기용 데이터
	typedef struct stageSetting {	
		int enemyNumber;
		int HP;
		int MP;
		int Speed;
		int DEF;
		int killMoney;
		int attribute;
	}StageSetting;
	StageSetting EnemySetting[MAX_STAGE_NUMBER];

	enemySet EnemySet;
	BOOL getStageData();

	int getIncomeUpgradeValue();
	int convert_int(TCHAR *obj);

	//msg Box
	msgBox *msgUI;

	//Tower List를 포함
	towerHandle *TowerHandle;

	//현재 선택된 attribute Upgrade 항목
	int clicked_Attribute;

	//------------------------------------------------------
	////게임 시 필요한 Data 목록을 담고 있습니다.////

	//각 맵에 들어갈 Data
	int** TileSetArray;

	////현재 진행중인 게임 내 정보를 포함합니다.
	//난이도(0 쉬움,  1 보통,  2 어려움,  3 불가능)
	int Difficulty;
	CString DifficultyString;
	CString MapName;	//MAP 이름
	BOOL GameState;	//게임 상태(라운드 진행중 TRUE , 아니면 FALSE)
	int Money;	//현재 소지금
	int Lives;	//현재 목숨
	int Score;	//점수
	int Interest;	//이자율
	int Wave;	//현재 WAVE
	int CursorState;	//커서 상태
	CString msg;	//메세지를 출력하기 위한 Temp CString객체

	//Enemy 이동 구현을 위한 Thread 생성
	int GameSpeed;
	CWinThread *pWinThread;
	static UINT StageThread(LPVOID _mothod);

	//UI목록에 표시되는 세부 정보들을 갱신한다.
	void UpdateUI();

	//////////////
	//------------------------------------------------------

#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_GAMEVIEW };
#endif
#ifdef _DEBUG
	virtual void AssertValid() const;
#ifndef _WIN32_WCE
	virtual void Dump(CDumpContext& dc) const;
#endif
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg BOOL OnEraseBkgnd(CDC* pDC);
	virtual void OnDraw(CDC* /*pDC*/);
	virtual void OnInitialUpdate();
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
protected:

public:
	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnDestroy();
};

