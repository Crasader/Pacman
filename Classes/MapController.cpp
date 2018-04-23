#include "MapController.h"
#include "Ghost.h"
#include "TileFood.h"
#include "IntroScene.h"
#include "StaticStorage.h"

//------------------- CREATE OBJECT FUNCTION (PROTECTED) ----------------------- //

Pacman * MapController::createPacman(int col, int row)
{
	Pacman* instance = Pacman::create();
	instance->initialize(Sprite::create("block.png"), "", this);
	instance->sprite->setContentSize(Size(blockSize, blockSize));
	instance->sprite->setScale(1.3f);
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	instance->beforeMovingPosition = instance->getPosition();
	instance->setSpeed(100);
	instance->setZOrder(2);
	instance->setContentSize(instance->sprite->getContentSize() / 2);
	return instance;
}

Ghost * MapController::createGhost(int col, int row)
{
	Ghost* instance = Ghost::create();
	instance->initialize(Sprite::create("block.png"), "", this);
	instance->sprite->setContentSize(Size(blockSize, blockSize));
	instance->sprite->setScale(1.3f);
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	instance->beforeMovingPosition = instance->getPosition();
	instance->setSpeed(100);
	instance->setZOrder(1);
	instance->setContentSize(instance->sprite->getContentSize() / 2);
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
	foodCount++;
	auto instance = TileFood::create();
	instance->initialize(Sprite::createWithSpriteFrameName("(86).png"), "", this);
	instance->sprite->setContentSize(Size(blockSize, blockSize));
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	return instance;
}

TileBigFood * MapController::createTileBigFood(int col, int row)
{
	foodCount++;
	auto instance = TileBigFood::create();
	instance->initialize(Sprite::createWithSpriteFrameName("(86).png"), "", this);
	instance->sprite->setColor(Color3B::YELLOW);
	instance->setScale(1.3f);
	instance->sprite->setContentSize(Size(blockSize, blockSize));
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	return instance;
}

TileBlock * MapController::createTileBlock(int col, int row)
{
	auto instance = TileBlock::create();
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	return instance;
}

TileBlock * MapController::createTileFree(int col, int row)
{
	auto instance = TileBlock::create();
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	instance->mapController = this;
	return instance;
}

TileBase * MapController::createTileBase(int col, int row)
{
	auto instance = TileBase::create();
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	instance->mapController = this;
	return instance;
}

TileDoor * MapController::createTileDoor(int col, int row)
{
	auto instance = TileDoor::create();
	instance->setPosition(getBlockOrigin() + Vec2(col * blockSize, -row * blockSize));
	instance->mapController = this;
	return instance;
}

Vec2 MapController::getBlockOrigin()
{
	return Vec2(blockSize / 2.0f, -blockSize / 2.0f);
}

//-------------------- GAMEPLAY FUNTION (PUBLIC) -------------------------- //

void MapController::changeGhostForm(GhostForm form)
{
	for each(Ghost* ghost in ghosts) {
		ghost->changeForm(form, { GhostForm::Eaten });
	}
}

void MapController::releaseGhost(float deltaTime)
{
	elapsedTime += deltaTime;
	if (ghostCount < ghosts.size() && elapsedTime >= ghostCount * 8) {
		ghosts.at(ghostCount)->changeForm(GhostForm::Door);
		ghostCount++;
	}
}

void MapController::respawn()
{
	if (lifeCount > 0) {
		player->respawn();
		for (int i = 0; i < ghosts.size(); i++) {
			ghosts.at(i)->respawn();
		}
		elapsedTime = 0;
		ghostCount = 0;
		wait(1.5f);
	}
	else { // LOSE
		StaticStorage::stringValue = "GAME OVER\nPRESS ANY KEY TO CONTINUE";
		this->getEventDispatcher()->removeAllEventListeners();
		Director::getInstance()->replaceScene(IntroScene::createScene());
	}
	lifeCount--;
	lifeLabel->setString(" x " + std::to_string(lifeCount));
}

void MapController::wait(float waitTime)
{
	this->waitTime = waitTime;
}

bool MapController::init()
{
	Vec2 origin = Vec2::ZERO;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 downRight = origin + Vec2(visibleSize.width, -visibleSize.height);
	Vec2 center = (origin + downRight) / 2;

	auto sprite = Sprite::createWithSpriteFrameName(" (7).png");
	sprite->setPosition(Vec2(center.x - 10, downRight.y + sprite->getBoundingBox().size.height));
	this->addChild(sprite);

	this->lifeLabel = Label::createWithSystemFont(" x " + std::to_string(lifeCount), "Arial", 15);
	lifeLabel->setPosition(Vec2(center.x + 10, downRight.y + sprite->getBoundingBox().size.height));
	this->addChild(lifeLabel);

	this->scheduleUpdate();
	return true;
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

	
	this->face = Sprite::create("maze3.png");
	
	auto oriSize = face->getContentSize();
	float scaleX = blockSize * 28 / oriSize.width;
	float scaleY = blockSize * 31 / oriSize.height;

	this->face->setZOrder(-1);
	this->face->setScale(scaleX, scaleY);
	Vec2 ori = this->face->getBoundingBox().size / 2;
	this->face->setPosition(Vec2(ori.x + blockSize, -ori.y));
	this->addChild(this->face);
}

void MapController::parseMap()
{
	TileTeleport* temp = nullptr;
	for (int i = 0; i < map.size(); i++) {
		Vector<TileMap*> line;
		for (int j = 0; j < map.at(i).size(); j++) {
			char item = map.at(i).at(j);
			if (item == '+' || item == '=' || item == '-' ||
				item == '|' || item == ':' || item == 'X' || item == 'G') {
				auto block = createTileBlock(j, i);
				this->addChild(block);
				line.pushBack(block);
			}
			else if (item == 'T') {
				if (temp == nullptr) {
					temp = createTileTeleport(j, i, Direction::Left);
					this->addChild(temp);
					line.pushBack(temp);
				}
				else {
					auto tile = createTileTeleport(j, i, Direction::Right);
					tile->linkTwoSide(temp);
					this->addChild(tile);
					line.pushBack(tile);
				}
			}
			else if (item == 'E') {
				for (int k = 0; k < 4; k++) {
					auto enemy = createGhost(j, i);
					this->addChild(enemy);
					ghosts.pushBack(enemy);
				}
				enemySpawn = createTileFree(j, i);
				line.pushBack(enemySpawn);
			}
			else if (item == 'D') {
				door = createTileDoor(j, i);
				this->addChild(door);
				line.pushBack(door);
			}
			else if (item == '1') {
				player = createPacman(j, i);
				this->addChild(player);

				playerSpawn = createTileFree(j, i);
				this->addChild(playerSpawn);
				line.pushBack(playerSpawn);
			}
			else if (item == '9') {
				auto tileFood = createTileFood(j, i);
				this->addChild(tileFood);
				line.pushBack(tileFood);
			}
			else if (item == '5') {
				auto tileBigFood = createTileBigFood(j, i);
				this->addChild(tileBigFood);
				line.pushBack(tileBigFood);
			}
			else if (item == 'B') {
				this->base = createTileBase(j, i);
				this->addChild(this->base);
				line.pushBack(base);
			}
			else {
				line.pushBack(createTileFree(j, i));
			}
		}
		mapObject.push_back(line);
	}
	for (int i = 0; i < ghosts.size(); i++) {
		ghosts.at(i)->setGhostColor(i);
		ghosts.at(i)->setDefaultRadius(250 + 100 * i);
		ghosts.at(i)->changeForm(GhostForm::Base);
	}
	this->ready = true;
	this->respawn();
}

bool MapController::isWalkable(Vec2 position, GhostForm form)
{
	int row = (int)(-position.y / blockSize);
	int col = (int)(position.x / blockSize);
	char item = map.at(row).at(col);

	std::vector<char> banList = { '+', '=', '-', '|', ':', 'X', 'U' };
	if (form != GhostForm::Eaten && form != GhostForm::Door) {
		banList.push_back('G');
	}

	return std::find(banList.begin(), banList.end(), item) == banList.end();
}

bool MapController::isPositionValid(Vec2 position)
{
	Vec2 topLeft = mapObject.at(0).at(0)->getPosition();
	Vec2 bottomRight = mapObject.at(mapObject.size() - 1).at(mapObject.at(mapObject.size() - 1).size() - 1)->getPosition();
	if (position.x < topLeft.x || position.x > bottomRight.x ||
		position.y > topLeft.y || position.y < bottomRight.y) {
		return false;
	}
	return true;
}

char MapController::positionToChar(Vec2 position) {
	int row = (int)(-position.y / blockSize);
	int col = (int)(position.x / blockSize);
	return map.at(row).at(col);
}

TileMap * MapController::positionToObject(Vec2 position)
{
	int row = (int)(-position.y / blockSize);
	int col = (int)(position.x / blockSize);
	return this->mapObject.at(row).at(col);
}

Vec2 MapController::getNearestPosition(Vec2 source, Vec2 des, Vec2 passedPosition, GhostForm form)
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
	std::random_shuffle(std::begin(posArray), std::end(posArray));

	float minDistance = std::numeric_limits<float>::max();
	for (int i = 0; i < 4; i++) {
		if (isPositionValid(posArray[i]) && isWalkable(posArray[i], form) && posArray[i] != passedPosition) {
			float distance = posArray[i].distance(desPos);
			if (minDistance > distance) {
				minDistance = distance;
				min = posArray[i];
			}
		}
	}
	return min;
}

Vec2 MapController::getFurthestPosition(Vec2 source, Vec2 des, Vec2 passedPosition, GhostForm form) {
	Vec2 pos = source;
	Vec2 desPos = des;
	Vec2 max = pos;
	Vec2 posArray[4] = {
		pos + Vec2(0, blockSize),
		pos + Vec2(0, -blockSize),
		pos + Vec2(-blockSize, 0),
		pos + Vec2(blockSize, 0)
	};
	std::random_shuffle(std::begin(posArray), std::end(posArray));

	float maxDistance = -1;
	for (int i = 0; i < 4; i++) {
		if (isPositionValid(posArray[i]) && isWalkable(posArray[i], form) && posArray[i] != passedPosition) {
			float distance = posArray[i].distance(desPos);
			if (maxDistance < distance) {
				maxDistance = distance;
				max = posArray[i];
			}
		}
	}
	return max;
}

Vec2 MapController::getRandomPosition(Vec2 source, Vec2 passedPosition)
{
	Vec2 pos = source;
	Vec2 posArray[4] = {
		pos + Vec2(0, blockSize),
		pos + Vec2(0, -blockSize),
		pos + Vec2(-blockSize, 0),
		pos + Vec2(blockSize, 0)
	};
	std::random_shuffle(std::begin(posArray), std::end(posArray));

	for (int i = 0; i < 4; i++) {
		if (isPositionValid(posArray[i]) && isWalkable(posArray[i]) && posArray[i] != passedPosition) {
			return posArray[i];
		}
	}
	return pos;
}

void MapController::reduceFoodCount()
{
	foodCount--;
	if (isWin()) {
		/*WIN*/
		StaticStorage::stringValue = "YOU WIN\nPRESS ANY KEY TO CONTINUE";
		this->getEventDispatcher()->removeAllEventListeners();
		Director::getInstance()->replaceScene(IntroScene::createScene());
	}
}

bool MapController::isWin()
{
	return foodCount <= 0;
}

bool MapController::isReady()
{
 	return ready && waitTime <= 0;
}

void MapController::update(float deltaTime)
{
	if (waitTime <= 0) {
		releaseGhost(deltaTime);
	}
	else {
		waitTime -= deltaTime;
	}
}

MapController::MapController()
{
	this->blockSize = 16;
	this->ready = false;
}

MapController::~MapController()
{
}
