#include "Stdafx.h"
#include "MapAlorithm.h"
#include <stack>

MapAlorithm::MapAlorithm() { }
MapAlorithm::~MapAlorithm() { }

vector<vector<Tile>> MapAlorithm::getTileMap()
{
	bool callBack = false;
	float percent = 5.75f;
	_sizeTile = { 64, 64 }; _sizeField = { 3840, 1964 };

	while (!callBack)
	{
		_tiles.clear();
		for (int i = 0; i < _sizeField.y; i += _sizeTile.y)
		{
			_tiles.push_back(vector<Tile>());
			for (int h = 0; h < _sizeField.x; h += _sizeTile.x)
			{
				_tiles.back().push_back(Tile());
				_tiles.back().back().gold = -1;
				_tiles.back().back().type = Tile::Type::BACK;
				if (RND->getFloat(10.0f) < 5.75f)
				{
					_tiles.back().back().type = Tile::Type::WALL;
					if (RND->getInt(10) == 0) { _tiles.back().back().gold = RND->getInt(3); }
				}
				_tiles.back().back().object = RECT{ h, i, h + _sizeTile.x, i + _sizeTile.y };
			}
		}
		for (int i = 0; i < 3; i++) { _scalingMap(); } _impossibleMap();
		callBack = _roadMake();
	}

	return _tiles;
}

void MapAlorithm::_scalingMap()
{
	vector<vector<Tile>> vTile = _tiles;
	int count, y, x;
	for (int i = 1; i < _tiles.size() - 1; i++)
	{
		for (int h = 1; h < _tiles[i].size() - 1; h++)
		{
			count = 0;
			for (int p = 0; p <= 8; p++)
			{
				if (p == 4) { continue; }
				else if (p < 3) { y = -1; }
				else if (p < 6) { y = 0; }
				else if (p <= 8) { y = 1; }
				switch (p)
				{
				case 1: case 7: { x = 0; } break;
				case 2: case 5: case 8: { x = 1; } break;
				case 0: case 3: case 6: { x = -1; } break;
				}
				y = i + y; x = h + x;
				if (vTile[y][x].type == Tile::Type::WALL || vTile[y][x].type == Tile::Type::IMPOSSIBLE) { count++; }
			}

			if (count > 4) { _tiles[i][h].type = Tile::Type::WALL; }
			else { _tiles[i][h].type = Tile::Type::BACK; }
		}
	}
}

void MapAlorithm::_impossibleMap()
{
	for (int i = 0; i < _tiles.size(); i++)
	{
		if (i < 2 || i == _tiles.size() - 1 || i == _tiles.size() - 2)
		{
			for (int h = 0; h < _tiles[i].size(); h++) { _tiles[i][h].type = Tile::Type::IMPOSSIBLE; }
		}
		_tiles[i][0].type = _tiles[i][1].type = _tiles[i][_tiles[i].size() - 1].type = _tiles[i][_tiles[i].size() - 2].type = Tile::Type::IMPOSSIBLE;
	}
}

bool MapAlorithm::_roadMake()
{
	if (!_doorMake(Tile::Type::ENTRANCE)) { return false; }

	int x, y; bool search, exit, button;
	vArrival.clear();
	vArrival.push_back({ door[0],false });

	exit = false;
	for (int i = 0; i < vArrival.size(); i++)
	{
		vArrival[i].second = true;
		for (int p = 0; p < 4; p++)
		{
			switch (p)
			{
			case 0: y = -1; x = 0; break;
			case 1: y = 0; x = -1; break;
			case 2: y = 0; x = 1; break;
			case 3: y = 1; x = 0; break;
			}

			y = vArrival[i].first.y + y;
			x = vArrival[i].first.x + x;

			search = false;
			for (int h = 0; h < vArrival.size(); h++)
			{
				if (vArrival[h].first.x == x && vArrival[h].first.y == y)
				{
					search = true;
					break;
				}
			}
			if (search == true)
			{
				continue;
			}

			if (_tiles[y][x].type == Tile::Type::BACK)
			{
				vArrival.push_back({ {x,y},false });
			}
			else if (_tiles[y][x].type == Tile::Type::IMPOSSIBLE || _tiles[y][x].type == Tile::Type::WALL)
			{
				if (p == 3)
				{
					vArrival[i].second = 2; //위
				}
				else if (p == 0)
				{
					vArrival[i].second = 3; //아래
				}
				else
				{
					vArrival[i].second = 4; //벽
				}
			}
		}
	}

	if (vArrival.size() < 550) return false;

	for (int i = 0; i < 2; i++)
	{
		for (int h = 0; h < vArrival.size(); h++)
		{
			switch (i)
			{
			case 0: { 	if (vArrival[h].second == false) { return false; } } break;
			case 1: { 	if (vArrival[h].second == true) { vArrival.erase(vArrival.begin() + h); h--; } } break;
			}
		}
	}

	if (!_doorMake(Tile::Type::EXIT)) { return false; }

	return true;
}

bool MapAlorithm::_doorMake(Tile::Type type)
{
	int w, h, x, y, count;

	int stack = 0;
	if (type == Tile::Type::ENTRANCE)
	{
		door.clear();
		while (true)
		{
			count = 0;
			door.clear();
			h = RND->getFromIntTo(2, _tiles.size() / 3);
			w = RND->getFromIntTo(2, _tiles[h].size() / 3);

			for (int p = 0; p <= 8; p++)
			{
				if (p == 4) { continue; }
				else if (p < 3) { y = -1; }
				else if (p < 6) { y = 0; }
				else if (p <= 8) { y = 1; }
				switch (p)
				{
				case 1: case 7: { x = 0; } break;
				case 2: case 5: case 8: { x = 1; } break;
				case 0: case 3: case 6: { x = -1; } break;
				}

				y = h + y; x = w + x;
				if (p < 6) { if (_tiles[y][x].type == Tile::Type::BACK) { count++; } }
				else if (_tiles[y][x].type == Tile::Type::WALL || _tiles[y][x].type == Tile::Type::IMPOSSIBLE) { count++; }
			}

			if (count == 8)
			{
				this->door.push_back({ h,w });
				_tiles[h][w].type = type;
				return true;
			}
			else { stack++; if (stack >= 50) { return false; } }
		}
	}
	else if (type == Tile::Type::EXIT)
	{
		while (true)
		{
			count = RND->getFromIntTo(vArrival.size() - 10, vArrival.size() - 1);
			h = vArrival[count].first.y;
			w = vArrival[count].first.x;
			count = 0;

			for (int p = 0; p <= 8; p++)
			{
				if (p == 4) { continue; }
				else if (p < 3) { y = -1; }
				else if (p < 6) { y = 0; }
				else if (p <= 8) { y = 1; }
				switch (p)
				{
				case 1: case 7: { x = 0; } break;
				case 2: case 5: case 8: { x = 1; } break;
				case 0: case 3: case 6: { x = -1; } break;
				}

				y = h + y; x = w + x;
				if (p < 6) { if (_tiles[y][x].type == Tile::Type::BACK) { count++; } }
				else if (_tiles[y][x].type == Tile::Type::WALL || _tiles[y][x].type == Tile::Type::IMPOSSIBLE) { count++; }
			}

			if (count == 8)
			{
				this->door.push_back({ h,w });
				_tiles[h][w].type = type;
				return true;
			}
			else { stack++; if (stack >= 50) { return false; } }
		}
	}
	else return false;
}

vector<POINT> MapAlorithm::getDoor() { return door; }
