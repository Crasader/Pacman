#include "MapController.h"
#include "TeleportTile.h"
#include "Ghost.h"

void MapController::loadFile(std::string fileName)
{
	this->blockSize = 16;
	Data data = FileUtils::getInstance()->getDataFromFile(fileName);
	char* pBuffer = (char*)data.getBytes();
	std::stringstream ss(pBuffer);
	std::string item;
	while (std::getline(ss, item, '\n')) {
		std::vector<char> line;
		for (int i = 0; i < item.length(); i++) {
			line.push_back(item[i]);
		}
		this->map.push_back(line);
	}
}

void MapController::parseMap()
{
	Vec2 blockOrigin = Vec2(blockSize / 2, -blockSize / 2);
	TeleportTile* temp = nullptr;
	for (int i = 0; i < map.size(); i++) {
		std::vector<StaticObject*> line;
		for (int j = 0; j < map[i].size(); j++) {
			char item = map[i][j];
			if (item == '+' || item == '=' || item == '-' ||
				item == '|' || item == ':' || item == 'X') {
				StaticObject* wall = StaticObject::create();
				wall->initialize(Sprite::create("block.png"), std::to_string(i) + "_" + std::to_string(j));
				wall->setPosition(blockOrigin + Vec2(blockSize * j, -blockSize * i));
				wall->sprite->setContentSize(Size(blockSize, blockSize));
				wall->enableLabel(false);
				this->addChild(wall);
				line.push_back(wall);
			}
			else if (item == 'T') {
				if (temp == nullptr) {
					temp = TeleportTile::create();
					temp->setPosition(blockOrigin + Vec2(blockSize * j, -blockSize * i));
					this->addChild(temp);
					temp->triggerDirection = MovableObject::Direction::Left;
					line.push_back(temp);
				}
				else {
					TeleportTile* tile = TeleportTile::create();
					tile->setPosition(blockOrigin + Vec2(blockSize * j, -blockSize * i));
					this->addChild(tile);
					tile->triggerDirection = MovableObject::Direction::Right;
					tile->linkTwoSide(temp);
					line.push_back(tile);
				}
			}
			else if (item == 'E') {
				auto enemy = Ghost::create();
				enemy->initialize(Sprite::create("block.png"), std::to_string(i) + "_" + std::to_string(j));
				enemy->sprite->setColor(Color3B(200, 100, 200));
				enemy->sprite->setContentSize(Size(blockSize, blockSize));
				enemy->setPosition(blockOrigin + Vec2(blockSize * j, -blockSize * i));
				enemy->beforeMovingPosition = enemy->getPosition();
				enemy->setSpeed(100); // Set player speed
				enemy->setMapController(this); // Set player mapController
				//enemy->setTarget(player);
				this->addChild(enemy);
			}
			else if (item == '1') {
				player = Pacman::create();
				player->initialize(Sprite::create("block.png"), std::to_string(i) + "_" + std::to_string(j));
				player->sprite->setColor(Color3B(100, 100, 100));
				player->sprite->setContentSize(Size(blockSize, blockSize));
				player->setPosition(blockOrigin + Vec2(blockSize * j, -blockSize * i));
				player->beforeMovingPosition = player->getPosition();
				player->setSpeed(100); // Set player speed
				player->setMap(this); // Set player mapController
				this->addChild(player);
				line.push_back(player);
			}
			else {
				line.push_back(nullptr);
			}
		}
		mapObject.push_back(line);
	}

	StaticObject* lastObject = mapObject[mapObject.size() - 1][mapObject[mapObject.size() - 1].size() - 1];
	minX = 0;
	maxY = 0;
	maxX = (map.size() - 1) * blockSize;
	minY = (map[0].size() -1) * blockSize;
}

bool MapController::isWalkable(Vec2 position)
{
	int row = (int)(-position.y / blockSize);
	int col = (int)(position.x / blockSize);
	char item = map[row][col];
	if (item == '+' || item == '=' || item == '-' ||
		item == '|' || item == ':' || item == 'X' ||
		item == 'U') {
		return false;
	}
	return true;
}

char MapController::positionToChar(Vec2 position) {
	int row = (int)(-position.y / blockSize);
	int col = (int)(position.x / blockSize);
	return map[row][col];
}

StaticObject * MapController::positionToObject(Vec2 position)
{
	int row = (int)(-position.y / blockSize);
	int col = (int)(position.x / blockSize);
	return mapObject[row][col];
}

bool MapController::isPositionValid(Vec2 position)
{
	if (position.x < minX || position.x > maxX || position.y < minY || position.y > maxY) {
		return false;
	}
	return true;
}

Vec2 MapController::getNearestPositionIgnore(Vec2 source, Vec2 passedPosition)
{
	Vec2 pos = source;
	Vec2 desPos = player->getPosition();
	Vec2 min = pos;
	Vec2 posArray[4] = {
		pos + Vec2(0, blockSize),
		pos + Vec2(0, -blockSize),
		pos + Vec2(-blockSize, 0),
		pos + Vec2(blockSize, 0)
	};
	std::random_shuffle(std::begin(posArray), std::end(posArray));

	float minDistance = std::numeric_limits<float>::max();
	for (int i = 0; i < 4; i++) {
		if (isWalkable(posArray[i]) && posArray[i] != passedPosition) {
			float distance = posArray[i].distance(desPos);
			if (minDistance > distance) {
				minDistance = distance;
				min = posArray[i];
			}
		}
	}
	return min;
	return Vec2();
}

Vec2 MapController::getNearestPosition(Vec2 source)
{
	return getNearestPosition(source, player->getPosition());
}

Vec2 MapController::getNearestPosition(StaticObject * source)
{
	return getNearestPosition(source, player);
}

Vec2 MapController::getNearestPosition(StaticObject * source, StaticObject * des)
{
	return getNearestPosition(source->getPosition(), des->getPosition());
}

Vec2 MapController::getNearestPosition(Vec2 source, Vec2 des)
{
	Vec2 pos = source;
	Vec2 desPos = des;
	Vec2 min = pos;
	Vec2 posArray[4] = {
		pos + Vec2(0, blockSize),
		pos + Vec2(0, -blockSize),
		pos + Vec2(-blockSize, 0),
		pos + Vec2(blockSize, 0)
	};

	float minDistance = std::numeric_limits<float>::max();
	for (int i = 0; i < 4; i++) {
		if (isWalkable(posArray[i])) {
			float distance = posArray[i].distance(desPos);
			if (minDistance > distance) {
				minDistance = distance;
				min = posArray[i];
			}
		}
	}
	return min;
}

MapController::MapController()
{
}


MapController::~MapController()
{
}
