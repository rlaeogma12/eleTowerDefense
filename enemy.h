#ifndef ENEMY_H__
#define ENEMY_H__

#pragma once

#include "Setting.h"
#include "Utility.h"
#include "tile.h"

class GameView;
class EditView;

/*
	----------------------------------
	----------enemy.h-------------
	----------------------------------
*/

class enemySet;

//enemy 클래스 선언부------------------

//ENEMY_START_TILEID 는 시작지점을 , ENEMY_END_TILEID 는 적의 도착지를 의미.

class enemy
{
private:
	//멤버변수 정의	
	CPoint enemyPos;	//적의 위치
	int width, height;	//적의 크기
	int enemyIndex;	//해당 Enemy를 구별하기 위한 index
	enemySet *pParent;	//enemy의 parent enemySet

	tile *destinTile;		//목적지 타일
	tile *locateTile;		//현재 위치한 타일 p
	
	//체력바 정의
	CPoint HPBarPos;
	int barWidth, barHeight;
	int barInterval;	//체력 바와 유닛 간의 거리
	int currentBarWidth;	//남은 체력 바의 길이(무조건 barWidth보다 작음)

	double MaxHP;	//적의 최대 체력
	double HP;	//적의 현재 체력
	double MaxMP;	//적의 마력
	double MP;	//적의 현재 마력
	int MaxMoveSpeed;	//최대 이동 속도
	int moveSpeed;	//현재 이동 속도 (Default : 1)
	int MaxDEF;	//적의 최대 방어력
	int DEF;	//적의 현재 방어력
	int attribute;	//적의 속성

	int killMoney;	//적을 죽일 때 주는 돈
	int killScore;	//적을 죽일 때 주는 스코어

	int moveDirection;	// 0 : 정지, 1: 상, 2: 하, 3: 좌, 4: 우
	tile *beforeVisitedTile;	//이전에 거쳐온 타일을 저장.(중복 계산을 피함)

protected:
	Utility DrawUI;

public:
	//생존 여부
	BOOL alive;

	enemy();	//생성자
	~enemy();	//소멸자

	//적의 이동을 담당.(walk)
	void moveBy(int delta_xpos, int delta_ypos);	//적의 위치를 변경한다(더하거나 빼서)	

	//set함수 모음
	void setEnemyPos(int x_pos, int y_pos);	//적의 위치를 지정한다.
	void setEnemy(double _MaxHP, double _MaxMP, int moveSpeed, int _DEF, int _killMoney, int _killScore, int attribute);	//적의 (최대) 기본적인 설정 정의
	void setCurrent(double _NowHP, double _NowMP, int _NowSpeed, int _NowDEF);
	void setEnemySize(int _width, int _height);
	void setEnemyIndex(int _index);	//1번부터 시작한다.
	void setParent(enemySet *pParentSet);
	void setHPBarSize(int _width, int _height, int _interval);
	void setHPBarPos();	
	void setCurrentHPBar();

	void setNextTile();	//Thread를 사용해서 임의의 시간마다 방향 결정.
	void setLocateTile(tile *objTile);	//현재 위치한 타일을 설정.
	void setDestinTile(tile *objTile);	//도착 타일을 설정.

	void dealtDamage(double dmgValue);	//HP 데미지를 받을 경우.

	//get함수 모음
	double getHP();		//체력을 반환
	double getMP();	//마력을 반환
	int getSpeed();	//이동속도를 반환
	int getDEF();	//방어력을 반환
	int getMoney();	//이녀석의 현상금을 반환
	int getScore();	//이녀석의 점수를 반환
	int getAttribute();	//속성을 반환

	int getIndex();	//Index를 얻는다.
	int getDirection();	//방향 획득
	tile *getLocateTile();	//시작 타일을 얻는다.
	tile *getDestinTile();	//도착 타일을 얻는다.

	CRect getERect();	//Enemy의 Rect를 얻음.
	CRect getBRect();	//Enemy HP Bar의 Rect를 얻음.
	CPoint getEnemyCenterPos();	//Enemy의 중앙지점 Pos를 얻음.

	BOOL isOnTile();	//도착 타일의 인식범위 안에 들어왔는 지 반환하는 함수.
	
	void HPdamaged(double dealt_HP); //공격받을 경우 감소량
	void MPdamaged(double dealt_MP); //공격받을 경우 감소량
	
	void Death();	//죽..음...

	//Draw 지원
	void drawEnemy(CDC *pDC);	//적을 그려낸다.(Hp바도 그려야함..)
};


//enemy들을 모아놓은 enemySet 클래스 선언부-----------------

class enemySet
{
private:
	int maxNum;	//활성화 가능한 적의 최대 수
	int currentNum;	//현재 활성화된 적의 수
	int spawnedNum;	//죽은거, 산거 포함 생성된 적의 수
	
	CPoint startPos;	//적들의 생성위치를 정의
	CPoint endPos;		//적들의 도달위치를 정의

	tile *startTile;	//생성위치 타일 어디?
	tile *endTile;	//도착위치 어디?
	GameView *pGameView;	//적 죽었을 경우, 소지금 등 전달 위함. (게임 View와 연동)
	EditView *pEditView;	//테스트 모드에서 사용하기 위함.
	

protected:
	Utility DrawUI;
	
public:
	vector<enemy*> enemyList;	//적들을 저장

	enemySet(int _maxNum);	//enemy Set을 설정한다. 최대 숫자를 처음에 정의. (최대 숫자 이상이 되더라도 push_back으로 확장가능, 연산시간은 좀 느린듯..)
	enemySet();
	~enemySet();	//소멸자

	void setStartPos(tileSet *objTile);	//시작점을 설정
	void setEndPos(tileSet *objTile);		//도착점을 설정
	void setViewPointer(GameView *_pGameView);
	void setViewPointer(EditView *_pEditView);

	int getSpawnedNum();	//실제로 존재하는 숫자
	int getEnemyNum();	//현재 존재하는 적의 숫자를 반환
	void spawnEnemy(double HP, double MP, int Speed, int DEF, int KillMoney = 0, int KillScore = 0, int attribute = 0,int eWidth = ENEMY_SIZE , int eHeight = ENEMY_SIZE, int bWidth = 46, int bHeight = 5, int bInterval = 5);	//적을 생성한다. (반드시 시작점에서만 생성함)
	void RemoveAllEnemy();	//현재 존재하는 모든 적을 완벽히 삭제한다.(할당 해제)
	void MoveAllEnemy();	//각 적이 가지고 있는 destinTile의 위치에 도달하도록 모든 적들을 이동시킴(이동 속도만큼)


	//Draw 지원
	void drawAllEnemy(CDC *pDC);	//적들을 그려낸다.
};

#endif