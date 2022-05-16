#include "Stdafx.h"
#include "Item.h"



#pragma region  Whip

Whip::Whip(Character::Observer* character)
{
	image = new Image();
	image->init("Resources/Item/whip.bmp", 312, 128, 2, 2, true, RGB(255, 0, 255));
	tag = Item::WHIP;
	user = character;
	button = false;
	count = 1;
	rect = { 0,0,0,0 };
}

void Whip::update()
{
	user->state.first = "attack";
	if (user->move.second == -1)
	{ rect = RECT{ user->rect.left - 64, user->rect.top + 5, user->rect.left, user->rect.bottom - 5 }; }
	else 
	{ rect = RECT{ user->rect.right, user->rect.top + 5, user->rect.right + 64, user->rect.bottom - 5 }; }

	if (user->Anime->getNowPlayIdx() >= 5)
	{
		image->setFrameX(1);
		RECT temp;
		for (int i = 1; i < OBSERVER->character.getObserver().size(); i++)
		{
			if (IntersectRect(&temp, &OBSERVER->character.getObserver()[i]->rect, &rect))
			{
				OBSERVER->character.getObserver()[i]->hp -= 1;
			}
		}
	}

	if (user->Anime->isPlay() == false) 
	{ 
		button = false;
		Anime = nullptr;
	}
}

void Whip::render()
{
	if (!button) { return; }
	image->setX(rect.left + imagePoint.x);
	image->setY(rect.top + imagePoint.y);
	CAMAERA->setRender(true, 2, nullptr, image);
	//CAMAERA->setRender(true, 2, &rect, RGB(255, 0, 255), true, RGB(255, 0, 255), image);
}

void Whip::Interaction()
{
	if (button) { return; } else { button = true; }
	user->state.first = "attack";
	image->setFrameX(0);
	if (user->move.second == -1)
	{
		imagePoint = {5,0};
		image->setFrameY(0);
	}
	else
	{
		imagePoint = { -90,0 };
		image->setFrameY(1);
	}
}

#pragma endregion



#pragma region  Lope

Lope::Lope(Character::Observer* character)
{
	image = nullptr;
	this->user = character;
	_isdelete = button = _distance = 0;
	tag = Item::Tag::LOPE;
	count = 3;
}

void Lope::update()
{
	if (_distance < 448)
	{
		RECT temp;
		_distance += gameSpeed;
		rect.top -= gameSpeed;
		rect.bottom -= gameSpeed;
		image->setX(this->rect.left - 10);
		image->setY(this->rect.top);

		if (collider != nullptr)
		{
			if (collider->bottom == rect.top) { _distance = 448; }
			return; 
		}
		
		POINT point = RectToPoint(rect);
		point.x /= 64; point.y = (point.y / 64) -1;
		if (MAP->_tiles[point.y][point.x].type == Tile::Type::IMPOSSIBLE || MAP->_tiles[point.y][point.x].type == Tile::Type::WALL)
		{ 
			collider = &MAP->_tiles[point.y][point.x].object; 
		}
		
	}
	else
	{
		if (rect.bottom >= tail)
		{
			MAP->_item.push_back(new LopeTile(rect, false, rect.bottom - rect.top));
			button = _distance = 0;
			rect = { 0,0,0,0 };
			count--;
			image = nullptr;
		}
		else
		{
			rect.bottom += gameSpeed;
			image->setClippingH(rect.bottom - rect.top);
		}
	}
}

void Lope::render()
{ 
	if (!button)
	{
		if (image == nullptr)
		{
			image = new Image();
			image->init("Resources/Item/rope.bmp", 50, 50, true, RGB(255, 0, 255));
		}

		rect = user->rect;
		image->setX(rect.left-5);
		image->setY(rect.top+23);
	}

	if (CAMAERA->inTheAngle(rect)) 
	{ 
		CAMAERA->setRender(true, 4, nullptr, image);
	}
}

void Lope::Interaction()
{
	if (!user->_collider[3].first) { return; }
	if (user->_collider[1].first) { return; }
	if (button) { return; } else { button = true; }
	if (count == 0) { button = false; return; }
	//RECT rect = user->_collider[3].second;
	this->rect = RectMakeCenter(rect.left + ((rect.right - rect.left) / 2), user->rect.top, 10, 10);
	tail = rect.top;
	_distance = 0;
	collider = nullptr;

	image = new Image();
	image->init("Resources/Item/lopeTile.bmp", 32, 524, true, RGB(255, 0, 255));
	image->setClippingH(32);
	image->setClippingW(32);
	image->isClipping(true);
}

bool Lope::swap()
{ if (_distance == 0) { return true; } else { return false; } }

LopeTile::LopeTile(RECT rect, bool capsule, int distance)
{
	object = rect;
	_capsule = capsule;
	_isdelete = attach = false;
	tag = Item::Tag::LOPE;

	if (_capsule == false)
	{
		image = new Image();
		image->init("Resources/Item/lopeTile.bmp", 32, 524, true, RGB(255, 0, 255));
		image->setX(object.left - 10);
		image->setY(object.top);
		image->setClippingW(32);
		image->setClippingH(distance);
		image->isClipping(true);
	}
}


void LopeTile::update(Character::Observer* character)
{
	if (_capsule && character->_isDown == 2)
	{ 
		OBSERVER->item.setObserver(new Lope(character));
		_isdelete = true;
		return;
	}

	if (character->tag != Character::PLAYER) { return; }

	if (attach == true) 
	{ 
		character->state.first = "rope";
		character->isJump = { false,0 };
		character->subState.first = "idle";
		character->move.first = 0; 
	}

	if (KEYMANAGER->isStayKeyDown(VK_UP))
	{
		if (attach == false)
		{
			attach = true;
			int mid = object.left+((object.right - object.left)*0.5f);
			if (mid == 0) { return; }
			character->rect.left = mid - 22;
			character->rect.right = mid + 22;
		}
		else
		{
			character->subState.first = "move";
			if (character->rect.top > object.top)
			{
				character->rect.top -= gameSpeed * 0.5f;
				character->rect.bottom -= gameSpeed * 0.5f;
			}
		}
	}
	else if (KEYMANAGER->isStayKeyDown(VK_DOWN))
	{
		if (attach == true)
		{
			character->subState.first = "move";
			character->rect.top += gameSpeed * 0.5f;
			character->rect.bottom += gameSpeed * 0.5f;
		}
	}

	if (attach == true)
	{
		if (KEYMANAGER->isStayKeyDown(VK_LEFT) || KEYMANAGER->isStayKeyDown(VK_RIGHT))
		{
			character->subState.first.resize(0);
			character->subState.second.resize(0);
			attach = false;
			character->isJump.first = true;
		}
	}

}
void LopeTile::update()
{
	if (!_capsule) { return; }
}

void LopeTile::rander()
{
	CAMAERA->setRender(true, 2, &object,image);
}

#pragma endregion



#pragma region Boom

Boom::Boom()
{
	image = new Image();
	image->init("Resources/Item/boom.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	button = shoot = _isdelete = false;
	tag =  Item::BOOM;
	rect = { 0,0,0,0 };
	count = 3;
}

Boom::Boom(Character::Observer* character)
{
	image = new Image();
	image->init("Resources/Item/boom.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
	user = character;
	button = shoot = _isdelete = false;
	tag = Item::BOOM;
	rect = { 0,0,0,0 };
	count = 3;
}

void Boom::update()
{
	fps.first++;
	if (fps.first >= fps.second) 
	{
		if (image->getFrameX() == 0)
		{
			image->setFrameX(1);
		}
		else
		{
			image->setFrameX(0);
		}
		fps.first = 0;
	}

	if (shoot)
	{
		MAP->_item.push_back(new BoomTile(rect,user->move.second, _keeping,fps));
		shoot = button = false;
		queue<float>().swap(_keeping);
		if (count == 0) { _isdelete = true; }
		image->setFrameX(0);
		return;
	}
	if (_keeping.size() != 0)
	{
		if (TIMEMANAGER->getWorldTime() < _keeping.front()) { return; }
		fps.second -= 10;
		_keeping.pop();
	}
	else
	{
		MAP->_item.push_back(new BoomTile(rect,0));
		queue<float>().swap(_keeping);
		shoot = button = false;
		if (count == 0) { _isdelete = true; }
		image->setFrameX(0);
	}
}

void Boom::render()
{
	if (user != nullptr )
	{
		rect = RectMakeCenter(user->rect.left + 20, user->rect.top + ((user->rect.bottom - user->rect.top) / 2), 32, 32);
		image->setX(rect.left);
		image->setY(rect.top+15);
	}

	if (CAMAERA->inTheAngle(rect))
	{
		CAMAERA->setRender(true, 4,nullptr,image);
	}
}

void Boom::Interaction()
{
	if (button == true)
	{
		if (shoot == false) { shoot = true; }
		return; 
	}
	else 
	{ 
		count--;
		button = true;
		shoot = false;
		fps = { 0,30 };
		for (int i = 0; i < 3; i++) { _keeping.push(TIMEMANAGER->getWorldTime() + (i + 3)); }
	} 
}

bool Boom::swap()
{
	if (shoot == false)
	{
		button = shoot = false;
		return true;
	}
	else return false;
}


BoomTile::BoomTile(RECT rect)
{
	this->rect = rect;
	tag = Item::BOOM;
	OBSERVER->grvity.setObserver(this);
	Gravity::Observer* gravity = this; gravity->_isdelete = false;
	ItemTile* tile = this; tile->_isdelete = false;
	_capsule = true;
	speed = 0;
	move = 0;
	image = new Image();
	image->init("Resources/Item/boom.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
}

BoomTile::BoomTile(RECT rect, int move)
{ 
	this->rect = rect;
	this->move = move;
	tag = Item::BOOM;
	OBSERVER->grvity.setObserver(this);
	Gravity::Observer* gravity = this; gravity->_isdelete = false;
	ItemTile* tile = this; tile->_isdelete = false;
	_capsule = false;
	speed = gameSpeed;
	image = new Image();
	image->init("Resources/Item/boom.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
}

BoomTile::BoomTile(RECT rect, int move, queue<float> time,pair<int,int> fps)
{
	this-> fps = fps;
	this->rect = rect;
	this->move = move;
	_keeping = time;
	tag = Item::BOOM;
	OBSERVER->grvity.setObserver(this);
	Gravity::Observer* gravity = this; gravity->_isdelete = false;
	ItemTile* tile = this; tile->_isdelete = false;
	_capsule = false;
	speed = gameSpeed + 2;
	image = new Image();
	image->init("Resources/Item/boom.bmp", 64, 32, 2, 1, true, RGB(255, 0, 255));
}

void BoomTile::update()
{
	if (_collider.size() == 0) { return; }
	
	if (!_collider[3].first)
	{
		isJump.first = true;
	}
	else
	{
		//int error = (rect.bottom - _collider[3].second.top) + (gameSpeed - 0.1f);
		//if (error != 0) { isJump.first = false; }
		//rect.bottom -= error; rect.top -= error;
	}

	if ((_collider[0].first && move == -1) || (_collider[2].first && move == 1))
	{
		if (speed > 1)
		{
			if (move == -1) { move = 1; } else { move = -1; }
		}
		else
		{
			move = 0;
		}
	}
	if (_collider[1].first) { isJump.second = -1; }
	if (speed > 0) { speed -= 0.1f; } else { speed = 0; } 
	rect.left += move * (speed);  rect.right += move * (speed);

	_funcJump();
	object = rect;
	if (_capsule) { return; }

	fps.first++;
	if (fps.first >= fps.second)
	{
		if (image->getFrameX() == 0)
		{
			image->setFrameX(1);
		}
		else
		{
			image->setFrameX(0);
		}
		fps.first = 0;
	}

	if (_keeping.size() != 0)
	{
		if (TIMEMANAGER->getWorldTime() < _keeping.front()) { return; }
		fps.second -= 10;
		_keeping.pop();
	}
	else
	{
		blasting = { rect.left - 32, rect.top - 32, rect.right + 32, rect.bottom + 32 };

		RECT temp;
		POINT point = RectToPoint(object);
		point.x /= 64; point.y /= 64;

		pair<int, int> x = { point.x - 1, point.x + 1 };
		pair<int, int> y = { point.y - 1, point.y + 1 };

		for (int i = 0; i < MAP->_item.size(); i++)
		{
			if (IntersectRect(&temp, &MAP->_item[i]->object, &blasting))
			{
				MAP->_item[i]->_isdelete = true;
			}
		}

		for (int h = y.first; h <= y.second; h++)
		{
			if (h >= MAP->_tiles.size()) { continue; }
			for (int w = x.first; w <= x.second; w++)
			{
				if (w >= MAP->_tiles[h].size()) { continue; }
				if (MAP->_tiles[h][w].type != Tile::Type::IMPOSSIBLE)
				{
					MAP->_tiles[h][w].type = Tile::Type::BACK;
					if(MAP->_tiles[h][w].gold != -1)
					{ 
						MAP->_item.push_back(new GoldTile(MAP->_tiles[h][w].object, MAP->_tiles[h][w].gold));
					}
				}
			}
		}

		for (int i = 0; i < OBSERVER->character.getObserver().size(); i++)
		{
			if (IntersectRect(&temp, &OBSERVER->character.getObserver()[i]->rect, &blasting))
			{
				OBSERVER->character.getObserver(i)->hp = 0;
			}
		}

		OBSERVER->effect.setObserver(new Effect::Observer());
		OBSERVER->effect.getBack()->image = new Image();
		OBSERVER->effect.getBack()->image = IMAGEMANAGER->findImage("EffectBoom");
		OBSERVER->effect.getBack()->image->setX(object.left - 75); // 위치 조정
		OBSERVER->effect.getBack()->image->setY(object.top - 100); // 위치 조정 
		OBSERVER->effect.getBack()->anime = new Animation();
		OBSERVER->effect.getBack()->anime->init
		( OBSERVER->effect.getBack()->image->getWidth(), OBSERVER->effect.getBack()->image->getHeight(),
		  OBSERVER->effect.getBack()->image->getFrameWidth(), OBSERVER->effect.getBack()->image->getFrameHeight());
		OBSERVER->effect.getBack()->anime->setDefPlayFrame(false, false);
		OBSERVER->effect.getBack()->anime->setFPS(9);
		OBSERVER->effect.getBack()->anime->AniStart();

		Gravity::Observer* gravity =this; gravity->_isdelete = true;
		ItemTile* tile =this; tile->_isdelete = true;
	}
}

void BoomTile::rander()
{
	image->setX(object.left);
	image->setY(object.top);
	CAMAERA->setRender(true, 4, nullptr, image);
	//CAMAERA->setRender(true, 4, &object,image);
}

#pragma endregion



#pragma region  Arrow

Arrow::Arrow(Character::Observer* character)
{
	image = new Image();
	image->init("Resources/Item/arrow.bmp", 128/2, 64/2, 2, 1, true, RGB(255, 0, 255));
	user = character;
	button = _isdelete = false;
	tag = Item::ARROW;
	rect = character->rect;
}

void Arrow::update()
{
	MAP->_item.push_back(new ArrowTile(rect,direction));
	_isdelete = true;
}

void Arrow::render()
{
	if (user->tag != Character::TRAP)
	{
		if (CAMAERA->inTheAngle(rect))
		{
			if (user->move.second == -1) { image->setFrameX(0); }else { image->setFrameX(1); }
			rect = { user->rect.left, user->rect.top, user->rect.left+32, user->rect.top+16 };
			image->setX(rect.left);
			image->setY(rect.top);
			CAMAERA->setRender(true, 4, nullptr, image);
			//CAMAERA->setRender(true, 4, &rect, image);
		}
	}
}

void Arrow::Interaction()
{
	if (button == true) { return; }
	else
	{
		button = true;
		if (user->tag == Character::TRAP)
		{
			direction = user->move.first;
		}
		else
		{
			direction = user->move.second;
		}
	}
}

ArrowTile::ArrowTile(RECT rect, int direction)
{
	image = new Image();
	image->init("Resources/Item/arrow.bmp", 128/2, 64/2, 2, 1, true, RGB(255, 0, 255));
	this->move = direction;
	object = this->rect = { rect.left, rect.top, rect.left+32, rect.top+16 }; 
	tag = Item::ARROW;
	speed = gameSpeed + 3;
	Gravity::Observer* gravity = this;
	ItemTile* tile = this;
	tile->_isdelete = gravity->_isdelete = _capsule = false;
	isJump.second = -1;
	OBSERVER->grvity.setObserver(this);
}

void ArrowTile::update()
{
	if (_collider.size() == 0) { return; }
	if (move == -1) { image->setFrameX(0); } else if ( move == 1) { image->setFrameX(1); }

	if (!_collider[3].first)
	{
		isJump.first = true;
	}
	else
	{
		///int error = (rect.bottom - _collider[3].second.top) + (gameSpeed - 0.1f);
		///if (error != 0) { isJump.first = false; }
		///rect.bottom -= error; rect.top -= error;
	}

	if ((_collider[0].first && move == -1) || (_collider[2].first && move == 1))
	{
		if (speed > 1)
		{
			if (move == -1) { move = 1; } else { move = -1; }
		}
		else
		{
			move = 0;
		}
	}

	if (speed > 0) { speed -= 0.1f; } else { speed = 0; _capsule = true; }

	rect.left += move * (speed);  rect.right += move * (speed);
	object = rect;
	_funcJump();
}

void ArrowTile::update(Character::Observer * character)
{
	if (_capsule && character->_isDown == 2)
	{ 
		OBSERVER->item.setObserver(new Arrow(character),true);
		Gravity::Observer* gravity = this; gravity->_isdelete = true;
		ItemTile* tile = this; tile->_isdelete = true;
	}
	else
	{
		if (_capsule == false) { character->hp = 0; return; }
		_capsule = true;
	}
}

void ArrowTile::rander()
{
	image->setX(object.left);
	image->setY(object.top);
	CAMAERA->setRender(true, 4, nullptr, image);
	//CAMAERA->setRender(true, 4, &object,image);
}

#pragma endregion



#pragma region  Rock

Rock::Rock(Character::Observer* character)
{
	image = new Image();
	image->init("Resources/Item/rock.bmp", 64, 64, true, RGB(255, 0, 255));
	user = character;
	button = _isdelete = false;
	tag = Item::ROCK;
	rect = character->rect;
}

void Rock::update()
{
	MAP->_item.push_back(new RockTile(rect, direction));
	_isdelete = true;
}

void Rock::render()
{
	if (CAMAERA->inTheAngle(rect))
	{
		rect = { user->rect.left, user->rect.top, user->rect.left + 64, user->rect.top + 64 };
		image->setX(rect.left);
		image->setY(rect.top);
		CAMAERA->setRender(true, 4, &rect, image);
	}
}

void Rock::Interaction()
{
	if (button == true) { return; }
	else
	{
		button = true;
		direction = user->move.second;
	}
}

RockTile::RockTile(RECT rect, int direction)
{
	image = new Image();
	image->init("Resources/Item/rock.bmp", 64	, 64, true, RGB(255, 0, 255));
	this->move = direction;
	object = this->rect = { rect.left, rect.top, rect.left + 64, rect.top + 64 };
	tag = Item::ROCK;
	speed = gameSpeed + 3;
	Gravity::Observer* gravity = this;
	ItemTile* tile = this;
	tile->_isdelete = gravity->_isdelete = _capsule = false;
	isJump.second = -1;
	OBSERVER->grvity.setObserver(this);
}

void RockTile::update()
{
	if (_collider.size() == 0) { return; }

	if (!_collider[3].first)
	{
		isJump.first = true;
	}
	else
	{
	//	int error = (rect.bottom - _collider[3].second.top) + (gameSpeed - 0.1f);
		//if (error != 0) { isJump.first = false; }
		//rect.bottom -= error; rect.top -= error;
	}

	if ((_collider[0].first && move == -1) || (_collider[2].first && move == 1))
	{
		if (speed > 1)
		{
			if (move == -1) { move = 1; }
			else { move = -1; }
		}
		else
		{
			move = 0;
		}
	}

	if (speed > 0) { speed -= 0.1f; }
	else { speed = 0; _capsule = true; }

	rect.left += move * (speed);  rect.right += move * (speed);
	object = rect;
	_funcJump();
}

void RockTile::update(Character::Observer * character)
{
	if (_capsule && character->_isDown == 2)
	{
		OBSERVER->item.setObserver(new Rock(character), true);
		Gravity::Observer* gravity = this; gravity->_isdelete = true;
		ItemTile* tile = this; tile->_isdelete = true;
	}
	else
	{
		if (_capsule == false) { character->hp -= 1; return; }
		_capsule = true;
	}
}

void RockTile::rander()
{
	image->setX(object.left);
	image->setY(object.top);
	CAMAERA->setRender(true, 4, &object, image);
}

#pragma endregion



#pragma region  GoldTile

GoldTile::GoldTile(RECT rect,int size)
{
	image = new Image();
	image->init("Resources/Item/gold.bmp", 192, 64, 3, 1, true, RGB(255, 0, 255));
	image->setFrameX(size);
	switch (size)
	{
		case 0: { gold = 100; } break;
		case 1: { gold = 500; } break;
		case 2: { gold = 1000; } break;
		default: { ItemTile* tile = this; tile->_isdelete = true; } return;
	}
	this->rect = object = rect;
	tag = Item::GOLD;
	OBSERVER->grvity.setObserver(this);
	Gravity::Observer* gravity = this; gravity->_isdelete = false;
	ItemTile* tile = this; tile->_isdelete = false;
	_capsule = true;
}

void GoldTile::update()
{
	if (_collider.size() == 0) { return; }

	if (!_collider[3].first)
	{
		isJump.first = true;
	}
	else
	{
	//	int error = (rect.bottom - _collider[3].second.top) + (gameSpeed - 0.1f);
		//if (error != 0) { isJump.first = false; }
		//rect.bottom -= error; rect.top -= error;
	}
	_funcJump();
	object = rect;
}

void GoldTile::update(Character::Observer* character)
{
	character->gold += gold;
	Gravity::Observer* gravity = this; gravity->_isdelete = true;
	ItemTile* tile = this; tile->_isdelete = true;
}

void GoldTile::rander()
{
	image->setX(object.left);
	image->setY(object.top);
	CAMAERA->setRender(true, 4, nullptr, image);
}

#pragma endregion
