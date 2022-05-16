#include "Stdafx.h"
#include "Projectile.h"
#include "Item.h"

Projectile::Projectile(RECT rect, int direction)
{
	_isdelete = false;
	tag = Character::TRAP;
	this->rect = rect;
	move = { direction, 5 };
	POINT point = RectToPoint(rect);
	point.x /= 64; point.y /= 64;
	MAP->_tiles[point.y-1][point.x-1].type = Tile::Type::IMPOSSIBLE;
	MAP->TileImage(&MAP->_tiles[point.y - 1][point.x - 1]);
	OBSERVER->item.setObserver(new Arrow(this));
	image = new Image();
	image->init("Resources/block/projectile.bmp", 128, 64, 2, 1);
	if (direction == -1) { image->setFrameX(0); } else { image->setFrameX(1); }
	image->setX(this->rect.left);
	image->setY(this->rect.top);
}

void Projectile::update()
{
	if (items.size() == 0) { return; }

	RECT temp;
	POINT point = RectToPoint(rect);
	point.x /= 64; point.y /= 64;

	pair<int, int> x = { (point.x -2), (point.x - 2) + ( move.first * move.second) };
	point.y -= 1;

	for (int w = x.first; w != x.second; w += move.first)
	{
		if (point.y >= MAP->_tiles.size()) { continue; }
		if (w >= MAP->_tiles[point.y].size()) { continue; }
		if (MAP->_tiles[point.y][w].type == Tile::Type::WALL || MAP->_tiles[point.y][w].type == Tile::Type::IMPOSSIBLE) { break; }
		CAMAERA->setRender(true, 0, &MAP->_tiles[point.y][w].object, RGB(0, 0, 255), true, RGB(0, 0, 255));

  		for (int h = 0; h < OBSERVER->character.getObserver().size(); h ++)
		{
			if (IntersectRect(&temp, &MAP->_tiles[point.y][w].object, &OBSERVER->character.getObserver(h)->rect))
			{
				items[useItem.front()]->Interaction();
				break;
			}
		}

		for (int i = 0; i < MAP->_item.size(); i++)
		{
			if (IntersectRect(&temp, &MAP->_tiles[point.y][w].object, &MAP->_item[i]->object))
			{
				items[useItem.front()]->Interaction();
				break;
			}
		}
	}

}

void Projectile::render(void)
{
	if (image != nullptr)
	{
		CAMAERA->setRender(true, 2, nullptr, image,nullptr);
	}
}
