#pragma once

enum class Direction {
	Null = -1,
	Up = 0,
	Right = 1,
	Down = 2,
	Left = 3
};

enum class GhostForm {
	Good,
	Bad,
	Eaten,
	Door,
	Base
};