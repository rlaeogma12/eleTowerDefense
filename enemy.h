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

//enemy Ŭ���� �����------------------

//ENEMY_START_TILEID �� ���������� , ENEMY_END_TILEID �� ���� �������� �ǹ�.

class enemy
{
private:
	//������� ����	
	CPoint enemyPos;	//���� ��ġ
	int width, height;	//���� ũ��
	int enemyIndex;	//�ش� Enemy�� �����ϱ� ���� index
	enemySet *pParent;	//enemy�� parent enemySet

	tile *destinTile;		//������ Ÿ��
	tile *locateTile;		//���� ��ġ�� Ÿ�� p
	
	//ü�¹� ����
	CPoint HPBarPos;
	int barWidth, barHeight;
	int barInterval;	//ü�� �ٿ� ���� ���� �Ÿ�
	int currentBarWidth;	//���� ü�� ���� ����(������ barWidth���� ����)

	double MaxHP;	//���� �ִ� ü��
	double HP;	//���� ���� ü��
	double MaxMP;	//���� ����
	double MP;	//���� ���� ����
	int MaxMoveSpeed;	//�ִ� �̵� �ӵ�
	int moveSpeed;	//���� �̵� �ӵ� (Default : 1)
	int MaxDEF;	//���� �ִ� ����
	int DEF;	//���� ���� ����
	int attribute;	//���� �Ӽ�

	int killMoney;	//���� ���� �� �ִ� ��
	int killScore;	//���� ���� �� �ִ� ���ھ�

	int moveDirection;	// 0 : ����, 1: ��, 2: ��, 3: ��, 4: ��
	tile *beforeVisitedTile;	//������ ���Ŀ� Ÿ���� ����.(�ߺ� ����� ����)

protected:
	Utility DrawUI;

public:
	//���� ����
	BOOL alive;

	enemy();	//������
	~enemy();	//�Ҹ���

	//���� �̵��� ���.(walk)
	void moveBy(int delta_xpos, int delta_ypos);	//���� ��ġ�� �����Ѵ�(���ϰų� ����)	

	//set�Լ� ����
	void setEnemyPos(int x_pos, int y_pos);	//���� ��ġ�� �����Ѵ�.
	void setEnemy(double _MaxHP, double _MaxMP, int moveSpeed, int _DEF, int _killMoney, int _killScore, int attribute);	//���� (�ִ�) �⺻���� ���� ����
	void setCurrent(double _NowHP, double _NowMP, int _NowSpeed, int _NowDEF);
	void setEnemySize(int _width, int _height);
	void setEnemyIndex(int _index);	//1������ �����Ѵ�.
	void setParent(enemySet *pParentSet);
	void setHPBarSize(int _width, int _height, int _interval);
	void setHPBarPos();	
	void setCurrentHPBar();

	void setNextTile();	//Thread�� ����ؼ� ������ �ð����� ���� ����.
	void setLocateTile(tile *objTile);	//���� ��ġ�� Ÿ���� ����.
	void setDestinTile(tile *objTile);	//���� Ÿ���� ����.

	void dealtDamage(double dmgValue);	//HP �������� ���� ���.

	//get�Լ� ����
	double getHP();		//ü���� ��ȯ
	double getMP();	//������ ��ȯ
	int getSpeed();	//�̵��ӵ��� ��ȯ
	int getDEF();	//������ ��ȯ
	int getMoney();	//�̳༮�� ������� ��ȯ
	int getScore();	//�̳༮�� ������ ��ȯ
	int getAttribute();	//�Ӽ��� ��ȯ

	int getIndex();	//Index�� ��´�.
	int getDirection();	//���� ȹ��
	tile *getLocateTile();	//���� Ÿ���� ��´�.
	tile *getDestinTile();	//���� Ÿ���� ��´�.

	CRect getERect();	//Enemy�� Rect�� ����.
	CRect getBRect();	//Enemy HP Bar�� Rect�� ����.
	CPoint getEnemyCenterPos();	//Enemy�� �߾����� Pos�� ����.

	BOOL isOnTile();	//���� Ÿ���� �νĹ��� �ȿ� ���Դ� �� ��ȯ�ϴ� �Լ�.
	
	void HPdamaged(double dealt_HP); //���ݹ��� ��� ���ҷ�
	void MPdamaged(double dealt_MP); //���ݹ��� ��� ���ҷ�
	
	void Death();	//��..��...

	//Draw ����
	void drawEnemy(CDC *pDC);	//���� �׷�����.(Hp�ٵ� �׷�����..)
};


//enemy���� ��Ƴ��� enemySet Ŭ���� �����-----------------

class enemySet
{
private:
	int maxNum;	//Ȱ��ȭ ������ ���� �ִ� ��
	int currentNum;	//���� Ȱ��ȭ�� ���� ��
	int spawnedNum;	//������, ��� ���� ������ ���� ��
	
	CPoint startPos;	//������ ������ġ�� ����
	CPoint endPos;		//������ ������ġ�� ����

	tile *startTile;	//������ġ Ÿ�� ���?
	tile *endTile;	//������ġ ���?
	GameView *pGameView;	//�� �׾��� ���, ������ �� ���� ����. (���� View�� ����)
	EditView *pEditView;	//�׽�Ʈ ��忡�� ����ϱ� ����.
	

protected:
	Utility DrawUI;
	
public:
	vector<enemy*> enemyList;	//������ ����

	enemySet(int _maxNum);	//enemy Set�� �����Ѵ�. �ִ� ���ڸ� ó���� ����. (�ִ� ���� �̻��� �Ǵ��� push_back���� Ȯ�尡��, ����ð��� �� ������..)
	enemySet();
	~enemySet();	//�Ҹ���

	void setStartPos(tileSet *objTile);	//�������� ����
	void setEndPos(tileSet *objTile);		//�������� ����
	void setViewPointer(GameView *_pGameView);
	void setViewPointer(EditView *_pEditView);

	int getSpawnedNum();	//������ �����ϴ� ����
	int getEnemyNum();	//���� �����ϴ� ���� ���ڸ� ��ȯ
	void spawnEnemy(double HP, double MP, int Speed, int DEF, int KillMoney = 0, int KillScore = 0, int attribute = 0,int eWidth = ENEMY_SIZE , int eHeight = ENEMY_SIZE, int bWidth = 46, int bHeight = 5, int bInterval = 5);	//���� �����Ѵ�. (�ݵ�� ������������ ������)
	void RemoveAllEnemy();	//���� �����ϴ� ��� ���� �Ϻ��� �����Ѵ�.(�Ҵ� ����)
	void MoveAllEnemy();	//�� ���� ������ �ִ� destinTile�� ��ġ�� �����ϵ��� ��� ������ �̵���Ŵ(�̵� �ӵ���ŭ)


	//Draw ����
	void drawAllEnemy(CDC *pDC);	//������ �׷�����.
};

#endif