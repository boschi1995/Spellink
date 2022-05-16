#include "Stdafx.h"
#include "ImageClass.h"

HRESULT ImageClass::init(void)
{
	IMAGEMANAGER->addImage("backGround", "Resources/block/backGround.bmp", 3840, 1964);
	
	// player
	//IMAGEMANAGER->addFrameImage("²¿±òÁ¡ÇÁ", "Resources/Images/Player/playerFrontJumpOn.bmp", 1120, 158, 14, 2, MGT);
	IMAGEMANAGER->addFrameImage("playerIdle", "Resources/Player/idle.bmp", 512, 64, 8, 1,true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRun", "Resources/Player/run.bmp", 384, 128, 6, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerAttack", "Resources/Player/attack.bmp", 704, 128, 11, 2, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerRope", "Resources/Player/rope.bmp", 768, 96, 12, 1, true, RGB(255, 0, 255));
	IMAGEMANAGER->addFrameImage("playerStun", "Resources/Player/stun.bmp", 320, 128, 5, 2, true, RGB(255, 0, 255));

	// UI
	IMAGEMANAGER->addImage("Ui_Heart", "Resources/Ui/heart.bmp", 64, 64,true,RGB(255,0,255));
	IMAGEMANAGER->addImage("Ui_Boom", "Resources/Ui/boom.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ui_Rope", "Resources/Ui/rope.bmp", 64, 64, true, RGB(255, 0, 255));
	IMAGEMANAGER->addImage("Ui_Gold", "Resources/Ui/gold.bmp", 64, 64, true, RGB(255, 0, 255));

	//effect
	IMAGEMANAGER->addFrameImage("EffectBoom", "Resources/Effect/boom.bmp", 1728, 192, 9,1, true, RGB(255, 0, 255));

	return S_OK;
}

