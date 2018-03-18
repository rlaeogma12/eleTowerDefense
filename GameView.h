#pragma once
#include "afxcmn.h"
#include "afxwin.h"


#include "Utility.h"
#include "menu.h"
#include "msgBox.h"
#include "tower.h"
// GameView �� ���Դϴ�.

class GameView : public CFormView
{
	DECLARE_DYNCREATE(GameView)

public:
	GameView();           // ���� ����⿡ ���Ǵ� protected �������Դϴ�.
	virtual ~GameView();

protected:
	Utility Draw;	//�׸��� ����� Ŭ���� ����

public:
	//Menu â�� ����� ���� ���� Ŭ���� �̿�
	void InfoDraw(CDC* pDC);
	void SetDifficulty();
	static GameView* GetView();

	//UI����Ʈ �Ѱ�.
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
	//�ҷ������ ������
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

	//Tower List�� ����
	towerHandle *TowerHandle;

	//���� ���õ� attribute Upgrade �׸�
	int clicked_Attribute;

	//------------------------------------------------------
	////���� �� �ʿ��� Data ����� ��� �ֽ��ϴ�.////

	//�� �ʿ� �� Data
	int** TileSetArray;

	////���� �������� ���� �� ������ �����մϴ�.
	//���̵�(0 ����,  1 ����,  2 �����,  3 �Ұ���)
	int Difficulty;
	CString DifficultyString;
	CString MapName;	//MAP �̸�
	BOOL GameState;	//���� ����(���� ������ TRUE , �ƴϸ� FALSE)
	int Money;	//���� ������
	int Lives;	//���� ���
	int Score;	//����
	int Interest;	//������
	int Wave;	//���� WAVE
	int CursorState;	//Ŀ�� ����
	CString msg;	//�޼����� ����ϱ� ���� Temp CString��ü

	//Enemy �̵� ������ ���� Thread ����
	int GameSpeed;
	CWinThread *pWinThread;
	static UINT StageThread(LPVOID _mothod);

	//UI��Ͽ� ǥ�õǴ� ���� �������� �����Ѵ�.
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
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �����Դϴ�.

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

