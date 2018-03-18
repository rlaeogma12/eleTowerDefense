#ifndef TILE_H__
#define TILE_H__

#pragma once

#include "Setting.h"
#include "Utility.h"

class tower;
class tileSet;

class tile
{
private:
	//타일의 위치
	CPoint tilePos;

	//타일의 크기
	int width, height;

	//타일 ID
	//0 : 빈 공간, 1 : 진흙 , 2 : 풀, 3 : 
	int tileID;

	//타일 ID에 따른 리소스 위치
	CPoint resourcePos;

	//타일 ID에 따른 건물/이동가능 여부
	BOOL isWalk, isBuild;

	//TileSet에 지정된 고유 tile Index
	int tileIndex;

	//이 타일의 부모 타일셋 포인터
	tileSet *pParent;


public:
	//이 타일에 지어진 Tower ID
	//0 : 지어지지 않음. 1... : 각 타워의 ID Value
	tower *tileTower;

	//tile 생성자
	tile();

	//tile 소멸자
	~tile();

	//set함수 모음.
	//위치 설정
	void setPos(int x_pos, int y_pos);

	//타일의 사이즈 설정
	void setSize(int width, int height);

	//타일 ID 설정
	void setTileID(int _tileID);

	//타일 부모 및 index 설정
	void setParent(tileSet *_pParent, int _index);

	//Tile ID에 따른 set 설정
	//리소스 위치 설정
	void setResourcePos(int x_pos, int y_pos);

	//get함수 모음.
	//Resource Position을 받아온다.
	CPoint getResourcePos();

	//이 타일의 Rect 반환.
	CRect rRect();

	//이 타일의 pos 반환.
	CPoint rPoint();

	//이 타일의 tileID 반환
	int getTileID();

	//이 타일이 이동가능한지 반환
	BOOL isWalkable(tile *exceptTile);

	//건설가능한지 반환
	BOOL isBuildable();

	//이 타일이 Parent TileSet에서 부여받은 Index값을 반환
	int getTileIndex();

	//Draw함수
	void drawTile(CImage *tileImage,CDC *pDC);

	//현재 타일의 Mon 위치 pos를 반환.(enemy 객체가 도달할 목적지 CPoint를 알리기 위함)
	CPoint rEnemypos();

	//현재 타일의 Mon 범위 3만큼의 rect를 반환(enemy 객체가 해당 위치에 도달했는지 인식하기 위함)
	CRect rTileCenter();

	//현재 타일의 위, 아래, 왼, 오른 타일을 반환(이동 시 필요)
	tile *upTile();
	tile *downTile();
	tile  *leftTile();
	tile *rightTile();	
	//

	//현재 타일을 기점으로 상하좌우의 이동가능 타일의 개수가 정확히 1개일 경우 참값을 반환.
	//BOOL isOnlyOneWay();
	//그리고 그 타일을 반환
	//tile *wayTile();

};


class tileSet
{
private:
	//타일셋 시작점
	CPoint tileSetPos;

	//타일의 갯수(행 x 열)
	int col, row;

	//타일셋 배열
	vector<vector<tile> > vtile;

	//타일셋 Resource Image
	CImage tileSetImage;

	int eachTileWidth, eachTileHeight;

protected:
	Utility DrawUI;

public:
	//map Name
	CString MapName;

	//Focus 된 tile
	tile* ftile;

	//이전에  Focus되었던 tile(수동 입력 필요)
	tile* bftile;

	//타일 셋 생성자(행 갯수 , 열 갯수, 타일 셋 시작 x좌표, y좌표, 각 타일의 가로, 세로, 타일 이미지 출력에 사용될 ResourceID.
	//column = 특정 세로줄을 의미. colNum은 세로줄의 갯수, 즉 가로 갯수 , row = 특정 가로줄을 의미. rowNum은 가로줄의 갯수, 즉 세로 갯수
	//다시말하면 colNum x rowNum 은 (가로개수 x 세로개수) 가 된다.
	tileSet(int colNum, int rowNum, int start_xpos, int start_ypos, int width, int height, int ResourceID);	

	~tileSet();		//타일 셋 소멸자.
	void setEachTilePos(int start_xpos, int start_ypos, int width, int height);	//각 타일의 위치 및 크기를 결정.

	void setEachTileID(vector<vector<int> >mapArray);	//각 타일의 ID값을 한꺼번에 받아서 설정(Load)
	void setEachTileID(vector<int> mapArray);
	void drawTileSet(CDC *pDC);	//타일 셋을 한꺼번에 그린다.
	BOOL isInTile(CPoint pos);	//매개변수로 받은 point가 특정 타일에 있을 경우, 그 타일을 focus tile로 만들고, TRUE 반환. 없을 시 FALSE 반환.
	CRect getTileSetRect();	//타일 전체의 Rect를 반환한다.
	tile *rpTile(int index);	//해당 타일을 리턴


	int getAllTileNum();	//모든 타일의 개수를 반환한다	
	vector<vector<int> > returnTileArray();		//타일을 2차원 벡터 배열로 반환
	vector<int> getTileSetArray();	//tile Array를 일차원 벡터 배열로 반환.
	int getEachTileID(int _col, int _row);	//해당하는 tile의 ID값을 반환.	
	int getStartPosNum();	//시작/끝점의 개수를 반환한다.
	int getEndPosNum();	

	CPoint rStartPos();	//시작/끝점 위치를 반환한다.
	CPoint rEndPos();	
	tile *rStartTile();
	tile *rEndTile();

	BOOL isCanAvailableSave();	//게임 시작이 가능한 맵인지.(시작점 정확하게 2개, 각 길에서 다음 길로 연결된 Walkable val TRUE인 통로 무조건 1개)

};

#endif