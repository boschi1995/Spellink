#pragma once
#include "SingletonBase.h"
#include "Player.h"

class GameManager : public SingletonBase<GameManager>
{
	public:
		Player* player;
};

