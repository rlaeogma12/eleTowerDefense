#include "stdafx.h"
#include "enemy.h"
#include "GameView.h"
#include "EditView.h"
/*
	-------------------------------
	-------enemy.cpp----------
	-------------------------------
*/


//enemy��ü ������.--------------------------

void enemy::setNextTile()
{
	//top traverse
	
	if (locateTile->upTile()->isWalkable(beforeVisitedTile)) {
		beforeVisitedTile = locateTile;
		destinTile = locateTile->upTile();
		moveDirection = 1;
	}
	//Bottom traverse
	else if (locateTile->downTile()->isWalkable(beforeVisitedTile)) {
		beforeVisitedTile = locateTile;
		destinTile = locateTile->downTile();
		moveDirection = 2;
	}
	//left traverse
	else if (locateTile->leftTile()->isWalkable(beforeVisitedTile)) {
		beforeVisitedTile = locateTile;
		destinTile = locateTile->leftTile();
		moveDirection = 3;
	}
	//right traverse
	else if (locateTile->rightTile()->isWalkable(beforeVisitedTile)) {
		beforeVisitedTile = locateTile;
		destinTile = locateTile->rightTile();
		moveDirection = 4;
	}
	//else
	else {
		destinTile = NULL;
		beforeVisitedTile = destinTile;
		moveDirection = 0;
	}
}

BOOL enemy::isOnTile()
{
	if (destinTile && destinTile->rTileCenter().PtInRect(enemyPos)) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}

enemy::enemy()
{
	setParent(NULL);
	setEnemyPos(0, 0);
	setEnemy(1, 1, 1, 1, 1, 1, 0);
	setEnemySize(1, 1);
	setEnemyIndex(0);
	setCurrent(1, 1, 1, 1);
	beforeVisitedTile = NULL;
}


enemy::~enemy()
{
	
}

void enemy::moveBy(int delta_xpos, int delta_ypos)
{
	enemyPos.SetPoint(enemyPos.x + delta_xpos, enemyPos.y + delta_ypos);
	setHPBarPos();
	setCurrentHPBar();
}

void enemy::setEnemyPos(int x_pos, int y_pos)
{
	enemyPos.SetPoint(x_pos, y_pos);
}

void enemy::setEnemy(double _MaxHP, double _MaxMP, int _moveSpeed, int _DEF, int _killMoney, int _killScore, int _attribute)
{
	MaxHP = _MaxHP;
	MaxMP = _MaxMP;
	MaxMoveSpeed = _moveSpeed;
	MaxDEF = _DEF;
	killMoney = _killMoney;
	killScore = _killScore;
	attribute = _attribute;
}

void enemy::setCurrent(double _NowHP, double _NowMP, int _NowSpeed, int _NowDEF)
{
	HP = _NowHP;
	MP = _NowMP;
	moveSpeed = _NowSpeed;
	DEF = _NowDEF;
}

void enemy::setEnemySize(int _width, int _height)
{
	width = _width;
	height = _height;
}

void enemy::setEnemyIndex(int _index)
{
	enemyIndex = _index;
}

void enemy::setParent(enemySet * pParentSet)
{
	pParent = pParentSet;
}

void enemy::setHPBarSize(int _width, int _height, int _interval)
{
	barWidth = _width;
	barHeight = _height;
	barInterval = _interval;
	setHPBarPos();
	setCurrentHPBar();
}

void enemy::setHPBarPos()
{
	HPBarPos.SetPoint(enemyPos.x - (barWidth-width)/2, enemyPos.y - (barHeight + barInterval));
}

void enemy::setCurrentHPBar()
{
	currentBarWidth = barWidth * HP / MaxHP;
}

void enemy::setLocateTile(tile * objTile)
{
	locateTile = objTile;
}

void enemy::setDestinTile(tile * objTile)
{
	destinTile = objTile;
}

void enemy::dealtDamage(double dmgValue)
{
	HP -= dmgValue;
	setCurrentHPBar();
}

double enemy::getHP()
{
	return HP;
}

double enemy::getMP()
{
	return MP;
}

int enemy::getSpeed()
{
	return moveSpeed;
}

int enemy::getDEF()
{
	return DEF;
}

int enemy::getMoney()
{
	return killMoney;
}

int enemy::getScore()
{
	return killScore;
}

int enemy::getAttribute()
{
	return attribute;
}

int enemy::getIndex()
{
	return enemyIndex;
}

int enemy::getDirection()
{
	return moveDirection;
}

tile * enemy::getLocateTile()
{
	return locateTile;
}

tile * enemy::getDestinTile()
{
	return destinTile;
}

CRect enemy::getERect()
{
	return CRect(enemyPos.x, enemyPos.y, enemyPos.x + width, enemyPos.y + height);
}

CRect enemy::getBRect()
{
	return CRect(HPBarPos.x, HPBarPos.y, HPBarPos.x + barWidth, HPBarPos.y + barHeight);
}

CPoint enemy::getEnemyCenterPos()
{
	return CPoint(enemyPos.x + (width)/2, enemyPos.y + (height)/2);
}

void enemy::HPdamaged(double dealt_HP)
{
	HP -= dealt_HP;
	if (HP <= 0) {Death();}
}

void enemy::MPdamaged(double dealt_MP)
{
	MP -= dealt_MP;
	if (MP <= 0) {MP = 0;}
}

void enemy::Death()
{
	
}

void enemy::drawEnemy(CDC * pDC)
{
	if (alive) {
		DrawUI.DrawEnemy(pDC, enemyPos.x, enemyPos.y, width, height, barInterval, HPBarPos.x, HPBarPos.y, currentBarWidth, barHeight, attribute);
	}	
}


//---enemySet ������ -------------------------------

enemySet::enemySet(int _maxNum)
{
	pGameView = NULL;
	pEditView = NULL;
	maxNum = _maxNum;
	currentNum = 0;	//ó���� �Ѹ����� �����
	spawnedNum =0;
}

enemySet::enemySet()
{
	pGameView = NULL;
	pEditView = NULL;
	//�⺻ �ִ�ġ 1
	maxNum = 20;
	currentNum = 0;
	spawnedNum = 0;
}

enemySet::~enemySet()
{
	//enemyList Deallocate �ʿ� (�޸� ���� ����)
	vector<enemy*>::iterator iter = enemyList.begin();
	vector<enemy*>::iterator endIer = enemyList.end();
	for (; iter != enemyList.end(); ++iter)
	{
		delete (*iter);
	}
	enemyList.clear();
}

void enemySet::setStartPos(tileSet * objTile)
{
	if (objTile->getStartPosNum()) {
		startPos = objTile->rStartPos();
		startTile = objTile->rStartTile();
		startPos.Offset((DEFAULT_TILE_HEIGHT - ENEMY_SIZE) / 2, (DEFAULT_TILE_HEIGHT - ENEMY_SIZE) / 2);
	}
	else {
		TRACE(L"startPos ���� �Ұ���\n");
	}
}

void enemySet::setEndPos(tileSet * objTile)
{
	if (objTile->getEndPosNum()) {
		endPos = objTile->rEndPos();
		endTile = objTile->rEndTile();
		endPos.Offset((DEFAULT_TILE_HEIGHT - ENEMY_SIZE) / 2, (DEFAULT_TILE_HEIGHT - ENEMY_SIZE) / 2);
	}
	else {
		TRACE(L"EndPos ���� �Ұ���\n");
	}
}

void enemySet::setViewPointer(GameView * _pGameView)
{
	pGameView = _pGameView;
}

void enemySet::setViewPointer(EditView * _pEditView)
{
	pEditView = _pEditView;
}

int enemySet::getSpawnedNum()
{
	return spawnedNum;
}

int enemySet::getEnemyNum()
{
	return currentNum;
}

void enemySet::spawnEnemy(double HP, double MP, int Speed, int DEF, int KillMoney, int KillScore, int attribute, int eWidth, int eHeight, int bWidth, int bHeight, int bInterval)
{
	currentNum++;
	spawnedNum++;
	enemy* spawnedEnemy = new enemy();
	spawnedEnemy->setEnemy(HP, MP, Speed, DEF, KillMoney, KillScore, attribute);		//�⺻���� ������ ������ ����
	spawnedEnemy->setCurrent(HP, MP, Speed, DEF);	//���� ü�µ� �����ϰ� ����
	spawnedEnemy->setEnemyPos(startPos.x, startPos.y);	//���� �ʱ� ��ġ������
	spawnedEnemy->setEnemyIndex(currentNum);	//������ ���� index �ο�
	spawnedEnemy->setEnemySize(eWidth, eHeight);	//���� size ����
	spawnedEnemy->setParent(this);	//�θ� set�� ����
	spawnedEnemy->setHPBarSize(bWidth, bHeight, bInterval);	//HPBar ������ ����
	spawnedEnemy->setLocateTile(startTile);	//�ʱ� ��ġ�� Ÿ���� ����
	spawnedEnemy->setDestinTile(startTile);	//�ʱ� ������ �����ϰ� ����.
	spawnedEnemy->alive = TRUE;	//ó���� �������� ����
	enemyList.push_back(spawnedEnemy);
	if (currentNum > maxNum) { maxNum = currentNum; }
}

void enemySet::RemoveAllEnemy()
{
	vector<enemy*>::iterator iter = enemyList.begin();
	vector<enemy*>::iterator endIer = enemyList.end();
	for (; iter != enemyList.end(); ++iter)
	{
		delete (*iter);
	}
	enemyList.clear();
	currentNum = 0;
	spawnedNum = 0;
}

void enemySet::MoveAllEnemy()
{
	for(vector<enemy*>::size_type i=0;i<enemyList.size(); i++) {
		//���Ͱ� ����ִ� ��쿡�� ���
		if (enemyList[i]->alive) {
			//Ư�� ��ġ�� ������ ��츦 ����. 
			if (enemyList[i]->isOnTile()) {
				enemyList[i]->setLocateTile(enemyList[i]->getDestinTile());
				enemyList[i]->setNextTile();
			}

			//Move!
			switch (enemyList[i]->getDirection()) {
				//��
			case 1:
				enemyList[i]->moveBy(0, -(enemyList[i]->getSpeed()));
				break;
				//��
			case 2:
				enemyList[i]->moveBy(0, (enemyList[i]->getSpeed()));
				break;
				//��
			case 3:
				enemyList[i]->moveBy(-(enemyList[i]->getSpeed()), 0);
				break;
				//��
			case 4:
				enemyList[i]->moveBy((enemyList[i]->getSpeed()), 0);
				break;
			}

			//ü���� 0�� �Ǿ�����? 0�� �� ���� ���ְ�, �߰����� ������ ȹ��.
			if (enemyList[i]->getHP() <= 0) {
				enemyList[i]->alive = FALSE;
				currentNum--;

				//���� ȹ��
				if (pGameView) {
					pGameView->Money += enemyList[i]->getMoney();
					pGameView->Score += enemyList[i]->getScore();
					pGameView->UpdateUI();
				}
			
			}
			//Ȥ�� ������ ���� �ߴ���? ���������� �ش� ���� �������� ǥ��. + ��� 1�� ���� �ʿ�
			else if (enemyList[i]->getLocateTile()->getTileID() == ENEMY_END_TILEID) {
				enemyList[i]->alive = FALSE;
				currentNum--;

				//���� ����� ���

				//��� �Ҹ�
				if (pGameView) {
					pGameView->Lives -= 1;
					pGameView->UpdateUI();

					if (pGameView->Lives <= 0) {
						pGameView->GameState = FALSE;
						AfxMessageBox(L"����� 0�� �Ǽ̽��ϴ�. ���ӿ��� �й��߽��ϴ�.");
					}
				}
				//�׽�Ʈ����� ��� �׽�Ʈ ����� �˸�
				else if (pEditView) {
					pEditView->isTestCleared = TRUE;
					pEditView->msgUI->addMsg(L"�׽�Ʈ�� ����߽��ϴ�.");
				}
			}
		}
	}
}

void enemySet::drawAllEnemy(CDC * pDC)
{
	for (vector<enemy*>::size_type i = 0;i < enemyList.size(); i++) {
		enemyList[i]->drawEnemy(pDC);
	}
}
