#include "Stdafx.h"
#include "Observer.h"
#include "Tiles.h"

#pragma region Character

void Character::Nexus::setObserver(Observer* set) { _observer.push_back(set); }

vector<Character::Observer*> Character::Nexus::getObserver() { return _observer; }

Character::Observer* Character::Nexus::getObserver(int i) { return _observer[i]; }

void Character::Nexus::clearObserver() { _observer.clear(); }

void Character::Nexus::clearObserver(int clear) { _observer.erase(_observer.begin() + clear); }

void Character::Nexus::reading(void)
{
	for (int h = 0; h < _observer.size(); h++) 
	{ 
		if (_observer[h]->_isdelete)
		{
			_observer.erase(_observer.begin() + h);
			break;
		}

		_observer[h]->update();
		_observer[h]->render();
		RECT temp;
		for (int i = 0; i < MAP->_item.size(); i++)
		{
			if (IntersectRect(&temp, &_observer[h]->rect, &MAP->_item[i]->object))
			{
				MAP->_item[i]->update(_observer[h]);
				break;
			}
		}
	}

}

#pragma endregion



#pragma region Item

void Item::Nexus::reading(void)
{
	for (int i = 0; i <_observer.size(); i++)
	{
		if (_observer[i]->_isdelete) 
		{ 
			_observer[i]->user->items.erase(_observer[i]->tag);
			for (int h = 0; h < _observer[i]->user->useItem.size(); h++)
			{
				if (_observer[h]->user->useItem.front() == _observer[i]->tag) 
				{ 
					_observer[i]->user->useItem.pop();
					break;
				}
			}

			for (int h = 0; h < _observer[i]->user->useItem.size(); h++)
			{
				if (_observer[h]->user->useItem.front() == Item::WHIP) { break; }
				_observer[h]->user->useItem.push(_observer[h]->user->useItem.front());
				_observer[h]->user->useItem.pop();
			}

			_observer.erase(_observer.begin() + i); 
			break;
		}

		if (_observer[i]->button) { _observer[i]->update(); }
	}
}

void Item::Nexus::setObserver(Observer* set,bool first)
{
	if (set->user != nullptr)
	{
		for (int i = 0; i < _observer.size(); i++)
		{
			if (_observer[i]->tag == set->tag)
			{
				RECT temp[2] = { {_observer[i]->user->rect},{set->user->rect} };
				if (temp[0].left == temp[1].left &&temp[0].left == temp[1].left && temp[0].left == temp[1].left && temp[0].left == temp[1].left)
				{
					_observer[i]->count += set->count;

					if (first)
					{
						for (int i = 0; i < set->user->useItem.size(); i++)
						{
							if (set->user->useItem.front() == set->tag) { break; }
							set->user->useItem.push(set->user->useItem.front());
							set->user->useItem.pop();
						}
					}

					return;
				}
			}
		}
		set->user->useItem.push(set->tag);
		set->user->items.insert({set->tag,set});

		if (first)
		{
			for (int i = 0; i < set->user->useItem.size(); i++)
			{
				if (set->user->useItem.front() == set->tag) { break; }
				set->user->useItem.push(set->user->useItem.front());
				set->user->useItem.pop();
			}
		}
	}
	_observer.push_back({ set });
	_observer.back()->_isdelete = false;
}

void Item::Nexus::clearObserver()
{ _observer.clear(); }

#pragma endregion

#pragma region Gravity

void Gravity::Nexus::setObserver(Observer* set) 
{ 
	_observer.push_back(set); 
	_observer.back()->_collider.resize(9);
	_observer.back()->_isdelete = false;
}

void Gravity::Nexus::clearObserver() { _observer.clear(); }

void Gravity::Nexus::reading(void)
{
	for (int g = 0; g < _observer.size(); g++)
	{
		if (_observer[g]->_isdelete)
		{
			_observer.erase(_observer.begin() + g);
			break;
		}

		POINT point = RectToPoint(_observer[g]->rect);
		point.x -= 32;
		point.y -= 64;
		point.x /= 64; point.y /= 64;
		pair<int, int> x = { point.x - 1, point.x + 1, };
		pair<int, int> y = { point.y - 1, point.y + 1, };

		int count = 0;
		for (int h = y.first; h <= y.second; h++)
		{
			for (int w = x.first; w <= x.second; w++)
			{
				_observer[g]->_collider[count] = { false, 0 };
				if (MAP->_tiles[h][w].type == Tile::Type::IMPOSSIBLE || MAP->_tiles[h][w].type == Tile::Type::WALL)
				{
					CAMAERA->setRender(true, 3, &MAP->_tiles[h][w].object, RGB(255, 0, 0), true, NULL_BRUSH);
					_observer[g]->_collider[count].first = true;
					switch (count)
					{
						case 0: case 3: case 6: { _observer[g]->_collider[count].second = MAP->_tiles[h][w].object.right;  } break;
						case 2: case 5: case 8: { _observer[g]->_collider[count].second = MAP->_tiles[h][w].object.left;  } break;
						case 1: { 	_observer[g]->_collider[count].second = MAP->_tiles[h][w].object.bottom;  } break;
						case 7: { 	_observer[g]->_collider[count].second = MAP->_tiles[h][w].object.top;  } break;
					}
				}
				count++;
			}
		}
	}
}

void Gravity::Observer::_funcJump()
{
	if (isJump.first == true)
	{
		if (isJump.second < gameSpeed)
		{
			isJump.second += -1 * 0.05f;
		}
		rect.top += -1 * isJump.second;
		rect.bottom += -1 * isJump.second;
	}
	else
	{
		isJump.second = 0;
	}
}

#pragma endregion



#pragma region Effect

void Effect::Nexus::reading(void)
{
	for (int h = 0; h < _observer.size(); h++)
	{
		if (_observer[h]->anime != nullptr)
		{
			_observer[h]->anime->frameUpdate(TIMEMANAGER->getElapsedTime() * 1);
		}

		CAMAERA->setRender(true, 4, nullptr, RGB(255, 0, 255), true, RGB(255, 0, 255), _observer[h]->image, _observer[h]->anime);

		if (!_observer[h]->anime->isPlay())
		{
			_observer.erase(_observer.begin() + h);
			break;
		}
	}
}

void Effect::Nexus::setObserver(Observer* set)
{
	_observer.push_back(set);
}

Effect::Observer* Effect::Nexus::getBack()
{
	return _observer.back();
}


#pragma endregion