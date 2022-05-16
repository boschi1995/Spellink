#include "Stdafx.h"

void MapManager::init()
{
	MapAlorithm alorithm = MapAlorithm();
	_tiles = alorithm.getTileMap();
	_door = alorithm.getDoor();
	_spon = alorithm.getArrival();
	
	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int h = 0; h < _tiles[i].size(); h++)
		{
			MAP->TileImage(&_tiles[i][h]);
		}
	}

	/*
	RECT rect;
	for (int i = 0; i < MAP->_spon.size(); i++)
	{
		if (RND->getInt(100) <= 3)
		{
			switch (_spon[i].second)
			{
				case 2: 
				{
					if(RND->getInt(2) == 0)
					{ 
						FACTORY->produce(Factory::SNAKE, _tiles[_spon[i].first.y][_spon[i].first.x].object);
					}
					else
					{
						FACTORY->produce(Factory::THORN, _tiles[_spon[i].first.y][_spon[i].first.x].object);
					}
				}break;

				case 3:
				{
					FACTORY->produce(Factory::BAT, _tiles[_spon[i].first.y][_spon[i].first.x].object);
				}break;

				case 4:
				{
					// ½î´Â Æ®·¦
					FACTORY->produce(Factory::PROJECTILE, _tiles[_spon[i].first.y][_spon[i].first.x].object,-1);
				}break;
			}

		}
	}
	*/
}

void MapManager::relese()
{ _tiles.clear(); _door.clear(); _angleTiles.clear(); }

void MapManager::update()
{
	_angleTiles.clear();
	for (int i = 0; i < _tiles.size(); i++)
	{
		for (int h = 0; h < _tiles[i].size(); h++)
		{
			if (CAMAERA->inTheAngle(_tiles[i][h].object))
			{
				if (_tiles[i][h].type == Tile::Type::WALL || _tiles[i][h].type == Tile::Type::IMPOSSIBLE)
				{
					_angleTiles.push_back({ i,h });
				}
			}
		}
	}

	for (int i = 0; i < _item.size(); i++)
	{
		if (_item[i]->_isdelete) 
		{ 
			_item.erase(_item.begin() + i); 
			break;
		}
		_item[i]->update();

		if (CAMAERA->inTheAngle(_item[i]->object))
		{
			_item[i]->rander();
		}
	}
}

void MapManager::clearItem()
{
	_item.clear();
}

void MapManager::TileImage(Tile* tile)
{
	switch (tile->type)
	{
		case Tile::Type::WALL: case Tile::Type::IMPOSSIBLE:
		{
			POINT point = RectToPoint(tile->object);
			point.x = (point.x / 64) - 1;
			point.y = (point.y / 64) - 1;

			if (point.y - 1 >= 0)
			{
				if (MAP->_tiles[point.y-1][point.x].type == Tile::Type::BACK)
				{
					tile->image.init("Resources/block/wall_Up.bmp", 128, 64,2,1);
					MAP->_tiles[point.y][point.x].gold = -1;
					tile->image.setX(tile->object.left);
					tile->image.setY(tile->object.top);
					break;
				}
			}

			if (point.y + 1 < MAP->_tiles.size())
			{
				if (MAP->_tiles[point.y+1][point.x].type == Tile::Type::BACK)
				{
					tile->image.init("Resources/block/wall_Down.bmp", 128, 64, 2, 1);
					MAP->_tiles[point.y][point.x].gold = -1;
					tile->image.setX(tile->object.left);
					tile->image.setY(tile->object.top);
					break;
				}
			}

			tile->image.init("Resources/block/wall_Mid.bmp", 128, 64, 2, 1);
			if (MAP->_tiles[point.y][point.x].type == Tile::Type::WALL &&  MAP->_tiles[point.y][point.x].gold != -1) { tile->image.setFrameX(1); }
			tile->image.setX(tile->object.left);
			tile->image.setY(tile->object.top);
		}break;

		case Tile::Type::ENTRANCE:
		{
			tile->image.init("Resources/block/entrance.bmp", 64, 64);
			tile->image.setX(tile->object.left);
			tile->image.setY(tile->object.top);
		}break;

		case Tile::Type::EXIT:
		{
			tile->image.init("Resources/block/exit.bmp", 64, 64);
			tile->image.setX(tile->object.left);
			tile->image.setY(tile->object.top);
		}break;
	}
}

void MapManager::render()
{
	CAMAERA->setRender(true, 0, nullptr, IMAGEMANAGER->findImage("backGround"));
	
	for (int i = 0; i < _door.size(); i++)
	{
		CAMAERA->setRender(true, 1, nullptr, &_tiles[_door[i].x][_door[i].y].image);
	}

	for (int i = 0; i < _angleTiles.size(); i++)
	{
		CAMAERA->setRender(true, 1, nullptr, &_tiles[_angleTiles[i].x][_angleTiles[i].y].image);
	}
}

