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
	int attribute;	//�� Ÿ���� �Ӽ���
	int enemyAttribute;	//���� �Ӽ���
	CPoint bulletPos;
	tower *pTower;	//�� �Ѿ��� ���� Ÿ��
	enemy *targetEnemy;	//�� �Ѿ��� �븮�� ��
	CPoint destinPos;	//Ÿ���� ������� ������ ����
	CRect bulletRect;	//�Ѿ��� Rect (PtInRect�� ���� �Ѿ˰� ���� �浹�� ����)


	int strongAtt;
	int weakAtt;
	void setStrongWeak(int att);

public:
	BOOL vaild;	//vaild 0 �� delete����

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
	tower *pTower;	//�� �Ѿ� ���� ������ Ÿ���� ������

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