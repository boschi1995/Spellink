#include "Stdafx.h"
#include "MainGame.h"
#include "ImageClass.h"

HRESULT MainGame::init(void) //ÃÊ±âÈ­
{
	GameNode::init(TRUE);
	ImageClass image; 
	image.init();
	TIMEMANAGER->init();
	scene.init();
	return S_OK;
}

void MainGame::release(void)
{
	GameNode::release();
	scene.release();
}

void MainGame::update(void)
{
	GameNode::update();
	scene.update();
	OBSERVER->update();
	MAP->update();
}

void MainGame::render(void)
{
	PatBlt(getMemDC(), 0, 0, WINSIZE_X, WINSIZE_Y, BLACKNESS);
	
	scene.render();
	TIMEMANAGER->render(getMemDC());

	this->getBackBuffer()->render(getHDC()); 
}