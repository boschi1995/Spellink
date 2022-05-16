#include "Stdafx.h"
#include "Thorn.h"

Thorn::Thorn(RECT rect)
{
	// 해당 위치에 추가 
	image = new Image();
	image->init("Resources/block/thorn.bmp", 128, 64, 2, 1, true, RGB(255, 0, 255));
	image->setX(rect.left);
	image->setY(rect.top);
	_isdelete = false;
	this->object = rect;
}

void Thorn::update(Character::Observer* character)
{
	if (character->hp <= 0) { image->setFrameX(1); } else { image->setFrameX(0); }
	if (character->isJump.first == false) { return; }
	character->hp = 0;
}

void Thorn::rander(void)
{
	CAMAERA->setRender(true, 2, nullptr, image);
	//CAMAERA->setRender(true, 2, &object, image);
}
