#pragma once

#include "cocos2d.h"
#include "Pacman.h"
#include "Ghost.h"
#include "TileTeleport.h"
#include "TileFood.h"
#include "TileBlock.h"

USING_NS_CC;

class MapController : public Node
{
protected:
	int foodCount = 0;
	bool ready;

public:
	int blockSize;
	std::vector<std::vector<char>> map;
	std::vector<std::vector<TileMap*>> mapObject;
	Pacman* player;

protected:
	Pacman* createPacman(int col, int row);
	Ghost* createGhost(int col, int row);
	TileTeleport* createTileTeleport(int col, int row, Direction dir);
	TileFood* createTileFood(int col, int row);
	TileBlock* createTileBlock(int col, int row);
	TileMap* createTileFree(int col, int row);
	Vec2 getBlockOrigin();
	
public:
	CREATE_FUNC(MapController);

	/**
	  * Mở file theo fileName 
	  * Sau đó phân tích file đó rồi truyền dữ liệu vào map
	  *
	  * @param fileName: tên file cần đọc (relative path)
	*/
	virtual void loadFile(std::string fileName);

	/**
	  * Đọc dữ liệu từ map và chuyển đổi chúng sang các object trong game
	  */
	virtual void parseMap();

	/**
	  * Kiểm tra xem vị trí truyền vào có thể đi được không
	  *
	  * @param position: là điểm ta cần xét, ta quy chiếu nó xuống map xem có đi được không 
	  * @return: true nếu đi được, false nếu không đi được
	  */
	virtual bool isWalkable(Vec2 position); 

	virtual char positionToChar(Vec2 position);

	virtual TileMap* positionToObject(Vec2 position);

	virtual Vec2 getNearestPositionIgnore(Vec2 source, Vec2 passedPosition);

	virtual Vec2 getNearestPosition(Vec2 source);

	virtual Vec2 getNearestPosition(Vec2 source, Vec2 des);

	virtual void reduceFoodCount();

	virtual bool isWin();

	virtual bool isReady();
public:
	MapController();
	~MapController();
};
