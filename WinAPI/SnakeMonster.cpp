#include "Stdafx.h"
#include "SnakeMonster.h"

SnakeMonster::SnakeMonster(RECT rect)
{
	image = new Image();
	image->init("Resources/Monster/snake.bmp", 256, 128, 4, 2, true, RGB(255, 0, 255)); 
	Anime = nullptr;
	tag = Character::MONSTER;
	fps = 0;
	hp = 1;
	move = { 1,1 };
	pattern = END;
	this->rect = { rect.left + 10 , rect.top + gameSpeed, rect.right - 10, rect.bottom };
	this->rect.top -= 10;	this->rect.bottom -= 10;
}

void SnakeMonster::update()
{
	if (hp <= 0) 
	{ 
		Gravity::Observer* gravity = this; gravity->_isdelete = true;
		Character::Observer* charater = this; charater->_isdelete = true;
		return; 
	}

	if (pattern == END) { inputPattern(); }
	patternFunc();
	_funcCollision();
	_funcJump();
}

void SnakeMonster::inputPattern()
{
	pattern = (Pattern)RND->getInt(END);
	limit = TIMEMANAGER->getWorldTime();
	switch (pattern)
	{
		case IDLE:
		{
			Anime = nullptr;
			if (move.first == -1) { image->setFrameX(0); } else { image->setFrameX(1); }
			patternFunc = bind(&SnakeMonster::patternIdle, this);
			limit += RND->getFromFloatTo(2, 3);
		}break;
			
		case MOVE:
		{
			patternFunc = bind(&SnakeMonster::patternMove, this);
			limit += RND->getFromFloatTo(4,5);
			Anime = new Animation();
			Anime->init(image->getWidth(), image->getHeight(), image->getFrameWidth(), image->getFrameHeight());
			Anime->setFPS(4);
			Anime->AniStart();

			if (RND->getInt(2)) 
			{ 
				move = { -1,-1 }; 
				imagePoint = { 0,0 };
				Anime->setPlayFrame(0, 3, false, true);
			} 
			else 
			{ 
				move = { 1,1 }; 
				imagePoint = { 0,0 };
				Anime->setPlayFrame(4, 7, false, true);
			}
		}break;
	}
}

void SnakeMonster::patternIdle()
{
	if (TIMEMANAGER->getWorldTime() < limit) { return; }
	pattern = END;
}

void SnakeMonster::patternMove()
{
	if (Anime != nullptr) { Anime->frameUpdate(TIMEMANAGER->getElapsedTime() * 1); }
	if (fps != 6) { fps++; return; } else { fps = 0; }
	rect.left += move.first;
	rect.right += move.first;
	if (TIMEMANAGER->getWorldTime() < limit) { return; }
	pattern = END;
}

void SnakeMonster::_funcCollision()
{
	/*
	if (_collider.size() == 0) { return; }
	if (_collider[3].first)
	{
		int error = (rect.bottom - _collider[3].second.top) + (gameSpeed - 0.1f);
		if (error != 0) { isJump.first = false; }
		rect.bottom -= error; rect.top -= error;
	}
	else { isJump.first = true; }

	if ((_collider[0].first && move.first == -1) || (_collider[2].first && move.first == 1))
	{
		move.first = 0;
	}

	if (((!_collider[6].first) && move.first == -1) || ((!_collider[7].first) && move.first == 1))
	{
		if (move.first == 1)
		{
			move.first = -1;
			Anime = new Animation();
			Anime->init(image->getWidth(), image->getHeight(), image->getFrameWidth(), image->getFrameHeight());
			Anime->setPlayFrame(0, 3, false, true);
			Anime->setFPS(4);
			Anime->AniStart();
		}
		else
		{
			move.first = 1;
			Anime = new Animation();
			Anime->init(image->getWidth(), image->getHeight(), image->getFrameWidth(), image->getFrameHeight());
			Anime->setPlayFrame(4, 7, false, true);
			Anime->setFPS(4);
			Anime->AniStart();
		}
	}

	if (_collider[1].first) { isJump.second = -1; }
	*/
}

void SnakeMonster::render(void)
{
	if (CAMAERA->inTheAngle(rect))
	{
		image->setX(rect.left);
		image->setY(rect.top);
		CAMAERA->setRender(true, 4, NULL, image, Anime);
		//CAMAERA->setRender(true, 4, &rect, image,Anime);
	}
}
