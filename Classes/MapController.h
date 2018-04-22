#pragma once

#include "cocos2d.h"
#include "Pacman.h"
#include "Ghost.h"
#include "TileTeleport.h"
#include "TileFood.h"
#include "TileBlock.h"
#include "TileBase.h"
#include "TileBigFood.h"
USING_NS_CC;

class MapController : public Node
{
protected:
	int foodCount = 0;
	bool ready;
	Sprite* face;

public:
	int blockSize;
	std::vector<std::vector<char>> map;
	std::vector<Vector<TileMap*>> mapObject;

	Pacman* player;
	TileBase* base;
	Vector<Ghost*> ghosts;

protected:
	Pacman* createPacman(int col, int row);
	Ghost* createGhost(int col, int row);
	TileTeleport* createTileTeleport(int col, int row, Direction dir);
	TileFood* createTileFood(int col, int row);
	TileBigFood* createTileBigFood(int col, int row);
	TileBlock* createTileBlock(int col, int row);
	TileBlock* createTileFree(int col, int row);
	TileBase* createTileBase(int col, int row);

	Vec2 getBlockOrigin();
	
public: /* Các hàm tính năng trong ingame */
	virtual void changeGhostForm(GhostForm form);

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
	  * @param form: nếu là pacman thì không quan tâm, nếu là ghost sẽ xác định một số điểm có thể qua đư
	  * @return: true nếu đi được, false nếu không đi được
	  */
	virtual bool isWalkable(Vec2 position, GhostForm form = GhostForm::Bad);

	virtual bool isPositionValid(Vec2 position);

	virtual char positionToChar(Vec2 position);

	virtual TileMap* positionToObject(Vec2 position);

	virtual Vec2 getNearestPosition(Vec2 source, Vec2 des, Vec2 passedPosition, GhostForm form = GhostForm::Bad);

	virtual Vec2 getFurthestPosition(Vec2 source, Vec2 des, Vec2 passedPosition, GhostForm form = GhostForm::Bad);

	virtual void reduceFoodCount();

	virtual bool isWin();

	virtual bool isReady();
public:
	MapController();
	~MapController();
};
