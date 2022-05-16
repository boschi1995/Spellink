#include "Stdafx.h"
#include "BatMonster.h"

BatMonster::BatMonster(RECT rect)
{
	image = new Image();
	image->init("Resources/Monster/bat.bmp", 192, 192, 3, 3, true, RGB(255, 0, 255));
	tag = Character::MONSTER;
	fps = 0;
	hp = 1;
	move = { 0,0 };
	isdown = 0;
	_isDetect = false;
	_detect = rect;
	_detect.left -= 64;
	_detect.right += 64;
	_detect.bottom += 64*2;
	this->rect = { rect.left + 10 , rect.top + gameSpeed, rect.right - 10, rect.bottom-10 };

	OBSERVER->grvity.setObserver(this);
}

void BatMonster::update()
{
	if (hp <= 0)
	{
		Gravity::Observer* gravity = this; gravity->_isdelete = true;
		Character::Observer* charater = this; charater->_isdelete = true;
		return;
	}
	if (_isDetect) { patternMove(); } else { image->setFrameY(0); }
	_funcCollision();
	rect.top += isdown; rect.bottom += isdown;
	rect.left += move.first; rect.right += move.first;

}

void BatMonster::_funcCollision()
{
	/*
	if (_collider[3].first)
	{
		int error = (rect.bottom - _collider[3].second.top) + (gameSpeed - 0.1f);
		if (error != 0) { isJump.first = false; }
		rect.bottom -= error; rect.top -= error;
	}

	if ((_collider[0].first && move.first == -1) || (_collider[2].first && move.first == 1))
	{
		move.first = 0;
	}

	if (_collider[1].first) 
	{ 
		int error = (rect.bottom - _collider[1].second.top) + (gameSpeed - 0.1f);
		if (error != 0) { isJump.first = false; }
		rect.bottom += error; rect.top += error;
	}

	if(_isDetect && move.second == -1) { image->setFrameY(2); }
	else if (_isDetect && move.second == 1) { image->setFrameY(3); }
	if (_isDetect) { fps++; }
	if (_isDetect && fps == 10) 
	{ 
		fps = 0;
		if (image->getFrameX() == image->getMaxFrameX()) { image->setFrameX(0); }
		else { image->setFrameX(image->getFrameX()+1); }
	}

	if (_isDetect) { return; }
	for (int h = 0; h < OBSERVER->character.getObserver().size(); h++)
	{
		if (OBSERVER->character.getObserver(h)->tag != Character::PLAYER) { return; }
		RECT temp;
		if (IntersectRect(&temp, &OBSERVER->character.getObserver(h)->rect, &_detect)) 
		{
			_isDetect = true; 
			fps = 0;
		}
	}
	*/
}

void BatMonster::patternMove()
{
	int x, y;
	bool stop = false;
	POINT point = RectToPoint(rect);
	point.x /= 64; point.y /= 64;
	point.y -= 1;
	//CAMAERA->setRender(true, 2, &MAP->_tiles[point.y][point.x].object, RGB(0, 0, 255), true, RGB(0, 0, 255));

	POINT end;
	for (int h = 0; h < OBSERVER->character.getObserver().size(); h++)
	{
		if (OBSERVER->character.getObserver(h)->tag != Character::PLAYER) { return; }
		end = RectToPoint(OBSERVER->character.getObserver(h)->rect);
		end.x /= 64; end.y /= 64;
		break;
	}

	if (point.x == end.x && point.y == end.y) { return; }

	roet.resize(0);
	roet.push_back(datas(point,0,true));
	for (int i = 0; i < roet.size(); i++)
	{
		for (int h = 0; h < 9; h++)
		{
			switch (h)
			{
				case 0: { x = 0; y = -1; } break;
				case 1: { x = -1; y = -1; } break;
				case 2: { x = 1; y = -1; } break;
				case 3: { x = 0; y = 0; } break;
				case 4: { x = -1; y = 0; } break;
				case 5: { x = 1; y = 0; } break;
				case 6: { x = 0; y = 1; } break;
				case 7: { x = -1; y = 1; } break;
				case 8: { x = 1; y = 1; } break;
			}

			x = roet[i].point.x + x;
			y = roet[i].point.y + y;
			if (y >= MAP->_tiles.size() || x >= MAP->_tiles[y].size()) { continue; }

			bool check = false;
			for (int g = 0; g < roet.size(); g++)
			{
				if (roet[g].point.x == x && roet[g].point.y == y)
				{
					check = true; break;
				}
			}

			if (check)
			{
				continue;
			}

			roet.push_back(datas({ x,y }, i+1));
			POINT point = {0,0};
			if (end.x - x < 0) { point.x = x - end.x; } else { point.x = end.x -x; }
			if (end.y - y < 0) { point.y = y - end.y; } else { point.y = end.y -y; }
			roet.back().length = point.x + point.y;

			if (x == end.x && y == end.y)
			{
				stop = true;
			}

			if (MAP->_tiles[y][x].type == Tile::Type::WALL || MAP->_tiles[y][x].type == Tile::Type::IMPOSSIBLE)
			{
				roet.back().isStop = true;
			}
		}
		
		for (int h = 1; h < roet.size(); h++)
		{
			if (roet[h].isStop) { roet.erase(roet.begin() + h); h--; }
		}

		int num = 30000; int live = 0;
		for (int h = 1; h < roet.size(); h++)
		{
			if (roet[h].astar == i + 1)
			{
				if (num >= roet[h].length) { num = roet[h].length; live = h; }
			}
		}

		for (int h = 1; h < roet.size(); h++)
		{
			if (roet[h].astar == i + 1)
			{
				if (h != live)
				{
					roet[h].isStop = true;
				}
			}
		}
		for (int h = 1; h < roet.size(); h++)
		{
			if (roet[h].isStop) { roet.erase(roet.begin() + h); h--; }
		}

		if (stop) { break; }
	}

	point = RectToPoint(MAP->_tiles[roet[1].point.y][roet[1].point.x].object);
	if (point.x-50 < RectToPoint(rect).x)
	{
		move = { -1, -1 };
	}
	else
	{
		move = { 1, 1 };
	}

	if (point.y > RectToPoint(rect).y)
	{
		isdown = 1;
	}
	else
	{
		isdown = -1;
	}
	

	//for (int i = 1; i < roet.size(); i++) { CAMAERA->setRender(true, 2, &MAP->_tiles[roet[i].point.y][roet[i].point.x].object,RGB(0,144,0),false); }
}

void BatMonster::render(void)
{
	if (CAMAERA->inTheAngle(rect))
	{
		image->setX(rect.left-12);
		image->setY(rect.top);
		CAMAERA->setRender(true, 3, nullptr, image);
		//CAMAERA->setRender(true, 3, &rect,image);
	}
}