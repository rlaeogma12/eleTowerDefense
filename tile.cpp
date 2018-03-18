#include "stdafx.h"
#include "tile.h"
#include "tower.h"
////
//tile 구현
////
tile::tile()
{
	tilePos.SetPoint(0, 0);
	setSize(0, 0);
	setTileID(0);
	tileTower = NULL;	//tower ID 값 초기값 0 )건설되지 않음을 의미.
	tileIndex = 0;
	pParent = NULL;
}


tile::~tile()
{
}

void tile::setPos(int x_pos, int y_pos)
{
	tilePos.SetPoint(x_pos, y_pos);
}

void tile::setResourcePos(int x_pos, int y_pos)
{
	resourcePos.SetPoint(x_pos, y_pos);
}

void tile::setSize(int _width, int _height)
{
	width = _width;
	height = _height;
}

void tile::setTileID(int _tileID)
{
	tileID = _tileID;

	//tile ID에 따른 설정
	switch (tileID) {
	//0 : 빈 공간
	case 0:
		isWalk = FALSE;
		isBuild = FALSE;
		setResourcePos(0, 0);
		break;

	//1 : 밝은 진흙(건설 불가, 이동 가능)
	case 1:
		isWalk = TRUE;
		isBuild = FALSE;
		setResourcePos(0, 32);
		break;

	//2 : 어두운 진흙 (건설 불가, 이동 가능)
	case 2:
		isWalk = TRUE;
		isBuild = FALSE;
		setResourcePos(96, 32);
		break;

	//3 : 밝은 풀 (건설 가능, 이동 불가)
	case 3:
		isWalk = FALSE;
		isBuild = TRUE;
		setResourcePos(192, 32);
		break;

	//4 : 밝은 진흙(깔끔한 ver. 1,2와 동일)
	case 4:
		isWalk = TRUE;
		isBuild = FALSE;
		setResourcePos(288, 32);
		break;

	//5 : 밝은 풀(3과 동일)
	case 5:
		isWalk = FALSE;
		isBuild = TRUE;
		setResourcePos(432, 32);
		break;

	//6 : 적갈색 대지(시작점)
	case 6:
		isWalk = TRUE;
		isBuild = FALSE;
		setResourcePos(576, 32);
		break;

	//7 : 밝은 갈색 대지(도착점)
	case 7:
		isWalk = TRUE;
		isBuild = FALSE;
		setResourcePos(672, 32);
		break;
		
	//8 : 나무 1 (테두리용)
	case 8:
		isWalk = FALSE;
		isBuild = FALSE;
		setResourcePos(0, 87);
		break;
	//9 : 나무 2
	case 9:
		isWalk = FALSE;
		isBuild = FALSE;
		setResourcePos(48, 87);
		break;
	}
}

void tile::setParent(tileSet * _pParent, int _index)
{
	pParent = _pParent;
	tileIndex = _index;
}

CPoint tile::getResourcePos()
{
	return resourcePos;
}

CRect tile::rRect()
{
	return CRect(tilePos.x, tilePos.y, tilePos.x+width, tilePos.y+height);
}

CPoint tile::rPoint()
{
	return tilePos;
}

int tile::getTileID()
{
	return tileID;
}

BOOL tile::isWalkable(tile *exceptTile)
{
	if (exceptTile != this) {
		return isWalk;
	}
	else {
		return FALSE;
	}
}

BOOL tile::isBuildable()
{
	return isBuild;
}

int tile::getTileIndex()
{
	return tileIndex;
}

void tile::drawTile(CImage *tileImage, CDC * pDC)
{
	if (tileID) { tileImage->Draw(pDC->m_hDC, tilePos.x, tilePos.y, width, height, resourcePos.x, resourcePos.y, width, height); }
}

CPoint tile::rEnemypos()
{
	return tilePos;
}

CRect tile::rTileCenter()
{
	return CRect(tilePos.x + (DEFAULT_TILE_HEIGHT - ENEMY_SIZE) / 2 - REC_RANGE, tilePos.y + (DEFAULT_TILE_HEIGHT - ENEMY_SIZE) / 2 - REC_RANGE, 
		tilePos.x + (DEFAULT_TILE_HEIGHT - ENEMY_SIZE) / 2 + REC_RANGE, tilePos.y + (DEFAULT_TILE_HEIGHT - ENEMY_SIZE) / 2 + REC_RANGE);
}

tile * tile::upTile()
{
	if (pParent) 
	{
		return pParent->rpTile(tileIndex - STANDARD_COL);
	}
	else 
	{ 
		return NULL;
	}
}

tile * tile::downTile()
{
	if (pParent)
	{
		return pParent->rpTile(tileIndex + STANDARD_COL);
	}
	else
	{
		return NULL;
	}
}

tile * tile::leftTile()
{
	if (pParent)
	{
		return pParent->rpTile(tileIndex - 1);
	}
	else
	{
		return NULL;
	}
}

tile * tile::rightTile()
{
	if (pParent)
	{
		return pParent->rpTile(tileIndex + 1);
	}
	else
	{
		return NULL;
	}
}


////
//tileSet 구현.
////
tileSet::tileSet(int colNum, int rowNum, int start_xpos, int start_ypos, int width, int height, int ResourceID)
{
	col = colNum;
	row = rowNum;

	eachTileWidth = width;
	eachTileHeight = height;

	MapName = L"Standard Map";
	bftile = NULL;
	ftile = NULL;
	//col x row 2차원배열 생성
	for (int i = 0; i < col; i++) {
		vector<tile> elem;
		elem.resize(row);
		vtile.push_back(elem);
	}

	//각 타일의 위치 및 크기 설정.
	setEachTilePos(start_xpos, start_ypos, width, height);

	//포커스된 기본 tile은 [0][0].
	ftile = &(vtile[0][0]);

	//타일셋에 쓰일 이미지 초기화.
	DrawUI.SetImage(&tileSetImage, ResourceID, _T("PNG"));
}

tileSet::~tileSet()
{
	//2차원 배열 소멸
	for (int i = 0; i < (int)vtile.size(); i++) {
		vtile[i].clear();
	}
	vtile.clear();
}

void tileSet::setEachTilePos(int start_xpos, int start_ypos, int width, int height)
{
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			vtile[i][j].setSize(width, height);
			vtile[i][j].setParent(this, i + j*col);
			vtile[i][j].setPos(start_xpos + width*i, start_ypos + height*j);
		}
	}
}

void tileSet::setEachTileID(vector<vector<int>> mapArray)
{
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			vtile[i][j].setTileID(mapArray[i][j]);
		}
	}
}

void tileSet::setEachTileID(vector<int> mapArray) 
{
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			vtile[i][j].setTileID(mapArray[i*row + j]);
		}
	}
}

void tileSet::drawTileSet(CDC * pDC)
{
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			vtile[i][j].drawTile(&tileSetImage, pDC);
		}
	}
}

BOOL tileSet::isInTile(CPoint pos)
{
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			if (vtile[i][j].rRect().PtInRect(pos)) {
				ftile = &(vtile[i][j]);
				return TRUE;
			}
		}
	}
	return FALSE;
}

CRect tileSet::getTileSetRect()
{
	return CRect(tileSetPos.x, tileSetPos.y, tileSetPos.x+eachTileWidth*col, tileSetPos.y+eachTileWidth*row);
}

tile * tileSet::rpTile(int index)
{
	if(index >= 0 || index < STANDARD_COL * STANDARD_ROW)
	{
		return &vtile[index % STANDARD_COL][index / STANDARD_COL];
	}
	else
	{
		return NULL;
	}	
}

vector<vector<int>> tileSet::returnTileArray()
{
	vector<vector<int> > tempTileSet;
	for (int i = 0; i < col; i++) {
		vector<int> element;
		element.resize(row);
		tempTileSet.push_back(element);
	}

	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			tempTileSet[i][j] = vtile[i][j].getTileID();
		}
	}

	return tempTileSet;
}

BOOL tileSet::isCanAvailableSave()
{
	//시작점 갯수와 끝점 갯수가 1개이고..
	if (getStartPosNum() == 1 && getEndPosNum() == 1) {
		return TRUE;
	}

	return FALSE;
}

int tileSet::getAllTileNum()
{
	return col*row;
}

vector<int> tileSet::getTileSetArray()
{
	vector<int> tempArray;
	tempArray.resize(row*col);
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			tempArray[i*row + j] = vtile[i][j].getTileID();
		}		
	}
	return tempArray;
}

int tileSet::getEachTileID(int _col, int _row)
{
	return vtile[_col][_row].getTileID();
}

int tileSet::getStartPosNum()
{
	int result = 0;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			if (vtile[i][j].getTileID() == ENEMY_START_TILEID) { result++; }
		}
	}
	return result;
}

int tileSet::getEndPosNum()
{
	int result = 0;
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			if (vtile[i][j].getTileID() == ENEMY_END_TILEID) { result++; }
		}
	}
	return result;
}

CPoint tileSet::rStartPos()
{
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			if (vtile[i][j].getTileID() == ENEMY_START_TILEID) {
				return vtile[i][j].rPoint();
			}
		}
	}
	return CPoint(0, 0);
}

CPoint tileSet::rEndPos()
{
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			if (vtile[i][j].getTileID() == ENEMY_END_TILEID) {
				return vtile[i][j].rPoint();
			}
		}
	}
	return CPoint(0, 0);
}

tile * tileSet::rStartTile()
{
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			if (vtile[i][j].getTileID() == ENEMY_START_TILEID) {
				return &vtile[i][j];
			}
		}
	}
	return nullptr;
}

tile * tileSet::rEndTile()
{
	for (int i = 0; i < col; i++) {
		for (int j = 0; j < row; j++) {
			if (vtile[i][j].getTileID() == ENEMY_END_TILEID) {
				return &vtile[i][j];
			}
		}
	}
	return nullptr;
}
