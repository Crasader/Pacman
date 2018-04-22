#include "TileBigFood.h"
#include "MapController.h"


bool TileBigFood::initialize(Sprite * sprite, std::string labelText, MapController * mapController)
{
	TileMap::initialize(sprite, labelText, mapController);
	animateList.pushBack(getAnimate({ "(87).png", "(88).png" }, 0.5f));
	setAnimate(animateList.at(0));
	return true;
}

bool TileBigFood::triggerTile(Pacman * node, Direction direction)
{
	if (TileMap::triggerTile(node, direction)) {
		mapController->reduceFoodCount();
		this->sprite->setColor(Color3B(0, 0, 0));
		this->activate(false);
		mapController->changeGhostForm(GhostForm::Good);
		return true;
	}
	return false;
}

TileBigFood::TileBigFood() : TileMap()
{
	this->active = true;
}


TileBigFood::~TileBigFood()
{
}
