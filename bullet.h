#pragma once
#include "enemy.h"


#include <deque>
using namespace std;

#ifndef BULLET_H__
#define BULLET_H__

class tower;
class bulletSet;

class bullet
{
private:
	int width, height;
	int attribute;	//이 타워의 속성값
	int enemyAttribute;	//적의 속성값
	CPoint bulletPos;
	tower *pTower;	//이 총알의 소유 타워
	enemy *targetEnemy;	//이 총알이 노리는 적
	CPoint destinPos;	//타겟을 기반으로 목적지 설정
	CRect bulletRect;	//총알의 Rect (PtInRect를 통해 총알과 적의 충돌을 감지)


	int strongAtt;
	int weakAtt;
	void setStrongWeak(int att);

public:
	BOOL vaild;	//vaild 0 시 delete예약

	bullet(tower *objTower, enemy* objEnemy);
	~bullet();

	void moveToEnemy();
	void hitEnemy();

	void drawBullet(CDC *pDC);
};

class bulletSet
{
private:
	deque<bullet*> bulletList;
	tower *pTower;	//이 총알 셋을 소유한 타워의 포인터

public:
	bulletSet(tower *objTower);
	~bulletSet();

	void createBullet(enemy *objEnemy);
	void deleteBullet(int index);
	void deleteAllBullet();

	void moveAllBullet();
	void drawAllBullet(CDC *pDC);
};

#endif