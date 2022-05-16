#include "Stdafx.h"
#include "Player.h"
#include "Item.h"

Player::Player()
{
	subState.first.resize(0);
	subState.second.resize(0);
	state.second.resize(0);
	image = nullptr;
	Anime = nullptr;
	imagePoint = { 0,0 };
	gold = 0;
	tag = Character::PLAYER;
	_isdelete = false;
	OBSERVER->item.setObserver(new Whip(this));
	OBSERVER->character.setObserver(this);
	OBSERVER->grvity.setObserver(this);
	hp = 3;
	move = { 1,1 };
}

HRESULT Player::init()
{
	tag = Character::PLAYER;
	RECT door = MAP->_tiles[MAP->_door[0].x][MAP->_door[0].y].object;
	rect = { door.left +10 , door.top+10, door.right -10, door.bottom};
	//rect = door;
	rect.top -= 10;	rect.bottom -= 10;
	OBSERVER->item.setObserver(new Lope(this));
	OBSERVER->item.setObserver(new Boom(this));
	return S_OK;
}

void Player::update()
{
	_inputKey();
	_funcCollision();
	_funcJump();
	_funcImage();
	
	move.first *= (gameSpeed -1);
	rect.left += move.first; rect.right += move.first;
	CAMAERA->update(POINT{ rect.left - (WINSIZE_X / 2) , rect.top - (WINSIZE_Y / 2) });
}

void Player::render(void)
{
	items[useItem.front()]->render();
	if (image != nullptr)
	{
		image->setX(rect.left + imagePoint.x);
		image->setY(rect.top + imagePoint.y);
		//CAMAERA->setRender(true, 3, nullptr, image, Anime);
		CAMAERA->setRender(true, 3, &rect, RGB(255, 0, 255), true, RGB(255, 0, 255), image, Anime);
	}
}

void Player::_funcCollision()
{

	// 내려가기 방어 
	if (_collider[7].first)
	{
		int error = (rect.bottom - _collider[7].second);
		if (error != 0) { isJump.first = false; }
		rect.bottom -= error; rect.top -= error;
	}
	else if (!_collider[7].first && _collider[6].first) { if (rect.left > _collider[6].second) { isJump.first = true; } } 
	else if (!_collider[5].first && _collider[8].first) { if (rect.right < _collider[8].second) { isJump.first = true; } }
	else { isJump.first = true; }

	/*
	int func;
	if (move.first == -1)
	{
		if (isJump.first == true) { func = 6; } else { func = 3; }
		if (_collider[func].first && move.first == -1 && rect.left <= _collider[func].second) { move.first = 0; }
	}
	else if (move.first == 1)
	{
		if (isJump.first == true) { func = 8; } else { func = 5; }
		if (_collider[func].first && move.first == 1 && rect.right >= _collider[func].second) { move.first = 0; }
	}
	*/
	

	/*
	if (_collider.size() == 0) { return; }
	if(_collider[3].first)
	{
		int error = (rect.bottom - _collider[3].second.top) + (gameSpeed - 0.1f);
		if (error != 0) { isJump.first = false; }
		rect.bottom -= error; rect.top -= error;
	}
	else { isJump.first = true; }

	if (move.first != 0 && isJump.second <= 1)
	{
		int point, set;
		if (move.first == -1) { point = 4; set = 0; } else { point = 5; set = 2; }

		if (!_collider[point].first && _collider[set].first)
		{
			if ((_collider[set].second.top <= rect.top - 3) || (_collider[set].second.top <= rect.top + 3))
			{
				state.first = "climbing";
				isJump.first = false;
			}
		}
	}
	
	if ((_collider[0].first && move.first == -1) || (_collider[2].first && move.first == 1)) { move.first = 0; }
	if (_collider[1].first) { isJump.second = -1; }

	if (state.first == "attack") { return; }
	if (isJump.first == true) { state.first = "jump"; }
	*/
}

void Player::_inputKey()
{
	if (state.first == "die") { return; }
	move.first = 0; 	_isDown = 0;
	if (!(state.first == "attack" && items[Item::WHIP]->button))
	{ 
		state.first.resize(0); 
	} 
	else
	{ 
		return; 
	}

	if (KEYMANAGER->isStayKeyDown(VK_RIGHT)) { move = { 1, 1 }; state.first = "runRight"; }
	else if (KEYMANAGER->isStayKeyDown(VK_LEFT)) { move = { -1, -1 }; state.first = "runLeft"; }

	if (KEYMANAGER->isStayKeyDown(VK_DOWN)) { _isDown = 1; move.first = 0; state.first = "down"; }
	if (KEYMANAGER->isOnceKeyDown('Z') && !isJump.first) { isJump.first = true; isJump.second = 3.45f; }

	if (KEYMANAGER->isOnceKeyDown('C'))
	{
		if (items[useItem.front()]->swap())
		{
			useItem.push(useItem.front());
			useItem.pop();
		}
	}

	if (KEYMANAGER->isOnceKeyDown('X'))
	{
		if (_isDown == 1) { _isDown = 2; }
		else
		{
			items[useItem.front()]->Interaction();
		}
	}
}

void Player::_funcImage()
{
	if (hp <= 0) { state.first = "die"; }

	//cout << state.first << endl;
	if (state.first.size() == 0 && isJump.first == false)
	{
		image = IMAGEMANAGER->findImage("playerIdle");
		if (move.second == -1) { image->setFrameX(0);  imagePoint = { -15, 0 }; }
		else { image->setFrameX(1); imagePoint = { -16, 0 }; }
		state.second.resize(0);
		Anime = nullptr;
		return;
	}

	if (state.first == "die")
	{
		image = IMAGEMANAGER->findImage("playerStun");
		if (state.first.compare(state.second) == 1)
		{
			state.second = state.first;
			Anime = new Animation();
			Anime->init(image->getWidth(), image->getHeight(), image->getFrameWidth(), image->getFrameHeight());
			if (move.second == -1) { Anime->setPlayFrame(0, 4, false, true); } else { Anime->setPlayFrame(5, 9, false, true); }
			Anime->setFPS(5);
			Anime->AniStart();
		}
	}


	if (state.first == "attack")
	{
		image = IMAGEMANAGER->findImage("playerAttack");
		if (move.second == -1) { imagePoint = { -5, 0 }; }
		else { imagePoint = { -7, 0 }; }
		if (state.first.compare(state.second) == 1)
		{
			state.second = state.first;
			Anime = new Animation();
			Anime->init(image->getWidth(), image->getHeight(), image->getFrameWidth(), image->getFrameHeight());
			if (move.second == -1) { Anime->setPlayFrame(0, 10, false, false); }
			else { Anime->setPlayFrame(11, 21, false, false); }
			Anime->setFPS(10);
			Anime->AniStart();
		}
	}

	if (state.first == "jump")
	{
		if (subState.first.size() == 0)
		{
			image = IMAGEMANAGER->findImage("playerIdle");
			if (move.second == -1) { image->setFrameX(2);  imagePoint = { -15, 0 }; }
			else { image->setFrameX(3); imagePoint = { -16, 0 }; }
			state.second.resize(0);
			Anime = nullptr;
			return;
		}
		else
		{
			for (int i = 0; i < useItem.size(); i++)
			{
				if (useItem.front() == Item::WHIP) { break; }
				useItem.push(useItem.front());
				useItem.pop();
			}

			image = IMAGEMANAGER->findImage("playerRope");
			if (subState.first == "idle")
			{
				image->setFrameX(11);
				imagePoint = { -10,-30 };
				state.second.resize(0);
				Anime = nullptr;
				return;
			}
			else if (state.first.compare(state.second) == 1)
			{
				if (subState.first == "move" && Anime == nullptr)
				{
					imagePoint = { -10,-30 };
					Anime = new Animation();
					Anime->init(image->getWidth(), image->getHeight(), image->getFrameWidth(), image->getFrameHeight());
					Anime->setDefPlayFrame(false, true);
					Anime->setFPS(12,2);
					Anime->AniStart();
				}
			}
		}
	}

	if (state.first == "climbing")
	{
		image = IMAGEMANAGER->findImage("playerIdle");
		if (move.second == -1) { image->setFrameX(4);  imagePoint = { -15, 0 }; }
		else { image->setFrameX(5); imagePoint = { -16, 0 }; }
		state.second.resize(0);
		Anime = nullptr;
		return;
	}

	if (state.first == "down")
	{
		image = IMAGEMANAGER->findImage("playerIdle");
		if (move.second == -1) { image->setFrameX(6);  imagePoint = { -15, 0 }; }
		else { image->setFrameX(7); imagePoint = { -16, 0 }; }
		state.second.resize(0);
		Anime = nullptr;
		return;
	}

	if (state.first == "runLeft" || state.first == "runRight")
	{
		image = IMAGEMANAGER->findImage("playerRun");
		if (move.second == -1) { imagePoint = { -5, 0 }; } else { imagePoint = { -7, 0 }; }
		if (state.first.compare(state.second) == 1)
		{
			state.second = state.first;
			Anime = new Animation();
			Anime->init(image->getWidth(), image->getHeight(), image->getFrameWidth(), image->getFrameHeight());
			if (state.first == "runLeft") { Anime->setPlayFrame(0, 5, false, true); } else { Anime->setPlayFrame(6, 11, false, true); }
			Anime->setFPS(6,2);
			Anime->AniStart();
		}
	}

	if (state.first == "attack")
	{
		image = IMAGEMANAGER->findImage("playerAttack");
		if (move.second == -1) { imagePoint = { -5, 0 }; }
		else { imagePoint = { -7, 0 }; }
		if (state.first.compare(state.second) == 1)
		{
			state.second = state.first;
			Anime = new Animation();
			Anime->init(image->getWidth(), image->getHeight(), image->getFrameWidth(), image->getFrameHeight());
			if (move.second == -1) { Anime->setPlayFrame(0, 10, false, false); }
			else { Anime->setPlayFrame(11, 21, false, false); }
			Anime->setFPS(10);
			Anime->AniStart();
		}
	}

	if (Anime != nullptr) { Anime->frameUpdate(TIMEMANAGER->getElapsedTime() * 1); }
}
