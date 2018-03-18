#ifndef SETTING_H__
#define SETTING_H__

#pragma once
#include <vector>
using namespace std;
//�������� ���� ������ �����ϴ� Header

//�� ����� ���� �޽��� ����Ʈ
#define WM_ON_FORM_CHANGE WM_USER+1
#define WM_CHANGECURSOR WM_USER+2

//Ŀ�� ����
#define CURSORNORMAL 0
#define CURSORCLICK 1

//Ÿ�� ���� �������� ������ ����
#define ENEMY_START_TILEID	6
#define ENEMY_END_TILEID 7

//Ÿ�� �⺻ ũ�� ����
#define DEFAULT_TILE_WIDTH 46
#define DEFAULT_TILE_HEIGHT 46

//���� ���� -----------------
//���� �⺻ ũ�� ����
#define ENEMY_SIZE	26

//���� Ÿ�� ���� �ν� ����
#define REC_RANGE 3

//Ÿ�� �� ���� ���� ����
#define STANDARD_COL	23
#define STANDARD_ROW	11

//���� ���� ��������� �ɸ��� �ð�
#define ENEMY_ALLSPAWN_TIME	15000
#define MAX_STAGE_NUMBER 40


//Ÿ�� ���� ---------------------
//Ÿ���� ������ ����
#define NORMAL_TOWER	0
#define FIRE_TOWER				1
#define WATER_TOWER			2
#define ELECTRIC_TOWER	3
#define NATURE_TOWER		4

//Ÿ���� �ʱ� ������ ����
#define DEFAULT_TOWER_VALUE 100

#define DEFAULT_INTEREST_VALUE	500
#define DEFAULT_INTEREST_RATE	10
#define INTEREST_UPGRADE_RATE	5

//Thread ����(�ʴ� ������)
#define FRAME_PER_SECOND	60

#endif