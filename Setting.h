#ifndef SETTING_H__
#define SETTING_H__

#pragma once
#include <vector>
using namespace std;
//전반적인 게임 셋팅을 정의하는 Header

//폼 변경시 보낼 메시지 리스트
#define WM_ON_FORM_CHANGE WM_USER+1
#define WM_CHANGECURSOR WM_USER+2

//커서 설정
#define CURSORNORMAL 0
#define CURSORCLICK 1

//타일 몬스터 시작점과 도착점 정의
#define ENEMY_START_TILEID	6
#define ENEMY_END_TILEID 7

//타일 기본 크기 정의
#define DEFAULT_TILE_WIDTH 46
#define DEFAULT_TILE_HEIGHT 46

//몬스터 정의 -----------------
//몬스터 기본 크기 정의
#define ENEMY_SIZE	26

//몬스터 타일 도착 인식 범위
#define REC_RANGE 3

//타일 맵 가로 세로 정의
#define STANDARD_COL	23
#define STANDARD_ROW	11

//적이 전부 나오기까지 걸리는 시간
#define ENEMY_ALLSPAWN_TIME	15000
#define MAX_STAGE_NUMBER 40


//타워 정의 ---------------------
//타워의 종류를 정의
#define NORMAL_TOWER	0
#define FIRE_TOWER				1
#define WATER_TOWER			2
#define ELECTRIC_TOWER	3
#define NATURE_TOWER		4

//타워의 초기 가격을 정의
#define DEFAULT_TOWER_VALUE 100

#define DEFAULT_INTEREST_VALUE	500
#define DEFAULT_INTEREST_RATE	10
#define INTEREST_UPGRADE_RATE	5

//Thread 관련(초당 프레임)
#define FRAME_PER_SECOND	60

#endif