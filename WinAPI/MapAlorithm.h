#pragma once
#include "Tiles.h"

class MapAlorithm
{
	struct arrivalList
	{
		POINT point;
		bool state;
	};

protected:
	POINT _sizeField;
	POINT _sizeTile;

	vector<vector<Tile>> _tiles;
	void _scalingMap();
	void _impossibleMap();

	vector<pair<POINT, int>> vArrival;
	bool _roadMake();

	vector<POINT> door;
	bool _doorMake(Tile::Type);

public:
	vector<vector<Tile>> getTileMap();
	vector<POINT> getDoor();
	vector<pair<POINT, int>> getArrival() { return vArrival; }

	MapAlorithm();
	~MapAlorithm();
};

