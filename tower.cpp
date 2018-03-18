#include "stdafx.h"
#include "tower.h"


tower::tower()
{
	//기본값 정의
	//위치 & 가로, 세로 정의
	rangeEnemyListNum = 0;
	showRange = FALSE;
	towerPos.SetPoint(0, 0);
	tWidth = 40;
	tHeight = 40;
	setImage();
	//위치한 타일 정의
	pBulletHandle = new bulletSet(this);
	placedTile = NULL;
	settingTower(1, 1, 3, 1, DEFAULT_TOWER_VALUE);
	attribute = 0;
	setTowerElement(0, 0, 0, 0, 0);
	leftDelay = 0;
	setRangeRect();
	towerLv = 0;
}

tower::tower(tile * tileLocation, enemySet *enemyList)
{
	rangeEnemyListNum = 0;
	placedTile = tileLocation;
	showRange = FALSE;
	tWidth = 40;
	tHeight = 40;
	setImage();
	pEnemySet = enemyList;
	//
	pBulletHandle = new bulletSet(this);
	towerPos = placedTile->rPoint();
	int resizeValue = (DEFAULT_TILE_WIDTH - tWidth) / 2;
	towerPos.Offset(resizeValue+1, resizeValue+1);
	attribute = 0;
	settingTower(1, 1, 2, 1, DEFAULT_TOWER_VALUE);
	setTowerElement(0, 0, 0, 0, 0);
	leftDelay = 0;
	setRangeRect();
	towerLv = 0;
}


tower::~tower()
{
	delete pBulletHandle;
}

void tower::setImage()
{
	Draw.SetImage(&default_symbol, IDB_COMPONENT_SYMBOL, _T("PNG"));
	Draw.SetImage(&fire_symbol, IDB_FIRE_SYMBOL, _T("PNG"));
	Draw.SetImage(&water_symbol, IDB_WATER_SYMBOL, _T("PNG"));
	Draw.SetImage(&electric_symbol, IDB_ELECTRIC_SYMBOL, _T("PNG"));
	Draw.SetImage(&nature_symbol, IDB_NATURE_SYMBOL, _T("PNG"));
}

void tower::setSize(int _tWidth, int _tHeight)
{
	tWidth = _tWidth;
	tHeight = _tHeight;
}

void tower::setPos(int x_pos, int y_pos)
{
	towerPos.SetPoint(x_pos, y_pos);
}

void tower::setDmg(double dmg)
{
	Damage = dmg;
}

void tower::setSpd(double spd)
{
	atkSpeed = spd;
}

void tower::setRange(double range)
{
	towerRange = range;
	towerRangeRect = getRangeRect();
}

void tower::setAtkNum(int atknum)
{
	atkNumber = atknum;
}

void tower::setValue(int money)
{
	towerValue = money;
}

void tower::setTowerElement(int nom, int fire, int water, int electric, int nature)
{
	component[0] = nom;
	component[1] = fire;
	component[2] = water;
	component[3] = electric;
	component[4] = nature;
}

void tower::addAbility(int AttributeTYPE)
{
	//추가할 속성값을 가짐.
	attributeList.push_back(AttributeTYPE);
}

void tower::DeleteLastAttribute()
{
	attributeList.pop_back();
}

double tower::getDamage()
{
	return Damage;
}

double tower::getAtkSpeed()
{
	return atkSpeed;
}

double tower::getRange()
{
	return towerRange;
}

int tower::getTowerLv()
{
	return towerLv;
}

int tower::getTowerValue()
{
	return towerValue;
}

int tower::getFireLv()
{
	return component[FIRE_TOWER];
}

int tower::getWaterLv()
{
	return component[WATER_TOWER];
}

int tower::getElectricLv()
{
	return component[ELECTRIC_TOWER];
}

int tower::getNatureLv()
{
	return component[NATURE_TOWER];
}

int tower::getAttribute()
{
	return attribute;
}



CPoint tower::getTowerCPos()
{
	return CPoint(towerPos.x + (tWidth)/2, towerPos.y + (tHeight)/2);
}


void tower::setMyAttribute()
{
	if (component[1] == component[2]  && component[2] == component[3] && component[3] == component[4]) {
		attribute = 0;
	}

	else {
		int maxValue = 0;
		for (int i = 0; i < 5; i++) {
			if (component[i] > maxValue) {
				maxValue = component[i];
				attribute = i;
			}
		}
	}
}

void tower::setTowerLv()
{
	towerLv = 0;
	for (int i = 0; i < 5; i++) {
		towerLv += component[i];
	}
}

void tower::setTowerValue(int value)
{
	towerValue = value;
}

void tower::addTowerLv(int value)
{
	towerLv += value;
}

void tower::addAttribute(int attributeID)
{
	//이곳에 각 속성 LvUp시 나타날 효과를 정의.
	switch (attributeID) {
	case FIRE_TOWER:
		//불 타워 업그레이드 시, 공격력 6배 증가, 사거리 1 감소.
		component[FIRE_TOWER]++;
		Damage *= 6;
		towerRange -= 1;
		break;
	case WATER_TOWER:
		//물 타워 업그레이드 시, 공격속도 3배 증가. .
		component[WATER_TOWER]++;
		atkSpeed *= 3;
		break;
	case ELECTRIC_TOWER:
		//전기 타워 업그레이드 시, 공격력 2배 증가, 이 속성의 레벨이 2의 배수가 될 때마다, 공격가능한 적의 숫자 1 증가.
		component[ELECTRIC_TOWER]++;
		Damage *= 2;
		if (component[ELECTRIC_TOWER] % 2 == 0) {
			atkNumber += 1;
		}
		break;
	case NATURE_TOWER:
		//자연 타워 업그레이드 시, 사거리 1 증가, 공격속도 2배 감소, 공격력 3배 증가. 
		//이 속성 레벨이 3의 배수가 될 때, 특수 능력을 얻는다.
		component[NATURE_TOWER]++;
		towerRange += 1;
		Damage *= 3;
		atkSpeed /= 2;
		if (component[NATURE_TOWER] % 3 == 0) {

		}
		break;
	}
	//모든 업그레이드 시, 자신의 가치가 2배 상승함.(2배 더 비싸진다..)
	towerValue *= 2;

	//Tower Range Setting
	settingTower(Damage, atkSpeed, towerRange, atkNumber, towerValue);
	setTowerLv();
	setMyAttribute();
}

void tower::settingTower(double dmg, double spd, double range, int atknum, int money)
{
	setDmg(dmg);
	setSpd(spd);
	setRange(range);
	setAtkNum(atknum);
	setValue(money);
}

void tower::drawTower(CDC * pDC)
{	
	switch (attribute) {
	case 0:
		Draw.DrawTower(pDC, towerPos, tWidth, tHeight, &default_symbol, attribute, towerLv, towerRangeRect, 3, 4, showRange);
		break;
	case 1:
		Draw.DrawTower(pDC, towerPos, tWidth, tHeight, &fire_symbol, attribute, towerLv, towerRangeRect, 3, 4, showRange);
		break;
	case 2:
		Draw.DrawTower(pDC, towerPos, tWidth, tHeight, &water_symbol, attribute, towerLv, towerRangeRect, 3, 4, showRange);
		break;
	case 3:
		Draw.DrawTower(pDC, towerPos, tWidth, tHeight, &electric_symbol, attribute, towerLv, towerRangeRect, 3, 4, showRange);
		break;
	case 4:
		Draw.DrawTower(pDC, towerPos, tWidth, tHeight, &nature_symbol, attribute, towerLv, towerRangeRect, 3, 4, showRange);
		break;
	default:
		Draw.DrawTower(pDC, towerPos, tWidth, tHeight, &electric_symbol, attribute, towerLv, towerRangeRect, 3, 4, showRange);
	}
	pBulletHandle->drawAllBullet(pDC);
}

BOOL tower::isOnTower(CPoint point)
{
	CRect TowerRect(towerPos.x, towerPos.y, towerPos.x + tWidth, towerPos.y + tHeight);
	if (TowerRect.PtInRect(point)) {
		return TRUE;
	}
	else {
		return FALSE;
	}	
}

void tower::setRangeRect()
{
	towerRangeRect = getRangeRect();
}

CRect tower::getRangeRect()
{
	if (towerRange>0) {
		return CRect(towerPos.x - towerRange*DEFAULT_TILE_WIDTH, towerPos.y - towerRange*DEFAULT_TILE_HEIGHT,
			towerPos.x + tWidth + towerRange*DEFAULT_TILE_WIDTH, towerPos.y + tHeight + towerRange*DEFAULT_TILE_HEIGHT);
	}
	else {
		return CRect(towerPos.x , towerPos.y, towerPos.x + tWidth , towerPos.y + tHeight);
	}
}

BOOL tower::isInEnemy(enemy * objEnemy)
{
	if (towerRangeRect.PtInRect(objEnemy->getEnemyCenterPos())) {
		return TRUE;
	}
	else {
		return FALSE;
	}
}


void tower::setTowerDelay()
{
	pBulletHandle->moveAllBullet();
	//타워 공격 딜레이 감소
	if (leftDelay > 0) {
		leftDelay -= 20;
	}
	else {
		Attack();
	}
}

//적을 공격한다.
void tower::Attack()
{
	//적을 감지하여 자신의 List에 추가함.
	if (pEnemySet->getEnemyNum()) {
		//모든 존재하는 적에 대해 Loop
		for (int i = 0; i < pEnemySet->getSpawnedNum(); i++) {
			//살아있을 경우,.
			if (pEnemySet->enemyList[i]->alive) {
				if (isInEnemy(pEnemySet->enemyList[i])) {
					//포함시킨다.
					rangeEnemyListNum++;
					rangeEnemyList.push_back(pEnemySet->enemyList[i]);
				}
			}
		}
	}

	//공격 가능한 숫자 만큼 총알 생성(해당 적을 노린다..)
	for (int i = 0; i < atkNumber; i++) {
		//총알 생성 시 그 총알이 알아서 적을 찾아간다.
		if (i < rangeEnemyListNum) {
			pBulletHandle->createBullet(rangeEnemyList[i]);
		}				
	}

	if (rangeEnemyList.size()) {
		//딜레이 재설정
		leftDelay = 2000 / atkSpeed;
	}

	//사거리 안 적 리스트 모두 제거.
	rangeEnemyListNum = 0;
	rangeEnemyList.clear();	
}

CPoint tower::targetPos(int index)
{
	if (rangeEnemyList.size()) {
		return rangeEnemyList[index]->getEnemyCenterPos();
	}
	else {
		return getTowerCPos();
	}
	
}

void tower::deleteAllBulletSet()
{
	pBulletHandle->deleteAllBullet();
}



void tower::TRACE_Exist_InRange()
{
	for (vector<enemy*>::size_type i = 0; i < rangeEnemyList.size(); i++) {
		TRACE("[%d] ,", rangeEnemyList[i]->getIndex());
	}
	TRACE("\n");
}

towerHandle::towerHandle(msgBox *_pmsgBox, menuSet *_pInfoUI)
{
	pmsgBox = _pmsgBox;
	pTowerInfoUI = _pInfoUI;
}

towerHandle::~towerHandle()
{
	vector<tower*>::iterator iter = towerList.begin();
	vector<tower*>::iterator endIer = towerList.end();
	for (; iter != towerList.end(); ++iter)
	{
		delete (*iter);
	}
	towerList.clear();
}

void towerHandle::upgradeTower(int attributeID, int *currentMoney, enemySet *enemyList)
{
	if (Map->ftile) {
		if (Map->ftile->isBuildable()) {
			//타워가 이미 건설된 경우
			if (Map->ftile->tileTower) {
				if (*currentMoney >= Map->ftile->tileTower->getTowerValue()) {
					(*currentMoney) -= Map->ftile->tileTower->getTowerValue();
					Map->ftile->tileTower->addAttribute(attributeID);
					pmsgBox->addMsg(L"타워를 업그레이드 하였습니다.");
				}
				else {
					pmsgBox->addMsg(L"돈이 부족합니다.");
					return;
				}
			}
			else {
				//새 타워 건설.
				if (*currentMoney >= DEFAULT_TOWER_VALUE) {
					tower *tempTower = new tower(Map->ftile, enemyList);
					towerList.push_back(tempTower);
					Map->ftile->tileTower = tempTower;
					(*currentMoney) -= Map->ftile->tileTower->getTowerValue();
					tempTower->setTowerValue(DEFAULT_TOWER_VALUE * 2);
					pmsgBox->addMsg(L"타워를 건설 하였습니다.");
				}
				else {
					pmsgBox->addMsg(L"돈이 부족합니다.");
					return;
				}
			}
		}
		else {
			pmsgBox->addMsg(L"이곳에는 타워 건설 불가능.");
			return;
		}
	}
}

void towerHandle::sellTower(int& CurrentMoney)
{
	//타워가 건설된 경우만
	if (Map->ftile->tileTower) {
		int sellValue = (Map->ftile->tileTower->getTowerValue() * 9) / 20;
		delTower(Map->ftile->tileTower);
		Map->ftile->tileTower = NULL;
		CurrentMoney += sellValue;
		CString msg;
		msg.Format(L"타워를 판매했습니다. +%d$ 획득.", sellValue);
		pmsgBox->addMsg(msg);
		}
		else {
			pmsgBox->addMsg(L"판매할 타워가 없습니다.");
		}
	
}

void towerHandle::delTower(tower *objTower)
{
	for (vector<tower*>::size_type i = 0; i < towerList.size(); i++) {
		if (towerList[i] == objTower) {
			delete towerList[i];
			towerList.erase(towerList.begin() + i);
			return;
		}
	}
}

void towerHandle::showTowerInfo()
{
	//.....
	pTowerInfoUI->setEach(0, 0, L"Tower Name : ");
}

void towerHandle::showTowerRange()
{

}

void towerHandle::drawAllTower(CDC * pDC)
{
	for (vector<tower>::size_type i = 0; i < towerList.size(); i++) {
		towerList[i]->drawTower(pDC);
	}
}

void towerHandle::setAllTowerDelay()
{
	for (vector<tower*>::size_type i = 0; i < towerList.size(); i++) {
		towerList[i]->setTowerDelay();
	}
}

void towerHandle::deleteAllBullet()
{
	for (vector<tower*>::size_type i = 0; i < towerList.size(); i++) {
		towerList[i]->deleteAllBulletSet();
	}
}
