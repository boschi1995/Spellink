#pragma once
#include "SingletonBase.h"
#include "SnakeMonster.h"
#include "BatMonster.h"
#include "Thorn.h"
#include "Projectile.h"

class Factory : public SingletonBase <Factory>
{
	public:
		enum Tag
		{
			SNAKE, BAT,
			THORN, PROJECTILE
		};

		void produce(Tag, RECT,int=0);
};

