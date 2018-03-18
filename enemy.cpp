#include "stdafx.h"
#include "enemy.h"
#include "GameView.h"
#include "EditView.h"
/*
	-------------------------------
	-------enemy.cpp----------
	-------------------------------
*/


//enemy객체 구현부.--------------------------

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


//---enemySet 구현부 -------------------------------

enemySet::enemySet(int _maxNum)
{
	pGameView = NULL;
	pEditView = NULL;
	maxNum = _maxNum;
	currentNum = 0;	//처음엔 한마리도 없어요
	spawnedNum =0;
}

enemySet::enemySet()
{
	pGameView = NULL;
	pEditView = NULL;
	//기본 최대치 1
	maxNum = 20;
	currentNum = 0;
	spawnedNum = 0;
}

enemySet::~enemySet()
{
	//enemyList Deallocate 필요 (메모리 누수 방지)
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
		TRACE(L"startPos 설정 불가능\n");
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
		TRACE(L"EndPos 설정 불가능\n");
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
	spawnedEnemy->setEnemy(HP, MP, Speed, DEF, KillMoney, KillScore, attribute);		//기본적인 유닛의 정보를 세팅
	spawnedEnemy->setCurrent(HP, MP, Speed, DEF);	//현재 체력도 동일하게 셋팅
	spawnedEnemy->setEnemyPos(startPos.x, startPos.y);	//적의 초기 위치를설정
	spawnedEnemy->setEnemyIndex(currentNum);	//적에게 고유 index 부여
	spawnedEnemy->setEnemySize(eWidth, eHeight);	//적의 size 설정
	spawnedEnemy->setParent(this);	//부모 set을 설정
	spawnedEnemy->setHPBarSize(bWidth, bHeight, bInterval);	//HPBar 사이즈 설정
	spawnedEnemy->setLocateTile(startTile);	//초기 위치할 타일을 설정
	spawnedEnemy->setDestinTile(startTile);	//초기 목적지 동일하게 설정.
	spawnedEnemy->alive = TRUE;	//처음엔 생존으로 적용
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
		//몬스터가 살아있는 경우에만 사용
		if (enemyList[i]->alive) {
			//특정 위치에 도달한 경우를 감지. 
			if (enemyList[i]->isOnTile()) {
				enemyList[i]->setLocateTile(enemyList[i]->getDestinTile());
				enemyList[i]->setNextTile();
			}

			//Move!
			switch (enemyList[i]->getDirection()) {
				//상
			case 1:
				enemyList[i]->moveBy(0, -(enemyList[i]->getSpeed()));
				break;
				//하
			case 2:
				enemyList[i]->moveBy(0, (enemyList[i]->getSpeed()));
				break;
				//좌
			case 3:
				enemyList[i]->moveBy(-(enemyList[i]->getSpeed()), 0);
				break;
				//우
			case 4:
				enemyList[i]->moveBy((enemyList[i]->getSpeed()), 0);
				break;
			}

			//체력이 0이 되었는지? 0이 된 경우는 없애고, 추가적인 보상을 획득.
			if (enemyList[i]->getHP() <= 0) {
				enemyList[i]->alive = FALSE;
				currentNum--;

				//보상 획득
				if (pGameView) {
					pGameView->Money += enemyList[i]->getMoney();
					pGameView->Score += enemyList[i]->getScore();
					pGameView->UpdateUI();
				}
			
			}
			//혹시 목적지 도착 했는지? 도착했으면 해당 적을 죽음으로 표시. + 목숨 1개 감소 필요
			else if (enemyList[i]->getLocateTile()->getTileID() == ENEMY_END_TILEID) {
				enemyList[i]->alive = FALSE;
				currentNum--;

				//게임 모드일 경우

				//목숨 소멸
				if (pGameView) {
					pGameView->Lives -= 1;
					pGameView->UpdateUI();

					if (pGameView->Lives <= 0) {
						pGameView->GameState = FALSE;
						AfxMessageBox(L"목숨이 0이 되셨습니다. 게임에서 패배했습니다.");
					}
				}
				//테스트모드일 경우 테스트 통과를 알림
				else if (pEditView) {
					pEditView->isTestCleared = TRUE;
					pEditView->msgUI->addMsg(L"테스트를 통과했습니다.");
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
