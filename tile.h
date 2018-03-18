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
	//Ÿ���� ��ġ
	CPoint tilePos;

	//Ÿ���� ũ��
	int width, height;

	//Ÿ�� ID
	//0 : �� ����, 1 : ���� , 2 : Ǯ, 3 : 
	int tileID;

	//Ÿ�� ID�� ���� ���ҽ� ��ġ
	CPoint resourcePos;

	//Ÿ�� ID�� ���� �ǹ�/�̵����� ����
	BOOL isWalk, isBuild;

	//TileSet�� ������ ���� tile Index
	int tileIndex;

	//�� Ÿ���� �θ� Ÿ�ϼ� ������
	tileSet *pParent;


public:
	//�� Ÿ�Ͽ� ������ Tower ID
	//0 : �������� ����. 1... : �� Ÿ���� ID Value
	tower *tileTower;

	//tile ������
	tile();

	//tile �Ҹ���
	~tile();

	//set�Լ� ����.
	//��ġ ����
	void setPos(int x_pos, int y_pos);

	//Ÿ���� ������ ����
	void setSize(int width, int height);

	//Ÿ�� ID ����
	void setTileID(int _tileID);

	//Ÿ�� �θ� �� index ����
	void setParent(tileSet *_pParent, int _index);

	//Tile ID�� ���� set ����
	//���ҽ� ��ġ ����
	void setResourcePos(int x_pos, int y_pos);

	//get�Լ� ����.
	//Resource Position�� �޾ƿ´�.
	CPoint getResourcePos();

	//�� Ÿ���� Rect ��ȯ.
	CRect rRect();

	//�� Ÿ���� pos ��ȯ.
	CPoint rPoint();

	//�� Ÿ���� tileID ��ȯ
	int getTileID();

	//�� Ÿ���� �̵��������� ��ȯ
	BOOL isWalkable(tile *exceptTile);

	//�Ǽ��������� ��ȯ
	BOOL isBuildable();

	//�� Ÿ���� Parent TileSet���� �ο����� Index���� ��ȯ
	int getTileIndex();

	//Draw�Լ�
	void drawTile(CImage *tileImage,CDC *pDC);

	//���� Ÿ���� Mon ��ġ pos�� ��ȯ.(enemy ��ü�� ������ ������ CPoint�� �˸��� ����)
	CPoint rEnemypos();

	//���� Ÿ���� Mon ���� 3��ŭ�� rect�� ��ȯ(enemy ��ü�� �ش� ��ġ�� �����ߴ��� �ν��ϱ� ����)
	CRect rTileCenter();

	//���� Ÿ���� ��, �Ʒ�, ��, ���� Ÿ���� ��ȯ(�̵� �� �ʿ�)
	tile *upTile();
	tile *downTile();
	tile  *leftTile();
	tile *rightTile();	
	//

	//���� Ÿ���� �������� �����¿��� �̵����� Ÿ���� ������ ��Ȯ�� 1���� ��� ������ ��ȯ.
	//BOOL isOnlyOneWay();
	//�׸��� �� Ÿ���� ��ȯ
	//tile *wayTile();

};


class tileSet
{
private:
	//Ÿ�ϼ� ������
	CPoint tileSetPos;

	//Ÿ���� ����(�� x ��)
	int col, row;

	//Ÿ�ϼ� �迭
	vector<vector<tile> > vtile;

	//Ÿ�ϼ� Resource Image
	CImage tileSetImage;

	int eachTileWidth, eachTileHeight;

protected:
	Utility DrawUI;

public:
	//map Name
	CString MapName;

	//Focus �� tile
	tile* ftile;

	//������  Focus�Ǿ��� tile(���� �Է� �ʿ�)
	tile* bftile;

	//Ÿ�� �� ������(�� ���� , �� ����, Ÿ�� �� ���� x��ǥ, y��ǥ, �� Ÿ���� ����, ����, Ÿ�� �̹��� ��¿� ���� ResourceID.
	//column = Ư�� �������� �ǹ�. colNum�� �������� ����, �� ���� ���� , row = Ư�� �������� �ǹ�. rowNum�� �������� ����, �� ���� ����
	//�ٽø��ϸ� colNum x rowNum �� (���ΰ��� x ���ΰ���) �� �ȴ�.
	tileSet(int colNum, int rowNum, int start_xpos, int start_ypos, int width, int height, int ResourceID);	

	~tileSet();		//Ÿ�� �� �Ҹ���.
	void setEachTilePos(int start_xpos, int start_ypos, int width, int height);	//�� Ÿ���� ��ġ �� ũ�⸦ ����.

	void setEachTileID(vector<vector<int> >mapArray);	//�� Ÿ���� ID���� �Ѳ����� �޾Ƽ� ����(Load)
	void setEachTileID(vector<int> mapArray);
	void drawTileSet(CDC *pDC);	//Ÿ�� ���� �Ѳ����� �׸���.
	BOOL isInTile(CPoint pos);	//�Ű������� ���� point�� Ư�� Ÿ�Ͽ� ���� ���, �� Ÿ���� focus tile�� �����, TRUE ��ȯ. ���� �� FALSE ��ȯ.
	CRect getTileSetRect();	//Ÿ�� ��ü�� Rect�� ��ȯ�Ѵ�.
	tile *rpTile(int index);	//�ش� Ÿ���� ����


	int getAllTileNum();	//��� Ÿ���� ������ ��ȯ�Ѵ�	
	vector<vector<int> > returnTileArray();		//Ÿ���� 2���� ���� �迭�� ��ȯ
	vector<int> getTileSetArray();	//tile Array�� ������ ���� �迭�� ��ȯ.
	int getEachTileID(int _col, int _row);	//�ش��ϴ� tile�� ID���� ��ȯ.	
	int getStartPosNum();	//����/������ ������ ��ȯ�Ѵ�.
	int getEndPosNum();	

	CPoint rStartPos();	//����/���� ��ġ�� ��ȯ�Ѵ�.
	CPoint rEndPos();	
	tile *rStartTile();
	tile *rEndTile();

	BOOL isCanAvailableSave();	//���� ������ ������ ������.(������ ��Ȯ�ϰ� 2��, �� �濡�� ���� ��� ����� Walkable val TRUE�� ��� ������ 1��)

};

#endif