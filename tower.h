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
	
	CPoint towerPos;	//Ÿ���� ��ġ	
	CRect towerRangeRect;	//Ÿ���� ��Ÿ� Rect
	int tWidth, tHeight;	//Ÿ���� ���� ���α���
	
	double Damage;	//Ÿ���� ���ݷ�
	double atkSpeed;	//Ÿ���� ���ݼӵ�
	double towerRange;	//Ÿ���� ���ݹ���
	int atkNumber;		//Ÿ���� ���� ���� ��� ��
	int towerValue;	//Ÿ���� ����
	int component[5];	//Ÿ���� �� �Ӽ��� [0] : ��, [1], ��, [2] : ��, [3], ����, [4] : �ڿ�

	int attribute;	//Ÿ���� �� �Ӽ��� �� ���� ���� ���� �� Ÿ���� �Ӽ��� �ȴ�. [0] : ��, [1], ��, [2] : ��, [3], ����, [4] : �ڿ�
	int towerLv;	//���׷��̵� �� Ÿ�� �Ӽ����� ����

	vector<int> attributeList;	//Ÿ���� Ư���ɷµ��� ��Ƴ��´�.

	vector<enemy*> rangeEnemyList;	//��Ÿ� ���� Enemy List�� ��´�. 
	int rangeEnemyListNum;	//Enemy lIst Number
	bulletSet *pBulletHandle;	//Bullet���� �Ѱ��ϴ� Set�� �� Ÿ������ ������ ��.
	
	//���� ������ Enemy���� �Ѱ� ������ ��� �ִ�.(�� �ڷᰡ �־�߸�, �� ������ ��ġ�� �ڽ��� 
	//Ÿ�� ��Ÿ��� ���Ͽ� ���� ������� ������ �� �ִ�.
	enemySet *pEnemySet;

protected:
	Utility Draw;

public:
	//���ݽ� �ʿ��� Data Variable ����
	double leftDelay;	//���ݱ��� ���� Delay(s)
	tile *placedTile;	//Ÿ���� ��ġ�� Ÿ��
	BOOL showRange;	//Ÿ���� ��Ÿ��� ǥ���ϴ°�?

	//Ÿ���� ������.
	tower();
	tower(tile *tileLocation, enemySet *enemyList);

	//Ÿ�� �Ҹ���. Ÿ�� �Ǹ� � �Ͼ.
	~tower();

	//Set �Լ� ���
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

	//Get �Լ� ���

	//Ÿ���� �������� ��ȯ.
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
	CRect getRangeRect();	//Ÿ���� ��Ÿ� ��ȯ.
	CPoint getTowerCPos();	//Ÿ�� �߽��� ��ȯ

	BOOL isInEnemy(enemy *objEnemy);
	

	//�׸���
	void drawTower(CDC *pDC);

	//����
	BOOL isOnTower(CPoint point);

	//�� ���� ��, �ڽ��� �� ���� ����Ʈ�� �߰��Ѵ�.
	void setTowerDelay();
	void Attack();
	CPoint targetPos(int index = 0);
	//----------------
	
	void deleteAllBulletSet();

	//�߰��� ���� �״´ٸ�... �� ���� ���� Kill Event�� �Ͼ�� �Ѵ�.(Stack�������� �ױ� �Ұ���)

	//Debug��..
	void TRACE_Exist_InRange();

};


class towerHandle {
private:
	//Ÿ���� ����� �����ϴ� Vector.
	vector<tower*> towerList;

	//���� Ÿ���� ������ ǥ���� msgBox  &  TowerInfoUI 
	msgBox *pmsgBox;
	menuSet *pTowerInfoUI;

public:
	towerHandle(msgBox *_pmsgBox, menuSet *_pInfoUI);
	~towerHandle();

	//Ÿ���� ���׷��̵� �մϴ�. (�Ǽ��� ����)
	void upgradeTower(int attributeID, int *currentMoney, enemySet *enemyList);

	//Ÿ���� �Ǹ��մϴ�.
	void sellTower(int& CurrentMoney);
	void delTower(tower *objTower);

	//Ÿ���� ������ ���� �ݴϴ�.
	void showTowerInfo();

	//Ÿ���� ��Ÿ��� ���� �ݴϴ�.
	void showTowerRange();


	//��� Ÿ�� �Ѱ� �׸���
	void drawAllTower(CDC *pDC);
	void setAllTowerDelay();

	//���� ���� ��, ��� �Ѿ� ����
	void deleteAllBullet();

};

#endif