#pragma once

#include "cocos2d.h"
#include "Pacman.h"

USING_NS_CC;

class MapController : public Node
{
protected:
	float minX;
	float maxX;
	float minY;
	float maxY;

public:
	int blockSize;
	std::vector<std::vector<char>> map;
	std::vector<std::vector<StaticObject*>> mapObject;
	Pacman* player;
	
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

	virtual StaticObject* positionToObject(Vec2 position);

	virtual bool isPositionValid(Vec2 position);

	virtual Vec2 getNearestPositionIgnore(Vec2 source, Vec2 passedPosition);

	virtual Vec2 getNearestPosition(Vec2 source);

	virtual Vec2 getNearestPosition(StaticObject* source);
	
	virtual Vec2 getNearestPosition(StaticObject* source, StaticObject* des);

	virtual Vec2 getNearestPosition(Vec2 source, Vec2 des);

public:
	MapController();
	~MapController();
};
