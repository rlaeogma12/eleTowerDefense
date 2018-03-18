#include "stdafx.h"
#include "bullet.h"
#include "tower.h"


void bullet::setStrongWeak(int att)
{
	switch (att) {
	case 0:
		strongAtt = -1;
		weakAtt = -1;
		break;
	case 1:
		strongAtt = 4;
		weakAtt = 2;
		break;
	case 2:
		strongAtt = 1;
		weakAtt = 3;
		break;
	case 3:
		strongAtt = 2;
		weakAtt = 4;
		break;
	case 4:
		strongAtt = 3;
		weakAtt = 1;
		break;
	}
}

bullet::bullet(tower *objTower, enemy* objEnemy)
{
	//�� �Ѿ��� ������ Ÿ���� ������ ����.
	pTower = objTower;
	targetEnemy = objEnemy;
	vaild = TRUE;
	attribute = pTower->getAttribute();
	setStrongWeak(attribute);
	enemyAttribute = targetEnemy->getAttribute();
	//�Ѿ��� ũ�� &��ġ ����.
	width = 20;
	height = 20;
	
	bulletPos = pTower->getTowerCPos();
	bulletPos.Offset(-(width) / 2, -(height) / 2);
	bulletRect.SetRect(bulletPos.x, bulletPos.y, bulletPos.x + width, bulletPos.y + height);
}

bullet::~bullet()
{
}

void bullet::moveToEnemy()
{
	if (targetEnemy->alive) {
		destinPos = targetEnemy->getEnemyCenterPos();
	}
	else {
		vaild = FALSE;
	}
	//�� ���� �Ѿ���ġ ����
	bulletRect.SetRect(bulletPos.x, bulletPos.y, bulletPos.x + width, bulletPos.y + height);

	//�Ѿ� �����ȿ� DestinPos ��ġ��
	if (bulletRect.PtInRect(destinPos)) {
		if (vaild) {
			hitEnemy();
		}
	}
	//Move To
	else {
		//X axis move
		if (bulletPos.x > destinPos.x) {
			bulletPos.x -= 7;
		}
		else {
			bulletPos.x += 7;
		}

		//Y axis move
		if (bulletPos.y > destinPos.y) {
			bulletPos.y -= 7;
		}
		else {
			bulletPos.y += 7;
		}
	}
}

void bullet::hitEnemy()
{
	if (targetEnemy) {
		targetEnemy->dealtDamage(pTower->getDamage());	//�������� �ش�
		//���� �Ӽ��� �ڽſ��� ������ �Ӽ��� ���
		if (enemyAttribute == strongAtt) {
			targetEnemy->dealtDamage(pTower->getDamage());	
		}
		//�Ҹ��� ��� �� �������� 1/2��ŭ�� �ٽ� ȸ����Ŵ.
		else if (enemyAttribute == weakAtt) {
			targetEnemy->dealtDamage(-(pTower->getDamage())/2);
		}		

		vaild = FALSE;
	}
}



void bullet::drawBullet(CDC * pDC)
{
	if (vaild) {
		CBrush brush;
		switch (attribute) {
		case 0:
			brush.CreateSolidBrush(RGB(50, 40, 50));	//�߸� �Ӽ�
			break;
		case 1:
			brush.CreateSolidBrush(RGB(178, 34, 34));	//�� �Ӽ�
			break;
		case 2:
			brush.CreateSolidBrush(RGB(30, 144, 255));	//�� �Ӽ�
			break;
		case 3:
			brush.CreateSolidBrush(RGB(250, 250, 210));	//���� �Ӽ�
			break;
		case 4:
			brush.CreateSolidBrush(RGB(127, 255, 0));	//�ڿ� �Ӽ�
			break;
		}		
		CBrush* oldBrush = pDC->SelectObject(&brush);
		pDC->Ellipse(bulletRect);
		pDC->SelectObject(oldBrush);
	}
}

bulletSet::bulletSet(tower * objTower)
{
	pTower = objTower;
}

bulletSet::~bulletSet()
{
	deleteAllBullet();
}

void bulletSet::createBullet(enemy *objEnemy)
{
	bullet* tempBullet = new bullet(pTower, objEnemy);
	bulletList.push_back(tempBullet);
}

void bulletSet::deleteBullet(int index)
{
	delete bulletList[index];
	bulletList.erase(bulletList.begin() + index);
}

void bulletSet::deleteAllBullet()
{
	//����
	deque<bullet*>::iterator iter = bulletList.begin();
	deque<bullet*>::iterator endIer = bulletList.end();
	for (; iter != bulletList.end(); ++iter)
	{
		delete (*iter);
	}
	bulletList.clear();
}

void bulletSet::moveAllBullet()
{
	for (int i = bulletList.size()-1; i >=0; i--) {
		if (bulletList[i]->vaild) {
			bulletList[i]->moveToEnemy();
		}
		else {
			deleteBullet(i);
		}
	}
}

void bulletSet::drawAllBullet(CDC * pDC)
{
	for (deque<bullet*>::size_type i = 0; i < bulletList.size(); i++) {
		bulletList[i]->drawBullet(pDC);
	}
}
