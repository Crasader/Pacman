#include "MapController.h"
#include "Ghost.h"
#include "TileFood.h"

//------------------- CREATE OBJECT FUNCTION (PROTECTED) ----------------------- //

Pacman * MapController::createPacman(int col, int row)
{
	Pacman* instance = Pacman::create();
	instance->initialize(Sprite::create("block.png"), "", this);
	instance->sprite->setContentSize(Size(blockSize, blockSize));
	instance->sprite->setColor(Color3B(255, 100, 100));
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	instance->beforeMovingPosition = instance->getPosition();
	instance->setSpeed(100);
	instance->setZOrder(2);
	return instance;
}

Ghost * MapController::createGhost(int col, int row)
{
	Ghost* instance = Ghost::create();
	instance->initialize(Sprite::create("block.png"), "", this);
	instance->sprite->setContentSize(Size(blockSize, blockSize));
	instance->sprite->setColor(Color3B(100, 100, 100));
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	instance->beforeMovingPosition = instance->getPosition();
	instance->setSpeed(100);
	instance->setZOrder(2);
	return instance;
}

TileTeleport * MapController::createTileTeleport(int col, int row, Direction dir)
{
	TileTeleport* instance = TileTeleport::create();
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	instance->triggerDirection = dir;
	return instance;
}

TileFood * MapController::createTileFood(int col, int row)
{
	auto instance = TileFood::create();
	instance->initialize(Sprite::create("block.png"), "", this);
	instance->sprite->setColor(Color3B(0, 100, 200));
	instance->sprite->setContentSize(Size(blockSize, blockSize));
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	return instance;
}

TileBlock * MapController::createTileBlock(int col, int row)
{
	auto instance = TileBlock::create();
	instance->initialize(Sprite::create("block.png"), "", this);
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	instance->sprite->setContentSize(Size(blockSize, blockSize));
	return instance;
}

TileMap * MapController::createTileFree(int col, int row)
{
	auto instance = TileBlock::create();
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	return instance;
}

Vec2 MapController::getBlockOrigin()
{
	return Vec2(blockSize / 2.0f, -blockSize / 2.0f);
}


//-------------------- CORE FUNCTION (PUBLIC) ---------------------------- //

void MapController::loadFile(std::string fileName)
{
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
	TileTeleport* temp = nullptr;
	for (int i = 0; i < map.size(); i++) {
		std::vector<TileMap*> line;
		for (int j = 0; j < map[i].size(); j++) {
			char item = map[i][j];
			if (item == '+' || item == '=' || item == '-' ||
				item == '|' || item == ':' || item == 'X') {
				auto block = createTileBlock(j, i);
				this->addChild(block);
				line.push_back(block);
			}
			else if (item == 'T') {
				if (temp == nullptr) {
					temp = createTileTeleport(j, i, Direction::Left);
					this->addChild(temp);
					line.push_back(temp);
				}
				else {
					auto tile = createTileTeleport(j, i, Direction::Right);
					tile->linkTwoSide(temp);
					this->addChild(tile);
					line.push_back(tile);
				}
			}
			else if (item == 'E') {
				auto enemy = createGhost(j, i);
				this->addChild(enemy);
				line.push_back(createTileFree(j, i));
			}
			else if (item == '1') {
				player = createPacman(j, i);
				this->addChild(player);
				line.push_back(createTileFree(j, i));
			}
			else if (item == '9') {
				auto tileFood = createTileFood(j, i);
				this->addChild(tileFood);
				line.push_back(tileFood);
			}
			else {
				line.push_back(createTileFree(j, i));
			}
		}
		mapObject.push_back(line);
	}

	this->ready = true;
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

TileMap * MapController::positionToObject(Vec2 position)
{
	int row = (int)(-position.y / blockSize);
	int col = (int)(position.x / blockSize);
	return this->mapObject[row][col];
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

bool MapController::isWin()
{
	return foodCount <= 0;
}

void MapController::reduceFoodCount()
{
	foodCount--;
	if (isWin()) {
		/*WIN*/
	}
}

bool MapController::isReady()
{
 	return ready;
}

MapController::MapController()
{
	this->blockSize = 16;
	this->ready = false;
}

MapController::~MapController()
{
}
