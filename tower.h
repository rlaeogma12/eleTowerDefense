//------------------------------
//---------tower.h-----------
//-----------------------------

#pragma once
#include "enemy.h"
#include "tile.h"
#include "Setting.h"
#include "resource.h"
#include "msgBox.h"
#include "TileEx.h"
#include "bullet.h"

#ifndef TOWER_H__
#define TOWER_H__

//tower class definition----
class tower {
private:
	CImage default_symbol;
	CImage fire_symbol;
	CImage water_symbol;
	CImage electric_symbol;
	CImage nature_symbol;
	
	CPoint towerPos;	//타워의 위치	
	CRect towerRangeRect;	//타워의 사거리 Rect
	int tWidth, tHeight;	//타워의 가로 세로길이
	
	double Damage;	//타워의 공격력
	double atkSpeed;	//타워의 공격속도
	double towerRange;	//타워의 공격범위
	int atkNumber;		//타워의 동시 공격 대상 수
	int towerValue;	//타워의 가격
	int component[5];	//타워의 각 속성값 [0] : 무, [1], 불, [2] : 물, [3], 전기, [4] : 자연

	int attribute;	//타워의 각 속성값 중 가장 높은 값이 그 타워의 속성이 된다. [0] : 무, [1], 불, [2] : 물, [3], 전기, [4] : 자연
	int towerLv;	//업그레이드 된 타워 속성값의 총합

	vector<int> attributeList;	//타워의 특수능력들을 담아놓는다.

	vector<enemy*> rangeEnemyList;	//사거리 내의 Enemy List를 담는다. 
	int rangeEnemyListNum;	//Enemy lIst Number
	bulletSet *pBulletHandle;	//Bullet들을 총괄하는 Set를 각 타워들이 가져야 함.
	
	//현재 생성된 Enemy들의 총괄 정보를 담고 있다.(이 자료가 있어야만, 이 적들의 위치와 자신의 
	//타워 사거리를 비교하여 공격 대상으로 지정할 수 있다.
	enemySet *pEnemySet;

protected:
	Utility Draw;

public:
	//공격시 필요한 Data Variable 모음
	double leftDelay;	//공격까지 남은 Delay(s)
	tile *placedTile;	//타워가 위치한 타일
	BOOL showRange;	//타워의 사거리를 표시하는가?

	//타워의 생성자.
	tower();
	tower(tile *tileLocation, enemySet *enemyList);

	//타워 소멸자. 타워 판매 등에 일어남.
	~tower();

	//Set 함수 목록
	void setImage();
	void setSize(int _tWidth, int _tHeight);
	void setPos(int x_pos, int y_pos);
	void setDmg(double dmg);
	void setSpd(double spd);
	void setRange(double range);
	void setAtkNum(int atknum);
	void setValue(int money);
	void setTowerElement(int nom, int fire, int water, int electric, int nature);

	void addAbility(int AttributeTYPE);
	void DeleteLastAttribute();

	void setMyAttribute();
	void setTowerLv();
	void setTowerValue(int value);
	void addTowerLv(int value = 1);

	void addAttribute(int attributeID);
	void settingTower(double dmg, double spd, double range, int atknum, int money);

	//Get 함수 목록

	//타워의 데미지값 반환.
	double getDamage();
	double getAtkSpeed();
	double getRange();
	int getTowerLv();
	int getTowerValue();

	int getFireLv();
	int getWaterLv();
	int getElectricLv();
	int getNatureLv();
	int getAttribute();

	void setRangeRect();
	CRect getRangeRect();	//타워의 사거리 반환.
	CPoint getTowerCPos();	//타워 중심점 반환

	BOOL isInEnemy(enemy *objEnemy);
	

	//그리기
	void drawTower(CDC *pDC);

	//선택
	BOOL isOnTower(CPoint point);

	//적 감지 후, 자신의 적 감지 리스트를 추가한다.
	void setTowerDelay();
	void Attack();
	CPoint targetPos(int index = 0);
	//----------------
	
	void deleteAllBulletSet();

	//중간에 적이 죽는다면... 그 적에 대한 Kill Event가 일어나야 한다.(Stack형식으로 쌓기 불가능)

	//Debug용..
	void TRACE_Exist_InRange();

};


class towerHandle {
private:
	//타워의 목록을 관리하는 Vector.
	vector<tower*> towerList;

	//현재 타워의 정보를 표시할 msgBox  &  TowerInfoUI 
	msgBox *pmsgBox;
	menuSet *pTowerInfoUI;

public:
	towerHandle(msgBox *_pmsgBox, menuSet *_pInfoUI);
	~towerHandle();

	//타워를 업그레이드 합니다. (건설을 포함)
	void upgradeTower(int attributeID, int *currentMoney, enemySet *enemyList);

	//타워를 판매합니다.
	void sellTower(int& CurrentMoney);
	void delTower(tower *objTower);

	//타워의 정보를 보여 줍니다.
	void showTowerInfo();

	//타워의 사거리를 보여 줍니다.
	void showTowerRange();


	//모든 타워 총괄 그리기
	void drawAllTower(CDC *pDC);
	void setAllTowerDelay();

	//라운드 종료 시, 모든 총알 삭제
	void deleteAllBullet();

};

#endif